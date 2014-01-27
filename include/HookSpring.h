#ifndef HOOK_SPRING
#define HOOK_SPRING

#include <Link.h>

class HookSpring: public Link {
  public:
    HookSpring(const double k, PMat* m1, PMat* m2);

    void algo(void);
    void draw(void);

  private:
    double _k;
    double _l;
};

#endif
