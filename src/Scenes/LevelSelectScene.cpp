#include "LevelSelectScene.h"
#include <QFont>

LevelSelectScene::LevelSelectScene(QObject *parent) : Scene(parent) {
    setSceneRect(0, 0, 1280, 720);
    
    // 背景
    QPixmap bgPixmap(":/Scenes/levelselect_background.png");
    if (!bgPixmap.isNull()) {
        background = new QGraphicsPixmapItem(bgPixmap.scaled(1280, 720, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    } else {
        background = new QGraphicsPixmapItem();
        QPixmap colorBg(1280, 720);
        colorBg.fill(QColor(20, 100, 150));
        background->setPixmap(colorBg);
    }
    addItem(background);
    background->setPos(0, 0);
    
    // 标题
    titleText = new QGraphicsTextItem("选择关卡");
    titleText->setDefaultTextColor(Qt::white);
    QFont titleFont("Arial", 72, QFont::Bold);
    titleText->setFont(titleFont);
    addItem(titleText);
    titleText->setPos(640 - titleText->boundingRect().width() / 2, 50);
    
    // 关卡1按钮（左）
    level1Button = new UIButton(":/UI/level1_button.png");
    level1Button->setScale(1);
    addItem(level1Button);
    level1Button->setPos(340 - level1Button->boundingRect().width() * 1 / 2, 270);
    connect(level1Button, &UIButton::clicked, this, [this]() { emit levelSelected(1); });

    // 关卡2按钮（中）
    level2Button = new UIButton(":/UI/level2_button.png");
    level2Button->setScale(1);
    addItem(level2Button);
    level2Button->setPos(640 - level2Button->boundingRect().width() * 1 / 2, 270);
    connect(level2Button, &UIButton::clicked, this, [this]() { emit levelSelected(2); });

    // 关卡3按钮（右）
    level3Button = new UIButton(":/UI/level3_button.png");
    level3Button->setScale(1);
    addItem(level3Button);
    level3Button->setPos(940 - level3Button->boundingRect().width() * 1 / 2, 270);
    connect(level3Button, &UIButton::clicked, this, [this]() { emit levelSelected(3); });
    
    // 返回按钮
    backButton = new UIButton(":/UI/back_button.png");
    backButton->setScale(0.03);
    addItem(backButton);
    backButton->setPos(1180, 620);
    connect(backButton, &UIButton::clicked, this, &LevelSelectScene::backToTitle);
}