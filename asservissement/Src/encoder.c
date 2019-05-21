
#include "encoder.h"
#include <math.h>
#include <stdlib.h>
// branche prog    prog/test_odo/


#include "tim.h"
#include "stm32f4xx.h"


void theta(int* ptheta,unsigned int* cnt_droite,unsigned int* cnt_gauche,int distance_encoder){
    *ptheta=((*cnt_droite-*cnt_gauche)/distance_encoder*100/628)%628;
}

int mise_a_jour_distance(Encoder* encoder_droite,Encoder* encoder_gauche,unsigned int* pdistanceparcourue_droite,unsigned int* pdistanceparcourue_gauche)
{
  
    int rayonroue= 460; //(cm)
    int nb_tick_tour= 50 ;
    *pdistanceparcourue_droite+=6*rayonroue/(EncVal_droite/*TIM1->CNT/nb_tick_tour*/)/2;
    *pdistanceparcourue_gauche+=6*rayonroue/(EncVal_gauche/*TIM2->CNT/nb_tick_tour*/)/2;

    return(*pdistanceparcourue_droite);
}

void mise_a_jour_x_y(int* px,int* py,int* ptheta,int* moy_prev,unsigned int *pdistanceparcourue_droite,unsigned int* pdistanceparcourue_gauche){
    int moy_diff=(*pdistanceparcourue_droite+*pdistanceparcourue_gauche)/2-*moy_prev;
    *px+=moy_diff*cos(*ptheta);
    *py+=moy_diff*sin(*ptheta);
}

void consigne(int epsilon,int objectif_x,int objectif_y,int* px,int* py,int* pconsigne_gauche,int* pconsigne_y,int* ptheta){
    int alpha=1;
    int beta=1;
    int erreur_x=objectif_x-*px;
    int erreur_y=objectif_y-*py;
    int erreur_theta=atan(erreur_y/erreur_x)*10;//-*ptheta;
    int consigne_theta=(erreur_theta)*alpha; /*-*ptheta*/
    int consigne_rho_carre=(erreur_x*erreur_x+erreur_y*erreur_y)*10;
    
    if (consigne_theta>0.2 || consigne_theta>-0.2){
      *pconsigne_gauche=consigne_rho_carre*sin(consigne_theta);
      *pconsigne_droite=-consigne_rho_carre*sin(consigne_theta);

    }
    else{
      *pconsigne_gauche=beta*consigne_rho_carre;
      *pconsigne_droite=beta*consigne_rho_carre;
    }
    
}

void commande_moteur(int* pconsigne_gauche,int* pconsigne_droite){

    if(*pconsigne_gauche<0){
      htim3.Instance->CCR3 = 0; 
      htim3.Instance->CCR4 = -*pconsigne_gauche; 
    }
    if(*pconsigne_gauche>0){
      htim3.Instance->CCR3 =*pconsigne_gauche;
      htim3.Instance->CCR4 =0;
    }
    
    if(*pconsigne_droite>0){
      htim3.Instance->CCR1 =*pconsigne_droite;
      htim3.Instance->CCR2 =0;
    }
    if(*pconsigne_droite<0){
      htim3.Instance->CCR2 = -*pconsigne_droite;
      htim3.Instance->CCR1 = 0;
    }
    
}


void init(int nbpoint,int epsilon,Point* cap,int* ptheta,unsigned int* cnt_droite,unsigned int* cnt_gauche,
  unsigned int* pdistanceparcourue_droite,unsigned int* pdistanceparcourue_gauche,int* px,int* py,int* moy_prev,int* pconsigne_gauche,int* pconsigne_droite){
    distance_encoder=32;
    *cnt_droite=TIM1->CNT;
    *cnt_gauche=TIM2->CNT;
    *pdistanceparcourue_droite=0;
    *pdistanceparcourue_gauche=0;
    *px=0;//temporaire, préférable d'inscrire la position où on place le robot initialement
    *py=0;//temporaire, idem
    moy_prev=0;
    *pconsigne_gauche=255;
    *pconsigne_droite=255;
    nbpoint=5;
    cap=calloc(nbpoint,sizeof(Point*));
    epsilon=5;
    cap->x=65;
    cap->y=0;
    /*
    int i;
    for(i=0;i<nbpoint;i++){
        printf("premier point\n");
        scanf("x %d\n",&(cap+i)->x);
        scanf("y %d\n",&(cap+i)->y);
    }*/

    //list des coordonnées: abscisses puis ordonnée
}

void navigation(int nbpoint,int epsilon,Point* cap,int* ptheta,unsigned int* cnt_droite,unsigned int* cnt_gauche,unsigned int* pdistanceparcourue_droite,
  unsigned int* pdistanceparcourue_gauche,int* px,int* py,int* moy_prev,int* pconsigne_gauche,int* pconsigne_droite){
    int i=0;
    int erreur_x=255;
    int erreur_y=255;
    int objectif_x;
    int objectif_y;
    for(i=0;i<nbpoint;i++){
      objectif_x=(cap+i)->x;
      objectif_y=(cap+i)->y;

      while(epsilon>erreur_x || epsilon>erreur_y){

        theta(ptheta,cnt_droite,cnt_gauche,32);
        mise_a_jour_distance(pdistanceparcourue_droite,pdistanceparcourue_gauche);
        mise_a_jour_x_y(px,py,ptheta,moy_prev,pdistanceparcourue_droite,pdistanceparcourue_gauche);
        consigne(epsilon,objectif_x,objectif_y,px,py,pconsigne_gauche,pconsigne_droite,ptheta);
        
        *pconsigne_gauche=120;
        *pconsigne_droite=120;
        
        commande_moteur(pconsigne_gauche,pconsigne_droite);
        erreur_x=*px-objectif_x;
        erreur_y=*py-objectif_y;

    }
  }

}
