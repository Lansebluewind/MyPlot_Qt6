#include "myplot.h"

//********************图表接口**************************//

QChart* MyPlot::initChart(QWidget* widget, std::string name)
{
	m_chart = new QChart();
	m_chart->setTitle(name.c_str());

	// 创建并设置X轴
	QValueAxis* m_axisX = new QValueAxis;
	m_axisX->setRange(m_xRange.first, m_xRange.second);
	m_axisX->setTitleText("X");
	m_chart->addAxis(m_axisX, Qt::AlignBottom);

	// 创建并设置Y轴
	QValueAxis* m_axisY = new QValueAxis;
	m_axisY->setRange(m_yRange.first, m_yRange.second);
	m_axisY->setTitleText("Y");
	m_chart->addAxis(m_axisY, Qt::AlignLeft);

	// 默认添加2条曲线
	m_seriesList.clear();
	for (int i = 0; i < 2; ++i)
	{
		QLineSeries* series = new QLineSeries();
		series->setName(QString("曲线%1").arg(i + 1));
		m_chart->addSeries(series);
		series->attachAxis(m_axisX);
		series->attachAxis(m_axisY);
		std::string name = std::string("曲线") + std::to_string(i + 1);
		m_seriesList.push_back(std::make_pair(series, name));
	}

	// 使用简化版的 CustomChartView，只有坐标显示功能
	m_chartView = new CustomChartView(m_chart);
	m_chartView->setRenderHint(QPainter::Antialiasing);
	// 使用原生缩放功能
	m_chartView->setRubberBand(QChartView::RectangleRubberBand);



	QVBoxLayout* layout = new QVBoxLayout(widget);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	layout->addWidget(m_chartView);
	widget->setLayout(layout);

	return m_chart;
}

void MyPlot::setAxisRange(double xMin, double xMax, double yMin, double yMax)
{
	QValueAxis* axisX = qobject_cast<QValueAxis*>( m_chart->axes(Qt::Horizontal).first() );
	QValueAxis* axisY = qobject_cast<QValueAxis*>( m_chart->axes(Qt::Vertical).first() );

	if (axisX)
		axisX->setRange(xMin, xMax);
	if (axisY)
		axisY->setRange(yMin, yMax);
	m_xRange = std::make_pair(xMin, xMax);
	m_yRange = std::make_pair(yMin, yMax);
}

//*********************曲线操作接口**************************//

bool MyPlot::addSeries(const std::string& name, const QColor& color)
{
	// 检查是否已存在同名曲线
	for (const auto& pair : m_seriesList)
	{
		if (pair.second == name)
		{
			return true; // 已存在，直接返回
		}
	}

	// 创建新曲线并添加到图表
	QLineSeries* newSeries = new QLineSeries();
	newSeries->setName(QString::fromStdString(name));

	// 设置曲线颜色(如果提供了有效颜色)
	if (color.isValid())
	{
		newSeries->setColor(color);
		QPen pen = newSeries->pen();
		pen.setColor(color);
		pen.setWidth(2); // 可选:设置线宽
		newSeries->setPen(pen);
	}

	m_chart->addSeries(newSeries);

	// 获取当前的坐标轴
	QValueAxis* m_axisX = qobject_cast<QValueAxis*>( m_chart->axes(Qt::Horizontal).first() );
	QValueAxis* m_axisY = qobject_cast<QValueAxis*>( m_chart->axes(Qt::Vertical).first() );
	newSeries->attachAxis(m_axisX);
	newSeries->attachAxis(m_axisY);

	// 添加到曲线列表
	m_seriesList.push_back(std::make_pair(newSeries, name));
	return true;
}

bool MyPlot::updateData(const std::string& name, const QVector<QPointF>& points)
{
	for (auto& pair : m_seriesList)
	{
		if (pair.second == name)
		{
			pair.first->replace(points);
			return true;
		}
	}
	return false; // 未找到同名曲线
}

bool MyPlot::setSeriesStyle(const std::string& name, const QPen& pen, const QBrush& brush)
{
	for (auto& pair : m_seriesList)
	{
		if (pair.second == name)
		{
			pair.first->setPen(pen);
			pair.first->setBrush(brush);
			return true;
		}
	}
	return false; // 未找到同名曲线
}

bool MyPlot::setSeriesVisible(const std::string& name, bool visible)
{
	for (auto& pair : m_seriesList)
	{
		if (pair.second == name)
		{
			pair.first->setVisible(visible);
			return true;
		}
	}
	return false; // 未找到同名曲线
}

bool MyPlot::setAllSeriesVisible(bool visible)
{
	for (auto& pair : m_seriesList)
	{
		pair.first->setVisible(visible);
	}
	return true;
}

