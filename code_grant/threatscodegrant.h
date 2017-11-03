#ifndef THREATSCODEGRANT_H
#define THREATSCODEGRANT_H

#include <QString>

class ThreatsCodeGrant
{
public:
    ThreatsCodeGrant();

    // A3
    bool clientSecretLeakage(QString str_website);
};

extern ThreatsCodeGrant g_threatsCodeGrantInstance;

#endif // THREATSCODEGRANT_H
