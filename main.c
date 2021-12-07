#include <stdio.h>
#include <string.h>
#include "operatorsTranslations.h"

#define MAX_INPUT 500
#define MAX_INDEX 100


int readInput(char *fileName, struct assemblerInput *opInputs, struct index *indexs)
{
    int nbLine = 0;
    int nbIntruction = 0;
    int nbIndex = 0;
    FILE *myfile = fopen(fileName, "r");
    if (myfile == NULL)
    {
        printf("Cannot open file.\n");
        return 1;
    }
    else
    {
        //Check for number of line
        char ch;
        nbLine = 0;
        do
        {
            ch = fgetc(myfile);
            if (ch == '\n')
                nbLine++;
        } while (ch != EOF);
        rewind(myfile);

        char currentsParams[MAX_INPUT];
        for (int i = 0; i < nbLine; i++){
            char opp[100];
            fscanf(myfile, "%s %s\n", opp, currentsParams);
            if(strstr(opp, ":") )
            {
                //index
                printf("indexe %s find at %d\n", opp);
                strcpy(indexs[nbIndex].name, opp);
                indexs[nbIndex].position = nbLine;
                nbIndex++;
            } else {
                //operateur
                strcpy(opInputs[nbIntruction].opp, opp);
                printf("op %s\n", opInputs[nbIntruction].opp);

                //récupération des paramètres
                char delim[] = ",";
                char *ptr = strtok(currentsParams, delim);

                if (ptr != NULL)
                {
                    strcpy(opInputs[nbIntruction].p1, ptr);
                    ptr = strtok(NULL, delim);
                }
                if (ptr != NULL)
                {
                    strcpy(opInputs[nbIntruction].p2, ptr);
                    ptr = strtok(NULL, delim);
                }
                if (ptr != NULL)
                {
                    strcpy(opInputs[nbIntruction].p3, ptr);
                }
                printf("p1 %s\n", opInputs[nbIntruction].p1);
                printf("p2 %s\n", opInputs[nbIntruction].p2);
                printf("p3 %s\n", opInputs[nbIntruction].p3);
                nbIntruction++;
            }
        }
        indexs[nbIndex+1].position = -1;  // indicateur de fin de tableau
        printf("Nombre d'instruction dans le fichier : %d\n", nbLine);
    }
    return nbIntruction;
}

int writeResults(char *fileName, struct assemblerInput *opInputs, int nbLine){

    FILE *myfile = fopen(fileName, "w");

    if(myfile == NULL)
    {
        printf("Error!");
        return 1;
    }

    for (int i = 0; i < nbLine; i++)
    {
        fprintf(myfile,"%X\n", opInputs[i].hexa);
    }
    fclose(myfile);
    return 0;
}

//int vers tab de char
int nbDecimal(int value){
    int nbDecimal = 0;
    if (value == 0){
        nbDecimal = 1;
    }
    while (value>0) {
        value = value/10;
        nbDecimal++;
    }
    return nbDecimal;
}
int puissance(int x, int pow){
    for (int i = 1; i < pow; i++) {
        x = x*10;
    }
    return x;
}
void intVersChaine(int num, char chaine[], int nbBit){
    int nbDec = nbDecimal(num);
    int n, i;
    int lastVal=0;
    for (i = 0; i < nbDec; i++) {
        n = num / puissance(1,nbDec-i) - lastVal;
        lastVal = (n+lastVal)*10;
        chaine[i] = n+48;
    }
    for (; i < nbBit; ++i) {
        chaine[i+1]=chaine[i];
        chaine[i]='0';
    }
    chaine[i++]=0;
}
int processingParameter(char parameter[]){
    //traitement du parametre
    int count = strlen(parameter);
    printf("%s\n",parameter);
    if (parameter[0]=='$'){
        for (int i = 0; i < count; i++){
            parameter[i] = parameter[i + 1];
        }
    }
    return 0;
}
int conversionDecimalBinaire (char parameter[], char *res, int nbBit)
{
    unsigned long int valeur;
    char tab[15];
    int x=0;
    int i = 0;
    int reste;
    int binaire=0;
    processingParameter(parameter);
    sscanf(parameter,"%ld",&valeur);

    while (valeur > 0)
    {
        reste = valeur%2 ;//calcul le reste
        tab[x] = reste+48;
        x++;
        valeur = valeur/2;
    }
    while (x < nbBit){
        tab[x] = '0';
        x++;
    }
    int j = x-1;
    while ( i!=nbBit ) {
        res[i] = tab[j];
        i++;
        j--;
    }
    res[x]=0;
    return binaire ;
}
int decimalToHexa(char parameter[], char hexadecimalNumber[]){
    long int decimalNumber,quotient;
    int i=0,temp;
    printf("%s\n",parameter);
    sscanf(parameter,"%ld",&decimalNumber);
    quotient = decimalNumber;
    if (quotient==0){
        hexadecimalNumber[i]='0';
        i++;
    } else {
        while(quotient!=0) {
            temp = quotient % 16;
            //To convert integer into character
            if( temp < 10)
                temp = temp + 48; else
                temp = temp + 87;
            hexadecimalNumber[i] = temp;
            quotient = quotient / 16;
            i++;
        }
    }
    hexadecimalNumber[i]= 0;
    printf("Equivalent hexadecimal value of decimal number %ld: ",decimalNumber);
    printf("%s\n",hexadecimalNumber);
    return 0;
}

int binaryToHexa(char parameter[], char hexadecimalNumber[]){
    long int binaryval, hexadecimalval = 0, i = 1, remainder;
    sscanf(parameter,"%ld", &binaryval);
    while (binaryval != 0){
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
        int b = *a=='1'?1:0;
        num = (num<<1)|b;
        a++;
    } while (*a);
    return num;
}


