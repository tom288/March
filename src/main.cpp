#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "globals.hpp"
#include "shader.hpp"
#include "camera.hpp"

// The current camera
Camera* cam = nullptr;

// Keyboard input callback
void keyCallback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
   if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(win, GL_TRUE);
	}
}

// Mouse cursor movement callback
double xold, yold;
void cursorPosCallback(GLFWwindow* win, double xpos, double ypos)
{
   if (cam) cam->moveMouse(xpos - xold, yold - xpos);
   xold = xpos;
   yold = ypos;
}

// Mouse button input callback
void mouseButtonCallback(GLFWwindow* win, int button, int action, int mods)
{
   // TODO
}

// Mouse scroll wheel movement callback
void scrollCallback(GLFWwindow* win, double xoffset, double yoffset)
{
   // TODO
}


// Creates and returns a window
GLFWwindow* makeWindow()
{
   GLFWwindow* window = nullptr;
   glfwInit();

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

   if (AA_X > 1)
   {
      // Enable antialiasing
      glfwWindowHint(GLFW_SAMPLES, AA_X);
      glEnable(GL_MULTISAMPLE);
   }

   // Ignore hidden triangles
   glEnable(GL_CULL_FACE);
   glEnable(GL_DEPTH_TEST);

#ifdef __APPLE__
   // Fixes compilation on OS X
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

   window = glfwCreateWindow(WIN_W, WIN_H, ":D", nullptr, nullptr);
   glfwMakeContextCurrent(window);
   glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   glfwSetKeyCallback(window, keyCallback);
   glfwSetMouseButtonCallback(window, mouseButtonCallback);
   glfwSetCursorPosCallback(window, cursorPosCallback);
   glfwSetScrollCallback(window, scrollCallback);

   if (!VSYNC)
   {
      // Disable vertical sync
      glfwSwapInterval(0);
   }

   if (RAW_INPUT && glfwRawMouseMotionSupported())
   {
      // Disable mouse acceleration
      glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
   }

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

   cam = new Camera();
   Shader shader("persp");

   glClearColor(0.2f, 0.4f, 1.0f, 1.0f);
   glfwGetCursorPos(window, &xold, &yold);

   size_t frames = 0;
   double elapsed, newTime, time = glfwGetTime();

   while (!glfwWindowShouldClose(window))
   {
      elapsed = (newTime = glfwGetTime()) - time;

      // Runs every 1 second on average
      if (elapsed > 1 - elapsed / ++frames / 2)
      {
         std::cout <<   "T = " << 1000.0 * elapsed / frames << " ms\t"
                   << "FPS = " << frames / elapsed << std::endl;
         time = newTime;
         frames = 0;
      }

      glfwPollEvents();
      
      // TODO Calculate input vector
      cam->step(glm::dvec3(0.0, 0.0, 0.0), elapsed);

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      shader.use();
      // TODO draw

      glfwSwapBuffers(window);
   }

   glfwTerminate();
   delete cam;
   return 0;
}
