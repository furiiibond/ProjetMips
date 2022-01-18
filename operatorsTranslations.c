//
// Created by jcl on 07/12/2021.
//

#include <string.h>
#include <stdio.h>
#include "operatorsTranslations.h"
#include "utilsAndConverters.h"



int add(struct assemblerInput opInput, char *res) {
    char special[100] = "000000";
    char zero[100] = "00000";
    char opcode[100] = "100000";
    char p1[100];
    char p2[100];
    char p3[100];
    conversionDecimalBinaire(opInput.p1, p1, 5);
    conversionDecimalBinaire(opInput.p2, p2, 5);
    conversionDecimalBinaire(opInput.p3, p3, 5);
    strcat(res, special);
    strcat(res, p2);
    strcat(res, p3);
    strcat(res, p1);
    strcat(res, zero);
    strcat(res, opcode);
    return binaryToHex(res, opInput);
}

int addi(struct assemblerInput opInput, char res[])
{
    char opcode[100] = "001000";
    char p1[100];
    char p2[100];
    char p3[100];
    conversionDecimalBinaire(opInput.p1, p1, 5);
    conversionDecimalBinaire(opInput.p2, p2, 5);

    conversionDecimalBinaireMayBeNegative(opInput.p3, p3, 16, &p1);

    strcat(res, opcode);
    strcat(res, p2);
    strcat(res, p1);
    strcat(res, p3);
    return binaryToHex(res, opInput);
}

int and(struct assemblerInput opInput, char res[]) {
    char special[100] = "000000";
    char zero[100] = "00000";
    char opcode[100] = "100100";
    char p1[100];
    char p2[100];
    char p3[100];

    conversionDecimalBinaire(opInput.p1, p1, 5);

    conversionDecimalBinaire(opInput.p2, p2, 5);

    conversionDecimalBinaire(opInput.p3, p3, 5);

    strcat(res, special);
    strcat(res, p2);
    strcat(res, p3);
    strcat(res, p1);
    strcat(res, zero);
    strcat(res, opcode);
    return binaryToHex(res, opInput);
}

int beq(struct assemblerInput opInput, char res[]) {
    char opcode[100] = "000100";
    char p1[100];
    char p2[100];
    char p3[100];

    conversionDecimalBinaire(opInput.p1, p1, 5);

    conversionDecimalBinaire(opInput.p2, p2, 5);

    conversionDecimalBinaireMayBeNegative(opInput.p3, p3, 16, &p2);

    strcat(res, opcode);
    strcat(res, p1);
    strcat(res, p2);
    strcat(res, p3);
    return binaryToHex(res, opInput);
}

int bgtz(struct assemblerInput opInput, char res[]) {
    char opcode[100] = "000111";
    char zero[100] = "00000";
    char p1[100];
    char p2[100];

    conversionDecimalBinaire(opInput.p1, p1, 5);

    conversionDecimalBinaireMayBeNegative(opInput.p2, p2, 16, &zero);

    strcat(res, opcode);
    strcat(res, p1);
    strcat(res, zero);
    strcat(res, p2);
    return binaryToHex(res, opInput);
}

int blez(struct assemblerInput opInput, char res[]) {
    char opcode[100] = "000110";
    char zero[100] = "00000";
    char p1[100];
    char p2[100];

    conversionDecimalBinaire(opInput.p1, p1, 5);

    conversionDecimalBinaireMayBeNegative(opInput.p2, p2, 16, &zero);

    strcat(res, opcode);
    strcat(res, p1);
    strcat(res, zero);
    strcat(res, p2);
    return binaryToHex(res, opInput);
}

int bne(struct assemblerInput opInput, char res[]) {
    char opcode[100] = "000101";
    char p1[100];
    char p2[100];
    char p3[100];

    conversionDecimalBinaire(opInput.p1, p1, 5);

    conversionDecimalBinaire(opInput.p2, p2, 5);

    conversionDecimalBinaireMayBeNegative(opInput.p3, p3, 16, &p2);

    strcat(res, opcode);
    strcat(res, p1);
    strcat(res, p2);
    strcat(res, p3);
    return binaryToHex(res, opInput);
}

