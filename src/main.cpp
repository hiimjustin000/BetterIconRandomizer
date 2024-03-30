#include <random>
#include <Geode/Geode.hpp>
#include <Geode/modify/CharacterColorPage.hpp>
#include <Geode/modify/GJGarageLayer.hpp>

using namespace geode::prelude;

std::vector<std::vector<int>> unlocked = {};

int randomNumber(int start, int end) {
    std::random_device os_seed;
    const unsigned int seed = os_seed();

    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribute(start, end);

    return distribute(generator);
}

class $modify(BIRGarageLayer, GJGarageLayer) {
    bool init() override {
        if (!GJGarageLayer::init()) return false;
        auto shardsMenu = getChildByID("shards-menu");
        auto randomizeBtn = CCMenuItemSpriteExtra::create(CCSprite::create("BIR_randomBtn_001.png"_spr), this, menu_selector(BIRGarageLayer::onRandomize));
        randomizeBtn->setID("randomize-button"_spr);
        auto randomizeAllBtn = CCMenuItemSpriteExtra::create(CCSprite::create("BIR_randomBtn_002.png"_spr), this, menu_selector(BIRGarageLayer::onRandomizeAll));
        randomizeAllBtn->setID("randomize-all-button"_spr);

        shardsMenu->addChild(randomizeBtn);
        shardsMenu->addChild(randomizeAllBtn);
        shardsMenu->updateLayout();

        auto gameManager = GameManager::sharedState();
        unlocked.clear();
        unlocked.push_back({});
        for (int i = 1; i <= 484; i++) {
            if (gameManager->isIconUnlocked(i, IconType::Cube)) unlocked.back().push_back(i);
        }
        unlocked.push_back({});
        for (int i = 0; i <= 106; i++) {
            if (gameManager->isColorUnlocked(i, UnlockType::Col1)) unlocked.back().push_back(i);
        }
        unlocked.push_back({});
        for (int i = 0; i <= 106; i++) {
            if (gameManager->isColorUnlocked(i, UnlockType::Col2)) unlocked.back().push_back(i);
        }
        unlocked.push_back({});
        for (int i = 1; i <= 169; i++) {
            if (gameManager->isIconUnlocked(i, IconType::Ship)) unlocked.back().push_back(i);
        }
        unlocked.push_back({});
        for (int i = 1; i <= 118; i++) {
            if (gameManager->isIconUnlocked(i, IconType::Ball)) unlocked.back().push_back(i);
        }
        unlocked.push_back({});
        for (int i = 1; i <= 149; i++) {
            if (gameManager->isIconUnlocked(i, IconType::Ufo)) unlocked.back().push_back(i);
        }
        unlocked.push_back({});
        for (int i = 1; i <= 96; i++) {
            if (gameManager->isIconUnlocked(i, IconType::Wave)) unlocked.back().push_back(i);
        }
        unlocked.push_back({});
        for (int i = 1; i <= 68; i++) {
            if (gameManager->isIconUnlocked(i, IconType::Robot)) unlocked.back().push_back(i);
        }
        unlocked.push_back({});
        for (int i = 1; i <= 69; i++) {
            if (gameManager->isIconUnlocked(i, IconType::Spider)) unlocked.back().push_back(i);
        }
        unlocked.push_back({});
        for (int i = 1; i <= 7; i++) {
            if (gameManager->isIconUnlocked(i, IconType::Special)) unlocked.back().push_back(i);
        }
        unlocked.push_back({});
        for (int i = 1; i <= 20; i++) {
            if (gameManager->isIconUnlocked(i, IconType::DeathEffect)) unlocked.back().push_back(i);
        }
        unlocked.push_back({});
        for (int i = 1; i <= 43; i++) {
            if (gameManager->isIconUnlocked(i, IconType::Swing)) unlocked.back().push_back(i);
        }
        unlocked.push_back({});
        for (int i = 1; i <= 5; i++) {
            if (gameManager->isIconUnlocked(i, IconType::Jetpack)) unlocked.back().push_back(i);
        }
        unlocked.push_back({});
        for (int i = 1; i <= 6; i++) {
            if (gameManager->isIconUnlocked(i, (IconType)101)) unlocked.back().push_back(i);
        }
        return true;
    }

