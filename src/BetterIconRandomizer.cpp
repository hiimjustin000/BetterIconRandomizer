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
    unlocked.clear();

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

void BetterIconRandomizer::setupUnlockedIcons(int amount, IconType iconType) {
    auto gameManager = GameManager::sharedState();
    unlocked.push_back({});
    for (int i = 1; i <= amount; i++) {
        if (gameManager->isIconUnlocked(i, iconType)) unlocked.back().push_back(i);
    }
}

void BetterIconRandomizer::setupUnlockedColors(UnlockType unlockType) {
    auto gameManager = GameManager::sharedState();
    unlocked.push_back({});
    for (int i = 0; i <= 106; i++) {
        if (gameManager->isColorUnlocked(i, unlockType)) unlocked.back().push_back(i);
    }
}

int BetterIconRandomizer::randomize(UnlockType unlockType, bool randomizeGlow) {
    auto gameManager = GameManager::sharedState();
    auto num = 0;
    switch (unlockType) {
        case UnlockType::Cube:
            num = unlocked[0][randomNumber(0, unlocked[0].size() - 1)];
            gameManager->setPlayerFrame(num);
            break;
        case UnlockType::Col1:
            num = unlocked[1][randomNumber(0, unlocked[1].size() - 1)];
            gameManager->setPlayerColor(num);
            break;
        case UnlockType::Col2:
            num = unlocked[2][randomNumber(0, unlocked[2].size() - 1)];
            if (randomizeGlow) {
                gameManager->setPlayerColor3(num);
                gameManager->setPlayerGlow(randomNumber(0, 1));
            }
            else gameManager->setPlayerColor2(num);
            break;
        case UnlockType::Ship:
            num = unlocked[3][randomNumber(0, unlocked[3].size() - 1)];
            gameManager->setPlayerShip(num);
            break;
        case UnlockType::Ball:
            num = unlocked[4][randomNumber(0, unlocked[4].size() - 1)];
            gameManager->setPlayerBall(num);
            break;
        case UnlockType::Bird:
            num = unlocked[5][randomNumber(0, unlocked[5].size() - 1)];
            gameManager->setPlayerBird(num);
            break;
        case UnlockType::Dart:
            num = unlocked[6][randomNumber(0, unlocked[6].size() - 1)];
            gameManager->setPlayerDart(num);
            break;
        case UnlockType::Robot:
            num = unlocked[7][randomNumber(0, unlocked[7].size() - 1)];
            gameManager->setPlayerRobot(num);
            break;
        case UnlockType::Spider:
            num = unlocked[8][randomNumber(0, unlocked[8].size() - 1)];
            gameManager->setPlayerSpider(num);
            break;
        case UnlockType::Streak:
            num = unlocked[9][randomNumber(0, unlocked[9].size() - 1)];
            gameManager->setPlayerStreak(num);
            break;
        case UnlockType::Death:
            num = unlocked[10][randomNumber(0, unlocked[10].size() - 1)];
            gameManager->setPlayerDeathEffect(num);
            break;
        case UnlockType::Swing:
            num = unlocked[11][randomNumber(0, unlocked[11].size() - 1)];
            gameManager->setPlayerSwing(num);
            break;
        case UnlockType::Jetpack:
            num = unlocked[12][randomNumber(0, unlocked[12].size() - 1)];
            gameManager->setPlayerJetpack(num);
            break;
        case UnlockType::ShipFire:
            num = unlocked[13][randomNumber(0, unlocked[13].size() - 1)];
            gameManager->setPlayerShipStreak(num);
            break;
    }

    return num;
}
