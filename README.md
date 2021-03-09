# Compilateur_Logo
Exemple d'u compilateur du language de programmation Logo pour les enfants.



## ***Réalisation du compilateur***

>Le projet suit la structure suivant:

| Dossier / Fichier | Rôle                                                         |
| ----------------- | ------------------------------------------------------------ |
| Makefile          | ce fichier contient les commandes de make permettants de générer les executables et les dessins |
| parser.y            | code d'analyseur syntaxique et sémantique                    |
| scanner.l            | code d'analyseur lexical                                     |
| semantic.c    | des fonctions utiles                                         |
| semantic.h       | les structures et les fonctions utilisés dans la partie sémantique |
| test           | un ensemble de tests                                           |