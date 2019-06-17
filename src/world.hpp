#ifndef WORLD_H_
#define WORLD_H_

#include "chunk.hpp"

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
   static size_t cindex(glm::vec3 pos)
   {
      for (int d = 0; d < 3; d++)
      {
         if (glm::abs(pos[d] > SIZE / 2)) return SIZE_MAX;
      }
      glm::vec3 v = glm::vec3(WORLD_SIZE / 2) + pos / float(CHUNK_SIZE);
      return v.x + WORLD_SIZE * (v.y + WORLD_SIZE * v.z);
   }

private:

   // TODO
   Chunk* chunks[size_t(glm::pow(WORLD_SIZE, 3))];
};

#endif
