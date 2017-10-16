#include "generalthreats.h"

#include "sqlhandler.h"

#include <QStringList>
#include <QList>
#include <QDebug>
#include <QUrl>

GeneralThreats g_generalThreatsInstance;

GeneralThreats::GeneralThreats()
{

}


// A2
/**
 * This functoin checks if proper frame busting mechanisms are used to avoid clickjacking attacks
 * Note that these hold for newer browsers. If old ones are used the only frame busting way is via JavaScript
 * THE FOLLOWING CHECK IS BASED ON THE PAPER 'Busting Frame Busting:a Study of Clickjacking Vulnerabilities on Popular Sites' AND THE OAUTH THREAT MODEL
 * THE PAPER OBSERVED THAT ALL USED JAVA-SCRIPT FRAME BUSTING TECHNIQUES COULD BE DEFEATED
 *      THEY RECCOMEND TO USE BROWSER BASED FRAME BUSTING TECHNIQUES FOR PROPER PROTECTION AGAINST CLICKJACKING
 * THE OAUTH THREAT MODEL ONLY RECOMMENDS THE X-FRAME-OPTION HEADER AS COUNTERMEASURE AGAINST CLICKJACKING
 *
 * @brief ObtainAccessToken::clickjackingAttack
 * @param str_website
 * @return str_threatDescription
 */
bool GeneralThreats::clickjackingAttack(QString str_website)
{
    bool b_isThreat = 0;

    // get homepage and authentication/authorization traffic
    QList<QStringList> lst_clientHomePage = g_sqlHandlerInstance.getClientsIndexPageTraffic(str_website);
    QList<QStringList> lst_clientLoginPage = g_sqlHandlerInstance.getClientsLoginPageTraffic(str_website);
    QStringList strlst_showFacebookLoginDialog = g_sqlHandlerInstance.onLoginWithFacebookButtonKlicked(str_website);
    QStringList strlst_facebookLoginDialogResponse = g_sqlHandlerInstance.onLoginButtonInLoginDialogKlicked(str_website);
    QStringList strlst_showPermissionsDialog = g_sqlHandlerInstance.oauthPermissionsDialog(str_website);
    QStringList strlst_permissionsDialogResponse = g_sqlHandlerInstance.onAcceptPermissionsInPermissionsDialogKlicked(str_website);
    QStringList strlst_clientWebsite = g_sqlHandlerInstance.redirectToClientWebsite(str_website);

    QList<QStringList> lst_oauthFlow;

    if(!lst_clientHomePage.isEmpty())
    {
        // add home page traffic to oauth flow list
        for(int i=0; i<lst_clientHomePage.size(); i++)
        {
            lst_oauthFlow.append(lst_clientHomePage.at(i));
        }
    }

    if(!lst_clientLoginPage.isEmpty())
    {
        // add login site traffic to oauth flow list
        for(int i=0; i<lst_clientLoginPage.size(); i++)
        {
            lst_oauthFlow.append(lst_clientLoginPage.at(i));
        }
    }

    // append traffic of all other sites belonging to oauth flow
    lst_oauthFlow << strlst_showFacebookLoginDialog << strlst_facebookLoginDialogResponse << strlst_showPermissionsDialog << strlst_permissionsDialogResponse << strlst_clientWebsite;

    bool b_xFrameOptionsFound = 0, b_isXFrameThreat = 0, b_cspFound = 0, b_cspThreat = 0;
    if(!lst_oauthFlow.isEmpty())
    {
        for(int i=0; i<lst_oauthFlow.size(); i++)
        {
            // search for x-frame-options and/or csp frame-ancestors is response header field
            if(!lst_oauthFlow.at(i).isEmpty())
            {
                QString str_responseFields = lst_oauthFlow.at(i).at(6);
                QStringList strlst_checkResponseFields = str_responseFields.split(" || ");

                b_xFrameOptionsFound = 0, b_cspFound = 0;
                for(int j=0; j<strlst_checkResponseFields.size(); j++)
                {
                    if(strlst_checkResponseFields.at(j).startsWith("X-Frame-Options", Qt::CaseInsensitive))
                    {
                        b_xFrameOptionsFound = 1;

                        // check for value
                        QString str_frameOptionsValue = strlst_checkResponseFields.at(j);
                        str_frameOptionsValue = str_frameOptionsValue.remove(0, 16).trimmed();

                        if(!(str_frameOptionsValue == "DENY" || str_frameOptionsValue == "SAMEORIGIN"))
                        {
                            b_isXFrameThreat = 1;
                        }
                    }

                    if(strlst_checkResponseFields.at(j).startsWith("Content-Security-Policy", Qt::CaseInsensitive))
                    {
                        b_cspFound = 1;

                        // check for frame-ancestor option
                        QString str_cspValue = strlst_checkResponseFields.at(j);
                        str_cspValue = str_cspValue.remove(0, 23).trimmed();

                        if(!(str_cspValue.contains("frame-ancestors 'none'") || str_cspValue.contains("frame-ancestors 'self'")))
                        {
                            b_cspThreat = 1;
                        }
                    }
                }

                if(!b_xFrameOptionsFound)
                {
                    b_isXFrameThreat = 1;
                }

                if(!b_cspFound)
                {
                    b_cspThreat = 1;
                }
            }
        }
    }

    if(b_isXFrameThreat && b_cspThreat)
    {
        b_isThreat = 1;
    }

    return b_isThreat;
}

