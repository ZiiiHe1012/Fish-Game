#ifndef PAUSESCENE_H
#define PAUSESCENE_H

#include <QGraphicsScene>
#include "../UI/UIButton.h"

class PauseScene : public QGraphicsScene {
    Q_OBJECT
public:
    explicit PauseScene(QObject *parent);
    
signals:
    void resumeGame();
    void restartGame();
    void backToTitle();
    
private:
    QGraphicsRectItem *overlay;
    QGraphicsTextItem *pauseText;
    UIButton *resumeButton;
    UIButton *restartButton;
    UIButton *titleButton;
};

#endif