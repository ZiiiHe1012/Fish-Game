#ifndef BATTLESCENE_H
#define BATTLESCENE_H

#include <QKeyEvent>
#include <QMouseEvent>
#include "Scene.h"
#include "../Items/Maps/Map.h"
#include "../Items/Characters/Character.h"
#include "../Items/Fish/SmallFish.h"
#include "../Items/Fish/MediumFish.h"
#include "../Items/Fish/GoldenFish.h"
#include "../Items/Fish/BigFish.h"
#include "../UI/GameUI.h"
#include <QVector>

class BattleScene : public Scene {
Q_OBJECT

public:
    explicit BattleScene(QObject *parent);
    
    void processInput() override;
    void processMovement() override;
    void processCollision();
    
    int getScore() const { return score; }
    int getFishEaten() const { return fishEaten; }
    void resetGame();
    
    void setLevel(int level) { 
        currentLevel = level; 
        initializeLevel();  // 添加初始化函数
    }
    
signals:
    void pauseGame();
    void gameOver(bool victory);
    
protected slots:
    void update() override;
    
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void keyPressEvent(QKeyEvent *event) override;
    
private:
    void spawnSmallFish();
    void spawnMediumFish();
    void spawnGoldenFish();
    void spawnBigFish();
    void checkCollisions();
    void updateCameraView();
    void initializeLevel();

    
    Map *map;
    Character *character;
    QVector<SmallFish*> smallFishes;
    QVector<MediumFish*> mediumFishes;
    QVector<GoldenFish*> goldenFishes;
    QVector<BigFish*> bigFishes;
    int score{0};
    int fishEaten{0};
    int health{100};
    int maxHealth{100};
    int currentLevel{1};
    bool mouseInScene{false};

    GameUI *gameUI{nullptr};

    qint64 smallFishSpawnTimer{0};
    qint64 mediumFishSpawnTimer{0};
    qint64 goldenFishSpawnTimer{0};
    qint64 bigFishSpawnTimer{0};
    qint64 smallFishSpawnInterval{2000};
    qint64 mediumFishSpawnInterval{4000};
    qint64 goldenFishSpawnInterval{15000};
    qint64 bigFishSpawnInterval{5000};

    qint64 goldenFishEffectTimer{0};
    bool goldenFishEffectActive{false};
    qreal originalScale{0.2};

    qreal mapWidth{2560};
    qreal mapHeight{1440};

    QGraphicsTextItem *playerNotification{nullptr};
    qint64 notificationTimer{0};

    // 第三关相关
    qint64 survivalTimer{0};  // 存活时间
    qint64 autoHurtTimer{0};  // 自动扣血计时器
    qint64 autoHurtInterval{1500};  // 每3秒扣血一次
    int autoHurtAmount{5};  // 每次扣血量
};

#endif