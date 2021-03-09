#include <stdio.h>
#include <stdlib.h>

enum instructionLogo
{
	FORWARDc,
	LEFTc,
	RIGHTc,
	REPEATc,
	BLUEc,
	GREENc,
	REDc,
	TRANSPARENTc,
	BLACKc,
	SQUAREc,
	COLORc,
	STARc,
	IFc,
	ELSEc,
	USEFONCTIONc,
	DEFFONCTIONc
};

typedef enum instructionLogo instructionLogo;

typedef struct node
{
	instructionLogo instrLogo;
	int valeur;
	struct node *subProg;
	struct node *suivant;
} NODE;

typedef NODE *INSTRUCTION;

typedef struct ecartement
{
	double gauche;
	double droite;
	double bas;
	double haut;
} ECARTEMENT;

static NODE *root;
static double pi = 3.1415926;
static double xA, yA;
static int angle, color;

NODE *newNode(instructionLogo instr, int value, NODE *sousProg);
NODE *addNodeFin(NODE *pNoeud1, NODE *pNoeud2);
NODE *addNodeFinRepeat(NODE *pNoeudaAjouter, NODE *pNoeudRepeat);
NODE *addNodeFinIF(NODE *pNoeudaAjouter, NODE *pNoeudRepeat);
void affichageNode(NODE *pNoeud, int *tab);
void detruitNode(NODE **noeud);
void generationSVG(NODE *noeud);
void generationLigneSVG(FILE *fichier, NODE *noeud, NODE *racine);
/*Dans générationLigneSVG, l'entier correspondant à la couleur peut prendre les valeurs:
 * 0 pour transparent (crayon levé)
 * 1 pour rouge
 * 2 pour vert
 * 3 pour bleu
 * 4 pour noir
*/
void valeurFenetreSVG(NODE *noeud, NODE *racine, ECARTEMENT *valLimites);
void affichageStruc(ECARTEMENT ecart);
double max(double a, double b);
double absolu(double a);
void ecritureLigneSVG(FILE *fichier, double x2, double y2);
void ecritureEtoileSVG(FILE *fichier, double valNoeudDouble);
void ecritureCarreSVG(FILE *fichier, double valNoeud);
