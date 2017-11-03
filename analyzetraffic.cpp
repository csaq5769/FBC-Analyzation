#include "analyzetraffic.h"
#include "ui_analyzetraffic.h"

#include "sqlhandler.h"
#include "general/generalthreats.h"
#include "code_grant/threatscodegrant.h"
#include "implicit_grant/threatsimplicitgrant.h"
#include "analyzationdetails.h"
#include "analyzationstatistics.h"

#include <QtGlobal>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTableWidget>
#include <QStackedLayout>
#include <QCloseEvent>

Analyzetraffic::Analyzetraffic(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Analyzetraffic)
{
    ui->setupUi(this);    

    strlst_tlds << "" << ".at" << ".ch" << ".de";
    strlst_atSites << "" << "kurier.at" << "karriere.at" << "meinbezirk.at" << "vol.at" << "laola1.at" << "bergfex.at" << "ichkoche.at" << "wogibtswas.at" << "gutekueche.at" << "noen.at" << "oeticket.at" << "krone.at" << "futurezone.at" << "news.at" << "immobilienscout24.at" << "stepstone.at" << "cineplexx.at" << "vienna.at" << "tv-media.at" << "profil.at" << "preisjaeger.at";
    strlst_chSites << "" << "blick.ch" << "digitec.ch" << "local.ch" << "toppreise.ch" << "watson.ch" << "galaxus.ch" << "deindeal.ch" << "aargauerzeitung.ch" << "swissinfo.ch" << "blickamabend.ch" << "holidaycheck.ch" << "ticketcorner.ch" << "jobscout24.ch" << "laredoute.ch" << "immostreet.ch" << "cern.ch";
    strlst_deSites << "" << "bild.de" << "spiegel.de" << "welt.de" << "kicker.de" << "computerbild.de" << "giga.de" << "stern.de" << "mydealz.de" << "check24.de" << "gamestar.de" << "dasoertliche.de" << "notebooksbilliger.de" << "markt.de" << "t3n.de" << "moviepilot.de" << "filmstarts.de" << "tvspielfilm.de" << "n24.de" << "rp-online.de" << "dastelefonbuch.de" << "finya.de" << "eventim.de" << "deutsche-wirtschafts-nachrichten.de" << "winfuture.de" << "ladenzeile.de" << "gofeminin.de" << "spielaffe.de" << "kino.de" << "real.de" << "cyberport.de" << "jappy.de" << "aboutyou.de" << "kleiderkreisel.de" << "zalando-lounge.de";

    strlst_atSites.sort();
    strlst_chSites.sort();
    strlst_deSites.sort();

    ui->comboBoxTLD->addItems(strlst_tlds);

    if(ui->comboBoxTLD->currentText().isEmpty() && ui->comboBoxWebsite->currentText().isEmpty())
    {
        ui->pushButtonReset->setEnabled(false);
        ui->pushButtonTest->setEnabled(false);
    }

    ui->tableWidgetResults->horizontalHeader()->setVisible(false);

    // add empty rows and column to table widget
    ui->tableWidgetResults->setRowCount(6);
    ui->tableWidgetResults->setColumnCount(1);
}

Analyzetraffic::~Analyzetraffic()
{
    delete ui;
}


/**
 * This function fills the website combobox according to the users selected domain
 *
 * @brief Analyzetraffic::on_comboBoxTLD_currentTextChanged
 * @param str_newValue
 */
void Analyzetraffic::on_comboBoxTLD_currentTextChanged(const QString &str_newValue)
{
    // delete current combo box content
    int inr_items = ui->comboBoxWebsite->count();
    for(int i=0; i<inr_items; i++)
    {
        ui->comboBoxWebsite->removeItem(0);
    }

    // fill in corresponding websites
    if(str_newValue == ".at")
    {
        ui->comboBoxWebsite->addItems(strlst_atSites);
        ui->pushButtonReset->setEnabled(true);
    }
    else if(str_newValue == ".ch")
    {
        ui->comboBoxWebsite->addItems(strlst_chSites);
        ui->pushButtonReset->setEnabled(true);
    }
    else if(str_newValue == ".de")
    {
        ui->comboBoxWebsite->addItems(strlst_deSites);
        ui->pushButtonReset->setEnabled(true);
    }
    else
    {
        ui->comboBoxWebsite->addItem("");
        ui->pushButtonReset->setEnabled(false);
    }
}

/**
 * This function clears the comboboxes and disables buttons
 *
 * @brief Analyzetraffic::on_pushButtonReset_clicked
 */
void Analyzetraffic::on_pushButtonReset_clicked()
{
    ui->comboBoxTLD->setCurrentText(strlst_tlds.at(0));
    ui->tableWidgetResults->clear();
    ui->tableWidgetResults->horizontalHeader()->setVisible(false);
    ui->pushButtonReset->setEnabled(false);
    ui->pushButtonTest->setEnabled(false);
}

/**
 * This function enabeles the testion button if all neccessary information is given
 *
 * @brief Analyzetraffic::on_comboBoxWebsite_activated
 * @param str_value
 */
void Analyzetraffic::on_comboBoxWebsite_activated(const QString &str_value)
{
    if(!str_value.isEmpty())
    {
       ui->pushButtonTest->setEnabled(true);
    }
}


