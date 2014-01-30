/* ===============================================================
  E.Incerti - Université de Marne-la-Vallée - incerti@univ-mlv.fr 
       - Librairie G3X - Fonctions de base d'accès public -           
	                  version 5.0 - Dec.2012
  Modifications :
    Giry Geoffrey Intégration C++
      15/11/13 : Création du fichier de test
  ============================================================= */

#include <PMat.h>
#include <Particle.h>
#include <FixedPoint.h>

#include <Link.h>
#include <HookSpring.h>
#include <GlobalAction.h>
#include <Damper.h>
#include <Wind.h>

#include <Facet.h>

#include <Camera.h>

#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glfw.h>

#include <G3Xall.h>

#include <iostream>
#include <typeinfo>
#include <vector>

// Colors
G3Xcolor red  = {1.0,0.5,0.0};
G3Xcolor blue = {0.0,1.0,1.0};
G3Xcolor green = {0.0,1.0,0.0};
G3Xcolor yellow = {1.0,1.0,0.0};

/* paramètres géométriques */
static double angle= 0.00;
static double rayon= 0.66;
/* paramètres de lumière/matière */
double ambi = 0.2;
double diff = 0.3;
double spec = 0.4;
double shin = 0.5;

int FAFF = 1;

double Fe = 50.;
double h = 1 / Fe;
double alpha = 0.01;
double beta = 0.001;
double k = alpha * Fe * Fe;
double z = beta * Fe;

Camera camera;

std::vector<PMat*> pMats;
std::vector<Link*> links;
std::vector<Facet*> facets;

struct GUIStates
{
    bool panLock;
    bool turnLock;
    bool zoomLock;
    int lockPositionX;
    int lockPositionY;
    int camera;
    double time;
    bool playing;
    static const float MOUSE_PAN_SPEED;
    static const float MOUSE_ZOOM_SPEED;
    static const float MOUSE_TURN_SPEED;
};
const float GUIStates::MOUSE_PAN_SPEED = 0.001f;
const float GUIStates::MOUSE_ZOOM_SPEED = 0.05f;
const float GUIStates::MOUSE_TURN_SPEED = 0.005f;

GUIStates guiStates;

void init_gui_states(GUIStates & guiStates)
{
    guiStates.panLock = false;
    guiStates.turnLock = false;
    guiStates.zoomLock = false;
    guiStates.lockPositionX = 0;
    guiStates.lockPositionY = 0;
    guiStates.camera = 0;
    guiStates.time = 0.0;
    guiStates.playing = false;
}

/* Camera */
void handleMouvements() {
  // Mouse states
  int leftButton = glfwGetMouseButton( GLFW_MOUSE_BUTTON_LEFT );
  int rightButton = glfwGetMouseButton( GLFW_MOUSE_BUTTON_RIGHT );
  int middleButton = glfwGetMouseButton( GLFW_MOUSE_BUTTON_MIDDLE );

  if( leftButton == GLFW_PRESS )
    guiStates.turnLock = true;
  else
    guiStates.turnLock = false;

  if( rightButton == GLFW_PRESS )
    guiStates.zoomLock = true;
  else
    guiStates.zoomLock = false;

  if( middleButton == GLFW_PRESS )
    guiStates.panLock = true;
  else
    guiStates.panLock = false;
    
  std::cout << "Turn: " << guiStates.turnLock << std::endl;
  std::cout << "Zoom: " << guiStates.zoomLock << std::endl;
  std::cout << "Pan: " << guiStates.panLock << std::endl;

  // Camera movements
  int altPressed = glfwGetKey(GLFW_KEY_LSHIFT);
  if (!altPressed && (leftButton == GLFW_PRESS || rightButton == GLFW_PRESS || middleButton == GLFW_PRESS)) {
    std::cout << "GELLO" << std::endl;
    int x; int y;
    glfwGetMousePos(&x, &y);
    guiStates.lockPositionX = x;
    guiStates.lockPositionY = y;
  }
  if (altPressed == GLFW_PRESS) {
    int mousex; int mousey;
    glfwGetMousePos(&mousex, &mousey);
    int diffLockPositionX = mousex - guiStates.lockPositionX;
    int diffLockPositionY = mousey - guiStates.lockPositionY;
    if (guiStates.zoomLock) {
      float zoomDir = 0.0;
      if (diffLockPositionX > 0)
        zoomDir = -1.f;
      else if (diffLockPositionX < 0 )
        zoomDir = 1.f;
      camera.zoom(zoomDir * GUIStates::MOUSE_ZOOM_SPEED);
    } else if (guiStates.turnLock) {
      camera.turn(diffLockPositionY * GUIStates::MOUSE_TURN_SPEED,
          diffLockPositionX * GUIStates::MOUSE_TURN_SPEED);
    } else if (guiStates.panLock) {
      camera.pan(diffLockPositionX * GUIStates::MOUSE_PAN_SPEED,
        diffLockPositionY * GUIStates::MOUSE_PAN_SPEED);
    }
    guiStates.lockPositionX = mousex;
    guiStates.lockPositionY = mousey;
  }
}

/* Fonction d'animation */
void Anim(void) {
  g3x_SetRefreshFreq(FAFF);
  for (std::vector<PMat*>::const_iterator it = pMats.begin(); it != pMats.end(); ++it) {
    (*it)->algo();
  }
  
  for (std::vector<Link*>::const_iterator it = links.begin(); it != links.end(); ++it) {
    (*it)->algo();
  }
}

