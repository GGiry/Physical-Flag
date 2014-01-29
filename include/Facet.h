#ifndef FACET_H
#define FACET_H

#include <G3Xcoord.h>
#include <Particle.h>

class Facet {
  private:
  G3Xpoint _A, _B, _C;
  G3Xvector _normal;
  
  public:
    Facet(G3Xpoint, G3Xpoint, G3Xpoint);

    void algo(Particle);
    void draw(void) const;
};

#endif
