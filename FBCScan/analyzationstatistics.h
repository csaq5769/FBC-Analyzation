#ifndef ANALYZATIONSTATISTICS_H
#define ANALYZATIONSTATISTICS_H

#include <QDialog>

namespace Ui {
class AnalyzationStatistics;
}

class AnalyzationStatistics : public QDialog
{
    Q_OBJECT

public:
    explicit AnalyzationStatistics(QWidget *parent = 0);
    ~AnalyzationStatistics();

    //void showEvent(QShowEvent *event);

private:
    Ui::AnalyzationStatistics *ui;

    bool m_statisticsCalculationCancelled;

    QList<int> calculateStatistics(QStringList strlst_websites);

    void writeOutStatistics(int inr_totalAmountWebsites, QList<int> lst_results);

};

#endif // ANALYZATIONSTATISTICS_H
