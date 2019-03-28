#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt_opencv.h"
#pragma once
#include <QtWidgets/QMainWindow>
#include <QtGui>
#include <QtWidgets>
#include <QMainWindow>
//#include "ui_mainWindow.h"



class Qt_opencv : public QMainWindow
{
	Q_OBJECT

public:
	Qt_opencv(QWidget *parent = Q_NULLPTR);
	~Qt_opencv();
	

private:
	Ui::Qt_opencvClass ui;
	QDockWidget *dock_Image;                    // 图像窗口
	QString currentPath;                        // 当前图像的路径
	QLabel *imgLabel;                           // 图像显示框
	QScrollArea* scrollArea;
	void InitImage();                           // 初始化图像
	void Menu_File();                           // 文件菜单
	
signals:
	void clicked();

	
private slots:             // 槽函数
	void File_new();        // 新建
	void File_open();       // 打开
	void File_save();       // 保存
	void File_saveas();     // 另存为
							// 关闭不需要，直接使用close()
	void dealimage();        //自适应窗口
	
};
