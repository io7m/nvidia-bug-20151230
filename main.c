#include <GLFW/glfw3.h>
#include <stdio.h>
#include "example.h"

int
main(void)
{
  GLFWwindow* window;

  if (!glfwInit()) {
    fprintf(stderr, "Unable to initialize\n");
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(640, 480, "Main", NULL, NULL);
  if (!window) {
    fprintf(stderr, "Unable to create window\n");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  printf("GL_VERSION: %s\n", glGetString(GL_VERSION));

  example_init();

  while (!glfwWindowShouldClose(window)) {
    example_render();
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
