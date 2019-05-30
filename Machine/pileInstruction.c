#define TIMEW 5

PILE pile;

int initPileInstruction(){
	pile = lecturePath(/*chemin du fichier du Path*/);//remplis la pile avec les instructions
}

int cyclePileInstruction(){
	//Detection ultrason
	if(detectUS()){
		INSTRUCTION wait = creerW(TIMEW);
		pilePush(pile,wait); // PILE pile, INSTRUCTION wait
	}
		
	//Execution de l'Instruction TOP
	if(pileRun(pile)==END){
		break;
	}
}

TYPE_INST pileRun(PILE pile){
	if(pile.instruction.temps < 1){
		pilePop(pile);
		return RUN; //encore en cours
	}
	else{
		pile.instruction.temps--;
		return doInstruction(pile.instruction); //verifie si END ou autre
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

INSTRUCTION creerW(int temps){
	INSTRUCTION inst;
	inst.type = WAIT;
	inst.temps = temps;
	return inst;
}

INSTRUCTION creerT(double angle){
	INSTRUCTION inst;
	inst.type = TOURNER;
	/*REMPLIR AVEC LA FONCTION DE CALCUL DU TEMPS*/
	
	return inst;
}

INSTRUCTION creerA(double distance){
	INSTRUCTION inst;
	inst.type = AVANCER;
	/*REMPLIR AVEC LA FONCTION DE CALCUL DU TEMPS*/
	
	return inst;
}

TYPE_INST doInstruction(INSTRUCTION instruction){
	
	switch(instruction.type) {
		case RUN:
			printf("type is run\n");
			break;
		case WAIT: 
			printf("type is wait\n"); 
			break;
		case ESQUIVE: 
			printf("type is esquive\n"); 
			break;
		case TOURNER: 
			printf("type is tourner\n"); 
			break;
		case AVANCER: 
			printf("type is avancer\n"); 
			break;
		case END: 
			printf("type is end\n"); 
			break;
		default: 
			printf("---DEFAULT---\n"); 
			break;
	}
}


