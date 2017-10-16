#include "sqlhandler.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QStringList>
#include <QDebug>

SqlHandler g_sqlHandlerInstance;

SqlHandler::SqlHandler()
{

}


/**
 * This function returns the URL of the Facebook login dialog
 *
 * @brief SqlHandler::getUrlLoginDialog
 * @param str_website
 * @return str_loginUrl
 *         A QString containing the login url or an empty QString if the login url was not found
 */
QString SqlHandler::getUrlLoginDialog(QString str_website)
{
    QString str_loginUrl;
    int inr_idPermissionsDialog = SqlHandler::getIdPermissionsDialog(str_website);

    if(inr_idPermissionsDialog != 0)
    {
        QString str_tableName = "`FBCTraffic_"+str_website+"_1`";

        // pointer to database
        QSqlDatabase::database();

        // query url of login dialog
        QSqlQuery queryLoginUrl("SELECT * FROM "+str_tableName+" WHERE request_method LIKE 'GET https://www.facebook.com/login.php%' AND id<"+QString::number(inr_idPermissionsDialog));
        // determine login url
        while(queryLoginUrl.next())
        {
            str_loginUrl = queryLoginUrl.value("request_method").toString();

        }

        if(!str_loginUrl.isEmpty())
        {
            str_loginUrl = str_loginUrl.remove(0, 3).trimmed();
            int inr_indexEndOfUrl = str_loginUrl.indexOf(' ');
            str_loginUrl.truncate(inr_indexEndOfUrl);
        }
    }

    return str_loginUrl;
}

/**
 * This function returns the id of the Facebook login dialog
 *
 * @brief SqlHandler::getIdFbLoginDialog
 * @param str_website
 * @return inr_idLoginDialog
 *         An integer holding the id of the login dialog request or 0 if the request was not found
 */
int SqlHandler::getIdFbLoginDialog(QString str_website)
{
    QString str_loginDialogUrl = SqlHandler::getUrlLoginDialog(str_website);

    int inr_idLoginDialog = 0;
    if(!str_loginDialogUrl.isEmpty())
    {
        QString str_tableName = "`FBCTraffic_"+str_website+"_1`";

        // pointer to database
        QSqlDatabase::database();

        //query id of login dialog
        QSqlQuery queryId("SELECT * FROM "+str_tableName+" WHERE request_method LIKE '%"+str_loginDialogUrl+"%'");

        while(queryId.next())
        {
            inr_idLoginDialog = queryId.value("id").toInt();
        }
    }

    return inr_idLoginDialog;
}

/**
 * This function returns the referrer of the Facebook login dialog, usually the login page of the clients website
 *
 * @brief SqlHandler::getRefererOfLoginDialog
 * @param str_website
 * @return str_loginReferer
 *         A QString containing the clients login page or homepage (referer of the facebook login dialog) or an empty QString if the page was not found
 */
QString SqlHandler::getRefererOfLoginDialog(QString str_website) // clients login page
{
    QString str_loginDialogUrl = SqlHandler::getUrlLoginDialog(str_website);

    QString str_loginReferer;
    if(!str_loginDialogUrl.isEmpty())
    {
        QString str_tableName = "`FBCTraffic_"+str_website+"_1`";

        // pointer to database
        QSqlDatabase::database();

        // query login referer
        QSqlQuery queryRefererLoginDialog("SELECT * FROM "+str_tableName+" WHERE request_method LIKE '%"+str_loginDialogUrl+"%'");
        // determine login referer
        while(queryRefererLoginDialog.next())
        {
            QString str_fieldsLoginCall = queryRefererLoginDialog.value("request_fields").toString();

            QStringList strlst_loginDialogParameters = str_fieldsLoginCall.split(" || ");

            for(int i=0; i<strlst_loginDialogParameters.size(); i++)
            {
                if(strlst_loginDialogParameters.at(i).startsWith("referer", Qt::CaseInsensitive))
                {
                    str_loginReferer = strlst_loginDialogParameters.at(i);
                    break;
                }
            }
        }

        if(!str_loginReferer.isEmpty())
        {
            str_loginReferer = str_loginReferer.remove(0, 8).trimmed();
        }
    }

    return str_loginReferer;
}

/**
 * This function returns the id of the clients login page request/response
 *
 * @brief SqlHandler::getIdClientLoginPage
 * @param str_website
 * @return inr_idLoginPage
 *         An integer holding the id of the clients login page or 0 if the request was not found
 */
int SqlHandler::getIdClientLoginPage(QString str_website)
{
    QString str_loginPageUrl = SqlHandler::getRefererOfLoginDialog(str_website);
    int inr_idFbLoginDialog = SqlHandler::getIdFbLoginDialog(str_website);

    int inr_idLoginPage = 0;
    if(!str_loginPageUrl.isEmpty() && inr_idFbLoginDialog!=0)
    {
        QString str_tableName = "`FBCTraffic_"+str_website+"_1`";

        // pointer to database
        QSqlDatabase::database();

        //query id of login dialog
        QSqlQuery queryId("SELECT * FROM "+str_tableName+" WHERE request_method LIKE '%"+str_loginPageUrl+"%' AND id<"+QString::number(inr_idFbLoginDialog)+" AND response_method LIKE '<< 2%'");

        while(queryId.next())
        {
            inr_idLoginPage = queryId.value("id").toInt();
        }
    }

    return inr_idLoginPage;
}

/**
 * This function returns the url of the clients home page
 *
 * @brief SqlHandler::getUrlClientIndex
 * @param str_website
 * @return str_urlclientsIndexPage
 *         A QString containing the url of the clients homepage or an empty QString if the request was not found
 */
