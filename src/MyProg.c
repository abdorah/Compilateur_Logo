#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "MyProg.h"

NODE *newNode(instructionLogo instr, int value, NODE *sousProg)
{
	NODE *pNoeud = (NODE *)malloc(sizeof(NODE));
	if (pNoeud == NULL)
	{
		fprintf(stderr, "Problème de malloc: plus de mémoire\n");
	}
	pNoeud->instrLogo = instr;
	pNoeud->valeur = value;
	pNoeud->subProg = sousProg;
	return pNoeud;
}

NODE *addNodeFin(NODE *pNoeudaAjouter, NODE *pNoeud)
{
	if (pNoeud == NULL)
	{
		pNoeudaAjouter = pNoeud;
	}
	else
	{
		/*if(pNoeud->suivant==NULL){
			pNoeud->suivant=pNoeudaAjouter;
			return pNoeud;
		}*/
		NODE *cur = pNoeud;
		while (cur->suivant != NULL)
		{
			cur = cur->suivant;
		}
		cur->suivant = pNoeudaAjouter;
	}
	return pNoeud;
}

NODE *addNodeFinRepeat(NODE *pNoeudaAjouter, NODE *pNoeudRepeat)
{
	if (pNoeudRepeat->instrLogo == REPEATc || pNoeudRepeat->instrLogo == DEFFONCTIONc)
	{
		if (pNoeudRepeat->subProg == NULL)
		{
			pNoeudRepeat->subProg = pNoeudaAjouter;
		}
		else
		{
			NODE *cur = pNoeudRepeat->subProg;
			while (cur->suivant != NULL)
			{
				cur = cur->suivant;
			}
			cur->suivant = pNoeudaAjouter;
		}
	}
	else
	{
		printf("Erreur: pas un addFinRepeat appelé sur un non repeat\n");
	}
	return pNoeudRepeat;
}

NODE *addNodeFinIF(NODE *pNoeudaAjouter, NODE *pNoeudRepeat)
{
	if (pNoeudRepeat->instrLogo == IFc || pNoeudRepeat->instrLogo == DEFFONCTIONc)
	{
		//if (pNoeudRepeat->valeur)
		//{
			if (pNoeudRepeat->subProg == NULL)
			{
				pNoeudRepeat->subProg = pNoeudaAjouter;
			}
			else
			{
				NODE *cur = pNoeudRepeat->subProg;
				while (cur->suivant != NULL)
				{
					cur = cur->suivant;
				}
				cur->suivant = pNoeudaAjouter;
			}
		//}
		
	}
	else
	{
		printf("Erreur: pas un addFinRepeat appelé sur un non repeat\n");
	}
	return pNoeudRepeat;
}

void detruitNode(NODE **ppNoeud)
{
	if (*ppNoeud == NULL)
		return;
	detruitNode(&(**ppNoeud).suivant);
	detruitNode(&(**ppNoeud).subProg);
	free(*ppNoeud);
}

void affichageNode(NODE *pNoeud, int *tab)
{
	if (pNoeud == NULL)
		return;
	else
	{
		int i;
		int a = *tab;
		for (i = 1; i <= a; i++)
		{
			printf("\t");
		}
		switch (pNoeud->instrLogo)
		{
		case FORWARDc:
			printf("FORWARD ");
			printf("%d", pNoeud->valeur);
			break;
		case LEFTc:
			printf("LEFT ");
			printf("%d", pNoeud->valeur);
			break;
		case RIGHTc:
			printf("RIGHT ");
			printf("%d", pNoeud->valeur);
			break;
		case REPEATc:
			printf("REPEAT ");
			printf("%d", pNoeud->valeur);
			break;
		case IFc:
			printf("IF ");
			printf("%d", pNoeud->valeur);
			break;
		case BLUEc:
			printf("BLUE ");
			break;
		case GREENc:
			printf("GREEN ");
			break;
		case REDc:
			printf("RED ");
			break;
		case TRANSPARENTc:
			printf("TRANSPARENT ");
			break;
		case BLACKc:
			printf("BLACK ");
			break;
		case COLORc:
			printf("COLOR ");
			printf("#%X", pNoeud->valeur);
			break;
		case STARc:
			printf("STAR ");
			printf("%d", pNoeud->valeur);
			break;
		case DEFFONCTIONc:
			printf("DEFINE FONCTION ");
			printf("%d", pNoeud->valeur);
			break;
		case USEFONCTIONc:
			printf("USE FONCTION ");
			printf("%d", pNoeud->valeur);
			break;
		default:
			printf("Instruction inconnue");
			break;
		}
		if (pNoeud->instrLogo == REPEATc || pNoeud->instrLogo == DEFFONCTIONc)
		{
			printf(" [\n");
			a = a + 1;
			affichageNode(pNoeud->subProg, &a);
			a = a - 1;
			for (i = 1; i <= a; i++)
			{
				printf("\t");
			}
			printf("]");
		}
		else if (pNoeud->instrLogo == IFc)
		{
			
				printf(" [\n");
				a = a + 1;
				affichageNode(pNoeud->subProg, &a);
				a = a - 1;
				for (i = 1; i <= a; i++)
				{
					printf("\t");
				}
				printf("]");
			
		}

		printf("\n");
		affichageNode(pNoeud->suivant, tab);
		return;
	}
}

