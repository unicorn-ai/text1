#include "mainwindow.h"
#include <QDebug>
#include <QGuiApplication>
#include "commonhelper.h"
#include "musicwidget/musicwidget.h"
#include "calculatorwidget/calculatorwidget.h"
#include "videiowidget/videowidget.h"
#include "mapwidget/mapwidget.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QList <QScreen *> list_screen =  QGuiApplication::screens();
    ui_init();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setBackground(const QPixmap &pixmap)
{
    QPalette  palette = this->palette();
    palette.setBrush(backgroundRole(), pixmap.scaled(screenWidth, screenHeigh, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    setPalette(palette);
    setAutoFillBackground(true);
}

void MainWindow::led_control()
{
    /* 开发板的LED控制接口 */
    file.setFileName("/sys/class/leds/firefly:blue:power/brightness");

    if (!file.exists())
        /* 设置按钮的初始化文本 */
        pushButton->setText("未获取到LED设备！");

    /* 获取LED的状态 */
    getLedState();

    /* 信号槽连接 */
    connect(pushButton, SIGNAL(clicked()),
            this, SLOT(pushButtonClicked()));
}

void MainWindow::setLedState()
{
    /* 在设置LED状态时先读取 */
    bool state = getLedState();

    /* 如果文件不存在，则返回 */
    if (!file.exists())
        return;

    if(!file.open(QIODevice::ReadWrite))
        qDebug()<<file.errorString();

    QByteArray buf[2] = {"0", "1"};

    /* 写0或1 */
    if (state)
        file.write(buf[0]);
    else
        file.write(buf[1]);

    /* 关闭文件 */
    file.close();

    /*重新获取LED的状态 */
    getLedState();
}

bool MainWindow::getLedState()
{
    /* 如果文件不存在，则返回 */
    if (!file.exists())
        return false;

    if(!file.open(QIODevice::ReadWrite))
        qDebug()<<file.errorString();

    QTextStream in(&file);

    /* 读取文件所有数据 */
    QString buf = in.readLine();

    /* 打印出读出的值 */
    qDebug()<<"buf: "<<buf<<endl;
    file.close();
    if (buf == "1") {
        pushButton->setText("LED点亮");
        return true;
    } else {
        pushButton->setText("LED熄灭");
        return false;
    }
}

void MainWindow::pushButtonClicked()
{
    /* 设置LED的状态 */
    setLedState();
}
void MainWindow::pb1()
{
    pushButton->setText("遥控");
}
void MainWindow::pb2()
{
pushButton->setText("LED熄灭2");
}
void MainWindow::pb3()
{
pushButton->setText("LED熄灭3");
}
void MainWindow::pb4()
{
pushButton->setText("oled");
}
void MainWindow::pb5()
{
pushButton->setText("相机");
}
void MainWindow::ui_init()
{
    //    screenWidth=list_screen.at(0)->geometry().width();
    //    screenHeigh=list_screen.at(0)->geometry().height();
        this->setGeometry(0,0,screenWidth,screenHeigh);

        setBackground(QPixmap(":/misc/resource/image/text3.jpeg"));

        pushButton = new QPushButton(this);
//        pbt2 = new QPushButton(this);
//        pbt2->setGeometry(300,200,80,40);
        /* 居中显示 */
        pushButton->setMinimumSize(200, 50);
        pushButton->setGeometry(770 ,
                                400,
                                pushButton->width(),
                                pushButton->height()
                                );
        //led_control();
        hWidget = new QWidget(this);
        hWidget->setGeometry(0, 0,1000, 500);



    //    vWidget = new QWidget(this);
    //    vWidget->setGeometry(0, 360, 1469, 360);
    //    hLayout = new QHBoxLayout();
    //    vLayout = new QVBoxLayout();
        auto pLayout = new QGridLayout;
        QList <QString>list;
        list<<"one"<<"two"<<"three"<<"four"<<"five"<<"six"<<"7"<<"8"<<"9"<<"10"<<"11";
        /* 用一个循环实例化 6 个按钮 */
        //oled
        auto pOLEDBtn = createButton("", "OLEDBtn");
        pOLEDBtn->setStyleSheet("border-image: url(:/misc/resource/oled.png);");
        connect(pOLEDBtn, &QPushButton::clicked, this, &MainWindow::pb4);
        pOLEDBtn->setMaximumSize(100, 100);
        label[1] = new QLabel(this);
        QFont ft;
        ft.setPointSize(16);
        label[1]->setFont(ft);
        label[1]->setGeometry(242, 420, 100,40);
        label[1]->setText("oled");

        label[2] = new QLabel(this);
        QFont ft1;
        ft1.setPointSize(14);
        label[2]->setFont(ft1);
        label[2]->setGeometry(74, 420, 100,40);//(124, 420, 100,40);
        label[2]->setText("遥控器");
        //遥控器
        auto pRemoteControlBtn = createButton("", "remoteControlBtn");
        pRemoteControlBtn->setStyleSheet("border-image: url(:/misc/resource/image/remotecontrol.png);");
        connect(pRemoteControlBtn, &QPushButton::clicked, this, &MainWindow::pb1);
        pRemoteControlBtn->setMaximumSize(100, 100);

        auto pUltrasonicWaveBtn = createButton("", "ultrasonicWaveBtn");
        pUltrasonicWaveBtn->setStyleSheet("border-image: url(:/misc/resource/image/ultrasonicwave.png);");
        connect(pUltrasonicWaveBtn, &QPushButton::clicked, this, &MainWindow::pb4);
        pUltrasonicWaveBtn->setMaximumSize(100, 100);

        auto pPhotosensitiveBtn = createButton("", "photosensitiveBtn");
        pPhotosensitiveBtn->setStyleSheet("border-image: url(:/misc/resource/image/photosensitive.png);");
        connect(pPhotosensitiveBtn, &QPushButton::clicked, this, &MainWindow::pb3);
        pPhotosensitiveBtn->setMaximumSize(100, 100);

        auto pElectricityBtn = createButton("", "electricityBtn");
        pElectricityBtn->setStyleSheet("border-image: url(:/misc/resource/image/electricity.png);");
        connect(pElectricityBtn, &QPushButton::clicked, this, &MainWindow::pb2);
        pElectricityBtn->setMaximumSize(100, 100);

        auto pInfraredBtn = createButton("", "infraredBtn");
        pInfraredBtn->setStyleSheet("border-image: url(:/misc/resource/image/infrared.png);");
        connect(pInfraredBtn, &QPushButton::clicked, this, &MainWindow::pb1);
        pInfraredBtn->setMaximumSize(100, 100);
        /*******************/
        auto pCameraBtn = createButton("相机", "cameraBtn", this);
        pCameraBtn->setStyleSheet("border-image: url(:/misc/resource/image/camera.png);");
        connect(pCameraBtn, &QPushButton::clicked, this, &MainWindow::pb5);
        pCameraBtn->setMaximumSize(100, 100);
        auto pMusicBtn = createButton("音乐", "musicBtn");
        pMusicBtn->setStyleSheet("border-image: url(:/misc/resource/image/music.png);");
        connect(pMusicBtn, &QPushButton::clicked, this, &MainWindow::musicBtnClicked);
        pMusicBtn->setMaximumSize(100, 100);
        auto pCalculatorBtn = createButton("计算器", "calculatorBtn");
        pCalculatorBtn->setStyleSheet("border-image: url(:/misc/resource/image/calculator.png);");
        connect(pCalculatorBtn, &QPushButton::clicked, this, &MainWindow::calculatorBtnClicked);
        pCalculatorBtn->setMaximumSize(100, 100);
        auto pSystemBtn = createButton("系统", "systemBtn");
        pSystemBtn->setStyleSheet("border-image: url(:/misc/resource/image/system.png);");
        connect(pSystemBtn, &QPushButton::clicked, this, &MainWindow::systemBtnClicked);
        pSystemBtn->setMaximumSize(100, 100);
        auto pRecorderBtn = createButton("录音机", "recorderBtn");
        pRecorderBtn->setStyleSheet("border-image: url(:/misc/resource/image/recorder.png);");
        connect(pRecorderBtn, &QPushButton::clicked, this, &MainWindow::recorderBtnClicked);
        pRecorderBtn->setMaximumSize(100, 100);
        auto pVideoBtn = createButton("视频", "videoBtn");
        pVideoBtn->setStyleSheet("border-image: url(:/misc/resource/image/video.png);");
        connect(pVideoBtn, &QPushButton::clicked, this, &MainWindow::videoBtnClicked);
        pVideoBtn->setMaximumSize(100, 100);

/*
        for(int i = 1; i < 4; i++)
        {
            pb[i] = new QPushButton();
            pb[i]->setText(list[i-1]);
            //pb[i]->setMinimumSize(50, 50);
            pb[i]->setMaximumSize(100, 100);
//            if(i < 4)
//            {
                pLayout->addWidget(pb[i],0,i);
//            }
//            else
//            {
//                pLayout->addWidget(pb[i],1,i-3);
//            }

        }
    //    hLayout->setSpacing(50);
        //pLayout->setSpacing(300);
*/

        pLayout->addWidget(pCameraBtn,0,1);
        pLayout->addWidget(pMusicBtn,0,2);
        pLayout->addWidget(pCalculatorBtn,0,3);
        pLayout->addWidget(pSystemBtn,0,4);
        pLayout->addWidget(pRecorderBtn,0,5);
        pLayout->addWidget(pVideoBtn,0,6);
        pLayout->addWidget(pRemoteControlBtn,1,1 );
        pLayout->addWidget(pOLEDBtn,1,2);


    //    connect(pb[1], &QPushButton::clicked, this, &MainWindow::pb1);
    //    connect(pb[2], &QPushButton::clicked, this, &MainWindow::pb2);
    //    connect(pb[3], &QPushButton::clicked, this, &MainWindow::pb3);
    //    connect(pb[4], &QPushButton::clicked, this, &MainWindow::pb4);
    //    connect(pb[5], &QPushButton::clicked, this, &MainWindow::pb5);
        pLayout->setHorizontalSpacing(10);
        pLayout->setVerticalSpacing(50);
        pLayout->setMargin(20);
        hWidget->setLayout(pLayout);
    //    vWidget->setLayout(vLayout);
}
QPushButton *MainWindow::createButton(const QString &text, const QString& objName, QWidget *parent)
{
    auto ret = new QPushButton(text, parent);

    ret->setObjectName(objName);

    return ret;
}


void MainWindow::videoBtnClicked()
{
    pushButton->setText("视频");
    m_pGenericWidget = new videowidget(this);
    m_pGenericWidget->installEventFilter(this);
    m_pGenericWidget->setFixedSize(this->size());
    //m_pGenericWidget->setCursor(QCursor(QPixmap(":/misc/resource/image/point.png"), -1, -1));
    m_pGenericWidget->show();
}

void MainWindow::recorderBtnClicked()
{
    pushButton->setText("录音机");
}

void MainWindow::systemBtnClicked()
{
    pushButton->setText("系统");
}

void MainWindow::calculatorBtnClicked()
{
    pushButton->setText("计算器");
    m_pGenericWidget = new calculatorwidget(this);
    m_pGenericWidget->installEventFilter(this);
    m_pGenericWidget->setFixedSize(this->size());
    //m_pGenericWidget->setCursor(QCursor(QPixmap(":/misc/resource/image/point.png"), -1, -1));
    m_pGenericWidget->show();
}

void MainWindow::musicBtnClicked()
{
    pushButton->setText("音乐");
    m_pGenericWidget = new musicwidget(this);
    m_pGenericWidget->installEventFilter(this);
    m_pGenericWidget->setFixedSize(this->size());
    m_pGenericWidget->setCursor(QCursor(QPixmap(":/misc/resource/image/point.png"), -1, -1));
    m_pGenericWidget->show();
    //pbclose= ~pbclose;
}

void MainWindow::cameraBtnClicked()
{
    pushButton->setText("相机");
    m_pGenericWidget = new MapWidget(this);
    m_pGenericWidget->installEventFilter(this);
    m_pGenericWidget->setFixedSize(this->size());
    //m_pGenericWidget->setCursor(QCursor(QPixmap(":/misc/resource/image/point.png"), -1, -1));
    m_pGenericWidget->show();


}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    auto ptr = m_pGenericWidget;
    if ((ptr != nullptr) && (ptr == obj)) {
        if (event->type() == QEvent::KeyPress) {
            auto keyEvt = reinterpret_cast<QKeyEvent*>(event);
            if (keyEvt != nullptr && keyEvt->key() == Qt::Key_Escape) {
                removeEventFilter(ptr);
                delete ptr;
                return true;
            }
        }
        else if (event->type() == QEvent::Close) {
            removeEventFilter(ptr);
            delete ptr;
            return true;
        }
    }

    return false;
}
