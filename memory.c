//
// Created by jcl on 16/12/2021.
//

#include "memory.h"

int addInMemory(int memoryState[], int index, int value) {
    if (index < MEMORY_INPUT_SIZE) {
        memoryState[index] = value;
        return 0;
    }
    return 1;
}

int readFromMemory(int memoryState[], int index) {
    if (index < MEMORY_INPUT_SIZE) {
        return memoryState[index];
    }
    return -1;
}