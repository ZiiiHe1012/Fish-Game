#include "GameProgress.h"

GameProgress* GameProgress::m_instance = nullptr;

GameProgress::GameProgress(QObject *parent) : QObject(parent) {
}

GameProgress* GameProgress::instance() {
    if (!m_instance) {
        m_instance = new GameProgress();
    }
    return m_instance;
}

void GameProgress::completeLevel(int level) {
    completedLevels.insert(level);
}

bool GameProgress::isLevelCompleted(int level) const {
    return completedLevels.contains(level);
}

bool GameProgress::hasSharkFin() const {
    return isLevelCompleted(1);
}

bool GameProgress::hasPendant() const {
    return isLevelCompleted(2);
}

qreal GameProgress::getSpeedMultiplier() const {
    if (hasSharkFin()) {
        return 1.25;
    }
    return 1.0;
}

int GameProgress::getMaxHealth() const {
    if (hasPendant()) {
        return 150;
    }
    return 100;
}

void GameProgress::reset() {
    completedLevels.clear();
}