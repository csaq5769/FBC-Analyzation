#ifndef ANALYZETRAFFIC_H
#define ANALYZETRAFFIC_H

#include <QMainWindow>
#include <QStringList>
#include <QString>

namespace Ui {
class Analyzetraffic;
}

class Analyzetraffic : public QMainWindow
{
    Q_OBJECT

public:
    explicit Analyzetraffic(QWidget *parent = 0);
    ~Analyzetraffic();

    QStringList strlst_tlds;
    QStringList strlst_atSites;
    QStringList strlst_chSites;
    QStringList strlst_deSites;

private slots:
    void on_comboBoxTLD_currentTextChanged(const QString &str_newValue);


    void on_pushButtonReset_clicked();

    void on_comboBoxWebsite_activated(const QString &str_value);

    void on_pushButtonTest_clicked();


    void on_comboBoxWebsite_currentTextChanged(const QString &str_newValue);

    void on_actionWebsite_Details_triggered();

    void on_actionOverall_Statistics_triggered();

private:
    Ui::Analyzetraffic *ui;

    QString getAuthFlow(QString str_website);
};

#endif // ANALYZETRAFFIC_H
