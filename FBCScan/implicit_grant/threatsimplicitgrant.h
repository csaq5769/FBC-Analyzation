#ifndef THREATSIMPLICITGRANT_H
#define THREATSIMPLICITGRANT_H

#include <QString>

class ThreatsImplicitGrant
{
public:
    ThreatsImplicitGrant();

    // A1
    bool accessTokenEavesdropping(QString str_website);

};

extern ThreatsImplicitGrant g_threatsImplicitGrantInstance;

#endif // THREATSIMPLICITGRANT_H
