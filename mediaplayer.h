#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QMainWindow>
#include<QMediaPlayer>
#include<QVideoWidget>
#include<QFileDialog>
#include<QProgressBar>
#include<QSlider>
#include<QLabel>
#include<QWidget>
#include <QTime>
#include <QKeyEvent>
#include<QMouseEvent>
#include<QPushButton>
#include<QFormLayout>

namespace Ui {
class mediaplayer;
}

class mediaplayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit mediaplayer(QWidget *parent = 0);
    ~mediaplayer();

private slots:
    void on_actionOpen_triggered();

    void on_actionPlay_triggered();

    void on_actionStop_triggered();

    void on_actionPause_triggered();

    void mouseDoubleClickEvent(QMouseEvent*);
    void keyPressEvent(QKeyEvent*);
    void mouseMoveEvent(QMouseEvent*);



    void on_actionFullscreen_triggered();

    //void on_horizontalSlider_actionTriggered(int action);

    void on_actionQuit_triggered();
  //  void durationChanged(qint64 duration);
    //void positionChanged(qint64 progress);


#ifndef PLAYER_NO_COLOROPTIONS
    void showColorDialog();
#endif
private:
    Ui::mediaplayer *ui;
    QMediaPlayer* player;
    QVideoWidget* vw;
    QLabel* volume;
    QProgressBar* bar;
    QSlider* slider;
    QSlider* volumeSlider;
    //void updateDurationInfo(qint64 currentInfo);
    //QLabel *labelDuration;
    //qint64 duration;



#ifndef PLAYER_NO_COLOROPTIONS
QPushButton *colorButton;
QDialog *colorDialog;
#endif

};
#endif // MEDIAPLAYER_H
