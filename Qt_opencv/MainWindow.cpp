#include "MainWindow.h"
#include <QMainWindow>
#include <QtGui>
#include <QtWidgets>
#include <string>
#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
#pragma execution_character_set("utf-8")    // 解决汉字乱码问题
Qt_opencv::Qt_opencv(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle("浮游植物细胞自动提取自编软件 by 刘中天");

	QPushButton *button_auto = new QPushButton(tr("细胞图像提取"));    // 创建按钮
	// 软件图标
	setWindowIcon(QIcon("C:/Users/liuzhongtian/Desktop/opencvtest1/qt/图标库/魔术棒.png"));

	connect(button_auto, SIGNAL(clicked()), this, SLOT(dealimage()));

	ui.setupUi(this);
	Menu_File();        // 文件菜单
	InitImage();        // 初始化图像QLabel

	ui.mainToolBar->addWidget(button_auto);
}
Qt_opencv::~Qt_opencv()
{

}



void Qt_opencv::Menu_File()
{
	// 菜单栏
	QMenu *file = menuBar()->addMenu(tr("文件"));

	// 菜单动作
	QAction *Act_file_new = new QAction(QIcon("../../图标库/新建.png"), tr("新建"), this);
	Act_file_new->setShortcuts(QKeySequence::New);  // 快捷键 Ctrl+N
	connect(Act_file_new, SIGNAL(triggered()), this, SLOT(File_new()));

	QAction *Act_file_open = new QAction(QIcon("../../图标库/打开.png"), tr("打开"), this);
	Act_file_open->setShortcuts(QKeySequence::Open);// 快捷键 Ctrl+O
	connect(Act_file_open, SIGNAL(triggered()), this, SLOT(File_open()));

	QAction *Act_file_save = new QAction(QIcon(":/Qt_opencv/Resources/icon_保存.png"), tr("保存"), this);
	Act_file_save->setShortcuts(QKeySequence::Save);// 快捷键 Ctrl+S
	connect(Act_file_save, SIGNAL(triggered()), this, SLOT(File_save()));

	QAction *Act_file_saveas = new QAction(QIcon("../../图标库/另存为.png"), tr("另存为"), this);
	Act_file_saveas->setShortcuts(QKeySequence::SaveAs);// 快捷键 
	connect(Act_file_saveas, SIGNAL(triggered()), this, SLOT(File_saveas()));

	QAction *Act_file_close = new QAction(QIcon("../../图标库/关闭.png"), tr("关闭"), this);
	Act_file_close->setShortcuts(QKeySequence::Close);// 快捷键 Ctrl+F4
	connect(Act_file_close, SIGNAL(triggered()), this, SLOT(close()));

	// 将动作添加到菜单上
	file->addAction(Act_file_new);
	file->addAction(Act_file_open);
	file->addAction(Act_file_save);
	file->addAction(Act_file_saveas);
	file->addSeparator();                       //添加分割线
	file->addAction(Act_file_close);

	// 工具栏
	ui.mainToolBar->addAction(Act_file_new);
	ui.mainToolBar->addAction(Act_file_open);
	ui.mainToolBar->addAction(Act_file_save);

	// 任务栏
	Act_file_new->setStatusTip(tr("新建图像"));
	Act_file_open->setStatusTip(tr("打开图像"));
	Act_file_save->setStatusTip(tr("保存图像"));
	Act_file_saveas->setStatusTip(tr("图像另存为"));
	Act_file_close->setStatusTip(tr("关闭软件"));
	
}

void Qt_opencv::InitImage()        // 初始化图像
{
	// 初始化QDockWidget.在以后会讲到，是可移动隐藏的小窗口，
	// 可以实现PS、VS停靠窗口的效果，目前只需了解
	dock_Image = new QDockWidget(tr("图像"), this);          //   图像
	setCentralWidget(dock_Image);

	// 初始化QLabel
	imgLabel = new QLabel(dock_Image);
	imgLabel->setScaledContents(true);  // 设置QLabel自动适应图像大小

										// 初始图像
	QImage image = QImage(500, 500, QImage::Format_RGB32);  // 新建图像
	image.fill(qRgb(255, 255, 255));                        // 全白
	imgLabel->setPixmap(QPixmap::fromImage(image));         // 显示图像
	imgLabel->resize(image.width(), image.height());        // 图像与imgLabel同大小

															// 增加滚动条,如果图像比imgLabel大，就会出现滚动条
	QScrollArea* scrollArea = new QScrollArea(this);
	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setAlignment(Qt::AlignCenter);
	scrollArea->setWidget(imgLabel);
	dock_Image->setWidget(scrollArea);
}

