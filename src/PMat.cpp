#include <PMat.h>

#include <cassert>

PMat::PMat(): 
    _mass(-1), _pos(NUL), _vit(NUL), _frc(NUL) {
  // Empty
}

PMat::PMat(const double mass, const G3Xpoint pos0, const G3Xvector vit0): 
    _mass(mass), _pos(pos0), _vit(vit0), _frc(NUL) {
  // Empty
}

PMat::PMat(const PMat& o): 
    _mass(o._mass), _pos(o._pos), _vit(o._vit), _frc(o._frc) {
  // Empty
}

void PMat::setPos(G3Xpoint newPos) {
  _pos = newPos;
}

const G3Xpoint& PMat::getPos() const {
  return _pos;
}

const G3Xvector& PMat::getVit() const {
  return _vit;
}

void PMat::updateFrc(G3Xvector vector) {
  _frc += vector;
}

void PMat::algo() {
  assert(false);
}

void PMat::draw() const {
  assert(false);
}
