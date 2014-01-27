#ifndef FIXED_POINT
#define FIXED_POINT

#include <G3Xcoord.h>

#include <PMat.h>

class FixedPoint: public PMat {
  public:
    FixedPoint(G3Xpoint pos0);
    
    void algo(void);
    void draw(void) const;
};

#endif
