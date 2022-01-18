//
// Created by jcl on 16/12/2021.
//

#include "memory.h"
#include "fileIO.h"
#include "utilsAndConverters.h"
#include "operatorsTranslations.h"
#include <stdio.h>
#include "registers.h"

int addInRegister(int registersState[], int index, int value) {
    if (index < REGISTER_INPUT_SIZE) {
        registersState[index] = value;
        return 0;
    }
    return 1;
}

int readFromRegister(int registersState[], int index) {
    if (index < REGISTER_INPUT_SIZE) {
        return registersState[index];
    }
    return -1;
}