# Compilateur Logo
### **Contributeurs :**
Ce projet a été réalisé sous la contribution de :
  
  * [Ayoub HMADOUCH ](https://github.com/AyoubHmadouch)
  * [Abdessamad EL HAFI](https://github.com/abdoelhafi)
  * [Abderahmane KOTBI](https://github.com/abdorah)
  * [Jaouhar DERROUICH](https://github.com/jaouharder)
  * [Mohammed OUTALLEB](https://github.com/mohammedouttaleb)
  
___



### __Objectif du projet :__
Le but de ce projet est de développer un compilateur de langage LOGO en C.Ce projet a pour but principal d'aider les enfants dans l'apprentissage des différentes figures.

### __Introduction :__
Le langage de programmation LOGO a pour but d'améliorer chez les enfants leur manière de penser et d'aborder la résolution de problèmes. Matérialisé sous la forme d'un petit robot, la Tortue Logo, ce langage est utilisé dans la résolution de problèmes. Le langage de programmation Logo permet de déplacer cette « tortue géométrique », qui est un stylo représenté sous la forme d’une tortue que les enfants peuvent bouger ou dessiner sur l’écran.

___
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
___
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



___
### **Structure du projet**

>Le projet suit la structure suivant:

| Dossier / Fichier | Rôle                                                         |
| ----------------- | ------------------------------------------------------------ |
| Makefile          | ce fichier contient les commandes de make permettant de générer les executables et les dessins |
| parser.y            | code d'analyseur syntaxique et sémantique                    |
| scanner.l            | code d'analyseur lexical                                     |
| semantic.c    | des fonctions sémantiques                                         |
| semantic.h       | les structures et les fonctions utilisés dans la partie sémantique |
| test           | un ensemble de tests                                           |

___
### **Exécution du projet**
```
Pour compiler le projet avec l’exemple de code logo test.logo, il faut juste utiliser la commade : 
        > cd source
        > make draw 
```

### **Outils développement**
* FLEX
* BISON
* MAKE
* GNU GCC

