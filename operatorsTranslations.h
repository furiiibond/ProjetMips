//
// Created by jcl on 07/12/2021.
//

#ifndef MYOWN_OPERATORSTRANSLATIONS_H
#define MYOWN_OPERATORSTRANSLATIONS_H

struct assemblerInput{ // structure décrivant une instruction assembleur. Ainci que sa valeur en hexadécimal traduite.
    char opp[100];
    char p1[5];
    char p2[5];
    char p3[5];
    int hexa;
};

struct index{
    char name[100];
    int position;
};

int add(struct assemblerInput opInput, char res[]);
int addi(struct assemblerInput opInput, char res[]);
#endif //MYOWN_OPERATORSTRANSLATIONS_H
