#ifndef CUBE_H_
#define CUBE_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// TODO
static const GLfloat v[36 * 6] = {
   -1.0f, -1.0f, -1.0f,    0.583f,  0.771f,  0.014f,
   -1.0f, -1.0f,  1.0f,    0.609f,  0.115f,  0.436f,
   -1.0f,  1.0f,  1.0f,    0.327f,  0.483f,  0.844f,
    1.0f,  1.0f, -1.0f,    0.822f,  0.569f,  0.201f,
   -1.0f, -1.0f, -1.0f,    0.435f,  0.602f,  0.223f,
   -1.0f,  1.0f, -1.0f,    0.310f,  0.747f,  0.185f,
    1.0f, -1.0f,  1.0f,    0.597f,  0.770f,  0.761f,
   -1.0f, -1.0f, -1.0f,    0.559f,  0.436f,  0.730f,
    1.0f, -1.0f, -1.0f,    0.359f,  0.583f,  0.152f,
    1.0f,  1.0f, -1.0f,    0.483f,  0.596f,  0.789f,
    1.0f, -1.0f, -1.0f,    0.559f,  0.861f,  0.639f,
   -1.0f, -1.0f, -1.0f,    0.195f,  0.548f,  0.859f,
   -1.0f, -1.0f, -1.0f,    0.014f,  0.184f,  0.576f,
   -1.0f,  1.0f,  1.0f,    0.771f,  0.328f,  0.970f,
   -1.0f,  1.0f, -1.0f,    0.406f,  0.615f,  0.116f,
    1.0f, -1.0f,  1.0f,    0.676f,  0.977f,  0.133f,
   -1.0f, -1.0f,  1.0f,    0.971f,  0.572f,  0.833f,
   -1.0f, -1.0f, -1.0f,    0.140f,  0.616f,  0.489f,
   -1.0f,  1.0f,  1.0f,    0.997f,  0.513f,  0.064f,
   -1.0f, -1.0f,  1.0f,    0.945f,  0.719f,  0.592f,
    1.0f, -1.0f,  1.0f,    0.543f,  0.021f,  0.978f,
    1.0f,  1.0f,  1.0f,    0.279f,  0.317f,  0.505f,
    1.0f, -1.0f, -1.0f,    0.167f,  0.620f,  0.077f,
    1.0f,  1.0f, -1.0f,    0.347f,  0.857f,  0.137f,
    1.0f, -1.0f, -1.0f,    0.055f,  0.953f,  0.042f,
    1.0f,  1.0f,  1.0f,    0.714f,  0.505f,  0.345f,
    1.0f, -1.0f,  1.0f,    0.783f,  0.290f,  0.734f,
    1.0f,  1.0f,  1.0f,    0.722f,  0.645f,  0.174f,
    1.0f,  1.0f, -1.0f,    0.302f,  0.455f,  0.848f,
   -1.0f,  1.0f, -1.0f,    0.225f,  0.587f,  0.040f,
    1.0f,  1.0f,  1.0f,    0.517f,  0.713f,  0.338f,
   -1.0f,  1.0f, -1.0f,    0.053f,  0.959f,  0.120f,
   -1.0f,  1.0f,  1.0f,    0.393f,  0.621f,  0.362f,
    1.0f,  1.0f,  1.0f,    0.673f,  0.211f,  0.457f,
   -1.0f,  1.0f,  1.0f,    0.820f,  0.883f,  0.371f,
    1.0f, -1.0f,  1.0f,    0.982f,  0.099f,  0.879f
};

class Cube
{ public:

   // TODO
   Cube()
   {
      model = glm::mat4(1.0f);

      // TODO
      glGenVertexArrays(1, &VAO);
      glGenBuffers(1, &VBO);
      glBindVertexArray(VAO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                                            (GLvoid*)0);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                                            (GLvoid*)(3 * sizeof(GLfloat)));
      glEnableVertexAttribArray(1);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
   }

   // TODO
   ~Cube()
   {
      glDeleteVertexArrays(1, &VAO);
      glDeleteBuffers(1, &VBO);
   }

   // TODO
   glm::mat4 getModel() const
   {
      return model;
   }

   // TODO
   void draw() const
   {
      glBindVertexArray(VAO);
      glDrawArrays(GL_TRIANGLES, 0, 36);
      glBindVertexArray(0);
   }

private:

   // TODO
   GLuint VBO, VAO;

   // TODO
   glm::mat4 model;
};

#endif
