//
// Created by jcl on 07/12/2021.
//

#include <string.h>
#include <stdio.h>
#include "operatorsTranslations.h"



int add(struct assemblerInput opInput, char *res) {
    char special[100] = "000000";
    char zero[100] = "00000";
    char opcode[100] = "100000";
    char p1[100];
    char p2[100];
    char p3[100];
    conversionDecimalBinaire(opInput.p1, p1, 5);
    printf("p1 : %s\n",p1);
    conversionDecimalBinaire(opInput.p2, p2, 5);
    printf("p2 : %s\n",p2);
    conversionDecimalBinaire(opInput.p3, p3, 5);
    printf("p3 : %s\n",p3);
    strcat(res, special);
    strcat(res, p2);
    strcat(res, p3);
    strcat(res, p1);
    strcat(res, zero);
    strcat(res, opcode);
    binaryToHex(res, opInput);
    return 0;
}

int addi(struct assemblerInput opInput, char res[])
{
    char opcode[100] = "001000";
    char p1[100];
    char p2[100];
    char p3[100];
    conversionDecimalBinaire(opInput.p1, p1, 5);
    printf("p1 : %s\n",p1);
    conversionDecimalBinaire(opInput.p2, p2, 5);
    printf("p2 : %s\n",p2);
    conversionDecimalBinaire(opInput.p3, p3, 16);
    printf("p3 : %s\n",p3);
    strcat(res, opcode);
    strcat(res, p2);
    strcat(res, p1);
    strcat(res, p3);
    return binaryToHex(res, opInput);
}

int and(struct assemblerInput opInput, char res[])
{
   char special[100] = "000000";
   char zero[100] = "00000";
   char opcode[100] = "100100";
   char p1[100];
   char p2[100];
   char p3[100];

   conversionDecimalBinaire(opInput.p1, p1, 5);
   printf("p1 : %s\n",p1);
   conversionDecimalBinaire(opInput.p2, p2, 5);
   printf("p2 : %s\n",p2);
   conversionDecimalBinaire(opInput.p3, p3, 5);
   printf("p3 : %s\n",p3);
   strcat(res, special);
   strcat(res, p2);
   strcat(res, p1);
   strcat(res, p3);
   strcat(res, zero);
   strcat(res, opcode);
   return binaryToHex(res, opInput);
}

int beq(struct assemblerInput opInput, char res[])
{
   char opcode[100] = "000100";
   char p1[100];
   char p2[100];
   char p3[100];

   conversionDecimalBinaire(opInput.p1, p1, 5);
   printf("p1 : %s\n",p1);
   conversionDecimalBinaire(opInput.p2, p2, 5);
   printf("p2 : %s\n",p2);
   conversionDecimalBinaire(opInput.p3, p3, 16);
   printf("p3 : %s\n",p3);
   strcat(res, opcode);
   strcat(res, p1);
   strcat(res, p2);
   strcat(res, p3);
   return binaryToHex(res, opInput);
}

int bgtz(struct assemblerInput opInput, char res[])
{
   char opcode[100] = "000111";
   char zero[100] = "00000";
   char p1[100];
   char p2[100];

   conversionDecimalBinaire(opInput.p1, p1, 5);
   printf("p1 : %s\n",p1);
   conversionDecimalBinaire(opInput.p2, p2, 16);
   printf("p2 : %s\n",p2);
   strcat(res, opcode);
   strcat(res, p1);
   strcat(res, zero);
   strcat(res, p2);
   return binaryToHex(res, opInput);
}

int blez(struct assemblerInput opInput, char res[])
{
   char opcode[100] = "000110";
   char zero[100] = "00000";
   char p1[100];
   char p2[100];

   conversionDecimalBinaire(opInput.p1, p1, 5);
   printf("p1 : %s\n",p1);
   conversionDecimalBinaire(opInput.p2, p2, 16);
   printf("p2 : %s\n",p2);
   strcat(res, opcode);
   strcat(res, p1);
   strcat(res, zero);
   strcat(res, p2);
   return binaryToHex(res, opInput);
}

