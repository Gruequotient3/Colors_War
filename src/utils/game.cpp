#ifndef GAME_CPP
#define GAME_CPP

#include "game.hpp"

#include <iostream>
#include <cstdlib>


GLFWwindow *Game::window = nullptr;
Game::Game(){
    Init();
}

Game::~Game(){
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Game::Init(){
    // Initialise GLFW
    if (!glfwInit()){
        std::cout << "Failed to initialise GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    // OpenGL context Parameters
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Initialise OpenGL context
    window = glfwCreateWindow(640, 320, "Color Battle", NULL, NULL);
    if (!window){
        std::cout << "Failed to initialise OpenGL Context" << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    // Initialise GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialise GLAD" << std::endl;
        glfwTerminate();
        glfwDestroyWindow(window);
        exit(EXIT_FAILURE);
    }

    SetParameters();
}

void Game::Update(){
    while(!glfwWindowShouldClose(window)){
        ProcessInput();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Game::SetParameters(){
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
}

void Game::SetCallback(){
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
}

void Game::ProcessInput(){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

void Game::FrameBufferSizeCallback(GLFWwindow *, int width, int height){
    glViewport(0, 0, width, height);

}

#endif
