/*--------------------------------------------------------         
                  DEFINITIONS
--------------------------------------------------------*/
%{
#include <stdio.h>
#include <stdlib.h> 
#include "semantic.h"

int yywrap(){
  return 1;
}

int yyerror()
{
  printf("\n syntax error !\n");
  exit(1);
}

%}   

// symbole terminaux
%token   FORWARD RIGHT LEFT REPEAT IF ELSE VALUE BLUE GREEN RED TRANSPARENT BLACK COLOR HEXA DEFFONCTION USEFONCTION

//type de yylval
%union {
    NODE* NODE_TYPE;
    int val;
 };

//type des  symboles
%type <NODE_TYPE> FORWARD RIGHT LEFT REPEAT IF ELSE BLOCK BLUE GREEN RED TRANSPARENT BLACK COLOR DEFFONCTION USEFONCTION
%type <NODE_TYPE> PROG INST 
%type  <val> VALUE HEXA


%%
/*--------------------------------------------------------         
                  GRAMMAIRE ANNOTEE
--------------------------------------------------------*/

FILE : PROG
       {
	 root=$1;
	 YYACCEPT;
       }

PROG : INST
        {
	  $$=$1;
	}
  |    PROG INST
        {
	  $$=append_node($2,$1);  //on ajoute l'instruction à la fin du programme
	}
  
  
INST : FORWARD VALUE
        {
	  $$=create_node(FORWARD_TOKEN,$2,NULL);
	}
  |    LEFT VALUE
        {
	  $$=create_node(LEFT_TOKEN,$2,NULL);
	}
  |    RIGHT VALUE
       {
	 $$=create_node(RIGHT_TOKEN,$2,NULL);
    }
  |	   REPEAT VALUE '[' PROG ']'
		{
		NODE* rep=create_node(REPEATc,$2,NULL);
		$$=append_node_repeat($4, rep);
	}
  |	   IF VALUE '[' PROG ']' BLOCK
		{
		NODE* ift=create_node(IF_TOKEN,$2,NULL);
		$$=NULL;
		$$=append_node_if($4, ift);
		$$=append_node($6,$$);
	}
	
  |	   DEFFONCTION VALUE '[' PROG ']'
		{
		NODE* def=create_node(DEFFONCTION_TOKEN,$2,NULL);
		$$=append_node_repeat($4, def);
	}
  |		RED
		{
		$$=create_node(RED_TOKEN,0,NULL);
	}
  |		GREEN
		{
		$$=create_node(GREEN_TOKEN,0,NULL);
	}
  |		BLUE
		{
		$$=create_node(BLUE_TOKEN,0,NULL);
	}
  |		TRANSPARENT
		{
		$$=create_node(TRANSPARENT_TOKEN,0,NULL);
	}
  |		BLACK
		{
		$$=create_node(BLACK_TOKEN,0,NULL);
	}
  |		COLOR HEXA
		{
		$$=create_node(COLOR_TOKEN,$2,NULL);
	}
  |		USEFONCTION VALUE
		{
		$$=create_node(USEFONCTION_TOKEN,$2,NULL);
	}

BLOCK:
  ELSE '[' PROG ']' {
	NODE* elst=create_node(ELSE_TOKEN,0,$3);
	$$=NULL;
	$$=append_node_if($$, elst);
  }
  | %empty {
	$$=NULL;
    printf("\n");
  }

%%
/*--------------------------------------------------------         
                  FONCTIONS MAIN
--------------------------------------------------------*/

int main(){

	yyparse();
	int a=0;
	print_node(root, &a); 
	draw(root);
	free_node(&root);
	return 0;
}
