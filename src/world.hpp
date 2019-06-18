#ifndef WORLD_H_
#define WORLD_H_

#include "chunk.hpp"
#include "shader.hpp"

// TODO
static const int SIZE = WORLD_SIZE * CHUNK_SIZE;

class World
{ public:

   // TODO
   World()
   {
      for       (int x = -SIZE / 2; x < SIZE / 2; x += CHUNK_SIZE)
         for    (int y = -SIZE / 2; y < SIZE / 2; y += CHUNK_SIZE)
            for (int z = -SIZE / 2; z < SIZE / 2; z += CHUNK_SIZE)
            {
               glm::vec3 v(x, y, z);
               chunks[cindex(v)] = new Chunk(v);
            }
   }

   // TODO
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
#if 0
      int r = rad / CHUNK_SIZE + 1;
      for       (int x = -r; x <= r; x++)
         for    (int y = -r; y <= r; y++)
            for (int z = -r; z <= r; z++)
            {
               size_t i = cindex(glm::vec3(x, y, z) * float(CHUNK_SIZE) + pos);
               if (i < SIZE_MAX) chunks[i]->dig(pos, rad, amt);
            }
#else
      for (int c = 0; c < glm::pow(WORLD_SIZE, 3); c++)
      {
         chunks[c]->dig(pos, rad, amt);
      }
#endif
   }

private:

   // TODO
   Chunk* chunks[size_t(glm::pow(WORLD_SIZE, 3))];

   // TODO
   static size_t cindex(glm::vec3 pos)
   {
      for (int d = 0; d < 3; d++)
      {
         if (glm::abs(pos[d] > SIZE / 2)) return SIZE_MAX;
      }
      glm::vec3 v = glm::vec3(WORLD_SIZE / 2) + pos / float(CHUNK_SIZE);
      return v.x + WORLD_SIZE * (v.y + WORLD_SIZE * v.z);
   }
};

#endif
