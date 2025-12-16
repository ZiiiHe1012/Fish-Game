#include "BattleScene.h"
#include "../Items/Characters/Link.h"
#include "../Items/Maps/Battlefield.h"
#include <QRandomGenerator>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

BattleScene::BattleScene(QObject *parent) : Scene(parent) {
    setSceneRect(0, 0, 1280, 720);
    
    map = new Battlefield();
    character = new Link();
    
    addItem(map);
    addItem(character);
    
    map->scaleToFitScene(this);
    character->setPos(640, 360);
    
    // 初始生成鱼
    for (int i = 0; i < 5; i++) {
        spawnSmallFish();
    }
    for (int i = 0; i < 2; i++) {
        spawnBigFish();
    }
}

void BattleScene::spawnSmallFish() {
    auto rand = QRandomGenerator::global();
    SmallFish *fish = new SmallFish();
    fish->setPos(rand->bounded(1280), rand->bounded(720));
    addItem(fish);
    smallFishes.append(fish);
}

void BattleScene::spawnBigFish() {
    auto rand = QRandomGenerator::global();
    BigFish *fish = new BigFish();
    fish->setPos(rand->bounded(1280), rand->bounded(720));
    addItem(fish);
    bigFishes.append(fish);
}

void BattleScene::processInput() {
    Scene::processInput();
}

void BattleScene::processMovement() {
    Scene::processMovement();
    
    if (character) {
        // 只有鼠标在场景中时才移动
        if (mouseInScene) {
            character->updateMovement(deltaTime);
        }
        
        // 限制在屏幕内
        QPointF pos = character->pos();
        if (pos.x() < 50) pos.setX(50);
        if (pos.x() > 1230) pos.setX(1230);
        if (pos.y() < 50) pos.setY(50);
        if (pos.y() > 670) pos.setY(670);
        character->setPos(pos);
    }
    
    // 更新小鱼移动
    for (SmallFish *fish : smallFishes) {
        fish->updateMovement(deltaTime);
        
        // 边界处理
        QPointF pos = fish->pos();
        if (pos.x() < 0 || pos.x() > 1280 || pos.y() < 0 || pos.y() > 720) {
            fish->setPos(QRandomGenerator::global()->bounded(1280), 
                        QRandomGenerator::global()->bounded(720));
        }
    }
    
    // 更新大鱼移动
    for (BigFish *fish : bigFishes) {
        fish->updateMovement(deltaTime);
        
        // 边界处理
        QPointF pos = fish->pos();
        if (pos.x() < 0 || pos.x() > 1280 || pos.y() < 0 || pos.y() > 720) {
            fish->setPos(QRandomGenerator::global()->bounded(1280), 
                        QRandomGenerator::global()->bounded(720));
        }
    }
}

void BattleScene::processCollision() {
    checkCollisions();
}

void BattleScene::checkCollisions() {
    if (!character) return;
    
    // 检测与小鱼的碰撞
    for (int i = smallFishes.size() - 1; i >= 0; i--) {
        SmallFish *fish = smallFishes[i];
        qreal distance = QLineF(character->pos(), fish->pos()).length();
        
        if (distance < 60 && character->getSize() > fish->getSize()) {
            score++;
            character->grow(1);
            removeItem(fish);
            smallFishes.removeAt(i);
            delete fish;
            spawnSmallFish();
            qDebug() << "Score:" << score;
        }
    }
    
    // 检测与大鱼的碰撞
    for (BigFish *fish : bigFishes) {
        qreal distance = QLineF(character->pos(), fish->pos()).length();
        
        if (distance < 60 && character->getSize() < fish->getSize()) {
            qDebug() << "Game Over! Final Score:" << score;
            // TODO: 游戏结束逻辑
        }
    }
}

void BattleScene::update() {
    Scene::update();
    processCollision();
}

void BattleScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    mouseInScene = true;
    if (character) {
        character->setTargetPos(event->scenePos());
    }
    Scene::mouseMoveEvent(event);
}

void BattleScene::enterEvent(QEvent *event) {
    mouseInScene = true;
}

void BattleScene::leaveEvent(QEvent *event) {
    mouseInScene = false;
}