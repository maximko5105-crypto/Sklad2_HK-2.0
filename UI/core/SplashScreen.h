#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QSplashScreen>

class SplashScreen : public QSplashScreen
{
    Q_OBJECT

public:
    explicit SplashScreen();
    void showSplash(int durationMs = 1500);
};

#endif
