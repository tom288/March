#ifndef CHUNK_H_
#define CHUNK_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iomanip>
#include "osn.h"

// Triangulation table for all possible cube configurations
static const GLuint64 tris[256] = {
0xffffffffffffffff, 0x083fffffffffffff, 0x019fffffffffffff, 0x183981ffffffffff,
0x12afffffffffffff, 0x08312affffffffff, 0x92a029ffffffffff, 0x2832a8a98fffffff,
0x3b2fffffffffffff, 0x0b28b0ffffffffff, 0x19023bffffffffff, 0x1b219b98bfffffff,
0x3a1ba3ffffffffff, 0x0a108a8bafffffff, 0x3903b9ba9fffffff, 0x98aa8bffffffffff,
0x478fffffffffffff, 0x430734ffffffffff, 0x019847ffffffffff, 0x419471731fffffff,
0x12a847ffffffffff, 0x34730412afffffff, 0x92a902847fffffff, 0x2a9297273794ffff,
0x8473b2ffffffffff, 0xb47b24204fffffff, 0x90184723bfffffff, 0x47b94b9b2921ffff,
0x3a13ba784fffffff, 0x1ba14b1047b4ffff, 0x47890b9bab03ffff, 0x47b4b99bafffffff,
0x954fffffffffffff, 0x954083ffffffffff, 0x054150ffffffffff, 0x854835315fffffff,
0x12a954ffffffffff, 0x30812a495fffffff, 0x52a542402fffffff, 0x2a5325354348ffff,
0x95423bffffffffff, 0x0b208b495fffffff, 0x05401523bfffffff, 0x21525828b485ffff,
0xa3ba13954fffffff, 0x4950818a18baffff, 0x54050b5bab03ffff, 0x54858aa8bfffffff,
0x978579ffffffffff, 0x930953573fffffff, 0x078017157fffffff, 0x153357ffffffffff,
0x978957a12fffffff, 0xa12950530573ffff, 0x802825857a52ffff, 0x2a5253357fffffff,
0x7957893b2fffffff, 0x95797292027bffff, 0x23b018178157ffff, 0xb21b17715fffffff,
0x958857a13a3bffff, 0x5705097b010aba0f, 0xba0b03a50807570f, 0xba57b5ffffffffff,
0xa65fffffffffffff, 0x0835a6ffffffffff, 0x9015a6ffffffffff, 0x1831985a6fffffff,
0x165261ffffffffff, 0x165126308fffffff, 0x965906026fffffff, 0x598582526328ffff,
0x23ba65ffffffffff, 0xb08b20a65fffffff, 0x01923b5a6fffffff, 0x5a61929b298bffff,
0x63b653513fffffff, 0x08b0b50515b6ffff, 0x3b6036065059ffff, 0x65969bb98fffffff,
0x5a6478ffffffffff, 0x43047365afffffff, 0x1905a6847fffffff, 0xa65197173794ffff,
0x612651478fffffff, 0x125526304347ffff, 0x847905065026ffff, 0x739794329596269f,
0x3b2784a65fffffff, 0x5a647242027bffff, 0x01947823b5a6ffff, 0x9219b294b7b45a6f,
0x8473b53515b6ffff, 0x51b5b610b7b404bf, 0x059065036b63847f, 0x65969b4797b9ffff,
0xa4964affffffffff, 0x4a649a083fffffff, 0xa01a60640fffffff, 0x83181686461affff,
0x149124264fffffff, 0x308129249264ffff, 0x024426ffffffffff, 0x832824426fffffff,
0xa49a64b23fffffff, 0x08228b49a4a6ffff, 0x3b201606461affff, 0x64161a48121b8b1f,
0x964936913b63ffff, 0x8b1810b61914641f, 0x3b6360064fffffff, 0x648b68ffffffffff,
0x7a678a89afffffff, 0x0730a709a67affff, 0xa671a7178180ffff, 0xa67a71173fffffff,
0x126168189867ffff, 0x269291679093739f, 0x780706602fffffff, 0x732672ffffffffff,
0x23ba68a89867ffff, 0x20727b09767a9a7f, 0x1801781a767a23bf, 0xb21b17a61671ffff,
0x896867916b63136f, 0x091b67ffffffffff, 0x7807063b0b60ffff, 0x7b6fffffffffffff,
0x76bfffffffffffff, 0x308b76ffffffffff, 0x019b76ffffffffff, 0x819831b76fffffff,
0xa126b7ffffffffff, 0x12a3086b7fffffff, 0x2902a96b7fffffff, 0x6b72a3a83a98ffff,
0x723627ffffffffff, 0x708760620fffffff, 0x276237019fffffff, 0x162186198876ffff,
0xa76a17137fffffff, 0xa7617a187108ffff, 0x03707a0a96a7ffff, 0x76a7a88a9fffffff,
0x684b86ffffffffff, 0x36b306046fffffff, 0x86b846901fffffff, 0x946963931b36ffff,
0x6846b82a1fffffff, 0x12a30b06b046ffff, 0x4b846b0292a9ffff, 0xa93a32943b36463f,
0x823842462fffffff, 0x042462ffffffffff, 0x190234246438ffff, 0x194142246fffffff,
0x8138618466a1ffff, 0xa10a06604fffffff, 0x4634386a3039a93f, 0xa946a4ffffffffff,
0x49576bffffffffff, 0x083495b76fffffff, 0x50154076bfffffff, 0xb76834354315ffff,
0x954a1276bfffffff, 0x6b712a083495ffff, 0x76b54a42a402ffff, 0x348354325a52b76f,
0x723762549fffffff, 0x954086062687ffff, 0x362376150540ffff, 0x628687218485158f,
0x954a16176137ffff, 0x16a176107870954f, 0x40a4a503a6a737af, 0x76a7a854a48affff,
0x6956b9b89fffffff, 0x36b063056095ffff, 0x0b805b01556bffff, 0x6b3635531fffffff,
0x12a95b9b8b56ffff, 0x0b306b09656912af, 0xb85b56805a52025f, 0x6b36352a3a53ffff,
0x589528562382ffff, 0x956960062fffffff, 0x158180568382628f, 0x156216ffffffffff,
0x13616a386569896f, 0xa10a06950560ffff, 0x03856affffffffff, 0xa56fffffffffffff,
0xb5a75bffffffffff, 0xb5ab75830fffffff, 0x5b75ab190fffffff, 0xa75ab7981831ffff,
0xb12b71751fffffff, 0x08312717572bffff, 0x9759279022b7ffff, 0x75272b592328982f,
0x25a235375fffffff, 0x820852875a25ffff, 0x9015a35373a2ffff, 0x982921872a25752f,
0x135375ffffffffff, 0x087071175fffffff, 0x903935537fffffff, 0x987597ffffffffff,
0x5845a8ab8fffffff, 0x5045b05abb30ffff, 0x01984a8aba45ffff, 0xab4a45b34941314f,
0x2512852b8458ffff, 0x04b0b345b2b151bf, 0x0250592b5458b85f, 0x9452b3ffffffffff,
0x25a352345384ffff, 0x5a2524420fffffff, 0x3a235a385458019f, 0x5a2524192942ffff,
0x845853351fffffff, 0x045105ffffffffff, 0x845853905035ffff, 0x945fffffffffffff,
0x4b749b9abfffffff, 0x0834979b79abffff, 0x1ab1b414074bffff, 0x3143481a474bab4f,
0x4b79b492b912ffff, 0x9749b791b2b1083f, 0xb74b42240fffffff, 0xb74b42834324ffff,
0x29a279237749ffff, 0x9a7974a27870207f, 0x37a3a274a1a040af, 0x1a2874ffffffffff,
0x491417713fffffff, 0x491417081871ffff, 0x403743ffffffffff, 0x487fffffffffffff,
0x9a8ab8ffffffffff, 0x30939bb9afffffff, 0x01a0a88abfffffff, 0x31ab3affffffffff,
0x12b1b99b8fffffff, 0x30939b1292b9ffff, 0x02b80bffffffffff, 0x32bfffffffffffff,
0x23828aa89fffffff, 0x9a2092ffffffffff, 0x23828a0181a8ffff, 0x1a2fffffffffffff,
0x138918ffffffffff, 0x091fffffffffffff, 0x038fffffffffffff, 0xffffffffffffffff
};

