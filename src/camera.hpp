#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{ public:

   // TODO comment
   Camera()
   {
      // TODO Initialise members
      pitch = yaw = 0.0;
      fov = 106.26;
      sens = 0.1;
      calcVectors();
      calcProjection();
   }

   // TODO comment
   void moveMouse(double dx, double dy)
   {
      double PITCH_MAX = 89.0;

      yaw   += dx * sens;
      pitch += dy * sens;

      while (yaw < -180) yaw += 360;
      while (yaw >= 180) yaw -= 360;

      pitch = glm::clamp(pitch, -PITCH_MAX, PITCH_MAX);

      calcVectors();
   }

   // TODO comment
   void setFOV(double fov)
   {
      double FOV_MIN = 10, FOV_MAX = 170;

      fov = glm::clamp(fov, FOV_MIN, FOV_MAX);
      calcProjection();
   }

   // TODO getter(s) for P, V or P * V

   // TODO step

private:
   // TODO
   glm::dvec3 position;
   glm::dvec3 velocity;

   // Aim
   double yaw;
   double pitch;
   double sens;
   double fov;

   // Populated by calcVectors
   glm::dvec3 look;
   glm::dvec3 up;
   glm::dvec3 right;
   glm::dvec3 front;

   // TODO comment
   void calcVectors()
   {
      double y = glm::radians(yaw), p = glm::radians(pitch), c = cos(p);
      look = glm::normalize(glm::dvec3(cos(y) * c, sin(p), sin(y) * c));
      up = glm::dvec3(0.0f, 1.0f, 0.0f);
      right = glm::normalize(glm::cross(up, look));
      front = glm::normalize(glm::cross(up, right));
   }

   // Populated by calcProjection
   glm::dmat4 projection;

   // TODO comment
   void calcProjection()
   {
      const double NEAR = 0.1f, FAR = 1000.0f;
      
      double rad = glm::radians(fov);
      projection = glm::perspective(rad, double(WIN_W) / WIN_H, NEAR, FAR);
   }

};

#endif
