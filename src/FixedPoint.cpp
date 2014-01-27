#include <FixedPoint.h>
#include <G3Xmacros.h>

#include <GL/gl.h>
#include <GL/glut.h>

#include <g3x_tools.h>        /* g3x_Material                       */

extern double h;

extern G3Xcolor red;

extern double ambi;
extern double diff;
extern double spec;
extern double shin;

FixedPoint::FixedPoint(G3Xpoint pos0): 
    PMat(0., pos0, NUL) {
  // Empty
}

void FixedPoint::algo(void) {
  PMat::_frc = NUL;
}

void FixedPoint::draw(void) const {
  glPushMatrix();
    glTranslatef(_pos[0], _pos[1], _pos[2]);
    g3x_Material(red, ambi, diff, spec, shin, 1.);
    glutSolidCube(1.);
  glPopMatrix();
}
