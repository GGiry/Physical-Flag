#include <Particle.h>
#include <G3Xmacros.h>

#include <iostream>

#include <GL/gl.h>
#include <GL/glut.h>

#include <g3x_tools.h>        /* g3x_Material                       */

extern double h;

extern G3Xcolor blue;

extern double ambi;
extern double diff;
extern double spec;
extern double shin;

Particle::Particle(double mass, G3Xpoint pos0, G3Xvector vit0): 
    PMat(mass, pos0, vit0) {
  // Empty
}

void Particle::algo(void) {

  PMat::_vit += PMat::_frc * h * PMat::_mass;
  PMat::_pos += PMat::_vit * h;
  
  PMat::_frc = NUL;
}

void Particle::draw(void) const {

  glPushMatrix();
    glTranslatef(_pos[0], _pos[1], _pos[2]);
    g3x_Material(blue, ambi, diff, spec, shin, 1.);
    glutSolidSphere(.5, 10, 10);
  glPopMatrix();
}
