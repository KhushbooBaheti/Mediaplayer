#include "mediaplayer.h"
#include "ui_mediaplayer.h"
#include <QMediaService>

mediaplayer::mediaplayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mediaplayer)
  #ifndef PLAYER_NO_COLOROPTIONS
      , colorDialog(0)
  #endif

{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    vw = new QVideoWidget(this);
    player->setVideoOutput(vw);
    this->setCentralWidget(vw);


//     connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));

   QLabel* volume=new QLabel(this);

   volume->setText("volume");


    slider = new QSlider(this);
   bar = new QProgressBar(this);
    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);
    volumeSlider->setFixedWidth(100);
    volumeSlider->setValue(100);
    slider->setFixedWidth(700);
    slider->setOrientation(Qt::Horizontal);
    ui->statusBar->addPermanentWidget(slider);
    ui->statusBar->addPermanentWidget(bar);
   ui->statusBar->addPermanentWidget(volume);

    ui->statusBar->addPermanentWidget(volumeSlider);

    connect(volumeSlider, SIGNAL(valueChanged(int)), this, SIGNAL(volumeChanged(int)));
    connect(volumeSlider, SIGNAL(valueChanged(int)), player, SLOT(setVolume(int)));
    connect(player,&QMediaPlayer::durationChanged,slider,&QSlider::setMaximum);
    connect(player,&QMediaPlayer::positionChanged,slider,&QSlider::setValue);
    connect(slider,&QSlider::sliderMoved,player,&QMediaPlayer::setPosition);

    connect(player,&QMediaPlayer::durationChanged,bar,&QProgressBar::setMaximum);
    connect(player,&QMediaPlayer::positionChanged,bar,&QProgressBar::setValue);
#ifndef PLAYER_NO_COLOROPTIONS
    colorButton = new QPushButton(tr("Color Options..."), this);
    ui->statusBar->addPermanentWidget(colorButton);
    colorButton->setEnabled(false);
    connect(colorButton, SIGNAL(clicked()), this, SLOT(showColorDialog()));
#endif
#ifndef PLAYER_NO_COLOROPTIONS
        colorButton->setEnabled(true);
#endif



  }


void mediaplayer::mouseDoubleClickEvent(QMouseEvent *e) {
  QWidget::mouseDoubleClickEvent(e);
  if(isFullScreen()) {
     this->setWindowState(Qt::WindowNoState);
      ui->statusBar->show();
       ui->menuBar->show();
       ui->fullscreen->show();
  } else {
     this->setWindowState(Qt::WindowFullScreen);
       ui->statusBar->hide();
       ui->menuBar->hide();
       ui->fullscreen->hide();
  }
}
void mediaplayer::keyPressEvent(QKeyEvent* event){
    //QWidget::keyPressEvent(event);
    if ((event->key()==Qt::Key_Escape)){
          // this->setWindowState(Qt::WindowFullScreen);

        this->setWindowState(Qt::WindowNoState);
         ui->statusBar->show();
          ui->menuBar->show();
          ui->fullscreen->show();

    }
    else if(event->key()==Qt::Key_Space){
        player->pause();
         ui->statusBar->showMessage("paused!!");

    }
    else if(event->key()==Qt::Key_P){
        player->play();
         ui->statusBar->showMessage("playing!!");
    }
}

void mediaplayer::mouseMoveEvent(QMouseEvent* q) {
 // QWidget::mouseDoubleClickEvent(e);
    if (q->type() == QEvent::MouseMove){
     //this->setWindowState(Qt::WindowNoState);
      ui->statusBar->show();
      // ui->menuBar->show();
       ui->fullscreen->show();
       /*if(q->type() == QEvent::){
           this->setWindowState(Qt::WindowFullScreen);
             ui->statusBar->hide();
             ui->menuBar->hide();
             ui->fullscreen->hide();

       }*/
  }}

mediaplayer::~mediaplayer()
{
    delete ui;


}

void mediaplayer::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"open a file","","Audio Files(*.*),Video Files(*.*)");

    on_actionStop_triggered();

    player->setMedia(QUrl::fromLocalFile(filename));

    on_actionPlay_triggered();
}

void mediaplayer::on_actionPlay_triggered()
{
    player->play();
    ui->statusBar->showMessage("playing!!");
}

void mediaplayer::on_actionStop_triggered()
{
    player->stop();
    ui->statusBar->showMessage("stopped!!");
}

void mediaplayer::on_actionPause_triggered()
{
    player->pause();
    ui->statusBar->showMessage("paused!!");
}




void mediaplayer::on_actionFullscreen_triggered()
{
   /* if(isFullScreen()) {
       this->setWindowState(Qt::WindowNoState);
        ui->statusBar->show();
        ui->menuBar->show();
        ui->fullscreen->show();
    }else {*/
       this->setWindowState(Qt::WindowFullScreen);
        ui->statusBar->hide();
        ui->menuBar->hide();
        ui->fullscreen->hide();

}

void mediaplayer::on_actionQuit_triggered()
{
    mediaplayer::close();

}
#ifndef PLAYER_NO_COLOROPTIONS
void mediaplayer::showColorDialog()
{
    if (!colorDialog) {
        QSlider *brightnessSlider = new QSlider(Qt::Horizontal);
        brightnessSlider->setRange(-100, 100);
        brightnessSlider->setValue(vw->brightness());
        connect(brightnessSlider, SIGNAL(sliderMoved(int)), vw,SLOT(setBrightness(int)));
        connect(vw, SIGNAL(brightnessChanged(int)), brightnessSlider, SLOT(setValue(int)));

        QSlider *contrastSlider = new QSlider(Qt::Horizontal);
        contrastSlider->setRange(-100, 100);
        contrastSlider->setValue(vw->contrast());
        connect(contrastSlider, SIGNAL(sliderMoved(int)), vw, SLOT(setContrast(int)));
        connect(vw, SIGNAL(contrastChanged(int)), contrastSlider, SLOT(setValue(int)));

        QSlider *hueSlider = new QSlider(Qt::Horizontal);
        hueSlider->setRange(-100, 100);
        hueSlider->setValue(vw->hue());
        connect(hueSlider, SIGNAL(sliderMoved(int)), vw, SLOT(setHue(int)));
        connect(vw, SIGNAL(hueChanged(int)), hueSlider, SLOT(setValue(int)));

        QSlider *saturationSlider = new QSlider(Qt::Horizontal);
        saturationSlider->setRange(-100, 100);
        saturationSlider->setValue(vw->saturation());
        connect(saturationSlider, SIGNAL(sliderMoved(int)), vw, SLOT(setSaturation(int)));
        connect(vw, SIGNAL(saturationChanged(int)), saturationSlider, SLOT(setValue(int)));

        QFormLayout *layout = new QFormLayout;
        layout->addRow(tr("Brightness"), brightnessSlider);
        layout->addRow(tr("Contrast"), contrastSlider);
        layout->addRow(tr("Hue"), hueSlider);
        layout->addRow(tr("Saturation"), saturationSlider);

        QPushButton *button = new QPushButton(tr("Close"));
        layout->addRow(button);

        colorDialog = new QDialog(this);
        colorDialog->setWindowTitle(tr("Color Options"));
        colorDialog->setLayout(layout);

        connect(button, SIGNAL(clicked()), colorDialog, SLOT(close()));
    }
    colorDialog->show();
}
#endif

