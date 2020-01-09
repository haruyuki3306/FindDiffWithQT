#include "TimeCount.h"



TimeCount::TimeCount(QPixmap valePixName, QPixmap movePixName, QWidget *parent, int totalVale, int currentValue)
	:QWidget(parent),totalVale(totalVale),currentValue(currentValue)
{
	totalValePix = valePixName.copy(0,0,605,55);
	currentValuePix = valePixName.copy(0,55,605,55);
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}


TimeCount::~TimeCount()
{
}

QSize TimeCount::getSize()
{
	return sizeHint();
}

void TimeCount::paintEvent(QPaintEvent * event)
{
	QPainter p(this);
	p.drawPixmap(0,0,totalValePix);
}

QSize TimeCount::sizeHint() const
{
	return QSize(totalValePix.size());
}