// Geometry noise scale
static const float GSCALE = 8;

// Colour relative noise scale
static const float CSCALE = 2;

// Minimum distance from center to exterior
static const int RADIUS = CHUNK_SIZE / 2;

class Chunk
{ public:

   // Initialises members and generates the initial mesh
   Chunk(glm::vec3 position)
   {
      this->position = position;

      // Use the identity matrix
      model = glm::translate(glm::mat4(1.0f), position);

      // Create the OpenSimplex noise context
      int64_t seed = 0;
      ctx = nullptr;
      open_simplex_noise(seed, &ctx);

      // Initialise deformation information
      dug = new GLubyte[size_t(glm::pow(CHUNK_SIZE + 1, 3))];
      for (int i = 0; i < glm::pow(CHUNK_SIZE + 1, 3); i++) dug[i] = 128;

      // Generate the mesh
      generate();

#if 0
      // Print number of tris
      double t = positions.size() / 9;
      int index = 0;
      while ((t /= 1000.0) >= 1000.0) index++;
      std::streamsize s = std::cout.precision();
      std::cout << std::setprecision(3) << t << "KMBT?"[index] << " TRIS\n"
                << std::setprecision(s);
#endif
   }

   // Frees dynamically allocated memory
   ~Chunk()
   {
      free();
      delete[] dug;
   }

