#define GL_GLEXT_PROTOTYPES 1
#include <assert.h>
#include <GL/glcorearb.h>
#include "example.h"
#include <stdio.h>
#include <string.h>

static GLuint vbo;
static GLuint vao;

static void
check_error()
{
  int e = glGetError();
  if (e != GL_NO_ERROR) {
    if (e == GL_INVALID_OPERATION) {
      printf("GL_INVALID_OPERATION\n");
    }
  }
  assert (e == GL_NO_ERROR);
}

static const char *vs_source = "#version 330\n in vec4 position;\n void main() {\n gl_Position = vec4(position.xyz*0.0001, 1\n); }";
static const char *fs_source = "#version 330\n out vec4 o_color;void main() {o_color = vec4(1,0,1,1);}";

void
example_init()
{
  glGenVertexArrays(1, &vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 6 * 16, (void *) 0L, GL_STATIC_DRAW);
  glBindVertexArray(vao);

  const int vs = glCreateShader(GL_VERTEX_SHADER);
  const int vs_length = strlen(vs_source);
  glShaderSource(vs, 1,  (const char **) &vs_source, &vs_length);
  glCompileShader(vs);

  const int fs = glCreateShader(GL_FRAGMENT_SHADER);
  const int fs_length = strlen(fs_source);
  glShaderSource(fs, 1,  (const char **) &fs_source, &fs_length);
  glCompileShader(fs);

  const int program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);

  glUseProgram(program);

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

  printf("bind vao\n");
  glBindVertexArray(vao);
  check_error();

  printf("call glDrawArraysInstanced\n");
  glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 37365);
  check_error();
  printf("unbind vao\n");
  glBindVertexArray(0);

  printf("passed!\n");
  check_error();
}

