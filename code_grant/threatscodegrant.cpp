#include "threatscodegrant.h"

#include "sqlhandler.h"

#include <QList>
#include <QStringList>
#include <QDebug>

ThreatsCodeGrant g_threatsCodeGrantInstance;

ThreatsCodeGrant::ThreatsCodeGrant()
{

}


// A3
/**
 * This function checks if the client secret is sent from any client side code and thus leaked to an attacker
 * Note: The client secret is sent when code is exchanged for an access token which should never be done on client side
 *
 * @brief GeneralThreats::clientSecretLeakage
 * @param str_website
 * @return str_threatDescription
 */
bool ThreatsCodeGrant::clientSecretLeakage(QString str_website)
{
    bool b_isThreat=0;

    // check if code is exchanged for access token on client side
    QList<QStringList> lst_trafficClientSideCodeExchange = g_sqlHandlerInstance.clientExchangeCodeForToken(str_website);

    if(!lst_trafficClientSideCodeExchange.isEmpty())
    {
        b_isThreat = 1;
    }


    return b_isThreat;
}

