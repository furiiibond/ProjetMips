# ProjetMips
## Mode interactif

*“./emul-mips”* sans argument lance le programme en mode interactif, c'est-à-dire que l’utilisateur va entrer les instructions à exécuter une à une durant l’exécution.

Afin de quitter ce mode l’utilisateur doit appeler la commande *“exit”*.

Les labels et les boucles sont également disponibles via ce mode, ce qui l’a rendu particulièrement difficile à implémenter. Pour proposer cette fonctionnalité nous stockons les anciennes instructions tapées par l’utilisateur afin de les exécuter à nouveau dans le cadre d’un rebouclage 

## Mode non-interactif

Le mode non interactif est disponible via un appel de type 

`./emul-mips in1.s in1.hex in1.state`  

Les instructions sont alors lues par la fonction de lecture `readInput` présente dans le fichier “*filreIO.c”*

Dans le fichier en paramètre 1, ici in1.s.

Les instructions peuvent être de différents formats et avec un nombre variable de paramètres :

par exemple *addi $20,$20,10* fonctionne, mais peut aussi s’écrire *ADDI $20, $20, 10*.

Nous gérons ici en effet les espaces entre les paramètres ainsi que les majuscules et minuscules dans l’opérande.

Le résultat en hexadécimal de cette suite d’instructions est stoké dans le fichier passé en paramètre 2 ici in1.hex

La valeur des registres est enregistrée à la fin de l’exécution dans le fichier en troisième paramètre, ici in1.state. 

### Mode pas à pas 🐾

Avec un appel du type `emul-mips prog_filename <-pas>`  le mode pas à pas est activé. Le programme va alors afficher à chaque exécution d’une instruction la valeur des registres, mais aussi la valeur de la mémoire.

L’utilisateur va devoir appuyer sur une touche de son clavier pour passer à l’instruction suivante.

Le mode pas à pas est disponible via l’ajout du paramètre “-pas” en position 2.

```c
if (iterate) {
            showRegisterStates(registersState);
            showMemoryState(memoryState);
            printf("-----------------\n");
            printf("Instruction suivante %s %s,%s,%s \n", opInputs[pc].opp, opInputs[pc].p1, opInputs[pc].p2,
                   opInputs[pc].p3);
            printf("press a key\n");
            getchar();   // bloquage sur entré utilisateur
        }
```
