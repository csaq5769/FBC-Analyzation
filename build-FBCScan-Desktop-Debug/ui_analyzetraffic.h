/********************************************************************************
** Form generated from reading UI file 'analyzetraffic.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALYZETRAFFIC_H
#define UI_ANALYZETRAFFIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Analyzetraffic
{
public:
    QAction *actionWebsite_Details;
    QAction *actionOverall_Statistics;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *labelTLD;
    QComboBox *comboBoxTLD;
    QVBoxLayout *verticalLayout;
    QLabel *labelWebsite;
    QComboBox *comboBoxWebsite;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButtonReset;
    QPushButton *pushButtonTest;
    QFrame *line;
    QVBoxLayout *verticalLayout_6;
    QTableWidget *tableWidgetResults;
    QLabel *labelTitle;
    QSpacerItem *verticalSpacer_2;
    QMenuBar *menuBar;
    QMenu *menuStatistics;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Analyzetraffic)
    {
        if (Analyzetraffic->objectName().isEmpty())
            Analyzetraffic->setObjectName(QStringLiteral("Analyzetraffic"));
        Analyzetraffic->resize(1206, 674);
        Analyzetraffic->setAutoFillBackground(false);
        Analyzetraffic->setStyleSheet(QStringLiteral(""));
        actionWebsite_Details = new QAction(Analyzetraffic);
        actionWebsite_Details->setObjectName(QStringLiteral("actionWebsite_Details"));
        actionOverall_Statistics = new QAction(Analyzetraffic);
        actionOverall_Statistics->setObjectName(QStringLiteral("actionOverall_Statistics"));
        centralWidget = new QWidget(Analyzetraffic);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral(""));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        labelTLD = new QLabel(centralWidget);
        labelTLD->setObjectName(QStringLiteral("labelTLD"));
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu"));
        font.setPointSize(15);
        font.setBold(false);
        font.setWeight(50);
        labelTLD->setFont(font);

        verticalLayout_4->addWidget(labelTLD);

        comboBoxTLD = new QComboBox(centralWidget);
        comboBoxTLD->setObjectName(QStringLiteral("comboBoxTLD"));
        comboBoxTLD->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBoxTLD->sizePolicy().hasHeightForWidth());
        comboBoxTLD->setSizePolicy(sizePolicy);
        comboBoxTLD->setMinimumSize(QSize(300, 0));
        comboBoxTLD->setMaximumSize(QSize(16777215, 16777215));
        comboBoxTLD->setSizeIncrement(QSize(0, 0));
        comboBoxTLD->setBaseSize(QSize(0, 0));
        comboBoxTLD->setStyleSheet(QStringLiteral(""));
        comboBoxTLD->setEditable(false);

        verticalLayout_4->addWidget(comboBoxTLD);


        verticalLayout_2->addLayout(verticalLayout_4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        labelWebsite = new QLabel(centralWidget);
        labelWebsite->setObjectName(QStringLiteral("labelWebsite"));
        labelWebsite->setFont(font);

        verticalLayout->addWidget(labelWebsite);

        comboBoxWebsite = new QComboBox(centralWidget);
        comboBoxWebsite->setObjectName(QStringLiteral("comboBoxWebsite"));
        sizePolicy.setHeightForWidth(comboBoxWebsite->sizePolicy().hasHeightForWidth());
        comboBoxWebsite->setSizePolicy(sizePolicy);
        comboBoxWebsite->setMinimumSize(QSize(300, 0));

        verticalLayout->addWidget(comboBoxWebsite);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        pushButtonReset = new QPushButton(centralWidget);
        pushButtonReset->setObjectName(QStringLiteral("pushButtonReset"));

        horizontalLayout_4->addWidget(pushButtonReset);

        pushButtonTest = new QPushButton(centralWidget);
        pushButtonTest->setObjectName(QStringLiteral("pushButtonTest"));

        horizontalLayout_4->addWidget(pushButtonTest);


        verticalLayout_2->addLayout(horizontalLayout_4);


        horizontalLayout->addLayout(verticalLayout_2);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout_6->setContentsMargins(10, -1, -1, -1);
        tableWidgetResults = new QTableWidget(centralWidget);
        tableWidgetResults->setObjectName(QStringLiteral("tableWidgetResults"));
        tableWidgetResults->setEnabled(true);
        tableWidgetResults->setMinimumSize(QSize(850, 0));
        tableWidgetResults->setFrameShape(QFrame::WinPanel);
        tableWidgetResults->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        tableWidgetResults->setProperty("showDropIndicator", QVariant(false));
        tableWidgetResults->setDragDropOverwriteMode(false);
        tableWidgetResults->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidgetResults->setSelectionBehavior(QAbstractItemView::SelectColumns);
        tableWidgetResults->setShowGrid(false);
        tableWidgetResults->setGridStyle(Qt::NoPen);
        tableWidgetResults->horizontalHeader()->setVisible(false);
        tableWidgetResults->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidgetResults->horizontalHeader()->setHighlightSections(false);
        tableWidgetResults->horizontalHeader()->setStretchLastSection(true);
        tableWidgetResults->verticalHeader()->setVisible(false);
        tableWidgetResults->verticalHeader()->setHighlightSections(false);

        verticalLayout_6->addWidget(tableWidgetResults);


        horizontalLayout->addLayout(verticalLayout_6);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 1);

        labelTitle = new QLabel(centralWidget);
        labelTitle->setObjectName(QStringLiteral("labelTitle"));
        labelTitle->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelTitle->sizePolicy().hasHeightForWidth());
        labelTitle->setSizePolicy(sizePolicy1);
        labelTitle->setBaseSize(QSize(0, 0));
        QFont font1;
        font1.setFamily(QStringLiteral("Ubuntu"));
        font1.setPointSize(25);
        font1.setBold(false);
        font1.setWeight(50);
        labelTitle->setFont(font1);
        labelTitle->setStyleSheet(QStringLiteral("QLabel {color: dodgerblue;}"));
        labelTitle->setFrameShape(QFrame::NoFrame);
        labelTitle->setFrameShadow(QFrame::Sunken);
        labelTitle->setTextFormat(Qt::AutoText);
        labelTitle->setScaledContents(false);
        labelTitle->setAlignment(Qt::AlignCenter);
        labelTitle->setWordWrap(false);

        gridLayout->addWidget(labelTitle, 1, 0, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 2, 0, 1, 1);

        Analyzetraffic->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Analyzetraffic);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1206, 25));
        menuStatistics = new QMenu(menuBar);
        menuStatistics->setObjectName(QStringLiteral("menuStatistics"));
        Analyzetraffic->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Analyzetraffic);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Analyzetraffic->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Analyzetraffic);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Analyzetraffic->setStatusBar(statusBar);

        menuBar->addAction(menuStatistics->menuAction());
        menuStatistics->addAction(actionWebsite_Details);
        menuStatistics->addAction(actionOverall_Statistics);

        retranslateUi(Analyzetraffic);

        QMetaObject::connectSlotsByName(Analyzetraffic);
    } // setupUi

    void retranslateUi(QMainWindow *Analyzetraffic)
    {
        Analyzetraffic->setWindowTitle(QApplication::translate("Analyzetraffic", "Security Analyzer for Facebook Login with OAuth 2.0", 0));
        actionWebsite_Details->setText(QApplication::translate("Analyzetraffic", "Website Details", 0));
        actionOverall_Statistics->setText(QApplication::translate("Analyzetraffic", "Overall Statistics", 0));
        labelTLD->setText(QApplication::translate("Analyzetraffic", "Top-Level-Domain:", 0));
        labelWebsite->setText(QApplication::translate("Analyzetraffic", "Website:", 0));
        pushButtonReset->setText(QApplication::translate("Analyzetraffic", "Reset", 0));
        pushButtonTest->setText(QApplication::translate("Analyzetraffic", "Test", 0));
        labelTitle->setText(QApplication::translate("Analyzetraffic", "Security Analyzer for Facebook Login with OAuth 2.0", 0));
        menuStatistics->setTitle(QApplication::translate("Analyzetraffic", "Statistics", 0));
    } // retranslateUi

};

namespace Ui {
    class Analyzetraffic: public Ui_Analyzetraffic {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYZETRAFFIC_H
