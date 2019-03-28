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
	QDockWidget *dock_Image;                    // ͼ�񴰿�
	QString currentPath;                        // ��ǰͼ���·��
	QLabel *imgLabel;                           // ͼ����ʾ��
	QScrollArea* scrollArea;
	void InitImage();                           // ��ʼ��ͼ��
	void Menu_File();                           // �ļ��˵�
	
signals:
	void clicked();

	
private slots:             // �ۺ���
	void File_new();        // �½�
	void File_open();       // ��
	void File_save();       // ����
	void File_saveas();     // ���Ϊ
							// �رղ���Ҫ��ֱ��ʹ��close()
	void dealimage();        //����Ӧ����
	
};
