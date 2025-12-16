#ifndef HELPSCENE_H
#define HELPSCENE_H

#include "Scene.h"
#include "../UI/UIButton.h"

class HelpScene : public Scene {
    Q_OBJECT
public:
    explicit HelpScene(QObject *parent);
    
signals:
    void backToTitle();
    
private:
    QGraphicsPixmapItem *background;
    QGraphicsTextItem *helpText;
    UIButton *backButton;
};

#endif