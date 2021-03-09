#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "MyProg.h"

int main(){
	
		
	NODE* pNoeud1;
	NODE* pNoeud2;
	NODE* pNoeud3;
	NODE* pNoeud4;
	NODE* pNoeud5;
	NODE* pNoeud6;
	NODE* pNoeud7;
	NODE* pNoeud8;
	
	//Test des fonctions newNode, addNodeFin, addNodeFinRepeat, affichage et detruitNode
	pNoeud1=newNode(FORWARDc,100,NULL);
	pNoeud2=newNode(LEFTc,50,NULL);
	pNoeud3=newNode(RIGHTc,30,NULL);
	pNoeud4=newNode(REPEATc, 40, NULL);
	pNoeud5=newNode(RIGHTc, 30, NULL);
	pNoeud6=newNode(REPEATc, 40, NULL);
	pNoeud7=newNode(FORWARDc, 50, NULL);
	pNoeud8=newNode(LEFTc, 30, NULL);
	
	pNoeud5=addNodeFin(pNoeud6, pNoeud5);
	pNoeud4=addNodeFinRepeat(pNoeud5, pNoeud4);
	
	pNoeud7=addNodeFin(pNoeud8,pNoeud7);
	pNoeud6=addNodeFinRepeat(pNoeud7,pNoeud6);
	
	pNoeud1=addNodeFin(pNoeud2, pNoeud1);
	pNoeud2=addNodeFin(pNoeud3, pNoeud2);
	pNoeud3=addNodeFin(pNoeud4, pNoeud3);
	
	int a=0;
	printf("Affichage \n");
	affichageNode(pNoeud1, &a);
	detruitNode(&pNoeud1);
	
	return 0;
}
