#include "PauseScene.h"
#include <QGraphicsRectItem>
#include <QBrush>
#include <QFont>

PauseScene::PauseScene(QObject *parent) : QGraphicsScene(parent) {
    setSceneRect(0, 0, 1280, 720);
    
    // 半透明背景
    QPixmap bgPixmap(":/Scenes/pause_background.png");
    if (!bgPixmap.isNull()) {
        QGraphicsPixmapItem *bg = new QGraphicsPixmapItem(bgPixmap.scaled(1280, 720, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        addItem(bg);
        bg->setPos(0, 0);
    } else {
        // 半透明遮罩作为备用
        overlay = new QGraphicsRectItem(0, 0, 1280, 720);
        overlay->setBrush(QBrush(QColor(0, 0, 0, 180)));
        overlay->setPen(Qt::NoPen);
        addItem(overlay);
    }
    
    // 暂停文本
    pauseText = new QGraphicsTextItem("游戏暂停");
    pauseText->setDefaultTextColor(Qt::white);
    QFont font("Arial", 72, QFont::Bold);
    pauseText->setFont(font);
    addItem(pauseText);
    pauseText->setPos(640 - pauseText->boundingRect().width() / 2, 150);
    
    // 恢复游戏按钮
    resumeButton = new UIButton(":/UI/resume_button.png");
    resumeButton->setScale(0.6);
    addItem(resumeButton);
    resumeButton->setPos(640 - resumeButton->boundingRect().width() * 0.6 / 2, 300);
    connect(resumeButton, &UIButton::clicked, this, &PauseScene::resumeGame);
    
    // 重新开始按钮
    restartButton = new UIButton(":/UI/restart_button.png");
    restartButton->setScale(0.58);
    addItem(restartButton);
    restartButton->setPos(640 - restartButton->boundingRect().width() * 0.58 / 2, 400);
    connect(restartButton, &UIButton::clicked, this, &PauseScene::restartGame);
    
    // 回到标题按钮
    titleButton = new UIButton(":/UI/title_button.png");
    titleButton->setScale(0.058);
    addItem(titleButton);
    titleButton->setPos(640 - titleButton->boundingRect().width() * 0.058 / 2, 500);
    connect(titleButton, &UIButton::clicked, this, &PauseScene::backToTitle);
}