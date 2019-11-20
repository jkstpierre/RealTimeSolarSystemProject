/**
 * @file rtssp.h
 * @author Joseph St. Pierre
 * @brief This file contains the major global definitions and functions used by main.c
 * @version 0.1
 * @date 2019-11-19
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _RTSSP_H_
#define _RTSSP_H_


// INCLUDES //

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


// DEFINES //

// Target OpenGL v3.3
#define DEFAULT_OPENGL_MAJOR_VERSION  3
#define DEFAULT_OPENGL_MINOR_VERSION  3

// Window specifications
#define DEFAULT_WINDOW_WIDTH_PIXELS   800
#define DEFAULT_WINDOW_HEIGHT_PIXELS  600

// Number of physics steps per second (independent of framerate)
#define DEFAULT_PHYS_TICKS_PER_SECOND 50


// VARIABLES //

// Tracks whether the program loop is running or not, default value is true
extern bool is_running;


// FUNCTIONS //

/**
 * @brief Process errors encountered by GLFW.
 * 
 * @param error_code  The GLFW error code
 * @param message     The error string
 */
extern void processError(int error_code, const char *message);

/**
 * @brief Process input from the window. This function is registered with GLFW and called from it.
 * 
 * @param window    The instance of the window calling the function
 * @param key       The key the event refers to
 * @param scancode  The OS-specific scancode of the key
 * @param action    The type of event
 * @param mods      The modifiers to the event
 */
extern void processInput(GLFWwindow *window, int key, int scancode, int action, int mods);



#endif