#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "semantic.h"

NODE *create_node(token instr, int value, NODE *sousProg)
{
	NODE *pn = (NODE *)malloc(sizeof(NODE));
	if (pn == NULL)
	{
		fprintf(stderr, "Problème de malloc: plus de mémoire\n");
	}
	pn->intstruction = instr;
	pn->value = value;
	pn->program = sousProg;
	return pn;
}

NODE *append_node(NODE *pn1, NODE *pn)
{
	if (pn == NULL)
	{
		pn1 = pn;
	}
	else
	{
		/*if(pn->next==NULL){
			pn->next=pn1;
			return pn;
		}*/
		NODE *cur = pn;
		while (cur->next != NULL)
		{
			cur = cur->next;
		}
		cur->next = pn1;
	}
	return pn;
}

NODE *append_node_repeat(NODE *pn1, NODE *pn2)
{
	if (pn2->intstruction == REPEATc || pn2->intstruction == DEFFONCTION_TOKEN)
	{
		if (pn2->program == NULL)
		{
			pn2->program = pn1;
		}
		else
		{
			NODE *cur = pn2->program;
			while (cur->next != NULL)
			{
				cur = cur->next;
			}
			cur->next = pn1;
		}
	}
	else
	{
		printf("Erreur: pas un addFinRepeat appelé sur un non repeat\n");
	}
	return pn2;
}

NODE *append_node_if(NODE *pn1, NODE *pn2)
{
	if (pn2->intstruction == IF_TOKEN || pn2->intstruction == DEFFONCTION_TOKEN || pn2->intstruction == ELSE_TOKEN)
	{
		//if (pn2->value)
		//{
			if (pn2->program == NULL)
			{
				pn2->program = pn1;
			}
			else
			{
				NODE *cur = pn2->program;
				while (cur->next != NULL)
				{
					cur = cur->next;
				}
				cur->next = pn1;
			}
		//}
		
	}
	else
	{
		printf("Erreur: pas un addFinRepeat appelé sur un non repeat\n");
	}
	return pn2;
}

void free_node(NODE **pn)
{
	if (*pn == NULL)
		return;
	free_node(&(**pn).next);
	free_node(&(**pn).program);
	free(*pn);
}

void print_node(NODE *pn, int *tab)
{
	if (pn == NULL)
		return;
	else
	{
		int i;
		int a = *tab;
		for (i = 1; i <= a; i++)
		{
			printf("\t");
		}
		switch (pn->intstruction)
		{
		case FORWARD_TOKEN:
			printf("FORWARD ");
			printf("%d", pn->value);
			break;
		case LEFT_TOKEN:
			printf("LEFT ");
			printf("%d", pn->value);
			break;
		case RIGHT_TOKEN:
			printf("RIGHT ");
			printf("%d", pn->value);
			break;
		case REPEATc:
			printf("REPEAT ");
			printf("%d", pn->value);
			break;
		case IF_TOKEN:
			printf("IF ");
			printf("%d", pn->value);
			break;
		case ELSE_TOKEN:
			printf("ESLE ");
			//printf("%d", pn->value);
			break;
		case BLUE_TOKEN:
			printf("BLUE ");
			break;
		case GREEN_TOKEN:
			printf("GREEN ");
			break;
		case RED_TOKEN:
			printf("RED ");
			break;
		case TRANSPARENT_TOKEN:
			printf("TRANSPARENT ");
			break;
		case BLACK_TOKEN:
			printf("BLACK ");
			break;
		case COLOR_TOKEN:
			printf("COLOR ");
			printf("#%X", pn->value);
			break;
		case DEFFONCTION_TOKEN:
			printf("DEFINE FONCTION ");
			printf("%d", pn->value);
			break;
		case USEFONCTION_TOKEN:
			printf("USE FONCTION ");
			printf("%d", pn->value);
			break;
		default:
			printf("Instruction inconnue");
			break;
		}
		if (pn->intstruction == REPEATc || pn->intstruction == IF_TOKEN || pn->intstruction == ELSE_TOKEN  ||  pn->intstruction == DEFFONCTION_TOKEN)
		{
			printf(" [\n");
			a = a + 1;
			print_node(pn->program, &a);
			a = a - 1;
			for (i = 1; i <= a; i++)
			{
				printf("\t");
			}
			printf("]");
		}

		printf("\n");
		print_node(pn->next, tab);
		return;
	}
}

void draw(NODE *n)
{
	if (n == NULL)
	{
		printf("Generation SVG sur un n nul\n");
	}

	FILE *dest = NULL;
	dest = fopen("dessin.svg", "w+");
	ACTION valuesMax;
	valuesMax.left = 0.0;
	valuesMax.right = 0.0;
	valuesMax.up = 0.0;
	valuesMax.down = 0.0;
	xo = 0; //xo et yo correspondent au milieu de la fenêtre: on cherche l'écartement maximal par rapport à ce milieu
	yo = 0;
	angle = 0;
	color = 4; //Noir par défaut
	update_svg(n, n, &valuesMax);
	double width = 2 * max(absolute_value(valuesMax.left), valuesMax.right) + 100.0;
	double height = 2 * max(absolute_value(valuesMax.up), valuesMax.down) + 100.0;
	fputs("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n", dest);
	fprintf(dest, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%f\" height=\"%f\">\n", width, height);

	xo = width / 2;
	yo = height / 2;
	angle = 0;
	draw_line(dest, n, n);

	fputs("</svg>", dest);
	fclose(dest);
}