QString SqlHandler::getUrlClientIndex(QString str_website)
{
    QString str_clientsLoginPage = SqlHandler::getRefererOfLoginDialog(str_website);
    int inr_idFbLoginDialog = SqlHandler::getIdFbLoginDialog(str_website);

    QString str_urlClientsIndexPage;
    if(!str_clientsLoginPage.isEmpty() && inr_idFbLoginDialog != 0)
    {
        QString str_tableName = "`FBCTraffic_"+str_website+"_1`";

        // pointer to database
        QSqlDatabase::database();

        // query index url
        QSqlQuery queryIndex("SELECT * FROM "+str_tableName+" WHERE request_method LIKE '%"+str_clientsLoginPage+"%' AND id<"+QString::number(inr_idFbLoginDialog)+" AND response_method LIKE '<< 2%'");
        // determine index url by searching for referer
        while(queryIndex.next())
        {
            QString str_fieldsClientsLoginPage = queryIndex.value("request_fields").toString();
            QStringList strlst_checkFieldsClientsLoginPage = str_fieldsClientsLoginPage.split(" || ");

            for(int i=0; i<strlst_checkFieldsClientsLoginPage.size(); i++)
            {
                if(strlst_checkFieldsClientsLoginPage.at(i).startsWith("referer", Qt::CaseInsensitive))
                {
                    str_urlClientsIndexPage = strlst_checkFieldsClientsLoginPage.at(i);
                }
            }
        }

        str_urlClientsIndexPage = str_urlClientsIndexPage.remove(0, 8).trimmed();
    }

    return str_urlClientsIndexPage;
}

/**
 * This function returns the URL of the Facebook permissions dialog
 *
 * @brief SqlHandler::getUrlPermissionsDialog
 * @param str_website
 * @return str_permissionsUrl
 *         A QString containing the url of the facebook permission dialog or an empty QString if the request was not found
 */
QString SqlHandler::getUrlPermissionsDialog(QString str_website)
{
    // query url of permissions dialog
    QString str_loginUrl = SqlHandler::getUrlLoginDialog(str_website);

    QString str_permissionsUrl;
    if(!str_loginUrl.isEmpty())
    {
        QString str_tableName = "`FBCTraffic_"+str_website+"_1`";

        // pointer to database
        QSqlDatabase::database();

        QSqlQuery queryPermissionsUrl("SELECT * FROM "+str_tableName+" WHERE request_method LIKE 'GET https://www.facebook.com/%/dialog/oauth%' AND request_fields LIKE '%referer: "+str_loginUrl+"%'");
        // determine permissions dialog url
        while(queryPermissionsUrl.next())
        {
            str_permissionsUrl = queryPermissionsUrl.value("request_method").toString();

            str_permissionsUrl = str_permissionsUrl.remove(0, 3).trimmed();
            int inr_indexEndOfUrl = str_permissionsUrl.indexOf(' ');
            str_permissionsUrl.truncate(inr_indexEndOfUrl);
        }
    }

    return str_permissionsUrl;
}

/**
 * This function returns the id of the Facebook permission dialog
 *
 * @brief SqlHandler::getIdPermissionsDialog
 * @param str_website
 * @return inr_idPermissionsDialog
 */
int SqlHandler::getIdPermissionsDialog(QString str_website)
{
    int inr_idPermissionsDialog = 0;
    QString str_tableName = "`FBCTraffic_"+str_website+"_1`";

    // pointer to database
    QSqlDatabase::database();

    QSqlQuery queryPermissionsDialogId("SELECT * FROM "+str_tableName+" WHERE request_method LIKE 'GET https://www.facebook.com/%/dialog/oauth%' AND request_fields LIKE '%referer: https://www.facebook.com/login.php%'");

    // determine permissions dialog url
    while(queryPermissionsDialogId.next())
    {
        inr_idPermissionsDialog = queryPermissionsDialogId.value("id").toInt();
    }

    return inr_idPermissionsDialog;
}

/**
 * This function returns the redirect uri to the clients website after authorization process
 *
 * @brief SqlHandler::getRedirectUri
 * @param str_website
 * @return str_redirectUri
 *         A QString containing the redirect uri of the client or an empty QString if the request was not found
 */
QString SqlHandler::getRedirectUri(QString str_website)
{
    QStringList strlst_trafficPermissionsDialog = SqlHandler::oauthPermissionsDialog(str_website);

    QString str_redirectUri;
    if(!strlst_trafficPermissionsDialog.isEmpty())
    {
        QString str_requestContentPermissionsDialog = strlst_trafficPermissionsDialog.at(4);
        QStringList strlst_checkForRedirectUri = str_requestContentPermissionsDialog.split(" || ");

        // search for redirect uri
        for(int i=0; i<strlst_checkForRedirectUri.size(); i++)
        {
            if(strlst_checkForRedirectUri.at(i).startsWith("redirect_uri", Qt::CaseInsensitive))
            {
                // filter url
                str_redirectUri = strlst_checkForRedirectUri.at(i);
                str_redirectUri = str_redirectUri.remove(0, 13).trimmed();

                break;
            }
        }
    }

    return str_redirectUri;
}

/**
 * This function returns the authorization flow
 *
 * @brief SqlHandler::getAuthFlow
 * @param str_website
 * @return str_authFlow
 *         A QString containing the used authorization flow (code or token) or an empty QString if the response_type parameter was not specified
 */
QString SqlHandler::getAuthFlow(QString str_website)
{
    QString str_loginUrl = SqlHandler::getUrlLoginDialog(str_website);

    QString str_authFlow;
    if(!str_loginUrl.isEmpty())
    {
        QString str_tableName = "`FBCTraffic_"+str_website+"_1`";

        // pointer to database
        QSqlDatabase::database();

        // query response type
        QSqlQuery queryAuthFlow("SELECT * FROM "+str_tableName+" WHERE request_method LIKE 'GET https://www.facebook.com/%/dialog/oauth%' AND request_fields LIKE '%referer: "+str_loginUrl+"%'");
        // determine response type
        while(queryAuthFlow.next())
        {
            QString str_oauthCall = queryAuthFlow.value("request_content").toString();

            if(!str_oauthCall.isEmpty())
            {
                QStringList strlst_oauthCallParameters = str_oauthCall.split(" || ");

                for(int i=0; i<strlst_oauthCallParameters.size(); i++)
                {
                    if(strlst_oauthCallParameters.at(i).startsWith("response_type", Qt::CaseInsensitive))
                    {
                        str_authFlow = strlst_oauthCallParameters.at(i);
                        break;
                    }
                }
            }

            if(!str_authFlow.isEmpty())
            {
                break;
            }
        }

        str_authFlow = str_authFlow.remove(0, 14).trimmed();
    }

    return str_authFlow;
}

