%{
#include <stdio.h>
#include <stdlib.h> 
#include "semantic.h"

int yywrap(){
  return 1;
}

int yyerror()
{
  printf("\n syntax error !");
  exit(1);
}

%}   

%token   FORWARD RIGHT LEFT REPEAT IF ELSE VALUE BLUE GREEN RED TRANSPARENT BLACK COLOR HEXA DEFFONCTION USEFONCTION


%union {
    NODE* NODE_TYPE;
    int val;
 };

%type <NODE_TYPE> FORWARD RIGHT LEFT REPEAT IF ELSE BLOCK BLUE GREEN RED TRANSPARENT BLACK COLOR DEFFONCTION USEFONCTION
%type <NODE_TYPE> PROGRAM INSTRUCTION 
%type  <val> EXPRESSION VALUE TERM FACTOR HEXA


%%

START : PROGRAM
{
    root = $1;
    YYACCEPT;
}

PROGRAM : INSTRUCTION
{
    $$ = $1;
}
| PROGRAM INSTRUCTION
{
    $$ = append_node($2, $1);
}

INSTRUCTION : FORWARD EXPRESSION
{
    $$ = create_node(FORWARD_TOKEN, $2, NULL);
}
| LEFT EXPRESSION
{
    $$ = create_node(LEFT_TOKEN, $2, NULL);
}
| RIGHT EXPRESSION
{
    $$ = create_node(RIGHT_TOKEN, $2, NULL);
}
| REPEAT EXPRESSION '[' PROGRAM ']'
{
    NODE *rep = create_node(REPEATc, $2, NULL);
    $$ = append_node_repeat($4, rep);
}
| IF EXPRESSION '[' PROGRAM ']' BLOCK
{
    NODE *ift = create_node(IF_TOKEN, $2, NULL);
    $$ = NULL;
    $$ = append_node_if($4, ift);
    $$ = append_node($6, $$);
}
| DEFFONCTION EXPRESSION '[' PROGRAM ']'
{
    NODE *def = create_node(DEFFONCTION_TOKEN, $2, NULL);
    $$ = append_node_repeat($4, def);
}
| RED
{
    $$ = create_node(RED_TOKEN, 0, NULL);
}
| GREEN
{
    $$ = create_node(GREEN_TOKEN, 0, NULL);
}
| BLUE
{
    $$ = create_node(BLUE_TOKEN, 0, NULL);
}
| TRANSPARENT
{
    $$ = create_node(TRANSPARENT_TOKEN, 0, NULL);
}
| BLACK
{
    $$ = create_node(BLACK_TOKEN, 0, NULL);
}
| COLOR HEXA
{
    $$ = create_node(COLOR_TOKEN, $2, NULL);
}
| USEFONCTION EXPRESSION
{
    $$ = create_node(USEFONCTION_TOKEN, $2, NULL);
}

BLOCK : ELSE '[' PROGRAM ']'
{
    NODE *elst = create_node(ELSE_TOKEN, 0, $3);
    $$ = NULL;
    $$ = append_node_if($$, elst);
}
| %empty
{
    $$ = NULL;
    printf("\n");
}

EXPRESSION : EXPRESSION '+' TERM
{
    $$ = $1 + $3;
}
| EXPRESSION '-' TERM
{
    $$ = $1 - $3;
}
| TERM
{
    $$ = $1;
}

TERM : TERM '*' FACTOR
{
    $$ = $1 * $3;
}
| TERM '/' FACTOR
{
    $$ = $1 / $3;
}
| FACTOR
{
    $$ = $1;
}

FACTOR : VALUE
{
    $$ = $1;
}
| '-' FACTOR
{
    $$ = -$2;
}
| '(' EXPRESSION ')'
{
    $$ = $2;
}

%%

int main(){

	yyparse();
	int a=0;
	print_node(root, &a); 
	draw(root);
	free_node(&root);
	return 0;
}
