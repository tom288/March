#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "globals.hpp"
#include "shader.hpp"

// Creates and returns a window
GLFWwindow* makeWindow()
{
   GLFWwindow* window = nullptr;
   glfwInit();

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

   if (AA_X != 1)
   {
      // Enable antialiasing
      glfwWindowHint(GLFW_SAMPLES, AA_X);
      glEnable(GL_MULTISAMPLE);
   }

#ifdef __APPLE__
   // Fixes compilation on OS X
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

   window = glfwCreateWindow(WIN_W, WIN_H, ":D", nullptr, nullptr);
   glfwMakeContextCurrent(window);
   glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

   if (!VSYNC)
   {
      // Disable vertical sync
      glfwSwapInterval(0);
   }

   if (RAW_INPUT && glfwRawMouseMotionSupported())
   {
      // Disable mouse accel
      glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
      std::cout << "Raw input is enabled!" << std::endl;
   }
   // TODO read input
   // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   // glfwSetKeyCallback(window, keyCB);
   // glfwSetMouseButtonCallback(window, mouseButtonCB);
   // glfwSetCursorPosCallback(window, mouseCursorCB);
   // glfwSetScrollCallback(window, scrollCB);

   glewExperimental = GL_TRUE;
   glewInit();

   int width, height;
   glfwGetFramebufferSize(window, &width, &height);
   glViewport(0, 0, width, height);

   return window;
}

// Launches the program
int main()
{
   GLFWwindow* window = makeWindow();
   if (!window)
   {
      glfwTerminate();
      return 1;
   }

   Shader shader("persp");
   glClearColor(0.2f, 0.4f, 1.0f, 1.0f);

   size_t frames = 0;
   double elapsed, newTime, time = glfwGetTime();

   while (!glfwWindowShouldClose(window))
   {
      glfwPollEvents();
      glClear(GL_COLOR_BUFFER_BIT);

      shader.use();
      glfwSwapBuffers(window);

      elapsed = (newTime = glfwGetTime()) - time;
      frames++;

      // Runs every 1 second on average
      if (elapsed > 1 - elapsed / frames / 2)
      {
         std::cout << "T = "   << 1000.0 * elapsed / frames << " ms\t"
                   << "FPS = " << frames / elapsed << std::endl;
         time = newTime;
         frames = 0;
      }
   }

   glfwTerminate();
   return 0;
}
