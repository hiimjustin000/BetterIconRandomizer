#include <random>
#include "BetterIconRandomizer.hpp"

int BetterIconRandomizer::randomNumber(int start, int end) {
    std::random_device os_seed;
    const unsigned int seed = os_seed();

    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribute(start, end);

    return distribute(generator);
}

int BetterIconRandomizer::activeIconForType(IconType type, bool dual) {
    auto gameManager = GameManager::sharedState();
    auto separateDualIcons = Loader::get()->getLoadedMod("weebify.separate_dual_icons");
    switch (type) {
        case IconType::Cube:
            return dual ? separateDualIcons->getSavedValue("cube", 1) : gameManager->getPlayerFrame();
        case IconType::Ship:
            return dual ? separateDualIcons->getSavedValue("ship", 1) : gameManager->getPlayerShip();
        case IconType::Ball:
            return dual ? separateDualIcons->getSavedValue("roll", 1) : gameManager->getPlayerBall();
        case IconType::Ufo:
            return dual ? separateDualIcons->getSavedValue("bird", 1) : gameManager->getPlayerBird();
        case IconType::Wave:
            return dual ? separateDualIcons->getSavedValue("dart", 1) : gameManager->getPlayerDart();
        case IconType::Robot:
            return dual ? separateDualIcons->getSavedValue("robot", 1) : gameManager->getPlayerRobot();
        case IconType::Spider:
            return dual ? separateDualIcons->getSavedValue("spider", 1) : gameManager->getPlayerSpider();
        case IconType::Special:
            return dual ? separateDualIcons->getSavedValue("trail", 1) : gameManager->getPlayerStreak();
        case IconType::DeathEffect:
            return dual ? separateDualIcons->getSavedValue("death", 1) : gameManager->getPlayerDeathEffect();
        case IconType::Swing:
            return dual ? separateDualIcons->getSavedValue("swing", 1) : gameManager->getPlayerSwing();
        case IconType::Jetpack:
            return dual ? separateDualIcons->getSavedValue("jetpack", 1) : gameManager->getPlayerJetpack();
        case IconType::ShipFire:
            return dual ? separateDualIcons->getSavedValue("shiptrail", 1) : gameManager->getPlayerShipFire();
        default:
            return 0;
    }
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
    setupUnlockedIcons(IconType::Item);
    setupUnlockedIcons(IconType::Swing);
    setupUnlockedIcons(IconType::Jetpack);
    setupUnlockedIcons(IconType::ShipFire);
}

void BetterIconRandomizer::setupUnlockedIcons(IconType iconType) {
    auto gameManager = GameManager::sharedState();
    auto& vec = UNLOCKED[gameManager->iconTypeToUnlockType(iconType)];
    vec.clear();
    auto amount = iconType == IconType::Item ? 20 : gameManager->countForType(iconType);
    for (int i = iconType == IconType::Item ? 18 : 1; i <= amount; i++) {
        if (gameManager->isIconUnlocked(i, iconType)) vec.push_back(i);
    }
}

void BetterIconRandomizer::setupUnlockedColors(UnlockType unlockType) {
    auto gameManager = GameManager::sharedState();
    auto& vec = UNLOCKED[unlockType];
    vec.clear();
    for (int i = 0; i < 107; i++) {
        if (gameManager->isColorUnlocked(i, unlockType)) vec.push_back(i);
    }
}

int BetterIconRandomizer::randomize(UnlockType unlockType, bool dual, bool randomizeGlow) {
    auto& vec = UNLOCKED[unlockType];
    if (unlockType == UnlockType::GJItem) {
        auto gameStatsManager = GameStatsManager::sharedState();
        for (int i = 0; i < vec.size(); i++) {
            gameStatsManager->toggleEnableItem(unlockType, vec[i], randomNumber(0, 1));
        }
        return 0;
    }
    auto gameManager = GameManager::sharedState();
    auto separateDualIcons = Loader::get()->getLoadedMod("weebify.separate_dual_icons");
    auto num = vec[(size_t)randomNumber(0, vec.size() - 1)];
    switch (unlockType) {
        case UnlockType::Cube:
            if (dual) separateDualIcons->setSavedValue("cube", num);
            else gameManager->setPlayerFrame(num);
            return num;
        case UnlockType::Col1:
            if (dual) separateDualIcons->setSavedValue("color1", num);
            else gameManager->setPlayerColor(num);
            return num;
        case UnlockType::Col2:
            if (randomizeGlow) {
                if (dual) {
                    separateDualIcons->setSavedValue("colorglow", num);
                    separateDualIcons->setSavedValue<bool>("glow", randomNumber(0, 1));
                }
                else {
                    gameManager->setPlayerColor3(num);
                    gameManager->setPlayerGlow(randomNumber(0, 1));
                }
            }
            else if (dual) separateDualIcons->setSavedValue("color2", num);
            else gameManager->setPlayerColor2(num);
            return num;
        case UnlockType::Ship:
            if (dual) separateDualIcons->setSavedValue("ship", num);
            else gameManager->setPlayerShip(num);
            return num;
        case UnlockType::Ball:
            if (dual) separateDualIcons->setSavedValue("roll", num);
            else gameManager->setPlayerBall(num);
            return num;
        case UnlockType::Bird:
            if (dual) separateDualIcons->setSavedValue("bird", num);
            else gameManager->setPlayerBird(num);
            return num;
        case UnlockType::Dart:
            if (dual) separateDualIcons->setSavedValue("dart", num);
            else gameManager->setPlayerDart(num);
            return num;
        case UnlockType::Robot:
            if (dual) separateDualIcons->setSavedValue("robot", num);
            else gameManager->setPlayerRobot(num);
            return num;
        case UnlockType::Spider:
            if (dual) separateDualIcons->setSavedValue("spider", num);
            else gameManager->setPlayerSpider(num);
            return num;
        case UnlockType::Streak:
            if (dual) separateDualIcons->setSavedValue("trail", num);
            else gameManager->setPlayerStreak(num);
            return num;
        case UnlockType::Death:
            if (dual) separateDualIcons->setSavedValue("death", num);
            else gameManager->setPlayerDeathEffect(num);
            return num;
        case UnlockType::Swing:
            if (dual) separateDualIcons->setSavedValue("swing", num);
            else gameManager->setPlayerSwing(num);
            return num;
        case UnlockType::Jetpack:
            if (dual) separateDualIcons->setSavedValue("jetpack", num);
            else gameManager->setPlayerJetpack(num);
            return num;
        case UnlockType::ShipFire:
            if (dual) separateDualIcons->setSavedValue("shiptrail", num);
            else gameManager->setPlayerShipStreak(num);
            return num;
        default:
            return 0;
    }
}
