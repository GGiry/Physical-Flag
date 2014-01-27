#include <GlobalAction.h>

#include <GL/gl.h>

#include <cmath>
#include <G3Xall.h>

#include <iostream>

extern G3Xcolor yellow;

extern double ambi;
extern double diff;
extern double spec;
extern double shin;

GlobalAction::GlobalAction(G3Xvector v, std::vector<PMat*>::iterator begin, std::vector<PMat*>::iterator end):
    Link(), _v(v), _begin(begin), _end(end) {
  // Empty
}

void GlobalAction::algo() {
  for (std::vector<PMat*>::const_iterator it = _begin; it != _end; ++it) {
    (*it)->updateFrc(_v);
  }
}

void GlobalAction::draw() {
  //
}
