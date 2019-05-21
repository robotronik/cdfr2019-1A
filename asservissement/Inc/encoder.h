#ifndef ENCODER_H
#define ENCODER_H

typedef struct
{
  int x;
  int y;
} Point;

int* ptheta;
int distance_encoder;
int objectif_x;
int objectif_y;
unsigned int* cnt_droite;
unsigned int* cnt_gauche;
unsigned int* pdistanceparcourue_droite;
unsigned int* pdistanceparcourue_gauche;
int* px;
int* py;
int* moy_prev;
int* pconsigne_gauche;
int* pconsigne_droite;
Point* cap;
int nbpoint;
int epsilon;

/*

*/

void theta(int* ptheta,unsigned int* cnt_droite,unsigned int* cnt_gauche,int distance_encoder);
int mise_a_jour_distance(unsigned int* pdistanceparcourue_droite,unsigned int* pdistanceparcourue_gauche);
void mise_a_jour_x_y(int* px,int* py,int* ptheta,int* moy_prev,unsigned int *pdistanceparcourue_droite,unsigned int* pdistanceparcourue_gauche);
void consigne(int epsilon,int objectif_x,int objectif_y,int* px,int* py,int* pconsigne_gauche,int* pconsigne_droite,int* ptheta);
void commande_moteur(int* pconsigne_gauche,int* pconsigne_y);
void init(int nbpoint,int epsilon,Point* cap,int* ptheta,unsigned int* cnt_droite,unsigned int* cnt_gauche,unsigned int* pdistanceparcourue_droite,unsigned int* pdistanceparcourue_gauche,int* px,int* py,int* moy_prev,int* pconsigne_gauche,int* pconsigne_droite);
void navigation(int nbpoint,int epsilon,Point* cap,int* ptheta,unsigned int* cnt_droite,unsigned int* cnt_gauche,unsigned int* pdistanceparcourue_droite,unsigned int* pdistanceparcourue_gauche,int* px,int* py,int* moy_prev,int* pconsigne_gauche,int* pconsigne_droite);
  
/*

*/


#endif
