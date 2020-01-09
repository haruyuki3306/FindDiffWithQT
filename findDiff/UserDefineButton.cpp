#include "UserDefineButton.h"

UserDefineButton::UserDefineButton(QString fileName, QWidget *parent,int xnum, int ynum, QString bkGrnd)
	:QPushButton(parent)
{
	QPixmap pixmap(fileName);
	/*���ݴ�����ļ�·��fileName������pixmap��Ϊһ����ͼƬ��Ȼ����copy��������ͼƬ�г�һ����СͼƬ������pixList*/
	for (int cnt = 0; cnt < xnum; ++cnt)
	{
		for (int y = 0; y < ynum; ++y)
		{
			pixList.push_back(pixmap.copy(cnt*pixmap.width() / xnum, y*pixmap.height() / ynum, pixmap.width() / xnum, pixmap.height() / ynum));
		}
	}
	if (bkGrnd != NULL)
	{
		background = new QPixmap(bkGrnd);
	}
	else
	{
		background = NULL;
	}
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	currentIndex = 0;
}
UserDefineButton::UserDefineButton(QVector<QString>&list, QWidget *parent, QString bkGrnd)
	:QPushButton(parent)
{
	setPixList(list);
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	if (bkGrnd != NULL)
	{
		background = new QPixmap(bkGrnd);
	}
	else
	{
		background = NULL;
	}
	currentIndex = 0;
}

UserDefineButton::~UserDefineButton()
{
}

QSize UserDefineButton::getSize()
{
	return sizeHint();
}

void UserDefineButton::setPixList(QVector<QString>& list)
{
	/*list�����кܶ��СͼƬ��·������iterator����֮��ȡ��ÿһ��ͼƬ��·��Ȼ������һ��qpixmap,����pixList��*/
	if (list.size() <= 0)
	{
		return;
	}
	pixList.clear();
	for (QVector<QString>::iterator pos = list.begin(); pos != list.end(); ++pos)
	{
		pixList.push_back(QPixmap(*pos));
	}
}

void UserDefineButton::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	painter.drawPixmap(event->rect(), pixList[currentIndex]);
}

void UserDefineButton::enterEvent(QEvent * event)
{
	if (pixList.size() > 1)
	{
		currentIndex = 1;
	}
	else
	{
		currentIndex = 0;
	}
	update();
	QPushButton::enterEvent(event);
}

void UserDefineButton::leaveEvent(QEvent * event)
{
	currentIndex = 0;
	update();
	QPushButton::leaveEvent(event);
}

void UserDefineButton::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		if (pixList.size() > 2)
		{
			currentIndex = 2;
			update();
		}
	}
	QPushButton::mousePressEvent(event);
}

void UserDefineButton::mouseReleaseEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		if (pixList.size() > 1)
		{
			currentIndex = 1;
			update();
		}
	}
	QPushButton::mouseReleaseEvent(event);
}

QSize UserDefineButton::sizeHint() const
{
	return background!=NULL?QSize(background->width(),background->height()):QSize(pixList[0].width(),pixList[0].height());
}
