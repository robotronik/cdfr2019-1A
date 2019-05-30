#include "ultrason.h"

typedef struct{
	TYPE_INST type; //1 = wait, 2= esquive, 3= tourner, 4= avancer, 5= end
	int fini;
	double par; // parametres pour tourner angle pour avancer distance
} INSTRUCTION;

typedef struct _pile{
	struct _pile *next;
	INSTRUCTION instruction;
}* PILE;

typedef enum type{RUN,WAIT,TOURNER,AVANCER,END} TYPE_INST;

PILE pilePush(PILE pile, INSTRUCTION inst);
PILE pilePop(PILE pile);
TYPE_INST  pileRun(PILE pile);

TYPE_INST doInstruction(INSTRUCTION instruction);

PILE lecturePath(); //remplis la pile avec les instructions

INSTRUCTION creerW(int temps);
INSTRUCTION creerE(int temps);
INSTRUCTION creerT(double angle);//entre -1 et +1
INSTRUCTION creerA(double distance);//distance float

int initPileInstruction();
int cyclePileInstruction();
