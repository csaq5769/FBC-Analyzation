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

    QList <int> lst_results;
    lst_results = calculateStatistics(strlst_websites);

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
    QProgressDialog progressDialog(this);
    QPushButton *cancelButton = new QPushButton(tr("&Cancel"), &progressDialog);
    progressDialog.setCancelButton(cancelButton);
    progressDialog.setRange(0, strlst_websites.size());
    progressDialog.setWindowTitle(tr("Calculate Statistics"));
    progressDialog.setMinimumWidth(300);

    QList<int> lst_results;
    int inr_amountClickjacking=0, inr_amountCsrf=0, inr_amountSecretLeak=0, inr_amountTokenEavesdropping=0, inr_amountCodeFlow=0, inr_amountImplicitFlow=0, inr_amountFlowUndetermined=0;
    for(int i=0; i<strlst_websites.size(); i++)
    {
       progressDialog.setValue(i);
       progressDialog.setLabelText(tr("Checking website number %1 of %n...", 0, strlst_websites.size()).arg(i));
       QCoreApplication::processEvents();

       if(progressDialog.wasCanceled())
       {
           emit this->rejected();
           return lst_results;
       }


       QString str_currentWebsite = strlst_websites.at(i);
       str_currentWebsite.chop(3); // removes .tld from string

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

       if(g_generalThreatsInstance.clickjackingAttack(str_currentWebsite))
           inr_amountClickjacking++;

       if(g_generalThreatsInstance.loginCsrfAttack(str_currentWebsite))
           inr_amountCsrf++;

       if(g_threatsCodeGrantInstance.clientSecretLeakage(str_currentWebsite))
           inr_amountSecretLeak++;

       if(g_threatsImplicitGrantInstance.accessTokenEavesdropping(str_currentWebsite))
           inr_amountTokenEavesdropping++;
    }

    lst_results << inr_amountClickjacking << inr_amountCsrf << inr_amountSecretLeak << inr_amountTokenEavesdropping << inr_amountCodeFlow << inr_amountImplicitFlow << inr_amountFlowUndetermined;

    return lst_results;
}

void AnalyzationStatistics::writeOutStatistics(int inr_totalAmountWebsites, QList<int> lst_results)
{
    int inr_clickjackingThreat=lst_results.at(0), inr_csrfThreat=lst_results.at(1), inr_secretLeakThreat=lst_results.at(2), inr_tokenEavesdroppingLeak=lst_results.at(3);
    int inr_codeFlow=lst_results.at(4), inr_implicitFlow=lst_results.at(5), inr_undeterminedFlow=lst_results.at(6);

    // calculate overall amount of threat precence
    float f_percentClickjacking=(100*inr_clickjackingThreat)/inr_totalAmountWebsites, f_percentCsrf=(100*inr_csrfThreat)/inr_totalAmountWebsites, f_percentSecretLeak=(100*inr_secretLeakThreat)/inr_totalAmountWebsites, f_percentTokenEavesdropping=(100*inr_tokenEavesdroppingLeak)/inr_totalAmountWebsites;

    // calculate overall amount of different flows
    float f_percentCodeFlow=(100*inr_codeFlow)/inr_totalAmountWebsites, f_percentImplicitFlow=(100*inr_implicitFlow)/inr_totalAmountWebsites, f_percentUndeterminedFlow=(100*inr_undeterminedFlow)/inr_totalAmountWebsites;

    // write out threat results
    ui->labelStatT1->setText(QString::number(f_percentClickjacking, 'f', 2)+"%");
    ui->labelStatT2->setText(QString::number(f_percentCsrf, 'f', 2)+"%");
    ui->labelStatT3->setText(QString::number(f_percentSecretLeak, 'f', 2)+"%");
    ui->labelStatT4->setText(QString::number(f_percentTokenEavesdropping, 'f', 2)+"%");

    // write out flow results
    ui->labelCodeFlow->setText(QString::number(f_percentCodeFlow, 'f', 2)+"%");
    ui->labelImplicitFlow->setText(QString::number(f_percentImplicitFlow, 'f', 2)+"%");
    ui->labelFlowUndetermined->setText(QString::number(f_percentUndeterminedFlow, 'f', 2)+"%");
}
