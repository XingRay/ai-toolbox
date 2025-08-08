#include "Renderer.h"

#include <opencv2/imgproc.hpp>

#include "Log.h"
#include "util/FileUtil.h"
#include "vklite_engine/graphic_pipeline_engine/WindowsGraphicPipelineEngineBuilder.h"
#include "vklite/plugin/validation/ValidationPlugin.h"

namespace test {
    Renderer::Renderer()
        : mWindow(nullptr) {
    }

    Renderer::~Renderer() = default;

    void Renderer::init(GLFWwindow* window, int width, int height) {
        mWidth = width;
        mHeight = height;
        LOG_D("Test01::init: window:%p, width:%d, height:%d", window, width, height);

        std::vector<uint32_t> vertexShaderCode = util::FileUtil::loadSpvFile("resource/spv/05_texture_image.vert.spv");
        std::vector<uint32_t> fragmentShaderCode = util::FileUtil::loadSpvFile("resource/spv/05_texture_image.frag.spv");

        vklite::ShaderConfigure shaderConfigure = vklite::ShaderConfigure()
                .vertexShaderCode(std::move(vertexShaderCode))
                .fragmentShaderCode(std::move(fragmentShaderCode))
                .addVertexBinding([&](vklite::VertexBindingConfigure& vertexBindingConfigure) {
                    vertexBindingConfigure
                            .binding(0)
                            .stride(sizeof(Vertex))
                            .addAttribute(0, ShaderFormat::Vec3)
                            .addAttribute(1, ShaderFormat::Vec2);
                })
                .addDescriptorSetConfigure([&](vklite::DescriptorSetConfigure& descriptorSetConfigure) {
                    descriptorSetConfigure
                            .set(0)
                            .addCombinedImageSampler(0, vk::ShaderStageFlagBits::eFragment);
                });

        mEngine = vklite::WindowsGraphicPipelineEngineBuilder::asDefault(window)
                .shaderConfigure(std::move(shaderConfigure))
                .addInstancePlugin(vklite::ValidationPlugin::buildUnique())
                .clearColor(0.2f, 0.4f, 0.8f)
                .buildUnique();
        LOG_D("mEngine: build end");


        std::vector<Vertex> vertices = {
            {{-1.0f, -1.0f, 0.0f}, {0.0f, 1.0f}}, // 左上
            {{1.0f, -1.0f, 0.0f}, {1.0f, 1.0f}}, // 右上
            {{-1.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}, // 左下
            {{1.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}, // 右下

        };

        std::vector<uint32_t> indices = {
            0, 2, 1, 1, 2, 3,
        };

        uint32_t indicesSize = indices.size() * sizeof(uint32_t);
        mIndexBuffer = mEngine->indexBufferBuilder()
                .size(indicesSize)
                .buildUnique();
        mIndexBuffer->update(mEngine->getCommandPool(), indices);
        mEngine->indexBuffer(*mIndexBuffer, indices.size());

        uint32_t verticesSize = vertices.size() * sizeof(Vertex);
        mVertexBuffer = mEngine->vertexBufferBuilder()
                .size(verticesSize)
                .buildUnique();
        mVertexBuffer->update(mEngine->getCommandPool(), vertices.data(), verticesSize);
        mEngine->addVertexBuffer(*mVertexBuffer);


        mSamplers = mEngine->samplerBuilder().asTexture()
                .width(mWidth)
                .height(mHeight)
                .format(vk::Format::eR8G8B8A8Srgb)
                .build(mEngine->getFrameCount());

        for (uint32_t i = 0; i < mEngine->getFrameCount(); i++) {
            mSamplers[i].getImage().changeImageLayout(mEngine->getCommandPool());
        }

        mEngine->updateDescriptorSets([&](uint32_t frameIndex, vklite::DescriptorSetMappingConfigure& configure) {
            configure
                    .descriptorSet(mEngine->getDescriptorSets(frameIndex, 0))
                    .addCombinedImageSampler([&](vklite::CombinedImageSamplerDescriptorMapping& mapping) {
                        mapping
                                .addImageInfo(mSamplers[frameIndex].getSampler(), mSamplers[frameIndex].getImageView());
                    });
        });
    }

    void Renderer::cleanUp() {
        LOG_D("Renderer::cleanUp()");
    }

    void Renderer::drawFrame(const cv::Mat& frame) {
        LOG_D("Renderer::drawFrame(): [%dx%d]", frame.cols, frame.rows);
        cv::Mat flipped;
        // -1 : 左右和上下同时翻转
        cv::flip(frame, flipped, -1);
        cv::Mat rgba;
        cv::cvtColor(flipped, rgba, cv::COLOR_BGR2RGBA); // 转为 4 通道

        try {
            uint32_t pixelBytes = rgba.total() * rgba.elemSize();
            LOG_D("pixelBytes:%d", pixelBytes);
            mSamplers[(*mEngine).getFrameIndex()].update(mEngine->getCommandPool(), rgba.data, rgba.total() * rgba.elemSize());
        } catch (const vk::SystemError& error) {
            LOG_E("Renderer::drawFrame(): vk::SystemError: %s", error.what());
        }

        mEngine->drawIndexed();
    }

    void Renderer::onWindowResized(int width, int height) {
        LOG_D("Renderer::onWindowResized: width:%d, height:%d", width, height);
    }
}
