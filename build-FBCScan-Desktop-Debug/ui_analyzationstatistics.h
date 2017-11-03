/********************************************************************************
** Form generated from reading UI file 'analyzationstatistics.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALYZATIONSTATISTICS_H
#define UI_ANALYZATIONSTATISTICS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AnalyzationStatistics
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_4;
    QLabel *labelThreatStatistics;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_7;
    QLabel *labelStatT1;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_6;
    QLabel *labelStatT2;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_5;
    QLabel *labelStatT3;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_4;
    QLabel *labelStatT4;
    QSpacerItem *verticalSpacer_3;
    QFrame *line;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelDescriptionCodeFlow;
    QSpacerItem *horizontalSpacer;
    QLabel *labelCodeFlow;
    QHBoxLayout *horizontalLayout;
    QLabel *labelDescriptionImplicitFlow;
    QSpacerItem *horizontalSpacer_2;
    QLabel *labelImplicitFlow;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelDescriptionFlowUndetermined;
    QSpacerItem *horizontalSpacer_3;
    QLabel *labelFlowUndetermined;
    QSpacerItem *verticalSpacer;
    QFrame *line_2;
    QLabel *labelSdkStatistics;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelUsingSdk;
    QSpacerItem *horizontalSpacer_8;
    QLabel *labelPercentSdk;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelSdkCode;
    QSpacerItem *horizontalSpacer_9;
    QLabel *labelPercentSdkCode;
    QHBoxLayout *horizontalLayout_7;
    QLabel *labelSdkImplicit;
    QSpacerItem *horizontalSpacer_10;
    QLabel *labelPercentSdkImplicit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelSdkUndetermined;
    QSpacerItem *horizontalSpacer_11;
    QLabel *labelPercentSdkUndetermined;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *AnalyzationStatistics)
    {
        if (AnalyzationStatistics->objectName().isEmpty())
            AnalyzationStatistics->setObjectName(QStringLiteral("AnalyzationStatistics"));
        AnalyzationStatistics->resize(779, 559);
        gridLayout = new QGridLayout(AnalyzationStatistics);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalSpacer_4 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_4);

        labelThreatStatistics = new QLabel(AnalyzationStatistics);
        labelThreatStatistics->setObjectName(QStringLiteral("labelThreatStatistics"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelThreatStatistics->sizePolicy().hasHeightForWidth());
        labelThreatStatistics->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu"));
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        labelThreatStatistics->setFont(font);

        verticalLayout_4->addWidget(labelThreatStatistics);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_2 = new QLabel(AnalyzationStatistics);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font1;
        font1.setPointSize(14);
        label_2->setFont(font1);

        horizontalLayout_8->addWidget(label_2);

        horizontalSpacer_7 = new QSpacerItem(93, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_7);

        labelStatT1 = new QLabel(AnalyzationStatistics);
        labelStatT1->setObjectName(QStringLiteral("labelStatT1"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelStatT1->sizePolicy().hasHeightForWidth());
        labelStatT1->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setFamily(QStringLiteral("Ubuntu"));
        font2.setPointSize(12);
        labelStatT1->setFont(font2);

        horizontalLayout_8->addWidget(labelStatT1);


        verticalLayout_3->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_3 = new QLabel(AnalyzationStatistics);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font1);

        horizontalLayout_9->addWidget(label_3);

        horizontalSpacer_6 = new QSpacerItem(98, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_6);

        labelStatT2 = new QLabel(AnalyzationStatistics);
        labelStatT2->setObjectName(QStringLiteral("labelStatT2"));
        sizePolicy1.setHeightForWidth(labelStatT2->sizePolicy().hasHeightForWidth());
        labelStatT2->setSizePolicy(sizePolicy1);
        labelStatT2->setFont(font2);

        horizontalLayout_9->addWidget(labelStatT2);


        verticalLayout_3->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_4 = new QLabel(AnalyzationStatistics);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font1);

        horizontalLayout_10->addWidget(label_4);

        horizontalSpacer_5 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_5);

        labelStatT3 = new QLabel(AnalyzationStatistics);
        labelStatT3->setObjectName(QStringLiteral("labelStatT3"));
        sizePolicy1.setHeightForWidth(labelStatT3->sizePolicy().hasHeightForWidth());
        labelStatT3->setSizePolicy(sizePolicy1);
        labelStatT3->setFont(font2);

        horizontalLayout_10->addWidget(labelStatT3);


        verticalLayout_3->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_5 = new QLabel(AnalyzationStatistics);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font1);

        horizontalLayout_11->addWidget(label_5);

        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_4);

        labelStatT4 = new QLabel(AnalyzationStatistics);
        labelStatT4->setObjectName(QStringLiteral("labelStatT4"));
        sizePolicy1.setHeightForWidth(labelStatT4->sizePolicy().hasHeightForWidth());
        labelStatT4->setSizePolicy(sizePolicy1);
        labelStatT4->setFont(font2);

        horizontalLayout_11->addWidget(labelStatT4);


        verticalLayout_3->addLayout(horizontalLayout_11);


        verticalLayout_4->addLayout(verticalLayout_3);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);

        line = new QFrame(AnalyzationStatistics);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line);

        label = new QLabel(AnalyzationStatistics);
        label->setObjectName(QStringLiteral("label"));
        QFont font3;
        font3.setPointSize(15);
        font3.setBold(true);
        font3.setWeight(75);
        label->setFont(font3);

        verticalLayout_4->addWidget(label);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelDescriptionCodeFlow = new QLabel(AnalyzationStatistics);
        labelDescriptionCodeFlow->setObjectName(QStringLiteral("labelDescriptionCodeFlow"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labelDescriptionCodeFlow->sizePolicy().hasHeightForWidth());
        labelDescriptionCodeFlow->setSizePolicy(sizePolicy2);
        QFont font4;
        font4.setPointSize(14);
        font4.setBold(false);
        font4.setWeight(50);
        labelDescriptionCodeFlow->setFont(font4);

        horizontalLayout_2->addWidget(labelDescriptionCodeFlow);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        labelCodeFlow = new QLabel(AnalyzationStatistics);
        labelCodeFlow->setObjectName(QStringLiteral("labelCodeFlow"));
        sizePolicy.setHeightForWidth(labelCodeFlow->sizePolicy().hasHeightForWidth());
        labelCodeFlow->setSizePolicy(sizePolicy);
        QFont font5;
        font5.setPointSize(12);
        labelCodeFlow->setFont(font5);

        horizontalLayout_2->addWidget(labelCodeFlow);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelDescriptionImplicitFlow = new QLabel(AnalyzationStatistics);
        labelDescriptionImplicitFlow->setObjectName(QStringLiteral("labelDescriptionImplicitFlow"));
        sizePolicy2.setHeightForWidth(labelDescriptionImplicitFlow->sizePolicy().hasHeightForWidth());
        labelDescriptionImplicitFlow->setSizePolicy(sizePolicy2);
        labelDescriptionImplicitFlow->setFont(font4);

        horizontalLayout->addWidget(labelDescriptionImplicitFlow);

        horizontalSpacer_2 = new QSpacerItem(115, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        labelImplicitFlow = new QLabel(AnalyzationStatistics);
        labelImplicitFlow->setObjectName(QStringLiteral("labelImplicitFlow"));
        sizePolicy.setHeightForWidth(labelImplicitFlow->sizePolicy().hasHeightForWidth());
        labelImplicitFlow->setSizePolicy(sizePolicy);
        labelImplicitFlow->setFont(font5);

        horizontalLayout->addWidget(labelImplicitFlow);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        labelDescriptionFlowUndetermined = new QLabel(AnalyzationStatistics);
        labelDescriptionFlowUndetermined->setObjectName(QStringLiteral("labelDescriptionFlowUndetermined"));
        sizePolicy2.setHeightForWidth(labelDescriptionFlowUndetermined->sizePolicy().hasHeightForWidth());
        labelDescriptionFlowUndetermined->setSizePolicy(sizePolicy2);
        labelDescriptionFlowUndetermined->setFont(font1);

        horizontalLayout_3->addWidget(labelDescriptionFlowUndetermined);

        horizontalSpacer_3 = new QSpacerItem(110, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        labelFlowUndetermined = new QLabel(AnalyzationStatistics);
        labelFlowUndetermined->setObjectName(QStringLiteral("labelFlowUndetermined"));
        sizePolicy.setHeightForWidth(labelFlowUndetermined->sizePolicy().hasHeightForWidth());
        labelFlowUndetermined->setSizePolicy(sizePolicy);
        labelFlowUndetermined->setFont(font5);

        horizontalLayout_3->addWidget(labelFlowUndetermined);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_4->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        line_2 = new QFrame(AnalyzationStatistics);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line_2);

        labelSdkStatistics = new QLabel(AnalyzationStatistics);
        labelSdkStatistics->setObjectName(QStringLiteral("labelSdkStatistics"));
        labelSdkStatistics->setFont(font3);

        verticalLayout_4->addWidget(labelSdkStatistics);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        labelUsingSdk = new QLabel(AnalyzationStatistics);
        labelUsingSdk->setObjectName(QStringLiteral("labelUsingSdk"));
        sizePolicy2.setHeightForWidth(labelUsingSdk->sizePolicy().hasHeightForWidth());
        labelUsingSdk->setSizePolicy(sizePolicy2);
        labelUsingSdk->setFont(font1);

        horizontalLayout_5->addWidget(labelUsingSdk);

        horizontalSpacer_8 = new QSpacerItem(120, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_8);

        labelPercentSdk = new QLabel(AnalyzationStatistics);
        labelPercentSdk->setObjectName(QStringLiteral("labelPercentSdk"));
        sizePolicy.setHeightForWidth(labelPercentSdk->sizePolicy().hasHeightForWidth());
        labelPercentSdk->setSizePolicy(sizePolicy);
        labelPercentSdk->setFont(font5);

        horizontalLayout_5->addWidget(labelPercentSdk);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        labelSdkCode = new QLabel(AnalyzationStatistics);
        labelSdkCode->setObjectName(QStringLiteral("labelSdkCode"));
        sizePolicy2.setHeightForWidth(labelSdkCode->sizePolicy().hasHeightForWidth());
        labelSdkCode->setSizePolicy(sizePolicy2);
        labelSdkCode->setFont(font1);

        horizontalLayout_6->addWidget(labelSdkCode);

        horizontalSpacer_9 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_9);

        labelPercentSdkCode = new QLabel(AnalyzationStatistics);
        labelPercentSdkCode->setObjectName(QStringLiteral("labelPercentSdkCode"));
        sizePolicy.setHeightForWidth(labelPercentSdkCode->sizePolicy().hasHeightForWidth());
        labelPercentSdkCode->setSizePolicy(sizePolicy);
        labelPercentSdkCode->setFont(font5);

        horizontalLayout_6->addWidget(labelPercentSdkCode);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        labelSdkImplicit = new QLabel(AnalyzationStatistics);
        labelSdkImplicit->setObjectName(QStringLiteral("labelSdkImplicit"));
        sizePolicy2.setHeightForWidth(labelSdkImplicit->sizePolicy().hasHeightForWidth());
        labelSdkImplicit->setSizePolicy(sizePolicy2);
        labelSdkImplicit->setFont(font1);

        horizontalLayout_7->addWidget(labelSdkImplicit);

        horizontalSpacer_10 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_10);

        labelPercentSdkImplicit = new QLabel(AnalyzationStatistics);
        labelPercentSdkImplicit->setObjectName(QStringLiteral("labelPercentSdkImplicit"));
        sizePolicy.setHeightForWidth(labelPercentSdkImplicit->sizePolicy().hasHeightForWidth());
        labelPercentSdkImplicit->setSizePolicy(sizePolicy);
        labelPercentSdkImplicit->setFont(font5);

        horizontalLayout_7->addWidget(labelPercentSdkImplicit);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        labelSdkUndetermined = new QLabel(AnalyzationStatistics);
        labelSdkUndetermined->setObjectName(QStringLiteral("labelSdkUndetermined"));
        sizePolicy2.setHeightForWidth(labelSdkUndetermined->sizePolicy().hasHeightForWidth());
        labelSdkUndetermined->setSizePolicy(sizePolicy2);
        labelSdkUndetermined->setFont(font1);

        horizontalLayout_4->addWidget(labelSdkUndetermined);

        horizontalSpacer_11 = new QSpacerItem(90, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_11);

        labelPercentSdkUndetermined = new QLabel(AnalyzationStatistics);
        labelPercentSdkUndetermined->setObjectName(QStringLiteral("labelPercentSdkUndetermined"));
        sizePolicy.setHeightForWidth(labelPercentSdkUndetermined->sizePolicy().hasHeightForWidth());
        labelPercentSdkUndetermined->setSizePolicy(sizePolicy);
        labelPercentSdkUndetermined->setFont(font5);

        horizontalLayout_4->addWidget(labelPercentSdkUndetermined);


        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout_4->addLayout(verticalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);


        gridLayout->addLayout(verticalLayout_4, 0, 0, 1, 1);


        retranslateUi(AnalyzationStatistics);

        QMetaObject::connectSlotsByName(AnalyzationStatistics);
    } // setupUi

    void retranslateUi(QDialog *AnalyzationStatistics)
    {
        AnalyzationStatistics->setWindowTitle(QApplication::translate("AnalyzationStatistics", "Analyzation Statistics", 0));
        labelThreatStatistics->setText(QApplication::translate("AnalyzationStatistics", "Threat Statistics", 0));
        label_2->setText(QApplication::translate("AnalyzationStatistics", "Clickjacking Attack:", 0));
        labelStatT1->setText(QString());
        label_3->setText(QApplication::translate("AnalyzationStatistics", "Login CSRF Attack:", 0));
        labelStatT2->setText(QString());
        label_4->setText(QApplication::translate("AnalyzationStatistics", "Client Secret Leak:", 0));
        labelStatT3->setText(QString());
        label_5->setText(QApplication::translate("AnalyzationStatistics", "Eavesdropping Access Token:", 0));
        labelStatT4->setText(QString());
        label->setText(QApplication::translate("AnalyzationStatistics", "Flow Statistics", 0));
        labelDescriptionCodeFlow->setText(QApplication::translate("AnalyzationStatistics", "Authorization Code Grant:", 0));
        labelCodeFlow->setText(QString());
        labelDescriptionImplicitFlow->setText(QApplication::translate("AnalyzationStatistics", "Implicit Grant:", 0));
        labelImplicitFlow->setText(QString());
        labelDescriptionFlowUndetermined->setText(QApplication::translate("AnalyzationStatistics", "Undetermined:", 0));
        labelFlowUndetermined->setText(QString());
        labelSdkStatistics->setText(QApplication::translate("AnalyzationStatistics", "SDK Statistics", 0));
        labelUsingSdk->setText(QApplication::translate("AnalyzationStatistics", "Using SDK:", 0));
        labelPercentSdk->setText(QString());
        labelSdkCode->setText(QApplication::translate("AnalyzationStatistics", "SDK with Code Grant:", 0));
        labelPercentSdkCode->setText(QString());
        labelSdkImplicit->setText(QApplication::translate("AnalyzationStatistics", "SDK with Implicit Grant:", 0));
        labelPercentSdkImplicit->setText(QString());
        labelSdkUndetermined->setText(QApplication::translate("AnalyzationStatistics", "Undetermined", 0));
        labelPercentSdkUndetermined->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AnalyzationStatistics: public Ui_AnalyzationStatistics {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYZATIONSTATISTICS_H
