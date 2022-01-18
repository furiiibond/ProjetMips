//
// Created by jcl on 08/12/2021.
//

#include "operatorsTranslations.h"
#include <string.h>
#include <stdio.h>
#include "utilsAndConverters.h"
#include <math.h>

void upperCase(char *chaine) {
    int i = 0;
    for (i = 0; chaine[i] != '\0'; i++) {
        if (chaine[i] >= 'a' && chaine[i] <= 'z')
            chaine[i] -= 'a' - 'A';
    }
}

void removeSpaces(char *s) {
    char *d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*s++ = *d++);
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
        int k = 0;   // inversion des bits
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
        int nextOpValue = binaryToDec(nextOp);
        int len = strlen(nextOp);
        if (nextOpValue == 0) {  //Decrease in the value of the opperator follow in order to determine the profit
            nextOpValue = (pow(2, len - 1) - 1);
        } else {
            nextOpValue--;
        }
        conversionDecimalBinaireInt(nextOpValue, nextOp, len);
    }
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
    return 0;
}