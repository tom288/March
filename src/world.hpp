#ifndef WORLD_H_
#define WORLD_H_

#include "chunk.hpp"
#include "shader.hpp"

// The number of grid cubes found along every axis
static const int SIZE = WORLD_SIZE * CHUNK_SIZE;

class World
{ public:

   // Initialises chunks
   World()
   {
      for       (int x = (CHUNK_SIZE - SIZE) / 2; x < SIZE / 2; x += CHUNK_SIZE)
         for    (int y = (CHUNK_SIZE - SIZE) / 2; y < SIZE / 2; y += CHUNK_SIZE)
            for (int z = (CHUNK_SIZE - SIZE) / 2; z < SIZE / 2; z += CHUNK_SIZE)
            {
               glm::vec3 v(x, y, z);
               chunks[cindex(v)] = new Chunk(v);
            }
   }

   // Frees dynamically allocated memory
   ~World()
   {
      for (int c = 0; c < glm::pow(WORLD_SIZE, 3); c++) delete chunks[c];
   }

   // TODO
   void draw(Shader shader)
   {
      for (int c = 0; c < glm::pow(WORLD_SIZE, 3); c++)
      {
         shader.setMat4("model", chunks[c]->getModel());
         chunks[c]->draw();
      }
   }

   // TODO
   void dig(glm::vec3 pos, float rad, float amt)
   {
      int r = 1 + rad / CHUNK_SIZE;
      for       (int x = -r; x <= r; x++)
         for    (int y = -r; y <= r; y++)
            for (int z = -r; z <= r; z++)
            {
               size_t i = cindex(pos + glm::vec3(x, y, z) * float(CHUNK_SIZE));
               if (i < SIZE_MAX) chunks[i]->dig(pos, rad, amt);
            }
   }

private:

   // All of the chunks
   Chunk* chunks[size_t(glm::pow(WORLD_SIZE, 3))];

   // Returns the index of chunks corresponding to position pos
   static size_t cindex(glm::vec3 pos)
   {
      glm::vec3 v = glm::vec3(WORLD_SIZE / 2) + pos / float(CHUNK_SIZE);

      for (int d = 0; d < 3; d++)
      {
         v[d] = glm::floor(v[d]);
         if (v[d] >= WORLD_SIZE || v[d] < 0) return SIZE_MAX;
      }

      return v.x + WORLD_SIZE * (v.y + WORLD_SIZE * v.z);
   }
};

#endif
