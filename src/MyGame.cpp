#include "MyGame.h"
#include "Scenes/BattleScene.h"
#include "Scenes/TitleScene.h"
#include "Scenes/HelpScene.h"
#include "Scenes/GameOverScene.h"
#include "Scenes/PauseScene.h"

MyGame::MyGame(QWidget *parent) : QMainWindow(parent) {
    view = new QGraphicsView(this);
    view->setFixedSize(1280, 720);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFrameShape(QFrame::NoFrame);
    view->setMouseTracking(true);
    
    // 删除 pauseView 相关代码
    
    setCentralWidget(view);
    setFixedSize(1280, 720);
    
    // 初始化场景
    titleScene = nullptr;
    helpScene = nullptr;
    levelSelectScene = nullptr;
    levelIntroScene = nullptr;
    battleScene = nullptr;
    gameOverScene = nullptr;
    
    // 显示标题界面
    showTitleScene();
}

void MyGame::showTitleScene() {
    // 清理战斗场景
    if (battleScene) {
        if (view->scene() == battleScene) {
            view->setScene(nullptr);
        }
        delete battleScene;
        battleScene = nullptr;
    }
    
    if (titleScene) {
        delete titleScene;
    }
    titleScene = new TitleScene(this);
    connect(titleScene, &TitleScene::startGame, this, &MyGame::showBattleScene);
    connect(titleScene, &TitleScene::showHelp, this, &MyGame::showHelpScene);
    
    view->setScene(titleScene);
    view->show();
}

void MyGame::showHelpScene() {
    if (helpScene) {
        delete helpScene;
    }
    helpScene = new HelpScene(this);
    connect(helpScene, &HelpScene::backToTitle, this, &MyGame::showTitleScene);
    
    view->setScene(helpScene);
}

void MyGame::showBattleScene() {
    if (battleScene) {
        delete battleScene;
    }
    battleScene = new BattleScene(this);
    connect(battleScene, &BattleScene::pauseGame, this, &MyGame::showPauseMenu);
    connect(battleScene, &BattleScene::gameOver, this, &MyGame::showGameOverScene);
    
    view->setScene(battleScene);
    battleScene->startLoop();
}

void MyGame::showPauseMenu() {
    if (battleScene) {
        battleScene->stopLoop();
    }
    
    PauseScene *pauseScene = new PauseScene(this);
    connect(pauseScene, &PauseScene::resumeGame, this, &MyGame::resumeFromPause);
    connect(pauseScene, &PauseScene::restartGame, this, &MyGame::restartGame);
    connect(pauseScene, &PauseScene::backToTitle, this, &MyGame::showTitleScene);
    
    view->setScene(pauseScene);
}

void MyGame::showGameOverScene(bool victory) {
    if (battleScene) {
        battleScene->stopLoop();
    }
    
    int score = battleScene ? battleScene->getScore() : 0;
    
    if (gameOverScene) {
        delete gameOverScene;
    }
    gameOverScene = new GameOverScene(this, victory, score);
    connect(gameOverScene, &GameOverScene::restartGame, this, &MyGame::restartGame);
    connect(gameOverScene, &GameOverScene::backToTitle, this, &MyGame::showTitleScene);
    
    view->setScene(gameOverScene);
}

void MyGame::resumeFromPause() {
    if (battleScene) {
        view->setScene(battleScene);
        battleScene->startLoop();
    }
}

void MyGame::restartGame() {
    showBattleScene();
}

void MyGame::showLevelSelectScene() {
    if (levelSelectScene) {
        delete levelSelectScene;
    }
    levelSelectScene = new LevelSelectScene(this);
    connect(levelSelectScene, &LevelSelectScene::levelSelected, this, &MyGame::showLevelIntroScene);
    connect(levelSelectScene, &LevelSelectScene::backToTitle, this, &MyGame::showTitleScene);
    
    view->setScene(levelSelectScene);
}

void MyGame::showLevelIntroScene(int level) {
    if (levelIntroScene) {
        delete levelIntroScene;
    }
    levelIntroScene = new LevelIntroScene(this, level);
    connect(levelIntroScene, &LevelIntroScene::startLevel, this, &MyGame::showBattleScene);
    connect(levelIntroScene, &LevelIntroScene::backToLevelSelect, this, &MyGame::showLevelSelectScene);
    
    view->setScene(levelIntroScene);
}