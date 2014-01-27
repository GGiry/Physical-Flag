#ifndef LINK
#define LINK

#include <cstdlib>

#include <PMat.h>

class Link {
  protected:
    PMat *_m1, *_m2;   
    Link(PMat* m1 = NULL, PMat* m2 = NULL);
    
  public:
    virtual void algo(void) = 0;
    virtual void draw(void) = 0;
};

#endif
