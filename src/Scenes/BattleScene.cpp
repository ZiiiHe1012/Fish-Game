#include "BattleScene.h"
#include "../Items/Characters/Link.h"
#include "../Items/Maps/Battlefield.h"
#include <QRandomGenerator>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

BattleScene::BattleScene(QObject *parent) : Scene(parent) {
    setSceneRect(0, 0, 1280, 720);
    
    // 背景
    map = new Battlefield();
    addItem(map);
    
    if (map->getPixmapItem()) {
        QPixmap bgPixmap = map->getPixmapItem()->pixmap();
        if (!bgPixmap.isNull()) {
            map->getPixmapItem()->setPixmap(bgPixmap.scaled(1280, 720, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        }
    }
    map->setPos(0, 0);
    
    character = new Link();
    addItem(character);
    character->setPos(640, 360);
}

void BattleScene::spawnSmallFish() {
    auto rand = QRandomGenerator::global();
    bool spawnFromLeft = rand->bounded(2) == 0;  // 改名更清晰
    
    SmallFish *fish = new SmallFish(nullptr, spawnFromLeft);
    
    if (spawnFromLeft) {
        // 从左边生成，往右游
        fish->setPos(-50, rand->bounded(720));
    } else {
        // 从右边生成，往左游
        fish->setPos(1330, rand->bounded(720));
    }
    
    addItem(fish);
    smallFishes.append(fish);
}

void BattleScene::spawnBigFish() {
    auto rand = QRandomGenerator::global();
    bool spawnFromLeft = rand->bounded(2) == 0;  // 改名更清晰

    BigFish *fish = new BigFish(nullptr, spawnFromLeft);
    
    if (spawnFromLeft) {
        // 从左边生成，往右游
        fish->setPos(-100, rand->bounded(720));
    } else {
        // 从右边生成，往左游
        fish->setPos(1380, rand->bounded(720));
    }
    
    addItem(fish);
    bigFishes.append(fish);
}

void BattleScene::processInput() {
    Scene::processInput();
}

void BattleScene::processMovement() {
    Scene::processMovement();

    smallFishSpawnTimer += deltaTime;
    bigFishSpawnTimer += deltaTime;
    
    // 检查是否该生成小鱼
    if (smallFishSpawnTimer >= smallFishSpawnInterval) {
        spawnSmallFish();
        smallFishSpawnTimer = 0;
        // 随机下次生成时间
        smallFishSpawnInterval = QRandomGenerator::global()->bounded(500, 1500);
    }
    
    // 检查是否该生成大鱼
    if (bigFishSpawnTimer >= bigFishSpawnInterval) {
        spawnBigFish();
        bigFishSpawnTimer = 0;
        // 随机下次生成时间
        bigFishSpawnInterval = QRandomGenerator::global()->bounded(1000, 2000);
    }

    if (character) {
        // 只有鼠标在场景中时才移动
        if (mouseInScene) {
            character->updateMovement(deltaTime);
        }
        
        // 限制在屏幕内
        QPointF pos = character->pos();
        if (pos.x() < 0) pos.setX(0);
        if (pos.x() > 1280) pos.setX(1280);
        if (pos.y() < 0) pos.setY(0);
        if (pos.y() > 720) pos.setY(720);
        character->setPos(pos);
    }
    
    for (int i = smallFishes.size() - 1; i >= 0; i--) {
        SmallFish *fish = smallFishes[i];
        fish->updateMovement(deltaTime);
        
        QPointF pos = fish->pos();
        // 只有完全离开屏幕很远才删除
        if (pos.x() < -200 || pos.x() > 1480) {  // 扩大边界
            removeItem(fish);
            smallFishes.removeAt(i);
            delete fish;
        }
    }
    
    // 更新大鱼移动 - 修改删除边界
    for (int i = bigFishes.size() - 1; i >= 0; i--) {
        BigFish *fish = bigFishes[i];
        fish->updateMovement(deltaTime);
        
        QPointF pos = fish->pos();
        // 只有完全离开屏幕很远才删除
        if (pos.x() < -250 || pos.x() > 1930) {  // 扩大边界
            removeItem(fish);
            bigFishes.removeAt(i);
            delete fish;
        }
    }
}

void BattleScene::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        emit pauseGame();
    }
    Scene::keyPressEvent(event);
}


void BattleScene::processCollision() {
    checkCollisions();
}

void BattleScene::checkCollisions() {
    if (!character || !character->getPlayerFish()) return;
    
    qreal playerSize = character->getSize();
    QRectF playerRect = character->getPlayerFish()->sceneBoundingRect();
    
    // 检测与小鱼的碰撞
    for (int i = smallFishes.size() - 1; i >= 0; i--) {
        SmallFish *fish = smallFishes[i];
        QRectF fishRect = fish->sceneBoundingRect();
        
        // 使用矩形相交检测
        if (playerRect.intersects(fishRect) && playerSize > fish->getSize()) {
            score++;
            character->grow(1);
            removeItem(fish);
            smallFishes.removeAt(i);
            delete fish;
            spawnSmallFish();
            qDebug() << "Score:" << score;
            
            // 胜利条件：分数达到20
            if (score >= 20) {
                emit gameOver(true);
            }
        }
    }
    
    // 检测与大鱼的碰撞
    for (BigFish *fish : bigFishes) {
        QRectF fishRect = fish->sceneBoundingRect();
        
        // 使用矩形相交检测
        if (playerRect.intersects(fishRect) && playerSize < fish->getSize()) {
            emit gameOver(false);
        }
    }
}

// 添加重置游戏方法
void BattleScene::resetGame() {
    score = 0;
    
    // 清除所有鱼
    for (SmallFish *fish : smallFishes) {
        removeItem(fish);
        delete fish;
    }
    smallFishes.clear();
    
    for (BigFish *fish : bigFishes) {
        removeItem(fish);
        delete fish;
    }
    bigFishes.clear();
    
    // 重置玩家
    if (character) {
        character->setPos(640, 360);
    }
    
    // 重置计时器
    smallFishSpawnTimer = 0;
    bigFishSpawnTimer = 0;
    smallFishSpawnInterval = 2000;
    bigFishSpawnInterval = 5000;
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