int bne(struct assemblerInput opInput, char res[])
{
   char opcode[100] = "000101";
   char p1[100];
   char p2[100];
   char p3[100];

   conversionDecimalBinaire(opInput.p1, p1, 5);
   printf("p1 : %s\n",p1);
   conversionDecimalBinaire(opInput.p2, p2, 5);
   printf("p2 : %s\n",p2);
   conversionDecimalBinaire(opInput.p3, p3, 16);
   printf("p3 : %s\n",p3);
   strcat(res, opcode);
   strcat(res, p1);
   strcat(res, p2);
   strcat(res, p3);
   return binaryToHex(res, opInput);
}

int div(struct assemblerInput opInput, char res[])
{
   char special[100] = "000000";
   char opcode[100] = "011010";
   char zero[100] = "0000000000";
   char p1[100];
   char p2[100];

   conversionDecimalBinaire(opInput.p1, p1, 5);
   printf("p1 : %s\n",p1);
   conversionDecimalBinaire(opInput.p2, p2, 5);
   printf("p2 : %s\n",p2);
   strcat(res, special);
   strcat(res, p1);
   strcat(res, p2);
   strcat(res, zero);
   strcat(res, opcode);
   return binaryToHex(res, opInput);
}

int j(struct assemblerInput opInput, char res[])
{
   //TODO Formatspécial à reprendre
   char opcode[100] = "000010";
   char p1[100];
   char p2[100];
   char p3[100];

   conversionDecimalBinaire(opInput.p1, p1, 5);
   printf("p1 : %s\n",p1);
   conversionDecimalBinaire(opInput.p2, p2, 5);
   printf("p2 : %s\n",p2);
   conversionDecimalBinaire(opInput.p3, p3, 16);
   printf("p3 : %s\n",p3);
   strcat(res, opcode);
   strcat(res, p2);
   strcat(res, p1);
   strcat(res, p3);
   return binaryToHex(res, opInput);
}

int jal(struct assemblerInput opInput, char res[], struct index *indexs) {
    char opcode[100] = "000011";
    char p1[100];

    //recherche de l'indexe du label
    int i=0;
    while (indexs[i].position != -1){
        if (strcmp(opInput.p1, indexs[i].name) == 0) {
            conversionDecimalBinaire(indexs[i].position, p1, 16);  //TODO continue
        }
        i++;
    }

   printf("p1 : %s\n",p1);
   strcat(res, opcode);
   strcat(res, p1);
   return binaryToHex(res, opInput);
}

int jr(struct assemblerInput opInput, char res[])
{
   char opcode[100] = "001000";
   char p1[100];
   char p2[100];
   char p3[100];

   conversionDecimalBinaire(opInput.p1, p1, 5);
   printf("p1 : %s\n",p1);
   conversionDecimalBinaire(opInput.p2, p2, 5);
   printf("p2 : %s\n",p2);
   conversionDecimalBinaire(opInput.p3, p3, 16);
   printf("p3 : %s\n",p3);
   strcat(res, opcode);
   strcat(res, p2);
   strcat(res, p1);
   strcat(res, p3);
   return binaryToHex(res, opInput);
}

int lui(struct assemblerInput opInput, char res[])
{
   char opcode[100] = "001111";
   char p1[100];
   char p2[100];
   char p3[100];

   conversionDecimalBinaire(opInput.p1, p1, 5);
   printf("p1 : %s\n",p1);
   conversionDecimalBinaire(opInput.p2, p2, 5);
   printf("p2 : %s\n",p2);
   conversionDecimalBinaire(opInput.p3, p3, 16);
   printf("p3 : %s\n",p3);
   strcat(res, opcode);
   strcat(res, p2);
   strcat(res, p1);
   strcat(res, p3);
   return binaryToHex(res, opInput);
}

int lw(struct assemblerInput opInput, char res[])
{
   char opcode[100] = "100011";
   char p1[100];
   char p2[100];
   char p3[100];

   conversionDecimalBinaire(opInput.p1, p1, 5);
   printf("p1 : %s\n",p1);
   conversionDecimalBinaire(opInput.p2, p2, 5);
   printf("p2 : %s\n",p2);
   conversionDecimalBinaire(opInput.p3, p3, 16);
   printf("p3 : %s\n",p3);
   strcat(res, opcode);
   strcat(res, p2);
   strcat(res, p1);
   strcat(res, p3);
   return binaryToHex(res, opInput);
}

