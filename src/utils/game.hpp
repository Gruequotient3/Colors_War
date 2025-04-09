#ifndef GAME_HPP
#define GAME_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Game{
    private:
        void Init();

        void SetParameters();
        void SetCallback();
        void ProcessInput();

        // Callback
        static void FrameBufferSizeCallback(GLFWwindow *window, int width, int height);

    public:
        static GLFWwindow *window;

        Game();
        ~Game();

        void Update();

};

#endif
