#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QFile>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScreen>
#include <QRect>
#include <QList>
#include <QLabel>
#include "musicwidget/musicwidget.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
    bool pbclose=0;
    static constexpr int m_screenHeigh = 502;
    static constexpr int m_screenWidth = 1024;
    int screenHeigh = 720;
    int screenWidth = 1469;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //QMainWindow *m_pGenericWidget    = nullptr;
    QWidget *m_pGenericWidget    = nullptr;
protected:
    bool eventFilter(QObject *obj, QEvent *event);
private:

    /* 按钮 */
    QPushButton *pushButton;
    QPushButton *pbt2;
    QPushButton *pb[10];
    QLabel *label[6];
    QWidget *hWidget;
    QWidget *vWidget;
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;
    QPushButton *createButton(const QString &text, const QString &objName, QWidget *parent = nullptr);
    void ui_init();



    /* 文件 */
    QFile file;

    /* 设置lED的状态 */
    void setLedState();

    /* 获取lED的状态 */
    bool getLedState();

    void setBackground(const QPixmap &pixmap);
    void led_control();

private slots:
    void pushButtonClicked();
    void pb1();
    void pb2();
    void pb3();
    void pb4();
    void pb5();
    void videoBtnClicked();
    void recorderBtnClicked();
    void systemBtnClicked();
    void calculatorBtnClicked();
    void musicBtnClicked();
    void cameraBtnClicked();
    //void videoBtnClicked();
};
#endif // MAINWINDOW_H
