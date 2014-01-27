#ifndef GLOBAL_ACTION
#define GLOBAL_ACTION

#include <vector>

#include <Link.h>

class GlobalAction: public Link {
  protected:
    G3Xvector _v; // GlobalAction vector
    std::vector<PMat*>::iterator _begin;
    std::vector<PMat*>::iterator _end;

  public:
    GlobalAction(G3Xvector, std::vector<PMat*>::iterator begin, std::vector<PMat*>::iterator end);

    void algo(void);
    void draw(void);
};

#endif