/**
 * This function returns the clients public id
 *
 * @brief SqlHandler::getClientId
 * @param str_website
 * @return str_clientId
 *         A QString holding the clients app id or an empty QString if the id was not found
 */
QString SqlHandler::getClientId(QString str_website)
{
    QStringList strlst_trafficPermissionsDialog = SqlHandler::oauthPermissionsDialog(str_website);

    QString str_clientId;
    if(!strlst_trafficPermissionsDialog.isEmpty())
    {
        QString str_searchForClientId = strlst_trafficPermissionsDialog.at(4);
        QStringList strlst_searForClientId = str_searchForClientId.split(" || ");

        for(int i=0; i<strlst_searForClientId.size(); i++)
        {
            if(strlst_searForClientId.at(i).startsWith("client_id", Qt::CaseInsensitive) || strlst_searForClientId.at(i).startsWith("app_id", Qt::CaseInsensitive))
            {
                str_clientId = strlst_searForClientId.at(i);
                break;
            }
        }

        if(str_clientId.startsWith("client_id", Qt::CaseInsensitive))
        {
            str_clientId = str_clientId.remove(0, 10).trimmed();
        }
        else if(str_clientId.startsWith("app_id", Qt::CaseInsensitive))
        {
            str_clientId = str_clientId.remove(0, 7).trimmed();
        }
    }

    return str_clientId;
}

/**
 * This function returns the location where the browser is redirected to in case the clients website needs further authorization means after the Facebook OAuth authorization
 *
 * @brief SqlHandler::getRedirectLocationForPermissionsDialog
 * @param str_website
 * @return str_locationUrl
 *         A QString containing the url in case of a http redirect response from the facebook permissions dialog or an empty QString if the request was not found
 */
QString SqlHandler::getRedirectLocationForPermissionsDialog(QString str_website)
{
    QStringList strlst_trafficPermissionsDialog = SqlHandler::oauthPermissionsDialog(str_website);

    QString str_locationUrl;
    if(!strlst_trafficPermissionsDialog.isEmpty())
    {
        QString str_checkResponseFields = strlst_trafficPermissionsDialog.at(6);
        QStringList strlst_checkForLocation = str_checkResponseFields.split(" || ");

        // search for location url
        for(int i=0; i<strlst_checkForLocation.size(); i++)
        {
            if(strlst_checkForLocation.at(i).startsWith("location", Qt::CaseInsensitive))
            {
                // filter url
                QString str_checkLocationUrl = strlst_checkForLocation.at(i);
                str_checkLocationUrl = str_checkLocationUrl.remove(0,10).trimmed();

                // remove url fragment
                if(str_checkLocationUrl.contains('#'))
                {
                    int inr_indexFragment = str_checkLocationUrl.indexOf('#');
                    str_locationUrl = str_checkLocationUrl.left(inr_indexFragment);
                }
                else
                {
                    str_locationUrl = str_checkLocationUrl;
                }

                break;
            }
        }
    }

    return str_locationUrl;
}


/**
 * This function returns the requests and responses on the clients login page
 *
 * @brief SqlHandler::getClientsLoginPageTraffic
 * @param str_website
 * @return lst_trafficClientLoginPage
 *         A QList of QStringLists holding the traffic concerning the clients login page or an empty QList if no traffic was found
 */
QList<QStringList> SqlHandler::getClientsLoginPageTraffic(QString str_website)
{
    QString str_clientsLoginPageUrl = SqlHandler::getRefererOfLoginDialog(str_website);
    int inr_idFbLoginDialog = SqlHandler::getIdFbLoginDialog(str_website);

    QList<QStringList> lst_trafficClientLoginPage;
    if(!str_clientsLoginPageUrl.isEmpty() && inr_idFbLoginDialog != 0)
    {
        QString str_id, str_localhostId, str_requestMethod, str_requestFields, str_requestContent, str_responseMethod, str_responseFields, str_responseContent;
        QStringList strlst_traffic;

        QString str_tableName = "`FBCTraffic_"+str_website+"_1`";

        // pointer to database
        QSqlDatabase::database();
        QSqlQuery queryTraffic("SELECT * FROM "+str_tableName+" WHERE request_method LIKE '%"+str_clientsLoginPageUrl+"%' AND id<"+QString::number(inr_idFbLoginDialog)+" AND response_method LIKE '<< 2%'");

        // query traffic
        while(queryTraffic.next())
        {
            str_id = queryTraffic.value("id").toString();
            str_localhostId = queryTraffic.value("localhost_id").toString();
            str_requestMethod = queryTraffic.value("request_method").toString();
            str_requestFields = queryTraffic.value("request_fields").toString();
            str_requestContent = queryTraffic.value("request_content").toString();
            str_responseMethod = queryTraffic.value("response_method").toString();
            str_responseFields = queryTraffic.value("response_fields").toString();
            str_responseContent = queryTraffic.value("response_content").toString();

            strlst_traffic << str_id << str_localhostId << str_requestMethod << str_requestFields << str_requestContent << str_responseMethod << str_responseFields << str_responseContent;

            // if no result was found make list empty
            strlst_traffic.removeAll("");

            if(!strlst_traffic.isEmpty())
            {
                lst_trafficClientLoginPage.append(strlst_traffic);
                strlst_traffic.clear();
            }
        }
    }

    return lst_trafficClientLoginPage;
}

/**
 * This function returns the requests and responses of the clients homepage
 *
 * @brief SqlHandler::getClientsIndexPageTraffic
 * @param str_website
 * @return lst_trafficClientIndexPage
 *         A QList of QStringLists holding the traffic concerning the clients homepage or an empty QList if no traffic was found
 */
