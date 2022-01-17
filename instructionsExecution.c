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
#include <malloc.h>
#include "instructionsExecution.h"

int showRegisterStates(int registersState[]) {
    printf("Registers Values: \n");
    for (int i = 0; i < 8; i++) {
        printf("R%d: %d    R%d: %d   R%d: %d     R%d: %d\n", i, readFromRegister(registersState, i), i + 8,
               readFromRegister(registersState, i + 8), i + 16,
               readFromRegister(registersState, i + 16), i + 24, readFromRegister(registersState, i + 24));
    }
    printf("LO: %d  |  HI: %d  |  RA: %d\n", readFromRegister(registersState, LO_REGISTER),
           readFromRegister(registersState, HI_REGISTER),
           readFromRegister(registersState, RA_REGISTER));
    printf("-----------------\n");
    return 0;
}

int showMemoryState(int memoryState[]) {
    printf("Memory state: \n");
    for (int i = 0; i < 16; i += 4) {
        printf("@%08d: %d    @%08d: %d   @%08d: %d     @%08d: %d\n", i * 4, readFromMemory(memoryState, i), (i + 1) * 4,
               readFromMemory(memoryState, i + 1), (i + 2) * 4, readFromMemory(memoryState, i + 2), (i + 3) * 4,
               readFromMemory(memoryState, i + 3));
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
    int res = readFromRegister(registersState, parameters[1]) + readFromRegister(registersState, parameters[2]);
    addInRegister(registersState, parameters[0], res);
    return currentInstructionIndex;
}

int subExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
           int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    int res = readFromRegister(registersState, parameters[1]) - readFromRegister(registersState, parameters[2]);
    addInRegister(registersState, parameters[0], res);
    return currentInstructionIndex;
}

int addiExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
            int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    int res = readFromRegister(registersState, parameters[1]) + parameters[2];
    addInRegister(registersState, parameters[0], res);
    return currentInstructionIndex;
}

int andExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
           int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    int res = readFromRegister(registersState, parameters[1]) && readFromRegister(registersState, parameters[2]);
    addInRegister(registersState, parameters[0], res);
    return currentInstructionIndex;
}

int orExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
          int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    int res = readFromRegister(registersState, parameters[1]) || readFromRegister(registersState, parameters[2]);
    addInRegister(registersState, parameters[0], res);
    return currentInstructionIndex;
}

int xorExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
           int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    int res = readFromRegister(registersState, parameters[1]) ^ readFromRegister(registersState, parameters[2]);
    addInRegister(registersState, parameters[0], res);
    return currentInstructionIndex;
}

int beqExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
           int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    if (readFromRegister(registersState, parameters[0]) == readFromRegister(registersState, parameters[1])) {
        currentInstructionIndex += parameters[2];
    }
    return currentInstructionIndex;
}

int bgtzExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
            int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    if (readFromRegister(registersState, parameters[0]) > 0) {
        currentInstructionIndex += parameters[1];
    }
    return currentInstructionIndex;
}

int blezExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
            int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    if (readFromRegister(registersState, parameters[0]) <= 0) {
        currentInstructionIndex += parameters[1];
    }
    return currentInstructionIndex;
}

int bneExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
           int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    if (readFromRegister(registersState, parameters[0]) != readFromRegister(registersState, parameters[1])) {
        currentInstructionIndex += parameters[2];
    }
    return currentInstructionIndex;
}

int divExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
           int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    int lo = readFromRegister(registersState, parameters[0]) / readFromRegister(registersState, parameters[1]);
    int hi = readFromRegister(registersState, parameters[0]) % readFromRegister(registersState, parameters[1]);
    addInRegister(registersState, LO_REGISTER, lo);
    addInRegister(registersState, HI_REGISTER, hi);
    return currentInstructionIndex;
}

int jExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
         int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    int i = 0;
    while (indexs[i].position != -1) {
        if (strcmp(opInput.p1, indexs[i].name) == 0) {
            currentInstructionIndex = indexs[i].position;
            break;
        }
        i++;
    }
    return currentInstructionIndex;
}

int jalExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
           int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    int i = 0;
    addInRegister(registersState, RA_REGISTER, currentInstructionIndex);
    while (indexs[i].position != -1) {
        if (strcmp(opInput.p1, indexs[i].name) == 0) {
            currentInstructionIndex = indexs[i].position;
            break;
        }
        i++;
    }
    return currentInstructionIndex;
}

int jrExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
          int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    return readFromRegister(registersState, parameters[0]);
}

int luiExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
           int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    addInRegister(registersState, parameters[0], parameters[1] << 16);
    return currentInstructionIndex;
}

int mfhiExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
            int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    addInRegister(registersState, parameters[0], readFromRegister(registersState, HI_REGISTER));
    return currentInstructionIndex;
}

int mfloExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
            int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    addInRegister(registersState, parameters[0], readFromRegister(registersState, LO_REGISTER));
    return currentInstructionIndex;
}

int swExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
          int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    char offset[100];
    char base[100];
    indirectWithDecline(opInput.p2, offset, base);
    processingParameter(base);
    sscanf(offset, "%d", &parameters[1]);
    sscanf(base, "%d", &parameters[2]);
    addInMemory(memoryState, readFromRegister(registersState, parameters[2]) + parameters[1],
                readFromRegister(registersState, parameters[0]));
    return currentInstructionIndex;
}

int lwExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
          int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    char offset[100];
    char base[100];
    indirectWithDecline(opInput.p2, offset, base);
    processingParameter(base);
    sscanf(offset, "%d", &parameters[1]);
    sscanf(base, "%d", &parameters[2]);
    addInRegister(registersState, parameters[0],
                  memoryState[readFromRegister(registersState, parameters[2]) + parameters[1]]);
    return currentInstructionIndex;
}

int multExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
            int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    int res = readFromRegister(registersState, parameters[0]) * readFromRegister(registersState, parameters[1]);
    char binaryRes[100];
    char binaryResHi[100];
    conversionDecimalBinaireInt(res, binaryRes, 64);
    strncpy(binaryResHi, binaryRes, 32);
    char *binaryResLo = binaryRes + 32;
    addInRegister(registersState, LO_REGISTER, binaryToDec(binaryResLo));
    addInRegister(registersState, HI_REGISTER, binaryToDec(binaryResHi));
    return currentInstructionIndex;
}

int sllExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
           int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    int res = readFromRegister(registersState, parameters[1]) << parameters[2];
    addInRegister(registersState, parameters[0], res);
    return currentInstructionIndex;
}

int srlExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
           int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    int res = readFromRegister(registersState, parameters[1]) >> parameters[2];
    addInRegister(registersState, parameters[0], res);
    return currentInstructionIndex;
}

int rotrExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
            int registersState[]) {  // TODO Tester ceci !
    int parameters[3];
    extractParmsValues(opInput, parameters);
    int valueToRotate = readFromRegister(registersState, parameters[1]);
    int rotated = (valueToRotate >> parameters[2]) | (valueToRotate << (31 - parameters[2]));
    addInRegister(registersState, parameters[0], rotated);
    return currentInstructionIndex;
}

int sltExe(struct assemblerInput opInput, struct index *indexs, int currentInstructionIndex, int memoryState[],
           int registersState[]) {
    int parameters[3];
    extractParmsValues(opInput, parameters);
    if (readFromRegister(registersState, parameters[1]) < readFromRegister(registersState, parameters[2])) {
        addInRegister(registersState, parameters[0], 1);
    } else {
        addInRegister(registersState, parameters[0], 0);
    }
    return currentInstructionIndex;
}