int div(struct assemblerInput opInput, char res[]) {
    char special[100] = "000000";
    char opcode[100] = "011010";
    char zero[100] = "0000000000";
    char p1[100];
    char p2[100];

    conversionDecimalBinaire(opInput.p1, p1, 5);

    conversionDecimalBinaire(opInput.p2, p2, 5);

    strcat(res, special);
    strcat(res, p1);
    strcat(res, p2);
    strcat(res, zero);
    strcat(res, opcode);
    return binaryToHex(res, opInput);
}

int j(struct assemblerInput opInput, char res[], struct index *indexs) {
    char opcode[100] = "000010";
    char p1[100] = "";

    //recherche de l'indexe du label
    int i = 0;
    while (indexs[i].position != -1) {
        if (strcmp(opInput.p1, indexs[i].name) == 0) {
            conversionDecimalBinaireInt(indexs[i].position, p1, 26);
        }
        i++;
    }


    strcat(res, opcode);
    strcat(res, p1);
    return binaryToHex(res, opInput);
}

int jal(struct assemblerInput opInput, char res[], struct index *indexs) {
    char opcode[100] = "000011";
    char p1[100] = "";

    //recherche de l'indexe du label
    int i = 0;
    while (indexs[i].position != -1) {
        if (strcmp(opInput.p1, indexs[i].name) == 0) {
            conversionDecimalBinaireInt(indexs[i].position, p1, 26);
        }
        i++;
    }


    strcat(res, opcode);
    strcat(res, p1);
    return binaryToHex(res, opInput);
}

int jr(struct assemblerInput opInput, char res[]) {
    char special[100] = "000000";
    char zero[100] = "0000000000";
    char opcode[100] = "001000";
    char hint[100] = "00000";   // release 1 of architecture
    char p1[100];

    conversionDecimalBinaire(opInput.p1, p1, 5);

    strcat(res, special);
    strcat(res, p1);
    strcat(res, zero);
    strcat(res, hint);
    strcat(res, opcode);
    return binaryToHex(res, opInput);
}

int lui(struct assemblerInput opInput, char res[]) {
    char opcode[100] = "001111";
    char zero[100] = "00000";
    char p1[100];
    char p2[100];


    conversionDecimalBinaire(opInput.p1, p1, 5);

    conversionDecimalBinaireMayBeNegative(opInput.p2, p2, 16, &p1);


    strcat(res, opcode);
    strcat(res, zero);
    strcat(res, p1);
    strcat(res, p2);

    return binaryToHex(res, opInput);
}

int lw(struct assemblerInput opInput, char res[]) {
    char opcode[100] = "100011";
    char p1[100];
    char offset[100];
    char base[100];
    char offsetDecimal[100];
    char baseDecimal[100];

    //Séparation du parametre 2 en indirect avec décalage
    indirectWithDecline(opInput.p2, offsetDecimal, baseDecimal);
    conversionDecimalBinaire(opInput.p1, p1, 5);

    conversionDecimalBinaireMayBeNegative(offsetDecimal, offset, 16, &p1);

    conversionDecimalBinaire(baseDecimal, base, 5);

    strcat(res, opcode);
    strcat(res, base);
    strcat(res, p1);
    strcat(res, offset);
    return binaryToHex(res, opInput);
}

int mfhi(struct assemblerInput opInput, char res[]) {
    char special[100] = "000000";
    char zero1[100] = "0000000000";
    char zero2[100] = "00000";
    char opcode[100] = "010000";
    char p1[100];

    conversionDecimalBinaire(opInput.p1, p1, 5);


    strcat(res, special);
    strcat(res, zero1);
    strcat(res, p1);
    strcat(res, zero2);
    strcat(res, opcode);


    return binaryToHex(res, opInput);
}

