/********************************************************************************
** Form generated from reading UI file 'test.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_H
#define UI_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_testClass
{
public:
    QWidget *centralWidget;
    QWidget *widgetChart1;
    QPushButton *zoom_reset;
    QPushButton *display_xy;
    QWidget *widgetChart2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *testClass)
    {
        if (testClass->objectName().isEmpty())
            testClass->setObjectName("testClass");
        testClass->resize(746, 623);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(testClass->sizePolicy().hasHeightForWidth());
        testClass->setSizePolicy(sizePolicy);
        testClass->setStyleSheet(QString::fromUtf8("QMainWindow { background-color: #F5F5DC; }\n"
"QWidget { color: #000000; }\n"
"QLineEdit{\n"
"    border: 1px solid #000000;\n"
"    color: #000000;\n"
"    background: #FFFFFF;\n"
"    border-radius: 10px;\n"
"}"));
        centralWidget = new QWidget(testClass);
        centralWidget->setObjectName("centralWidget");
        widgetChart1 = new QWidget(centralWidget);
        widgetChart1->setObjectName("widgetChart1");
        widgetChart1->setGeometry(QRect(0, 10, 351, 271));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widgetChart1->sizePolicy().hasHeightForWidth());
        widgetChart1->setSizePolicy(sizePolicy1);
        widgetChart1->setStyleSheet(QString::fromUtf8("QWidget{\n"
"    border: 2px inset #888888;\n"
"    color: #000000;\n"
"    background: #FFFFFF;\n"
"    border-radius: 10px;\n"
"    padding: 2px 8px;\n"
"    font-weight: bold;\n"
"	border-radius: 8px;\n"
"}"));
        zoom_reset = new QPushButton(centralWidget);
        zoom_reset->setObjectName("zoom_reset");
        zoom_reset->setGeometry(QRect(240, 310, 108, 40));
        QFont font;
        font.setBold(true);
        zoom_reset->setFont(font);
        zoom_reset->setAcceptDrops(false);
        zoom_reset->setAutoFillBackground(false);
        zoom_reset->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 6px;\n"
"    background: qlineargradient(\n"
"        x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #fdfdfd, stop:1 #c3c3c3\n"
"    );\n"
"    min-width: 80px;\n"
"    min-height: 28px;\n"
"    color: #222222;\n"
"    font-weight: bold;\n"
"    padding: 4px 12px;\n"
"    /* \350\275\273\345\276\256\345\244\226\351\230\264\345\275\261\357\274\214\345\242\236\345\274\272\347\253\213\344\275\223\346\204\237 */\n"
"    box-shadow: 1px 1px 3px #b0b0b0;\n"
"}\n"
"QPushButton:hover {\n"
"    background: qlineargradient(\n"
"        x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #eaeaea, stop:1 #bdbdbd\n"
"    );\n"
"    border: 2px solid #5a5a5a;\n"
"}\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(\n"
"        x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #c3c3c3, stop:1 #fdfdfd\n"
"    );\n"
"    border: 3px inset #5a5a5a;\n"
"}"));
        display_xy = new QPushButton(centralWidget);
        display_xy->setObjectName("display_xy");
        display_xy->setGeometry(QRect(360, 310, 108, 40));
        display_xy->setFont(font);
        display_xy->setAcceptDrops(false);
        display_xy->setAutoFillBackground(false);
        display_xy->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 6px;\n"
"    background: qlineargradient(\n"
"        x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #fdfdfd, stop:1 #c3c3c3\n"
"    );\n"
"    min-width: 80px;\n"
"    min-height: 28px;\n"
"    color: #222222;\n"
"    font-weight: bold;\n"
"    padding: 4px 12px;\n"
"    /* \350\275\273\345\276\256\345\244\226\351\230\264\345\275\261\357\274\214\345\242\236\345\274\272\347\253\213\344\275\223\346\204\237 */\n"
"    box-shadow: 1px 1px 3px #b0b0b0;\n"
"}\n"
"QPushButton:hover {\n"
"    background: qlineargradient(\n"
"        x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #eaeaea, stop:1 #bdbdbd\n"
"    );\n"
"    border: 2px solid #5a5a5a;\n"
"}\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(\n"
"        x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #c3c3c3, stop:1 #fdfdfd\n"
"    );\n"
"    border: 3px inset #5a5a5a;\n"
"}"));
        widgetChart2 = new QWidget(centralWidget);
        widgetChart2->setObjectName("widgetChart2");
        widgetChart2->setGeometry(QRect(360, 10, 371, 271));
        sizePolicy1.setHeightForWidth(widgetChart2->sizePolicy().hasHeightForWidth());
        widgetChart2->setSizePolicy(sizePolicy1);
        widgetChart2->setStyleSheet(QString::fromUtf8("QWidget{\n"
"    border: 2px inset #888888;\n"
"    color: #000000;\n"
"    background: #FFFFFF;\n"
"    border-radius: 10px;\n"
"    padding: 2px 8px;\n"
"    font-weight: bold;\n"
"	border-radius: 8px;\n"
"}"));
        testClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(testClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 746, 21));
        testClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(testClass);
        mainToolBar->setObjectName("mainToolBar");
        testClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(testClass);
        statusBar->setObjectName("statusBar");
        testClass->setStatusBar(statusBar);

        retranslateUi(testClass);

        QMetaObject::connectSlotsByName(testClass);
    } // setupUi

    void retranslateUi(QMainWindow *testClass)
    {
        testClass->setWindowTitle(QCoreApplication::translate("testClass", "test", nullptr));
        zoom_reset->setText(QCoreApplication::translate("testClass", "\345\244\215\344\275\215", nullptr));
        display_xy->setText(QCoreApplication::translate("testClass", "\346\230\276\347\244\272/\351\232\220\350\227\217\345\235\220\346\240\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class testClass: public Ui_testClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_H
