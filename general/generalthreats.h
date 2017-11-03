#ifndef GENERALTHREATS_H
#define GENERALTHREATS_H

#include <QString>

class GeneralThreats
{
public:
    GeneralThreats();


    // A1
    bool clickjackingAttack(QString str_website);

    // A2
    bool loginCsrfAttack(QString str_website);

};

extern GeneralThreats g_generalThreatsInstance;

#endif // GENERALTHREATS_H
