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

struct index {
    char name[100];
    int position;
};

int add(struct assemblerInput opInput, char res[]);

int addi(struct assemblerInput opInput, char res[]);

int and(struct assemblerInput opInput, char res[]);

int beq(struct assemblerInput opInput, char res[]);

int bgtz(struct assemblerInput opInput, char res[]);

int blez(struct assemblerInput opInput, char res[]);

int bne(struct assemblerInput opInput, char res[]);

int div(struct assemblerInput opInput, char res[]);

int j(struct assemblerInput opInput, char res[]);

int jal(struct assemblerInput opInput, char res[], struct index *indexs);

int jr(struct assemblerInput opInput, char res[]);

int lui(struct assemblerInput opInput, char res[]);

int lw(struct assemblerInput opInput, char res[]);

int mfhi(struct assemblerInput opInput, char res[]);

int mult(struct assemblerInput opInput, char res[]);

int mflo(struct assemblerInput opInput, char res[]);

int or(struct assemblerInput opInput, char res[]);

int nop(struct assemblerInput opInput, char res[]);

int sll(struct assemblerInput opInput, char res[]);

int rotr(struct assemblerInput opInput, char res[]);

int srl(struct assemblerInput opInput, char res[]);

int slt(struct assemblerInput opInput, char res[]);

int sw(struct assemblerInput opInput, char res[]);

int sub(struct assemblerInput opInput, char res[]);

int xor(struct assemblerInput opInput, char res[]);

int syscall(struct assemblerInput opInput, char res[]);

int hexaTranslat(struct assemblerInput *opInputs, int count, struct index *indexs);

#endif //MYOWN_OPERATORSTRANSLATIONS_H
