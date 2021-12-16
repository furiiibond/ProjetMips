#include <stdio.h>
#include "operatorsTranslations.h"
#include "utilsAndConverters.h"
#include "fileIO.h"
#include "memory.h"
#include "registers.h"

//étape 4 LAPIERRE Jean-Camille CARERRE Scott


int main(int argc, char *argv[]) {
    printf("Lecture de %s\n", argv[1]);
    struct assemblerInput opInputs[MAX_INPUT];
    int memoryState[MEMORY_INPUT_SIZE];  // stands for memory.
    int registersState[REGISTER_INPUT_SIZE];  // stands for registers.
    struct index indexs[MAX_INDEX];
    int nbLine = readInput(argv[1], opInputs, indexs);
    hexaTranslat(opInputs, nbLine, indexs);
    writeResults(argv[2], opInputs, nbLine);
    return 0;
}
