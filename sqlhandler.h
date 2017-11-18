#ifndef SQLHANDLER_H
#define SQLHANDLER_H

#include <QString>
#include <QList>

class SqlHandler
{
public:
    SqlHandler();



    /* get necessary data for oauth traffic queries */

    // rp starting page
    QString getUrlClientIndex(QString str_website); // referer of client login page
    QStringList getClientIndexPage(QString str_website);

    // rp login page
    int getIdClientLoginPage(QString str_website); // referer of login dialog
    QString getRefererOfLoginDialog(QString str_website); // login page of client
    QStringList getClientLoginPage(QString str_website);

    // data regarding fb login dialog
    int getIdFbLoginDialog(QString str_website);
    QString getUrlLoginDialog(QString str_website);

    // data regarding fb permissions dialog
    int getIdPermissionsDialog(QString str_website);
    QString getUrlPermissionsDialog(QString str_website);


    /* get necessary oauth fields */

    // client_id
    QString getClientId(QString str_website);

    // response_type
    QString getAuthFlow(QString str_website);

    // redirect_uri
    QString getRedirectUri(QString str_website);


    /* check for sdk usage */

    bool checkJSSdkUsage(QString str_website);

    bool checkPHPSdkUsage(QString str_website);


    /* trace oauth credentials from their origin */

    QList<QStringList> traceAccessToken(QString str_website);

    QList<QStringList> traceAuthorizationCode(QString str_website);


    /* fb oauth flow */

    // 1
    // on login with facebook button clicked
    QStringList onLoginWithFacebookButtonKlicked(QString str_website);

    // 2
    // user login in with fb credentials -> send fb login credentials (authentication)
    QStringList onLoginButtonInLoginDialogKlicked(QString str_website);

    // 3
    // fb login permissions dialog -> here oauth is initiated (authorization)
    QStringList oauthPermissionsDialog(QString str_website);

    // if use is not directly redirected to rp login site when permissions are accepted i. e. if rp needs further athorization after fb oauth authorization
    QString getRedirectLocationForPermissionsDialog(QString str_website);

    // 4
    // accept permissions
    QStringList onAcceptPermissionsInPermissionsDialogKlicked(QString str_website);

    // 5
    // fb dialog response -> go to redirect uri
    QStringList redirectToClientWebsite(QString str_website);

    QStringList followRedirectUri(QString str_website);


    /* error check queries */

    // exchange code for access token on client side (error)
    QList<QStringList> clientExchangeCodeForToken(QString str_website);

    // make api calls with access token on client side
    QList<QStringList> clientApiCalls(QString str_website);

    // rp set token cookie via response header
    bool checkSetTokenCookie(QString str_website);

};

extern SqlHandler g_sqlHandlerInstance;

#endif // SQLHANDLER_H