int mfhi(struct assemblerInput opInput, char res[])
{
   char opcode[100] = "010000";
   char p1[100];
   char p2[100];
   char p3[100];

   conversionDecimalBinaire(opInput.p1, p1, 5);
   printf("p1 : %s\n",p1);
   conversionDecimalBinaire(opInput.p2, p2, 5);
   printf("p2 : %s\n",p2);
   conversionDecimalBinaire(opInput.p3, p3, 16);
   printf("p3 : %s\n",p3);
   strcat(res, opcode);
   strcat(res, p2);
   strcat(res, p1);
   strcat(res, p3);
   return binaryToHex(res, opInput);
}

int mult(struct assemblerInput opInput, char res[])
{
   char opcode[100] = "011000";
   char p1[100];
   char p2[100];
   char p3[100];

   conversionDecimalBinaire(opInput.p1, p1, 5);
   printf("p1 : %s\n",p1);
   conversionDecimalBinaire(opInput.p2, p2, 5);
   printf("p2 : %s\n",p2);
   conversionDecimalBinaire(opInput.p3, p3, 16);
   printf("p3 : %s\n",p3);
   strcat(res, opcode);
   strcat(res, p2);
   strcat(res, p1);
   strcat(res, p3);
   return binaryToHex(res, opInput);
}

int mflo(struct assemblerInput opInput, char res[])
{
   char special[100] = "000000";
   char zero1[100] = "0000000000"; //TODO c'est bon comme ça? Regarde la pdf
   char zero2[100] = "00000";
   char opcode[100] = "100000";
   char p1[100];

   conversionDecimalBinaire(opInput.p1, p1, 5);
   printf("p1 : %s\n",p1);
   strcat(res, special);
   strcat(res, zero1);
   strcat(res, p1);
   strcat(res, zero2);
   strcat(res, opcode);
   return binaryToHex(res, opInput);
}

int or(struct assemblerInput opInput, char res[])
{
   char opcode[100] = "100101";
   char p1[100];
   char p2[100];
   char p3[100];

   conversionDecimalBinaire(opInput.p1, p1, 5);
   printf("p1 : %s\n",p1);
   conversionDecimalBinaire(opInput.p2, p2, 5);
   printf("p2 : %s\n",p2);
   conversionDecimalBinaire(opInput.p3, p3, 16);
   printf("p3 : %s\n",p3);
   strcat(res, opcode);
   strcat(res, p2);
   strcat(res, p1);
   strcat(res, p3);
   return binaryToHex(res, opInput);
}


//TODO JAL


//TODO LW


