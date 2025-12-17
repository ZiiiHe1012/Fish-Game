#include "GameOverScene.h"
#include "../Audio/AudioManager.h"
#include <QFont>

GameOverScene::GameOverScene(QObject *parent, bool victory, int score, int level) 
    : Scene(parent) {
    currentLevel = level;  
    setSceneRect(0, 0, 1280, 720);
    
    // 根据胜利/失败播放不同音乐
    if (victory) {
        AudioManager::instance()->playVictoryMusic();
    } else {
        AudioManager::instance()->playGameOverMusic();
    }

    // 背景 - 全屏缩放
    QString bgPath = victory ? ":/Scenes/victory_background.png" : ":/Scenes/gameover_background.png";
    QPixmap bgPixmap(bgPath);
    if (!bgPixmap.isNull()) {
        background = new QGraphicsPixmapItem(bgPixmap.scaled(1280, 720, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    } else {
        // 纯色背景作为备用
        background = new QGraphicsPixmapItem();
        QPixmap colorBg(1280, 720);
        colorBg.fill(victory ? QColor(50, 150, 50) : QColor(150, 50, 50));
        background->setPixmap(colorBg);
    }
    addItem(background);
    background->setPos(0, 0);
    
    // 结果文本
    resultText = new QGraphicsTextItem(victory ? "游戏胜利" : "游戏结束");
    resultText->setDefaultTextColor(victory ? QColor(255, 215, 0) : Qt::red);
    QFont titleFont("Arial", 84, QFont::Bold);
    resultText->setFont(titleFont);
    addItem(resultText);
    resultText->setPos(640 - resultText->boundingRect().width() / 2, 150);
    
    // 分数文本
    scoreText = new QGraphicsTextItem(QString("得分: %1").arg(score));
    scoreText->setDefaultTextColor(Qt::white);
    QFont scoreFont("Arial", 36);
    scoreText->setFont(scoreFont);
    addItem(scoreText);
    scoreText->setPos(640 - scoreText->boundingRect().width() / 2, 280);
    
    // 额外文本（仅关卡1和2显示）
    if (currentLevel == 1 || currentLevel == 2) {
        QString extraMessage;
        if (currentLevel == 1) {
            extraMessage = victory ? "恭喜通关！获得道具：鲨鱼鳍（速度+25%）" : "";
        } else if (currentLevel == 2) {
            extraMessage = victory ? "恭喜通关！获得道具：护身符（血量上限150）" : "";
        }else if (currentLevel == 3) {
            extraMessage = victory ? "恭喜通关游戏！" : "";
        }
        
        extraText = new QGraphicsTextItem(extraMessage);
        extraText->setDefaultTextColor(Qt::yellow);
        QFont extraFont("Arial", 24);
        extraText->setFont(extraFont);
        addItem(extraText);
        extraText->setPos(640 - extraText->boundingRect().width() / 2, 340);
    }
    
    // 重新开始按钮
    restartButton = new UIButton(":/UI/restart_button.png");
    restartButton->setScale(0.58);
    addItem(restartButton);
    restartButton->setPos(640 - restartButton->boundingRect().width() * 0.58 / 2, 420);
    connect(restartButton, &UIButton::clicked, this, &GameOverScene::restartGame);
    
    // 回到标题按钮
    titleButton = new UIButton(":/UI/title_button.png");
    titleButton->setScale(0.058);
    addItem(titleButton);
    titleButton->setPos(640 - titleButton->boundingRect().width() * 0.058 / 2, 520);
    connect(titleButton, &UIButton::clicked, this, &GameOverScene::backToTitle);
}