QList<QStringList> SqlHandler::getClientsIndexPageTraffic(QString str_website)
{
    QString str_clientsIndexPageUrl = SqlHandler::getUrlClientIndex(str_website);
    int inr_idClientsLoginPage = SqlHandler::getIdClientLoginPage(str_website);

    QList<QStringList> lst_trafficClientIndexPage;
    if(!str_clientsIndexPageUrl.isEmpty() && inr_idClientsLoginPage != 0)
    {
        QString str_id, str_localhostId, str_requestMethod, str_requestFields, str_requestContent, str_responseMethod, str_responseFields, str_responseContent;
        QStringList strlst_traffic;

        QString str_tableName = "`FBCTraffic_"+str_website+"_1`";

        // pointer to database
        QSqlDatabase::database();

        QSqlQuery queryTraffic("SELECT * FROM "+str_tableName+" WHERE request_method LIKE '%"+str_clientsIndexPageUrl+"%' AND id<"+QString::number(inr_idClientsLoginPage)+" AND request_fields NOT LIKE '%referer%'");

        // query traffic
        while(queryTraffic.next())
        {
            str_id = queryTraffic.value("id").toString();
            str_localhostId = queryTraffic.value("localhost_id").toString();
            str_requestMethod = queryTraffic.value("request_method").toString();
            str_requestFields = queryTraffic.value("request_fields").toString();
            str_requestContent = queryTraffic.value("request_content").toString();
            str_responseMethod = queryTraffic.value("response_method").toString();
            str_responseFields = queryTraffic.value("response_fields").toString();
            str_responseContent = queryTraffic.value("response_content").toString();

            strlst_traffic << str_id << str_localhostId << str_requestMethod << str_requestFields << str_requestContent << str_responseMethod << str_responseFields << str_responseContent;

            // if no result was found make list empty
            strlst_traffic.removeAll("");

            if(!strlst_traffic.isEmpty())
            {
                lst_trafficClientIndexPage.append(strlst_traffic);
                strlst_traffic.clear();
            }
        }
    }

    return lst_trafficClientIndexPage;
}


/**
 * This function returns all requests which contain the access token
 *
 * @brief SqlHandler::traceAccessToken
 * @param str_website
 * @return lst_accessTokenTraffic
 *         A QList of QStringLists holding the traffic where an access token is sent along or an empty QList if no traffic was found
 */
QList<QStringList> SqlHandler::traceAccessToken(QString str_website)
{
    QStringList strlst_accessTokenOrigin = SqlHandler::onAcceptPermissionsInPermissionsDialogKlicked(str_website);

    QList<QStringList> lst_accessTokenTraffic;
    if(!strlst_accessTokenOrigin.isEmpty())
    {
        QStringList strlst_resultingTraffic;
        QString str_id, str_localhostId, str_requestMethod, str_requestFields, str_requestContent, str_responseMethod, str_responseFields, str_responseContent;

        QString str_tableName = "`FBCTraffic_"+str_website+"_1`";

        // pointer to database
        QSqlDatabase::database();


        // get access token value
        QString str_accessTokenOriginResponseContent = strlst_accessTokenOrigin.at(7);
        QStringList strlst_checkAccessTokenOriginResponseContent = str_accessTokenOriginResponseContent.split(" || ");
        QString str_accessTokenElementOfResponse = strlst_checkAccessTokenOriginResponseContent.at(7);
        QStringList strlst_getAccessToken = str_accessTokenElementOfResponse.split('&');

        QString str_accessTokenValue;
        for(int i=0; i<strlst_getAccessToken.size(); i++)
        {
            if(strlst_getAccessToken.at(i).startsWith("access_token", Qt::CaseInsensitive))
            {
                str_accessTokenValue = strlst_getAccessToken.at(i);
                str_accessTokenValue = str_accessTokenValue.remove(0, 13).trimmed();
            }
        }

        if(!str_accessTokenValue.isEmpty())
        {
            QSqlQuery queryTokenTraffic("SELECT * FROM "+str_tableName+" WHERE request_content LIKE '%"+str_accessTokenValue+"%'");

            // query access token traffic
            while(queryTokenTraffic.next())
            {
                str_id = queryTokenTraffic.value("id").toString();
                str_localhostId = queryTokenTraffic.value("localhost_id").toString();
                str_requestMethod = queryTokenTraffic.value("request_method").toString();
                str_requestFields = queryTokenTraffic.value("request_fields").toString();
                str_requestContent = queryTokenTraffic.value("request_content").toString();
                str_responseMethod = queryTokenTraffic.value("response_method").toString();
                str_responseFields = queryTokenTraffic.value("response_fields").toString();
                str_responseContent = queryTokenTraffic.value("response_content").toString();

                strlst_resultingTraffic << str_id << str_localhostId << str_requestMethod << str_requestFields << str_requestContent << str_responseMethod << str_responseFields << str_responseContent;

                // if no result was found make list empty
                strlst_resultingTraffic.removeAll("");

                if(!strlst_resultingTraffic.isEmpty())
                {
                    lst_accessTokenTraffic.append(strlst_resultingTraffic);
                    strlst_resultingTraffic.clear();
                }
            }
        }
    }

    return lst_accessTokenTraffic;
}


/**
 * This function traces the traffic where the authorization code is sent in the referer header or in the web pages content (trace from origin = from login dialog response)
 * Note that the code could be easily leaked to an attacker if sent in the referer header without SSL
 *
 * @brief SqlHandler::traceAuthorizationCode
 * @param str_website
 * @return lst_authCodeTraffic
 *         A QList of QStringLists holding the traffic where the authorization code is sent along or an empty QList if no traffic was found
 */