void Qt_opencv::File_new()// 新建
{
	QImage image = QImage(500, 500, QImage::Format_RGB32);  // 创建长宽各500的RGB图像
	image.fill(qRgb(255, 255, 255));                        // 白色图像
	imgLabel->setPixmap(QPixmap::fromImage(image));         // 转载图像
	imgLabel->resize(image.width(), image.height());        // imgLabel与图像同大小
	currentPath = "";                                       // 当前路径为空
}

void Qt_opencv::File_open()        // 打开
{
	QString path = QFileDialog::getOpenFileName(this, tr("选择图像"), ".", tr("Images(*.jpg *.png *.bmp)"));                            // 文件选择框
	if (!path.isEmpty())                                    // 检测当前路径是否正确
	{
		QImage* img = new QImage();
		if (!(img->load(path)))
		{
			QMessageBox::information(this, tr("错误"), tr("打开图像失败！"));
			delete img;
			return;
		}
		imgLabel->setPixmap(QPixmap::fromImage(*img));
		imgLabel->resize(img->width(), img->height());
		currentPath = path;


	}

}

void Qt_opencv::File_save()        // 保存
{
	if (currentPath.isEmpty())      // 判断是新建的图像还是打开的图像
	{
		QString path = QFileDialog::getSaveFileName(this, tr("保存图像"), ".", tr("Images(*.jpg *.png *.bmp)"));
		{
			if (!path.isEmpty())
				currentPath = path;
		}
	}
	QImage img = imgLabel->pixmap()->toImage();     // 读取图像
	img.save(currentPath);                          // 保存图像
}

void Qt_opencv::File_saveas()      // 另存为
{
	QString path = QFileDialog::getSaveFileName(this, tr("图像另存为"), ".", tr("Images(*.jpg *.png *.bmp)"));
	if (!path.isEmpty())
	{
		QImage img = imgLabel->pixmap()->toImage();
		img.save(path);
		currentPath = path;
	}
}



// cv::Mat转换成QImage
QImage cvMat2QImage(const Mat& mat)
{
	if (mat.type() == CV_8UC1)                          // 单通道
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		image.setColorCount(256);                       // 灰度级数256
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		uchar *pSrc = mat.data;                         // 复制mat数据
		for (int row = 0; row < mat.rows; row++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
	else if (mat.type() == CV_8UC3)                     // 3通道
	{
		const uchar *pSrc = (const uchar*)mat.data;     // 复制像素
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);    // R, G, B 对应 0,1,2
		return image.rgbSwapped();                      // rgbSwapped是为了显示效果色彩好一些。
	}
	else if (mat.type() == CV_8UC4)                     // 4通道
	{
		const uchar *pSrc = (const uchar*)mat.data;     // 复制像素
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);        // B,G,R,A 对应 0,1,2,3
		return image.copy();
	}
	else
	{
		return QImage();
	}
}


Mat QImage2cvMat(QImage image)//QImage转换成Mat
{
	Mat mat;
	switch (image.format())
	{
	case QImage::Format_ARGB32:
	case QImage::Format_RGB32:
	case QImage::Format_ARGB32_Premultiplied:
		mat = Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
		break;
	case QImage::Format_RGB888:
		mat = Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
		cv::cvtColor(mat, mat, CV_BGR2RGB);
		break;
	case QImage::Format_Indexed8:
		mat = Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
		break;
	}
	return mat;
}

