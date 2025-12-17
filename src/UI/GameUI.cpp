#include "GameUI.h"
#include <QBrush>
#include <QPen>
#include <QFont>
#include <QGraphicsScene>

GameUI::GameUI(QGraphicsScene *scene, QObject *parent) 
    : QObject(parent), scene(scene) {
    
    // === 进度条（左上角）===
    progressBarBg = new QGraphicsRectItem(0, 0, 250, 30);
    progressBarBg->setBrush(QBrush(QColor(50, 50, 50, 200)));
    progressBarBg->setPen(QPen(Qt::white, 2));
    progressBarBg->setZValue(10000);
    scene->addItem(progressBarBg);
    
    progressBarFill = new QGraphicsRectItem(0, 0, 0, 30);
    progressBarFill->setBrush(QBrush(QColor(0, 255, 0)));
    progressBarFill->setPen(Qt::NoPen);
    progressBarFill->setZValue(10001);
    scene->addItem(progressBarFill);
    
    progressText = new QGraphicsTextItem("进度: 0/20");
    progressText->setDefaultTextColor(Qt::white);
    QFont font("Arial", 12, QFont::Bold);
    progressText->setFont(font);
    progressText->setZValue(10002);
    scene->addItem(progressText);
    
    // === 血量条（右上角）===
    healthBarBg = new QGraphicsRectItem(0, 0, 250, 30);
    healthBarBg->setBrush(QBrush(QColor(50, 50, 50, 200)));
    healthBarBg->setPen(QPen(Qt::white, 2));
    healthBarBg->setZValue(10000);
    scene->addItem(healthBarBg);
    
    healthBarFill = new QGraphicsRectItem(0, 0, 246, 30);
    healthBarFill->setBrush(QBrush(QColor(255, 0, 0)));
    healthBarFill->setPen(Qt::NoPen);
    healthBarFill->setZValue(10001);
    scene->addItem(healthBarFill);
    
    healthText = new QGraphicsTextItem("血量: 100");
    healthText->setDefaultTextColor(Qt::white);
    healthText->setFont(font);
    healthText->setZValue(10002);
    scene->addItem(healthText);

    timerText = new QGraphicsTextItem("时间: 0s");
    timerText->setDefaultTextColor(Qt::white);
    QFont timerFont("Arial", 20, QFont::Bold);
    timerText->setFont(timerFont);
    timerText->setZValue(10002);
    scene->addItem(timerText);
    timerText->setVisible(false);
}

void GameUI::updateProgress(int current, int total) {
    qreal fillWidth = (246.0 * current) / total;
    QRectF bgRect = progressBarBg->rect();
    progressBarFill->setRect(2, 2, fillWidth, 26);
    
    progressText->setPlainText(QString("进度: %1/%2").arg(current).arg(total));
}

void GameUI::updateHealth(int current, int max) {
    qreal fillWidth = (246.0 * current) / max;
    healthBarFill->setRect(2, 2, fillWidth, 26);
    
    if (current > max * 0.6) {
        healthBarFill->setBrush(QBrush(QColor(0, 255, 0)));
    } else if (current > max * 0.3) {
        healthBarFill->setBrush(QBrush(QColor(255, 255, 0)));
    } else {
        healthBarFill->setBrush(QBrush(QColor(255, 0, 0)));
    }
    
    healthText->setPlainText(QString("血量: %1").arg(current));
}

void GameUI::updatePosition(const QPointF &viewTopLeft) {
    // 进度条固定在视角左上角
    progressBarBg->setPos(viewTopLeft.x() + 20, viewTopLeft.y() + 20);
    progressBarFill->setPos(viewTopLeft.x() + 20, viewTopLeft.y() + 20);
    progressText->setPos(viewTopLeft.x() + 100, viewTopLeft.y() + 23);
    
    // 血量条固定在视角右上角
    healthBarBg->setPos(viewTopLeft.x() + 1010, viewTopLeft.y() + 20);
    healthBarFill->setPos(viewTopLeft.x() + 1010, viewTopLeft.y() + 20);
    healthText->setPos(viewTopLeft.x() + 1090, viewTopLeft.y() + 23);

    timerText->setPos(viewTopLeft.x() + 640 - timerText->boundingRect().width() / 2, 
                      viewTopLeft.y() + 20);
}

void GameUI::updateTimer(int seconds) {
    timerText->setPlainText(QString("时间: %1s").arg(seconds));
}

void GameUI::showTimer(bool show) {
    timerText->setVisible(show);
}