#ifndef MESH_CPP
#define MESH_CPP

#include "mesh.hpp"

#include <iostream>

Mesh::Mesh() : vao{0}, vbo{0}, ebo{0} { }

Mesh::~Mesh(){
    DestroyMesh();
}

void Mesh::GenerateMesh(){
    if (!vao) glGenVertexArrays(1, &vao);
    if (!vbo) glGenBuffers(1, &vbo);
    if (!ebo) glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, normal));

    // TexCoord
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex),
                          (void*)offsetof(Vertex, texCoord));

    glBindVertexArray(0);
}

void Mesh::DestroyMesh(){
    if (vao) { glDeleteVertexArrays(1, &vao); vao = 0;}
    if (vbo) { glDeleteBuffers(1, &vbo); vbo = 0;} 
    if (ebo) { glDeleteBuffers(1, &ebo); ebo = 0;}
}

void Mesh::Draw(Shader &shader){
    shader.Use();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}


Mesh Mesh::GetQuadMesh(){
    Mesh mesh;
    mesh.vertices = std::vector<Vertex>{
        {glm::vec3(-0.5f, -0.5f, 0.0), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0, 1)},
        {glm::vec3( 0.5f, -0.5f, 0.0), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1, 1)},
        {glm::vec3( -0.5f,  0.5f, 0.0), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0, 0)},
        {glm::vec3( 0.5f,  0.5f, 0.0), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1, 0)},
    };
    mesh.indices = std::vector<unsigned int>{
        0, 1, 2,
        1, 3, 2
    };

    return mesh;
}

#endif
