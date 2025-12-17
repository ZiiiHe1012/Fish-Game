#ifndef BATTLESCENE_H
#define BATTLESCENE_H

#include <QKeyEvent>
#include <QMouseEvent>
#include "Scene.h"
#include "../Items/Maps/Map.h"
#include "../Items/Characters/Character.h"
#include "../Items/Fish/SmallFish.h"
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
    
    void setLevel(int level) { currentLevel = level; }
    
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
    void spawnBigFish();
    void checkCollisions();
    void updateCameraView();
    
    Map *map;
    Character *character;
    QVector<SmallFish*> smallFishes;
    QVector<BigFish*> bigFishes;
    int score{0};
    int fishEaten{0};  // 记录吃掉的小鱼数量
    int health{100};        // 血量
    int maxHealth{100};     // 最大血量
    int currentLevel{1};  // 当前关卡
    bool mouseInScene{false};

    GameUI *gameUI{nullptr};  // 添加 UI

    qint64 smallFishSpawnTimer{0};
    qint64 bigFishSpawnTimer{0};
    qint64 smallFishSpawnInterval{2000};  // 小鱼生成间隔2秒
    qint64 bigFishSpawnInterval{5000};    // 大鱼生成间隔5秒

    // 添加地图和视角相关
    qreal mapWidth{2560};   // 地图宽度：1280 * 2
    qreal mapHeight{1440};  // 地图高度：720 * 2

    QGraphicsTextItem *playerNotification{nullptr};  // 玩家提示文字
    qint64 notificationTimer{0};  // 提示显示计时器
};

#endif