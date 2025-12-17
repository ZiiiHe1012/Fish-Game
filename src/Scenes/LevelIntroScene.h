#ifndef LEVELINTROSCENE_H
#define LEVELINTROSCENE_H

#include "Scene.h"
#include "../UI/UIButton.h"

class LevelIntroScene : public Scene {
    Q_OBJECT
public:
    explicit LevelIntroScene(QObject *parent, int level);
    
signals:
    void startLevel();
    void backToLevelSelect();
    
private:
    QGraphicsPixmapItem *background;
    QGraphicsTextItem *titleText;
    QGraphicsTextItem *descText;
    UIButton *startButton;
    UIButton *backButton;
    int currentLevel;
};

#endif