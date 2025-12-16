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
    if (!battleScene) return;
    
    battleScene->stopLoop();
    
    // 在当前场景上添加暂停界面
    PauseScene *pauseScene = new PauseScene(this);
    
    // 保存原场景
    QGraphicsScene *originalScene = view->scene();
    
    // 恢复游戏
    connect(pauseScene, &PauseScene::resumeGame, this, [this, pauseScene, originalScene]() {
        view->setScene(originalScene);
        delete pauseScene;
        if (battleScene) {
            battleScene->startLoop();
        }
    });
    
    // 重新开始
    connect(pauseScene, &PauseScene::restartGame, this, [this, pauseScene]() {
        delete pauseScene;
        restartGame();
    });
    
    // 回到标题
    connect(pauseScene, &PauseScene::backToTitle, this, [this, pauseScene]() {
        delete pauseScene;
        showTitleScene();
    });
    
    // 切换到暂停场景
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

void MyGame::restartGame() {
    showBattleScene();
}