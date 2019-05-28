#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>

// Used for lookAt and perspective
#include <glm/gtc/matrix_transform.hpp>

class Camera
{ public:

   // TODO comment
   Camera()
   {
      position = velocity = glm::dvec3(0.0, 0.0, 0.0);
      sens = 0.1;

      setAngle(0.0, 0.0);
      setFOV(106.26);
   }

   // Uses mouse input to reorient the camera
   void moveMouse(double dx, double dy)
   {
      setAngle(yaw + dx * sens, pitch + dy * sens);
   }

   // Changes the camera angle and recalculates the view matrix + vectors
   void setAngle(double yaw, double pitch)
   {
      this->yaw = glm::mod(yaw + 180.0, 360.0) - 180.0;
      this->pitch = glm::clamp(pitch, -PITCH_MAX, PITCH_MAX);

      calcVectors();
   }

   // Changes the FOV and recalculates the projection matrix
   void setFOV(double fov)
   {
      this->fov = glm::clamp(fov, FOV_MIN, FOV_MAX);

      calcProjection();
   }

   // Returns the product of the projection and view matrices TODO rename?
   glm::mat4 getPxV()
   {
      return projection * view;
   }

   // TODO
   void step()
   {
      // TODO
   }

private:

   const glm::dvec3 UP = glm::dvec3(0.0, 1.0, 0.0);
   const double PITCH_MAX = 89.0;
   const double FOV_MIN = 10;
   const double FOV_MAX = 170;
   const double NEAR = 0.1;
   const double FAR = 1000.0;

   glm::dvec3 position;
   glm::dvec3 velocity;

   // Aim
   double yaw;
   double pitch;
   double sens;
   double fov;

   // Populated by calcVectors
   glm::dvec3 look;
   glm::dvec3 right;
   glm::dvec3 front;

   // Populated by calcView
   glm::mat4 view;

   // Populated by calcProjection
   glm::mat4 projection;

   // Calculates the look, right and front vectors
   void calcVectors()
   {
      double y = glm::radians(yaw), p = glm::radians(pitch), c = cos(p);
      look  = glm::normalize(glm::dvec3(cos(y) * c, sin(p), sin(y) * c));
      right = glm::normalize(glm::cross(UP, look));
      front = glm::normalize(glm::cross(UP, right));

      calcView();
   }

   // Calculates the new view matrix
   void calcView()
   {
      view = glm::lookAt(position, position + look, UP);
   }

   // Calculates the new projection matrix
   void calcProjection()
   {
      double rad = glm::radians(fov);
      projection = glm::perspective(rad, double(WIN_W) / WIN_H, NEAR, FAR);
   }
};

#endif
