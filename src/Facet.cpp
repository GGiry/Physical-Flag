#include <Facet.h>

#include <cmath>

#include <cstdlib>

#include <GL/gl.h>

extern double h;

// Produit scalaire
// define G3Xprodscal(U,V)    ((U)[0]*(V)[0]+(U)[1]*(V)[1]+(U)[2]*(V)[2])
double scalar(G3Xvector u, G3Xvector v) {
  return u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
}

// Produit vectoriel
G3Xvector dotProduct(G3Xpoint &A, G3Xpoint &B, G3Xpoint &C) {
  double a,b,c;
  a = (B[1] - A[1]) * (C[2] - A[2]) - (B[2] - A[2]) * (C[1] - A[1]);
  b = (B[2] - A[2]) * (C[0] - A[0]) - (B[0] - A[0]) * (C[2] - A[2]);
  c = (B[0] - A[0]) * (C[1] - A[1]) - (B[1] - A[1]) * (C[0] - A[0]);
  return G3Xvector((const double) a, (const double) b, (const double) c);
}

G3Xvector dotProduct(G3Xvector &u, G3Xvector &v) {
  double a,b,c;
  a = u[1] * v[2] - u[2] * v[1];
  b = u[2] * v[0] - u[0] * v[2];
  c = u[0] * v[1] - u[1] * v[0];
  return G3Xvector((const double) a, (const double) b, (const double) c);
}

double sqrNorm(G3Xvector v) {
  return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

double norm(G3Xvector v) {
  return sqrt(sqrNorm(v));
}


G3Xvector normalize(G3Xvector v) {
  double l = norm(v);
  
  return G3Xvector(v[0] / l, v[1] / l, v[2] / l);
}


Facet::Facet(G3Xpoint A, G3Xpoint B, G3Xpoint C, double alpha, double beta): _A(A), _B(B), _C(C), _normal(normalize(dotProduct(A, B, C))), _alpha(alpha), _beta(beta) {
  
}


G3Xvector createVector(G3Xpoint a, G3Xpoint p) {
  return G3Xvector(p[0] - a[0], p[1] - a[1], p[2] - a[2]);
}

bool approxEqual( float a, float b, float tolerance )
{
    return abs( a - b ) < tolerance;
}

bool sameDir(G3Xvector a, G3Xvector b, float tolerance )
{
    G3Xvector aUnit = normalize(a);
    G3Xvector bUnit = normalize(b);
    return approxEqual( scalar(aUnit, bUnit), 1.0f, tolerance);
}


void Facet::algo(PMat &part) {
  G3Xpoint p = part.getPos();
  G3Xvector v = part.getVit();
  G3Xpoint q = p + v * h;
  G3Xvector ap = createVector(_A, p);
  G3Xvector pq = createVector(p, q);

  double e = 0.000001;

  double nap = scalar(_normal, ap);
  if (nap < e) {
    return;
  }
  
  double npq = scalar(_normal, pq);
  if (npq > e) {
    return;
  }
  
  double u = - nap / npq;
  if (u > 1 || u < 0) {
    return;
  }

  G3Xpoint m = p + pq * u;

  G3Xvector ma = createVector(m, _A);
  G3Xvector mb = createVector(m, _B);
  G3Xvector mc = createVector(m, _C);

  G3Xvector mamb = dotProduct(ma, mb);
  G3Xvector mbmc = dotProduct(mb, mc);
  G3Xvector mcma = dotProduct(mc, ma);

  if (!(sameDir(mamb, mbmc, 0.0001) && sameDir(mamb, mcma, 0.0001))) {
    return;
  }
  
  G3Xvector f = part.getFrc();
  G3Xvector fn = _normal * scalar(f, _normal);
  G3Xvector ft = f - fn;
  
  G3Xvector vn = _normal * scalar(v, _normal);
  G3Xvector vt = v - vn;
  
  double normFt = norm(ft);
  double normFn = norm(fn);
  
  double normVt = norm(vt);
  double normVn = norm(vn);
  
  if (normFt < _beta * normFn) {
    f = fn * (-_alpha);
  } else {
    f = fn * (-_alpha) + ft * (1 - _beta * normFn / normFt);
  }
  
  if (normVt < _beta * normVn) {
    v = vn * (-_alpha);
  } else {
    v = vn * (-_alpha) + vt * (1 - _beta * normFn / normFt);
  }
  
  part.setFrc(f);
  part.setVit(v);
  

  return;
}

void Facet::draw(void) const {
  G3Xpoint p1 = _A;
  G3Xpoint p2 = _B;
  G3Xpoint p3 = _C;
  
  G3Xpoint g = G3Xpoint((p1[0] + p2[0] + p3[0])/3, 
      (p1[1] + p2[1] + p3[1])/3,
      (p1[2] + p2[2] + p3[2])/3);
  G3Xpoint n = _normal;

  glDisable(GL_LIGHTING);
  glBegin(GL_LINES);
    //g3x_Material(yellow,ambi,diff,spec,shin,1.);
    glColor3f(1.0, .0, 0.0);
    glVertex3f(p1[0], p1[1], p1[2]);
    glVertex3f(p2[0], p2[1], p2[2]);
    
    glVertex3f(p1[0], p1[1], p1[2]);
    glVertex3f(p3[0], p3[1], p3[2]);
    
    glVertex3f(p2[0], p2[1], p2[2]);
    glVertex3f(p3[0], p3[1], p3[2]);
    
    glVertex3f(g[0], g[1], g[2]);
    glVertex3f(g[0] + n[0], g[1] + n[1], g[2] + n[2]);
  glEnd();
  glEnable(GL_LIGHTING);
}