QList<QStringList> SqlHandler::traceAuthorizationCode(QString str_website)
{
    QStringList strlst_authCodeOrigin = SqlHandler::onAcceptPermissionsInPermissionsDialogKlicked(str_website);

    QList<QStringList> lst_authCodeTraffic;
    if(!strlst_authCodeOrigin.isEmpty())
    {
        QStringList strlst_resultingTraffic;
        QString str_id, str_localhostId, str_requestMethod, str_requestFields, str_requestContent, str_responseMethod, str_responseFields, str_responseContent;

        QString str_tableName = "`FBCTraffic_"+str_website+"_1`";

        // pointer to database
        QSqlDatabase::database();

        // get code value
        QString str_authCodeOriginResponseContent = strlst_authCodeOrigin.at(7);
        QStringList strlst_checkForCodeElementOfResponse = str_authCodeOriginResponseContent.split(" || ");
        QString str_authCodeElementOfResponse = strlst_checkForCodeElementOfResponse.at(7);

        int inr_indexParams = str_authCodeElementOfResponse.indexOf('?');
        str_authCodeElementOfResponse.remove(0, inr_indexParams+1);

        int inr_indexFragment = str_authCodeElementOfResponse.indexOf('#');
        str_authCodeElementOfResponse.truncate(inr_indexFragment);

        QStringList strlst_getAuthCode = str_authCodeElementOfResponse.split('&');

        QString str_codeValue;
        for(int i=0; i<strlst_getAuthCode.size(); i++)
        {
            if(strlst_getAuthCode.at(i).startsWith("code", Qt::CaseInsensitive))
            {
                str_codeValue = strlst_getAuthCode.at(i);
                str_codeValue = str_codeValue.remove(0, 5).trimmed();
            }
        }

        if(!str_codeValue.isEmpty())
        {
            // check if code is in referer
            QSqlQuery queryCodeTraffic("SELECT * FROM "+str_tableName+" WHERE request_fields LIKE '%"+str_codeValue+"%'");

            // query code traffic
            while(queryCodeTraffic.next())
            {
                str_id = queryCodeTraffic.value("id").toString();
                str_localhostId = queryCodeTraffic.value("localhost_id").toString();
                str_requestMethod = queryCodeTraffic.value("request_method").toString();
                str_requestFields = queryCodeTraffic.value("request_fields").toString();
                str_requestContent = queryCodeTraffic.value("request_content").toString();
                str_responseMethod = queryCodeTraffic.value("response_method").toString();
                str_responseFields = queryCodeTraffic.value("response_fields").toString();
                str_responseContent = queryCodeTraffic.value("response_content").toString();

                strlst_resultingTraffic << str_id << str_localhostId << str_requestMethod << str_requestFields << str_requestContent << str_responseMethod << str_responseFields << str_responseContent;

                // if no result was found make list empty
                strlst_resultingTraffic.removeAll("");

                if(!strlst_resultingTraffic.isEmpty())
                {
                    lst_authCodeTraffic.append(strlst_resultingTraffic);
                    strlst_resultingTraffic.clear();
                }
            }
        }
    }

    return lst_authCodeTraffic;
}


// 1
/**
 * This function returns the request and response information for the Facebook login dialog
 *
 * @brief SqlHandler::onLoginWithFacebookButtonKlicked
 * @param str_website
 * @return strlst_resultingTraffic
 *         A QStringList holding the request for the Facebook login dialog or an empty QStringList if no such request was found
 */
QStringList SqlHandler::onLoginWithFacebookButtonKlicked(QString str_website)
{
    QString str_urlLoginDialog = SqlHandler::getUrlLoginDialog(str_website);

    QStringList strlst_resultingTraffic;
    if(!str_urlLoginDialog.isEmpty())
    {
        QString str_tableName, str_id, str_localhostId, str_requestMethod, str_requestFields, str_requestContent, str_responseMethod, str_responseFields, str_responseContent;

        str_tableName = "`FBCTraffic_"+str_website+"_1`";

        // pointer to database
        QSqlDatabase::database();

        QSqlQuery queryLoginDialog("SELECT * FROM "+str_tableName+" WHERE request_method LIKE '%"+str_urlLoginDialog+"%'");

        while(queryLoginDialog.next())
        {
            str_id = queryLoginDialog.value("id").toString();
            str_localhostId = queryLoginDialog.value("localhost_id").toString();
            str_requestMethod = queryLoginDialog.value("request_method").toString();
            str_requestFields = queryLoginDialog.value("request_fields").toString();
            str_requestContent = queryLoginDialog.value("request_content").toString();
            str_responseMethod = queryLoginDialog.value("response_method").toString();
            str_responseFields = queryLoginDialog.value("response_fields").toString();
            str_responseContent = queryLoginDialog.value("response_content").toString();
        }

        strlst_resultingTraffic << str_id << str_localhostId << str_requestMethod << str_requestFields << str_requestContent << str_responseMethod << str_responseFields << str_responseContent;

        // if no result was found return empty list
        strlst_resultingTraffic.removeAll("");
    }

    return strlst_resultingTraffic;
}

// 2
/**
 * This function returns the request and response information from the users login to Facebook
 *
 * @brief SqlHandler::onLoginButtonInLoginDialogKlicked
 * @param str_website
 * @return strlst_resultingTraffic
 *         A QStringList holding the request for the Facebook login dialog response or an empty QStringList if no such request was found
 */
QStringList SqlHandler::onLoginButtonInLoginDialogKlicked(QString str_website)
{
    QString str_loginUrl = SqlHandler::getUrlLoginDialog(str_website);

    QStringList strlst_resultingTraffic;
    if(!str_loginUrl.isEmpty())
    {
        QString str_id, str_localhostId, str_requestMethod, str_requestFields, str_requestContent, str_responseMethod, str_responseFields, str_responseContent;

        QString str_tableName = "`FBCTraffic_"+str_website+"_1`";

        // pointer to database
        QSqlDatabase::database();

        QSqlQuery queryAuthentication("SELECT * FROM "+str_tableName+" WHERE request_method LIKE 'POST https://www.facebook.com/login.php?%' AND request_fields LIKE '%referer: "+str_loginUrl+"%'");

        while(queryAuthentication.next())
        {
            str_id = queryAuthentication.value("id").toString();
            str_localhostId = queryAuthentication.value("localhost_id").toString();
            str_requestMethod = queryAuthentication.value("request_method").toString();
            str_requestFields = queryAuthentication.value("request_fields").toString();
            str_requestContent = queryAuthentication.value("request_content").toString();
            str_responseMethod = queryAuthentication.value("response_method").toString();
            str_responseFields = queryAuthentication.value("response_fields").toString();
            str_responseContent = queryAuthentication.value("response_content").toString();
        }

        strlst_resultingTraffic << str_id << str_localhostId << str_requestMethod << str_requestFields << str_requestContent << str_responseMethod << str_responseFields << str_responseContent;

        // if no result was found return empty list
        strlst_resultingTraffic.removeAll("");
    }

    return strlst_resultingTraffic;
}


