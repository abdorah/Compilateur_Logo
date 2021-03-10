# Compilateur Logo
Exemple d'un compilateur du language de programmation Logo pour le dessin des figures destiné aux les enfants.
___

### __Objectif du projet :__
Le but de ce projet est de développer un compilateur de langage LOGO en C.

### __Introduction :__
Le langage de programmation LOGO a pour but d'améliorer chez les enfants leur manière de penser et d'aborder la résolution de problèmes. Matérialisé sous la forme d'un petit robot, la Tortue Logo, ce langage est utilisé dans la résolution de problèmes. Le langage de programmation Logo permet de déplacer cette « tortue géométrique », qui est un stylo représenté sous la forme d’une tortue que les enfants peuvent bouger ou dessiner sur l’écran.

### __Unités lexicales du langage :__
```

* Mots clés = { IF,
                ELSE,
                REPEAT,
                FORWARD,
                LEFT,
                RIGHT,
                COLOR,
                DEFINE,
                USE,
                FONCTION,
                TRANSPARENT,
                RED,
                GREEN,
                BLACK,
                BLUE}
* Symboles spéciaux = {[,]}
* Opérateurs = {+,-,*,/}
```
### __Grammaire du langage :__


```
Soit  G = <T,NT,S,P> la grammaire de notre langage LOGO,les règles de productions sont les suivantes:

<START> ::= <PROGRAM>

<PROGRAM> ::= <INSTRUCTION>
            | <PROGRAM> <INSTRUCTION>

<INSTRUCTION> ::= <FORWARD> <EXPRESSION>
                | <LEFT> <EXPRESSION>
                | <RIGHT> <EXPRESSION>
                | <REPEAT> <EXPRESSION> '[' <PROGRAM> ']'
                | <IF> <EXPRESSION> '[' <PROGRAM> ']' <BLOCK>
                | <DEFFONCTION> <EXPRESSION> '[' <PROGRAM> ']'
                | <RED>
                | <GREEN>
                | <BLUE>
                | <TRANSPARENT>
                | <BLACK>
                | <COLOR>
                | <USEFONCTION> <EXPRESSION>
                

<BLOCK> ::= <ELSE> '[' <PROGRAM> ']'
            | <empty>

<EXPRESSION> ::= <EXPRESSION> '+' <TERM>
                | <EXPRESSION> '-' <TERM>
                | <EXPRESSION> '*' <TERM>
                | <EXPRESSION> '/' <TERM>
                | TERM

<TERM> ::= <TERM> '*' <FACTOR>
        | <TERM> '/' <FACTOR>
        | <FACTOR>

<FACTOR> ::= <VALUE>
            | '-' <FACTOR>
            | '(' <EXPRESSION> ')'

```




## **Structure du projet**

>Le projet suit la structure suivant:

| Dossier / Fichier | Rôle                                                         |
| ----------------- | ------------------------------------------------------------ |
| Makefile          | ce fichier contient les commandes de make permettant de générer les executables et les dessins |
| parser.y            | code d'analyseur syntaxique et sémantique                    |
| scanner.l            | code d'analyseur lexical                                     |
| semantic.c    | des fonctions sémantiques                                         |
| semantic.h       | les structures et les fonctions utilisés dans la partie sémantique |
| test           | un ensemble de tests                                           |