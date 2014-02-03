/* ===============================================================
  E.Incerti - Université de Marne-la-Vallée - incerti@univ-mlv.fr 
       - Librairie G3X - Fonctions de base d'accès public -           
	                  version 5.0 - Dec.2012
  Modifications :
    Giry Geoffrey Intégration C++
      15/11/13 : Classe G3Xcoord
  ============================================================= */

#ifndef G3XPP_COORD_CPP
#define G3XPP_COORD_CPP

#define SQR(a) ((a)*(a))

#include <iostream>

class G3Xcoord {
  protected:
    double _x;
    double _y;
    double _z;

    G3Xcoord();

  public:
    G3Xcoord(const double, const double, const double);
    G3Xcoord(const double[]);
    G3Xcoord(const G3Xcoord&);
    
    double& operator[](unsigned int);
    double operator[](unsigned int) const;
    
    const G3Xcoord operator*(const double d) const;
    
    const G3Xcoord operator-() const;
    const G3Xcoord operator-(const G3Xcoord& o) const;
    
    const G3Xcoord operator+(const G3Xcoord& o) const;
    
    const G3Xcoord& operator+=(const G3Xcoord&);
    
    friend std::ostream& operator<<(std::ostream& os, const G3Xcoord& v) {
  os << "[" << v._x << ", " << v._y << ", " << v._z << "]";
  return os;
}

    static double distance(G3Xcoord const &A, G3Xcoord const &B);
    static double sqrDistance(const G3Xcoord &A, const G3Xcoord &B);
};

class G3Xpoint: public G3Xcoord {
  public:
    G3Xpoint(const double, const double, const double);
    G3Xpoint(const double[]);
    G3Xpoint(const G3Xcoord&);
};

class G3Xvector: public G3Xcoord {
  public:
    G3Xvector(const double, const double, const double);
    G3Xvector(const double[]);
    G3Xvector(const G3Xcoord&);
    G3Xvector(const G3Xpoint &a, const G3Xpoint &p);
    
    G3Xvector operator*(G3Xvector &v) const;
    const G3Xvector operator*(const double d) const;
    
    double scalar(const G3Xvector &v) const;
    
    double sqrNorm() const;
    double norm() const;
    G3Xvector normalize() const;
    
};

G3Xvector operator*(const double d, const G3Xvector& v);

const G3Xcoord NUL(0,0,0);

#endif
