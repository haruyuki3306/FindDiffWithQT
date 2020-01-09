#include "MainView.h"
#include <qlabel.h>
#include "MainFrontView.h"
#include <QHBoxLayout>

MainView::MainView(QWidget *parent)
	: QWidget(parent)
{
	//ui.setupUi(this);
	setWindowTitle(tr("Spot The Differences"));
	resize(1280,720);
	//showFullScreen();//È«ÆÁ
	QLabel *gameLogo = new QLabel(tr("Spot The Differences"),this);
	MainFrontView *f = new MainFrontView(this);
	QHBoxLayout *mainLayout = new QHBoxLayout(this);
	//setWindowFlags(Qt::Window | Qt::FramelessWindowHint);//È¥µô´°¿Ú±ß¿ò
	mainLayout->setMargin(0);
	mainLayout->addWidget(f);
	
}