// A3
/**
 * This function checks wheter the state parameter offered by Facebook Login to prevent CSRF attacks is used properly
 *
 * @brief GeneralThreats::loginCsrfAttack
 * @param str_website
 * @return str_threatDescription
 */
bool GeneralThreats::loginCsrfAttack(QString str_website)
{
    bool b_isThreat = 0;

    // get oauth flow
    QStringList strlst_showPermissionsDialog = g_sqlHandlerInstance.oauthPermissionsDialog(str_website);
    QStringList strlst_permissionsDialogResponse = g_sqlHandlerInstance.onAcceptPermissionsInPermissionsDialogKlicked(str_website);
    QStringList strlst_clientWebsite = g_sqlHandlerInstance.redirectToClientWebsite(str_website);

    QString str_stateParam;
    bool b_stateParamPermissionsDialog = 0, b_stateParamPermissionsResponse = 0, b_stateParamClientRedirect = 0;
    if(!strlst_showPermissionsDialog.isEmpty())
    {
        QString str_permissionsRequestContent = strlst_showPermissionsDialog.at(4);
        QStringList strlst_checkPermissionsRequestContent = str_permissionsRequestContent.split(" || ");

        for(int i=0; i<strlst_checkPermissionsRequestContent.size(); i++)
        {
            if(strlst_checkPermissionsRequestContent.at(i).startsWith("state"))
            {
                str_stateParam = strlst_checkPermissionsRequestContent.at(i);
                str_stateParam = str_stateParam.remove(0, 6).trimmed();

                break;
            }
        }

        if(!str_stateParam.isEmpty())
        {
            b_stateParamPermissionsDialog = 1;
        }
    }

    if(b_stateParamPermissionsDialog)
    {
        if(!strlst_permissionsDialogResponse.isEmpty())
        {
            QString str_permissionsResponseRequestContent = strlst_permissionsDialogResponse.at(4);
            QStringList strlst_checkPermissionsResponseRequestContent = str_permissionsResponseRequestContent.split(" || ");

            // check if same state param sent in permissions dialog response
            for(int i=0; i<strlst_checkPermissionsResponseRequestContent.size(); i++)
            {
                if(strlst_checkPermissionsResponseRequestContent.at(i).startsWith("encoded_state"))
                {
                    QString str_checkEncodedStateMatch = strlst_checkPermissionsResponseRequestContent.at(i);
                    // get encoded state value
                    str_checkEncodedStateMatch = str_checkEncodedStateMatch.remove(0, 14).trimmed();

                    // encode state param sent with permissions dialog request
                    QString str_stateParamEncoded = QString::fromLatin1(QUrl::toPercentEncoding(str_stateParam));

                    // check if values are equal
                    if(str_checkEncodedStateMatch == str_stateParamEncoded)
                    {
                        b_stateParamPermissionsResponse = 1;

                        break;
                    }

                }
            }

        }

        if(!strlst_clientWebsite.isEmpty())
        {
            QString str_clientRedirectRequestContent = strlst_clientWebsite.at(4);
            QStringList strlst_checkClientRedirectRequestContent = str_clientRedirectRequestContent.split(" || ");

            // check if same state param sent with client redirect
            for(int i=0; i<strlst_checkClientRedirectRequestContent.size(); i++)
            {
                if(strlst_checkClientRedirectRequestContent.at(i).startsWith("state"))
                {
                    QString str_checkStateMatch = strlst_checkClientRedirectRequestContent.at(i);
                    // get state value
                    str_checkStateMatch = str_checkStateMatch.remove(0, 6).trimmed();

                    // check if state values are equal
                    if(str_checkStateMatch == str_stateParam)
                    {
                        b_stateParamClientRedirect = 1;

                        break;
                    }
                }
            }
        }

        if(!strlst_showPermissionsDialog.isEmpty() && !strlst_permissionsDialogResponse.isEmpty() && !strlst_clientWebsite.isEmpty())
        {
            if(!(b_stateParamPermissionsDialog && b_stateParamPermissionsResponse && b_stateParamClientRedirect))
            {
                b_isThreat = 1;
            }
        }
    }
    else
    {
        // check if no state param in permissions dialog was found or if there was no permissions dialog request at all
        if(!strlst_showPermissionsDialog.isEmpty())
        {
            b_isThreat = 1;
        }
    }


    return b_isThreat;
}