void generationSVG(NODE *noeud)
{
	if (noeud == NULL)
	{
		printf("Generation SVG sur un noeud nul\n");
	}

	FILE *dest = NULL;
	dest = fopen("dessin.svg", "w+");
	ECARTEMENT valeursMax;
	valeursMax.gauche = 0.0;
	valeursMax.droite = 0.0;
	valeursMax.haut = 0.0;
	valeursMax.bas = 0.0;
	xA = 0; //xA et yA correspondent au milieu de la fenêtre: on cherche l'écartement maximal par rapport à ce milieu
	yA = 0;
	angle = 0;
	color = 4; //Noir par défaut
	valeurFenetreSVG(noeud, noeud, &valeursMax);
	double width = 2 * max(absolu(valeursMax.gauche), valeursMax.droite) + 100.0;
	double height = 2 * max(absolu(valeursMax.haut), valeursMax.bas) + 100.0;
	fputs("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n", dest);
	fprintf(dest, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%f\" height=\"%f\">\n", width, height);

	xA = width / 2;
	yA = height / 2;
	angle = 0;
	generationLigneSVG(dest, noeud, noeud);

	fputs("</svg>", dest);
	fclose(dest);
}

void generationLigneSVG(FILE *fichier, NODE *noeud, NODE *racine)
{
	if (noeud == NULL)
		return;
	if (noeud->instrLogo == REPEATc)
	{
		int i;
		int a = noeud->valeur;
		for (i = 0; i < a; i++)
		{
			generationLigneSVG(fichier, noeud->subProg, racine);
		}
	}
	else if (noeud->instrLogo == IFc)
	{

		int a = noeud->valeur;
		if (a)
		{
			generationLigneSVG(fichier, noeud->subProg, racine);
		}
	}
	else
	{
		int valNoeud = noeud->valeur;
		double valNoeudDouble = (double)valNoeud;
		double dx, dy;
		double x2, y2;
		NODE *parcours = racine;
		switch (noeud->instrLogo)
		{
		case RIGHTc:
			angle = angle + valNoeud;
			break;

		case LEFTc:
			angle = angle - valNoeud;
			break;

		case FORWARDc:
			dx = (double)valNoeud * cos((double)angle * pi / 180);
			dy = (double)valNoeud * sin((double)angle * pi / 180);
			x2 = xA + dx;
			y2 = yA + dy;
			ecritureLigneSVG(fichier, x2, y2);
			xA = x2;
			yA = y2;
			break;
		case SQUAREc:
			ecritureCarreSVG(fichier, valNoeudDouble);

			xA = xA + valNoeud; //Le curseur passe du coin haut gauche du carré dessiné au coin haut droit

			break;

		case TRANSPARENTc:
			color = 0;
			break;

		case REDc:
			color = 1;
			break;

		case GREENc:
			color = 2;
			break;

		case BLUEc:
			color = 3;
			break;

		case BLACKc:
			color = 4;
			break;
		case COLORc:
			color = valNoeud;
			break;
		case STARc:
			ecritureEtoileSVG(fichier, valNoeudDouble);
			xA += 2 * valNoeud + 2 * valNoeud * cos((double)pi / 180 * 72.0);
			break;
		case USEFONCTIONc:
			while (parcours != NULL)
			{
				if (parcours->instrLogo == DEFFONCTIONc && parcours->valeur == valNoeud)
				{
					generationLigneSVG(fichier, parcours->subProg, racine);
					break;
				}
				parcours = (parcours->suivant);
			}
			break;
		}
	}
	generationLigneSVG(fichier, noeud->suivant, racine);
}

