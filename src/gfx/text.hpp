#ifndef TEXT_HPP
#define TEXT_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>
#include <string>

#include "shader.hpp"

struct Character{
    unsigned int textureId;     // Id of the texture
    glm::vec2 size;             // size of glyph
    glm::vec2 bearing;          // offset form baseling to left/top glyph
    unsigned int advance;       // offset to advance to next glyph
};

class TextMesh{
    private:
        unsigned int vao, vbo;
        std::map<char, Character> characters;
    public:
        Shader shader;
        TextMesh();

        void GenerateMesh();
        void DestroyMesh();
        void LoadListCharacter();
        void SetShader(Shader &shader);
        void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);
};




#endif