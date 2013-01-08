/********************************************************************************
** Form generated from reading UI file 'Exp.ui'
**
** Created: Sun 29. Jul 18:50:29 2012
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXP_H
#define UI_EXP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QSlider *minSlider;
    QSlider *maxSlider;
    QLabel *labelMinSlider;
    QLabel *labelMaxSlider;
    QWidget *widgetTopRight;
    QCheckBox *checkBoxDiff;
    QSlider *ROISlider;
    QLabel *labelROI;
    QPushButton *buttonLeft;
    QPushButton *buttonUp;
    QPushButton *buttonDown;
    QPushButton *buttonRight;
    QWidget *widgetTopLeft;
    QPushButton *lineButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(678, 432);
        minSlider = new QSlider(Form);
        minSlider->setObjectName(QString::fromUtf8("minSlider"));
        minSlider->setGeometry(QRect(9, 30, 651, 20));
        minSlider->setOrientation(Qt::Horizontal);
        maxSlider = new QSlider(Form);
        maxSlider->setObjectName(QString::fromUtf8("maxSlider"));
        maxSlider->setGeometry(QRect(10, 100, 651, 20));
        maxSlider->setOrientation(Qt::Horizontal);
        labelMinSlider = new QLabel(Form);
        labelMinSlider->setObjectName(QString::fromUtf8("labelMinSlider"));
        labelMinSlider->setGeometry(QRect(10, 10, 111, 16));
        labelMaxSlider = new QLabel(Form);
        labelMaxSlider->setObjectName(QString::fromUtf8("labelMaxSlider"));
        labelMaxSlider->setGeometry(QRect(10, 80, 111, 16));
        labelMaxSlider->setLayoutDirection(Qt::LeftToRight);
        widgetTopRight = new QWidget(Form);
        widgetTopRight->setObjectName(QString::fromUtf8("widgetTopRight"));
        widgetTopRight->setGeometry(QRect(340, 181, 320, 240));
        checkBoxDiff = new QCheckBox(Form);
        checkBoxDiff->setObjectName(QString::fromUtf8("checkBoxDiff"));
        checkBoxDiff->setGeometry(QRect(10, 60, 111, 17));
        ROISlider = new QSlider(Form);
        ROISlider->setObjectName(QString::fromUtf8("ROISlider"));
        ROISlider->setGeometry(QRect(80, 140, 391, 19));
        ROISlider->setOrientation(Qt::Horizontal);
        labelROI = new QLabel(Form);
        labelROI->setObjectName(QString::fromUtf8("labelROI"));
        labelROI->setGeometry(QRect(10, 140, 81, 16));
        buttonLeft = new QPushButton(Form);
        buttonLeft->setObjectName(QString::fromUtf8("buttonLeft"));
        buttonLeft->setGeometry(QRect(490, 130, 21, 23));
        buttonUp = new QPushButton(Form);
        buttonUp->setObjectName(QString::fromUtf8("buttonUp"));
        buttonUp->setGeometry(QRect(520, 120, 21, 23));
        buttonDown = new QPushButton(Form);
        buttonDown->setObjectName(QString::fromUtf8("buttonDown"));
        buttonDown->setGeometry(QRect(520, 140, 21, 23));
        buttonRight = new QPushButton(Form);
        buttonRight->setObjectName(QString::fromUtf8("buttonRight"));
        buttonRight->setGeometry(QRect(550, 130, 21, 23));
        widgetTopLeft = new QWidget(Form);
        widgetTopLeft->setObjectName(QString::fromUtf8("widgetTopLeft"));
        widgetTopLeft->setGeometry(QRect(10, 180, 320, 240));
        lineButton = new QPushButton(Form);
        lineButton->setObjectName(QString::fromUtf8("lineButton"));
        lineButton->setGeometry(QRect(590, 130, 75, 23));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
        labelMinSlider->setText(QApplication::translate("Form", "Min Slider: 0", 0, QApplication::UnicodeUTF8));
        labelMaxSlider->setText(QApplication::translate("Form", "Max Slider: 0", 0, QApplication::UnicodeUTF8));
        checkBoxDiff->setText(QApplication::translate("Form", "Lock Difference", 0, QApplication::UnicodeUTF8));
        labelROI->setText(QApplication::translate("Form", "ROI: 1", 0, QApplication::UnicodeUTF8));
        buttonLeft->setText(QApplication::translate("Form", "<", 0, QApplication::UnicodeUTF8));
        buttonUp->setText(QApplication::translate("Form", "/\\", 0, QApplication::UnicodeUTF8));
        buttonDown->setText(QApplication::translate("Form", "\\/", 0, QApplication::UnicodeUTF8));
        buttonRight->setText(QApplication::translate("Form", ">", 0, QApplication::UnicodeUTF8));
        lineButton->setText(QApplication::translate("Form", "Lines", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXP_H