// 3
/**
 * This function returns the request and response for Facebooks permission dialog
 * Note that here client_id, response_type, scope, logger_id, ... can be found
 *
 * @brief SqlHandler::oauthPermissionsDialog
 * @param str_website
 * @return strlst_resultingTraffic
 *         A QStringList holding the request for the Facebook OAuth permission dialog or an empty QStringList if no such request was found
 */
QStringList SqlHandler::oauthPermissionsDialog(QString str_website)
{
    QString str_loginUrl = SqlHandler::getUrlLoginDialog(str_website);

    QStringList strlst_resultingTraffic;
    if(!str_loginUrl.isEmpty())
    {
        QString str_id, str_localhostId, str_requestMethod, str_requestFields, str_requestContent, str_responseMethod, str_responseFields, str_responseContent;

        QString str_tableName = "`FBCTraffic_"+str_website+"_1`";

        // pointer to database
        QSqlDatabase::database();

        QSqlQuery queryPermissionsDialog("SELECT * FROM "+str_tableName+" WHERE request_method LIKE 'GET https://www.facebook.com/%/dialog/oauth%' AND request_fields LIKE '%referer: "+str_loginUrl+"%'");

        while(queryPermissionsDialog.next())
        {
            str_id = queryPermissionsDialog.value("id").toString();
            str_localhostId = queryPermissionsDialog.value("localhost_id").toString();
            str_requestMethod = queryPermissionsDialog.value("request_method").toString();
            str_requestFields = queryPermissionsDialog.value("request_fields").toString();
            str_requestContent = queryPermissionsDialog.value("request_content").toString();
            str_responseMethod = queryPermissionsDialog.value("response_method").toString();
            str_responseFields = queryPermissionsDialog.value("response_fields").toString();
            str_responseContent = queryPermissionsDialog.value("response_content").toString();
        }

        strlst_resultingTraffic << str_id << str_localhostId << str_requestMethod << str_requestFields << str_requestContent << str_responseMethod << str_responseFields << str_responseContent;

        // if no result was found return empty list
        strlst_resultingTraffic.removeAll("");
    }

    return strlst_resultingTraffic;
}

// 4
/**
 * This function returns the request and response from the users acceptance of the requested permissions
 *
 * @brief SqlHandler::onAcceptPermissionsInPermissionsDialogKlicked
 * @param str_website
 * @return strlst_resutltinTraffic
 *         A QStringList holding the request for the Facebook OAuth permission dialog response or an empty QStringList if no such request was found
 */
QStringList SqlHandler::onAcceptPermissionsInPermissionsDialogKlicked(QString str_website)
{
    QString str_permissionsDialogUrl = SqlHandler::getUrlPermissionsDialog(str_website);

    QStringList strlst_resultingTraffic;
    if(!str_permissionsDialogUrl.isEmpty())
    {
        QString str_id, str_localhostId, str_requestMethod, str_requestFields, str_requestContent, str_responseMethod, str_responseFields, str_responseContent;

        QString str_tableName = "`FBCTraffic_"+str_website+"_1`";

        // pointer to database
        QSqlDatabase::database();

        QSqlQuery queryPermissionDialogResponse("SELECT * FROM "+str_tableName+" WHERE request_method LIKE 'POST https://www.facebook.com/%/dialog/oauth/read?dpr=1%' AND request_fields LIKE '%referer: "+str_permissionsDialogUrl+"%'");

        while (queryPermissionDialogResponse.next())
        {
            str_id = queryPermissionDialogResponse.value("id").toString();
            str_localhostId = queryPermissionDialogResponse.value("localhost_id").toString();
            str_requestMethod = queryPermissionDialogResponse.value("request_method").toString();
            str_requestFields = queryPermissionDialogResponse.value("request_fields").toString();
            str_requestContent = queryPermissionDialogResponse.value("request_content").toString();
            str_responseMethod = queryPermissionDialogResponse.value("response_method").toString();
            str_responseFields = queryPermissionDialogResponse.value("response_fields").toString();
            str_responseContent = queryPermissionDialogResponse.value("response_content").toString();
        }

        strlst_resultingTraffic << str_id << str_localhostId << str_requestMethod << str_requestFields << str_requestContent << str_responseMethod << str_responseFields << str_responseContent;

        // if no result was found return empty list
        strlst_resultingTraffic.removeAll("");
    }

    return strlst_resultingTraffic;
}

// 5
/**
 * Thsi functon returns the request and response for the redirection to the clients website
 * Note that here the OAuth credentials code or access token can be found
 *
 * @brief SqlHandler::redirectToClientWebsite
 * @param str_website
 * @return strlst_resultingTraffic
 *         A QStringList holding the request to the redirect uri of the client or an empty QStringList if no such request was found
 */