void Qt_opencv::dealimage() // 处理图像
{
	QImage img = imgLabel->pixmap()->toImage();     // 读取图像
	Mat src = QImage2cvMat(img);

	Mat gray_src;//转灰度
	cvtColor(src, gray_src, CV_BGR2GRAY);

	Mat blur_src;//滤波
	bilateralFilter(gray_src, blur_src, 7, 150, 50);
	

	//边缘发现
	Mat x;
	Mat y;
	Mat fin;
	
	Sobel(blur_src, x, CV_16S, 1, 0, 3);
	Sobel(blur_src, y, CV_16S, 0, 1, 3);
	convertScaleAbs(x, x);
	convertScaleAbs(y, y);
	

	int h = x.rows;
	int w = x.cols;
	fin = Mat(x.size(), x.type());

	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {

			int xg = x.at<uchar>(row, col);
			int yg = y.at<uchar>(row, col);
			int xyg = xg + yg;
			fin.at<uchar>(row, col) = saturate_cast<uchar>(xyg);

		}
	}
	threshold(fin, fin, /*230*/10/*（复杂细胞外形）most_num*/, 255, THRESH_BINARY);
	


	//膨胀（看情况使用，一般用于细胞边缘与背景极为接近）
	Mat str0;
	str0 = getStructuringElement(MORPH_RECT, Size(4, 4), Point(-1, -1));
	dilate(fin, fin, str0, Point(-1, -1), 1);//膨胀
	erode(fin, fin, str0, Point(-1, -1), 1);//腐蚀
											

	//轮廓+填充
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(fin, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());//轮廓发现
	Mat ddst = Mat::zeros(src.size(), gray_src.type());
	for (size_t i = 0; i < contours.size(); i++) {
		if (contours[i].size() > 50) drawContours(ddst, contours, i, Scalar(255, 255, 255), -1);
	}
	

	fin = ddst;

	//填充孔洞,如果不执行这一步也可以，但是碰到较小细胞时容易被当作小物体去除，遇到复杂外形细胞时易于做膨胀操作
	Mat dstBw;
	Size m_Size = fin.size();
	Mat Temp = Mat::zeros(m_Size.height + 2, m_Size.width + 2, fin.type());//延展图像
	fin.copyTo(Temp(Range(1, m_Size.height + 1), Range(1, m_Size.width + 1)));
	cv::floodFill(Temp, Point(0, 0), Scalar(255));
	Mat cutImg;//裁剪延展的图像
	Temp(Range(1, m_Size.height + 1), Range(1, m_Size.width + 1)).copyTo(cutImg);
	dstBw = fin | (~cutImg);


	//膨胀（看情况使用，一般用于细胞边缘与背景极为接近）
	Mat str;
	str = getStructuringElement(MORPH_RECT, Size(6, 6), Point(-1, -1));
	dilate(dstBw, dstBw, str, Point(-1, -1), 1);
	


	//轮廓发现、绘制、截取、保存
	vector<vector<Point>> contours1;
	vector<Vec4i> hierarchy1;
	findContours(dstBw, contours1, hierarchy1, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());//发现轮廓

	Mat bg;
	src.copyTo(bg);
	for (size_t i = 0; i < contours1.size(); i++) {
		if (contours1[i].size() > 20) {
			//绘制轮廓矩形
			Rect rect = boundingRect(contours1[i]);
			rect = rect + Point(-3, -3);	//平移
			rect = rect + Size(6, 6);	    //缩放，左上顶点不变
			rectangle(bg, rect, Scalar(0, 255, 230), 2, LINE_AA, 0);

			//割取矩形区域保存（改进）
			Mat src_ex;
			char file_name[] = "C:\\Users\\liuzhongtian\\Desktop\\2\\test0000.jpg";
			//sprintf_s(file_name, "C:\\Users\\liuzhongtian\\Desktop\\2\\test%d.jpg", int(i + 1));
			copyMakeBorder(src, src_ex, 8, 8, 8, 8, BORDER_CONSTANT, Scalar(255, 255, 255));	//扩大原图像并填充边缘
		  //imwrite(file_name, src_ex(rect + Point(8, 8)));
		}
	}

	//imshow("提取结果", bg);
	//imwrite("C:\\Users\\liuzhongtian\\Desktop\\2\\test0.jpg", bg);
	QImage imagesrc = cvMat2QImage(bg);
	imgLabel->setPixmap(QPixmap::fromImage(imagesrc));
	
}