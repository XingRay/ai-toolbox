//
// Created by leixing on 2025-07-13.
//

#pragma once

#include <cstdint>
#include <memory>

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <opencv2/core.hpp>

#include "vklite/vklite.h"
#include "vklite_engine/graphic_pipeline_engine/GraphicPipelineEngine.h"

#include <ncnn/mat.h>
#include <ncnn/net.h>

namespace test {
    class Vertex {
    public:
        glm::vec3 position;
        glm::vec2 uv;
    };

    class Renderer {
    private:
        int32_t mWidth = 0;
        int32_t mHeight = 0;
        GLFWwindow* mWindow;

        // config
        bool mMsaaEnable = false;
        bool mDepthTestEnable = false;
        std::array<float, 4> mClearColor = {0.0f, 0.0f, 0.0f, 1.0f};
        float mClearDepth = 1.0f;
        uint32_t mFrameCount = 2;
        vk::SampleCountFlagBits mSampleCount;

        // vulkan instance
        std::unique_ptr<vklite::Instance> mInstance;
        std::unique_ptr<vklite::Surface> mSurface;
        std::unique_ptr<vklite::PhysicalDevice> mPhysicalDevice;

        std::unique_ptr<vklite::Device> mDevice;

        std::unique_ptr<vklite::Queue> mGraphicQueue;
        std::unique_ptr<vklite::Queue> mComputeQueue;
        std::unique_ptr<vklite::Queue> mPresentQueue;

        std::unique_ptr<vklite::Swapchain> mSwapchain;
        std::vector<vklite::ImageView> mDisplayImageViews;
        std::vector<vk::Viewport> mViewports;
        std::vector<vk::Rect2D> mScissors;

        std::unique_ptr<vklite::CommandPool> mCommandPool;
        std::unique_ptr<vklite::CommandBuffers> mCommandBuffers;
        std::unique_ptr<vklite::CommandBuffers> mComputeCommandBuffers;

        std::unique_ptr<vklite::RenderPass> mRenderPass;
        std::unique_ptr<vklite::CombinedImageView> mColorImageView;
        std::unique_ptr<vklite::CombinedImageView> mDepthImageView;
        vklite::Framebuffers mFramebuffers;

        std::vector<vklite::Semaphore> mImageAvailableSemaphores;
        std::vector<vklite::Semaphore> mRenderFinishedSemaphores;
        std::vector<vklite::Fence> mFences;


        std::unique_ptr<vklite::DescriptorPool> mDescriptorPool;


        //status
        uint32_t mCurrentFrameIndex = 0;
        bool mFramebufferResized = false;


        // image preprocess compute pipeline
        std::unique_ptr<vklite::CombinedPipeline> mPreprocessPipeline;
        std::vector<vklite::Fence> mComputeFences;
        std::vector<vklite::Semaphore> mComputeFinishSemaphores;

        // input
        std::unique_ptr<vklite::CombinedImageView> mCameraInputSampler;
        std::unique_ptr<vklite::CombinedImageView> mCameraInputImageView;

        // param
        std::vector<vklite::UniformBuffer> mLetterboxParamsUniformBuffers;

        // output
        std::vector<ncnn::VkMat> mLetterBoxOutputNcnnBuffers;
//        std::vector<ncnn::VkImageMat> mLetterBoxOutputNcnnImages;
//        std::vector<vklite::CombinedImageView> mLetterBoxOutputImageViews;


        //preview pipeline
        std::unique_ptr<vklite::CombinedPipeline> mPreviewPipeline;
        // vertex buffer
        std::unique_ptr<vklite::VertexBuffer> mVertexBuffer;
        std::vector<vk::Buffer> mVertexBuffers;
        std::vector<vk::DeviceSize> mVertexBufferOffsets;

        // index buffer
        std::unique_ptr<vklite::IndexBuffer> mIndexBuffer;
        vk::Buffer mIndexVkBuffer;
        uint32_t mIndexCount;

        std::vector<vklite::Sampler> mPreprocessOutputImageSamplers;


        // lines pipeline resources
        std::unique_ptr<vklite::CombinedPipeline> mLinesPipeline;
        // vertex buffer
        std::unique_ptr<vklite::VertexBuffer> mLinesVertexBuffer;
        std::vector<vk::Buffer> mLinesVertexBuffers;
        std::vector<vk::DeviceSize> mLinesVertexBufferOffsets;

        // index buffer
        std::unique_ptr<vklite::IndexBuffer> mLinesIndexBuffer;
        vk::Buffer mLinesIndexVkBuffer;
        uint32_t mLinesIndexCount;

        std::vector<vklite::UniformBuffer> mLinesUniformBuffers;


        // points pipeline resources
        std::unique_ptr<vklite::CombinedPipeline> mPointsPipeline;
        // vertex buffer
        std::unique_ptr<vklite::VertexBuffer> mPointsVertexBuffer;
        std::vector<vk::Buffer> mPointsVertexBuffers;
        std::vector<vk::DeviceSize> mPointsVertexBufferOffsets;
        uint32_t mPointsCount;

        std::vector<vklite::UniformBuffer> mPointsUniformBuffers;

        std::unique_ptr<vklite::IndexBuffer> mIndexBuffer;
        std::unique_ptr<vklite::VertexBuffer> mVertexBuffer;

        std::vector<vklite::CombinedImageSampler> mSamplers;

    public:
        explicit Renderer();

        ~Renderer();

        void init(GLFWwindow* window, int width, int height);

        void cleanUp();

        void drawFrame(const cv::Mat& frame);

        void onWindowResized(int width, int height);
    };
} // test