int mult(struct assemblerInput opInput, char res[]) {
    char special[100] = "000000";
    char opcode[100] = "011000";
    char p1[100];
    char p2[100];
    char zero[100] = "0000000000";
    conversionDecimalBinaire(opInput.p1, p1, 5);

    conversionDecimalBinaire(opInput.p2, p2, 5);

    strcat(res, special);
    strcat(res, p1);
    strcat(res, p2);
    strcat(res, zero);
    strcat(res, opcode);
    return binaryToHex(res, opInput);
}

int mflo(struct assemblerInput opInput, char res[]) {
    char special[100] = "000000";
    char zero1[100] = "0000000000";
    char zero2[100] = "00000";
    char opcode[100] = "010010";
    char p1[100];

    conversionDecimalBinaire(opInput.p1, p1, 5);

    strcat(res, special);
    strcat(res, zero1);
    strcat(res, p1);
    strcat(res, zero2);
    strcat(res, opcode);
    return binaryToHex(res, opInput);
}

int or(struct assemblerInput opInput, char res[]) {
    char special[100] = "000000";
    char p1[100];
    char p2[100];
    char p3[100];
    char zero[100] = "00000";
    char opcode[100] = "100101";

    conversionDecimalBinaire(opInput.p1, p1, 5);

    conversionDecimalBinaire(opInput.p2, p2, 5);

    conversionDecimalBinaire(opInput.p3, p3, 5);

    strcat(res, special);
    strcat(res, p2);
    strcat(res, p3);
    strcat(res, p1);
    strcat(res, zero);
    strcat(res, opcode);
    return binaryToHex(res, opInput);
}


int nop(struct assemblerInput opInput, char res[]) {
    char opcode[100] = "00000000000000000000000000000000";
    strcat(res, opcode);

    return binaryToHex(res, opInput);
}


int sll(struct assemblerInput opInput, char res[]) {
    char special[100] = "000000";
    char zero[100] = "00000";
    char p1[100];
    char p2[100];
    char p3[100];
    char opcode[100] = "000000";


    conversionDecimalBinaire(opInput.p1, p1, 5);

    conversionDecimalBinaire(opInput.p2, p2, 5);

    conversionDecimalBinaireMayBeNegative(opInput.p3, p3, 5, &p1);

    strcat(res, special);
    strcat(res, zero);
    strcat(res, p2);
    strcat(res, p1);
    strcat(res, p3);
    strcat(res, opcode);
    return binaryToHex(res, opInput);
}

int rotr(struct assemblerInput opInput, char res[]) {
    char special[100] = "000000";
    char zero[100] = "0000";
    char p1[100];
    char p2[100];
    char p3[100];
    char opcode[100] = "000010";

    conversionDecimalBinaire(opInput.p1, p1, 5);

    conversionDecimalBinaire(opInput.p2, p2, 5);

    conversionDecimalBinaireMayBeNegative(opInput.p3, p3, 5, &p1);

    strcat(res, special);
    strcat(res, zero);
    strcat(res, p2);
    strcat(res, p1);
    strcat(res, p3);
    strcat(res, opcode);
    return binaryToHex(res, opInput);
}

int srl(struct assemblerInput opInput, char res[]) {
    char special[100] = "000000";
    char zero[100] = "0000";
    char opcode[100] = "000010";
    char rZero[100] = "0";
    char p1[100];
    char p2[100];
    char p3[100];

    conversionDecimalBinaire(opInput.p1, p1, 5);

    conversionDecimalBinaire(opInput.p2, p2, 5);

    conversionDecimalBinaireMayBeNegative(opInput.p3, p3, 5, &p1);

    strcat(res, special);
    strcat(res, zero);
    strcat(res, rZero);
    strcat(res, p2);
    strcat(res, p1);
    strcat(res, p3);
    strcat(res, opcode);
    return binaryToHex(res, opInput);
}

