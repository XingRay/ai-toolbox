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

        std::unique_ptr<vklite::GraphicPipelineEngine> mEngine;
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
