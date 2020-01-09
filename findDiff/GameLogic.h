#pragma once
#include "qwidget.h"
#include <qpainter.h>
#include <qlist.h>
#include <Qtime>
#include <qevent.h>
#include <qrect.h>
#include <qdebug.h>
/**
*游戏逻辑类
*接收两张图片，一张是原版，一张是修改版，接收一组数据，这组数据是修改版与原版不同的地方对应的坐标
*将界面分为左右两部分，左右两边都放原版图，根据数据坐标，去修改版取出不同的部分，贴到右边原版图对应位置
**/
class GameLogic :
	public QWidget
{
	Q_OBJECT
public:
	GameLogic(QString firstPicName,QString diffPicName,QVector<QRect> &list,QWidget *parent=0);//firsPicName,原版图路径,diffPicName,修改图路径,list不同点坐标
	GameLogic(QString picName,QVector<QRect> &list,QWidget *parent=0);//picName,大图（包含原版与修改版）路径,list不同点坐标
	GameLogic(QVector<QString> &list,QWidget *parent=0);//list里包含图片与不同点信息
	~GameLogic();
	void setDiffPointPix(QVector<QString> &list);
	QList<QPixmap> getDiffPointPix(void) const { return diffPointPix; };
	QRect picRect = QRect(0,0,640,480);

	QList<int> getRandom(int total);//total是要产生随机数的个数，返回值是所产生的随机数集合

private:
	QList<QPixmap> diffPointPix;//所有不同点的图片
	QList<QRect> diffPointPos;//所有不同点坐标

	QPixmap *mainPic;//原图

	QPixmap *canvans;//用于缓冲，将游戏中的原图和修改图画到这上面

	bool found[5];//标记5个不同点是否已找出，true为已找出，false未找出
protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void enterEvent(QEvent *event);
	virtual void leaveEvent(QEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual QSize sizeHint() const;
};

