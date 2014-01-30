#ifndef FACET_H
#define FACET_H

#include <G3Xcoord.h>
#include <PMat.h>

class Facet {
  private:
  G3Xpoint _A, _B, _C;
  G3Xvector _normal;
  
  double _alpha, _beta;
  
  public:
    Facet(G3Xpoint, G3Xpoint, G3Xpoint, double, double);

    void algo(PMat &);
    void draw(void) const;
};

#endif
