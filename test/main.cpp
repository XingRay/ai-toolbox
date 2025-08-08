#include <iostream>

#include <opencv2/opencv.hpp>
#include "Log.h"
#include "Renderer.h"

cv::VideoCapture cap;
std::unique_ptr<test::Renderer> mRenderer;
GLFWwindow* mWindow;
const int32_t mWidth = 640;
const int32_t mHeight = 480;

void init();

void mainLoop();

void cleanUp();

int main() {
    init();
    mainLoop();
    cleanUp();
}

void init() {
    cap = cv::VideoCapture(0);
    if (!cap.isOpened()) {
        LOG_E("错误：无法打开视频文件或摄像头！");
        return;
    }

    mRenderer = std::make_unique<test::Renderer>();

    glfwInit();

    // Because GLFW was originally designed to create an OpenGL context,
    // we need to tell it to not create an OpenGL context with a subsequent call:
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // Because handling resized windows takes special care that we'll look into later, disable it for now
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    mWindow = glfwCreateWindow(mWidth, mHeight, "ai-toolbox", nullptr, nullptr);
    // 将 this 指针保存到window对象中， 这样可以在callback中取出， 这里使用 lambda， 可以不需要
    glfwSetWindowUserPointer(mWindow, mRenderer.get());
    glfwSetFramebufferSizeCallback(mWindow, [](GLFWwindow* window, int width, int height) {
        test::Renderer* renderer = reinterpret_cast<test::Renderer*>(glfwGetWindowUserPointer(window));
        (*renderer).onWindowResized(width, height);
    });
    (*mRenderer).init(mWindow, mWidth, mHeight);
}

void mainLoop() {
    cv::Mat frame;

    while (!glfwWindowShouldClose(mWindow)) {
        glfwPollEvents();

        cap.read(frame);
        if (frame.empty()) {
            LOG_D("cap frame is empty");
            break;
        }

        (*mRenderer).drawFrame(frame);
    }
}

void cleanUp() {
    cap.release();
    (*mRenderer).cleanUp();
    glfwDestroyWindow(mWindow);
}
