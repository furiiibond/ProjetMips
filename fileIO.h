//
// Created by jcl on 16/12/2021.
//

#ifndef MYOWN_FILEIO_H
#define MYOWN_FILEIO_H

int readInput(char *fileName, struct assemblerInput *opInputs, struct index *indexs);

int writeResults(char *fileName, struct assemblerInput *opInputs, int nbLine);

void writeStateFile(char *fileInput, int registerState[]);

#endif //MYOWN_FILEIO_H
