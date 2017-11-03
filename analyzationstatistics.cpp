#include "analyzationstatistics.h"
#include "ui_analyzationstatistics.h"

#include "code_grant/threatscodegrant.h"
#include "implicit_grant/threatsimplicitgrant.h"
#include "general/generalthreats.h"
#include "sqlhandler.h"
#include <QStringList>
#include <QList>
#include <QProgressDialog>
#include <QPushButton>
#include <QDebug>

AnalyzationStatistics::AnalyzationStatistics(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnalyzationStatistics)
{
    ui->setupUi(this);

    QStringList strlst_websites;
    strlst_websites << "kurier.at" << "karriere.at" << "meinbezirk.at" << "vol.at" << "laola1.at" << "bergfex.at" << "ichkoche.at" << "wogibtswas.at" << "gutekueche.at" << "noen.at" << "oeticket.at" << "krone.at" << "futurezone.at" << "news.at" << "immobilienscout24.at" << "stepstone.at" << "cineplexx.at" << "vienna.at" << "tv-media.at" << "profil.at" << "preisjaeger.at" << "blick.ch" << "digitec.ch" << "local.ch" << "toppreise.ch" << "watson.ch" << "galaxus.ch" << "deindeal.ch" << "aargauerzeitung.ch" << "swissinfo.ch" << "blickamabend.ch" << "holidaycheck.ch" << "ticketcorner.ch" << "jobscout24.at" << "laredoute.ch" << "immostreet.ch" << "cern.ch" << "bild.de" << "spiegel.de" << "welt.de" << "kicker.de" << "computerbild.de" << "giga.de" << "stern.de" << "mydealz.de" << "check24.de" << "gamestar.de" << "dasoertliche.de" << "notebooksbilliger.de" << "markt.de" << "t3n.de" << "moviepilot.de" << "filmstarts.de" << "tvspielfilm.de" << "n24.de" << "rp-online.de" << "dastelefonbuch.de" << "finya.de" << "eventim.de" << "deutsche-wirtschafts-nachrichten.de" << "winfuture.de" << "ladenzeile.de" << "gofeminin.de" << "spielaffe.de" << "kino.de" << "real.de" << "immobilienscout24.de" << "cyberport.de" << "jappy.de" << "aboutyou.de" << "kleiderkreisel.de" << "zalando-lounge.de";

    int inr_totalAmountWebsites = strlst_websites.size();

    // calculate statistics
    QList <int> lst_results;
    lst_results = calculateStatistics(strlst_websites);

    // show results
    if(!lst_results.isEmpty())
    {
       this->setModal(true);
       this->show();
       writeOutStatistics(inr_totalAmountWebsites, lst_results);
    }
}

AnalyzationStatistics::~AnalyzationStatistics()
{
    delete ui;
}

// calculate statistics
QList<int> AnalyzationStatistics::calculateStatistics(QStringList strlst_websites)
{
    // show progress dialog until calculations are done
    QProgressDialog progressDialog(this);
    QPushButton *cancelButton = new QPushButton(tr("&Cancel"), &progressDialog);
    progressDialog.setCancelButton(cancelButton);
    progressDialog.setRange(0, strlst_websites.size());
    progressDialog.setWindowTitle(tr("Calculate Statistics"));
    progressDialog.setMinimumWidth(300);

    QList<int> lst_results;
    int inr_amountClickjacking=0, inr_amountCsrf=0, inr_amountSecretLeak=0, inr_amountTokenEavesdropping=0, inr_amountCodeFlow=0, inr_amountImplicitFlow=0, inr_amountFlowUndetermined=0, inr_amountSdkUsed=0, inr_amountSdkCode=0, inr_amountSdkImplicit=0, inr_amountSdkUndetermined=0;
    int inr_tokenSetCookie = 0, inr_tokenCookieRequest = 0, inr_totalAmountTokenCookie = 0;
    // check threat, flow and sdk usage for each website
    for(int i=0; i<strlst_websites.size(); i++)
    {
       // update progress dialog
       progressDialog.setValue(i);
       progressDialog.setLabelText(tr("Checking website number %1 of %n...", 0, strlst_websites.size()).arg(i));
       QCoreApplication::processEvents();

       // stop calculations if progress dialog is cancelled
       if(progressDialog.wasCanceled())
       {
           emit this->rejected();
           return lst_results;
       }


       QString str_currentWebsite = strlst_websites.at(i);
       str_currentWebsite.chop(3); // removes .tld from string

       // check flow
       QString str_flow = g_sqlHandlerInstance.getAuthFlow(str_currentWebsite);
       if(str_flow.contains("code", Qt::CaseInsensitive))
       {
           inr_amountCodeFlow++;

           if(g_sqlHandlerInstance.checkSdkUsage(str_currentWebsite))
           {
               inr_amountSdkCode++;
               inr_amountSdkUsed++;
           }
       }
       else if(str_flow.contains("token", Qt::CaseInsensitive))
       {
           inr_amountImplicitFlow++;
           if(g_sqlHandlerInstance.checkSdkUsage(str_currentWebsite))
           {
               inr_amountSdkImplicit++;
               inr_amountSdkUsed++;
           }
       }
       else
       {
           inr_amountFlowUndetermined++;
           if(g_sqlHandlerInstance.checkSdkUsage(str_currentWebsite))
           {
               inr_amountSdkUndetermined++;
               inr_amountSdkUsed++;
           }
       }

       // calculate amount token cookie threats
       if(g_sqlHandlerInstance.checkSetTokenCookie(str_currentWebsite))
       {
           inr_tokenSetCookie++;
       }

       if(g_sqlHandlerInstance.checkTokenCookieRequestHeader(str_currentWebsite))
       {
           inr_tokenCookieRequest++;
       }

       // calculate amount clickjacking
       if(g_generalThreatsInstance.clickjackingAttack(str_currentWebsite))
           inr_amountClickjacking++;

       // calculate amount csrf
       if(g_generalThreatsInstance.loginCsrfAttack(str_currentWebsite))
           inr_amountCsrf++;

       // calculate amount secret leak
       if(g_threatsCodeGrantInstance.clientSecretLeakage(str_currentWebsite))
           inr_amountSecretLeak++;

       // calculate amount token leak
       if(g_threatsImplicitGrantInstance.accessTokenEavesdropping(str_currentWebsite))
           inr_amountTokenEavesdropping++;
    }

    // calculate total amount of cookie leaks
    inr_totalAmountTokenCookie = inr_tokenSetCookie + inr_tokenCookieRequest;

    lst_results << inr_amountClickjacking << inr_amountCsrf << inr_amountSecretLeak << inr_amountTokenEavesdropping << inr_totalAmountTokenCookie << inr_amountCodeFlow << inr_amountImplicitFlow << inr_amountFlowUndetermined << inr_amountSdkUsed << inr_amountSdkCode << inr_amountSdkImplicit << inr_amountSdkUndetermined;

    return lst_results;
}

