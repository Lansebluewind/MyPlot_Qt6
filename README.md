高效 Qt Charts 动态曲线图表库，支持多曲线批量刷新、鼠标交互、原生缩放、坐标显示等功能。适用于科学绘图、实时数据可视化等场景。

一、主要特性

    1、多曲线管理：支持动态添加/删除/重命名曲线，按名称操作，无需下标映射
    2、高效批量刷新：支持 8000 点 × 多曲线的高频实时刷新，无额外拷贝开销
    3、鼠标交互：悬停显示坐标值，矩形区域缩放，一键复位视图 
    4、样式自定义：支持设置曲线颜色、线型、粗细、填充等属性
    5、易于集成：简洁明了的接口设计，只需两个文件即可集成到任何 Qt 项目
    
  二、安装方法
    
    1、将 Myplot/myplot.h 和 Myplot/myplot.cpp 添加到你的项目源代码目录
    2、在项目设置中添加 Qt Charts 模块：
    3、.pro 文件中添加：QT += charts，或在 CMake 中添加：find_package(Qt6 COMPONENTS Charts REQUIRED)
    4、在需要使用的文件中包含头文件：#include "myplot.h"

三、快速开始

（1）基本使用示例

    // 创建并初始化图表
    MyPlot plot;
    plot.initChart(ui.widgetChart);      // 将图表添加到布局控件
    plot.enableRubberBand(true);         // 启用区域缩放
    plot.enableCoordinateDisplay(true);  // 启用坐标显示
    plot.setAxisRange(0, 10, -5, 5);     // 设置坐标轴范围
    
    // 添加曲线
    plot.addSeries("正弦", Qt::red);
    plot.addSeries("余弦", Qt::blue);
    
    // 更新数据
    QVector<QPointF> sineData, cosineData;
    // ...填充数据...
    plot.updateData("正弦", sineData);
    plot.updateData("余弦", cosineData);
    
    // 复位缩放
    plot.zoomReset();

（三）批量高效刷新示例

    // 预分配容器空间
    QVector<std::pair<std::string, QVector<QPointF>>> dataList;
    dataList.resize(2);
    dataList[0].first = "正弦";
    dataList[1].first = "余弦";
    
    // 通过引用直接填充数据，避免拷贝
    QVector<QPointF>& sineDataRef = dataList[0].second;
    QVector<QPointF>& cosineDataRef = dataList[1].second;
    
    sineDataRef.reserve(numPoints);
    cosineDataRef.reserve(numPoints);
    for (int i = 0; i <= numPoints; ++i) {
        double x = (2 * PI / numPoints) * i;
        sineDataRef.push_back(QPointF(x, 5 * sin(x + phase)));
        cosineDataRef.push_back(QPointF(x, 5 * cos(x + phase)));
    }
    
    // 批量更新所有曲线
    plot.batchUpdate(dataList);

四、主要接口说明

  （一）图表初始化
  
    •	initChart(QWidget* widget): 初始化图表并添加到控件
    •	setAxisRange(double xMin, double xMax, double yMin, double yMax): 设置坐标轴范围
  （二）曲线操作
  
    •	addSeries(const std::string& name, const QColor& color): 添加新曲线
    •	updateData(const std::string& name, const QVector<QPointF>& points): 更新曲线数据
    •	batchUpdate(const std::vector<std::pair<std::string, QVector<QPointF>>>& dataList): 批量更新多条曲线
    •	removeSeriesByName(const std::string& name): 删除指定曲线
    •	clearAllSeries(): 清除所有曲线
  （三）鼠标交互
  
    •	enableCoordinateDisplay(bool enable): 启用/禁用鼠标坐标显示
    •	enableRubberBand(bool enable): 启用/禁用区域缩放
    •	zoomReset(): 复位图表视图
  （四）性能说明
  
    •	支持 8000 点 × 多曲线的 60FPS 实时刷新
    •	采用引用填充 + 批量更新策略，最小化内存开销
    •	默认仅显示鼠标坐标和区域缩放功能，确保绘图性能最优
    
五、项目示例

    本仓库中的 test.cpp 和 test.h 包含了完整的使用示例，展示了如何在实际项目中应用 MyPlot。
六、兼容性

    •	主要针对 Qt 6.x 优化，同时兼容 Qt 5.12 及以上版本
    •	要求 C++14 及以上标准
七、许可

    本项目采用 MIT 许可证 - 详见 LICENSE 文件
八、贡献

    欢迎提交 Issue 和 Pull Request 来改进这个项目！

