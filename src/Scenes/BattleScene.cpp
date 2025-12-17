#include "BattleScene.h"
#include "../GameData/GameProgress.h"
#include "../Items/Characters/Link.h"
#include "../Items/Maps/Battlefield.h"
#include "../Items/Maps/BattlefieldLevel2.h"
#include "../Items/Maps/BattlefieldLevel3.h"
#include "../Audio/AudioManager.h"
#include <QRandomGenerator>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsView>

BattleScene::BattleScene(QObject *parent) : Scene(parent) {
    setSceneRect(0, 0, mapWidth, mapHeight);
    
    maxHealth = GameProgress::instance()->getMaxHealth();
    health = maxHealth;

    AudioManager::instance()->playBattleMusic();
    
    character = new Link();
    character->setSpeedMultiplier(GameProgress::instance()->getSpeedMultiplier());
    addItem(character);
    character->setPos(mapWidth / 2, mapHeight / 2);
    
    if (character->getPlayerFish()) {
        originalScale = character->getPlayerFish()->scale();
    }
    
    gameUI = new GameUI(this, this);
    gameUI->updateHealth(health, maxHealth);
    
    playerNotification = new QGraphicsTextItem("");
    playerNotification->setDefaultTextColor(Qt::yellow);
    QFont notifyFont("Arial", 16, QFont::Bold);
    playerNotification->setFont(notifyFont);
    playerNotification->setZValue(11000);
    addItem(playerNotification);
    playerNotification->setVisible(false);
}

void BattleScene::spawnSmallFish() {
    if (!character) return;
    
    auto rand = QRandomGenerator::global();
    bool spawnFromLeft = rand->bounded(2) == 0;
    
    SmallFish *fish = new SmallFish(nullptr, spawnFromLeft);
    
    QPointF playerPos = character->pos();
    
    if (spawnFromLeft) {
        fish->setPos(playerPos.x() - 700, playerPos.y() + rand->bounded(-300, 300));
    } else {
        fish->setPos(playerPos.x() + 700, playerPos.y() + rand->bounded(-300, 300));
    }
    
    addItem(fish);
    smallFishes.append(fish);
}

void BattleScene::spawnMediumFish() {
    if (!character) return;
    
    auto rand = QRandomGenerator::global();
    bool spawnFromLeft = rand->bounded(2) == 0;
    
    MediumFish *fish = new MediumFish(nullptr, spawnFromLeft);
    
    QPointF playerPos = character->pos();
    
    if (spawnFromLeft) {
        fish->setPos(playerPos.x() - 700, playerPos.y() + rand->bounded(-300, 300));
    } else {
        fish->setPos(playerPos.x() + 700, playerPos.y() + rand->bounded(-300, 300));
    }
    
    addItem(fish);
    mediumFishes.append(fish);
}

void BattleScene::spawnGoldenFish() {
    if (!character) return;
    
    auto rand = QRandomGenerator::global();
    bool spawnFromLeft = rand->bounded(2) == 0;
    
    GoldenFish *fish = new GoldenFish(nullptr, spawnFromLeft);
    
    QPointF playerPos = character->pos();
    
    if (spawnFromLeft) {
        fish->setPos(playerPos.x() - 700, playerPos.y() + rand->bounded(-300, 300));
    } else {
        fish->setPos(playerPos.x() + 700, playerPos.y() + rand->bounded(-300, 300));
    }
    
    addItem(fish);
    goldenFishes.append(fish);
}

