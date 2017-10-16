/********************************************************************************
** Form generated from reading UI file 'analyzationdetails.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALYZATIONDETAILS_H
#define UI_ANALYZATIONDETAILS_H

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

class Ui_AnalyzationDetails
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_4;
    QLabel *labelHeader;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelDescriptionName;
    QSpacerItem *horizontalSpacer;
    QLabel *labelWebsiteName;
    QHBoxLayout *horizontalLayout;
    QLabel *labelDescriptionFlow;
    QSpacerItem *horizontalSpacer_2;
    QLabel *labelFlow;
    QSpacerItem *verticalSpacer;
    QFrame *line;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QDialog *AnalyzationDetails)
    {
        if (AnalyzationDetails->objectName().isEmpty())
            AnalyzationDetails->setObjectName(QStringLiteral("AnalyzationDetails"));
        AnalyzationDetails->resize(751, 457);
        gridLayout = new QGridLayout(AnalyzationDetails);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_4);

        labelHeader = new QLabel(AnalyzationDetails);
        labelHeader->setObjectName(QStringLiteral("labelHeader"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelHeader->sizePolicy().hasHeightForWidth());
        labelHeader->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(15);
        labelHeader->setFont(font);

        verticalLayout->addWidget(labelHeader);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        labelDescriptionName = new QLabel(AnalyzationDetails);
        labelDescriptionName->setObjectName(QStringLiteral("labelDescriptionName"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelDescriptionName->sizePolicy().hasHeightForWidth());
        labelDescriptionName->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        labelDescriptionName->setFont(font1);

        horizontalLayout_4->addWidget(labelDescriptionName);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        labelWebsiteName = new QLabel(AnalyzationDetails);
        labelWebsiteName->setObjectName(QStringLiteral("labelWebsiteName"));
        sizePolicy.setHeightForWidth(labelWebsiteName->sizePolicy().hasHeightForWidth());
        labelWebsiteName->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setPointSize(12);
        labelWebsiteName->setFont(font2);

        horizontalLayout_4->addWidget(labelWebsiteName);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        labelDescriptionFlow = new QLabel(AnalyzationDetails);
        labelDescriptionFlow->setObjectName(QStringLiteral("labelDescriptionFlow"));
        sizePolicy1.setHeightForWidth(labelDescriptionFlow->sizePolicy().hasHeightForWidth());
        labelDescriptionFlow->setSizePolicy(sizePolicy1);
        labelDescriptionFlow->setFont(font1);

        horizontalLayout->addWidget(labelDescriptionFlow);

        horizontalSpacer_2 = new QSpacerItem(42, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        labelFlow = new QLabel(AnalyzationDetails);
        labelFlow->setObjectName(QStringLiteral("labelFlow"));
        sizePolicy.setHeightForWidth(labelFlow->sizePolicy().hasHeightForWidth());
        labelFlow->setSizePolicy(sizePolicy);
        labelFlow->setFont(font2);

        horizontalLayout->addWidget(labelFlow);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        line = new QFrame(AnalyzationDetails);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(AnalyzationDetails);

        QMetaObject::connectSlotsByName(AnalyzationDetails);
    } // setupUi

    void retranslateUi(QDialog *AnalyzationDetails)
    {
        AnalyzationDetails->setWindowTitle(QApplication::translate("AnalyzationDetails", "Details", 0));
        labelHeader->setText(QApplication::translate("AnalyzationDetails", "Website Details", 0));
        labelDescriptionName->setText(QApplication::translate("AnalyzationDetails", "Website Name:", 0));
        labelWebsiteName->setText(QString());
        labelDescriptionFlow->setText(QApplication::translate("AnalyzationDetails", "Used Flow:", 0));
        labelFlow->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AnalyzationDetails: public Ui_AnalyzationDetails {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYZATIONDETAILS_H
