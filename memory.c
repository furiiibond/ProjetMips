//
// Created by jcl on 16/12/2021.
//

#include "fileIO.h"
#include "utilsAndConverters.h"
#include "operatorsTranslations.h"
#include <stdio.h>
#include "memory.h"

int addInMemory(int memoryState[], int index, int value) {
    memoryState[index] = value;
    return 0;
}

int removeFromMemory(int memoryState[], int index) {
    int res = memoryState[index];
    memoryState[index] = 0;
    return res;
}