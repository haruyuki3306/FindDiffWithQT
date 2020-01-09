#pragma once
#include "qwidget.h"
#include <qpainter.h>
#include <qlist.h>
#include <Qtime>
#include <qevent.h>
#include <qrect.h>
#include <qdebug.h>
/**
*��Ϸ�߼���
*��������ͼƬ��һ����ԭ�棬һ�����޸İ棬����һ�����ݣ������������޸İ���ԭ�治ͬ�ĵط���Ӧ������
*�������Ϊ���������֣��������߶���ԭ��ͼ�������������꣬ȥ�޸İ�ȡ����ͬ�Ĳ��֣������ұ�ԭ��ͼ��Ӧλ��
**/
class GameLogic :
	public QWidget
{
	Q_OBJECT
public:
	GameLogic(QString firstPicName,QString diffPicName,QVector<QRect> &list,QWidget *parent=0);//firsPicName,ԭ��ͼ·��,diffPicName,�޸�ͼ·��,list��ͬ������
	GameLogic(QString picName,QVector<QRect> &list,QWidget *parent=0);//picName,��ͼ������ԭ�����޸İ棩·��,list��ͬ������
	GameLogic(QVector<QString> &list,QWidget *parent=0);//list�����ͼƬ�벻ͬ����Ϣ
	~GameLogic();
	void setDiffPointPix(QVector<QString> &list);
	QList<QPixmap> getDiffPointPix(void) const { return diffPointPix; };
	QRect picRect = QRect(0,0,640,480);

	QList<int> getRandom(int total);//total��Ҫ����������ĸ���������ֵ�������������������

private:
	QList<QPixmap> diffPointPix;//���в�ͬ���ͼƬ
	QList<QRect> diffPointPos;//���в�ͬ������

	QPixmap *mainPic;//ԭͼ

	QPixmap *canvans;//���ڻ��壬����Ϸ�е�ԭͼ���޸�ͼ����������

	bool found[5];//���5����ͬ���Ƿ����ҳ���trueΪ���ҳ���falseδ�ҳ�
protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void enterEvent(QEvent *event);
	virtual void leaveEvent(QEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual QSize sizeHint() const;
};