void draw_line(FILE *file, NODE *n, NODE *start)
{
	if (n == NULL)
		return;
	if (n->intstruction == REPEATc)
	{
		int i;
		int a = n->value;
		for (i = 0; i < a; i++)
		{
			draw_line(file, n->program, start);
		}
	}
	else if (n->intstruction == IF_TOKEN)
	{
		int a = n->value;
		if (a)
		{
			draw_line(file, n->program, start);
		}
		if ((n->next->intstruction == ELSE_TOKEN) && !a)
		{
			draw_line(file, n->next->program, start);
		}
		
	}
	else
	{
		int valn = n->value;
		double valnDouble = (double)valn;
		double dx, dy;
		double x2, y2;
		NODE *parcours = start;
		switch (n->intstruction)
		{
		case RIGHT_TOKEN:
			angle = angle + valn;
			break;

		case LEFT_TOKEN:
			angle = angle - valn;
			break;

		case FORWARD_TOKEN:
			dx = (double)valn * cos((double)angle * pi / 180);
			dy = (double)valn * sin((double)angle * pi / 180);
			x2 = xo + dx;
			y2 = yo + dy;
			write_line(file, x2, y2);
			xo = x2;
			yo = y2;
			break;
		case TRANSPARENT_TOKEN:
			color = 0;
			break;

		case RED_TOKEN:
			color = 1;
			break;

		case GREEN_TOKEN:
			color = 2;
			break;

		case BLUE_TOKEN:
			color = 3;
			break;

		case BLACK_TOKEN:
			color = 4;
			break;
		case COLOR_TOKEN:
			color = valn;
			break;
		case USEFONCTION_TOKEN:
			while (parcours != NULL)
			{
				if (parcours->intstruction == DEFFONCTION_TOKEN && parcours->value == valn)
				{
					draw_line(file, parcours->program, start);
					break;
				}
				parcours = (parcours->next);
			}
			break;
		}
	}
	draw_line(file, n->next, start);
}

void update_svg(NODE *n, NODE *start, ACTION *value)
{
	if (n == NULL)
		return;
	if (n->intstruction == REPEATc)
	{
		int i;
		int a = n->value;
		for (i = 0; i < a; i++)
		{
			update_svg(n->program, start, value);
		}
	}
	else if (n->intstruction == IF_TOKEN)
	{

		int a = n->value;
		if (a)
		{
			update_svg(n->program, start, value);
		}
		if ((n->next->intstruction == ELSE_TOKEN) && !a)
		{
			update_svg(n->next->program, start, value);
		}
	}
	else
	{
		int valn = n->value;
		double valnDouble = (double)valn;
		double dx, dy;
		double x2, y2;
		NODE *parcours = start;
		switch (n->intstruction)
		{
		case RIGHT_TOKEN:
			angle = angle + valn;
			break;

		case LEFT_TOKEN:
			angle = angle - valn;
			break;
		case FORWARD_TOKEN:
			dx = valnDouble * cos((double)angle * pi / 180);
			dy = valnDouble * sin((double)angle * pi / 180);
			xo = xo + dx;
			yo = yo + dy;
			if (xo > value->right)
				value->right = xo;
			else if (xo < value->left)
				value->left = xo;

			if (yo > value->down)
				value->down = yo;
			else if (yo < value->up)
				value->up = yo;
			break;
		case USEFONCTION_TOKEN:
			while (parcours != NULL)
			{
				if (parcours->intstruction == DEFFONCTION_TOKEN && parcours->value == valn)
				{
					update_svg(parcours->program, start, value);
					break;
				}
				parcours = (parcours->next);
			}
			break;
		}
	}
	update_svg(n->next, start, value);
}

void show_struct(ACTION movment)
{
	printf("Right: %f, Left: %f, Up: %f, Down: %f\n", movment.right, movment.left, movment.up, movment.down);
}

double max(double a, double b)
{
	if (a > b)
		return a;
	else
		return b;
}

double absolute_value(double a)
{
	if (a > 0)
		return a;
	else
		return -a;
}

void write_line(FILE *file, double x2, double y2)
{
	switch (color)
	{
	case 1:
		fprintf(file, "<line x1=\"%f\" x2=\"%f\" y1=\"%f\" y2=\"%f\" style=\"stroke:rgb(255,0,0);stroke-width:1\" />\n", xo, x2, yo, y2);
		break;
	case 2:
		fprintf(file, "<line x1=\"%f\" x2=\"%f\" y1=\"%f\" y2=\"%f\" style=\"stroke:rgb(0,255,0);stroke-width:1\" />\n", xo, x2, yo, y2);
		break;
	case 3:
		fprintf(file, "<line x1=\"%f\" x2=\"%f\" y1=\"%f\" y2=\"%f\" style=\"stroke:rgb(0,0,255);stroke-width:1\" />\n", xo, x2, yo, y2);
		break;
	case 4:
		fprintf(file, "<line x1=\"%f\" x2=\"%f\" y1=\"%f\" y2=\"%f\" style=\"stroke:rgb(0,0,0);stroke-width:1\" />\n", xo, x2, yo, y2);
		break;
	default:
		fprintf(file, "<line x1=\"%f\" x2=\"%f\" y1=\"%f\" y2=\"%f\" style=\"stroke:#%X;stroke-width:1\" />\n", xo, x2, yo, y2, color);
		break;
	}
}
