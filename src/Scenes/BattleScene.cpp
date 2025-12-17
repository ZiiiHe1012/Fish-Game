#include "BattleScene.h"
#include "../Items/Characters/Link.h"
#include "../Items/Maps/Battlefield.h"
#include "../Audio/AudioManager.h"
#include <QRandomGenerator>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsView>


BattleScene::BattleScene(QObject *parent) : Scene(parent) {
    setSceneRect(0, 0, mapWidth, mapHeight);
    
    // 播放战斗音乐
    AudioManager::instance()->playBattleMusic();

    // 背景
    map = new Battlefield();
    addItem(map);
    
    if (map->getPixmapItem()) {
        QPixmap bgPixmap = map->getPixmapItem()->pixmap();
        if (!bgPixmap.isNull()) {
            map->getPixmapItem()->setPixmap(bgPixmap.scaled(mapWidth, mapHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        }
    }
    map->setPos(0, 0);
    
    character = new Link();
    addItem(character);
    character->setPos(mapWidth / 2, mapHeight / 2);
    
    // 创建 UI
    gameUI = new GameUI(this, this);
    gameUI->updateProgress(0, 20);
    gameUI->updateHealth(health, maxHealth);
}

void BattleScene::spawnSmallFish() {
    if (!character) return;
    
    auto rand = QRandomGenerator::global();
    bool spawnFromLeft = rand->bounded(2) == 0;
    
    SmallFish *fish = new SmallFish(nullptr, spawnFromLeft);
    
    // 在玩家视野边缘生成
    QPointF playerPos = character->pos();
    
    if (spawnFromLeft) {
        // 从玩家左边生成
        fish->setPos(playerPos.x() - 700, playerPos.y() + rand->bounded(-300, 300));
    } else {
        // 从玩家右边生成
        fish->setPos(playerPos.x() + 700, playerPos.y() + rand->bounded(-300, 300));
    }
    
    addItem(fish);
    smallFishes.append(fish);
}

void BattleScene::spawnBigFish() {
    if (!character) return;
    
    auto rand = QRandomGenerator::global();
    bool spawnFromLeft = rand->bounded(2) == 0;
    
    BigFish *fish = new BigFish(nullptr, spawnFromLeft);
    
    // 在玩家视野边缘生成
    QPointF playerPos = character->pos();
    
    if (spawnFromLeft) {
        // 从玩家左边生成
        fish->setPos(playerPos.x() - 700, playerPos.y() + rand->bounded(-300, 300));
    } else {
        // 从玩家右边生成
        fish->setPos(playerPos.x() + 700, playerPos.y() + rand->bounded(-300, 300));
    }
    
    addItem(fish);
    bigFishes.append(fish);
}

void BattleScene::processInput() {
    Scene::processInput();
}

void BattleScene::processMovement() {
    Scene::processMovement();
    
    // 累积时间
    smallFishSpawnTimer += deltaTime;
    bigFishSpawnTimer += deltaTime;
    
    // 检查是否该生成小鱼
    if (smallFishSpawnTimer >= smallFishSpawnInterval) {
        spawnSmallFish();
        smallFishSpawnTimer = 0;
        smallFishSpawnInterval = QRandomGenerator::global()->bounded(1500, 3000);
    }
    
    // 检查是否该生成大鱼
    if (bigFishSpawnTimer >= bigFishSpawnInterval) {
        spawnBigFish();
        bigFishSpawnTimer = 0;
        bigFishSpawnInterval = QRandomGenerator::global()->bounded(4000, 7000);
    }
    
    if (character) {
        // 只有鼠标在场景中时才移动
        if (mouseInScene) {
            character->updateMovement(deltaTime);
        }
        
        // 限制玩家在地图范围内
        QPointF pos = character->pos();
        if (pos.x() < 0) pos.setX(0);
        if (pos.x() > mapWidth) pos.setX(mapWidth);
        if (pos.y() < 0) pos.setY(0);
        if (pos.y() > mapHeight) pos.setY(mapHeight);
        character->setPos(pos);
        
        // 视角跟随玩家 - 关键代码
        updateCameraView();
    }
    
    // 更新小鱼移动
    for (int i = smallFishes.size() - 1; i >= 0; i--) {
        SmallFish *fish = smallFishes[i];
        fish->updateMovement(deltaTime);
        
        QPointF pos = fish->pos();
        // 超出地图范围删除
        if (pos.x() < -200 || pos.x() > mapWidth + 200) {
            removeItem(fish);
            smallFishes.removeAt(i);
            delete fish;
        }
    }
    
    // 更新大鱼移动
    QPointF playerPos = character ? character->pos() : QPointF(0, 0);
    for (int i = bigFishes.size() - 1; i >= 0; i--) {
        BigFish *fish = bigFishes[i];
        fish->updateMovement(deltaTime, playerPos);  // 传入玩家位置
        
        QPointF pos = fish->pos();
        if (pos.x() < -250 || pos.x() > mapWidth + 250 || 
            pos.y() < -250 || pos.y() > mapHeight + 250) {  // 也检查Y坐标
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
        
        if (playerRect.intersects(fishRect) && playerSize > fish->getSize()) {
            score++;
            fishEaten++;
            character->grow(1);
            removeItem(fish);
            smallFishes.removeAt(i);
            delete fish;
            
            // 更新进度条
            if (gameUI) {
                gameUI->updateProgress(score, 20);
            }
            
            qDebug() << "Score:" << score << "Fish eaten:" << fishEaten;
            
            if (score >= 20) {
                emit gameOver(true);
            }
        }
    }
    
    // 检测与大鱼的碰撞
    for (int i = bigFishes.size() - 1; i >= 0; i--) {
        BigFish *fish = bigFishes[i];
        QRectF fishRect = fish->sceneBoundingRect();
        
        if (playerRect.intersects(fishRect)) {
            // 碰到大鱼扣血
            health -= 50;
            
            if (gameUI) {
                gameUI->updateHealth(health, maxHealth);
            }
            
            // 击退大鱼（删除并重新生成）
            removeItem(fish);
            bigFishes.removeAt(i);
            delete fish;
            
            qDebug() << "Hit by big fish! Health:" << health;
            
            if (health <= 0) {
                emit gameOver(false);
            }
        }
    }
}

// 添加重置游戏方法
void BattleScene::resetGame() {
    score = 0;
    fishEaten = 0;
    health = 100;  // 重置血量
    
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
    
    // 重置玩家到地图中心
    if (character) {
        character->setPos(mapWidth / 2, mapHeight / 2);
    }
    
    // 重置 UI
    if (gameUI) {
        gameUI->updateProgress(0, 20);
        gameUI->updateHealth(health, maxHealth);
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

void BattleScene::updateCameraView() {
    if (!character) return;
    
    QList<QGraphicsView*> viewsList = views();
    if (viewsList.isEmpty()) return;
    
    QGraphicsView *view = viewsList.first();
    
    QPointF playerPos = character->pos();
    
    qreal viewWidth = 1280;
    qreal viewHeight = 720;
    
    qreal viewX = playerPos.x() - viewWidth / 2;
    qreal viewY = playerPos.y() - viewHeight / 2;
    
    if (viewX < 0) viewX = 0;
    if (viewY < 0) viewY = 0;
    if (viewX + viewWidth > mapWidth) viewX = mapWidth - viewWidth;
    if (viewY + viewHeight > mapHeight) viewY = mapHeight - viewHeight;
    
    view->centerOn(viewX + viewWidth / 2, viewY + viewHeight / 2);
    
    // 每帧更新 UI 位置到视角顶部
    if (gameUI) {
        gameUI->updatePosition(QPointF(viewX, viewY));
    }
}