#include "test.h"
#include <QMessageBox>
#include <QTimer>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis> // 头文件放在文件顶部
#include<string>
#include<vector>

static void show2(MyPlot* m_plot_test2, QWidget* widget)
{
	const double PI = 3.14159265358979323846;

	// 直接初始化当前对象
	m_plot_test2->initChart(widget);
	m_plot_test2->enableRubberBand(true);
	m_plot_test2->enableCoordinateDisplay(true);
	m_plot_test2->setAxisRange(0, 2 * PI, -6, 6);

	// 添加2条正弦曲线
	int numPoints = 100;
	m_plot_test2->addSeries("正弦", Qt::red);
	m_plot_test2->addSeries("余弦", Qt::blue);
}

test::test(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// 初始化图表并添加到UI
	m_plot_test1.initWithExample1(ui.widgetChart1);
	show2(&m_plot_test2, ui.widgetChart2);
	//**************************鼠标交互功能**************************//

	//根据当前状态设置按钮文字
	if (m_plot_test1.isCoordinateDisplayEnabled())
		ui.display_xy->setText("隐藏坐标");
	else
		ui.display_xy->setText("显示坐标");


	//复位缩放按钮，点击后复位图表缩放
	connect(ui.zoom_reset, &QPushButton::clicked, this, [=]()
		{
			m_plot_test1.zoomReset();
			m_plot_test2.zoomReset();
		});

	//显示鼠标坐标按钮，点击后显示/隐藏鼠标坐标，且按钮文字切换
	connect(ui.display_xy, &QPushButton::clicked, this, [=]()
		{
			static bool display = m_plot_test1.isCoordinateDisplayEnabled();
			display = !display;
			m_plot_test1.enableCoordinateDisplay(display);
			m_plot_test2.enableCoordinateDisplay(display);
			if (display)
				ui.display_xy->setText("隐藏坐标");
			else
				ui.display_xy->setText("显示坐标");
		});


	// 定时器动态更新数据
	QTimer* timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, [=]()
		{
			static double phase = 0;
			//得到当前坐标系范围
			auto [xRange, yRange] = m_plot_test2.getAxisRange();
			const double PI = 3.14159265358979323846;
			int numPoints = 8000;
			QVector<QPointF> sineData, cosineData;
			//生成新数据
			QVector<std::pair<std::string, QVector<QPointF>>> dataList;
			dataList.resize(2);
			dataList[0].first = "正弦";
			dataList[1].first = "余弦";

			// 直接用引用操作原始容器
			QVector<QPointF>& sineDataRef = dataList[0].second;
			QVector<QPointF>& cosineDataRef = dataList[1].second;

			sineDataRef.reserve(numPoints);
			cosineDataRef.reserve(numPoints);
			for (int i = 0; i <= numPoints; ++i)
			{
				double x = ( 2 * PI / numPoints ) * i;
				sineDataRef.push_back(QPointF(x, 5 * sin(x + phase)));
				cosineDataRef.push_back(QPointF(x, 5 * cos(x + phase)));
			}
			// 只传 dataList，不会有多余拷贝
			m_plot_test2.batchUpdate(dataList);
			phase += 0.1;
			if (phase > 2 * PI) phase = 0;
		});
	timer->start(16);
}

test::~test()
{}
