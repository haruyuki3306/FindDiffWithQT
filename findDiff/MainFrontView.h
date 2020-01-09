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
	QPoint *scene_middle_point;//��Ϸ�����е�
	QVector<QList<QString>> readSources();
	QVector<QList<QString>> five_pic;//�����Ϸ�����е�5��ͼ������Ҫע���ڴ��ͷ����⣬��һ�μ�5����ȥ���ڶ����ټ�5���ͱ�10����
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

