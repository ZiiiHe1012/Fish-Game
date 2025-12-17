#include "LevelIntroScene.h"
#include <QFont>
#include <QTextOption>
#include <QTextDocument> 


LevelIntroScene::LevelIntroScene(QObject *parent, int level) 
    : Scene(parent), currentLevel(level) {
    setSceneRect(0, 0, 1280, 720);
    
    // 背景
    QString bgPath = QString(":/Scenes/level%1_intro_background.png").arg(level);
    QPixmap bgPixmap(bgPath);
    if (!bgPixmap.isNull()) {
        background = new QGraphicsPixmapItem(bgPixmap.scaled(1280, 720, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    } else {
        background = new QGraphicsPixmapItem();
        QPixmap colorBg(1280, 720);
        colorBg.fill(QColor(30, 120, 180));
        background->setPixmap(colorBg);
    }
    addItem(background);
    background->setPos(0, 0);
    
    // 关卡标题
    QString levelTitle = QString("Level %1").arg(level);
    titleText = new QGraphicsTextItem(levelTitle);
    titleText->setDefaultTextColor(Qt::white);
    QFont titleFont("Arial", 56, QFont::Bold);
    titleText->setFont(titleFont);
    addItem(titleText);
    titleText->setPos(640 - titleText->boundingRect().width() / 2, 150);
    
    // 关卡描述
    QString description;
    if (level == 1) {
        description = "目标：吃掉20条小鱼\n鱼类：金鱼(可吃) 鲨鱼(敌人 会进行追逐)\n";
    } else if (level == 2) {
        description = "关卡2描述\n（待开发）";
    } else if (level == 3) {
        description = "关卡3描述\n（待开发）";
    }
    
    descText = new QGraphicsTextItem(description);
    descText->setDefaultTextColor(Qt::white);
    QFont descFont("Arial", 24, QFont::Bold);
    descText->setFont(descFont);
    
    addItem(descText);
    descText->setPos(640 - descText->boundingRect().width() / 2, 300);
    
    // 开始按钮
    startButton = new UIButton(":/UI/start_button.png");
    startButton->setScale(2.0);
    addItem(startButton);
    startButton->setPos(640 - startButton->boundingRect().width() * 2.0 / 2, 500);
    connect(startButton, &UIButton::clicked, this, &LevelIntroScene::startLevel);
    
    // 返回按钮
    backButton = new UIButton(":/UI/back_button.png");
    backButton->setScale(0.03);
    addItem(backButton);
    backButton->setPos(1180, 620);
    connect(backButton, &UIButton::clicked, this, &LevelIntroScene::backToLevelSelect);
}