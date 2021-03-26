#include <stdio.h>
#include <stdlib.h>

enum token
{
	FORWARD_TOKEN,
	LEFT_TOKEN,
	RIGHT_TOKEN,
	REPEAT_TOKEN,
	IF_TOKEN,
	ELSE_TOKEN,
	BLUE_TOKEN,
	GREEN_TOKEN,
	RED_TOKEN,
	TRANSPARENT_TOKEN,
	BLACK_TOKEN,
	COLOR_TOKEN,
	USEFONCTION_TOKEN,
	DEFFONCTION_TOKEN
};

typedef enum token token;

typedef struct node
{
	token intstruction;
	int value;
	struct node *program;
	struct node *next;
} NODE;

typedef NODE *INSTRUCTION;
typedef struct action
{
	double left;
	double right;
	double down;
	double up;
} ACTION;

static NODE *root;
static double pi = 3.1415926;
static double xo, yo;
static int angle, color;
//create the node
NODE *create_node(token instruction, int value, NODE *program);
//append the node to the linkedlist
NODE *append_node(NODE *pn1, NODE *pn2);
//append the node repeat to the linkedlist
NODE *append_node_repeat(NODE *pn1, NODE *pn2);
//append the node if to the linkedlist
NODE *append_node_if(NODE *pn1, NODE *pn2);
//print the node 
void print_node(NODE *pn, int *tab);
//free the memoire
void free_node(NODE **n);
void draw(NODE *n);
void draw_line(FILE *file, NODE *n, NODE *start);
void update_svg(NODE *n, NODE *start, ACTION *value);
double max(double a, double b);
double absolute_value(double a);
void write_line(FILE *file, double x2, double y2);
