#pragma once
#include "qpushbutton.h"
#include <qevent.h>
#include <qpainter.h>

/*�Զ��尴ť�������룬��������л���ͬ��ͼƬ���Ӷ�ʵ�ֺܺÿ��İ�ťЧ��*/
class UserDefineButton :
	public QPushButton
{
	Q_OBJECT
		Q_PROPERTY(int currentIndex READ getCurrentIndex WRITE setCurrentIndex)
public:
	/*���캯��������fileName,ͼƬ�ļ�·����xnum,���ͼƬ����ֳɼ��ݣ�ynum����ֳɼ��ݣ�bkGrnd������ͼƬ,�����������ť������*/
	UserDefineButton(QString fileName, QWidget *parent = 0,int xnum=1,int ynum=1,QString bkGrnd=NULL);
	/*���캯��������list���ܶ�СͼƬ���ļ�·����bkGrnd����ͼƬ·��*/
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

