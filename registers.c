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
    registersState[index] = value;
    return 0;
}

int readFromRegister(int registersState[], int index) {
    int res = registersState[index];
    return res;
}