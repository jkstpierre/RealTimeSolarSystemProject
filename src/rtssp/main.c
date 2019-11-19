/**
 * @file main.c
 * @author Joseph St. Pierre
 * @brief RealTimeSolarSystemProject's program entry point
 * @version 0.1
 * @date 2019-11-19
 * 
 * @copyright Copyright (c) 2019
 * 
 */

// INCLUDES //
#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "rtssp/rtssp.h"

int main(int argc, char **args) {
  // Attempt to initialize glfw
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize glfw! Aborting...\n");
    exit(EXIT_FAILURE); // Terminate with error
  }

  // Set hints for window creation

  // Target OpenGL 3.3 and request a core profile
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, DEFAULT_OPENGL_MAJOR_VERSION);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, DEFAULT_OPENGL_MINOR_VERSION);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Enable forward compatibility on MacOS
  #ifndef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif

  // Create a glfw window
  GLFWwindow *window = glfwCreateWindow(
    DEFAULT_WINDOW_WIDTH_PIXELS, 
    DEFAULT_WINDOW_HEIGHT_PIXELS,
    "Real Time Solar System Project",
    NULL,
    NULL
  );
  if (!window) {
    fprintf(stderr, "Failed to create a window instance!\n");
    glfwTerminate();  // Terminate glfw
    exit(EXIT_FAILURE); // Indicate failure
  }
  glfwMakeContextCurrent(window);   // Make the window context current

  // Load GLAD and set the process address
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "Failed to initialize GLAD!\n");
    glfwTerminate();  // Terminate glfw
    exit(EXIT_FAILURE); // Indicate failure
  }

  // Program loop
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // (TODO: Program logic goes here)

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();  // Shutdown glfw

  return 0;
}