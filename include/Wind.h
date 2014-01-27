#ifndef WIND
#define WIND

#include <vector>

#include <GlobalAction.h>

class Wind: public GlobalAction {
  private:
    double _val;

  public:
    Wind(G3Xvector, std::vector<PMat*>::iterator begin, std::vector<PMat*>::iterator end);

    void algo(void);
    void draw(void);
};

#endif
