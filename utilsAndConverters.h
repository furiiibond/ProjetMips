//
// Created by jcl on 08/12/2021.
//

#ifndef MYOWN_UTILSANDCONVERTERS_H
#define MYOWN_UTILSANDCONVERTERS_H

#define MAX_INPUT 500
#define MAX_INDEX 100

void intVersChaine(int num, char chaine[], int nbBit);

int processingParameter(char parameter[]);

int conversionDecimalBinaireInt(int valeur, char res[], int nbBit);

int conversionDecimalBinaire(char parameter[], char *res, int nbBit);

int conversionDecimalBinaireMayBeNegative(char parameter[], char *res, int nbBit, char *nextOp);

int decimalToHexa(char parameter[], char hexadecimalNumber[]);

int binaryToHexa(char parameter[], char hexadecimalNumber[]);

int binaryToHex(char inStr[], struct assemblerInput opInput);

int binaryToDec(char inStr[]);

int indirectWithDecline(char parameter[], char *offset, char *base);

#endif //MYOWN_UTILSANDCONVERTERS_H
