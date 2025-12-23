#include "TitleScene.h"
#include "../Audio/AudioManager.h"
#include <QGraphicsPixmapItem>

TitleScene::TitleScene(QObject *parent) : Scene(parent) {
    setSceneRect(0, 0, 1280, 720);

    // 播放标题音乐
    AudioManager::instance()->playTitleMusic();

    // 背景 缩放到场景大小
    QPixmap bgPixmap(":/Scenes/title_background.png");
    if (bgPixmap.isNull()) {
        // 如果图片不存在，创建纯色背景
        background = new QGraphicsPixmapItem();
        QPixmap colorBg(1280, 720);
        colorBg.fill(QColor(0, 120, 180));  // 蓝色背景
        background->setPixmap(colorBg);
    } else {
        // 缩放背景图片到1280x720
        background = new QGraphicsPixmapItem(bgPixmap.scaled(1280, 720, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    addItem(background);
    background->setPos(0, 0);
    
    // 游戏标题
    QPixmap titlePixmap(":/UI/game_title.png");
    if (!titlePixmap.isNull()) {
        titleImage = new QGraphicsPixmapItem(titlePixmap);
        addItem(titleImage);
        titleImage->setPos(640 - titleImage->boundingRect().width() / 2, -100);
    } else {
        // 如果没有标题图片，用文字代替
        QGraphicsTextItem *titleText = new QGraphicsTextItem("大鱼吃小鱼");
        titleText->setDefaultTextColor(Qt::white);
        QFont font("Arial", 84, QFont::Bold);
        titleText->setFont(font);
        addItem(titleText);
        titleText->setPos(640 - titleText->boundingRect().width() / 2, 150);
    }
    
    // 开始按钮
    startButton = new UIButton(":/UI/start_button.png");
    startButton->setScale(2.8);
    addItem(startButton);
    startButton->setPos(640 - startButton->boundingRect().width() * 2.8 / 2, 360 - startButton->boundingRect().height() * 2.8 / 2 + 180);
    connect(startButton, &UIButton::clicked, this, &TitleScene::startGame);
    
    // 帮助按钮
    helpButton = new UIButton(":/UI/help_button.png");
    helpButton->setScale(0.03);
    addItem(helpButton);
    helpButton->setPos(1280 - helpButton->boundingRect().width() * 0.03 - 20, 720 - helpButton->boundingRect().height() * 0.03 - 20);    
    connect(helpButton, &UIButton::clicked, this, &TitleScene::showHelp);
}