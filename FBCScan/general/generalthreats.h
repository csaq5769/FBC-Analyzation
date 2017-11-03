#ifndef GENERALTHREATS_H
#define GENERALTHREATS_H

#include <QString>

class GeneralThreats
{
public:
    GeneralThreats();


    // A2
    bool clickjackingAttack(QString str_website);

    // A3
    bool loginCsrfAttack(QString str_website);

};

extern GeneralThreats g_generalThreatsInstance;

#endif // GENERALTHREATS_H