    void randomize(IconType iconType, bool update) {
        auto gameManager = GameManager::sharedState();
        auto num = 0;
        switch (iconType) {
            case IconType::Cube:
                num = unlocked[0][randomNumber(0, unlocked[0].size() - 1)];
                gameManager->setPlayerFrame(num);
                m_iconPages[IconType::Cube] = (num - 1) / 36;
                if (update) {
                    m_playerObject->updatePlayerFrame(num, IconType::Cube);
                    m_selectedIconType = IconType::Cube;
                    m_iconID = num;
                }
                break;
            case IconType::Ship:
                num = unlocked[3][randomNumber(0, unlocked[3].size() - 1)];
                gameManager->setPlayerShip(num);
                m_iconPages[IconType::Ship] = (num - 1) / 36;
                if (update) {
                    m_playerObject->updatePlayerFrame(num, IconType::Ship);
                    m_selectedIconType = IconType::Ship;
                    m_iconID = num;
                }
                break;
            case IconType::Ball:
                num = unlocked[4][randomNumber(0, unlocked[4].size() - 1)];
                gameManager->setPlayerBall(num);
                m_iconPages[IconType::Ball] = (num - 1) / 36;
                if (update) {
                    m_playerObject->updatePlayerFrame(num, IconType::Ball);
                    m_selectedIconType = IconType::Ball;
                    m_iconID = num;
                }
                break;
            case IconType::Ufo:
                num = unlocked[5][randomNumber(0, unlocked[5].size() - 1)];
                gameManager->setPlayerBird(num);
                m_iconPages[IconType::Ufo] = (num - 1) / 36;
                if (update) {
                    m_playerObject->updatePlayerFrame(num, IconType::Ufo);
                    m_selectedIconType = IconType::Ufo;
                    m_iconID = num;
                }
                break;
            case IconType::Wave:
                num = unlocked[6][randomNumber(0, unlocked[6].size() - 1)];
                gameManager->setPlayerDart(num);
                m_iconPages[IconType::Wave] = (num - 1) / 36;
                if (update) {
                    m_playerObject->updatePlayerFrame(num, IconType::Wave);
                    m_selectedIconType = IconType::Wave;
                    m_iconID = num;
                }
                break;
            case IconType::Robot:
                num = unlocked[7][randomNumber(0, unlocked[7].size() - 1)];
                gameManager->setPlayerRobot(num);
                m_iconPages[IconType::Robot] = (num - 1) / 36;
                if (update) {
                    m_playerObject->updatePlayerFrame(num, IconType::Robot);
                    m_selectedIconType = IconType::Robot;
                    m_iconID = num;
                }
                break;
            case IconType::Spider:
                num = unlocked[8][randomNumber(0, unlocked[8].size() - 1)];
                gameManager->setPlayerSpider(num);
                m_iconPages[IconType::Spider] = (num - 1) / 36;
                if (update) {
                    m_playerObject->updatePlayerFrame(num, IconType::Spider);
                    m_selectedIconType = IconType::Spider;
                    m_iconID = num;
                }
                break;
            case IconType::Swing:
                num = unlocked[11][randomNumber(0, unlocked[11].size() - 1)];
                gameManager->setPlayerSwing(num);
                m_iconPages[IconType::Swing] = (num - 1) / 36;
                if (update) {
                    m_playerObject->updatePlayerFrame(num, IconType::Swing);
                    m_selectedIconType = IconType::Swing;
                    m_iconID = num;
                }
                break;
            case IconType::Jetpack:
                num = unlocked[12][randomNumber(0, unlocked[12].size() - 1)];
                gameManager->setPlayerJetpack(num);
                m_iconPages[IconType::Jetpack] = 0;
                if (update) {
                    m_playerObject->updatePlayerFrame(num, IconType::Jetpack);
                    m_selectedIconType = IconType::Jetpack;
                    m_iconID = num;
                }
                break;
            case IconType::DeathEffect:
                num = unlocked[10][randomNumber(0, unlocked[10].size() - 1)];
                gameManager->setPlayerDeathEffect(num);
                m_iconPages[IconType::DeathEffect] = 0;
                if (update) {
                    m_selectedIconType = IconType::DeathEffect;
                    m_iconID = num;
                }
                break;
            case IconType::Special:
                num = unlocked[9][randomNumber(0, unlocked[9].size() - 1)];
                gameManager->setPlayerStreak(num);
                m_iconPages[IconType::Special] = 0;
                if (update) {
                    m_selectedIconType = IconType::Special;
                    m_iconID = num;
                }
                gameManager->setPlayerShipStreak(unlocked[13][randomNumber(0, unlocked[13].size() - 1)]);
                m_iconPages[(IconType)101] = 0;
                break;
        }
    }

    void onRandomize(CCObject* sender) {
        randomize(m_iconType, true);
        setupPage(-1, m_iconType);
    }

