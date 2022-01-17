//
// Created by jcl on 16/12/2021.
//

#include "utilsAndConverters.h"
#include "operatorsTranslations.h"
#include <string.h>
#include <stdio.h>
#include "fileIO.h"
#include "registers.h"

int readInput(char *fileName, struct assemblerInput *opInputs, struct index *indexs) {
    int nbLine = 0;
    int nbIntruction = 0;
    int nbIndex = 0;
    FILE *myfile = fopen(fileName, "r");
    if (myfile == NULL) {
        printf("Cannot open file.\n");
        return 1;
    } else {
        //Check for number of line
        char ch;
        nbLine = 0;
        do {
            ch = fgetc(myfile);
            if (ch == '\n')
                nbLine++;
        } while (ch != EOF);
        rewind(myfile);

        char currentsParams[MAX_INPUT];
        for (int i = 0; i < nbLine; i++) {
            char opp[100];
            fscanf(myfile, "%s ", &opp);
            if (strstr(opp, ":")) {
                //index
                printf("indexe %s find at %d\n", opp, i);
                //remove ':'
                int len = strlen(opp);
                opp[len - 1] = 0;

                strcpy(indexs[nbIndex].name, opp);
                indexs[nbIndex].position = i;
                nbIndex++;
            } else {
                //operateur
                if (strcmp(opp, "NOP") != 0 && strcmp(opp, "SYSCALL") != 0) {  // ici les opperateur à 0 opperandes
                    //fscanf(myfile, "%s\n", &currentsParams);
                    fscanf(myfile, "%[^\n]*c", &currentsParams);
                }
                strcpy(opInputs[nbIntruction].opp, opp);
                printf("op %s\n", opInputs[nbIntruction].opp);

                //récupération des paramètres
                char delim[] = ",";
                removeSpaces(currentsParams);     // remove space from parametres
                char *ptr = strtok(currentsParams, delim);

                if (ptr != NULL) {
                    strcpy(opInputs[nbIntruction].p1, ptr);
                    ptr = strtok(NULL, delim);
                }
                if (ptr != NULL) {
                    strcpy(opInputs[nbIntruction].p2, ptr);
                    ptr = strtok(NULL, delim);
                }
                if (ptr != NULL) {
                    strcpy(opInputs[nbIntruction].p3, ptr);
                }
                nbIntruction++;
            }
        }
        indexs[nbIndex + 1].position = -1;  // indicateur de fin de tableau
        printf("Nombre d'instruction dans le fichier : %d\n", nbLine);
    }
    return nbIntruction;
}

int writeResults(char *fileName, struct assemblerInput *opInputs, int nbLine) {

    FILE *myfile = fopen(fileName, "w");

    if (myfile == NULL) {
        printf("Error!");
        return 1;
    }

    for (int i = 0; i < nbLine; i++) {
        fprintf(myfile, "%X\n", opInputs[i].hexa);
    }
    fclose(myfile);
    return 0;
}

void writeStateFile(char *fileName, int registerState[]) {
    FILE *fp;
    fp = fopen(fileName, "w");
    if (fp != NULL) {
        for (int i = 0; i < 32; ++i) {
            fprintf(fp, "$%02d:%d\n", i, readFromRegister(registerState, i));
        }
        fprintf(fp, "HI:%d\n", readFromRegister(registerState, HI_REGISTER));
        fprintf(fp, "LO:%d\n", readFromRegister(registerState, LO_REGISTER));
        fclose(fp);
    }
}