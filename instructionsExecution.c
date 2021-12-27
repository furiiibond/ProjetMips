//
// Created by jcl on 23/12/2021.
//

#include <string.h>
#include "registers.h"
#include "memory.h"
#include "fileIO.h"
#include "utilsAndConverters.h"
#include "operatorsTranslations.h"
#include <stdio.h>
#include "instructionsExecution.h"

int showRegisterStates(int registersState[]) {
    printf("Registers Values: \n");
    for (int i = 0; i < 8; i++) {
        printf("R%d: %d    R%d: %d   R%d: %d     R%d: %d\n", i, registersState[i], i + 8, registersState[i + 8], i + 16,
               registersState[i + 16], i + 24, registersState[i + 24]);
    }
    return 0;
}

int *extractParmsValues(struct assemblerInput opInput, int res[]) {
    processingParameter(opInput.p1);
    processingParameter(opInput.p2);
    processingParameter(opInput.p3);

    sscanf(opInput.p1, "%d", &res[0]);
    sscanf(opInput.p2, "%d", &res[1]);
    sscanf(opInput.p3, "%d", &res[2]);
    return res;
}

int addExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
           int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    int res = registersState[parameters[1]] + registersState[parameters[2]];
    addInRegister(registersState, parameters[0], res);
    return currentInstructionIndex;
}

int addiExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
            int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    int res = registersState[parameters[1]] + parameters[2];
    addInRegister(registersState, parameters[0], res);
    return currentInstructionIndex;
}

int andExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
           int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    int res = registersState[parameters[1]] && registersState[parameters[2]];
    addInRegister(registersState, parameters[0], res);
    return currentInstructionIndex;
}

int beqExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
           int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    if (registersState[parameters[0]] == registersState[parameters[1]]) {
        currentInstructionIndex += parameters[2];
    }
    return currentInstructionIndex;
}

int bgtzExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
            int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    if (registersState[parameters[0]] > 0) {
        currentInstructionIndex += parameters[1];
    }
    return currentInstructionIndex;
}

int blezExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
            int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    if (registersState[parameters[0]] <= 0) {
        currentInstructionIndex += parameters[1];
    }
    return currentInstructionIndex;
}

int bneExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
           int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    if (registersState[parameters[0]] != registersState[parameters[1]]) {
        currentInstructionIndex += parameters[2];
    }
    return currentInstructionIndex;
}

processInstruction(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
                   int registersState[]) { // return next instruction to execute
    int pc = currentInstructionIndex;
    if (strcmp(opInput.opp, "ADD") == 0) {
        pc = addExe(opInput, indexs, currentInstructionIndex, memoryState, registersState);
    }

        // ADDI
    else if (strcmp(opInput.opp, "ADDI") == 0) {
        pc = addiExe(opInput, indexs, currentInstructionIndex, memoryState, registersState);
    }

        // AND
    else if (strcmp(opInput.opp, "AND") == 0) {
        pc = andExe(opInput, indexs, currentInstructionIndex, memoryState, registersState);
    }

        // BEQ
    else if (strcmp(opInput.opp, "BEQ") == 0) {
        pc = beqExe(opInput, indexs, currentInstructionIndex, memoryState, registersState);
    }

        // BGTZ
    else if (strcmp(opInput.opp, "BGTZ") == 0) {


    }

        // BLEZ
    else if (strcmp(opInput.opp, "BLEZ") == 0) {

    }

        // BNE
    else if (strcmp(opInput.opp, "BNE") == 0) {

    }

        // DIV
    else if (strcmp(opInput.opp, "DIV") == 0) {

    }

        // J
    else if (strcmp(opInput.opp, "J") == 0) {

    }

        // JAL
    else if (strcmp(opInput.opp, "JAL") == 0) {

    }

        // JR
    else if (strcmp(opInput.opp, "JR") == 0) {

    }

        //LUI
    else if (strcmp(opInput.opp, "LUI") == 0) {

    }

        //LW
    else if (strcmp(opInput.opp, "LW") == 0) {

    }

        //MFHI
    else if (strcmp(opInput.opp, "MFHI") == 0) {

    }

        //MULT
    else if (strcmp(opInput.opp, "MULT") == 0) {

    }

        //MFLO
    else if (strcmp(opInput.opp, "MFLO") == 0) {

    }

        //OR
    else if (strcmp(opInput.opp, "OR") == 0) {

    }

        //NOP
    else if (strcmp(opInput.opp, "NOP") == 0) {

    }

        //SLL
    else if (strcmp(opInput.opp, "SLL") == 0) {

    }

        //ROTR
    else if (strcmp(opInput.opp, "ROTR") == 0) {

    }

        //SRL
    else if (strcmp(opInput.opp, "SRL") == 0) {

    }

        //SLT
    else if (strcmp(opInput.opp, "SLT") == 0) {

    }

        //SW
    else if (strcmp(opInput.opp, "SW") == 0) {


    }

        //SUB
    else if (strcmp(opInput.opp, "SUB") == 0) {


    }

/*        //SYSCALL
        else if (strcmp(opInput.opp, "SYSCALL") == 0)
        {

        }*/

        //XOR
    else if (strcmp(opInput.opp, "XOR") == 0) {


    } else {
        printf("operande %s inconue de l'executeur\n", opInput.opp);
        pc = currentInstructionIndex;
    }
    return pc;
}

int processInstructions(struct assemblerInput *opInputs, int nbInputs, struct index *indexs, int memoryState[],
                        int registersState[], int iterate) {
    int pc = 0;
    while (pc < nbInputs) {
        if (iterate) {
            showRegisterStates(registersState);
            printf("-----------------\n");
            printf("Instruction suivante %s %s,%s,%s \n", opInputs[pc].opp, opInputs[pc].p1, opInputs[pc].p2,
                   opInputs[pc].p3);
            getchar();   // bloquage sur entré utilisateur
        }
        pc = processInstruction(opInputs[pc], indexs, pc, memoryState, registersState);
        pc++; // passage à l'instruction suivante
    }
    return 0;
}