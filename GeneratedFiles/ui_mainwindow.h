/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDial>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "gltest.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad;
    QAction *actionSave;
    QAction *actionFlower;
    QAction *actionTree;
    QWidget *centralWidget;
    GLTest *widget;
    QPushButton *buttonRead;
    QPushButton *buttonSave;
    QGroupBox *groupBox;
    QTabWidget *tabTree;
    QWidget *tab;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QLineEdit *lineTreeLevel;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLineEdit *lineTreeWidth;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *lineTreeHeight;
    QWidget *tab_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_7;
    QRadioButton *radioFlowerA;
    QRadioButton *radioFlowerB;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_8;
    QLineEdit *lineFlowerLevels;
    QLabel *label_9;
    QLineEdit *lineFlowerLevenCnt;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_10;
    QRadioButton *radioFTexture1;
    QRadioButton *radioFTexture2;
    QRadioButton *radioFTexture3;
    QRadioButton *radioFTexture4;
    QGroupBox *groupBox_4;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioTree;
    QRadioButton *radioFlowers;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_13;
    QScrollBar *scrollFlakeCount;
    QLabel *labelFlakeCount;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_12;
    QScrollBar *scrollSnowArea;
    QLabel *labelSnowArea;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label;
    QScrollBar *scrollFalSpeed;
    QLabel *labelFallSpeed;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_14;
    QScrollBar *scrollMeltSpeed;
    QLabel *labelTemperature;
    QWidget *tab_4;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_15;
    QDial *dialWind;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_16;
    QScrollBar *scrollWindLevel;
    QLabel *labelWindLevel;
    QGroupBox *groupBox_2;
    QPushButton *buttonCreate;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1344, 594);
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionFlower = new QAction(MainWindow);
        actionFlower->setObjectName(QStringLiteral("actionFlower"));
        actionTree = new QAction(MainWindow);
        actionTree->setObjectName(QStringLiteral("actionTree"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new GLTest(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 811, 571));
        widget->setFocusPolicy(Qt::StrongFocus);
        buttonRead = new QPushButton(centralWidget);
        buttonRead->setObjectName(QStringLiteral("buttonRead"));
        buttonRead->setGeometry(QRect(1180, 280, 101, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        buttonRead->setFont(font);
        buttonSave = new QPushButton(centralWidget);
        buttonSave->setObjectName(QStringLiteral("buttonSave"));
        buttonSave->setGeometry(QRect(1180, 350, 101, 51));
        buttonSave->setFont(font);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(830, 10, 331, 321));
        groupBox->setFont(font);
        tabTree = new QTabWidget(groupBox);
        tabTree->setObjectName(QStringLiteral("tabTree"));
        tabTree->setGeometry(QRect(10, 100, 311, 211));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayoutWidget = new QWidget(tab);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 281, 161));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);

        horizontalLayout_4->addWidget(label_5);

        lineTreeLevel = new QLineEdit(verticalLayoutWidget);
        lineTreeLevel->setObjectName(QStringLiteral("lineTreeLevel"));

        horizontalLayout_4->addWidget(lineTreeLevel);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);

        horizontalLayout_3->addWidget(label_4);

        lineTreeWidth = new QLineEdit(verticalLayoutWidget);
        lineTreeWidth->setObjectName(QStringLiteral("lineTreeWidth"));

        horizontalLayout_3->addWidget(lineTreeWidth);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        horizontalLayout_2->addWidget(label_3);

        lineTreeHeight = new QLineEdit(verticalLayoutWidget);
        lineTreeHeight->setObjectName(QStringLiteral("lineTreeHeight"));

        horizontalLayout_2->addWidget(lineTreeHeight);


        verticalLayout->addLayout(horizontalLayout_2);

        tabTree->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        layoutWidget = new QWidget(tab_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(7, 10, 291, 161));
        verticalLayout_6 = new QVBoxLayout(layoutWidget);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font);

        horizontalLayout_5->addWidget(label_7);

        radioFlowerA = new QRadioButton(layoutWidget);
        radioFlowerA->setObjectName(QStringLiteral("radioFlowerA"));
        radioFlowerA->setFont(font);

        horizontalLayout_5->addWidget(radioFlowerA);

        radioFlowerB = new QRadioButton(layoutWidget);
        radioFlowerB->setObjectName(QStringLiteral("radioFlowerB"));
        radioFlowerB->setFont(font);
        radioFlowerB->setChecked(true);

        horizontalLayout_5->addWidget(radioFlowerB);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font);

        horizontalLayout_6->addWidget(label_8);

        lineFlowerLevels = new QLineEdit(layoutWidget);
        lineFlowerLevels->setObjectName(QStringLiteral("lineFlowerLevels"));

        horizontalLayout_6->addWidget(lineFlowerLevels);


        verticalLayout_2->addLayout(horizontalLayout_6);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFont(font);

        verticalLayout_2->addWidget(label_9);

        lineFlowerLevenCnt = new QLineEdit(layoutWidget);
        lineFlowerLevenCnt->setObjectName(QStringLiteral("lineFlowerLevenCnt"));

        verticalLayout_2->addWidget(lineFlowerLevenCnt);


        verticalLayout_6->addLayout(verticalLayout_2);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setFont(font);

        horizontalLayout_8->addWidget(label_10);

        radioFTexture1 = new QRadioButton(layoutWidget);
        radioFTexture1->setObjectName(QStringLiteral("radioFTexture1"));
        radioFTexture1->setFont(font);

        horizontalLayout_8->addWidget(radioFTexture1);

        radioFTexture2 = new QRadioButton(layoutWidget);
        radioFTexture2->setObjectName(QStringLiteral("radioFTexture2"));
        radioFTexture2->setFont(font);

        horizontalLayout_8->addWidget(radioFTexture2);

        radioFTexture3 = new QRadioButton(layoutWidget);
        radioFTexture3->setObjectName(QStringLiteral("radioFTexture3"));
        radioFTexture3->setFont(font);

        horizontalLayout_8->addWidget(radioFTexture3);

        radioFTexture4 = new QRadioButton(layoutWidget);
        radioFTexture4->setObjectName(QStringLiteral("radioFTexture4"));
        radioFTexture4->setFont(font);
        radioFTexture4->setChecked(true);

        horizontalLayout_8->addWidget(radioFTexture4);


        verticalLayout_6->addLayout(horizontalLayout_8);

        tabTree->addTab(tab_2, QString());
        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 20, 311, 71));
        horizontalLayoutWidget = new QWidget(groupBox_4);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 20, 191, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        radioTree = new QRadioButton(horizontalLayoutWidget);
        radioTree->setObjectName(QStringLiteral("radioTree"));
        radioTree->setFont(font);
        radioTree->setChecked(true);

        horizontalLayout->addWidget(radioTree);

        radioFlowers = new QRadioButton(horizontalLayoutWidget);
        radioFlowers->setObjectName(QStringLiteral("radioFlowers"));
        radioFlowers->setFont(font);

        horizontalLayout->addWidget(radioFlowers);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(840, 360, 311, 181));
        tabWidget->setFont(font);
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        layoutWidget1 = new QWidget(tab_3);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 19, 291, 121));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_13 = new QLabel(layoutWidget1);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setFont(font);

        horizontalLayout_9->addWidget(label_13);

        scrollFlakeCount = new QScrollBar(layoutWidget1);
        scrollFlakeCount->setObjectName(QStringLiteral("scrollFlakeCount"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollFlakeCount->sizePolicy().hasHeightForWidth());
        scrollFlakeCount->setSizePolicy(sizePolicy);
        scrollFlakeCount->setMaximum(80000);
        scrollFlakeCount->setValue(2000);
        scrollFlakeCount->setOrientation(Qt::Horizontal);

        horizontalLayout_9->addWidget(scrollFlakeCount);

        labelFlakeCount = new QLabel(layoutWidget1);
        labelFlakeCount->setObjectName(QStringLiteral("labelFlakeCount"));

        horizontalLayout_9->addWidget(labelFlakeCount);


        verticalLayout_3->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_12 = new QLabel(layoutWidget1);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setFont(font);

        horizontalLayout_10->addWidget(label_12);

        scrollSnowArea = new QScrollBar(layoutWidget1);
        scrollSnowArea->setObjectName(QStringLiteral("scrollSnowArea"));
        sizePolicy.setHeightForWidth(scrollSnowArea->sizePolicy().hasHeightForWidth());
        scrollSnowArea->setSizePolicy(sizePolicy);
        scrollSnowArea->setMinimum(1);
        scrollSnowArea->setMaximum(90);
        scrollSnowArea->setValue(50);
        scrollSnowArea->setOrientation(Qt::Horizontal);

        horizontalLayout_10->addWidget(scrollSnowArea);

        labelSnowArea = new QLabel(layoutWidget1);
        labelSnowArea->setObjectName(QStringLiteral("labelSnowArea"));

        horizontalLayout_10->addWidget(labelSnowArea);


        verticalLayout_3->addLayout(horizontalLayout_10);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);

        horizontalLayout_13->addWidget(label);

        scrollFalSpeed = new QScrollBar(layoutWidget1);
        scrollFalSpeed->setObjectName(QStringLiteral("scrollFalSpeed"));
        sizePolicy.setHeightForWidth(scrollFalSpeed->sizePolicy().hasHeightForWidth());
        scrollFalSpeed->setSizePolicy(sizePolicy);
        scrollFalSpeed->setValue(30);
        scrollFalSpeed->setOrientation(Qt::Horizontal);

        horizontalLayout_13->addWidget(scrollFalSpeed);

        labelFallSpeed = new QLabel(layoutWidget1);
        labelFallSpeed->setObjectName(QStringLiteral("labelFallSpeed"));

        horizontalLayout_13->addWidget(labelFallSpeed);


        verticalLayout_3->addLayout(horizontalLayout_13);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_14 = new QLabel(layoutWidget1);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setFont(font);

        horizontalLayout_11->addWidget(label_14);

        scrollMeltSpeed = new QScrollBar(layoutWidget1);
        scrollMeltSpeed->setObjectName(QStringLiteral("scrollMeltSpeed"));
        sizePolicy.setHeightForWidth(scrollMeltSpeed->sizePolicy().hasHeightForWidth());
        scrollMeltSpeed->setSizePolicy(sizePolicy);
        scrollMeltSpeed->setMaximum(30);
        scrollMeltSpeed->setOrientation(Qt::Horizontal);

        horizontalLayout_11->addWidget(scrollMeltSpeed);

        labelTemperature = new QLabel(layoutWidget1);
        labelTemperature->setObjectName(QStringLiteral("labelTemperature"));

        horizontalLayout_11->addWidget(labelTemperature);


        verticalLayout_3->addLayout(horizontalLayout_11);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        layoutWidget2 = new QWidget(tab_4);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(21, 21, 269, 72));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_15 = new QLabel(layoutWidget2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setFont(font);

        horizontalLayout_7->addWidget(label_15);

        dialWind = new QDial(layoutWidget2);
        dialWind->setObjectName(QStringLiteral("dialWind"));
        dialWind->setMaximum(360);

        horizontalLayout_7->addWidget(dialWind);

        layoutWidget3 = new QWidget(tab_4);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(20, 110, 261, 19));
        horizontalLayout_12 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        label_16 = new QLabel(layoutWidget3);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setFont(font);

        horizontalLayout_12->addWidget(label_16);

        scrollWindLevel = new QScrollBar(layoutWidget3);
        scrollWindLevel->setObjectName(QStringLiteral("scrollWindLevel"));
        sizePolicy.setHeightForWidth(scrollWindLevel->sizePolicy().hasHeightForWidth());
        scrollWindLevel->setSizePolicy(sizePolicy);
        scrollWindLevel->setMaximum(20);
        scrollWindLevel->setOrientation(Qt::Horizontal);

        horizontalLayout_12->addWidget(scrollWindLevel);

        labelWindLevel = new QLabel(layoutWidget3);
        labelWindLevel->setObjectName(QStringLiteral("labelWindLevel"));

        horizontalLayout_12->addWidget(labelWindLevel);

        tabWidget->addTab(tab_4, QString());
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(830, 340, 331, 211));
        groupBox_2->setFont(font);
        buttonCreate = new QPushButton(centralWidget);
        buttonCreate->setObjectName(QStringLiteral("buttonCreate"));
        buttonCreate->setGeometry(QRect(1180, 200, 101, 61));
        buttonCreate->setFont(font);
        MainWindow->setCentralWidget(centralWidget);
        groupBox_2->raise();
        widget->raise();
        buttonRead->raise();
        buttonSave->raise();
        groupBox->raise();
        tabWidget->raise();
        buttonCreate->raise();
        label->raise();
        labelFallSpeed->raise();
        scrollFalSpeed->raise();
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabTree->setCurrentIndex(0);
        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionLoad->setText(QApplication::translate("MainWindow", "Load", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
        actionFlower->setText(QApplication::translate("MainWindow", "Flower", 0));
        actionTree->setText(QApplication::translate("MainWindow", "Tree", 0));
        buttonRead->setText(QApplication::translate("MainWindow", "\350\257\273\345\217\226\346\226\207\344\273\266", 0));
        buttonSave->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\346\226\207\344\273\266", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "\346\226\260\345\273\272\346\244\215\346\240\252", 0));
        label_5->setText(QApplication::translate("MainWindow", "\345\261\202\346\225\260\357\274\2103-10\357\274\211", 0));
        lineTreeLevel->setText(QApplication::translate("MainWindow", "3", 0));
        label_4->setText(QApplication::translate("MainWindow", "\345\256\275\345\272\246\357\274\2102-6\357\274\211", 0));
        lineTreeWidth->setText(QApplication::translate("MainWindow", "2", 0));
        label_3->setText(QApplication::translate("MainWindow", "\351\253\230\345\272\246\357\274\2105-15\357\274\211", 0));
        lineTreeHeight->setText(QApplication::translate("MainWindow", "5", 0));
        tabTree->setTabText(tabTree->indexOf(tab), QApplication::translate("MainWindow", "\346\240\221\346\234\250\350\256\276\345\256\232", 0));
        label_7->setText(QApplication::translate("MainWindow", "\350\212\261\347\223\243\347\247\215\347\261\273", 0));
        radioFlowerA->setText(QApplication::translate("MainWindow", "\347\252\204\347\223\243", 0));
        radioFlowerB->setText(QApplication::translate("MainWindow", "\345\256\275\347\223\243", 0));
        label_8->setText(QApplication::translate("MainWindow", "\350\212\261\347\223\243\345\261\202\346\225\260\357\274\2103-6\357\274\211", 0));
        lineFlowerLevels->setText(QApplication::translate("MainWindow", "3", 0));
        label_9->setText(QApplication::translate("MainWindow", "\346\257\217\345\261\202\350\212\261\347\223\243\346\225\260\357\274\210\347\224\250\347\251\272\346\240\274\345\210\206\345\211\262\357\274\214\344\276\213\357\274\232\342\200\23420 20 10 10\342\200\235\357\274\211", 0));
        lineFlowerLevenCnt->setText(QApplication::translate("MainWindow", "4 4 4", 0));
        label_10->setText(QApplication::translate("MainWindow", "\347\272\271\347\220\206\347\247\215\347\261\273", 0));
        radioFTexture1->setText(QApplication::translate("MainWindow", "\347\231\275", 0));
        radioFTexture2->setText(QApplication::translate("MainWindow", "\347\201\260", 0));
        radioFTexture3->setText(QApplication::translate("MainWindow", "\347\272\242", 0));
        radioFTexture4->setText(QApplication::translate("MainWindow", "\347\262\211", 0));
        tabTree->setTabText(tabTree->indexOf(tab_2), QApplication::translate("MainWindow", "\350\212\261\347\223\243\350\256\276\345\256\232", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "\346\244\215\346\240\252\347\247\215\347\261\273", 0));
        radioTree->setText(QApplication::translate("MainWindow", "\346\240\221", 0));
        radioFlowers->setText(QApplication::translate("MainWindow", "\350\212\261", 0));
        label_13->setText(QApplication::translate("MainWindow", "\351\233\252\350\212\261\346\225\260\351\207\217", 0));
        labelFlakeCount->setText(QApplication::translate("MainWindow", "2000", 0));
        label_12->setText(QApplication::translate("MainWindow", "\344\270\213\351\233\252\351\235\242\347\247\257", 0));
        labelSnowArea->setText(QApplication::translate("MainWindow", "50", 0));
        label->setText(QApplication::translate("MainWindow", "\344\270\213\350\220\275\351\200\237\345\272\246", 0));
        labelFallSpeed->setText(QApplication::translate("MainWindow", "-0.05", 0));
        label_14->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\346\270\251\345\272\246", 0));
        labelTemperature->setText(QApplication::translate("MainWindow", "0", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "\351\233\252\350\212\261\346\216\247\345\210\266", 0));
        label_15->setText(QApplication::translate("MainWindow", "\351\243\216\345\220\221\350\260\203\350\212\202", 0));
        label_16->setText(QApplication::translate("MainWindow", "\351\243\216\345\212\233", 0));
        labelWindLevel->setText(QApplication::translate("MainWindow", "0", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "\351\243\216\345\212\233\346\216\247\345\210\266", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\347\216\257\345\242\203\346\216\247\345\210\266", 0));
        buttonCreate->setText(QApplication::translate("MainWindow", "\345\273\272\347\253\213\346\244\215\346\240\252", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
