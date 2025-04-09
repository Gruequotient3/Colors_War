#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

class Shader{
    private:
        void CheckCompileErrors(unsigned int shader, std::string type);
    public:
        unsigned int id;

        Shader(const char *vertexPath, const char *fragmentPath);
        ~Shader();

        void Use();
};


#endif
