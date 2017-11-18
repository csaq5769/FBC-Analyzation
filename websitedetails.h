#ifndef ANALYZATIONDETAILS_H
#define ANALYZATIONDETAILS_H

#include <QDialog>

namespace Ui {
class AnalyzationDetails;
}

class AnalyzationDetails : public QDialog
{
    Q_OBJECT

public:
    explicit AnalyzationDetails(const QString &str_website, const QString &str_websiteName, const QString &str_flow, QWidget *parent = 0);
    ~AnalyzationDetails();

private:
    Ui::AnalyzationDetails *ui;

    QString mstr_website;

    QString mstr_websiteName;

    QString mstr_flow;
};

#endif // ANALYZATIONDETAILS_H
