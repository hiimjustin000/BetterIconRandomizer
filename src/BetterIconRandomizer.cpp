#include <random>
#include "BetterIconRandomizer.hpp"

int BetterIconRandomizer::randomNumber(int start, int end) {
    std::random_device os_seed;
    const unsigned int seed = os_seed();

    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribute(start, end);

    return distribute(generator);
}

void BetterIconRandomizer::setupUnlocked() {
    for (auto& [_, vec] : unlocked) vec.clear();

    setupUnlockedIcons(484, IconType::Cube);
    setupUnlockedColors(UnlockType::Col1);
    setupUnlockedColors(UnlockType::Col2);
    setupUnlockedIcons(169, IconType::Ship);
    setupUnlockedIcons(118, IconType::Ball);
    setupUnlockedIcons(149, IconType::Ufo);
    setupUnlockedIcons(96, IconType::Wave);
    setupUnlockedIcons(68, IconType::Robot);
    setupUnlockedIcons(69, IconType::Spider);
    setupUnlockedIcons(7, IconType::Special);
    setupUnlockedIcons(20, IconType::DeathEffect);
    setupUnlockedIcons(43, IconType::Swing);
    setupUnlockedIcons(5, IconType::Jetpack);
    setupUnlockedIcons(6, IconType::ShipFire);
}

UnlockType BetterIconRandomizer::iconTypeToUnlockType(IconType iconType) {
    switch (iconType) {
        case IconType::Cube: return UnlockType::Cube;
        case IconType::Ship: return UnlockType::Ship;
        case IconType::Ball: return UnlockType::Ball;
        case IconType::Ufo: return UnlockType::Bird;
        case IconType::Wave: return UnlockType::Dart;
        case IconType::Robot: return UnlockType::Robot;
        case IconType::Spider: return UnlockType::Spider;
        case IconType::Special: return UnlockType::Streak;
        case IconType::DeathEffect: return UnlockType::Death;
        case IconType::Swing: return UnlockType::Swing;
        case IconType::Jetpack: return UnlockType::Jetpack;
        case IconType::ShipFire: return UnlockType::ShipFire;
    }
}

void BetterIconRandomizer::setupUnlockedIcons(int amount, IconType iconType) {
    auto gameManager = GameManager::sharedState();
    auto& vec = unlocked[iconTypeToUnlockType(iconType)];
    for (int i = 1; i <= amount; i++) {
        if (gameManager->isIconUnlocked(i, iconType)) vec.push_back(i);
    }
}

void BetterIconRandomizer::setupUnlockedColors(UnlockType unlockType) {
    auto gameManager = GameManager::sharedState();
    auto& vec = unlocked[unlockType];
    for (int i = 0; i <= 106; i++) {
        if (gameManager->isColorUnlocked(i, unlockType)) vec.push_back(i);
    }
}

int BetterIconRandomizer::randomize(UnlockType unlockType, bool randomizeGlow) {
    auto gameManager = GameManager::sharedState();
    auto& vec = unlocked[unlockType];
    auto num = vec[randomNumber(0, vec.size() - 1)];
    switch (unlockType) {
        case UnlockType::Cube:
            gameManager->setPlayerFrame(num);
            return num;
        case UnlockType::Col1:
            gameManager->setPlayerColor(num);
            return num;
        case UnlockType::Col2:
            if (randomizeGlow) {
                gameManager->setPlayerColor3(num);
                gameManager->setPlayerGlow(randomNumber(0, 1));
            }
            else gameManager->setPlayerColor2(num);
            return num;
        case UnlockType::Ship:
            gameManager->setPlayerShip(num);
            return num;
        case UnlockType::Ball:
            gameManager->setPlayerBall(num);
            return num;
        case UnlockType::Bird:
            gameManager->setPlayerBird(num);
            return num;
        case UnlockType::Dart:
            gameManager->setPlayerDart(num);
            return num;
        case UnlockType::Robot:
            gameManager->setPlayerRobot(num);
            return num;
        case UnlockType::Spider:
            gameManager->setPlayerSpider(num);
            return num;
        case UnlockType::Streak:
            gameManager->setPlayerStreak(num);
            return num;
        case UnlockType::Death:
            gameManager->setPlayerDeathEffect(num);
            return num;
        case UnlockType::Swing:
            gameManager->setPlayerSwing(num);
            return num;
        case UnlockType::Jetpack:
            gameManager->setPlayerJetpack(num);
            return num;
        case UnlockType::ShipFire:
            gameManager->setPlayerShipStreak(num);
            return num;
        default:
            return -1;
    }
}