void BattleScene::spawnBigFish() {
    if (!character) return;
    
    auto rand = QRandomGenerator::global();
    bool spawnFromLeft = rand->bounded(2) == 0;
    
    BigFish *fish = new BigFish(nullptr, spawnFromLeft);
    
    QPointF playerPos = character->pos();
    
    if (spawnFromLeft) {
        fish->setPos(playerPos.x() - 700, playerPos.y() + rand->bounded(-300, 300));
    } else {
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
    
    smallFishSpawnTimer += deltaTime;
    bigFishSpawnTimer += deltaTime;
    
    if (currentLevel == 2 || currentLevel == 3) {
        mediumFishSpawnTimer += deltaTime;
        goldenFishSpawnTimer += deltaTime;
    }
    
    // 第三关特殊逻辑
    if (currentLevel == 3) {
        survivalTimer += deltaTime;
        autoHurtTimer += deltaTime;
        
        // 更新计时器显示
        if (gameUI) {
            gameUI->updateTimer(survivalTimer / 1000);
        }

        // 自动扣血
        if (autoHurtTimer >= autoHurtInterval) {
            health -= autoHurtAmount;
            autoHurtTimer = 0;
            
            if (gameUI) {
                gameUI->updateHealth(health, maxHealth);
            }
            
            if (health <= 0) {
                emit gameOver(false);
            }
        }
        
        // 存活60秒胜利
        if (survivalTimer >= 60000) {
            GameProgress::instance()->completeLevel(currentLevel);
            emit gameOver(true);
        }
    }
    
    if (smallFishSpawnTimer >= smallFishSpawnInterval) {
        spawnSmallFish();
        smallFishSpawnTimer = 0;
        smallFishSpawnInterval = QRandomGenerator::global()->bounded(1500, 3000);
    }
    
    if (currentLevel == 2 || currentLevel == 3) {
        if (mediumFishSpawnTimer >= mediumFishSpawnInterval) {
            spawnMediumFish();
            mediumFishSpawnTimer = 0;
            mediumFishSpawnInterval = QRandomGenerator::global()->bounded(3000, 5000);
        }
        
        if (goldenFishSpawnTimer >= goldenFishSpawnInterval) {
            spawnGoldenFish();
            goldenFishSpawnTimer = 0;
            goldenFishSpawnInterval = QRandomGenerator::global()->bounded(12000, 18000);
        }
    }
    
    if (bigFishSpawnTimer >= bigFishSpawnInterval) {
        spawnBigFish();
        bigFishSpawnTimer = 0;
        // 第三关增加鲨鱼生成频率
        if (currentLevel == 3) {
            bigFishSpawnInterval = QRandomGenerator::global()->bounded(2000, 4000);
        } else {
            bigFishSpawnInterval = QRandomGenerator::global()->bounded(4000, 7000);
        }
    }
    
    if (goldenFishEffectActive) {
        goldenFishEffectTimer -= deltaTime;
        if (goldenFishEffectTimer <= 0) {
            goldenFishEffectActive = false;
            if (character && character->getPlayerFish()) {
                character->getPlayerFish()->setScale(originalScale);
            }
        }
    }
    
    if (character) {
        if (mouseInScene) {
            character->updateMovement(deltaTime);
        }
        
        QPointF pos = character->pos();
        pos.setX(qBound(0.0, pos.x(), mapWidth - 100));
        pos.setY(qBound(0.0, pos.y(), mapHeight - 100));
        character->setPos(pos);
        
        updateCameraView();
    }
    
    for (int i = smallFishes.size() - 1; i >= 0; i--) {
        SmallFish *fish = smallFishes[i];
        fish->updateMovement(deltaTime);
        
        QPointF pos = fish->pos();
        if (pos.x() < -200 || pos.x() > mapWidth + 200) {
            removeItem(fish);
            smallFishes.removeAt(i);
            delete fish;
        }
    }
    
    for (int i = mediumFishes.size() - 1; i >= 0; i--) {
        MediumFish *fish = mediumFishes[i];
        fish->updateMovement(deltaTime);
        
        QPointF pos = fish->pos();
        if (pos.x() < -200 || pos.x() > mapWidth + 200) {
            removeItem(fish);
            mediumFishes.removeAt(i);
            delete fish;
        }
    }
    
    for (int i = goldenFishes.size() - 1; i >= 0; i--) {
        GoldenFish *fish = goldenFishes[i];
        fish->updateMovement(deltaTime);
        
        QPointF pos = fish->pos();
        if (pos.x() < -200 || pos.x() > mapWidth + 200) {
            removeItem(fish);
            goldenFishes.removeAt(i);
            delete fish;
        }
    }
    
    QPointF playerPos = character ? character->pos() : QPointF(0, 0);
    int playerSize = character ? character->getSize() : 5;
    for (int i = bigFishes.size() - 1; i >= 0; i--) {
        BigFish *fish = bigFishes[i];
        fish->updateMovement(deltaTime, playerPos, playerSize);  // 传入 playerSize
        
        QPointF pos = fish->pos();
        if (pos.x() < -250 || pos.x() > mapWidth + 250 || 
            pos.y() < -250 || pos.y() > mapHeight + 250) {
            removeItem(fish);
            bigFishes.removeAt(i);
            delete fish;
        }
    }

    if (character && playerNotification) {
        if (playerNotification->isVisible()) {
            QPointF playerPos = character->pos();
            playerNotification->setPos(playerPos.x() - playerNotification->boundingRect().width() / 2 - 10, 
                                    playerPos.y() - 120);
            
            notificationTimer -= deltaTime;
            if (notificationTimer <= 0) {
                playerNotification->setVisible(false);
                playerNotification->setDefaultTextColor(Qt::yellow);
            }
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
            
            // 第三关吃鱼加血
            if (currentLevel == 3) {
                health = qMin(health + 10, maxHealth);
                if (gameUI) {
                    gameUI->updateHealth(health, maxHealth);
                }
            }

            AudioManager::instance()->playEatSound();
            character->playEatingAnimation();
            
            removeItem(fish);
            smallFishes.removeAt(i);
            delete fish;
            
            if (gameUI) {
                int targetScore = (currentLevel == 2) ? 50 : ((currentLevel == 3) ? 999 : 20);
                gameUI->updateProgress(score, targetScore);
            }
            
            qDebug() << "Score:" << score << "Fish eaten:" << fishEaten;
            
            if (currentLevel == 1 && score >= 20) {
                GameProgress::instance()->completeLevel(currentLevel);
                emit gameOver(true);
            } else if (currentLevel == 2 && score >= 50) {
                GameProgress::instance()->completeLevel(currentLevel);
                emit gameOver(true);
            }
        }
    }
    
    // 检测与中等鱼的碰撞（关卡2和3）
     for (int i = mediumFishes.size() - 1; i >= 0; i--) {
        MediumFish *fish = mediumFishes[i];
        QRectF fishRect = fish->sceneBoundingRect();
        
        if (playerRect.intersects(fishRect)) {
            // 如果金色鱼效果激活，直接可以吃
            bool canEat = goldenFishEffectActive || (playerSize > fish->getSize() * 3);
            
            if (canEat) {
                // 玩家吃掉中等鱼
                score += 3;
                fishEaten++;
                character->grow(3);
                
                // 第三关吃鱼加血
                if (currentLevel == 3) {
                    health = qMin(health + 15, maxHealth);
                    if (gameUI) {
                        gameUI->updateHealth(health, maxHealth);
                    }
                }
                
                AudioManager::instance()->playEatSound();
                character->playEatingAnimation();
                
                removeItem(fish);
                mediumFishes.removeAt(i);
                delete fish;
                
                if (gameUI) {
                    int targetScore = (currentLevel == 2) ? 50 : ((currentLevel == 3) ? 999 : 20);
                    gameUI->updateProgress(score, targetScore);
                }
                
                qDebug() << "Ate medium fish! Score:" << score;
                
                if (currentLevel == 1 && score >= 20) {
                    GameProgress::instance()->completeLevel(currentLevel);
                    emit gameOver(true);
                } else if (currentLevel == 2 && score >= 50) {
                    GameProgress::instance()->completeLevel(currentLevel);
                    emit gameOver(true);
                }
            } else {
                // 被中等鱼吃掉，扣血
                health -= 30;
                
                AudioManager::instance()->playHurtSound();
                character->applyRedTint();
                
                if (gameUI) {
                    gameUI->updateHealth(health, maxHealth);
                }
                
                removeItem(fish);
                mediumFishes.removeAt(i);
                delete fish;
                
                qDebug() << "Hit by medium fish! Health:" << health;
                
                if (health <= 0) {
                    emit gameOver(false);
                }
            }
        }
    }
    
    // 检测与金色鱼的碰撞（关卡2）
    for (int i = goldenFishes.size() - 1; i >= 0; i--) {
        GoldenFish *fish = goldenFishes[i];
        QRectF fishRect = fish->sceneBoundingRect();
        
        if (playerRect.intersects(fishRect)) {
            // 吃到金色鱼，激活效果
            goldenFishEffectActive = true;
            goldenFishEffectTimer = 8000;
            score += 5;

            if (character && character->getPlayerFish()) {
                originalScale = character->getPlayerFish()->scale();
                character->getPlayerFish()->setScale(originalScale * 2.0);
            }
            
            AudioManager::instance()->playEatSound();
            
            removeItem(fish);
            goldenFishes.removeAt(i);
            delete fish;
            
            qDebug() << "Ate golden fish! Scale doubled for 10 seconds!";
        
            if (currentLevel == 2 && score >= 50) {
                GameProgress::instance()->completeLevel(currentLevel);
                emit gameOver(true);
            }
        }
    }
    
    // 检测与大鱼的碰撞
    for (int i = bigFishes.size() - 1; i >= 0; i--) {
        BigFish *fish = bigFishes[i];
        QRectF fishRect = fish->sceneBoundingRect();
        
        if (playerRect.intersects(fishRect)) {
            health -= 50;
            
            AudioManager::instance()->playHurtSound();
            character->applyRedTint();

            if (gameUI) {
                gameUI->updateHealth(health, maxHealth);
            }
            
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

void BattleScene::resetGame() {
    score = 0;
    fishEaten = 0;
    maxHealth = GameProgress::instance()->getMaxHealth();
    health = maxHealth;
    goldenFishEffectActive = false;
    goldenFishEffectTimer = 0;
    
    for (SmallFish *fish : smallFishes) {
        removeItem(fish);
        delete fish;
    }
    smallFishes.clear();
    
    for (MediumFish *fish : mediumFishes) {
        removeItem(fish);
        delete fish;
    }
    mediumFishes.clear();
    
    for (GoldenFish *fish : goldenFishes) {
        removeItem(fish);
        delete fish;
    }
    goldenFishes.clear();
    
    for (BigFish *fish : bigFishes) {
        removeItem(fish);
        delete fish;
    }
    bigFishes.clear();
    
    if (character) {
        character->setPos(mapWidth / 2, mapHeight / 2);
        if (character->getPlayerFish()) {
            character->getPlayerFish()->setScale(originalScale);
        }
    }
    
    if (gameUI) {
        int targetScore = (currentLevel == 2) ? 50 : ((currentLevel == 3) ? 999 : 20);
        gameUI->updateProgress(0, targetScore);
        gameUI->updateHealth(health, maxHealth);
    }
    
    smallFishSpawnTimer = 0;
    mediumFishSpawnTimer = 0;
    goldenFishSpawnTimer = 0;
    bigFishSpawnTimer = 0;
    smallFishSpawnInterval = 2000;
    mediumFishSpawnInterval = 4000;
    goldenFishSpawnInterval = 15000;
    bigFishSpawnInterval = 5000;
    survivalTimer = 0;
    autoHurtTimer = 0;
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
    
    if (gameUI) {
        gameUI->updatePosition(QPointF(viewX, viewY));
    }
}

void BattleScene::initializeLevel() {
    // 创建地图
    if (currentLevel == 2) {
        map = new BattlefieldLevel2();
    } else if (currentLevel == 3) {
        map = new BattlefieldLevel3();
    } else {
        map = new Battlefield();
    }
    addItem(map);
    
    if (map->getPixmapItem()) {
        QPixmap bgPixmap = map->getPixmapItem()->pixmap();
        if (!bgPixmap.isNull()) {
            map->getPixmapItem()->setPixmap(bgPixmap.scaled(mapWidth, mapHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        }
    }
    map->setPos(0, 0);
    map->setZValue(-1);  // 确保背景在最底层
    
    // 设置 UI
    if (!gameUI) return;
    
    if (currentLevel == 3) {
        gameUI->updateProgress(0, 999);
        gameUI->showTimer(true);
        gameUI->updateTimer(0);
    } else if (currentLevel == 2) {
        gameUI->updateProgress(0, 50);
        gameUI->showTimer(false);
    } else {
        gameUI->updateProgress(0, 20);
        gameUI->showTimer(false);
    }
}