int hexaTranslat(struct assemblerInput *opInputs, int count, struct index *indexs)
{
    for (int i = 0; i < count; i++)
    {
        // ADD
        if (strcmp(opInputs[i].opp, "ADD") == 0)
        {
            char res[100] = "";
            opInputs[i].hexa = add(opInputs[i], res);
        }

        // ADDI
        else if (strcmp(opInputs[i].opp, "ADDI") == 0)
        {
            char res[100] = "";
            opInputs[i].hexa = addi(opInputs[i], res);
        }
/*
        // BEQ
        else if (strcmp(opInputs[i].opp, "BEQ") == 0)
        {
            char res[100] = "";
            beq(opInputs[i], res);
            opInputs[i].hexa = res;
        }

        // BGTZ
        else if (strcmp(opInputs[i].opp, "BGTZ") == 0)
        {
            char res[100] = "";
            bgtz(opInputs[i], res);
            opInputs[i].hexa = res;
        }

        // BLEZ
        else if (strcmp(opInputs[i].opp, "BLEZ") == 0)
        {
            char res[100] = "";
            blez(opInputs[i], res);
            opInputs[i].hexa = res;
        }

        // BNE
        else if (strcmp(opInputs[i].opp, "BNE") == 0)
        {
            char res[100] = "";
            bne(opInputs[i], res);
            opInputs[i].hexa = res;
        }

        // DIV
        else if (strcmp(opInputs[i].opp, "DIV") == 0)
        {
            char res[100] = "";
            div(opInputs[i], res);
            opInputs[i].hexa = res;
        }

        // J
        else if (strcmp(opInputs[i].opp, "J") == 0)
        {
            char res[100] = "";
            j(opInputs[i], res);
            opInputs[i].hexa = res;
        }

        // JAL
        else if (strcmp(opInputs[i].opp, "JAL") == 0)
        {
            char res[100] = "";
            jal(opInputs[i], res, indexs);
            opInputs[i].hexa = res;
        }

        // JR
        else if (strcmp(opInputs[i].opp, "JR") == 0)
        {
            char res[100] = "";
            jr(opInputs[i], res);
            opInputs[i].hexa = res;
        }

        //LUI
        else if (strcmp(opInputs[i].opp, "LUI") == 0)
        {
            char res[100] = "";
            lui(opInputs[i], res);
            opInputs[i].hexa = res;
        }

        //LW
        else if (strcmp(opInputs[i].opp, "LW") == 0)
        {
            char res[100] = "";
            lw(opInputs[i], res);
            opInputs[i].hexa = res;
        }

        //MFHI
        else if (strcmp(opInputs[i].opp, "MFHI") == 0)
        {
            char res[100] = "";
            mfhi(opInputs[i], res);
            opInputs[i].hexa = res;
        }

        //MULT
        else if (strcmp(opInputs[i].opp, "MULT") == 0)
        {
            char res[100] = "";
            mult(opInputs[i], res);
            opInputs[i].hexa = res;
        }

        //MFLO
        else if (strcmp(opInputs[i].opp, "MFLO") == 0)
        {
            char res[100] = "";
            mflo(opInputs[i], res);
            opInputs[i].hexa = res;
        }

        //OR
        else if (strcmp(opInputs[i].opp, "OR") == 0)
        {
            char res[100] = "";
            or(opInputs[i], res);
            opInputs[i].hexa = res;
        }

        //NOP
        else if (strcmp(opInputs[i].opp, "NOP") == 0)
        {
            char res[100] = "";
            nop(opInputs[i], res);
            opInputs[i].hexa = res;
        }

        //SLL
        else if (strcmp(opInputs[i].opp, "SLL") == 0)
        {
            char res[100] = "";
            sll(opInputs[i], res);
            opInputs[i].hexa = res;
        }

        //ROTR
        else if (strcmp(opInputs[i].opp, "ROTR") == 0)
        {
            char res[100] = "";
            rotr(opInputs[i], res);
            opInputs[i].hexa = res;
        }

        //SRL
        else if (strcmp(opInputs[i].opp, "SRL") == 0)
        {
            char res[100] = "";
            srl(opInputs[i], res);
            opInputs[i].hexa = res;
        }

        //SLT
        else if (strcmp(opInputs[i].opp, "SLT") == 0)
        {
            char res[100] = "";
            slt(opInputs[i], res);
            opInputs[i].hexa = res;
        }

        //SW
        else if (strcmp(opInputs[i].opp, "SW") == 0)
        {
            char res[100] = "";
            sw(opInputs[i], res);
            opInputs[i].hexa = res;
        }

        //SUB
        else if (strcmp(opInputs[i].opp, "SUB") == 0)
        {
            char res[100] = "";
            sub(opInputs[i], res);
            opInputs[i].hexa = res;
        }

        //SYSCALL
        else if (strcmp(opInputs[i].opp, "SYSCALL") == 0)
        {
            char res[100] = "";
            syscall(opInputs[i], res);
            opInputs[i].hexa = res;
        }
        
        //XOR
        else if (strcmp(opInputs[i].opp, "XOR") == 0)
        {
            char res[100] = "";
            xor(opInputs[i], res);
            opInputs[i].hexa = res;
        }
        */
        
        else
        {
            opInputs[i].hexa = 1;
            printf("operande %s Inconue\n", opInputs[i].opp);
        }
        printf("%X\n", opInputs[i].hexa);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    printf("Lecture de %s\n", argv[1]);
    struct assemblerInput opInputs[MAX_INPUT];
    struct index indexs[MAX_INDEX];
    int nbLine = readInput(argv[1], opInputs, indexs);
    hexaTranslat(opInputs, nbLine, indexs);
    writeResults(argv[2], opInputs, nbLine);
    return 0;
}