int slt(struct assemblerInput opInput, char res[]) {
    char opcode[100] = "101010";
    char special[100] = "000000";
    char zero[100] = "00000";
    char p1[100];
    char p2[100];
    char p3[100];
    conversionDecimalBinaire(opInput.p1, p1, 5);

    conversionDecimalBinaire(opInput.p2, p2, 5);

    conversionDecimalBinaire(opInput.p3, p3, 5);

    strcat(res, special);
    strcat(res, p2);
    strcat(res, p3);
    strcat(res, p1);
    strcat(res, zero);
    strcat(res, opcode);
    return binaryToHex(res, opInput);
}

int sw(struct assemblerInput opInput, char res[]) {
    char opcode[100] = "101011";
    char p1[100];
    char p2[100];
    char offset[100];
    char base[100];
    char offsetDecimal[100];
    char baseDecimal[100];
    //Séparation du parametre 2 en indirect avec décalage
    indirectWithDecline(opInput.p2, offsetDecimal, baseDecimal);
    conversionDecimalBinaire(opInput.p1, p1, 5);

    conversionDecimalBinaire(baseDecimal, base, 5);

    conversionDecimalBinaireMayBeNegative(offsetDecimal, offset, 16, &p1);

    strcat(res, opcode);
    strcat(res, base);
    strcat(res, p1);
    strcat(res, offset);
    return binaryToHex(res, opInput);
}

int sub(struct assemblerInput opInput, char res[]) {
    char special[100] = "000000";
    char zero[100] = "00000";
    char opcode[100] = "100010";
    char p1[100];
    char p2[100];
    char p3[100];

    conversionDecimalBinaire(opInput.p1, p1, 5);

    conversionDecimalBinaire(opInput.p2, p2, 5);

    conversionDecimalBinaire(opInput.p3, p3, 5);

    strcat(res, special);
    strcat(res, p2);
    strcat(res, p3);
    strcat(res, p1);
    strcat(res, zero);
    strcat(res, opcode);
    return binaryToHex(res, opInput);
}

int xor(struct assemblerInput opInput, char res[]) {
    char special[100] = "000000";
    char opcode[100] = "100110 ";
    char zero[100] = "00000";
    char p1[100];
    char p2[100];
    char p3[100];

    conversionDecimalBinaire(opInput.p1, p1, 5);

    conversionDecimalBinaire(opInput.p2, p2, 5);

    conversionDecimalBinaire(opInput.p3, p3, 5);

    strcat(res, special);
    strcat(res, p2);
    strcat(res, p3);
    strcat(res, p1);
    strcat(res, zero);

    strcat(res, opcode);
    return binaryToHex(res, opInput);
}



