/* ===============================================================
  E.Incerti - Université de Marne-la-Vallée - incerti@univ-mlv.fr 
       - Librairie G3X - Fonctions de base d'accès public -           
	                  version 5.0 - Dec.2012
  Modifications :
    Giry Geoffrey Intégration C++
      15/11/13 : Classe G3Xcoord
  ============================================================= */

#include <G3Xcoord.h>

#include <cassert>
#include <cmath>

G3Xcoord::G3Xcoord(const double x, const double y, const double z): 
    _x(x), _y(y), _z(z) {
  // Empty
}

G3Xcoord::G3Xcoord(const double array[]): _x(array[1]), _y(array[2]), _z(array[3]) {
  // Empty
}

G3Xcoord::G3Xcoord(const G3Xcoord &coord): _x(coord._x), _y(coord._y), _z(coord._z) {
  // Empty
}

G3Xcoord::G3Xcoord() {
  // Empty
}

double& G3Xcoord::operator[](unsigned int i) {
  assert(i >= 0 && i < 3);
  
  if (i == 0) {
    return _x;
  }
  
  if (i == 1) {
    return _y;
  }
  
  return _z;
}

double G3Xcoord::operator[](unsigned int i) const {
  assert(i >= 0 && i < 3);
  
  if (i == 0) {
    return _x;
  }
  
  if (i == 1) {
    return _y;
  }
  
  return _z;
}

const G3Xcoord G3Xcoord::operator*(const double d) const {
  return G3Xcoord(_x * d, _y * d, _z * d);
}

const G3Xcoord G3Xcoord::operator-() const {
  return G3Xcoord(-_x, -_y, -_z);
}

const G3Xcoord G3Xcoord::operator-(const G3Xcoord& o) const {
  return G3Xcoord(_x - o._x, _y - o._y, _z - o._z);
}

const G3Xcoord G3Xcoord::operator+(const G3Xcoord& o) const {
  return G3Xcoord(_x + o._x, _y + o._y, _z + o._z);
}

const G3Xcoord& G3Xcoord::operator+=(const G3Xcoord& o) {
  *this = *this + o;
  
  return *this;
}

double G3Xcoord::sqrDistance(const G3Xcoord &A, const G3Xcoord &B) {
  return SQR(B[0] - A[0]) + SQR(B[1] - A[1]) + SQR(B[2] - A[2]);
}

double G3Xcoord::distance(const G3Xcoord &A, const G3Xcoord &B) {
  return sqrt(sqrDistance(A, B));
}

G3Xpoint::G3Xpoint(const double x, const double y, const double z): 
    G3Xcoord(x, y, z) {
  // Empty
}

G3Xpoint::G3Xpoint(const double t[]): G3Xcoord(t) {
  // Empty
}

G3Xpoint::G3Xpoint(const G3Xcoord& o): G3Xcoord(o) {
  // Empty
}

G3Xvector::G3Xvector(const double x, const double y, const double z): 
    G3Xcoord(x, y, z) {
  // Empty
}

G3Xvector::G3Xvector(const double t[]): G3Xcoord(t) {
  // Empty
}

G3Xvector::G3Xvector(const G3Xcoord& o): G3Xcoord(o) {
  // Empty
}

G3Xvector::G3Xvector(const G3Xpoint &a, const G3Xpoint &p) {
  _x = p[0] - a[0];
  _y = p[1] - a[1];
  _z = p[2] - a[2];
}

double G3Xvector::scalar(const G3Xvector &v) const {
  return _x * v._x + _y * v._y + _z * v._z;
}

G3Xvector G3Xvector::operator*(G3Xvector &v) const {
  double a,b,c;
  a = _y * v._z - _z * v._y;
  b = _z * v._x - _x * v._z;
  c = _x * v._y - _y * v._x;
  return G3Xvector((const double) a, (const double) b, (const double) c);
}

const G3Xvector G3Xvector::operator*(const double d) const {
  return G3Xvector(_x * d, _y * d, _z * d);
}

G3Xvector operator*(const double d, const G3Xvector& v) {
  return G3Xvector(v[0] * d, v[1] * d, v[2] * d);
}

double G3Xvector::sqrNorm() const {
  return _x * _x + _y * _y + _z * _z;
}

double G3Xvector::norm() const {
  return sqrt(sqrNorm());
}

G3Xvector G3Xvector::normalize() const {
  double l = norm();
  
  return G3Xvector(_x / l, _y / l, _z / l);
}

