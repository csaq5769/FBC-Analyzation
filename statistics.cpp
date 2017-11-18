#include "statistics.h"
#include "ui_statistics.h"

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

    // set up website list
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
/**
 * This function calculates overall amount of threats, sdk usage and used flows
 *
 * @brief AnalyzationStatistics::calculateStatistics
 * @param strlst_websites
 * @return lst_results
 */
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
    int inr_amountClickjacking=0, inr_amountCsrf=0, inr_amountSecretLeak=0, inr_amountTokenEavesdropping=0, inr_amountTokenSetCookie = 0;
    int inr_amountCodeFlow=0, inr_amountImplicitFlow=0, inr_amountFlowUndetermined=0;
    int inr_amountJSSdkUsed=0, inr_amountPHPSdkUsed=0;

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

       // get current website name
       QString str_currentWebsite = strlst_websites.at(i);
       str_currentWebsite.chop(3); // removes .tld from string

       // check flow
       QString str_flow = g_sqlHandlerInstance.getAuthFlow(str_currentWebsite);
       if(str_flow.contains("code", Qt::CaseInsensitive))
       {
           inr_amountCodeFlow++;
       }
       else if(str_flow.contains("token", Qt::CaseInsensitive))
       {
           inr_amountImplicitFlow++;
       }
       else
       {
           inr_amountFlowUndetermined++;
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

       // calculate amount token cookie threats
       if(g_sqlHandlerInstance.checkSetTokenCookie(str_currentWebsite))
           inr_amountTokenSetCookie++;

       // check js sdk
       if(g_sqlHandlerInstance.checkJSSdkUsage(str_currentWebsite))
           inr_amountJSSdkUsed++;

       // check php sdk
       if(g_sqlHandlerInstance.checkPHPSdkUsage(str_currentWebsite))
           inr_amountPHPSdkUsed++;
    }

    lst_results << inr_amountClickjacking << inr_amountCsrf << inr_amountSecretLeak << inr_amountTokenEavesdropping << inr_amountTokenSetCookie << inr_amountCodeFlow << inr_amountImplicitFlow << inr_amountFlowUndetermined << inr_amountJSSdkUsed << inr_amountPHPSdkUsed;

    return lst_results;
}

/**
 * This function calculates the statistics out of the above calculated results
 *
 * @brief AnalyzationStatistics::writeOutStatistics
 * @param inr_totalAmountWebsites
 * @param lst_results
 */
void AnalyzationStatistics::writeOutStatistics(int inr_totalAmountWebsites, QList<int> lst_results)
{
    // get results
    int inr_clickjackingThreat=lst_results.at(0), inr_csrfThreat=lst_results.at(1), inr_secretLeakThreat=lst_results.at(2), inr_tokenEavesdroppingLeak=lst_results.at(3), inr_tokenCookie=lst_results.at(4);
    int inr_codeFlow=lst_results.at(5), inr_implicitFlow=lst_results.at(6), inr_undeterminedFlow=lst_results.at(7);
    int inr_jsSdkUsed=lst_results.at(8), inr_phpSdkUsed=lst_results.at(9);

    // calculate overall threat precence
    float f_percentClickjacking=(100*(float)inr_clickjackingThreat)/(float)inr_totalAmountWebsites, f_percentCsrf=(100*(float)inr_csrfThreat)/(float)inr_totalAmountWebsites, f_percentSecretLeak=(100*(float)inr_secretLeakThreat)/(float)inr_totalAmountWebsites, f_percentTokenEavesdropping=(100*(float)inr_tokenEavesdroppingLeak)/(float)inr_totalAmountWebsites, f_percentTokenCookie=(100*(float)inr_tokenCookie)/(float)inr_totalAmountWebsites;

    // calculate overall flows used
    float f_percentCodeFlow=(100*(float)inr_codeFlow)/(float)inr_totalAmountWebsites, f_percentImplicitFlow=(100*(float)inr_implicitFlow)/(float)inr_totalAmountWebsites, f_percentUndeterminedFlow=(100*(float)inr_undeterminedFlow)/(float)inr_totalAmountWebsites;

    // calculate overall sdk usage
    float f_percentJSSdkUsed=(100*(float)inr_jsSdkUsed)/(float)inr_totalAmountWebsites, f_percentPHPSdkUsed=(100*(float)inr_phpSdkUsed)/(float)inr_totalAmountWebsites;

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
    ui->labelPercentJSSdk->setText(QString::number(f_percentJSSdkUsed, 'g', 4)+"%");
    ui->labelPercentPHPSdk->setText(QString::number(f_percentPHPSdkUsed, 'g', 4)+"%");
}