QStringList SqlHandler::redirectToClientWebsite(QString str_website)
{
    QString str_tableName, str_id, str_localhostId, str_requestMethod, str_requestFields, str_requestContent, str_responseMethod, str_responseFields, str_responseContent;
    QStringList strlst_resultingTraffic;

    str_tableName = "`FBCTraffic_"+str_website+"_1`";

    // pointer to database
    QSqlDatabase::database();


    QStringList strlst_trafficPermissionsAccepted = SqlHandler::onAcceptPermissionsInPermissionsDialogKlicked(str_website);

    if(strlst_trafficPermissionsAccepted.isEmpty())
    {
        QStringList strlst_trafficPermissionsDialog = SqlHandler::oauthPermissionsDialog(str_website);

        if(!strlst_trafficPermissionsDialog.isEmpty())
        {
            QString str_responseMethodPermissionsDialog = strlst_trafficPermissionsDialog.at(5);
            str_responseMethodPermissionsDialog = str_responseMethodPermissionsDialog.remove(0, 2).trimmed();

            if(str_responseMethodPermissionsDialog.startsWith("3"))
            {
                QString str_locationUrl = SqlHandler::getRedirectLocationForPermissionsDialog(str_website);
                int inr_idPermissionsDialog = SqlHandler::getIdPermissionsDialog(str_website);

                if(!str_locationUrl.isEmpty() && inr_idPermissionsDialog!=0)
                {
                    // goto location url
                    QSqlQuery queryLocation("SELECT * FROM "+str_tableName+" WHERE request_method LIKE '%"+str_locationUrl+"%' AND request_fields LIKE '%referer: https://www.facebook.com%' AND response_content LIKE '<!DOCTYPE html%'");

                    while(queryLocation.next())
                    {
                        str_id = queryLocation.value("id").toString();
                        str_localhostId = queryLocation.value("localhost_id").toString();
                        str_requestMethod = queryLocation.value("request_method").toString();
                        str_requestFields = queryLocation.value("request_fields").toString();
                        str_requestContent = queryLocation.value("request_content").toString();
                        str_responseMethod = queryLocation.value("response_method").toString();
                        str_responseFields = queryLocation.value("response_fields").toString();
                        str_responseContent = queryLocation.value("response_content").toString();
                    }

                    strlst_resultingTraffic << str_id << str_localhostId << str_requestMethod << str_requestFields << str_requestContent << str_responseMethod << str_responseFields << str_responseContent;

                    // if no result was found return empty list
                    strlst_resultingTraffic.removeAll("");
                }
            }
        }
    }
    else
    {
        QString str_redirectUri = SqlHandler::getRedirectUri(str_website);

        QString str_idPermissionsAccepted = strlst_trafficPermissionsAccepted.at(0);

        if(!str_redirectUri.isEmpty())
        {
            if(str_redirectUri.startsWith("https://staticxx.facebook.com") || str_redirectUri.startsWith("http://staticxx.facebook.com"))
            {

                QString str_requestContentPermissionsAccepted = strlst_trafficPermissionsAccepted.at(4);
                QStringList strlst_requestContentPermissionsAccepted = str_requestContentPermissionsAccepted.split(" || ");

                QString str_domain;
                for(int i=0; i<strlst_requestContentPermissionsAccepted.size(); i++)
                {
                    if(strlst_requestContentPermissionsAccepted.at(i).startsWith("domain", Qt::CaseInsensitive))
                    {
                        str_domain = strlst_requestContentPermissionsAccepted.at(i);
                        str_domain = str_domain.remove(0, 7).trimmed();
                    }
                }

                QSqlQuery queryStaticxxRedirect("SELECT * FROM "+str_tableName+" WHERE request_method LIKE '%"+str_website+"%' AND id>"+str_idPermissionsAccepted+" AND (request_fields LIKE '%authority: www."+str_website+"%' OR request_fields LIKE '%Host: www."+str_website+"%' OR request_fields LIKE '%authority: "+str_domain+"%' OR request_fields LIKE '%Host: "+str_domain+"%') AND response_method LIKE '<< 200%'  AND response_content LIKE '<!DOCTYPE html%'");

                while(queryStaticxxRedirect.next())
                {
                    str_id = queryStaticxxRedirect.value("id").toString();
                    str_localhostId = queryStaticxxRedirect.value("localhost_id").toString();
                    str_requestMethod = queryStaticxxRedirect.value("request_method").toString();
                    str_requestFields = queryStaticxxRedirect.value("request_fields").toString();
                    str_requestContent = queryStaticxxRedirect.value("request_content").toString();
                    str_responseMethod = queryStaticxxRedirect.value("response_method").toString();
                    str_responseFields = queryStaticxxRedirect.value("response_fields").toString();
                    str_responseContent = queryStaticxxRedirect.value("response_content").toString();

                    break;
                }
            }
            else
            {

                if(!str_redirectUri.isEmpty())
                {
                    // goto redirect uri
                    QSqlQuery queryRedirectUri("SELECT * FROM "+str_tableName+" WHERE request_method LIKE '%"+str_redirectUri+"%' AND request_fields LIKE '%referer: https://www.facebook.com%' AND response_method LIKE '<< 200%' AND id>"+str_idPermissionsAccepted);

                    if(queryRedirectUri.next())
                    {
                        // position query pointer before firs record
                        queryRedirectUri.seek(-1);

                        while(queryRedirectUri.next())
                        {
                            str_id = queryRedirectUri.value("id").toString();
                            str_localhostId = queryRedirectUri.value("localhost_id").toString();
                            str_requestMethod = queryRedirectUri.value("request_method").toString();
                            str_requestFields = queryRedirectUri.value("request_fields").toString();
                            str_requestContent = queryRedirectUri.value("request_content").toString();
                            str_responseMethod = queryRedirectUri.value("response_method").toString();
                            str_responseFields = queryRedirectUri.value("response_fields").toString();
                            str_responseContent = queryRedirectUri.value("response_content").toString();
                        }
                    }
                    else
                    {
                        QSqlQuery queryForRedirectResponse("SELECT * FROM "+str_tableName+" WHERE request_method LIKE '%"+str_redirectUri+"%' AND request_fields LIKE '%referer: https://www.facebook.com%' AND id>"+str_idPermissionsAccepted);
                        QString str_responseFields;

                        while(queryForRedirectResponse.next())
                        {
                            str_responseFields = queryForRedirectResponse.value("response_fields").toString();
                        }

                        // search for location url
                        QStringList strlst_checkResponseFields = str_responseFields.split(" || ");
                        QString str_locationUrlForRedirect;
                        for(int i=0; i<strlst_checkResponseFields.size(); i++)
                        {
                            if(strlst_checkResponseFields.at(i).startsWith("location", Qt::CaseInsensitive))
                            {
                                str_locationUrlForRedirect = strlst_checkResponseFields.at(i);
                                str_locationUrlForRedirect = str_locationUrlForRedirect.remove(0, 9).trimmed();
                            }
                        }

                        // if only location without host is given
                        if(str_locationUrlForRedirect.startsWith('/'))
                        {
                            int inr_indexLocSpec = str_redirectUri.indexOf('/', 11);
                            str_redirectUri.truncate(inr_indexLocSpec);

                            str_redirectUri.append(str_locationUrlForRedirect);
                        }

                        if(!str_locationUrlForRedirect.isEmpty())
                        {
                            QSqlQuery queryLocationForRedirectUri("SELECT * FROM "+str_tableName+" WHERE request_method LIKE '%"+str_locationUrlForRedirect+"%' AND id>"+str_idPermissionsAccepted+" AND response_content LIKE '<!DOCTYPE html%'");

                            while(queryLocationForRedirectUri.next())
                            {
                                str_id = queryLocationForRedirectUri.value("id").toString();
                                str_localhostId = queryLocationForRedirectUri.value("localhost_id").toString();
                                str_requestMethod = queryLocationForRedirectUri.value("request_method").toString();
                                str_requestFields = queryLocationForRedirectUri.value("request_fields").toString();
                                str_requestContent = queryLocationForRedirectUri.value("request_content").toString();
                                str_responseMethod = queryLocationForRedirectUri.value("response_method").toString();
                                str_responseFields = queryLocationForRedirectUri.value("response_fields").toString();
                                str_responseContent = queryLocationForRedirectUri.value("response_content").toString();
                            }
                        }
                    }

                }
            }

            strlst_resultingTraffic << str_id << str_localhostId << str_requestMethod << str_requestFields << str_requestContent << str_responseMethod << str_responseFields << str_responseContent;

            // if no result was found return empty list
            strlst_resultingTraffic.removeAll("");
        }
    }

    return strlst_resultingTraffic;
}

