//
// Created by leixing on 2025-07-13.
//

#pragma once

#include <cstdint>
#include <memory>

#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <opencv2/core.hpp>

#include "vklite/vklite.h"
#include "vklite_engine/graphic_pipeline_engine/GraphicPipelineEngine.h"

namespace test {
    class Vertex {
    public:
        glm::vec3 pos;
    };

    class Renderer {
    private:
        const int32_t mWidth = 1024;
        const int32_t mHeight = 1024;
        GLFWwindow* mWindow;

        std::unique_ptr<vklite::GraphicPipelineEngine> mEngine;
        std::unique_ptr<vklite::IndexBuffer> mIndexBuffer;
        std::unique_ptr<vklite::VertexBuffer> mVertexBuffer;

    public:
        explicit Renderer();

        ~Renderer();

        void init(GLFWwindow* window, int width, int height);

        void cleanUp();

        void drawFrame(const cv::Mat& frame);

        void onWindowResized(int width, int height);
    };
} // test
