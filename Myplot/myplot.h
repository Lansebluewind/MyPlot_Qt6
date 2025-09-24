#ifndef MYPLOT_H
#define MYPLOT_H

#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>
#include <QApplication> 
#include <QMouseEvent>
#include <QToolTip>
#include <QVBoxLayout>
#include <string>
#include <vector>
#include <utility>
#include <QTimer>
#include <QMenu> 
#include <QFileDialog> 
#include<QMessageBox>

class CustomChartView : public QChartView
{
	Q_OBJECT


private:
	QPoint m_lastMousePos;
	QTimer* m_tooltipTimer = nullptr;
	QMenu* m_contextMenu = nullptr;
	bool m_showCoordinates = true;
	void exportCsvRequested();
public:
	explicit CustomChartView(QChart* chart, QWidget* parent = nullptr)
		: QChartView(chart, parent), m_showCoordinates(true)
	{
		setMouseTracking(true); // 启用鼠标跟踪

		m_tooltipTimer = new QTimer(this);
		m_tooltipTimer->setInterval(100); // 100ms 刷新一次
		connect(m_tooltipTimer, &QTimer::timeout, this, [this]()
			{
				if (m_showCoordinates && this->chart())
				{
					QRectF plotArea = this->chart()->plotArea();
					QPointF scenePos = mapToScene(m_lastMousePos);
					QPointF chartPos = this->chart()->mapFromScene(scenePos);
					if (plotArea.contains(chartPos))
					{
						QPointF value = this->chart()->mapToValue(chartPos);
						QString text = QString("X: %1, Y: %2").arg(value.x(), 0, 'f', 2).arg(value.y(), 0, 'f', 2);
						QToolTip::showText(mapToGlobal(m_lastMousePos), text, this);
					}
					else
					{
						QToolTip::hideText();// 超出区域，隐藏 tooltip
					}
				}
				else
				{
					QToolTip::hideText(); // 不显示坐标，隐藏 tooltip
				}
			});
	}

	// 启用/禁用鼠标坐标显示
	void setCoordinateDisplayEnabled(bool enable)
	{
		m_showCoordinates = enable;
	}

	bool getCoordinateDisplayEnabled() const
	{
		return m_showCoordinates;
	}
protected:

	void mousePressEvent(QMouseEvent* event) override
	{
		if (event->button() == Qt::RightButton)
		{
			// 菜单弹出前，停止坐标提示的定时器并隐藏提示，防止冲突
			if (m_tooltipTimer->isActive())
			{
				m_tooltipTimer->stop();
			}
			QToolTip::hideText();

			if (!m_contextMenu)
			{
				m_contextMenu = new QMenu(this);
				m_contextMenu->setWindowFlags(m_contextMenu->windowFlags() | Qt::WindowStaysOnTopHint); // 设置菜单在最上层显示
				QAction* exportAction = m_contextMenu->addAction("导出为 CSV");
				connect(exportAction, &QAction::triggered, this, &CustomChartView::exportCsvRequested);

				// 当菜单即将隐藏时，重新触发一次鼠标移动事件来恢复坐标提示的逻辑
				connect(m_contextMenu, &QMenu::aboutToHide, this, [this]()
					{
						// 模拟一个鼠标移动事件，以恢复 tooltip 的状态
						QPointF localPos = QPointF(m_lastMousePos);
						QPointF screenPos = mapToGlobal(m_lastMousePos);
						QMouseEvent* dummyEvent = new QMouseEvent(QEvent::MouseMove, localPos, screenPos, Qt::NoButton, Qt::NoButton, Qt::NoModifier);
						QApplication::postEvent(this, dummyEvent);
					});
			}
			m_contextMenu->popup(event->globalPosition().toPoint());
		}
		else
		{
			QChartView::mousePressEvent(event);
		}
	}


