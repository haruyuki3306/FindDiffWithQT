#pragma once
#include <qgraphicsview.h>
#include <qgraphicsscene.h>
#include <qgraphicsproxywidget.h>
#include <qpainter.h>
#include "UserDefineButton.h"
#include <qlayout.h>
#include<qdebug.h>
#include <GameLogic.h>
#include <QtXml\QDomDocument>
#include <QtXml\QDomElement>
#include <QtXml\QDomNode>
#include "TimeCount.h"
#define iniFilePath "./Resources/resources.xml"

class MainFrontView :
	public QGraphicsView
{
	Q_OBJECT
public:
	MainFrontView(QWidget *parent);
	~MainFrontView();
	QPoint *scene_middle_point;//游戏场景中点
	QVector<QList<QString>> readSources();
	QVector<QList<QString>> five_pic;//存放游戏进行中的5张图，这里要注意内存释放问题，第一次加5个进去，第二次再加5个就变10个了
	public slots:
	void initGame();
	void initLogoPanel();
private:
	QGraphicsWidget *background_mask;
	QGraphicsWidget *logo_widget;

	QGraphicsWidget *logo_btn_widget;
	QGraphicsWidget *logic_widget;
	QGraphicsScene *scene;
};