int
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
        pc = bgtzExe(opInput, indexs, currentInstructionIndex, memoryState, registersState);

    }

        // BLEZ
    else if (strcmp(opInput.opp, "BLEZ") == 0) {
        pc = blezExe(opInput, indexs, currentInstructionIndex, memoryState, registersState);
    }

        // BNE
    else if (strcmp(opInput.opp, "BNE") == 0) {
        pc = bneExe(opInput, indexs, currentInstructionIndex, memoryState, registersState);
    }

        // DIV
    else if (strcmp(opInput.opp, "DIV") == 0) {
        pc = divExe(opInput, indexs, currentInstructionIndex, memoryState, registersState);
    }

        // J
    else if (strcmp(opInput.opp, "J") == 0) {
        pc = jExe(opInput, indexs, currentInstructionIndex, memoryState, registersState);
    }

        // JAL
    else if (strcmp(opInput.opp, "JAL") == 0) {
        pc = jalExe(opInput, indexs, currentInstructionIndex, memoryState, registersState);
    }

        // JR
    else if (strcmp(opInput.opp, "JR") == 0) {
        pc = jrExe(opInput, indexs, currentInstructionIndex, memoryState, registersState);
    }

        //LUI
    else if (strcmp(opInput.opp, "LUI") == 0) {
        pc = luiExe(opInput, indexs, currentInstructionIndex, memoryState, registersState);
    }

        //LW
    else if (strcmp(opInput.opp, "LW") == 0) {
        pc = lwExe(opInput, indexs, currentInstructionIndex, memoryState, registersState);
    }

        //MFHI
    else if (strcmp(opInput.opp, "MFHI") == 0) {
        pc = mfhiExe(opInput, indexs, currentInstructionIndex, memoryState, registersState);
    }

        //MULT
    else if (strcmp(opInput.opp, "MULT") == 0) {
        pc = multExe(opInput, indexs, currentInstructionIndex, memoryState, registersState);
    }

        //MFLO
    else if (strcmp(opInput.opp, "MFLO") == 0) {
        pc = mfloExe(opInput, indexs, currentInstructionIndex, memoryState, registersState);
    }

        //OR
    else if (strcmp(opInput.opp, "OR") == 0) {
        pc = orExe(opInput, indexs, currentInstructionIndex, memoryState, registersState);
    }

        //SLL
    else if (strcmp(opInput.opp, "SLL") == 0) {
        pc = sllExe(opInput, indexs, currentInstructionIndex, memoryState, registersState);
    }

        //ROTR
    else if (strcmp(opInput.opp, "ROTR") == 0) {
        pc = rotrExe(opInput, indexs, currentInstructionIndex, memoryState, registersState);
    }

        //SRL
    else if (strcmp(opInput.opp, "SRL") == 0) {
        pc = srlExe(opInput, indexs, currentInstructionIndex, memoryState, registersState);
    }

        //SLT
    else if (strcmp(opInput.opp, "SLT") == 0) {
        pc = sltExe(opInput, indexs, currentInstructionIndex, memoryState, registersState);
    }

        //SW
    else if (strcmp(opInput.opp, "SW") == 0) {
        pc = swExe(opInput, indexs, currentInstructionIndex, memoryState, registersState);
    }

        //SUB
    else if (strcmp(opInput.opp, "SUB") == 0) {
        pc = subExe(opInput, indexs, currentInstructionIndex, memoryState, registersState);
    }
        //XOR
    else if (strcmp(opInput.opp, "XOR") == 0) {
        pc = xorExe(opInput, indexs, currentInstructionIndex, memoryState, registersState);
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
            showMemoryState(memoryState);
            printf("-----------------\n");
            printf("Instruction suivante %s %s,%s,%s \n", opInputs[pc].opp, opInputs[pc].p1, opInputs[pc].p2,
                   opInputs[pc].p3);
            printf("press a key\n");
            getchar();   // bloquage sur entré utilisateur
        }
        pc = processInstruction(opInputs[pc], indexs, pc, memoryState, registersState);
        pc++; // passage à l'instruction suivante
    }
    return 0;
}

int processInstructionsInteractiveMode(struct assemblerInput *opInputs, struct index *indexs, int memoryState[],
                                       int registersState[]) {
    int pc = 0;
    int nbIndex = 0;
    int nbInstructions = 0;
    while (1) {
        struct assemblerInput *input = malloc(sizeof(struct assemblerInput));
        showRegisterStates(registersState);
        showMemoryState(memoryState);
        printf("Enter operator\n");
        char firstInput[100];
        scanf("%s", firstInput);
        if (strcmp(firstInput, "EXIT") == 0 || strcmp(firstInput, "exit") == 0) {
            printf("fin de l'execution");
            break;
        }
        if (pc == (nbInstructions + nbIndex)) { // then ask user for input
            if (strstr(firstInput, ":")) { // if it's a label
                struct index *index = malloc(sizeof(struct index));
                index->position = pc;
                strcpy(index->name, firstInput);
                indexs[nbIndex] = *index;
                nbIndex++;
            } else {
                upperCase(firstInput);
                strcpy(input->opp, firstInput);
                printf("Enter first parameter\n");
                scanf("%s", input->p1);
                printf("Enter second parameter\n");
                scanf("%s", input->p2);
                printf("Enter third parameter\n");
                scanf("%s", input->p3);
                opInputs[nbInstructions] = *input;
                nbInstructions++;
            }
        }
        printf("-----------------\n");
        printf("Instruction %s %s,%s,%s \n", opInputs[pc].opp, opInputs[pc].p1, opInputs[pc].p2,
               opInputs[pc].p3);

        pc = processInstruction(opInputs[pc], indexs, pc, memoryState, registersState);
        pc++; // passage à l'instruction suivante
    }
    return 0;
}