    void onRandomizeAll(CCObject* sender) {
        createQuickPopup(
            "Randomize All Icons",
            "Do you want to randomize all icons and colors? This action cannot be undone.",
            "No",
            "Yes",
            [this](FLAlertLayer* alert, bool btn2) {
                if (btn2) {
                    auto gameManager = GameManager::sharedState();
                    randomize(IconType::Cube, false);
                    randomize(IconType::Ship, false);
                    randomize(IconType::Ball, false);
                    randomize(IconType::Ufo, false);
                    randomize(IconType::Wave, false);
                    randomize(IconType::Robot, false);
                    randomize(IconType::Spider, false);
                    randomize(IconType::Swing, false);
                    randomize(IconType::Jetpack, false);
                    randomize(IconType::DeathEffect, false);
                    randomize(IconType::Special, false);
                    gameManager->setPlayerColor(unlocked[1][randomNumber(0, unlocked[1].size() - 1)]);
                    gameManager->setPlayerColor2(unlocked[2][randomNumber(0, unlocked[2].size() - 1)]);
                    gameManager->setPlayerColor3(unlocked[2][randomNumber(0, unlocked[2].size() - 1)]);
                    gameManager->setPlayerGlow(randomNumber(0, 1));
                    auto randomType = (IconType)randomNumber(0, 8);
                    auto playerFrame = 0;
                    switch (randomType) {
                        case IconType::Cube:
                            playerFrame = gameManager->getPlayerFrame();
                            break;
                        case IconType::Ship:
                            playerFrame = gameManager->getPlayerShip();
                            break;
                        case IconType::Ball:
                            playerFrame = gameManager->getPlayerBall();
                            break;
                        case IconType::Ufo:
                            playerFrame = gameManager->getPlayerBird();
                            break;
                        case IconType::Wave:
                            playerFrame = gameManager->getPlayerDart();
                            break;
                        case IconType::Robot:
                            playerFrame = gameManager->getPlayerRobot();
                            break;
                        case IconType::Spider:
                            playerFrame = gameManager->getPlayerSpider();
                            break;
                        case IconType::Swing:
                            playerFrame = gameManager->getPlayerSwing();
                            break;
                        case IconType::Jetpack:
                            playerFrame = gameManager->getPlayerJetpack();
                            break;
                    }
                    m_playerObject->setColor(gameManager->colorForIdx(gameManager->getPlayerColor()));
                    m_playerObject->setSecondColor(gameManager->colorForIdx(gameManager->getPlayerColor2()));
                    if (gameManager->getPlayerGlow()) m_playerObject->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                    else m_playerObject->disableGlowOutline();
                    m_playerObject->updatePlayerFrame(playerFrame, randomType);
                    m_selectedIconType = randomType;
                    m_iconID = playerFrame;
                    selectTab(randomType);
                }
            }
        );
    }
};

class $modify(BIRCharacterColorPage, CharacterColorPage) {
    bool init() override {
        if (!CharacterColorPage::init()) return false;
        auto glowToggler = static_cast<CCMenuItemToggler*>(m_buttonMenu->getChildByID("glow-toggler"));
        auto randomizeSpr = CCSprite::create("BIR_randomBtn_001.png"_spr);
        randomizeSpr->setScale(0.5f);
        auto randomizeBtn = CCMenuItemSpriteExtra::create(randomizeSpr, this, menu_selector(BIRCharacterColorPage::onRandomize));
        randomizeBtn->setID("randomize-button"_spr);
        randomizeBtn->setPosition(glowToggler->getPositionX() + 80.0f, glowToggler->getPositionY());
        m_buttonMenu->addChild(randomizeBtn);
        return true;
    }

    void onRandomize(CCObject* sender) {
        auto gameManager = GameManager::sharedState();
        auto num = 0;
        switch (m_colorMode) {
            case 0:
                num = unlocked[1][randomNumber(0, unlocked[1].size() - 1)];
                gameManager->setPlayerColor(num);
                break;
            case 1:
                num = unlocked[2][randomNumber(0, unlocked[2].size() - 1)];
                gameManager->setPlayerColor2(num);
                break;
            case 2:
                num = unlocked[2][randomNumber(0, unlocked[2].size() - 1)];
                gameManager->setPlayerColor3(num);
                gameManager->setPlayerGlow(true);
                m_glowToggler->toggle(false);
                break;
        }
        static_cast<CCSprite*>(m_cursors->objectAtIndex(m_colorMode))->setPosition(
            m_mainLayer->convertToNodeSpace(m_buttonMenu->convertToWorldSpace(static_cast<CCSprite*>(m_colorButtons->objectForKey(num))->getParent()->getPosition()))
        );
        updateIconColors();
    }
};