void valeurFenetreSVG(NODE *noeud, NODE *racine, ECARTEMENT *valLimites)
{
	if (noeud == NULL)
		return;
	if (noeud->instrLogo == REPEATc)
	{
		int i;
		int a = noeud->valeur;
		for (i = 0; i < a; i++)
		{
			valeurFenetreSVG(noeud->subProg, racine, valLimites);
		}
	}
	else if (noeud->instrLogo == IFc)
	{

		int a = noeud->valeur;
		if (a)
		{
			valeurFenetreSVG(noeud->subProg, racine, valLimites);
		}
	}
	else
	{
		int valNoeud = noeud->valeur;
		double valNoeudDouble = (double)valNoeud;
		double dx, dy;
		double x2, y2;
		NODE *parcours = racine;
		switch (noeud->instrLogo)
		{
		case RIGHTc:
			angle = angle + valNoeud;
			break;

		case LEFTc:
			angle = angle - valNoeud;
			break;
		case FORWARDc:
			dx = valNoeudDouble * cos((double)angle * pi / 180);
			dy = valNoeudDouble * sin((double)angle * pi / 180);
			xA = xA + dx;
			yA = yA + dy;
			if (xA > valLimites->droite)
				valLimites->droite = xA;
			else if (xA < valLimites->gauche)
				valLimites->gauche = xA;

			if (yA > valLimites->bas)
				valLimites->bas = yA;
			else if (yA < valLimites->haut)
				valLimites->haut = yA;
			break;

		case SQUAREc:
			if (xA + valNoeudDouble > valLimites->droite)
				valLimites->droite = xA + valNoeudDouble;
			if (yA + valNoeudDouble > valLimites->bas)
				valLimites->bas = yA + valNoeudDouble;
			xA = xA + valNoeudDouble;

			break;
		case STARc:
			xA += 2 * valNoeudDouble + 2 * valNoeudDouble * cos((double)pi / 180 * 72.0);
			if (xA > valLimites->droite)
				valLimites->droite = xA;

			if (yA + valNoeudDouble * sin((double)pi / 180 * 72.0) > valLimites->bas)
				valLimites->bas = yA + valNoeudDouble * sin((double)pi / 180 * 72.0) + valNoeudDouble * sin((double)pi / 180 * 144.0);
			else if (yA - valNoeudDouble * sin((double)pi / 180 * 72.0) < valLimites->haut)
				valLimites->haut = yA - valNoeudDouble * sin((double)pi / 180 * 72.0);

			break;
		case USEFONCTIONc:
			while (parcours != NULL)
			{
				if (parcours->instrLogo == DEFFONCTIONc && parcours->valeur == valNoeud)
				{
					valeurFenetreSVG(parcours->subProg, racine, valLimites);
					break;
				}
				parcours = (parcours->suivant);
			}
			break;
		}
	}
	valeurFenetreSVG(noeud->suivant, racine, valLimites);
}

void affichageStruc(ECARTEMENT ecart)
{
	printf("Droite: %f, Gauche: %f, Haut: %f, Bas: %f\n", ecart.droite, ecart.gauche, ecart.haut, ecart.bas);
}

double max(double a, double b)
{
	if (a > b)
		return a;
	else
		return b;
}

double absolu(double a)
{
	if (a > 0)
		return a;
	else
		return -a;
}

void ecritureLigneSVG(FILE *fichier, double x2, double y2)
{
	switch (color)
	{
	case 1:
		fprintf(fichier, "<line x1=\"%f\" x2=\"%f\" y1=\"%f\" y2=\"%f\" style=\"stroke:rgb(255,0,0);stroke-width:1\" />\n", xA, x2, yA, y2);
		break;
	case 2:
		fprintf(fichier, "<line x1=\"%f\" x2=\"%f\" y1=\"%f\" y2=\"%f\" style=\"stroke:rgb(0,255,0);stroke-width:1\" />\n", xA, x2, yA, y2);
		break;
	case 3:
		fprintf(fichier, "<line x1=\"%f\" x2=\"%f\" y1=\"%f\" y2=\"%f\" style=\"stroke:rgb(0,0,255);stroke-width:1\" />\n", xA, x2, yA, y2);
		break;
	case 4:
		fprintf(fichier, "<line x1=\"%f\" x2=\"%f\" y1=\"%f\" y2=\"%f\" style=\"stroke:rgb(0,0,0);stroke-width:1\" />\n", xA, x2, yA, y2);
		break;
	default:
		fprintf(fichier, "<line x1=\"%f\" x2=\"%f\" y1=\"%f\" y2=\"%f\" style=\"stroke:#%X;stroke-width:1\" />\n", xA, x2, yA, y2, color);
		break;
	}
}

