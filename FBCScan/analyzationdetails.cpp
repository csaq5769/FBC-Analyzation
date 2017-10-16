#include "analyzationdetails.h"
#include "ui_analyzationdetails.h"

#include "code_grant/threatscodegrant.h"
#include "implicit_grant/threatsimplicitgrant.h"
#include "general/generalthreats.h"
#include "sqlhandler.h"
#include <QStringList>
#include <QList>
#include <QDebug>

AnalyzationDetails::AnalyzationDetails(const QString &str_website, const QString &str_flow, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnalyzationDetails),
    mstr_website(str_website),
    mstr_flow(str_flow)
{
    ui->setupUi(this);

    ui->labelWebsiteName->setText(mstr_website);

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
}

AnalyzationDetails::~AnalyzationDetails()
{
    delete ui;
}

