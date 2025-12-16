#include "GameOverScene.h"
#include <QFont>

GameOverScene::GameOverScene(QObject *parent, bool victory, int score) : Scene(parent) {
    setSceneRect(0, 0, 1280, 720);
    
    // 背景
    QString bgPath = victory ? ":/Scenes/victory_background.png" : ":/Scenes/gameover_background.png";
    background = new QGraphicsPixmapItem(QPixmap(bgPath));
    addItem(background);
    
    // 结果文本
    resultText = new QGraphicsTextItem(victory ? "胜利!" : "游戏结束");
    resultText->setDefaultTextColor(victory ? Qt::yellow : Qt::red);
    QFont titleFont("Arial", 64, QFont::Bold);
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
    
    // 重新开始按钮
    restartButton = new UIButton(":/UI/restart_button.png");
    addItem(restartButton);
    restartButton->setPos(640 - restartButton->boundingRect().width() / 2, 400);
    connect(restartButton, &UIButton::clicked, this, &GameOverScene::restartGame);
    
    // 回到标题按钮
    titleButton = new UIButton(":/UI/title_button.png");
    addItem(titleButton);
    titleButton->setPos(640 - titleButton->boundingRect().width() / 2, 500);
    connect(titleButton, &UIButton::clicked, this, &GameOverScene::backToTitle);
}