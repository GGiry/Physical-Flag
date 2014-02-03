#include <Facet.h>

#include <cmath>

#include <cstdlib>

#include <GL/gl.h>

#include <G3Xall.h>

#define DEBUG (0)

extern double h;

// Normal au plan contenant les points A, B et C
G3Xvector computeNormal(G3Xpoint &A, G3Xpoint &B, G3Xpoint &C) {
  G3Xvector ab(A, B);
  G3Xvector bc(B, C);

  return (ab * bc).normalize();
}

Facet::Facet(G3Xpoint A, G3Xpoint B, G3Xpoint C, double alpha, double beta): _A(A), _B(B), _C(C), _normal(computeNormal(A, B, C)), _alpha(alpha), _beta(beta) {

}

int sameDir(G3Xvector u, G3Xvector n, double e) {
  if (u.scalar(n) < e) {
    return -1;
  }
  return 1;
} 

void Facet::algo(PMat &part) {
  
  G3Xpoint p = part.getPos();
  G3Xvector ap(_A, p);
  
  if (DEBUG) {
    std::cout << "Facette:" << std::endl;
    std::cout << "P: " << p << std::endl; 
  }

  double e = 0.00000001;

  double nap = _normal.scalar(ap);
  if (nap < e) {
    if (DEBUG) {
      std::cout << "Masse au dessous de la facette: " << nap << std::endl;
    }
    return;
  }

  G3Xvector v = part.getVit();
  G3Xvector f = part.getFrc();
  // On intègre aussi les forces qui s'appliquent à la particule
  G3Xpoint q = p + h * (v + f * h * part.getMas());
  G3Xvector pq(p, q);
  if (DEBUG) {
    std::cout << "Q: " << q << std::endl; 
  }

  double npq = _normal.scalar(pq);
  if (npq >= 0) {
    if (DEBUG) {
      std::cout << "Masse ne se dirige pas vers" << std::endl;
    }
    return;
  }
  
  double u = - nap / npq;
  if (u > 1) {
    if (DEBUG) {
      std::cout << "Q au dessus de la facette" << std::endl;
    }
    return;
  }
  
  G3Xpoint m = p + u * pq;

  if (DEBUG) {
    std::cout << "M: " << m << std::endl;
  }

  G3Xvector ma(m, _A);
  G3Xvector mb(m, _B);
  G3Xvector mc(m, _C);

  G3Xvector mamb = ma * mb;
  G3Xvector mbmc = mb * mc;
  G3Xvector mcma = mc * ma;

  double ep = 0.000001;

  int dirMAMB = sameDir(mamb, _normal, ep);

  if ((dirMAMB != sameDir(mbmc, _normal, ep)) || (dirMAMB != sameDir(mcma, _normal, ep))) {
    if (DEBUG) {
      std::cout << "M n'appartient pas a [ABC]" << std::endl;
    }
    return;
  }

  G3Xvector fn = _normal * f.scalar(_normal);
  G3Xvector ft = f - fn;

  G3Xvector vn = _normal * v.scalar(_normal);
  G3Xvector vt = v - vn;

  double normFt = ft.norm();
  double normFn = fn.norm();

  double normVt = vt.norm();
  double normVn = vn.norm();
  
  G3Xvector fCpy(f);
  G3Xvector vCpy(v);

  if (normFt - _beta * normFn < e) {
    f = -_alpha * fn;
  } else {
    f = -_alpha * fn + (1 - _beta * normFn / normFt) * ft;
  }

  if (normVt - _beta * normVn < e) {
    v = -_alpha * vn;
  } else {
    v = -_alpha * vn + (1 - _beta * normVn / normVt) * vt;
  }
  
  part.setFrc(f);
  part.setVit(v);

  if (DEBUG) {
    std::cout << "F   : " << fCpy << std::endl;
    std::cout << "Fnew: " << f << std::endl;
    std::cout << "V   : " << vCpy << std::endl;
    std::cout << "Vnew: " << v << std::endl;
  }

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

