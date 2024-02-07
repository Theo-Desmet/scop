#include "scop/Obj.hpp"
#include "scop/ParserObj.hpp"
#include <fstream>

Obj::Obj(std::string objFileName) {
}

Obj::Obj(std::vector<Vertex> vertices, Texture textures) {
	this->vertices = vertices;
	this->textures = textures;

	setupObj();
}

void Obj::setupObj() {
	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);
  
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, id.size() * sizeof(unsigned int), 
    //              &id[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex texture coords
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TextureCoords));
    // vertex normal
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    glBindVertexArray(0);
}

void Obj::Draw(Shader &shader) 
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;

    // for(unsigned int i = 0; i < textures.size(); i++)
    // {
        glActiveTexture(GL_TEXTURE0); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        // std::string number;
        // std::string name = textures[i].type;
        // if(name == "texture_diffuse")
        //     number = std::to_string(diffuseNr++);
        // else if(name == "texture_specular")
        //     number = std::to_string(specularNr++);

        // shader.setInt((textures.type).c_str());
        glBindTexture(GL_TEXTURE_2D, textures.id);
    // }
    // glActiveTexture(GL_TEXTURE0);

    // draw mesh
    glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
