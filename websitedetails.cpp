#include "websitedetails.h"
#include "ui_websitedetails.h"

#include "code_grant/threatscodegrant.h"
#include "implicit_grant/threatsimplicitgrant.h"
#include "general/generalthreats.h"
#include "sqlhandler.h"
#include <QStringList>
#include <QList>
#include <QDebug>

AnalyzationDetails::AnalyzationDetails(const QString &str_website, const QString &str_websiteName, const QString &str_flow, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnalyzationDetails),
    mstr_website(str_website),
    mstr_websiteName(str_websiteName),
    mstr_flow(str_flow)
{
    ui->setupUi(this);

    // write out website name
    ui->labelWebsiteName->setText(mstr_website);

    // write out flow used
    QString str_exactFlowDescription;
    if(mstr_flow.contains("code", Qt::CaseInsensitive))
    {
        str_exactFlowDescription = "Authorization Code Grant";
    }
    else if(mstr_flow.contains("token", Qt::CaseInsensitive))
    {
        str_exactFlowDescription = "Implicit Grant";
    }

    ui->labelFlow->setText(str_exactFlowDescription);

    // write out if sdk is used
    if(g_sqlHandlerInstance.checkJSSdkUsage(mstr_websiteName))
    {
        ui->labelJSSdk->setText("Yes");
    }
    else if(!ui->labelWebsiteName->text().isEmpty())
    {
        ui->labelJSSdk->setText("No");
    }

    if(g_sqlHandlerInstance.checkPHPSdkUsage(mstr_websiteName))
    {
        ui->labelPHPSdk->setText("Yes");
    }
    else if(!ui->labelWebsiteName->text().isEmpty())
    {
        ui->labelPHPSdk->setText("No");
    }
}

AnalyzationDetails::~AnalyzationDetails()
{
    delete ui;
}

