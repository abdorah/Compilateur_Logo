/*--------------------------------------------------------         
                  DEFINITIONS
--------------------------------------------------------*/
%{
#include <stdio.h>
#include <stdlib.h> 
#include "MyProg.h"

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
%token   FORWARD RIGHT LEFT REPEAT IF VALUE BLUE GREEN RED TRANSPARENT BLACK SQUARE COLOR HEXA STAR DEFFONCTION USEFONCTION

//type de yylval
%union {
    NODE* NODE_TYPE;
    int val;
 };

//type des  symboles
%type <NODE_TYPE> FORWARD RIGHT LEFT REPEAT IF BLUE GREEN RED TRANSPARENT BLACK SQUARE COLOR STAR DEFFONCTION USEFONCTION
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
	  $$=addNodeFin($2,$1);  //on ajoute l'instruction à la fin du programme
	}
  
  
INST : FORWARD VALUE
        {
	  $$=newNode(FORWARDc,$2,NULL);
	}
  |    LEFT VALUE
        {
	  $$=newNode(LEFTc,$2,NULL);
	}
  |    RIGHT VALUE
       {
	 $$=newNode(RIGHTc,$2,NULL);
    }
  |	   REPEAT VALUE '[' PROG ']'
		{
		NODE* rep=newNode(REPEATc,$2,NULL);
		$$=addNodeFinRepeat($4, rep);
	}
  |	   IF VALUE '[' PROG ']'
		{
		NODE* ift=newNode(IFc,$2,NULL);
		$$=addNodeFinIF($4, ift);
	}
	
  |	   DEFFONCTION VALUE '[' PROG ']'
		{
		NODE* def=newNode(DEFFONCTIONc,$2,NULL);
		$$=addNodeFinRepeat($4, def);
	}
  |		RED
		{
		$$=newNode(REDc,0,NULL);
	}
  |		GREEN
		{
		$$=newNode(GREENc,0,NULL);
	}
  |		BLUE
		{
		$$=newNode(BLUEc,0,NULL);
	}
  |		TRANSPARENT
		{
		$$=newNode(TRANSPARENTc,0,NULL);
	}
  |		BLACK
		{
		$$=newNode(BLACKc,0,NULL);
	}
  |		SQUARE VALUE
		{
		$$=newNode(SQUAREc,$2,NULL);
	}
  |		COLOR HEXA
		{
		$$=newNode(COLORc,$2,NULL);
	}
  |		STAR VALUE
		{
		$$=newNode(STARc,$2,NULL);
	}
  |		USEFONCTION VALUE
		{
		$$=newNode(USEFONCTIONc,$2,NULL);
	}

%%
/*--------------------------------------------------------         
                  FONCTIONS MAIN
--------------------------------------------------------*/

int main(){

	yyparse();
	int a=0;
	affichageNode(root, &a); 
	generationSVG(root);
	detruitNode(&root);
	return 0;
}
