#include "MainFrontView.h"



MainFrontView::MainFrontView(QWidget *parent)
	:QGraphicsView(parent)
{
	setRenderHint(QPainter::Antialiasing);//使用抗锯齿的方式渲染
	setCacheMode(CacheBackground);//设置缓存背景，这样可以加快渲染速度
	initLogoPanel();
	
}


MainFrontView::~MainFrontView()
{
}

void MainFrontView::initLogoPanel()
{
	/*设置场景*/
	scene = new QGraphicsScene;
	scene->setSceneRect(0, 0, 1280, 720);
	scene->setBackgroundBrush(QPixmap(":/MainView/mainwin_back"));
	setScene(scene);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏滚动条
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scene_middle_point = new QPoint(scene->width() / 2, scene->height() / 2);

	/*给背景加一层黑色半透明遮罩*/
	QWidget *mask = new QWidget;
	mask->setAutoFillBackground(true);
	mask->setPalette(QPalette(QColor(0, 0, 0, 50)));//qcolor第四个参数是不透明度
	mask->resize(1280, 720);
	background_mask = scene->addWidget(mask);
	background_mask->setZValue(1);
	/*设置LOGO*/
	QWidget *game_logo = new QWidget;
	game_logo->resize(400, 250);
	this->setAutoFillBackground(true);
	QPalette palette = this->palette();
	palette.setBrush(QPalette::Window, QBrush(QPixmap(":/MainView/logo").scaled(game_logo->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));// brush使用平滑的缩放方式,使brush与父容器一样大，这样图片大小就无所谓了
	game_logo->setPalette(palette);
	logo_widget = scene->addWidget(game_logo);
	logo_widget->setPos(scene_middle_point->x() - logo_widget->size().width() / 2, scene_middle_point->y() - scene->height() / 3);//设置logo在屏幕的位置，这里是横轴中点，纵轴3分1
	logo_widget->setZValue(2);//放在z轴第2层.层数越高越靠前

							  /*logo界面用到的按钮*/
	QWidget *logo_panel_btn = new QWidget;
	logo_panel_btn->setAutoFillBackground(true);
	logo_panel_btn->setPalette(QPalette(QColor(0, 0, 0, 0)));
	UserDefineButton *startBtn = new UserDefineButton(":/MainView/start_game", logo_panel_btn, 1, 3);
	//UserDefineButton *pauseBtn = new UserDefineButton(":/MainView/pause",logo_panel_btn,1,3);
	//pauseBtn->move(0,startBtn->getSize().height()+10);//这里+10是为了留一点间隙
	UserDefineButton *exitBtn = new UserDefineButton(":/MainView/exit", logo_panel_btn, 1, 3);
	exitBtn->move(0, startBtn->getSize().height() + 10);//这里+10是为了留一点间隙
	connect(exitBtn, SIGNAL(clicked()), this->parent(), SLOT(close()));
	connect(startBtn, SIGNAL(clicked()), this, SLOT(initGame()));

	logo_btn_widget = scene->addWidget(logo_panel_btn);
	logo_btn_widget->setPos(scene_middle_point->x() - logo_panel_btn->size().width() / 2, scene_middle_point->y());
	logo_btn_widget->setZValue(2);
	logo_btn_widget->show();
}

void MainFrontView::initGame()
{
	QVector<QList<QString>> temp = readSources();
	if (temp.size()==0)return;
	for (int i = 0; i < 5; i++)
	{//随机取出5张图
		qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));//设置随机数从0开始
		five_pic.push_back(temp[qrand()%temp.size()]);
	}
	QString o_pic = five_pic[0][0];
	QString d_pic = five_pic[0][1];
	QVector<QRect> poins;
	for (int i = 2; i < five_pic[0].size(); i++)
	{
		QList<QString> diffPoint = five_pic.at(0).at(i).split(","); 
		qDebug() << "five_pic.....";
		poins.push_back(QRect(diffPoint[0].toInt(), diffPoint[1].toInt(), diffPoint[2].toInt(),diffPoint[3].toInt()));
	}
	QWidget *game_logic_widget = new QWidget;
	GameLogic *gameLogic = new GameLogic(o_pic,d_pic,poins,game_logic_widget);
	TimeCount *timeCount = new TimeCount(QPixmap(":/MainView/times"),QPixmap(":/MainView/booms"), game_logic_widget);
	timeCount->move(scene_middle_point->x()-(timeCount->getSize().width()/2),0);
	gameLogic->move(0,80);
	logic_widget = scene->addWidget(game_logic_widget);
	logic_widget->setPos(10,10);
	logic_widget->setZValue(2);
	logo_widget->hide();
	logo_btn_widget->hide();
	logic_widget->show();

}

QVector<QList<QString>> MainFrontView::readSources()
{
	QVector<QList<QString>> allPixPath;//每一个“找不同图”的信息都放到这里
	QFile file(iniFilePath);
	qDebug() << "file.."<< iniFilePath;
	if (!file.open(QIODevice::ReadOnly|QIODevice::Text))//文件打开失败则直接退出此函数
	{
		qDebug() << "Error:file open failure";
		return allPixPath;
	}
	QDomDocument doc;
	if (!doc.setContent(&file))//创建dom不成功则直接退出此函数
	{
		qDebug() << "Error:Dom create failure";
		return allPixPath;
	}
	qDebug() << "doc sucess";
	QDomElement root = doc.documentElement();
	if ("diffpic"!=root.tagName())
	{
		return allPixPath;//如何读到的第一个节点不是diffpic那么这个xml文件可能就不是我们要的文件，要提示错误，这里暂不作处理，直接退出此函数
	}
	else
	{
		QDomNode node = root.firstChild();//获得root下第一个节点，注意区分节点与元素
		while (!node.isNull())//节点非空就一直循环
		{
			QList<QString> one_pic;
			if ("pic"==node.toElement().tagName())
			{
				QString org_pic_path = node.toElement().attribute("o_path");
				QString diff_pic_path = node.toElement().attribute("d_path");
				one_pic.push_back(org_pic_path);
				one_pic.push_back(diff_pic_path);
				QDomNode subNode = node.firstChild();//获得node下第一个节点
				while (!subNode.isNull())
				{//因为pic节点下的节点元素全部是同样的名字diffrect，所以不作tagName判断了
					QString diff_point = subNode.toElement().text();//获得diffrect元素的文本节点内容
					one_pic.push_back(diff_point);//作为一个不同点加到one_pic
					subNode = subNode.nextSibling();//下一个同等级的节点
				}
			}
			else
			{
				return allPixPath;
			}
			allPixPath.push_back(one_pic);//将一个图片信息one_pic放到图片信息集allPixPath
			node = node.nextSibling();//下一个同等级的节点
		}
		file.close();
		return allPixPath;
	}
	return allPixPath;
}