bool MyPlot::batchUpdate(const QVector<std::pair<std::string, QVector<QPointF>>>& dataList)
{
	bool allFound = true;
	setAllSeriesVisible(false); // 先隐藏所有曲线
	for (const auto& dataPair : dataList)
	{
		const std::string& name = dataPair.first;
		const QVector<QPointF>& points = dataPair.second;
		bool found = false;
		for (auto& pair : m_seriesList)
		{
			if (pair.second == name)
			{
				pair.first->replace(points);
				found = true;
				break;
			}
		}
		if (!found)
		{
			allFound = false; // 有未找到的曲线
		}
	}
	setAllSeriesVisible(true); // 更新数据后显示所有曲线
	return allFound; // 如果所有曲线都找到了，返回true，否则返回false
}


bool MyPlot::renameSeries(const std::string& oldName, const std::string& newName)
{
	// 检查新名称是否已存在
	for (const auto& pair : m_seriesList)
	{
		if (pair.second == newName)
		{
			return false; // 新名称已存在，重命名失败
		}
	}
	for (auto& pair : m_seriesList)
	{
		if (pair.second == oldName)
		{
			pair.second = newName;
			pair.first->setName(QString::fromStdString(newName));
			return true; // 重命名成功
		}
	}
	return false; // 未找到旧名称的曲线
}

size_t MyPlot::seriesCount() const
{
	return m_seriesList.size();
}

bool MyPlot::removeSeriesByName(const std::string& name)
{
	for (int i = 0; i < m_seriesList.size(); ++i)
	{
		if (m_seriesList[i].second == name)
		{
			QLineSeries* series = m_seriesList[i].first;
			m_chart->removeSeries(series);
			delete series; // 释放内存
			m_seriesList.remove(i);
			return true;
		}
	}
	return false; // 未找到同名曲线
}

void MyPlot::clearAllSeries()
{
	for (auto& pair : m_seriesList)
	{
		m_chart->removeSeries(pair.first);
		delete pair.first; // 释放内存
	}
	m_seriesList.clear();
}



//********************************鼠标交互********************************************//

bool MyPlot::isCoordinateDisplayEnabled() const
{
	return	m_showCoordinates;
}

bool MyPlot::isRubberBandEnabled() const
{
	return m_enableRubberBand;
}

void MyPlot::enableCoordinateDisplay(bool enable)
{
	if (m_chartView)
	{
		// 使用 CustomChartView 的坐标显示功能
		CustomChartView* customView = static_cast<CustomChartView*>( m_chartView );
		customView->setCoordinateDisplayEnabled(enable);
		m_showCoordinates = enable;
	}
}

void MyPlot::enableRubberBand(bool enable)
{
	if (m_chartView)
	{
		// 使用Qt Charts原生的橡皮筋功能，而不是自定义的
		if (enable)
			m_chartView->setRubberBand(QChartView::RectangleRubberBand);
		else
			m_chartView->setRubberBand(QChartView::NoRubberBand);
		m_enableRubberBand = enable;
	}

}


void MyPlot::setRubberBandMode(int mode)
{
	if (m_chartView)
		m_chartView->setRubberBand(static_cast<QChartView::RubberBand>( mode ));
}

void MyPlot::zoomIn(const QRectF& rect)
{
	if (m_chart)
		m_chart->zoomIn(rect);
}

void MyPlot::zoom(qreal factor)
{
	if (m_chart)
		m_chart->zoom(factor);
}

void MyPlot::zoomReset()
{
	if (!m_chart || !m_chartView)
		return;

	// 调用标准的 zoomReset
	m_chart->zoomReset();

	// 恢复到初始范围
	QValueAxis* xAxis = qobject_cast<QValueAxis*>( m_chart->axes(Qt::Horizontal).first() );
	QValueAxis* yAxis = qobject_cast<QValueAxis*>( m_chart->axes(Qt::Vertical).first() );

	if (xAxis)
		xAxis->setRange(m_xRange.first, m_xRange.second);
	if (yAxis)
		yAxis->setRange(m_yRange.first, m_yRange.second);

	// 重置视图变换
	m_chartView->resetTransform();

	// 强制更新
	m_chart->update();
	m_chartView->viewport()->update();
}

//********************实例函数**************************//
void MyPlot::initWithExample1(QWidget* widget)
{
	const double PI = 3.14159265358979323846;

	// 直接初始化当前对象
	this->initChart(widget);
	this->enableRubberBand(true);
	this->enableCoordinateDisplay(true);
	this->setAxisRange(0, 2 * PI, -6, 6);

	// 添加2条正弦曲线
	int numPoints = 100;
	QVector<QPointF> points1, points2;
	for (int i = 0; i <= numPoints; ++i)
	{
		double x = ( 2 * PI / numPoints ) * i;
		points1.append(QPointF(x, 5 * sin(x)));
		points2.append(QPointF(x, 5 * cos(x)));
	}

	this->addSeries("曲线1", Qt::red);
	this->addSeries("曲线2", Qt::blue);

	this->setAllSeriesVisible(false);
	this->updateData("曲线1", points1);
	this->updateData("曲线2", points2);
	this->setAllSeriesVisible(true);
}