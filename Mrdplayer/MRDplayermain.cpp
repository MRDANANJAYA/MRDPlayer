#include "MRDplayer.h"
#include <QApplication>
#include <QSplashScreen>
#include<QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //declare splash screen
    QSplashScreen *splash = new QSplashScreen;
    splash ->setPixmap(QPixmap(":/Resources/ui_icons/Splash Screen.png"));
    splash ->show();
    PlayerWindow w;

    //splash screen time
    QTimer::singleShot(500,splash,SLOT(close()));
    QTimer::singleShot(500,&w,SLOT(show()));
    //w.show();

    return a.exec();
}
