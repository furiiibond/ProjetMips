//
// Created by jcl on 08/12/2021.
//

#include "operatorsTranslations.h"
#include <string.h>
#include <stdio.h>
#include "utilsAndConverters.h"
#include <math.h>

//int vers tab de char
int nbDecimal(int value) {
    int nbDecimal = 0;
    if (value == 0) {
        nbDecimal = 1;
    }
    while (value > 0) {
        value = value / 10;
        nbDecimal++;
    }
    return nbDecimal;
}

int puissance(int x, int pow) {
    for (int i = 1; i < pow; i++) {
        x = x * 10;
    }
    return x;
}

void intVersChaine(int num, char chaine[], int nbBit) {
    int nbDec = nbDecimal(num);
    int n, i;
    int lastVal = 0;
    for (i = 0; i < nbDec; i++) {
        n = num / puissance(1, nbDec - i) - lastVal;
        lastVal = (n + lastVal) * 10;
        chaine[i] = n + 48;
    }
    for (; i < nbBit; ++i) {
        chaine[i + 1] = chaine[i];
        chaine[i] = '0';
    }
    chaine[i++] = 0;
}

int processingParameter(char parameter[]) {
    //traitement du parametre
    int count = strlen(parameter);
    if (parameter[0] == '$') {
        for (int i = 0; i < count; i++) {
            parameter[i] = parameter[i + 1];
        }
    }
    return 0;
}

int conversionDecimalBinaireInt(int valeur, char res[], int nbBit) {
    char tab[MAX_INPUT];
    int x = 0;
    int i = 0;
    int reste;
    int binaire = 0;
    int neg = 0;
    if (valeur < 0) {
        neg = 1;
        valeur = -valeur - 1;
    }
    while (valeur > 0) {
        reste = valeur % 2;//calcul le reste
        tab[x] = reste + 48;
        x++;
        valeur = valeur / 2;
    }
    while (x < nbBit) {
        tab[x] = '0';
        x++;
    }
    int j = x - 1;
    while (i != nbBit) {
        res[i] = tab[j];
        i++;
        j--;
    }
    res[x] = 0;
    if (neg == 1) {
        int k = 0;
        while (k < nbBit) {
            if (res[k] == '0') {
                res[k] = '1';
            } else {
                res[k] = '0';
            }
            k++;
        }
    }
    return neg;
}

int conversionDecimalBinaire(char parameter[], char *res, int nbBit) {
    int valeur;
    processingParameter(parameter);
    sscanf(parameter, "%d", &valeur);
    return conversionDecimalBinaireInt(valeur, res, nbBit);

}

int conversionDecimalBinaireMayBeNegative(char parameter[], char *res, int nbBit, char *nextOp) {
    int valeur;
    processingParameter(parameter);
    sscanf(parameter, "%d", &valeur);
    if (conversionDecimalBinaireInt(valeur, res, nbBit)) {
        //nombre négatif on increment l'operande suivente
        int nextOpValue = binaryToDec(nextOp);
        int len = strlen(nextOp);
        if (nextOpValue == 0) {
            nextOpValue = (pow(2, len - 1) - 1);
        } else {
            nextOpValue--;
        }
        conversionDecimalBinaireInt(nextOpValue, nextOp, len);
    }
    return 0;
}

int decimalToHexa(char parameter[], char hexadecimalNumber[]) {
    long int decimalNumber, quotient;
    int i = 0, temp;
    sscanf(parameter, "%ld", &decimalNumber);
    quotient = decimalNumber;
    if (quotient == 0) {
        hexadecimalNumber[i] = '0';
        i++;
    } else {
        while (quotient != 0) {
            temp = quotient % 16;
            //To convert integer into character
            if (temp < 10)
                temp = temp + 48;
            else
                temp = temp + 87;
            hexadecimalNumber[i] = temp;
            quotient = quotient / 16;
            i++;
        }
    }
    hexadecimalNumber[i] = 0;
    printf("Equivalent hexadecimal value of decimal number %ld: ", decimalNumber);
    printf("%s\n", hexadecimalNumber);
    return 0;
}

int binaryToHexa(char parameter[], char hexadecimalNumber[]) {
    long int binaryval, hexadecimalval = 0, i = 1, remainder;
    sscanf(parameter, "%ld", &binaryval);
    while (binaryval != 0) {
        remainder = binaryval % 10;
        hexadecimalval = hexadecimalval + remainder * i;
        i = i * 2;
        binaryval = binaryval / 10;
    }
    printf("Equivalent hexadecimal value: %lX", hexadecimalval);
    return 0;
}

int binaryToHex(char inStr[], struct assemblerInput opInput) {
    char *a = inStr;
    int num = 0;
    do {
        int b = *a == '1' ? 1 : 0;
        num = (num << 1) | b;
        a++;
    } while (*a);
    return num;
}

int binaryToDec(char *inStr) {
    int i = strlen(inStr) - 1;
    int p = 0;
    int res = 0;
    while (i != -1) {
        if (inStr[i] == '1') {
            res += pow(2, p);
        }
        i--;
        p++;
    }
    return res;
}

int indirectWithDecline(char parameter[], char *offset, char *base) {
    char delim[] = "(";
    char *ptr = strtok(parameter, delim);

    if (ptr != NULL) {
        strcpy(offset, ptr);
        ptr = strtok(NULL, delim);
    }
    if (ptr != NULL) {
        char tmp[MAX_INPUT];
        strcpy(tmp, ptr);
        int len = strlen(tmp);
        tmp[len - 1] = 0;
        strcpy(base, tmp);
    }
}