void ecritureEtoileSVG(FILE *fichier, double valNoeudDouble)
{
	double x2, y2;
	x2 = xA;
	y2 = yA;
	ecritureLigneSVG(fichier, x2 + valNoeudDouble, y2);
	x2 = x2 + valNoeudDouble;
	xA = x2;
	yA = y2;

	ecritureLigneSVG(fichier, x2 + valNoeudDouble * cos((double)-72 * pi / 180), y2 + valNoeudDouble * sin((double)-72 * pi / 180));
	x2 = x2 + valNoeudDouble * cos((double)(-72) * pi / 180);
	y2 = y2 + valNoeudDouble * sin((double)-72 * pi / 180);
	xA = x2;
	yA = y2;

	ecritureLigneSVG(fichier, x2 + valNoeudDouble * cos((double)72 * pi / 180), y2 + valNoeudDouble * sin((double)72 * pi / 180));
	x2 = x2 + valNoeudDouble * cos((double)(72) * pi / 180);
	y2 = y2 + valNoeudDouble * sin((double)72 * pi / 180);
	xA = x2;
	yA = y2;

	ecritureLigneSVG(fichier, x2 + valNoeudDouble, y2);
	x2 = x2 + valNoeudDouble;
	xA = x2;
	yA = y2;

	ecritureLigneSVG(fichier, x2 + valNoeudDouble * cos((double)144 * pi / 180), y2 + valNoeudDouble * sin((double)144 * pi / 180));
	x2 = x2 + valNoeudDouble * cos((double)(144) * pi / 180);
	y2 = y2 + valNoeudDouble * sin((double)144 * pi / 180);
	xA = x2;
	yA = y2;

	ecritureLigneSVG(fichier, x2 + valNoeudDouble * cos((double)72 * pi / 180), y2 + valNoeudDouble * sin((double)72 * pi / 180));
	x2 = x2 + valNoeudDouble * cos((double)(72) * pi / 180);
	y2 = y2 + valNoeudDouble * sin((double)72 * pi / 180);
	xA = x2;
	yA = y2;

	ecritureLigneSVG(fichier, x2 + valNoeudDouble * cos((double)-144 * pi / 180), y2 + valNoeudDouble * sin((double)-144 * pi / 180));
	x2 = x2 + valNoeudDouble * cos((double)(-144) * pi / 180);
	y2 = y2 + valNoeudDouble * sin((double)-144 * pi / 180);
	xA = x2;
	yA = y2;

	ecritureLigneSVG(fichier, x2 + valNoeudDouble * cos((double)144 * pi / 180), y2 + valNoeudDouble * sin((double)144 * pi / 180));
	x2 = x2 + valNoeudDouble * cos((double)(144) * pi / 180);
	y2 = y2 + valNoeudDouble * sin((double)144 * pi / 180);
	xA = x2;
	yA = y2;

	ecritureLigneSVG(fichier, x2 + valNoeudDouble * cos((double)-72 * pi / 180), y2 + valNoeudDouble * sin((double)-72 * pi / 180));
	x2 = x2 + valNoeudDouble * cos((double)(-72) * pi / 180);
	y2 = y2 + valNoeudDouble * sin((double)-72 * pi / 180);
	xA = x2;
	yA = y2;

	ecritureLigneSVG(fichier, x2 + valNoeudDouble * cos((double)-144 * pi / 180), y2 + valNoeudDouble * sin((double)-144 * pi / 180));
	x2 = x2 + valNoeudDouble * cos((double)(-144) * pi / 180);
	y2 = y2 + valNoeudDouble * sin((double)-144 * pi / 180);
	xA = x2;
	yA = y2;
}

void ecritureCarreSVG(FILE *fichier, double valNoeud)
{
	switch (color)
	{
	case 1:
		fprintf(fichier, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\" fill:none; stroke:rgb(255,0,0)\" />\n", xA, yA, valNoeud, valNoeud);
		break;
	case 2:
		fprintf(fichier, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\" fill:none; stroke:rgb(0,255,0)\" />\n", xA, yA, valNoeud, valNoeud);
		break;
	case 3:
		fprintf(fichier, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\" fill:none; stroke:rgb(0,0,255)\" />\n", xA, yA, valNoeud, valNoeud);
		break;
	case 4:
		fprintf(fichier, "<<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\" fill:none; stroke:rgb(0,0,0)\" />\n", xA, yA, valNoeud, valNoeud);
		break;
	default:
		fprintf(fichier, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\" fill:none; stroke:#%X\" />\n", xA, yA, valNoeud, valNoeud, color);
		break;
	}
}