void AnalyzationStatistics::writeOutStatistics(int inr_totalAmountWebsites, QList<int> lst_results)
{
    // get results
    int inr_clickjackingThreat=lst_results.at(0), inr_csrfThreat=lst_results.at(1), inr_secretLeakThreat=lst_results.at(2), inr_tokenEavesdroppingLeak=lst_results.at(3), inr_tokenCookie=lst_results.at(4);
    int inr_codeFlow=lst_results.at(5), inr_implicitFlow=lst_results.at(6), inr_undeterminedFlow=lst_results.at(7);
    int inr_sdkUsed=lst_results.at(8), inr_sdkCode=lst_results.at(9), inr_sdkImplicit=lst_results.at(10), inr_sdkUndetermined=lst_results.at(11);

    // calculate overall amount of threat precence
    float f_percentClickjacking=(100*(float)inr_clickjackingThreat)/(float)inr_totalAmountWebsites, f_percentCsrf=(100*(float)inr_csrfThreat)/(float)inr_totalAmountWebsites, f_percentSecretLeak=(100*(float)inr_secretLeakThreat)/(float)inr_totalAmountWebsites, f_percentTokenEavesdropping=(100*(float)inr_tokenEavesdroppingLeak)/(float)inr_totalAmountWebsites, f_percentTokenCookie=(100*(float)inr_tokenCookie)/(float)inr_totalAmountWebsites;

    // calculate overall amount of different flows
    float f_percentCodeFlow=(100*(float)inr_codeFlow)/(float)inr_totalAmountWebsites, f_percentImplicitFlow=(100*(float)inr_implicitFlow)/(float)inr_totalAmountWebsites, f_percentUndeterminedFlow=(100*(float)inr_undeterminedFlow)/(float)inr_totalAmountWebsites;

    // calculate overall amount of sdk usage
    float f_percentSdkUsed=(100*(float)inr_sdkUsed)/(float)inr_totalAmountWebsites, f_percentSdkCode=(100*(float)inr_sdkCode)/(float)inr_totalAmountWebsites, f_percentSdkImplicit=(100*(float)inr_sdkImplicit)/(float)inr_totalAmountWebsites, f_percentSdkUndetermined=(100*(float)inr_sdkUndetermined)/(float)inr_totalAmountWebsites;

    // write out threat results
    ui->labelStatT1->setText(QString::number(f_percentClickjacking, 'g', 4)+"%");
    ui->labelStatT2->setText(QString::number(f_percentCsrf, 'g', 4)+"%");
    ui->labelStatT3->setText(QString::number(f_percentSecretLeak, 'g', 4)+"%");
    ui->labelStatT4->setText(QString::number(f_percentTokenEavesdropping, 'g', 4)+"%");
    ui->labelStatT5->setText(QString::number(f_percentTokenCookie, 'g', 4)+"%");

    // write out flow results
    ui->labelCodeFlow->setText(QString::number(f_percentCodeFlow, 'g', 4)+"%");
    ui->labelImplicitFlow->setText(QString::number(f_percentImplicitFlow, 'g', 4)+"%");
    ui->labelFlowUndetermined->setText(QString::number(f_percentUndeterminedFlow, 'g', 4)+"%");

    // write out sdk results
    ui->labelPercentSdk->setText(QString::number(f_percentSdkUsed, 'g', 4)+"%");
    ui->labelPercentSdkCode->setText(QString::number(f_percentSdkCode, 'g', 4)+"%");
    ui->labelPercentSdkImplicit->setText(QString::number(f_percentSdkImplicit, 'g', 4)+"%");
    ui->labelPercentSdkUndetermined->setText(QString::number(f_percentSdkUndetermined, 'g', 4)+"%");
}
