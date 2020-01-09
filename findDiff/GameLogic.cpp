#include "GameLogic.h"



GameLogic::GameLogic(QString firstPicName, QString diffPicName, QVector<QRect> &list, QWidget *parent)
	:QWidget(parent)
{
	qDebug() << "firstPic:"<<firstPicName<<"diffPicName:"<<diffPicName;
	mainPic = new QPixmap(firstPicName);//ԭ��ͼ
	QPixmap diffPic(diffPicName);
	/*����ó�5����ͬ��*/
	QList<int> randoms = getRandom(5);
	for (int i = 0; i < 5; i++)
	{
		//qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));//���д�������ö�ʱ���ڲ����������һ��
		//QTime time = QTime::currentTime();
		//qsrand(time.msec()+time.second()*1000);//�������������������ظ�
		int temp = randoms[i];//������0��list.size��Χ�������
		qDebug() << "rand:" << temp;
		diffPointPix.push_back(diffPic.copy(list[temp]));
		diffPointPos.push_back(list[temp]);
		found[i] = false;
	}
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	canvans = new QPixmap;
}

GameLogic::GameLogic(QString picName, QVector<QRect> &list, QWidget *parent)
	:QWidget(parent)
{

}

GameLogic::~GameLogic()
{
}

QList<int> GameLogic::getRandom(int total)
{	
	/*
	public static int[] GetRandomSequence2(int total)
        {
 
            int[] sequence = new int[total];
            int[] output = new int[total];
 
            for (int i = 0; i < total; i++)
            {
                sequence[i] = i;
            }
 
            Random random = new Random();
 
            int end = total - 1;
 
            for (int i = 0; i < total; i++)
            {
                int num = random.Next(0, end + 1);
                output[i] = sequence[num];
                sequence[num] = sequence[end];
                end--;
            }
 
            return output;
        }
	*/
	int *sequence = new int[total];
	int *output = new int[total];
	QList<int> list;
	for (int i = 0; i < total; i++)
	{
		sequence[i] = i;
	}
	int end = total - 1;
	for (int i = 0; i < total; i++)
	{
		int num = qrand()%(end+1);
		output[i] = sequence[num];
		sequence[num] = sequence[end];
		end--;
	}
	for (int i = 0; i < total; i++)
	{
		list.push_back(output[i]);
	}
	delete[] sequence;
	delete[] output;
	return list;
}

void GameLogic::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	//QPainter painter2(canvans);
	painter.drawPixmap(picRect,*mainPic);
	painter.drawPixmap(QRect(picRect.width(),picRect.topLeft().y(),picRect.width(),picRect.height()),*mainPic);
	//painter.drawPixmap(diffPointPos[0], diffPointPix[0]);
	for (int i = 0; i < diffPointPix.size(); i++)
	{
		painter.drawPixmap(diffPointPos[i],diffPointPix[i]);//����ͬ����ʾ����
	}
	//painter.drawPixmap(0,0,*canvans);
	for (int i = 0; i < 5; i++)
	{
		if (found[i])//��ͬ���ѱ��ҵ�
		{
			painter.setPen(QPen(Qt::red));
			painter.drawRect(diffPointPos[i]);
		}
	}
}

void GameLogic::enterEvent(QEvent * event)
{
}

void GameLogic::leaveEvent(QEvent * event)
{
}

void GameLogic::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)//�ж��Ƿ�������
	{
		for (int i = 0; i < 5; i++)
		{
			if(diffPointPos[i].contains(event->pos(), true))//�ж�������ĵط��Ƿ��ڲ�ͬ����
			{
				found[i] = true;//��ͬ���ѱ��ҵ�
				update();
			}
		}
	}
}

void GameLogic::mouseReleaseEvent(QMouseEvent * event)
{
}

QSize GameLogic::sizeHint() const
{
	return QSize(mainPic->size().width()*2,mainPic->size().height());
}
