#include <Damper.h>

#include <GL/gl.h>

#include <cmath>
#include <G3Xtypes.h>
#include <G3Xmacros.h>

#include <g3x_tools.h>        /* utilitaires divers                       */

Damper::Damper(const double z, PMat* m1, PMat* m2): 
    Link(m1, m2), _z(z) {
  // empty
}

void Damper::algo() { 
  G3Xvector frc = (_m2->getVit() - _m1->getVit()) * _z;
  
  _m1->updateFrc(frc);
  _m2->updateFrc(-frc);
}

void Damper::draw() {

}
