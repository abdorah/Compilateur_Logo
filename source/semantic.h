#include <stdio.h>
#include <stdlib.h>

enum token
{
	FORWARD_TOKEN,
	LEFT_TOKEN,
	RIGHT_TOKEN,
	REPEATc,
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

NODE *create_node(token instruction, int value, NODE *program);
NODE *append_node(NODE *pn1, NODE *pn2);
NODE *append_node_repeat(NODE *pn1, NODE *pn2);
NODE *append_node_if(NODE *pn1, NODE *pn2);
void print_node(NODE *pn, int *tab);
void free_node(NODE **n);
void draw(NODE *n);
void draw_line(FILE *file, NODE *n, NODE *start);
void update_svg(NODE *n, NODE *start, ACTION *value);
void show_struct(ACTION movment);
double max(double a, double b);
double absolute_value(double a);
void write_line(FILE *file, double x2, double y2);
