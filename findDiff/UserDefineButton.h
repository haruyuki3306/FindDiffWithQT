#pragma once
#include "qpushbutton.h"
#include <qevent.h>
#include <qpainter.h>

/*自定义按钮，鼠标进入，鼠标点击会切换不同的图片，从而实现很好看的按钮效果*/
class UserDefineButton :
	public QPushButton
{
	Q_OBJECT
		Q_PROPERTY(int currentIndex READ getCurrentIndex WRITE setCurrentIndex)
public:
	/*构造函数，参数fileName,图片文件路径，xnum,这个图片横向分成几份，ynum纵向分成几份，bkGrnd，背景图片,用来给这个按钮做背景*/
	UserDefineButton(QString fileName, QWidget *parent = 0,int xnum=1,int ynum=1,QString bkGrnd=NULL);
	/*构造函数，参数list，很多小图片的文件路径，bkGrnd背景图片路径*/
	UserDefineButton(QVector<QString>&list, QWidget *parent = 0,QString bkGrnd =NULL);
	~UserDefineButton();

	QList<QPixmap> *getPixList(void) { return &pixList; }
	int getCurrentIndex(void) { return currentIndex; }
	void setCurrentIndex(int index) { currentIndex = index; update(); }
	QSize getSize();
protected:
	int currentIndex;
	QList<QPixmap> pixList;
private:
	void setPixList(QVector<QString> &list);
	QPixmap *background;
protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void enterEvent(QEvent *event);
	virtual void leaveEvent(QEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual QSize sizeHint() const;
};

