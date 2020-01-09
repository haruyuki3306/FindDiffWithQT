#pragma once
#include "qwidget.h"
#include <qpainter.h>

/*时间进度条，用来显示倒计时进度，同时也是在这个类里面为游戏中每一幅图片计时*/
class TimeCount :
	public QWidget
{
	Q_OBJECT
public:
	TimeCount(QPixmap valePixName, QPixmap movePixName, QWidget *parent=NULL, int totalVale=100,int currentValue=0 );//valePixName,进度图片，movePixName,进度走动图片，totalVale最大值
	~TimeCount();
	QPixmap totalValePix;
	QPixmap currentValuePix;
	int totalVale;
	int currentValue;
	QSize getSize();

protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual QSize sizeHint() const;
};

