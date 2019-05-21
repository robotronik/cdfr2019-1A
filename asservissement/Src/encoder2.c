#include "encoder2.h"
#include <math.h>
#include <stdlib.h>
// branche prog    prog/test_odo/src/main.c

#include "tim.h"
#include "stm32f4xx.h"


void theta(int* ptheta,unsigned int* cnt_droite,unsigned int* cnt_gauche,int distance_encoder){
    *ptheta=((*cnt_droite-*cnt_gauche)/628/distance_encoder*100)%628;
}

int mise_a_jour_distance(unsigned int* pdistanceparcourue_droite,unsigned int* pdistanceparcourue_gauche)
{
    int rayonroue= 460;// (cm)
    int nb_tick_tour= 500 ;
    *pdistanceparcourue_droite+=6*rayonroue/(TIM1->CNT/nb_tick_tour)/2;
    *pdistanceparcourue_gauche+=6*rayonroue/(TIM2->CNT/nb_tick_tour)/2;

    return(*pdistanceparcourue_droite);
}

void mise_a_jour_x_y(asservissement* asserv){
    int moy_diff=(*(asserv->pdistanceparcourue->droite)+*(asserv->pdistanceparcourue->gauche)/2-*(asserv->moy_prev));
    asserv->pposition->x+=moy_diff*cos(*(asserv->ptheta));
    asserv->pposition->y+=moy_diff*sin(*(asserv->ptheta));
}

void consigne(int epsilon,Point* perreur,Point* pobjectif,Point* pposition,orientation* pconsigne,int* ptheta){
    /*int alpha=1;
    int beta=1;
    perreur->x=pobjectif->x-pposition->x;
    perreur->y=pobjectif->y-pposition->y;
    int erreur_theta=atan(perreur->y/perreur->x)*100;
    int consigne_theta=(erreur_theta-*ptheta)*alpha;
    int consigne_rho_carre=(perreur->x*perreur->x+perreur->y*perreur->y)*100;
    
    if (erreur_theta>epsilon ||erreur_theta>-epsilon){
      *(pconsigne->gauche)=-consigne_rho_carre*sin(consigne_theta);
      *(pconsigne->droite)=consigne_rho_carre*sin(consigne_theta);

    }
    else{
      *(pconsigne->gauche)=beta*consigne_rho_carre;
      *(pconsigne->droite)=beta*consigne_rho_carre;
    }
    */
    *(pconsigne->gauche)=255;
    *(pconsigne->droite)=255;
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

void init(asservissement* asserv,parametre* cstes){
    *(asserv->pdistanceparcourue->droite)=0;
    *(asserv->pdistanceparcourue->gauche)=0;
    asserv->pposition->x=0;//temporaire, préférable d'inscrire la position où on place le robot initialement
    asserv->pposition->y=0;//temporaire, idem
    asserv->moy_prev=0;
    *(asserv->pconsigne->gauche)=255;
    *(asserv->pconsigne->droite)=255;
    cstes->nbpoint=5;
    cstes->cap=calloc(cstes->nbpoint,sizeof(Point*));
    cstes->epsilon=5;
    cstes->cap->x=65;
    cstes->cap->y=0;
    (cstes->cap+1)->x=65;
    (cstes->cap+1)->y=30;
    (cstes->cap+2)->x=0;
    (cstes->cap+2)->y=30;
    /*
    int i;
    for(i=0;i<nbpoint;i++){
        printf("premier point\n");
        scanf("x %d\n",&(cap+i)->x);
        scanf("y %d\n",&(cap+i)->y);
    }*/

    //list des coordonnées: abscisses puis ordonnée
}
/*
void navigation(asservissement* asserv,parametre* cstes){
    int i=0;
    asserv->perreur->x=255;
    asserv->perreur->y=255;
    ///*
    *(asserv->pconsigne->gauche)=255;
    *(asserv->pconsigne->droite)=255;
    commande_moteur((asserv->pconsigne->gauche),(asserv->pconsigne->droite));
//*/
/*
    for(i=0;i<cstes->nbpoint;i++){
      asserv->pobjectif->x=((cstes->cap)+i)->x;
      asserv->pobjectif->y=((cstes->cap)+i)->y;

      while(cstes->epsilon>asserv->perreur->x || cstes->epsilon>asserv->perreur->y){

        theta(asserv->ptheta,TIM1->CNT,TIM2->CNT,cstes->distance_encoder);

        mise_a_jour_distance(asserv->pdistanceparcourue->droite,asserv->pdistanceparcourue->gauche);
        
        mise_a_jour_x_y(asserv);

        //consigne(cstes->epsilon,asserv->perreur,asserv->pobjectif,asserv->pposition,asserv->pconsigne,asserv->ptheta);
      *(asserv->pconsigne->gauche)=255;
      *(asserv->pconsigne->droite)=255;
        commande_moteur((asserv->pconsigne->gauche),(asserv->pconsigne->droite));

    }
  }

}
*/