/*

int nop(struct assemblerInput opInput, char res[]
   char special[100] = "000000";
   char zero1[100] = "00000"
   char zero2[100] = "00000"
   char zero3[100] = "00000"
   char zero4[100] = "00000"

   strcat(res, special);
   strcat(res, zero1);
   strcat(res, zero2);
   strcat(res, zero3);
   strcat(res, zero4);
   strcat(res, opcode);

   return binaryToHex(res, opInput);
}

int sll(struct assemblerInput opInput, char res[])
   char p1[100];
   char p2[100];
   char p3[100];

   conversionDecimalBinaire(opInput.p1, p1, 5);
   printf("p1 : %s\n",p1);
   conversionDecimalBinaire(opInput.p2, p2, 5);
   printf("p2 : %s\n",p2);
   conversionDecimalBinaire(opInput.p3, p3, 16);
   printf("p3 : %s\n",p3);
   strcat(res, opcode);
   strcat(res, p2);
   strcat(res, p1);
   strcat(res, p3);
   return binaryToHex(res, opInput);
}

int rotr(struct assemblerInput opInput, char res[])
{
   char special[100] = "000000";
   char zero[100] = "0000";
   char p1[100];
   char p2[100];
   char p3[100];
   conversionDecimalBinaire(opInput.p1, p1, 5);
   printf("p1 : %s\n",p1);
   conversionDecimalBinaire(opInput.p2, p2, 5);
   printf("p2 : %s\n",p2);
   conversionDecimalBinaire(opInput.p3, p3, 5);
   printf("p3 : %s\n",p3);
   strcat(res, special);
   strcat(res, zero);
   strcat(res, p2);
   strcat(res, p1);
   strcat(res, p3);
   strcat(res, opcode);
   return binaryToHex(res, opInput);
}

int srl(struct assemblerInput opInput, char res[])
{
   char opcode[100] = "101010";
   char p1[100];
   char p2[100];
   char p3[100];

   conversionDecimalBinaire(opInput.p1, p1, 5);
   printf("p1 : %s\n",p1);
   conversionDecimalBinaire(opInput.p2, p2, 5);
   printf("p2 : %s\n",p2);
   conversionDecimalBinaire(opInput.p3, p3, 16);
   printf("p3 : %s\n",p3);
   strcat(res, opcode);
   strcat(res, p2);
   strcat(res, p1);
   strcat(res, p3);
   return binaryToHex(res, opInput);
}

int slt(struct assemblerInput opInput, char res[])
{
   char opcode[100] = "101011";
   char special[100] = "000000";
   char zero[100] = "00000"
   char p1[100];
   char p2[100];
   char p3[100];
   conversionDecimalBinaire(opInput.p1, p1, 5);
   printf("p1 : %s\n",p1);
   conversionDecimalBinaire(opInput.p2, p2, 5);
   printf("p2 : %s\n",p2);
   conversionDecimalBinaire(opInput.p3, p3, 5);
   printf("p3 : %s\n",p3);
   strcat(res, special);
   strcat(res, p2);
   strcat(res, p3);
   strcat(res, p1);
   strcat(res, zero);
   strcat(res, opcode);
   return binaryToHex(res, opInput);
}

int sw(struct assemblerInput opInput, char res[])
{
   char special[100] = "000000";
   char zero[100] = "00000";
   char opcode[100] = "101011";
   char p1[100];
   char p2[100];
   char p3[100];
   conversionDecimalBinaire(opInput.p1, p1, 5);
   printf("p1 : %s\n",p1);
   conversionDecimalBinaire(opInput.p2, p2, 5);
   printf("p2 : %s\n",p2);
   conversionDecimalBinaire(opInput.p3, p3, 16);
   printf("p3 : %s\n",p3);
   strcat(res, opcode);
   strcat(res, p2);
   strcat(res, p1);
   strcat(res, p3);
   return binaryToHex(res, opInput);
}

int sub(struct assemblerInput opInput, char res[])
{
   char special[100] = "000000";
   char zero[100] = "00000";
   char opcode[100] = "100010";
   char p1[100];
   char p2[100];
   char p3[100];

   conversionDecimalBinaire(opInput.p1, p1, 5);
   printf("p1 : %s\n",p1);
   conversionDecimalBinaire(opInput.p2, p2, 5);
   printf("p2 : %s\n",p2);
   conversionDecimalBinaire(opInput.p3, p3, 5);
   printf("p3 : %s\n",p3);
   strcat(res, special);
   strcat(res, p2);
   strcat(res, p3);
   strcat(res, p1);
   strcat(res, zero);
   strcat(res, opcode);
   return binaryToHex(res, opInput);
}

int xor(struct assemblerInput opInput, char res[])
{
   char opcode[100] = "100110 ";
   char p1[100];
   char p2[100];
   char p3[100];

   conversionDecimalBinaire(opInput.p1, p1, 5);
   printf("p1 : %s\n",p1);
   conversionDecimalBinaire(opInput.p2, p2, 5);
   printf("p2 : %s\n",p2);
   conversionDecimalBinaire(opInput.p3, p3, 16);
   printf("p3 : %s\n",p3);
   strcat(res, opcode);
   strcat(res, p2);
   strcat(res, p1);
   strcat(res, p3);
   return binaryToHex(res, opInput);
}

int syscall(struct assemblerInput opInput, char res[])
{
   char opcode[100] = "001100"; //TODO A voir paramètres spéciaux
   char p1[100];
   char p2[100];
   char p3[100];

   conversionDecimalBinaire(opInput.p1, p1, 5);
   printf("p1 : %s\n",p1);
   conversionDecimalBinaire(opInput.p2, p2, 5);
   printf("p2 : %s\n",p2);
   conversionDecimalBinaire(opInput.p3, p3, 16);
   printf("p3 : %s\n",p3);
   strcat(res, opcode);
   strcat(res, p2);
   strcat(res, p1);
   strcat(res, p3);
   return binaryToHex(res, opInput);
}
*/