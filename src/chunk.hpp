#ifndef CHUNK_H_
#define CHUNK_H_

#include <glm/glm.hpp>

// Used for translate
#include <glm/gtc/matrix_transform.hpp>

GLfloat v[] = {
   // front
   -1.0, -1.0,  1.0,    0.0,  0.0,  1.0,
    1.0, -1.0,  1.0,    1.0,  0.0,  1.0,
    1.0,  1.0,  1.0,    1.0,  1.0,  1.0,
   -1.0,  1.0,  1.0,    0.0,  1.0,  1.0,
   // back
   -1.0, -1.0, -1.0,    0.0,  0.0,  0.0,
    1.0, -1.0, -1.0,    1.0,  0.0,  0.0,
    1.0,  1.0, -1.0,    1.0,  1.0,  0.0,
   -1.0,  1.0, -1.0,    0.0,  1.0,  0.0
};

GLuint e[] = {
   // front
   0, 1, 2,
   2, 3, 0,
   // right
   1, 5, 6,
   6, 2, 1,
   // back
   7, 6, 5,
   5, 4, 7,
   // left
   4, 0, 3,
   3, 7, 4,
   // bottom
   4, 5, 1,
   1, 0, 4,
   // top
   3, 2, 6,
   6, 7, 3
};

class Chunk
{ public:

   Chunk()
   {
      model = glm::mat4(1.0f);

      glGenVertexArrays(1, &VAO);
      glGenBuffers(1, &VBO);
      glGenBuffers(1, &EBO);
      glBindVertexArray(VAO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(e), e, GL_STATIC_DRAW);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                                            (GLvoid*)0);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                                            (GLvoid*)(3 * sizeof(GLfloat)));
      glEnableVertexAttribArray(1);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
   }

   ~Chunk()
   {
      glDeleteVertexArrays(1, &VAO);
      glDeleteBuffers(1, &VBO);
      glDeleteBuffers(1, &EBO);
   }

   glm::mat4 getModel() const
   {
      return model;
   }

   void draw() const
   {
      glBindVertexArray(VAO);
      glDrawElements(GL_TRIANGLES, sizeof e / sizeof *e, GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);
   }

private:

   GLuint VBO, VAO, EBO;
   glm::mat4 model;
};

#endif