   // Returns the model matrix
   glm::mat4 getModel() const
   {
      return model;
   }

   // Renders the chunk to the screen (the shader must already be set up)
   void draw() const
   {
      if (positions.size())
      {
         glBindVertexArray(VAO);
         glDrawArrays(GL_TRIANGLES, 0, positions.size() / 3);
         glBindVertexArray(0);
      }
   }

   // Deforms the mesh
   void dig(glm::vec3 pos, float rad, float amt)
   {
      bool changed = false;
      glm::vec3 v = pos - position;

      for       (int x = glm::floor(v.x - rad); x <= glm::ceil(v.x + rad); x++)
         for    (int y = glm::floor(v.y - rad); y <= glm::ceil(v.y + rad); y++)
            for (int z = glm::floor(v.z - rad); z <= glm::ceil(v.z + rad); z++)
            {
               glm::vec3 w(x, y, z);
               size_t i = dindex(w);
               if (i == SIZE_MAX) continue;

               float length = glm::length(v - w);
               int a = amt * glm::clamp(1.0f - length / rad, 0.0f, 1.0f);
               if (a == 0) continue;

               GLubyte old = dug[i];
               double oldSample = sample(w);

               dug[i] += glm::clamp(a, -old, 255 - old);
               // First check is redundant but far more efficient
               if (dug[i] != old && sample(w) != oldSample) changed = true;
            }

      if (changed)
      {
         free();
         generate();
      }
   }

private:

   // The position of the chunk
   glm::vec3 position;

   // GPU object references
   GLuint VAO, posVBO, colVBO;

   // Model matrix
   glm::mat4 model;

   // Vertex positions
   std::vector<GLfloat> positions;

   // Vertex colours
   std::vector<GLfloat> colours;

   // OpenSimplex noise context
   osn_context* ctx;

   // Deforation information
   GLubyte* dug;

   // Frees mesh data
   void free()
   {
      // Free VRAM
      glDeleteVertexArrays(1, &VAO);
      glDeleteBuffers(1, &posVBO);
      glDeleteBuffers(1, &colVBO);

      // Free RAM
      positions.clear();
      colours.clear();
   }

