#pragma once
#include "qwidget.h"
#include <qpainter.h>

/*ʱ���������������ʾ����ʱ���ȣ�ͬʱҲ�������������Ϊ��Ϸ��ÿһ��ͼƬ��ʱ*/
class TimeCount :
	public QWidget
{
	Q_OBJECT
public:
	TimeCount(QPixmap valePixName, QPixmap movePixName, QWidget *parent=NULL, int totalVale=100,int currentValue=0 );//valePixName,����ͼƬ��movePixName,�����߶�ͼƬ��totalVale���ֵ
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

