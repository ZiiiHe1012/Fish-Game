#ifndef TITLESCENE_H
#define TITLESCENE_H

#include "Scene.h"
#include "../UI/UIButton.h"

class TitleScene : public Scene {
    Q_OBJECT
public:
    explicit TitleScene(QObject *parent);
    
signals:
    void startGame();
    void showHelp();
    
private:
    QGraphicsPixmapItem *background;
    QGraphicsPixmapItem *titleImage;
    UIButton *startButton;
    UIButton *helpButton;
};

#endif