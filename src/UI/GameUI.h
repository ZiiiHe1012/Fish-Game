#ifndef GAMEUI_H
#define GAMEUI_H

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QObject>
#include <QPointF>

class GameUI : public QObject {
    Q_OBJECT
public:
    explicit GameUI(QGraphicsScene *scene, QObject *parent = nullptr);
    
    void updateProgress(int current, int total);
    void updateHealth(int current, int max);
    void updatePosition(const QPointF &viewTopLeft);
    void updateTimer(int seconds);
    void showTimer(bool show);
    
private:
    QGraphicsRectItem *progressBarBg;
    QGraphicsRectItem *progressBarFill;
    QGraphicsTextItem *progressText;
    
    QGraphicsRectItem *healthBarBg;
    QGraphicsRectItem *healthBarFill;
    QGraphicsTextItem *healthText;
    QGraphicsTextItem *timerText;

    QGraphicsScene *scene;
};

#endif