int hexaTranslat(struct assemblerInput *opInputs, int count, struct index *indexs) {
    for (int i = 0; i < count; i++) {
        // ADD
        if (strcmp(opInputs[i].opp, "ADD") == 0) {
            char res[100] = "";
            opInputs[i].hexa = add(opInputs[i], res);
        }

            // ADDI
        else if (strcmp(opInputs[i].opp, "ADDI") == 0) {
            char res[100] = "";
            opInputs[i].hexa = addi(opInputs[i], res);
        }

            // AND
        else if (strcmp(opInputs[i].opp, "AND") == 0) {
            char res[100] = "";
            opInputs[i].hexa = and(opInputs[i], res);
        }

            // BEQ
        else if (strcmp(opInputs[i].opp, "BEQ") == 0) {
            char res[100] = "";
            opInputs[i].hexa = beq(opInputs[i], res);

        }

            // BGTZ
        else if (strcmp(opInputs[i].opp, "BGTZ") == 0) {
            char res[100] = "";
            opInputs[i].hexa = bgtz(opInputs[i], res);

        }

            // BLEZ
        else if (strcmp(opInputs[i].opp, "BLEZ") == 0) {
            char res[100] = "";
            opInputs[i].hexa = blez(opInputs[i], res);

        }

            // BNE
        else if (strcmp(opInputs[i].opp, "BNE") == 0) {
            char res[100] = "";
            opInputs[i].hexa = bne(opInputs[i], res);

        }

            // DIV
        else if (strcmp(opInputs[i].opp, "DIV") == 0) {
            char res[100] = "";
            opInputs[i].hexa = div(opInputs[i], res);

        }

            // J
        else if (strcmp(opInputs[i].opp, "J") == 0) {
            char res[100] = "";
            opInputs[i].hexa = j(opInputs[i], res, indexs);

        }

            // JAL
        else if (strcmp(opInputs[i].opp, "JAL") == 0) {
            char res[100] = "";
            opInputs[i].hexa = jal(opInputs[i], res, indexs);

        }

            // JR
        else if (strcmp(opInputs[i].opp, "JR") == 0) {
            char res[100] = "";
            opInputs[i].hexa = jr(opInputs[i], res);

        }

            //LUI
        else if (strcmp(opInputs[i].opp, "LUI") == 0) {
            char res[100] = "";
            opInputs[i].hexa = lui(opInputs[i], res);

        }

            //LW
        else if (strcmp(opInputs[i].opp, "LW") == 0) {
            char res[100] = "";
            opInputs[i].hexa = lw(opInputs[i], res);

        }

            //MFHI
        else if (strcmp(opInputs[i].opp, "MFHI") == 0) {
            char res[100] = "";
            opInputs[i].hexa = mfhi(opInputs[i], res);

        }

            //MULT
        else if (strcmp(opInputs[i].opp, "MULT") == 0) {
            char res[100] = "";
            opInputs[i].hexa = mult(opInputs[i], res);

        }

            //MFLO
        else if (strcmp(opInputs[i].opp, "MFLO") == 0) {
            char res[100] = "";
            opInputs[i].hexa = mflo(opInputs[i], res);

        }

            //OR
        else if (strcmp(opInputs[i].opp, "OR") == 0) {
            char res[100] = "";
            opInputs[i].hexa = or(opInputs[i], res);

        }

            //NOP
        else if (strcmp(opInputs[i].opp, "NOP") == 0) {
            char res[100] = "";
            opInputs[i].hexa = nop(opInputs[i], res);

        }

            //SLL
        else if (strcmp(opInputs[i].opp, "SLL") == 0) {
            char res[100] = "";
            opInputs[i].hexa = sll(opInputs[i], res);

        }

            //ROTR
        else if (strcmp(opInputs[i].opp, "ROTR") == 0)
        {
            char res[100] = "";
            opInputs[i].hexa = rotr(opInputs[i], res);

        }

            //SRL
        else if (strcmp(opInputs[i].opp, "SRL") == 0)
        {
            char res[100] = "";
            opInputs[i].hexa = srl(opInputs[i], res);

        }

            //SLT
        else if (strcmp(opInputs[i].opp, "SLT") == 0)
        {
            char res[100] = "";
            opInputs[i].hexa = slt(opInputs[i], res);

        }

            //SW
        else if (strcmp(opInputs[i].opp, "SW") == 0)
        {
            char res[100] = "";
            opInputs[i].hexa = sw(opInputs[i], res);

        }

            //SUB
        else if (strcmp(opInputs[i].opp, "SUB") == 0)
        {
            char res[100] = "";
            opInputs[i].hexa = sub(opInputs[i], res);

        }

            //XOR
        else if (strcmp(opInputs[i].opp, "XOR") == 0)
        {
            char res[100] = "";
            opInputs[i].hexa = xor(opInputs[i], res);

        }
        else {
            opInputs[i].hexa = 1;
            printf("operande %s Inconue\n", opInputs[i].opp);
        }
        printf("%X\n", opInputs[i].hexa);
    }
    return 0;
}