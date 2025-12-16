#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include "Scene.h"
#include "../UI/UIButton.h"

class GameOverScene : public Scene {
    Q_OBJECT
public:
    explicit GameOverScene(QObject *parent, bool victory, int score);
    
signals:
    void restartGame();
    void backToTitle();
    
private:
    QGraphicsPixmapItem *background;
    QGraphicsTextItem *resultText;
    QGraphicsTextItem *scoreText;
    UIButton *restartButton;
    UIButton *titleButton;
};

#endif