#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include "Scene.h"
#include "../UI/UIButton.h"

class GameOverScene : public Scene {
    Q_OBJECT
public:
    explicit GameOverScene(QObject *parent, bool victory, int score, int level);    
signals:
    void restartGame();
    void backToTitle();
    
private:
    QGraphicsPixmapItem *background;
    QGraphicsTextItem *resultText;
    QGraphicsTextItem *scoreText;
    QGraphicsTextItem *extraText;
    UIButton *restartButton;
    UIButton *titleButton;
    int currentLevel;
};

#endif