/**
 * This function checks if the code is exchanged for an access token on client side
 * Note that this would be the result of a faulty implementation since API calls with authorization code need to be done on server side
 *
 * @brief SqlHandler::clientExchangeCodeForToken
 * @param str_website
 * @return lst_clientExchangeCalls;
 *         A QList of QStringLists holding the traffic where the RP exchanges an authorization code for an access token on client side or an empty QList if no such traffic was found
 */
QList<QStringList> SqlHandler::clientExchangeCodeForToken(QString str_website)
{
    QList<QStringList> lst_clientExchangeCalls;
    QString str_tableName, str_id, str_localhostId, str_requestMethod, str_requestFields, str_requestContent, str_responseMethod, str_responseFields, str_responseContent;
    QStringList strlst_resultingTraffic;

    str_tableName = "`FBCTraffic_"+str_website+"_1`";

    // pointer to database
    QSqlDatabase::database();

    QSqlQuery queryExchangeCalls("SELECT * FROM "+str_tableName+" WHERE request_method LIKE '%graph.facebook.com/%/oauth/access_token%'");

    while(queryExchangeCalls.next())
    {
        str_id = queryExchangeCalls.value("id").toString();
        str_localhostId = queryExchangeCalls.value("localhost_id").toString();
        str_requestMethod = queryExchangeCalls.value("request_method").toString();
        str_requestFields = queryExchangeCalls.value("request_fields").toString();
        str_requestContent = queryExchangeCalls.value("request_content").toString();
        str_responseMethod = queryExchangeCalls.value("response_method").toString();
        str_responseFields = queryExchangeCalls.value("response_fields").toString();
        str_responseContent = queryExchangeCalls.value("response_content").toString();

        strlst_resultingTraffic << str_id << str_localhostId << str_requestMethod << str_requestFields << str_requestContent << str_responseMethod << str_responseFields << str_responseContent;

        // if no result was found make list empty
        strlst_resultingTraffic.removeAll("");

        if(!strlst_resultingTraffic.isEmpty())
        {
            lst_clientExchangeCalls.append(strlst_resultingTraffic);
            strlst_resultingTraffic.clear();
        }
    }

    return lst_clientExchangeCalls;
}

/**
 * This function checks if API calls are made on client side
 * Note that for such api calls each endpoint needs to tls/ssl protected since otherwise the token could be eavesdropped
 *
 * @brief SqlHandler::clientApiCalls
 * @param str_website
 * @return lst_apiCalls
 *         A QList of QStringLists holding API calls from RPs done on client side or an empty QList if no such requests are found
 */
QList<QStringList> SqlHandler::clientApiCalls(QString str_website)
{
    QList<QStringList> lst_apiCalls;
    QString str_tableName, str_indexRequest, str_id, str_localhostId, str_requestMethod, str_requestFields, str_requestContent, str_responseMethod, str_responseFields, str_responseContent;
    QStringList strlst_resultingTraffic;

    str_tableName = "`FBCTraffic_"+str_website+"_1`";

    // pointer to database
    QSqlDatabase::database();

    QSqlQuery queryApiCalls("SELECT * FROM "+str_tableName+" WHERE request_method LIKE '%graph.facebook.com/%/me%'");

    while(queryApiCalls.next())
    {
        str_id = queryApiCalls.value("id").toString();
        str_localhostId = queryApiCalls.value("localhost_id").toString();
        str_requestMethod = queryApiCalls.value("request_method").toString();
        str_requestFields = queryApiCalls.value("request_fields").toString();
        str_requestContent = queryApiCalls.value("request_content").toString();
        str_responseMethod = queryApiCalls.value("response_method").toString();
        str_responseFields = queryApiCalls.value("response_fields").toString();
        str_responseContent = queryApiCalls.value("response_content").toString();

        strlst_resultingTraffic << str_indexRequest << str_id << str_localhostId << str_requestMethod << str_requestFields << str_requestContent << str_responseMethod << str_responseFields << str_responseContent;

        // if no result was found make list empty
        strlst_resultingTraffic.removeAll("");

        if(!strlst_resultingTraffic.isEmpty())
        {
            lst_apiCalls.append(strlst_resultingTraffic);
            strlst_resultingTraffic.clear();
        }
    }

    return lst_apiCalls;
}
