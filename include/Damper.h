#ifndef DAMPER
#define DAMPER

#include <Link.h>

class Damper: public Link {
  public:
    Damper(const double z, PMat* m1, PMat* m2);

    void algo(void);
    void draw(void);

  private:
    float _z;
};

#endif
