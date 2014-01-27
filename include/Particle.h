#ifndef PARTICLE
#define PARTICLE

#include <G3Xcoord.h>

#include <PMat.h>

class Particle: public PMat {
  public:
    Particle(double, G3Xpoint pos0, G3Xvector vit0);
    
    void algo(void);
    void draw(void) const;
};

#endif
