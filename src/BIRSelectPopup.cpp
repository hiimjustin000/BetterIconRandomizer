#include <random>
#include "BIRSelectPopup.hpp"

int BIRSelectPopup::randomNumber(int start, int end) {
    std::random_device os_seed;
    const unsigned int seed = os_seed();

    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribute(start, end);

    return distribute(generator);
}

void BIRSelectPopup::setupUnlocked() {
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
        if (gameManager->isIconUnlocked(i, IconType::ShipFire)) unlocked.back().push_back(i);
    }
}

BIRSelectPopup* BIRSelectPopup::create() {
    auto ret = new BIRSelectPopup();

    if (ret && ret->init(350.0f, 150.0f, "")) {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool BIRSelectPopup::setup(std::string const&) {
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    setTitle("Select Modes to Randomize");

    // Bear with me Copilot, I'm doing this 11 times
    auto iconSpriteOff = CCSprite::createWithSpriteFrameName("gj_iconBtn_off_001.png");
    iconSpriteOff->setScale(0.75f);
    auto iconSpriteOn = CCSprite::createWithSpriteFrameName("gj_iconBtn_on_001.png");
    iconSpriteOn->setScale(0.75f);
    m_iconToggler = CCMenuItemToggler::create(iconSpriteOff, iconSpriteOn, this, menu_selector(BIRSelectPopup::onToggle));
    m_iconToggler->setPosition(-150.0f, 25.0f);
    m_buttonMenu->addChild(m_iconToggler);

    auto shipSpriteOff = CCSprite::createWithSpriteFrameName("gj_shipBtn_off_001.png");
    shipSpriteOff->setScale(0.75f);
    auto shipSpriteOn = CCSprite::createWithSpriteFrameName("gj_shipBtn_on_001.png");
    shipSpriteOn->setScale(0.75f);
    m_shipToggler = CCMenuItemToggler::create(shipSpriteOff, shipSpriteOn, this, menu_selector(BIRSelectPopup::onToggle));
    m_shipToggler->setPosition(-120.0f, 25.0f);
    m_buttonMenu->addChild(m_shipToggler);

    auto ballSpriteOff = CCSprite::createWithSpriteFrameName("gj_ballBtn_off_001.png");
    ballSpriteOff->setScale(0.75f);
    auto ballSpriteOn = CCSprite::createWithSpriteFrameName("gj_ballBtn_on_001.png");
    ballSpriteOn->setScale(0.75f);
    m_ballToggler = CCMenuItemToggler::create(ballSpriteOff, ballSpriteOn, this, menu_selector(BIRSelectPopup::onToggle));
    m_ballToggler->setPosition(-90.0f, 25.0f);
    m_buttonMenu->addChild(m_ballToggler);

    auto birdSpriteOff = CCSprite::createWithSpriteFrameName("gj_birdBtn_off_001.png");
    birdSpriteOff->setScale(0.75f);
    auto birdSpriteOn = CCSprite::createWithSpriteFrameName("gj_birdBtn_on_001.png");
    birdSpriteOn->setScale(0.75f);
    m_birdToggler = CCMenuItemToggler::create(birdSpriteOff, birdSpriteOn, this, menu_selector(BIRSelectPopup::onToggle));
    m_birdToggler->setPosition(-60.0f, 25.0f);
    m_buttonMenu->addChild(m_birdToggler);

    auto dartSpriteOff = CCSprite::createWithSpriteFrameName("gj_dartBtn_off_001.png");
    dartSpriteOff->setScale(0.75f);
    auto dartSpriteOn = CCSprite::createWithSpriteFrameName("gj_dartBtn_on_001.png");
    dartSpriteOn->setScale(0.75f);
    m_dartToggler = CCMenuItemToggler::create(dartSpriteOff, dartSpriteOn, this, menu_selector(BIRSelectPopup::onToggle));
    m_dartToggler->setPosition(-30.0f, 25.0f);
    m_buttonMenu->addChild(m_dartToggler);

    auto robotSpriteOff = CCSprite::createWithSpriteFrameName("gj_robotBtn_off_001.png");
    robotSpriteOff->setScale(0.75f);
    auto robotSpriteOn = CCSprite::createWithSpriteFrameName("gj_robotBtn_on_001.png");
    robotSpriteOn->setScale(0.75f);
    m_robotToggler = CCMenuItemToggler::create(robotSpriteOff, robotSpriteOn, this, menu_selector(BIRSelectPopup::onToggle));
    m_robotToggler->setPosition(0.0f, 25.0f);
    m_buttonMenu->addChild(m_robotToggler);

    auto spiderSpriteOff = CCSprite::createWithSpriteFrameName("gj_spiderBtn_off_001.png");
    spiderSpriteOff->setScale(0.75f);
    auto spiderSpriteOn = CCSprite::createWithSpriteFrameName("gj_spiderBtn_on_001.png");
    spiderSpriteOn->setScale(0.75f);
    m_spiderToggler = CCMenuItemToggler::create(spiderSpriteOff, spiderSpriteOn, this, menu_selector(BIRSelectPopup::onToggle));
    m_spiderToggler->setPosition(30.0f, 25.0f);
    m_buttonMenu->addChild(m_spiderToggler);

    auto swingSpriteOff = CCSprite::createWithSpriteFrameName("gj_swingBtn_off_001.png");
    swingSpriteOff->setScale(0.75f);
    auto swingSpriteOn = CCSprite::createWithSpriteFrameName("gj_swingBtn_on_001.png");
    swingSpriteOn->setScale(0.75f);
    m_swingToggler = CCMenuItemToggler::create(swingSpriteOff, swingSpriteOn, this, menu_selector(BIRSelectPopup::onToggle));
    m_swingToggler->setPosition(60.0f, 25.0f);
    m_buttonMenu->addChild(m_swingToggler);

    auto jetpackSpriteOff = CCSprite::createWithSpriteFrameName("gj_jetpackBtn_off_001.png");
    jetpackSpriteOff->setScale(0.75f);
    auto jetpackSpriteOn = CCSprite::createWithSpriteFrameName("gj_jetpackBtn_on_001.png");
    jetpackSpriteOn->setScale(0.75f);
    m_jetpackToggler = CCMenuItemToggler::create(jetpackSpriteOff, jetpackSpriteOn, this, menu_selector(BIRSelectPopup::onToggle));
    m_jetpackToggler->setPosition(90.0f, 25.0f);
    m_buttonMenu->addChild(m_jetpackToggler);

    auto streakSpriteOff = CCSprite::createWithSpriteFrameName("gj_streakBtn_off_001.png");
    streakSpriteOff->setScale(0.75f);
    auto streakSpriteOn = CCSprite::createWithSpriteFrameName("gj_streakBtn_on_001.png");
    streakSpriteOn->setScale(0.75f);
    m_streakToggler = CCMenuItemToggler::create(streakSpriteOff, streakSpriteOn, this, menu_selector(BIRSelectPopup::onToggle));
    m_streakToggler->setPosition(120.0f, 25.0f);
    m_buttonMenu->addChild(m_streakToggler);

    auto explosionSpriteOff = CCSprite::createWithSpriteFrameName("gj_explosionBtn_off_001.png");
    explosionSpriteOff->setScale(0.75f);
    auto explosionSpriteOn = CCSprite::createWithSpriteFrameName("gj_explosionBtn_on_001.png");
    explosionSpriteOn->setScale(0.75f);
    m_explosionToggler = CCMenuItemToggler::create(explosionSpriteOff, explosionSpriteOn, this, menu_selector(BIRSelectPopup::onToggle));
    m_explosionToggler->setPosition(150.0f, 25.0f);
    m_buttonMenu->addChild(m_explosionToggler);

    // Okay here comes the color toggles, which are way different
    auto gameManager = GameManager::sharedState();

    auto color1 = gameManager->colorForIdx(gameManager->getPlayerColor());
    auto color1LabelOff = CCLabelBMFont::create("1", "bigFont.fnt");
    color1LabelOff->setScale(0.5f);
    color1LabelOff->setColor(color1);
    auto color1SpriteOff = CCSprite::createWithSpriteFrameName("player_special_01_001.png");
    color1SpriteOff->setColor(color1);
    color1SpriteOff->addChild(color1LabelOff);
    auto color1DarkSprite = CCSprite::createWithSpriteFrameName("player_special_01_001.png");
    color1DarkSprite->setColor({ 0, 0, 0 });
    color1DarkSprite->setOpacity(150);
    color1DarkSprite->addChild(color1SpriteOff, -1);
    auto color1LabelOn = CCLabelBMFont::create("1", "bigFont.fnt");
    color1LabelOn->setScale(0.5f);
    color1LabelOn->setColor(color1);
    auto color1SpriteOn = CCSprite::createWithSpriteFrameName("player_special_01_001.png");
    color1SpriteOn->setColor(color1);
    color1SpriteOn->addChild(color1LabelOn);
    m_colorToggler1 = CCMenuItemToggler::create(color1DarkSprite, color1SpriteOn, this, menu_selector(BIRSelectPopup::onToggle));
    color1SpriteOff->setPosition(color1DarkSprite->getPosition());
    color1LabelOff->setPosition(color1SpriteOff->getPosition());
    color1LabelOn->setPosition(color1SpriteOn->getPosition());
    m_colorToggler1->setPosition(-50.0f, -10.0f);
    m_buttonMenu->addChild(m_colorToggler1);

    auto color2 = gameManager->colorForIdx(gameManager->getPlayerColor2());
    auto color2LabelOff = CCLabelBMFont::create("2", "bigFont.fnt");
    color2LabelOff->setScale(0.5f);
    color2LabelOff->setColor(color2);
    auto color2SpriteOff = CCSprite::createWithSpriteFrameName("player_special_01_001.png");
    color2SpriteOff->setColor(color2);
    color2SpriteOff->addChild(color2LabelOff);
    auto color2DarkSprite = CCSprite::createWithSpriteFrameName("player_special_01_001.png");
    color2DarkSprite->setColor({ 0, 0, 0 });
    color2DarkSprite->setOpacity(150);
    color2DarkSprite->addChild(color2SpriteOff, -1);
    auto color2LabelOn = CCLabelBMFont::create("2", "bigFont.fnt");
    color2LabelOn->setScale(0.5f);
    color2LabelOn->setColor(color2);
    auto color2SpriteOn = CCSprite::createWithSpriteFrameName("player_special_01_001.png");
    color2SpriteOn->setColor(color2);
    color2SpriteOn->addChild(color2LabelOn);
    m_colorToggler2 = CCMenuItemToggler::create(color2DarkSprite, color2SpriteOn, this, menu_selector(BIRSelectPopup::onToggle));
    color2SpriteOff->setPosition(color2DarkSprite->getPosition());
    color2LabelOff->setPosition(color2SpriteOff->getPosition());
    color2LabelOn->setPosition(color2SpriteOn->getPosition());
    m_colorToggler2->setPosition(0.0f, -10.0f);
    m_buttonMenu->addChild(m_colorToggler2);

    auto color3 = gameManager->colorForIdx(gameManager->getPlayerGlowColor());
    auto color3LabelOff = CCLabelBMFont::create("G", "bigFont.fnt");
    color3LabelOff->setScale(0.5f);
    color3LabelOff->setColor(color3);
    auto color3SpriteOff = CCSprite::createWithSpriteFrameName("player_special_01_001.png");
    color3SpriteOff->setColor(color3);
    color3SpriteOff->addChild(color3LabelOff);
    auto color3DarkSprite = CCSprite::createWithSpriteFrameName("player_special_01_001.png");
    color3DarkSprite->setColor({ 0, 0, 0 });
    color3DarkSprite->setOpacity(150);
    color3DarkSprite->addChild(color3SpriteOff, -1);
    auto color3LabelOn = CCLabelBMFont::create("G", "bigFont.fnt");
    color3LabelOn->setScale(0.5f);
    color3LabelOn->setColor(color3);
    auto color3SpriteOn = CCSprite::createWithSpriteFrameName("player_special_01_001.png");
    color3SpriteOn->setColor(color3);
    color3SpriteOn->addChild(color3LabelOn);
    m_colorToggler3 = CCMenuItemToggler::create(color3DarkSprite, color3SpriteOn, this, menu_selector(BIRSelectPopup::onToggle));
    color3SpriteOff->setPosition(color3DarkSprite->getPosition());
    color3LabelOff->setPosition(color3SpriteOff->getPosition());
    color3LabelOn->setPosition(color3SpriteOn->getPosition());
    m_colorToggler3->setPosition(50.0f, -10.0f);
    m_buttonMenu->addChild(m_colorToggler3);

    auto randomizeButton = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Randomize", "goldFont.fnt", "GJ_button_01.png", 0.8f),
        this,
        menu_selector(BIRSelectPopup::onRandomize)
    );
    randomizeButton->setPositionY(-50.0f);
    m_buttonMenu->addChild(randomizeButton);
    return true;
}

void BIRSelectPopup::randomize(UnlockType unlockType, bool randomizeGlow) {
    auto gameManager = GameManager::sharedState();
    auto num = 0;
    switch (unlockType) {
        case UnlockType::Cube:
            num = unlocked[0][randomNumber(0, unlocked[0].size() - 1)];
            gameManager->setPlayerFrame(num);
            m_garageLayer->m_iconPages[IconType::Cube] = (num - 1) / 36;
            break;
        case UnlockType::Col1:
            num = unlocked[1][randomNumber(0, unlocked[1].size() - 1)];
            gameManager->setPlayerColor(num);
            break;
        case UnlockType::Col2:
            num = unlocked[2][randomNumber(0, unlocked[2].size() - 1)];
            if (randomizeGlow) gameManager->setPlayerColor3(num);
            else gameManager->setPlayerColor2(num);
            break;
        case UnlockType::Ship:
            num = unlocked[3][randomNumber(0, unlocked[3].size() - 1)];
            gameManager->setPlayerShip(num);
            m_garageLayer->m_iconPages[IconType::Ship] = (num - 1) / 36;
            break;
        case UnlockType::Ball:
            num = unlocked[4][randomNumber(0, unlocked[4].size() - 1)];
            gameManager->setPlayerBall(num);
            m_garageLayer->m_iconPages[IconType::Ball] = (num - 1) / 36;
            break;
        case UnlockType::Bird:
            num = unlocked[5][randomNumber(0, unlocked[5].size() - 1)];
            gameManager->setPlayerBird(num);
            m_garageLayer->m_iconPages[IconType::Ufo] = (num - 1) / 36;
            break;
        case UnlockType::Dart:
            num = unlocked[6][randomNumber(0, unlocked[6].size() - 1)];
            gameManager->setPlayerDart(num);
            m_garageLayer->m_iconPages[IconType::Wave] = (num - 1) / 36;
            break;
        case UnlockType::Robot:
            num = unlocked[7][randomNumber(0, unlocked[7].size() - 1)];
            gameManager->setPlayerRobot(num);
            m_garageLayer->m_iconPages[IconType::Robot] = (num - 1) / 36;
            break;
        case UnlockType::Spider:
            num = unlocked[8][randomNumber(0, unlocked[8].size() - 1)];
            gameManager->setPlayerSpider(num);
            m_garageLayer->m_iconPages[IconType::Spider] = (num - 1) / 36;
            break;
        case UnlockType::Streak:
            num = unlocked[9][randomNumber(0, unlocked[9].size() - 1)];
            gameManager->setPlayerStreak(num);
            m_garageLayer->m_iconPages[IconType::Special] = 0;
            break;
        case UnlockType::Death:
            num = unlocked[10][randomNumber(0, unlocked[10].size() - 1)];
            gameManager->setPlayerDeathEffect(num);
            m_garageLayer->m_iconPages[IconType::DeathEffect] = 0;
            break;
        case UnlockType::Swing:
            num = unlocked[11][randomNumber(0, unlocked[11].size() - 1)];
            gameManager->setPlayerSwing(num);
            m_garageLayer->m_iconPages[IconType::Swing] = (num - 1) / 36;
            break;
        case UnlockType::Jetpack:
            num = unlocked[12][randomNumber(0, unlocked[12].size() - 1)];
            gameManager->setPlayerJetpack(num);
            m_garageLayer->m_iconPages[IconType::Jetpack] = 0;
            break;
        case UnlockType::ShipFire:
            num = unlocked[13][randomNumber(0, unlocked[13].size() - 1)];
            gameManager->setPlayerShipStreak(num);
            m_garageLayer->m_iconPages[IconType::Special] = 0;
            break;
    }
}

void BIRSelectPopup::onRandomize(CCObject*) {
    auto enabledTypes = std::vector<IconType>();
    if (m_iconToggler->m_toggled) {
        enabledTypes.push_back(IconType::Cube);
        randomize(UnlockType::Cube);
    }
    if (m_shipToggler->m_toggled) {
        enabledTypes.push_back(IconType::Ship);
        randomize(UnlockType::Ship);
    }
    if (m_ballToggler->m_toggled) {
        enabledTypes.push_back(IconType::Ball);
        randomize(UnlockType::Ball);
    }
    if (m_birdToggler->m_toggled) {
        enabledTypes.push_back(IconType::Ufo);
        randomize(UnlockType::Bird);
    }
    if (m_dartToggler->m_toggled) {
        enabledTypes.push_back(IconType::Wave);
        randomize(UnlockType::Dart);
    }
    if (m_robotToggler->m_toggled) {
        enabledTypes.push_back(IconType::Robot);
        randomize(UnlockType::Robot);
    }
    if (m_spiderToggler->m_toggled) {
        enabledTypes.push_back(IconType::Spider);
        randomize(UnlockType::Spider);
    }
    if (m_swingToggler->m_toggled) {
        enabledTypes.push_back(IconType::Swing);
        randomize(UnlockType::Swing);
    }
    if (m_jetpackToggler->m_toggled) {
        enabledTypes.push_back(IconType::Jetpack);
        randomize(UnlockType::Jetpack);
    }
    if (m_streakToggler->m_toggled) randomize(UnlockType::Streak);
    if (m_explosionToggler->m_toggled) randomize(UnlockType::Death);
    if (m_colorToggler1->m_toggled) randomize(UnlockType::Col1);
    if (m_colorToggler2->m_toggled) randomize(UnlockType::Col2);
    if (m_colorToggler3->m_toggled) randomize(UnlockType::Col2, true);

    auto gameManager = GameManager::sharedState();
    auto randomType = enabledTypes.empty() ? gameManager->m_playerIconType : enabledTypes[randomNumber(0, enabledTypes.size() - 1)];
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

    gameManager->m_playerIconType = randomType;
    m_garageLayer->m_playerObject->setColor(gameManager->colorForIdx(gameManager->getPlayerColor()));
    m_garageLayer->m_playerObject->setSecondColor(gameManager->colorForIdx(gameManager->getPlayerColor2()));
    if (gameManager->getPlayerGlow()) m_garageLayer->m_playerObject->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
    else m_garageLayer->m_playerObject->disableGlowOutline();
    m_garageLayer->m_playerObject->updatePlayerFrame(playerFrame, randomType);
    m_garageLayer->m_playerObject->setScale(randomType == IconType::Jetpack ? 1.5f : 1.6f);
    m_garageLayer->m_selectedIconType = randomType;
    m_garageLayer->m_iconID = playerFrame;
    m_garageLayer->selectTab(randomType);
    onClose(nullptr);
}
