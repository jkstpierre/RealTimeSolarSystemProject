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
#include "rtssp/scene.h"
#include "rtssp/graphics.h"


// VARIABLES // 

bool is_running = true;   // Program is running by default


// FUNCTIONS //

// LOCAL FUNCTIONS //

/**
 * @brief Initialize and prepare OpenGL for rendering. Return true on success, false on failure
 * 
 * @return true 
 * @return false 
 */
bool initOpenGL() {
  // Set the initial view port
  glViewport(0, 0, DEFAULT_WINDOW_WIDTH_PIXELS, DEFAULT_WINDOW_HEIGHT_PIXELS);
  if (glGetError() != GL_NO_ERROR) {
    fprintf(stderr, "Failed to set the viewport!\n");
    return false;
  }

  // Enable depth testing
  glEnable(GL_DEPTH_TEST);
  if (glGetError() != GL_NO_ERROR) {
    fprintf(stderr, "Failed to enable depth testing!\n");
    return false;
  }

  glEnable(GL_MULTISAMPLE); // Enable anti-aliasing
  if (glGetError() != GL_NO_ERROR) {
    fprintf(stderr, "Failed to enable multisample buffers!\n");
    return false;
  }

  return true;
}

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

  // Disable vertical sync
  glfwSwapInterval(0);

  // Setup function callbacks
  glfwSetErrorCallback(processError);        // Error callback
  glfwSetKeyCallback(window, processInput);  // Input callback
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);  // Framebuffer size callback

  // Enable OpenGL (TODO: )
  if (!initOpenGL()) {
    exit(EXIT_FAILURE); // Terminate program if OpenGL failed to load
  }
  
  // Initialize the scene
  initScene();

  /**
   * @brief Variables for frame timing
   * 
   */
  float delta_time = 1.0f / DEFAULT_PHYS_TICKS_PER_SECOND;  // The delta time between phys steps
  float prev_time = glfwGetTime();    // Get the time in seconds
  float accumulator = 0.0f; // Accumulator for keeping phys steps and draw calls in sync

  // Application loop
  while (!glfwWindowShouldClose(window) && is_running) {
    // Compute the current time
    float curr_time = glfwGetTime();  // Get time in seconds
    float frame_time = (curr_time - prev_time); // Compute frame time
    if (frame_time > 0.25)
      frame_time = 0.25;  // Cap the frame time

    prev_time = curr_time;  // Update the previous time
    accumulator += frame_time;
    while (accumulator >= delta_time) {
      updateScene(delta_time);  // Update the scene with the calculated delta time
      accumulator -= delta_time;
    }
    
    // Compute alpha and draw scene using interpolation
    float alpha = accumulator / delta_time;
    drawScene(alpha);

    glfwSwapBuffers(window);  // Update the window with the default framebuffer's contents
    glfwPollEvents();   // Poll for user events
  }

  // CLEAN UP //

  freeScene();      // Free the scene assets

  glfwTerminate();  // Shutdown glfw

  return 0;
}

// CALLBACK FUNCTIONS //

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

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);  // Update the viewport with the new screen dimensions
}