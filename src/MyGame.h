#ifndef MYGAME_H
#define MYGAME_H

#include <QGraphicsView>
#include <QMainWindow>
#include <QStackedWidget>
#include "Scenes/Scene.h"
#include "Scenes/TitleScene.h"
#include "Scenes/HelpScene.h"
#include "Scenes/BattleScene.h"
#include "Scenes/GameOverScene.h"
#include "Scenes/LevelSelectScene.h"
#include "Scenes/LevelIntroScene.h"

class MyGame : public QMainWindow {
Q_OBJECT

public:
    explicit MyGame(QWidget *parent = nullptr);

private slots:
    void showTitleScene();
    void showHelpScene();
    void showBattleScene();
    void showPauseMenu();
    void showGameOverScene(bool victory);
    void restartGame();
    void resumeFromPause();
    void showLevelSelectScene();
    void showLevelIntroScene(int level);

private:
    QGraphicsView *view;
    
    TitleScene *titleScene;
    HelpScene *helpScene;
    BattleScene *battleScene;
    GameOverScene *gameOverScene;

    LevelSelectScene *levelSelectScene;
    LevelIntroScene *levelIntroScene;

};

#endif