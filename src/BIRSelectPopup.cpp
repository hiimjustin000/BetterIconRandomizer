#include "BIRSelectPopup.hpp"

BIRSelectPopup* BIRSelectPopup::create() {
    auto ret = new BIRSelectPopup();

    if (ret && ret->initAnchored(350.0f, 150.0f)) {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool BIRSelectPopup::setup() {
    setTitle("Select Modes to Randomize");

    m_iconToggles = CCArray::create();
    m_iconToggles->retain();
    m_iconToggles->addObject(createIconToggle("icon", 25.0f));
    m_iconToggles->addObject(createIconToggle("ship", 55.0f));
    m_iconToggles->addObject(createIconToggle("ball", 85.0f));
    m_iconToggles->addObject(createIconToggle("bird", 115.0f));
    m_iconToggles->addObject(createIconToggle("dart", 145.0f));
    m_iconToggles->addObject(createIconToggle("robot", 175.0f));
    m_iconToggles->addObject(createIconToggle("spider", 205.0f));
    m_iconToggles->addObject(createIconToggle("swing", 235.0f));
    m_iconToggles->addObject(createIconToggle("jetpack", 265.0f));

    m_specialToggles = CCArray::create();
    m_specialToggles->retain();
    m_specialToggles->addObject(createIconToggle("streak", 295.0f));
    m_specialToggles->addObject(createIconToggle("explosion", 325.0f));

    auto gameManager = GameManager::sharedState();
    m_colorToggles = CCArray::create();
    m_colorToggles->retain();
    m_colorToggles->addObject(createColorToggle("1", 125.0f, gameManager->getPlayerColor()));
    m_colorToggles->addObject(createColorToggle("2", 175.0f, gameManager->getPlayerColor2()));
    m_colorToggles->addObject(createColorToggle("G", 225.0f, gameManager->getPlayerGlowColor()));

    m_allIconsToggler = createAllToggle("Icons", 70.0f, menu_selector(BIRSelectPopup::onAllIconsToggle));
    m_allSpecialsToggler = createAllToggle("Special", 45.0f, menu_selector(BIRSelectPopup::onAllSpecialsToggle));
    m_allColorsToggler = createAllToggle("Colors", 20.0f, menu_selector(BIRSelectPopup::onAllColorsToggle));

    auto randomizeButton = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Randomize", "goldFont.fnt", "GJ_button_01.png", 0.8f),
        this,
        menu_selector(BIRSelectPopup::onRandomize)
    );
    randomizeButton->setPosition(175.0f, 25.0f);
    m_buttonMenu->addChild(randomizeButton);

    return true;
}

CCMenuItemToggler* BIRSelectPopup::createIconToggle(const char* frame, float x) {
    auto spriteOff = CCSprite::createWithSpriteFrameName(fmt::format("gj_{}Btn_off_001.png", frame).c_str());
    spriteOff->setScale(0.75f);
    auto spriteOn = CCSprite::createWithSpriteFrameName(fmt::format("gj_{}Btn_on_001.png", frame).c_str());
    spriteOn->setScale(0.75f);
    auto toggler = CCMenuItemToggler::create(spriteOff, spriteOn, this, menu_selector(BIRSelectPopup::onIconToggle));
    toggler->setPosition(x, 100.0f);
    m_buttonMenu->addChild(toggler);

    return toggler;
}

CCMenuItemToggler* BIRSelectPopup::createColorToggle(const char* label, float x, int colorIdx) {
    auto gameManager = GameManager::sharedState();

    auto color = gameManager->colorForIdx(colorIdx);
    auto colorLabelOff = CCLabelBMFont::create(label, "bigFont.fnt");
    colorLabelOff->setScale(0.5f);
    colorLabelOff->setColor(color);
    auto colorSpriteOff = CCSprite::createWithSpriteFrameName("player_special_01_001.png");
    colorSpriteOff->setColor(color);
    colorSpriteOff->addChild(colorLabelOff);
    auto colorDarkSprite = CCSprite::createWithSpriteFrameName("player_special_01_001.png");
    colorDarkSprite->setColor({ 0, 0, 0 });
    colorDarkSprite->setOpacity(150);
    colorDarkSprite->addChild(colorSpriteOff, -1);
    auto colorLabelOn = CCLabelBMFont::create(label, "bigFont.fnt");
    colorLabelOn->setScale(0.5f);
    colorLabelOn->setColor(color);
    auto colorSpriteOn = CCSprite::createWithSpriteFrameName("player_special_01_001.png");
    colorSpriteOn->setColor(color);
    colorSpriteOn->addChild(colorLabelOn);
    auto toggler = CCMenuItemToggler::create(colorDarkSprite, colorSpriteOn, this, menu_selector(BIRSelectPopup::onColorToggle));
    colorSpriteOff->setPosition(colorDarkSprite->getPosition());
    colorLabelOff->setPosition(colorSpriteOff->getPosition());
    colorLabelOn->setPosition(colorSpriteOn->getPosition());
    toggler->setPosition(x, 65.0f);
    m_buttonMenu->addChild(toggler);

    return toggler;
}

CCMenuItemToggler* BIRSelectPopup::createAllToggle(const char* label, float y, SEL_MenuHandler handler) {
    auto allLabel = CCLabelBMFont::create(label, "bigFont.fnt");
    allLabel->setScale(0.5f);
    allLabel->setAnchorPoint({ 1.0f, 0.5f });
    allLabel->setPosition(320.0f, y);
    m_buttonMenu->addChild(allLabel);

    auto spriteOff = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
    spriteOff->setScale(0.6f);
    auto spriteOn = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
    spriteOn->setScale(0.6f);
    auto toggler = CCMenuItemToggler::create(spriteOff, spriteOn, this, handler);
    toggler->setPosition(332.5f, y);
    m_buttonMenu->addChild(toggler);

    return toggler;
}

void BIRSelectPopup::onIconToggle(CCObject* sender) {
    auto toggler = static_cast<CCMenuItemToggler*>(sender);
    toggler->m_toggled = !toggler->m_toggled;
    auto iconToggles = CCArrayExt<CCMenuItemToggler*>(m_iconToggles);
    m_allIconsToggler->toggle(iconToggles.size() == std::count_if(iconToggles.begin(), iconToggles.end(), [](auto toggle) { return toggle->m_toggled; }));
    toggler->m_toggled = !toggler->m_toggled;
}

void BIRSelectPopup::onAllIconsToggle(CCObject*) {
    for (auto toggler : CCArrayExt<CCMenuItemToggler*>(m_iconToggles)) toggler->toggle(!m_allIconsToggler->m_toggled);
}

void BIRSelectPopup::onSpecialToggle(CCObject* sender) {
    auto toggler = static_cast<CCMenuItemToggler*>(sender);
    toggler->m_toggled = !toggler->m_toggled;
    auto specialToggles = CCArrayExt<CCMenuItemToggler*>(m_specialToggles);
    m_allSpecialsToggler->toggle(specialToggles.size() == std::count_if(specialToggles.begin(), specialToggles.end(), [](auto toggle) { return toggle->m_toggled; }));
    toggler->m_toggled = !toggler->m_toggled;
}

void BIRSelectPopup::onAllSpecialsToggle(CCObject*) {
    for (auto toggler : CCArrayExt<CCMenuItemToggler*>(m_specialToggles)) toggler->toggle(!m_allSpecialsToggler->m_toggled);
}

void BIRSelectPopup::onColorToggle(CCObject* sender) {
    auto toggler = static_cast<CCMenuItemToggler*>(sender);
    toggler->m_toggled = !toggler->m_toggled;
    auto colorToggles = CCArrayExt<CCMenuItemToggler*>(m_colorToggles);
    m_allColorsToggler->toggle(colorToggles.size() == std::count_if(colorToggles.begin(), colorToggles.end(), [](auto toggle) { return toggle->m_toggled; }));
    toggler->m_toggled = !toggler->m_toggled;
}

void BIRSelectPopup::onAllColorsToggle(CCObject*) {
    for (auto toggler : CCArrayExt<CCMenuItemToggler*>(m_colorToggles)) toggler->toggle(!m_allColorsToggler->m_toggled);
}

void BIRSelectPopup::randomize(UnlockType unlockType, bool randomizeGlow) {
    auto num = BetterIconRandomizer::randomize(unlockType, randomizeGlow);
    switch (unlockType) {
        case UnlockType::Cube:
            m_garageLayer->m_iconPages[IconType::Cube] = (num - 1) / 36;
            break;
        case UnlockType::Ship:
            m_garageLayer->m_iconPages[IconType::Ship] = (num - 1) / 36;
            break;
        case UnlockType::Ball:
            m_garageLayer->m_iconPages[IconType::Ball] = (num - 1) / 36;
            break;
        case UnlockType::Bird:
            m_garageLayer->m_iconPages[IconType::Ufo] = (num - 1) / 36;
            break;
        case UnlockType::Dart:
            m_garageLayer->m_iconPages[IconType::Wave] = (num - 1) / 36;
            break;
        case UnlockType::Robot:
            m_garageLayer->m_iconPages[IconType::Robot] = (num - 1) / 36;
            break;
        case UnlockType::Spider:
            m_garageLayer->m_iconPages[IconType::Spider] = (num - 1) / 36;
            break;
        case UnlockType::Streak:
        case UnlockType::ShipFire:
            m_garageLayer->m_iconPages[IconType::Special] = 0;
            break;
        case UnlockType::Death:
            m_garageLayer->m_iconPages[IconType::DeathEffect] = 0;
            break;
        case UnlockType::Swing:
            m_garageLayer->m_iconPages[IconType::Swing] = (num - 1) / 36;
            break;
        case UnlockType::Jetpack:
            m_garageLayer->m_iconPages[IconType::Jetpack] = 0;
            break;
    }
}

void BIRSelectPopup::onRandomize(CCObject*) {
    auto enabledTypes = std::vector<IconType>();

    auto iconToggles = CCArrayExt<CCMenuItemToggler*>(m_iconToggles);
    if (iconToggles[0]->m_toggled) {
        enabledTypes.push_back(IconType::Cube);
        randomize(UnlockType::Cube, false);
    }
    if (iconToggles[1]->m_toggled) {
        enabledTypes.push_back(IconType::Ship);
        randomize(UnlockType::Ship, false);
    }
    if (iconToggles[2]->m_toggled) {
        enabledTypes.push_back(IconType::Ball);
        randomize(UnlockType::Ball, false);
    }
    if (iconToggles[3]->m_toggled) {
        enabledTypes.push_back(IconType::Ufo);
        randomize(UnlockType::Bird, false);
    }
    if (iconToggles[4]->m_toggled) {
        enabledTypes.push_back(IconType::Wave);
        randomize(UnlockType::Dart, false);
    }
    if (iconToggles[5]->m_toggled) {
        enabledTypes.push_back(IconType::Robot);
        randomize(UnlockType::Robot, false);
    }
    if (iconToggles[6]->m_toggled) {
        enabledTypes.push_back(IconType::Spider);
        randomize(UnlockType::Spider, false);
    }
    if (iconToggles[7]->m_toggled) {
        enabledTypes.push_back(IconType::Swing);
        randomize(UnlockType::Swing, false);
    }
    if (iconToggles[8]->m_toggled) {
        enabledTypes.push_back(IconType::Jetpack);
        randomize(UnlockType::Jetpack, false);
    }

    auto specialToggles = CCArrayExt<CCMenuItemToggler*>(m_specialToggles);
    if (specialToggles[0]->m_toggled) {
        randomize(UnlockType::Streak, false);
        randomize(UnlockType::ShipFire, false);
    }
    if (specialToggles[1]->m_toggled) randomize(UnlockType::Death, false);

    auto colorToggles = CCArrayExt<CCMenuItemToggler*>(m_colorToggles);
    if (colorToggles[0]->m_toggled) randomize(UnlockType::Col1, false);
    if (colorToggles[1]->m_toggled) randomize(UnlockType::Col2, false);
    if (colorToggles[2]->m_toggled) randomize(UnlockType::Col2, true);

    auto gameManager = GameManager::sharedState();
    auto randomType = enabledTypes.empty() ? gameManager->m_playerIconType : enabledTypes[BetterIconRandomizer::randomNumber(0, enabledTypes.size() - 1)];
    gameManager->m_playerIconType = randomType;
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
    m_garageLayer->updatePlayerColors();
    m_garageLayer->m_playerObject->updatePlayerFrame(playerFrame, randomType);
    m_garageLayer->m_playerObject->setScale(randomType == IconType::Jetpack ? 1.5f : 1.6f);
    m_garageLayer->m_selectedIconType = randomType;
    m_garageLayer->m_iconID = playerFrame;
    m_garageLayer->selectTab(randomType);
    onClose(nullptr);
}
