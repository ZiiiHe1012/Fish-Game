#include "MyGame.h"
#include "Scenes/BattleScene.h"
#include "Scenes/TitleScene.h"
#include "Scenes/HelpScene.h"
#include "Scenes/GameOverScene.h"
#include "Scenes/PauseScene.h"

MyGame::MyGame(QWidget *parent) : QMainWindow(parent) {
    view = new QGraphicsView(this);
    view->setFixedSize(1280, 720);  // 固定视图大小
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFrameShape(QFrame::NoFrame);
    view->setMouseTracking(true);
    
    pauseView = new QGraphicsView(this);
    pauseView->setFixedSize(1280, 720);
    pauseView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pauseView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pauseView->setFrameShape(QFrame::NoFrame);
    pauseView->hide();
    
    setCentralWidget(view);
    
    // 关键：设置窗口大小为固定值
    setFixedSize(1280, 720);
    
    // 初始化场景
    titleScene = nullptr;
    helpScene = nullptr;
    battleScene = nullptr;
    gameOverScene = nullptr;
    
    // 显示标题界面
    showTitleScene();
}

void MyGame::showTitleScene() {
    if (titleScene) {
        delete titleScene;
    }
    titleScene = new TitleScene(this);
    connect(titleScene, &TitleScene::startGame, this, &MyGame::showBattleScene);
    connect(titleScene, &TitleScene::showHelp, this, &MyGame::showHelpScene);
    
    view->setScene(titleScene);
    view->show();
    pauseView->hide();
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
    pauseView->hide();
}

void MyGame::showPauseMenu() {
    if (battleScene) {
        battleScene->stopLoop();
    }
    
    PauseScene *pauseScene = new PauseScene(this);
    connect(pauseScene, &PauseScene::resumeGame, this, [this, pauseScene]() {
        pauseView->hide();
        delete pauseScene;
        if (battleScene) {
            battleScene->startLoop();
        }
    });
    connect(pauseScene, &PauseScene::restartGame, this, [this, pauseScene]() {
        pauseView->hide();
        delete pauseScene;
        restartGame();
    });
    connect(pauseScene, &PauseScene::backToTitle, this, [this, pauseScene]() {
        pauseView->hide();
        delete pauseScene;
        showTitleScene();
    });
    
    pauseView->setScene(pauseScene);
    pauseView->setGeometry(view->geometry());
    pauseView->show();
    pauseView->raise();
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

void MyGame::restartGame() {
    showBattleScene();
}