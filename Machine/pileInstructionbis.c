#define TIMEW 5

#include "instruction.h"

PILE pile;

int initPileInstruction(){
	pile = lecturePath(/*chemin du fichier du Path*/);//remplis la pile avec les instructions
}

int cyclePileInstruction(){
	//Detection ultrason
	if(detectUS()){
		stop();
	}
		
	//Execution de l'Instruction TOP
	if(pileRun(pile)==END){
		return 1;
	}
	else{
		return 0;
	}
}

TYPE_INST pileRun(PILE pile){
	if(pile.instruction.fini){
		pilePop(pile);
		//Reinit odometry
		
		return RUN; //encore en cours
	}
	else{
		return doInstruction(&(pile.instruction)); //verifie si END ou autre
	}
}

PILE pilePush(PILE pile, INSTRUCTION inst){
	PILE nouv = malloc(sizeof(*nouv));
	if(nouv != NULL){
		nouv->instruction = inst;
		nouv->next = pile;
	}
	return nouv;
}

PILE pilePop(PILE pile){
	if(pile != NULL){
		PILE nouv = pile;
		pile = pile->suiv;
		free(nouv);
	}
	return pile;
}

INSTRUCTION creerT(double angle){
	INSTRUCTION inst;
	inst.type = TOURNER;
	inst.fini = 0;
	inst.par = angle;
	
	return inst;
}

INSTRUCTION creerA(double distance){
	INSTRUCTION inst;
	inst.type = AVANCER;
	inst.fini = 0;
	inst.par = distance;
	
	return inst;
}

TYPE_INST doInstruction(INSTRUCTION* instruction){
	
	switch(instruction->type) {
		case RUN:
			stop();
			instruction->fini = 1;
			break;
		case TOURNER: 
			if(tourner(instruction->par)){
				instruction->fini = 1;
			} 
			break;
		case AVANCER: 
			if(avancer(instruction->par)){
				instruction->fini = 1;
			}
			break;
		case END: 
			stop();
			break;
		default: 
			stop(); 
			break;
	}
	
	return instruction->type; 
}


