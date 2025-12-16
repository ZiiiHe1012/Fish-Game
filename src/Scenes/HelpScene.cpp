#include "HelpScene.h"
#include <QFont>

HelpScene::HelpScene(QObject *parent) : Scene(parent) {
    setSceneRect(0, 0, 1280, 720);
    
    // 背景
    background = new QGraphicsPixmapItem(QPixmap(":/Scenes/help_background.png"));
    addItem(background);
    
    // 帮助文本
    helpText = new QGraphicsTextItem();
    helpText->setPlainText(
        "游戏玩法:\n\n"
        "1. 移动鼠标控制鱼的移动方向\n"
        "2. 吃掉比你小的鱼来成长\n"
        "3. 避开比你大的鱼\n"
        "4. 尽可能获得高分\n\n"
        "按ESC键暂停游戏"
    );
    helpText->setDefaultTextColor(Qt::white);
    QFont font("Arial", 24);
    helpText->setFont(font);
    addItem(helpText);
    helpText->setPos(200, 200);
    
    // 返回按钮（只用一个参数）
    backButton = new UIButton(":/UI/back_button.png");
    addItem(backButton);
    backButton->setPos(640 - backButton->boundingRect().width() / 2, 600);
    connect(backButton, &UIButton::clicked, this, &HelpScene::backToTitle);
}