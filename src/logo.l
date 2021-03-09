%{
#include "MyProg.h"
#include "logo.tab.h"
%}

%%

[1-9][0-9]*|0 	{ yylval.val=atoi(yytext); return VALUE;}
\[        		{return '[';}
\]        		{return ']';}
"REPEAT"        { return REPEAT;}
"IF"            { return IF;}
"ELSE"          { return ELSE;}
"FORWARD"       { return FORWARD;}
"RIGHT"        	{ return RIGHT;}
"LEFT"        	{ return LEFT;}
"BLUE"			{ return BLUE;}
"GREEN"			{ return GREEN;}
"RED"			{ return RED;}
"TRANSPARENT"	{ return TRANSPARENT;}
"BLACK"			{ return BLACK;}
"SQUARE"		{ return SQUARE;}
"COLOR"			{return COLOR;}
"STAR"			{return STAR;}
"0x"[1-9a-fA-F][0-9a-fA-F]*	{yylval.val=strtol(yytext,NULL,0); return HEXA;}
"USE FONCTION"	{return USEFONCTION;}
"DEFINE FONCTION"	{return DEFFONCTION;}
\t				{ /* ignorer */ }
\n				{ /* ignorer */ }
\ 				{ /* ignorer */ }

%%
