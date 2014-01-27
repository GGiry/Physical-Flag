#ifndef PMAT
#define PMAT

#include <G3Xcoord.h>

class PMat {
  protected:
    G3Xpoint _pos;
    G3Xvector _vit, _frc;
    double _mass;
  
    PMat(const double mass, const G3Xpoint pos0 = NUL, const G3Xvector vit0 = NUL);
    
  public:
    PMat();
    PMat(const PMat&);
    const G3Xpoint& getPos() const;
    const G3Xvector& getVit() const;
    void setPos(G3Xpoint);
    void updateFrc(G3Xvector);
    
    virtual void algo();
    virtual void draw(void) const;
};

#endif
