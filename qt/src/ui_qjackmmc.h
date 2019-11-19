/********************************************************************************
** Form generated from reading UI file 'qjackmmc.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QJACKMMC_H
#define UI_QJACKMMC_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QjackMMC
{
public:
    QAction *actionQuit;
    QAction *actionWhat;
    QAction *actionAbout;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *fpsLabel;
    QLineEdit *jitterEdit;
    QLabel *jittterLabel;
    QLineEdit *fpsEdit;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QLineEdit *deviceEdit;
    QLabel *deviceLabel;
    QPushButton *whatsThisButton;
    QCheckBox *verboseBox;
    QSpacerItem *verticalSpacer;
    QCheckBox *rtBox;
    QTextEdit *messageArea;
    QMenuBar *menubar;
    QMenu *menuQJackMMC;
    QMenu *menu_Help;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *QjackMMC)
    {
        if (QjackMMC->objectName().isEmpty())
            QjackMMC->setObjectName(QString::fromUtf8("QjackMMC"));
        QjackMMC->resize(419, 362);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QjackMMC->sizePolicy().hasHeightForWidth());
        QjackMMC->setSizePolicy(sizePolicy);
        QjackMMC->setMinimumSize(QSize(419, 335));
        QjackMMC->setMaximumSize(QSize(419, 32767));
        actionQuit = new QAction(QjackMMC);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionWhat = new QAction(QjackMMC);
        actionWhat->setObjectName(QString::fromUtf8("actionWhat"));
        actionAbout = new QAction(QjackMMC);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralwidget = new QWidget(QjackMMC);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetFixedSize);
        fpsLabel = new QLabel(centralwidget);
        fpsLabel->setObjectName(QString::fromUtf8("fpsLabel"));
        fpsLabel->setLineWidth(2);

        gridLayout->addWidget(fpsLabel, 1, 1, 1, 1);

        jitterEdit = new QLineEdit(centralwidget);
        jitterEdit->setObjectName(QString::fromUtf8("jitterEdit"));
        jitterEdit->setMaxLength(5);

        gridLayout->addWidget(jitterEdit, 2, 0, 1, 1);

        jittterLabel = new QLabel(centralwidget);
        jittterLabel->setObjectName(QString::fromUtf8("jittterLabel"));

        gridLayout->addWidget(jittterLabel, 2, 1, 1, 1);

        fpsEdit = new QLineEdit(centralwidget);
        fpsEdit->setObjectName(QString::fromUtf8("fpsEdit"));
        fpsEdit->setMaxLength(4);

        gridLayout->addWidget(fpsEdit, 1, 0, 1, 1);

        loadButton = new QPushButton(centralwidget);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));

        gridLayout->addWidget(loadButton, 7, 0, 1, 1);

        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        gridLayout->addWidget(saveButton, 7, 1, 1, 1);

        deviceEdit = new QLineEdit(centralwidget);
        deviceEdit->setObjectName(QString::fromUtf8("deviceEdit"));
        deviceEdit->setMaxLength(2);

        gridLayout->addWidget(deviceEdit, 3, 0, 1, 1);

        deviceLabel = new QLabel(centralwidget);
        deviceLabel->setObjectName(QString::fromUtf8("deviceLabel"));

        gridLayout->addWidget(deviceLabel, 3, 1, 1, 1);

        whatsThisButton = new QPushButton(centralwidget);
        whatsThisButton->setObjectName(QString::fromUtf8("whatsThisButton"));

        gridLayout->addWidget(whatsThisButton, 5, 1, 1, 1);

        verboseBox = new QCheckBox(centralwidget);
        verboseBox->setObjectName(QString::fromUtf8("verboseBox"));

        gridLayout->addWidget(verboseBox, 5, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 6, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        rtBox = new QCheckBox(centralwidget);
        rtBox->setObjectName(QString::fromUtf8("rtBox"));

        verticalLayout->addWidget(rtBox);

        messageArea = new QTextEdit(centralwidget);
        messageArea->setObjectName(QString::fromUtf8("messageArea"));
        messageArea->setReadOnly(true);

        verticalLayout->addWidget(messageArea);

        QjackMMC->setCentralWidget(centralwidget);
        menubar = new QMenuBar(QjackMMC);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 419, 23));
        menuQJackMMC = new QMenu(menubar);
        menuQJackMMC->setObjectName(QString::fromUtf8("menuQJackMMC"));
        sizePolicy1.setHeightForWidth(menuQJackMMC->sizePolicy().hasHeightForWidth());
        menuQJackMMC->setSizePolicy(sizePolicy1);
        menu_Help = new QMenu(menubar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        QjackMMC->setMenuBar(menubar);
        statusbar = new QStatusBar(QjackMMC);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        sizePolicy1.setHeightForWidth(statusbar->sizePolicy().hasHeightForWidth());
        statusbar->setSizePolicy(sizePolicy1);
        QjackMMC->setStatusBar(statusbar);
#ifndef QT_NO_SHORTCUT
        fpsLabel->setBuddy(fpsEdit);
        jittterLabel->setBuddy(jitterEdit);
        deviceLabel->setBuddy(deviceEdit);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(fpsEdit, jitterEdit);
        QWidget::setTabOrder(jitterEdit, deviceEdit);
        QWidget::setTabOrder(deviceEdit, loadButton);
        QWidget::setTabOrder(loadButton, saveButton);

        menubar->addAction(menuQJackMMC->menuAction());
        menubar->addAction(menu_Help->menuAction());
        menuQJackMMC->addAction(actionQuit);
        menu_Help->addAction(actionWhat);
        menu_Help->addAction(actionAbout);

        retranslateUi(QjackMMC);

        QMetaObject::connectSlotsByName(QjackMMC);
    } // setupUi

    void retranslateUi(QMainWindow *QjackMMC)
    {
        QjackMMC->setWindowTitle(QApplication::translate("QjackMMC", "QjackMMC", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("QjackMMC", "&Quit", 0, QApplication::UnicodeUTF8));
        actionWhat->setText(QApplication::translate("QjackMMC", "&What's This?", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("QjackMMC", "&About", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        fpsLabel->setWhatsThis(QApplication::translate("QjackMMC", "The framerate (number of frames per second) of the device(s) connected to QjackMMC", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        fpsLabel->setText(QApplication::translate("QjackMMC", "&Frames / sec", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        jitterEdit->setWhatsThis(QApplication::translate("QjackMMC", "The maximum allowable difference between the JACK transport position and the time specified by an incoming MMC locate messages without changing the JACK position.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        jitterEdit->setInputMask(QString());
        jitterEdit->setText(QApplication::translate("QjackMMC", "50", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        jittterLabel->setWhatsThis(QApplication::translate("QjackMMC", "The maximum allowable difference between the JACK transport position and the time specified by an incoming MMC locate messages without changing the JACK position.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        jittterLabel->setText(QApplication::translate("QjackMMC", " &Jitter tolerance (ms)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        fpsEdit->setWhatsThis(QApplication::translate("QjackMMC", "The framerate (number of frames per second) of the device(s) connected to QjackMMC", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        fpsEdit->setInputMask(QString());
        fpsEdit->setText(QApplication::translate("QjackMMC", "30", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        loadButton->setWhatsThis(QApplication::translate("QjackMMC", "Load your last saved settings from ~/.qjackmmc", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        loadButton->setText(QApplication::translate("QjackMMC", "&Load saved defaults", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        saveButton->setWhatsThis(QApplication::translate("QjackMMC", "Save your current settings to ~/.qjackmmc", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        saveButton->setText(QApplication::translate("QjackMMC", "Save as &Default settings", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        deviceEdit->setWhatsThis(QApplication::translate("QjackMMC", "The device ID of the MIDI device controlling QJackMMC. If you don't know, it's probably 7f.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        deviceEdit->setText(QApplication::translate("QjackMMC", "7f", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        deviceLabel->setWhatsThis(QApplication::translate("QjackMMC", "The device ID of the MIDI device controlling QJackMMC. If you don't know, it's probably 7f.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        deviceLabel->setText(QApplication::translate("QjackMMC", "Device &ID in hexadecimal", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        whatsThisButton->setWhatsThis(QApplication::translate("QjackMMC", "It shows you messages like this. Now try clicking this then something else you want to know about.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        whatsThisButton->setText(QApplication::translate("QjackMMC", "&What does that do?", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        verboseBox->setWhatsThis(QApplication::translate("QjackMMC", "Check this to output verbose messages to the message area below.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        verboseBox->setText(QApplication::translate("QjackMMC", "&Verbose output", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        rtBox->setWhatsThis(QApplication::translate("QjackMMC", "Check this to schedule alsa sequencer polling with the highest allowable thread priority.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        rtBox->setText(QApplication::translate("QjackMMC", "Use &high priority thread for alsa polling", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        messageArea->setWhatsThis(QApplication::translate("QjackMMC", "if \"Verbose output\" is checked, text about any received MMC messages will appear here.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        menuQJackMMC->setTitle(QApplication::translate("QjackMMC", "&QJackMMC", 0, QApplication::UnicodeUTF8));
        menu_Help->setTitle(QApplication::translate("QjackMMC", "&Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QjackMMC: public Ui_QjackMMC {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QJACKMMC_H
