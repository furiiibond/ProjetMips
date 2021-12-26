//
// Created by jcl on 23/12/2021.
//

#ifndef MYOWN_INSTRUCTIONSEXECUTION_H
#define MYOWN_INSTRUCTIONSEXECUTION_H

int showRegisterStates(int registersState[]);

int processInstructions(struct assemblerInput *opInputs, int nbInputs, struct index *indexs, int memoryState[],
                        int registersState[]);

#endif //MYOWN_INSTRUCTIONSEXECUTION_H
