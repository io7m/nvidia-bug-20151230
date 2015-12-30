#define GL_GLEXT_PROTOTYPES 1
#include <assert.h>
#include <GL/glcorearb.h>
#include "example.h"

static GLuint vbo;
static GLuint vao;

static void
check_error()
{
  int e = glGetError();
  assert (e == GL_NO_ERROR);
}

void
example_init()
{
  glGenVertexArrays(1, &vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 6 * 16, (void *) 0L, GL_STATIC_DRAW);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  check_error();
}

void
example_render()
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  glBindVertexArray(vao);
  glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 37361);
  glBindVertexArray(0);

  check_error();
}

