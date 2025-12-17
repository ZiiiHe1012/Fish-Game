#ifndef LEVELSELECTSCENE_H
#define LEVELSELECTSCENE_H

#include "Scene.h"
#include "../UI/UIButton.h"

class LevelSelectScene : public Scene {
    Q_OBJECT
public:
    explicit LevelSelectScene(QObject *parent);
    
signals:
    void levelSelected(int level);
    void backToTitle();
    
private:
    QGraphicsPixmapItem *background;
    QGraphicsTextItem *titleText;
    UIButton *level1Button;
    UIButton *level2Button;
    UIButton *level3Button;
    UIButton *backButton;
};

#endif