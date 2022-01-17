#include <stdio.h>
#include "operatorsTranslations.h"
#include "utilsAndConverters.h"
#include "fileIO.h"
#include "memory.h"
#include "registers.h"
#include "instructionsExecution.h"
#include <string.h>

//étape 4 LAPIERRE Jean-Camille CARRERE Scott


int main(int argc, char *argv[]) {
    printf("Lecture de %s\n", argv[1]);
    struct assemblerInput opInputs[MAX_INPUT];
    int memoryState[MEMORY_INPUT_SIZE];  // stands for memory.
    int registersState[REGISTER_INPUT_SIZE];  // stands for registers.
    struct index indexs[MAX_INDEX];
    int stepByStepMode = (argv[2] != NULL && strcmp(argv[2], "-pas") == 0);
    int nbLine = readInput(argv[1], opInputs, indexs);
    hexaTranslat(opInputs, nbLine, indexs);
    processInstructions(opInputs, nbLine, indexs, memoryState, registersState, stepByStepMode);
    showRegisterStates(registersState);
    showMemoryState(memoryState);
    if (!stepByStepMode) {
        writeResults(argv[2], opInputs, nbLine);
        writeStateFile(argv[3], registersState);
    }
    return 0;
}