void Analyzetraffic::on_comboBoxWebsite_currentTextChanged(const QString &str_newValue /* unused */)
{
    Q_UNUSED(str_newValue);

    ui->tableWidgetResults->horizontalHeader()->setVisible(false);
    ui->tableWidgetResults->clear();
}

/**
 * This function calls the test cases for the given website and shows the results
 *
 * @brief Analyzetraffic::on_pushButtonTest_clicked
 */
void Analyzetraffic::on_pushButtonTest_clicked()
{
    // get website name
    QString str_selectedWebsite = ui->comboBoxWebsite->currentText();
    str_selectedWebsite.chop(3); // removes .tld from string

    // check flow
    QString str_flow;
    str_flow = g_sqlHandlerInstance.getAuthFlow(str_selectedWebsite);

    // header of threat results
    QStringList strlst_tableHeaderLabel;
    QString str_tableHeaderDescription = "Potential Threats";
    strlst_tableHeaderLabel << str_tableHeaderDescription;
    ui->tableWidgetResults->horizontalHeader()->setVisible(true);
    ui->tableWidgetResults->setHorizontalHeaderLabels(strlst_tableHeaderLabel);

    int inr_row = 0, inr_col = 0;
    /*----------------------------------------------------------general----------------------------------------------------------*/
    // A1
    if(g_generalThreatsInstance.clickjackingAttack(str_selectedWebsite))
    {
        QTableWidgetItem *item_clickjacking = ui->tableWidgetResults->item(inr_row, inr_col);
        if(!item_clickjacking)
        {
            item_clickjacking = new QTableWidgetItem("Obtain user or OAuth credentials through clickjacking attack");
            item_clickjacking->setFlags(Qt::ItemIsEnabled);
            ui->tableWidgetResults->setItem(inr_row, inr_col, item_clickjacking);
        }
        inr_row++;
    }

    // A2
    if(g_generalThreatsInstance.loginCsrfAttack(str_selectedWebsite))
    {
        QTableWidgetItem *item_csrf = ui->tableWidgetResults->item(inr_row, inr_col);
        if(!item_csrf)
        {
            item_csrf = new QTableWidgetItem("Login CSRF-Attacks are possible due to missing or misused state parameter");
            item_csrf->setFlags(Qt::ItemIsEnabled);
            ui->tableWidgetResults->setItem(inr_row, inr_col, item_csrf);
        }
        inr_row++;
    }

    /*--------------------------------------------------authorization code flow--------------------------------------------------*/
    if(str_flow.contains("code", Qt::CaseInsensitive))
    {
        // A3
        if(g_threatsCodeGrantInstance.clientSecretLeakage(str_selectedWebsite))
        {
            QTableWidgetItem *item_secretLeak = ui->tableWidgetResults->item(inr_row, inr_col);
            if(!item_secretLeak)
            {
                item_secretLeak = new QTableWidgetItem("Client secret is leaked because code exchange calls are done client side");
                item_secretLeak->setFlags(Qt::ItemIsEnabled);
                ui->tableWidgetResults->setItem(inr_row, inr_col, item_secretLeak);
            }
            inr_row++;
        }
    }

    /*-------------------------------------------------------implicit flow-------------------------------------------------------*/
    else if(str_flow.contains("token", Qt::CaseInsensitive))
    {
        // A4
        if(g_threatsImplicitGrantInstance.accessTokenEavesdropping(str_selectedWebsite))
        {
            QTableWidgetItem *item_tokenEavesdropping = ui->tableWidgetResults->item(inr_row, inr_col);
            if(!item_tokenEavesdropping)
            {
                item_tokenEavesdropping= new QTableWidgetItem("Eavesdropping access token because the token is passed through subsequent communication without SSL protection");
                item_tokenEavesdropping->setFlags(Qt::ItemIsEnabled);
                ui->tableWidgetResults->setItem(inr_row, inr_col, item_tokenEavesdropping);
            }
        }
        // A5
        QString str_cookieResult = g_threatsImplicitGrantInstance.accessTokenInCookie(str_selectedWebsite);
        if(!str_cookieResult.isEmpty())
        {
            QTableWidgetItem *item_tokenCookie = ui->tableWidgetResults->item(inr_row, inr_col);

            if(!item_tokenCookie)
            {
                item_tokenCookie = new QTableWidgetItem(str_cookieResult);
                item_tokenCookie->setFlags(Qt::ItemIsEnabled);
                ui->tableWidgetResults->setItem(inr_row, inr_col, item_tokenCookie);
            }
        }
    }
}

void Analyzetraffic::on_actionWebsite_Details_triggered()
{
    // get website name
    QString str_selectedWebsite = ui->comboBoxWebsite->currentText();
    str_selectedWebsite.chop(3); // removes .tld from string

    // check flow
    QString str_flow;
    str_flow = g_sqlHandlerInstance.getAuthFlow(str_selectedWebsite);

    AnalyzationDetails *details = new AnalyzationDetails(ui->comboBoxWebsite->currentText(), str_selectedWebsite, str_flow, this);
    details->setModal(true);
    details->exec();
}

void Analyzetraffic::on_actionOverall_Statistics_triggered()
{
    AnalyzationStatistics *statistics = new AnalyzationStatistics(this);
    statistics->setModal(true);
}

