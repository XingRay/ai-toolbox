#include "Renderer.h"

#include "Log.h"
#include "util/FileUtil.h"
#include "vklite_engine/graphic_pipeline_engine/WindowsGraphicPipelineEngineBuilder.h"

namespace test {
    Renderer::Renderer()
        : mWindow(nullptr) {
    }

    Renderer::~Renderer() = default;

    void Renderer::init(GLFWwindow* window, int width, int height) {
        LOG_D("Test01::init: window:%p, width:%d, height:%d", window, width, height);
        std::vector<uint32_t> vertexShaderCode = util::FileUtil::loadSpvFile("spv/01_triangle.vert.spv");
        std::vector<uint32_t> fragmentShaderCode = util::FileUtil::loadSpvFile("spv/01_triangle.frag.spv");
        LOG_D("vertexShaderCode.size:%zd, fragmentShaderCode.size:%zd", vertexShaderCode.size(), fragmentShaderCode.size());

        vklite::ShaderConfigure shaderConfigure = vklite::ShaderConfigure()
                .vertexShaderCode(std::move(vertexShaderCode))
                .fragmentShaderCode(std::move(fragmentShaderCode))
                .addVertexBinding([&](vklite::VertexBindingConfigure& vertexBindingConfigure) {
                    vertexBindingConfigure
                            .binding(0)
                            .stride(sizeof(Vertex))
                            .addAttribute(0, ShaderFormat::Vec3);
                });

        LOG_D("mEngine: build");
        mEngine = vklite::WindowsGraphicPipelineEngineBuilder::asDefault(window)
                .shaderConfigure(std::move(shaderConfigure))
                .clearColor(0.2f, 0.4f, 0.8f)
                .buildUnique();
        LOG_D("mEngine: build end");

        std::vector<Vertex> vertices = {
            {{1.0f, -1.0f, 0.0f}},
            {{-1.0f, -1.0f, 0.0f}},
            {{0.0f, 1.0f, 0.0f}},
        };

        std::vector<uint32_t> indices = {0, 1, 2};

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
    }

    void Renderer::cleanUp() {
        LOG_D("Renderer::cleanUp()");
    }

    void Renderer::drawFrame(const cv::Mat& frame) {
        LOG_D("Renderer::drawFrame(): [%dx%d]", frame.cols, frame.rows);
        mEngine->drawIndexed();
    }

    void Renderer::onWindowResized(int width, int height) {
        LOG_D("Renderer::onWindowResized: width:%d, height:%d", width, height);
    }
}
