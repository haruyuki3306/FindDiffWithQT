#include "MainFrontView.h"



MainFrontView::MainFrontView(QWidget *parent)
	:QGraphicsView(parent)
{
	setRenderHint(QPainter::Antialiasing);//ʹ�ÿ���ݵķ�ʽ��Ⱦ
	setCacheMode(CacheBackground);//���û��汳�����������Լӿ���Ⱦ�ٶ�
	initLogoPanel();
	
}


MainFrontView::~MainFrontView()
{
}

void MainFrontView::initLogoPanel()
{
	/*���ó���*/
	scene = new QGraphicsScene;
	scene->setSceneRect(0, 0, 1280, 720);
	scene->setBackgroundBrush(QPixmap(":/MainView/mainwin_back"));
	setScene(scene);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//���ع�����
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scene_middle_point = new QPoint(scene->width() / 2, scene->height() / 2);

	/*��������һ���ɫ��͸������*/
	QWidget *mask = new QWidget;
	mask->setAutoFillBackground(true);
	mask->setPalette(QPalette(QColor(0, 0, 0, 50)));//qcolor���ĸ������ǲ�͸����
	mask->resize(1280, 720);
	background_mask = scene->addWidget(mask);
	background_mask->setZValue(1);
	/*����LOGO*/
	QWidget *game_logo = new QWidget;
	game_logo->resize(400, 250);
	this->setAutoFillBackground(true);
	QPalette palette = this->palette();
	palette.setBrush(QPalette::Window, QBrush(QPixmap(":/MainView/logo").scaled(game_logo->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));// brushʹ��ƽ�������ŷ�ʽ,ʹbrush�븸����һ��������ͼƬ��С������ν��
	game_logo->setPalette(palette);
	logo_widget = scene->addWidget(game_logo);
	logo_widget->setPos(scene_middle_point->x() - logo_widget->size().width() / 2, scene_middle_point->y() - scene->height() / 3);//����logo����Ļ��λ�ã������Ǻ����е㣬����3��1
	logo_widget->setZValue(2);//����z���2��.����Խ��Խ��ǰ

							  /*logo�����õ��İ�ť*/
	QWidget *logo_panel_btn = new QWidget;
	logo_panel_btn->setAutoFillBackground(true);
	logo_panel_btn->setPalette(QPalette(QColor(0, 0, 0, 0)));
	UserDefineButton *startBtn = new UserDefineButton(":/MainView/start_game", logo_panel_btn, 1, 3);
	//UserDefineButton *pauseBtn = new UserDefineButton(":/MainView/pause",logo_panel_btn,1,3);
	//pauseBtn->move(0,startBtn->getSize().height()+10);//����+10��Ϊ����һ���϶
	UserDefineButton *exitBtn = new UserDefineButton(":/MainView/exit", logo_panel_btn, 1, 3);
	exitBtn->move(0, startBtn->getSize().height() + 10);//����+10��Ϊ����һ���϶
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
	{//���ȡ��5��ͼ
		qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));//�����������0��ʼ
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
	QVector<QList<QString>> allPixPath;//ÿһ�����Ҳ�ͬͼ������Ϣ���ŵ�����
	QFile file(iniFilePath);
	qDebug() << "file.."<< iniFilePath;
	if (!file.open(QIODevice::ReadOnly|QIODevice::Text))//�ļ���ʧ����ֱ���˳��˺���
	{
		qDebug() << "Error:file open failure";
		return allPixPath;
	}
	QDomDocument doc;
	if (!doc.setContent(&file))//����dom���ɹ���ֱ���˳��˺���
	{
		qDebug() << "Error:Dom create failure";
		return allPixPath;
	}
	qDebug() << "doc sucess";
	QDomElement root = doc.documentElement();
	if ("diffpic"!=root.tagName())
	{
		return allPixPath;//��ζ����ĵ�һ���ڵ㲻��diffpic��ô���xml�ļ����ܾͲ�������Ҫ���ļ���Ҫ��ʾ���������ݲ�������ֱ���˳��˺���
	}
	else
	{
		QDomNode node = root.firstChild();//���root�µ�һ���ڵ㣬ע�����ֽڵ���Ԫ��
		while (!node.isNull())//�ڵ�ǿվ�һֱѭ��
		{
			QList<QString> one_pic;
			if ("pic"==node.toElement().tagName())
			{
				QString org_pic_path = node.toElement().attribute("o_path");
				QString diff_pic_path = node.toElement().attribute("d_path");
				one_pic.push_back(org_pic_path);
				one_pic.push_back(diff_pic_path);
				QDomNode subNode = node.firstChild();//���node�µ�һ���ڵ�
				while (!subNode.isNull())
				{//��Ϊpic�ڵ��µĽڵ�Ԫ��ȫ����ͬ��������diffrect�����Բ���tagName�ж���
					QString diff_point = subNode.toElement().text();//���diffrectԪ�ص��ı��ڵ�����
					one_pic.push_back(diff_point);//��Ϊһ����ͬ��ӵ�one_pic
					subNode = subNode.nextSibling();//��һ��ͬ�ȼ��Ľڵ�
				}
			}
			else
			{
				return allPixPath;
			}
			allPixPath.push_back(one_pic);//��һ��ͼƬ��Ϣone_pic�ŵ�ͼƬ��Ϣ��allPixPath
			node = node.nextSibling();//��һ��ͬ�ȼ��Ľڵ�
		}
		file.close();
		return allPixPath;
	}
	return allPixPath;
}
