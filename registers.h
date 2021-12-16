//
// Created by jcl on 16/12/2021.
//

#ifndef MYOWN_REGISTERS_H
#define MYOWN_REGISTERS_H

#define REGISTER_INPUT_SIZE 32 // 32 emplacement mémoires avec adresse et valeur en decimales.

int addInRegister(int registersState[], int index, int value);

int removeFromRegister(int registersState[], int index);

#endif //MYOWN_REGISTERS_H
