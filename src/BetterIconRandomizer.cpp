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
    setupUnlockedIcons(IconType::Cube);
    setupUnlockedColors(UnlockType::Col1);
    setupUnlockedColors(UnlockType::Col2);
    setupUnlockedIcons(IconType::Ship);
    setupUnlockedIcons(IconType::Ball);
    setupUnlockedIcons(IconType::Ufo);
    setupUnlockedIcons(IconType::Wave);
    setupUnlockedIcons(IconType::Robot);
    setupUnlockedIcons(IconType::Spider);
    setupUnlockedIcons(IconType::Special);
    setupUnlockedIcons(IconType::DeathEffect);
    setupUnlockedIcons(IconType::Swing);
    setupUnlockedIcons(IconType::Jetpack);
    setupUnlockedIcons(IconType::ShipFire);
}

void BetterIconRandomizer::setupUnlockedIcons(IconType iconType) {
    auto gameManager = GameManager::sharedState();
    auto& vec = unlocked[gameManager->iconTypeToUnlockType(iconType)];
    vec.clear();
    auto amount = gameManager->countForType(iconType);
    for (int i = 1; i <= amount; i++) {
        if (gameManager->isIconUnlocked(i, iconType)) vec.push_back(i);
    }
}

void BetterIconRandomizer::setupUnlockedColors(UnlockType unlockType) {
    auto gameManager = GameManager::sharedState();
    auto& vec = unlocked[unlockType];
    vec.clear();
    for (int i = 0; i < 107; i++) {
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