/*= FONCTION DE DESSIN PRINCIPALE =*/
static void Dessin(void) {
  for (std::vector<PMat*>::const_iterator it = pMats.begin(); it != pMats.end(); ++it) {
    (*it)->draw();
  }

  for (std::vector<Link*>::const_iterator it = links.begin(); it != links.end(); ++it) {
    (*it)->draw();
  }
  
  for (std::vector<Facet*>::const_iterator it = facets.begin(); it != facets.end(); ++it) {
    (*it)->draw();
  }
}

/*=    ACTION A EXECUTER EN SORTIE   =*/
/*= libération de mémoire, nettoyage =*/
/*= -> utilise la pile de <atexit()> =*/
static void Exit(void)
{
  // TODO
	std::cout << std::endl << "bye !" << std::endl;
}

int main(int argc, char** argv) {
  /* initialisation de la fenêtre graphique et paramétrage Gl */
  g3x_InitWindow(*argv, 768, 512);
  
  /* paramètres caméra */
  /* param. géométrique de la caméra. cf. gluLookAt(...) */
  g3x_SetPerspective(90.,100.,1.);
  /* position, orientation de la caméra */
  g3x_SetCameraSpheric(.5*PI, 0, 40., G3Xcoord(20, 0, 0));
  
  //init_gui_states(guiStates);
  
  /* fixe les param. colorimétriques du spot lumineux */
  /* lumiere blanche (c'est les valeurs par defaut)   */	
  g3x_SetLightAmbient (1.,1.,1.);
  g3x_SetLightDiffuse (1.,1.,1.);
  g3x_SetLightSpecular(1.,1.,1.);

  /* fixe la position et la direction du spot lumineux */
  /* (c'est les valeurs par defaut)                    */	
  g3x_SetLightPosition (10.,10.,10.);
  g3x_SetLightDirection( 0., 0., 0.); 


  g3x_CreateScrollv_i((char*) "Fq", &FAFF, 1, 100, 1, (char*) "");
  g3x_CreateScrollh_d((char*) "Fe", &Fe, 10., 10000, 1, (char*) "");


  /* définition des fonctions */
  g3x_SetExitFunction(Exit);       /*  la fonction de sortie  */
  g3x_SetDrawFunction(Dessin);     /*  la fonction de Dessin  */
  g3x_SetAnimFunction(Anim);       /* la fonction d'animation */

  int nbPart = 22*14;

  int height = 14;  
  int width = nbPart / height;
  
  for (int i = 0; i < nbPart; i++) {
    PMat *p;   
    /* Flag */
    if (i < height) {
      p = new FixedPoint(G3Xpoint(2 * i, 0, 0));
    } else {
      p = new Particle(1., G3Xpoint(2 * (i % height), 2 * (i / height), 0), NUL);
    }

    pMats.push_back(p);
  }


  /* Flag */
  float kMin = 0.25 * k;
  float step = (1 - kMin) / width;
  for (int i = 0; i < nbPart - 1; i++) {
    int col = i / width;
    float kOpt =  (1. - col * step) * k;
    float kOpt2 =  (1. - (col * step + step / 2)) * k;
     
    if (((i + 1) % height) != 0) { // liens verticaux
      HookSpring* hs = new HookSpring(k, pMats[i], pMats[i + 1]);
      links.push_back(hs);
      Damper *d = new Damper(z, pMats[i], pMats[i + 1]);
      links.push_back(d);
    }

    if (i < (nbPart - height)) { // liens horizontaux
      HookSpring* hs = new HookSpring(kOpt, pMats[i], pMats[i + height]);
      links.push_back(hs);
      Damper *d = new Damper(z,  pMats[i], pMats[i + height]);
      links.push_back(d);
    }
    
    if (i < (nbPart - height) && ((i + 1) % height) != 0) { // diagonale
      HookSpring* hs = new HookSpring(kOpt, pMats[i], pMats[i + height + 1]);
      links.push_back(hs);
      Damper *d = new Damper(z,  pMats[i], pMats[i + height + 1]);
      links.push_back(d);
    }
    
    if (i < (nbPart - height) && ((i) % height) != 0) { // diagonale
      HookSpring* hs = new HookSpring(kOpt, pMats[i], pMats[i + height - 1]);
      links.push_back(hs);
      Damper *d = new Damper(z,  pMats[i], pMats[i + height - 1]);
      links.push_back(d);
    }
    
    if ((i % height) < height - 2) { // liens verticaux 2
      HookSpring* hs = new HookSpring(k, pMats[i], pMats[i + 2]);
      links.push_back(hs);
      Damper *d = new Damper(z, pMats[i], pMats[i + 2]);
      links.push_back(d);
    }
    
    if (i < (nbPart - 2 * height)) { // liens horizontaux 2
      HookSpring* hs = new HookSpring(kOpt2, pMats[i], pMats[i + 2 * height]);
      links.push_back(hs);
      Damper *d = new Damper(z,  pMats[i], pMats[i + 2 * height]);
      links.push_back(d);
    }
  }

  // Gravité
  GlobalAction ga(G3Xvector(0, 0, -1), pMats.begin(), pMats.end());  
  links.push_back(&ga);
  
  // Vent
  Wind wind(G3Xvector(1, 1, 0), pMats.begin(), pMats.end());  
  //links.push_back(&wind);
  
  // Facet
  Facet facet(G3Xpoint(0,0,0), G3Xpoint(1,1,1), G3Xpoint(0,1,0));
  facets.push_back(&facet);  

  // Sortie du mode "stable"
  //(*pMats[20]).setPos(G3Xpoint(0, 0, 4));
  
  return g3x_MainStart();
}
