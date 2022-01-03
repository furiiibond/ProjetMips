//
// Created by jcl on 16/12/2021.
//

#ifndef MYOWN_REGISTERS_H
#define MYOWN_REGISTERS_H

#define REGISTER_INPUT_SIZE 34 // 33 emplacement mémoires avec adresse et valeur en decimales. plus LO et HI
#define RA_REGISTER 31
#define LO_REGISTER 32
#define HI_REGISTER 33

int addInRegister(int registersState[], int index, int value);

int removeFromRegister(int registersState[], int index);

#endif //MYOWN_REGISTERS_H
