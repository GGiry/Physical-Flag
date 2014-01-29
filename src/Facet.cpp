#include <Facet.h>

#include <GL/gl.h>

G3Xvector dotProduct(G3Xpoint &A, G3Xpoint &B, G3Xpoint &C) {
  double a,b,c;
  a = (B[1] - A[1]) * (C[2] - A[2]) - (B[2] - A[2]) * (C[1] - A[1]);
  b = (B[2] - A[2]) * (C[0] - A[0]) - (B[0] - A[0]) * (C[2] - A[2]);
  c = (B[0] - A[0]) * (C[1] - A[1]) - (B[1] - A[1]) * (C[0] - A[0]);
  return G3Xvector((const double) a, (const double) b, (const double) c);
}

Facet::Facet(G3Xpoint A, G3Xpoint B, G3Xpoint C): _A(A), _B(B), _C(C), _normal(dotProduct(A, B, C)) {
  
}

void Facet::algo(Particle p) {
    return;
}

void Facet::draw(void) const {
  G3Xpoint p1 = _A;
  G3Xpoint p2 = _B;
  G3Xpoint p3 = _C;

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
  glEnd();
  glEnable(GL_LIGHTING);
}

