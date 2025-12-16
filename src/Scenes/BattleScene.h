#ifndef BATTLESCENE_H
#define BATTLESCENE_H

#include <QKeyEvent>
#include <QMouseEvent>
#include "Scene.h"
#include "../Items/Maps/Map.h"
#include "../Items/Characters/Character.h"
#include "../Items/Fish/SmallFish.h"
#include "../Items/Fish/BigFish.h"
#include <QVector>

class BattleScene : public Scene {
Q_OBJECT

public:
    explicit BattleScene(QObject *parent);
    
    void processInput() override;
    void processMovement() override;
    void processCollision();
    
protected slots:
    void update() override;
    
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    
private:
    void spawnSmallFish();
    void spawnBigFish();
    void checkCollisions();
    
    Map *map;
    Character *character;
    QVector<SmallFish*> smallFishes;
    QVector<BigFish*> bigFishes;
    int score{0};
    bool mouseInScene{false};
};

#endif