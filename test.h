#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_test.h"
#include "myplot.h"
class test : public QMainWindow
{
	Q_OBJECT

public:
	test(QWidget* parent = nullptr);
	~test();

private:
	Ui::testClass ui;
public:
	MyPlot m_plot_test1;
	MyPlot m_plot_test2;

};

