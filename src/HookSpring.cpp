#include <HookSpring.h>

#include <GL/gl.h>

#include <iostream>
#include <cmath>
#include <G3Xtypes.h>
#include <G3Xmacros.h>

#include <g3x_tools.h>        /* utilitaires divers                       */

extern G3Xcolor yellow;

extern double ambi;
extern double diff;
extern double spec;
extern double shin;

double epsilon = 0.0000001;

HookSpring::HookSpring(const double k, PMat* m1, PMat* m2): 
    Link(m1, m2), _k(k) {
  if (_m1 != NULL && _m2 != NULL) {
    _l = G3Xcoord::distance(m1->getPos(), m2->getPos());
  }
}

void HookSpring::algo() {
  double d = G3Xcoord::distance(_m1->getPos(), _m2->getPos());

  if (abs(d) < epsilon) {
    // traitement d'urgence
    d = 1;
  }
  
  double e = (1 - _l / d);

  G3Xvector frc = (_m2->getPos() - _m1->getPos()) * (_k) * e;
  
  _m1->updateFrc(frc);
  _m2->updateFrc(-frc);
}

void HookSpring::draw() {
  G3Xpoint p1 = Link::_m1->getPos();
  G3Xpoint p2 = Link::_m2->getPos();

  glDisable(GL_LIGHTING);
  glBegin(GL_LINES);
    //g3x_Material(yellow,ambi,diff,spec,shin,1.);
    glColor3f(.0, .5, 0.0);
    glVertex3f(p1[0], p1[1], p1[2]);
    glVertex3f(p2[0], p2[1], p2[2]);
  glEnd();
  glEnable(GL_LIGHTING);
}
