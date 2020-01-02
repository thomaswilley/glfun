/* 
 * cube.c: a sandbox for playing w/opengl.
 * cube.c modified 201912 by @thomaswilley and integrated into larger app.
 * original cube.c itself Copyright (c) Mark J. Kilgard, 1997.
 */
#ifdef __APPLE__

/* Defined before OpenGL and GLUT includes to avoid deprecation messages from
 * OS X
 */
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <math.h>
#include "session.h"
#include "keyboard.h"
#include "utils.h"

GLfloat light_diffuse[] = {0.2, 0.1, 0.9, 1.0};  /* Red diffuse light. */
//GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};  /* Infinite light location. */
GLfloat light_position[] = {0.0, 1.0, -1.0, 0.1};
GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
  {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
  {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */

float resize_f = 1.0f;
Session_t session_data;
int fullscreen = 0;
float scale = 0.25f;

void drawBox(void)
{
  int i;

  for (i = 0; i < 6; i++) {
    glBegin(GL_QUADS);
    glNormal3fv(&n[i][0]);
    glVertex3fv(&v[faces[i][0]][0]);
    glVertex3fv(&v[faces[i][1]][0]);
    glVertex3fv(&v[faces[i][2]][0]);
    glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
  }
}

double myfn(double in)
{
  return 1/exp(sin(in));
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();

  gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
      0.0, 0.0, 0.0,      /* center is at (0,0,0) */
      0.0, 1.0, 0.0);      /* up is in positive Y direction */

  double (*fns[3])(double) = { sin, cos, myfn };

  int num_cubes = 3;
  int num_fns = (int)sizeof(fns)/sizeof(fns[0]);
  for(int i=0; i<num_fns; i++)
  {
    for(int j=0; j<num_cubes; j++)
    {
      glPushMatrix();
      glTranslatef(j - num_cubes/2, i - num_fns/2, 0.0);
      glRotatef((float)5.0*(*fns[i])(0.1*session_data.x_speed), 1.0, 0.0, 0.0);
      glRotatef((float)5.0*(*fns[i])(0.1*session_data.y_speed), 0.0, 1.0, 0.0);
      glRotatef((float)5.0*(*fns[i])(0.1*session_data.z_speed), 0.0, 0.0, 1.0);
      glTranslatef((float)0.07*sin(0.1*session_data.x_speed),
          (float)0.07*sin(0.1*session_data.x_speed) - \
          (float)0.07*cos(0.1*session_data.x_speed),
          (float)0.07*cos(0.1*session_data.x_speed));
      if(!(i==num_fns-1 && j==1))
      {
        drawBox();
      }
      glPopMatrix();
    }
  }

  glFlush();
  glutSwapBuffers();
}

void idle() {
  session_data.x_speed += session_data.acceleration;
  session_data.y_speed += session_data.acceleration;
  session_data.x_speed += session_data.acceleration;
  glutPostRedisplay();
}

void init(void)
{
  /* Setup cube vertex data. */
  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1 * scale;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1 * scale;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1 * scale;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1 * scale;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1 * scale;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1 * scale;

  /* Enable a single OpenGL light. */
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);

  /* Adjust cube position to be asthetic angle. */
  glTranslatef(0.0, 0.0, -1.0);

  /* setup session/data object */
  session_data.acceleration = 0.1f;
  session_data.x_speed = 0.3f;
  session_data.y_speed = 0.3f;
  session_data.z_speed = 0.3f;
  session_data.base_speed = 1.0f;
}

void reshape(int w, int h)
{
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();

  glViewport(0, 0, w, h);

  if (!fullscreen) { // todo: might need to exit the whole fn if fullscreen
    glutReshapeWindow(w, h);
  }

  gluPerspective(/* field of view in degree */ 40.0,
      /* aspect ratio */ resize_f * w / h,
      /* Z near */ resize_f,
      /* Z far */ 100 * resize_f);

  glMatrixMode(GL_MODELVIEW);
}

void on_keyboard(unsigned char key, int x, int y)
{
  keyboard(key, x, y, &session_data); // can mutate session_data

  glutPostRedisplay();
}

void on_fullscreen(int key, int x, int y)
{
  if (key == GLUT_KEY_F1)
  {
    fullscreen = !fullscreen;

    if (fullscreen)
      glutFullScreen();
    else
    {
      reshape(500, 500);
      glutPositionWindow(50, 50);
    }
  }
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("gl c sandbox 20191231");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(on_keyboard);
  glutSpecialFunc(on_fullscreen);
  glutIdleFunc(idle);
  init();
  reshape(500, 500);
  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}
