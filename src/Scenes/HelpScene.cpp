#include "HelpScene.h"
#include <QFont>
#include <QTextDocument>
#include <QTextOption>

HelpScene::HelpScene(QObject *parent) : Scene(parent) {
    setSceneRect(0, 0, 1280, 720);
    
    // 背景
    QPixmap bgPixmap(":/Scenes/help_background.png");
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
    
    // 标题文字
    QGraphicsTextItem *titleText = new QGraphicsTextItem("游戏帮助");
    titleText->setDefaultTextColor(QColor(255, 255, 255));
    QFont titleFont("Arial", 36, QFont::Bold);
    titleText->setFont(titleFont);
    addItem(titleText);
    
    titleText->setPos(640 - titleText->boundingRect().width() / 2, 130);
    
    // 帮助文本
    helpText = new QGraphicsTextItem();
    helpText->setPlainText(
        "移动鼠标控制鱼的移动方向\n"
        "吃掉比你小的鱼来成长 避开比你大的鱼\n"
        "获得指定分数以完成关卡\n"
        "按 ESC 键暂停游戏"
    );
    helpText->setDefaultTextColor(QColor(255, 255, 255)); 
    QFont contentFont("Monospace", 20); 
    helpText->setFont(contentFont);
    
    qreal textWidth = 800; // 设置文本块的宽度
    helpText->setTextWidth(textWidth);
    
    QTextOption option = helpText->document()->defaultTextOption();
    option.setAlignment(Qt::AlignCenter); // 设置文字内容居中
    helpText->document()->setDefaultTextOption(option);
    
    addItem(helpText);

    helpText->setPos((1280 - textWidth) / 2, 200);
    
    // 返回按钮
    backButton = new UIButton(":/UI/back_button.png");
    backButton->setScale(0.03);
    addItem(backButton);
    
    backButton->setPos(640 - backButton->boundingRect().width() * 0.8 / 2 + 1100, 350);
    
    connect(backButton, &UIButton::clicked, this, &HelpScene::backToTitle);
}