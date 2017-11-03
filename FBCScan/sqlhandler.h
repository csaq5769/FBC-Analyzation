#ifndef SQLHANDLER_H
#define SQLHANDLER_H

#include <QString>
#include <QList>

class SqlHandler
{
public:
    SqlHandler();

    QString getUrlLoginDialog(QString str_website);

    int getIdFbLoginDialog(QString str_website);

    QString getRefererOfLoginDialog(QString str_website); // login page of client

    int getIdClientLoginPage(QString str_website); // referer of login dialog

    QString getUrlClientIndex(QString str_website); // referer of client login page

    QString getUrlPermissionsDialog(QString str_website);

    int getIdPermissionsDialog(QString str_website);

    QString getRedirectUri(QString str_website);

    QString getAuthFlow(QString str_website);

    QString getClientId(QString str_website);

    QList<QStringList> getClientsLoginPageTraffic(QString str_website);

    QList<QStringList> getClientsIndexPageTraffic(QString str_website);

    QList<QStringList> traceAccessToken(QString str_website);

    QList<QStringList> traceAuthorizationCode(QString str_website);

    // if rp needs further athorization after fb oauth authorization
    QString getRedirectLocationForPermissionsDialog(QString str_website);

    // 1
    // on login with facebook button clicked
    QStringList onLoginWithFacebookButtonKlicked(QString str_website);

    // 2
    // user login in with fb credentials -> send fb login credentials (authentication)
    QStringList onLoginButtonInLoginDialogKlicked(QString str_website);

    // 3
    // fb login permissions dialog -> here oauth is initiated (authorization)
    QStringList oauthPermissionsDialog(QString str_website);

    // 4
    // accept permissions
    QStringList onAcceptPermissionsInPermissionsDialogKlicked(QString str_website);

    // 5
    // fb dialog response -> go to redirect uri //NOTE that here code or access token can be found
    QStringList redirectToClientWebsite(QString str_website);

    // exchange code for access token on client side (error)
    QList<QStringList> clientExchangeCodeForToken(QString str_website);

    // make api calls with access token on client side
    QList<QStringList> clientApiCalls(QString str_website);


};

extern SqlHandler g_sqlHandlerInstance;

#endif // SQLHANDLER_H