   // Generates chunk data
   void generate()
   {
      // Generate mesh
      for       (int x = -RADIUS; x < RADIUS; x++)
         for    (int y = -RADIUS; y < RADIUS; y++)
            for (int z = -RADIUS; z < RADIUS; z++)
               polygonise(glm::vec3(x, y, z), 0);

      glGenVertexArrays(1, &VAO);

      // Vertex positions
      glGenBuffers(1, &posVBO);
      glBindVertexArray(VAO);
      glBindBuffer(GL_ARRAY_BUFFER, posVBO);
      glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(positions[0]),
                                    positions.data(), GL_STATIC_DRAW);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(positions[0]),
                                                                   (GLvoid*)0);
      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);

      // Vertex colours
      glGenBuffers(1, &colVBO);
      glBindVertexArray(VAO);
      glBindBuffer(GL_ARRAY_BUFFER, colVBO);
      glBufferData(GL_ARRAY_BUFFER, colours.size() * sizeof(colours[0]),
                                    colours.data(), GL_STATIC_DRAW);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(colours[0]),
                                                                 (GLvoid*)0);
      glEnableVertexAttribArray(1);
      glBindBuffer(GL_ARRAY_BUFFER, 0);

      glBindVertexArray(0);
   }

   // Generates the mesh for position pos
   void polygonise(glm::vec3 pos, double lvl)
   {
      // Populate the grid array
      glm::vec3 grid[8];
      for (int g = 0; g < 8; g++)
      {
         // TODO fix this abomination (g % 2, g / 2 % 2, g / 4)
         grid[g] = pos + glm::vec3((g + 1) / 2 % 2, g / 4, g / 2 % 2);
      }

      // Determine the configuration index
      int config = 0;
      for (int g = 0; g < 8; g++) config |= (sample(grid[g]) < lvl) << g;

      // Create the triangles
      for (int v, i = 0; (v = tris[config] >> (15 - i) * 4 & 0xf) != 0xf; )
      {
         // Vertex position data
         for (int d = 0; d < 3; d++)
         {
            GLubyte other = 0123056744567 >> (11 - v) * 3 & 7;
            positions.push_back(verterp2(lvl, grid[v % 8], grid[other])[d]);
         }

         // Vertex colour data
         if (++i % 3 == 0)
         {
            // Get the average position of the triangle vertices
            glm::vec3 triPos = -position;
            for (int c = 0; c < 9; c++)
            {
               triPos[c % 3] += positions[positions.size() - 9 + c] / 3.0f;
            }

            // Use the triangle position to sample arbitrary gradient noise
            for (int c = 0; c < 9; c++)
            {
               glm::vec3 offset(0);
               offset[c % 3] = 9000;
               colours.push_back(glm::abs(noise(triPos / CSCALE + offset)));
            }
         }
      }
   }

   // TODO comment, rename
   void polygonise2(glm::vec3 pos, double lvl)
   {
      // Triangles for tetrahedral marching TODO fix face direction?
      const GLuint tetris[16] = {
         0xffffffff, 0x123fffff, 0x176fffff, 0x372762ff,
         0x26bfffff, 0x1b31b6ff, 0x17b1b2ff, 0x37bfffff,
         0x3b7fffff, 0x1b712bff, 0x13b16bff, 0x2b6fffff,
         0x327726ff, 0x167fffff, 0x132fffff, 0xffffffff
      };

      // TODO
      const int vs[6][4] = {{ 0, 2, 3, 7 }, { 0, 2, 6, 7 }, { 0, 4, 6, 7 },
                            { 0, 6, 1, 2 }, { 0, 6, 1, 4 }, { 5, 6, 1, 4 }};

      for (int t = 0; t < 6; t++)
      {
         // Populate the grid array
         glm::vec3 grid[8];
         for (int g = 0; g < 8; g++)
         {
            // TODO fix this abomination (g % 2, g / 2 % 2, g / 4)
            grid[g] = pos + glm::vec3((g + 1) / 2 % 2, g / 4, g / 2 % 2);
         }

         // Determine the configuration index
         int config = 0;
         for (int g = 0; g < 4; g++) config |= (sample(grid[vs[t][g]]) < lvl)
                                                                       << g;

         for (int v, i = 0; (v = tetris[config] >> (7 - i) * 4 & 0xf) != 0xf; )
         {
            // Vertex position data
            for (int d = 0; d < 3; d++)
            {
               positions.push_back(verterp2(lvl, grid[vs[t][v >> 2]],
                                                 grid[vs[t][v & 3]])[d]);
            }

            // Vertex colour data
            if (++i % 3 == 0)
            {
               glm::vec3 triPos = -position;
               for (int c = 0; c < 9; c++)
               {
                  triPos[c % 3] += positions[positions.size() - 9 + c] / 3.0f;
               }

               for (int c = 0; c < 9; c++)
               {
                  glm::vec3 offset(0);
                  offset[c % 3] = 9000;
                  colours.push_back(glm::abs(noise(triPos / CSCALE + offset)));
               }
            }
         }
      }
   }

   // Returns the midpoint between vectors a and b, lvl is unused
   glm::vec3 verterp0(double lvl, glm::vec3 a, glm::vec3 b) const
   {
      return (a + b) / 2.0f;
   }

   // Interpolates along the edge according to lvl and the vertex samples
   glm::vec3 verterp1(double lvl, glm::vec3 a, glm::vec3 b) const
   {
      if (glm::abs(lvl       - sample(a)) < 1e-5) return a;
      if (glm::abs(lvl       - sample(b)) < 1e-5) return b;
      if (glm::abs(sample(a) - sample(b)) < 1e-5) return a;

      return a + (b - a) * float((lvl - sample(a)) / (sample(b) - sample(a)));
   }

   // Supposedly fills small isosurface cracks during interpolation
   glm::vec3 verterp2(double lvl, glm::vec3 a, glm::vec3 b) const
   {
      if (less(b, a)) std::swap(b, a);
      float s = sample(b) - sample(a);

      glm::vec3 r = a;
      if (glm::abs(s) > 1e-5) r += (b - a) * float(lvl - sample(a)) / s;
      return r;
   }

   // Returns true if vector a is 'less' than vector b
   bool less(glm::vec3 a, glm::vec3 b) const
   {
      for (int d = 0; d < 3; d++) if (a[d] != b[d]) return a[d] < b[d];
      return false;
   }

   // Returns the value of the noise at position pos
   double noise(glm::vec3 pos) const
   {
      glm::vec3 v = pos + position;
      return open_simplex_noise3(ctx, v.x / GSCALE, v.y / GSCALE, v.z / GSCALE);
   }

   // Returns the value of the geometry information at position vector v
   double sample(glm::vec3 v) const
   {
      return glm::clamp(noise(v) + deformity(v), -1.0, 1.0);
   }

   // Returns the value of manual deformation at position vector v
   double deformity(glm::vec3 v) const
   {
      return dug[dindex(v)] / 128.0 - 1.0;
   }

   // Returns the index of dug corresponding to position v
   static size_t dindex(glm::vec3 v)
   {
      for (int d = 0; d < 3; d++) if (glm::abs(v[d]) > RADIUS) return SIZE_MAX;
      glm::vec3 w = v + glm::vec3(RADIUS);
      return w.x + (CHUNK_SIZE + 1) * (w.y + (CHUNK_SIZE + 1) * w.z);
   }
};

#endif
