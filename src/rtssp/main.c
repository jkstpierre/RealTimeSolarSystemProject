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

#include "rtssp/rtssp.h"
#include "rtssp/graphics.h"


// VARIABLES // 

bool is_running = true;   // Program is running by default


// FUNCTIONS //

/**
 * @brief The main function is where program entry begins.
 * 
 * @param argc  The number of arguments sent
 * @param args  The arguments themselves
 * @return int  Returns 0 on success
 */
int main(int argc, char **args) {
  // Initialize glfw
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize glfw! Aborting...\n");
    exit(EXIT_FAILURE); // Terminate with error
  }

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
    DEFAULT_WINDOW_WIDTH_PIXELS,          // Width in pixels
    DEFAULT_WINDOW_HEIGHT_PIXELS,         // Height in pixels
    "Real Time Solar System Project",     // Name of the window
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

  // Setup function callbacks
  glfwSetErrorCallback(processError);        // Error callback
  glfwSetKeyCallback(window, processInput);  // Input callback
  

  // Application loop
  while (!glfwWindowShouldClose(window) && is_running) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Set the clear color to black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color buffer and depth buffer



    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // CLEAN UP //

  glfwTerminate();  // Shutdown glfw

  return 0;
}

void processError(int error_code, const char *message) {
  fprintf(stdin, "Error:\nCode: %d\nMessage: %s\n", error_code, message);
  exit(EXIT_FAILURE);
}

void processInput(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    // User has pressed the escape key and wishes to exit program
    is_running = false;
  }
}