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
    
    const double getMas() const;
    const G3Xpoint& getPos() const;
    const G3Xvector& getVit() const;
    const G3Xvector& getFrc() const;
    
    void setPos(G3Xpoint);
    void setVit(G3Xvector& v) {
      _vit = v;
    }
    void setFrc(G3Xvector& v) {
      _frc = v;
    }
    
    void updateFrc(G3Xvector);
    
    virtual void algo();
    virtual void draw(void) const;
};

#endif
