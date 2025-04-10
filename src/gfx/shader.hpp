#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

#include <glm/glm.hpp>

class Shader{
    private:
        void CheckCompileErrors(unsigned int shader, std::string type);
    public:
        unsigned int id;

        Shader(const char *vertexPath, const char *fragmentPath);
        ~Shader();

        void Use();

        void SetBool(const std::string &name, bool value) const;
        void SetFloat(const std::string &name, float value) const;
        void SetFloatp(const std::string &name, int count, float* value) const;
        void SetInt(const std::string &name, int value) const;
        void SetVec3(const std::string &name, glm::vec3 value) const;
        void SetVec3p(const std::string &name, int count, const float* value) const;
        void SetMat4(const std::string &name, GLboolean transpose, const GLfloat *value) const;
};


#endif
