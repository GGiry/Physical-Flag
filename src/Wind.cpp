#include <Wind.h>

#include <cmath>
#include <cstdlib>
#include <ctime>

#include <iostream>

#include <GL/gl.h>

#include <G3Xall.h>

extern G3Xcolor yellow;

extern double ambi;
extern double diff;
extern double spec;
extern double shin;

Wind::Wind(G3Xvector v, std::vector<PMat*>::iterator begin, std::vector<PMat*>::iterator end):
   GlobalAction(v, begin, end) {
  /* initialize random seed: */
  srand(0); // time(NULL)
}

void Wind::algo() {
  for (std::vector<PMat*>::const_iterator it = _begin; it != _end; ++it) {
    (*it)->updateFrc(_v);
  }
  /*
  
  float x = (rand() % 100) / 1000. - 0.05;
  float y = (rand() % 100) / 1000. - 0.05;
  
  _v[0] += x;
  _v[1] += y;

  if (_v[0] > 3) {
    _v[0] = 3;
  }
  if (_v[1] > 3) {
    _v[1] = 3;
  }
  */
}

void Wind::draw() {
  G3Xpoint p1 = NUL;
  G3Xpoint p2 = _v * 10;
  
  p2[2] = 24;
  p1[2] = 24;

  glDisable(GL_LIGHTING);
  glBegin(GL_LINES);
    glColor3f(.0, .5, 1.0);
    glVertex3f(p1[0], p1[1], p1[2]);
    glVertex3f(p2[0], p2[1], p2[2]);
  glEnd();
  glEnable(GL_LIGHTING);
}
