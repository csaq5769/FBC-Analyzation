#include "threatsimplicitgrant.h"

#include "sqlhandler.h"

#include <QStringList>
#include <QList>
#include <QDebug>

ThreatsImplicitGrant g_threatsImplicitGrantInstance;

ThreatsImplicitGrant::ThreatsImplicitGrant()
{

}

// A1
/**
 * This function checks if the access token is properly protected on communication between the participating entities
 *
 * @brief GeneralThreats::accessTokenEavesdropping
 * @param str_website
 * @return str_threatDescription
 */
bool ThreatsImplicitGrant::accessTokenEavesdropping(QString str_website)
{
    bool b_isThreat = 0;

    QList<QStringList> lst_accessTokenTraffic = g_sqlHandlerInstance.traceAccessToken(str_website);

    bool b_noTls = 0;
    if(!lst_accessTokenTraffic.isEmpty())
    {
        for(int i=0; i<lst_accessTokenTraffic.size(); i++)
        {
            QStringList strlst_checkTokenTraffic = lst_accessTokenTraffic.at(i);
            QString str_checkRequestConfidentiality = strlst_checkTokenTraffic.at(2);

            int inr_indexHttp = str_checkRequestConfidentiality.indexOf("http");
            str_checkRequestConfidentiality.remove(0, inr_indexHttp);

            if(!str_checkRequestConfidentiality.startsWith("https"))
            {
                b_noTls = 1;
            }
        }
    }

    if(b_noTls)
    {
        b_isThreat = 1;
    }

    return b_isThreat;
}