	// 重写鼠标移动事件，用于显示坐标
	void mouseMoveEvent(QMouseEvent* event) override
	{
		// 如果右键菜单可见，则不处理鼠标移动，防止意外关闭菜单
		if (m_contextMenu && m_contextMenu->isVisible())
		{
			return;
		}

		QChartView::mouseMoveEvent(event); // 先调用基类处理
		m_lastMousePos = event->pos();

		// 检查是否在 chart 区域内
		if (chart())
		{
			QRectF plotArea = chart()->plotArea();
			QPointF scenePos = mapToScene(m_lastMousePos);
			if (plotArea.contains(chart()->mapFromScene(scenePos)))
			{
				// 在区域内，确保 timer 启动
				if (!m_tooltipTimer->isActive())
					m_tooltipTimer->start();
			}
			else
			{
				// 超出区域，停止 timer 并隐藏 tooltip
				if (m_tooltipTimer->isActive())
					m_tooltipTimer->stop();
				QToolTip::hideText();
			}
		}
	}
};

class MyPlot
{
public:
	MyPlot() : m_chart(nullptr), m_chartView(nullptr)
	{}

	~MyPlot()
	{
		// 释放资源
		if (m_chartView)
		{
			// m_chartView 会自动释放 chart
			m_chartView = nullptr;
		}

		// 确保指针置空
		m_chart = nullptr;
		m_seriesList.clear();
	}

	//********************图表初始化接口**************************//

	// 初始化图表并添加到UI
	QChart* initChart(QWidget* widget, std::string name = "曲线图表");

	//更改坐标系范围
	void setAxisRange(double xMin, double xMax, double yMin, double yMax);

	//获取当前坐标系范围
	std::pair<std::pair<double, double>, std::pair<double, double>> getAxisRange() const
	{
		return { m_xRange, m_yRange };
	}

	//********************曲线操作接口**************************//

	// 添加新曲线,能够指定颜色，失败返回-1
	bool addSeries(const std::string& name, const QColor& color = QColor());

	// 根据曲线名称，更新所有曲线数据
	bool updateData(const std::string& name, const QVector<QPointF>& points);

	//图例、样式设置
	bool setSeriesStyle(const std::string& name, const QPen& pen, const QBrush& brush);

	//曲线显示/隐藏
	bool setSeriesVisible(const std::string& name, bool visible);
	//隐藏或显示所有曲线
	bool setAllSeriesVisible(bool visible);

	bool batchUpdate(const QVector<std::pair<std::string, QVector<QPointF>>>& dataList);

	//曲线重命名
	bool renameSeries(const std::string& oldName, const std::string& newName);

	// 获取曲线数量
	size_t seriesCount() const;

	// 清除所有曲线
	void clearAllSeries();
	//根据曲线名称删除曲线
	bool removeSeriesByName(const std::string& name);

	//********************************鼠标交互********************************************//

	//获取鼠标显示坐标状态
	bool isCoordinateDisplayEnabled() const;

	//获取鼠标区域选择放大功能状态
	bool isRubberBandEnabled() const;

	// 启用/禁用鼠标坐标显示
	void enableCoordinateDisplay(bool enable);
	// 启用/禁用鼠标区域选择放大功能
	void enableRubberBand(bool enable);
	// 设置鼠标交互模式（矩形选择、水平选择、垂直选择）
	/*
	myPlot.setRubberBandMode(QChartView::RectangleRubberBand);  // 矩形选择（默认）
	myPlot.setRubberBandMode(QChartView::HorizontalRubberBand); // 水平范围选择
	myPlot.setRubberBandMode(QChartView::VerticalRubberBand);   // 垂直范围选择
	*/
	void setRubberBandMode(int mode = QChartView::RectangleRubberBand);
	// 放大到指定区域
	void zoomIn(const QRectF& rect);
	// 按系数放大/缩小
	void zoom(qreal factor);
	// 复位缩放
	void zoomReset();


	//********************实例函数**************************//

	//显示2条正弦曲线，开启鼠标交互和坐标显示
	void initWithExample1(QWidget* widget);

private:
	QChart* m_chart;			// 保存图表指针
	QChartView* m_chartView;	// 保存图表视图指针

	std::pair<double, double> m_xRange = { 0, 100 };   // X轴范围
	std::pair<double, double> m_yRange = { -100, 100 }; // Y轴范围

	bool m_showCoordinates = true; // 是否显示鼠标坐标
	bool m_enableRubberBand = true; // 是否启用鼠标区域选择放大功能
	QVector<std::pair<QLineSeries*, std::string>> m_seriesList;// 曲线列表


};

#endif // MYPLOT_H