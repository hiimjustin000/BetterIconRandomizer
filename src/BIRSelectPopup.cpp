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

    m_iconMenu = CCMenu::create();
    m_iconMenu->setLayout(RowLayout::create()->setGap(6.0f));
    m_iconMenu->setContentSize({ 340.0f, 30.0f });
    m_iconMenu->setPosition(175.0f, 100.0f);
    m_mainLayer->addChild(m_iconMenu);

    m_iconToggles = CCArray::create();
    m_iconToggles->retain();
    m_iconToggles->addObject(createIconToggle("icon"));
    m_iconToggles->addObject(createIconToggle("ship"));
    m_iconToggles->addObject(createIconToggle("ball"));
    m_iconToggles->addObject(createIconToggle("bird"));
    m_iconToggles->addObject(createIconToggle("dart"));
    m_iconToggles->addObject(createIconToggle("robot"));
    m_iconToggles->addObject(createIconToggle("spider"));
    m_iconToggles->addObject(createIconToggle("swing"));
    m_iconToggles->addObject(createIconToggle("jetpack"));

    m_specialToggles = CCArray::create();
    m_specialToggles->retain();
    m_specialToggles->addObject(createIconToggle("streak"));
    m_specialToggles->addObject(createIconToggle("explosion"));

    m_iconMenu->updateLayout();

    m_colorMenu = CCMenu::create();
    m_colorMenu->setLayout(RowLayout::create()->setGap(20.0f));
    m_colorMenu->setContentSize({ 150.0f, 40.0f });
    m_colorMenu->setPosition(175.0f, 65.0f);
    m_mainLayer->addChild(m_colorMenu);

    auto gameManager = GameManager::sharedState();
    m_colorToggles = CCArray::create();
    m_colorToggles->retain();
    m_colorToggles->addObject(createColorToggle("1", gameManager->getPlayerColor()));
    m_colorToggles->addObject(createColorToggle("2", gameManager->getPlayerColor2()));
    m_colorToggles->addObject(createColorToggle("G", gameManager->getPlayerGlowColor()));

    m_colorMenu->updateLayout();

    m_allMenu = CCMenu::create();
    m_allMenu->setLayout(ColumnLayout::create()->setGap(6.0f)->setAxisReverse(true));
    m_allMenu->setContentSize({ 30.0f, 80.0f });
    m_allMenu->setPosition(332.5f, 45.0f);
    m_mainLayer->addChild(m_allMenu);

    m_allIconsToggler = createAllToggle(menu_selector(BIRSelectPopup::onAllIconsToggle));
    m_allSpecialsToggler = createAllToggle(menu_selector(BIRSelectPopup::onAllSpecialsToggle));
    m_allColorsToggler = createAllToggle(menu_selector(BIRSelectPopup::onAllColorsToggle));

    m_allMenu->updateLayout();

    m_mainLayer->addChild(createAllLabel("Icons", m_allIconsToggler));
    m_mainLayer->addChild(createAllLabel("Special", m_allSpecialsToggler));
    m_mainLayer->addChild(createAllLabel("Colors", m_allColorsToggler));

    auto randomizeButton = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Randomize", "goldFont.fnt", "GJ_button_01.png", 0.8f),
        this,
        menu_selector(BIRSelectPopup::onRandomize)
    );
    randomizeButton->setPosition(175.0f, 25.0f);
    m_buttonMenu->addChild(randomizeButton);

    return true;
}

CCMenuItemToggler* BIRSelectPopup::createIconToggle(const char* frame) {
    auto toggler = CCMenuItemToggler::createWithSize(
        fmt::format("gj_{}Btn_off_001.png", frame).c_str(),
        fmt::format("gj_{}Btn_on_001.png", frame).c_str(),
        this,
        menu_selector(BIRSelectPopup::onIconToggle),
        0.75f
    );
    m_iconMenu->addChild(toggler);

    return toggler;
}

CCMenuItemToggler* BIRSelectPopup::createColorToggle(const char* label, int colorIdx) {
    auto gameManager = GameManager::sharedState();
    auto color = gameManager->colorForIdx(colorIdx);
    auto darkColor = ccColor3B {
        (unsigned char)floorf(color.r * 0.6f),
        (unsigned char)floorf(color.g * 0.6f),
        (unsigned char)floorf(color.b * 0.6f)
    };

    auto colorLabelOff = CCLabelBMFont::create(label, "bigFont.fnt");
    colorLabelOff->setScale(0.5f);
    colorLabelOff->setColor(darkColor);
    auto colorSpriteOff = CCSprite::createWithSpriteFrameName("player_special_01_001.png");
    colorSpriteOff->setColor(darkColor);
    colorSpriteOff->addChild(colorLabelOff);
    auto colorLabelOn = CCLabelBMFont::create(label, "bigFont.fnt");
    colorLabelOn->setScale(0.5f);
    colorLabelOn->setColor(color);
    auto colorSpriteOn = CCSprite::createWithSpriteFrameName("player_special_01_001.png");
    colorSpriteOn->setColor(color);
    colorSpriteOn->addChild(colorLabelOn);
    auto toggler = CCMenuItemToggler::create(colorSpriteOff, colorSpriteOn, this, menu_selector(BIRSelectPopup::onColorToggle));
    colorLabelOff->setPosition(colorSpriteOff->getPosition());
    colorLabelOn->setPosition(colorSpriteOn->getPosition());
    m_colorMenu->addChild(toggler);

    return toggler;
}

CCMenuItemToggler* BIRSelectPopup::createAllToggle(SEL_MenuHandler handler) {
    auto toggler = CCMenuItemToggler::createWithStandardSprites(this, handler, 0.6f);
    m_allMenu->addChild(toggler);

    return toggler;
}

CCLabelBMFont* BIRSelectPopup::createAllLabel(const char* label, CCMenuItemToggler* toggler) {
    auto allLabel = CCLabelBMFont::create(label, "bigFont.fnt");
    allLabel->setScale(0.5f);
    allLabel->setAnchorPoint({ 1.0f, 0.5f });
    allLabel->setPosition(m_mainLayer->convertToNodeSpace(m_allMenu->convertToWorldSpace(toggler->getPosition())) + CCPoint { -12.5f, 0.0f });

    return allLabel;
}

void BIRSelectPopup::onIconToggle(CCObject* sender) {
    onToggle(m_iconToggles, static_cast<CCMenuItemToggler*>(sender), m_allIconsToggler);
}

void BIRSelectPopup::onAllIconsToggle(CCObject*) {
    onAllToggle(m_iconToggles, m_allIconsToggler);
}

void BIRSelectPopup::onSpecialToggle(CCObject* sender) {
    onToggle(m_specialToggles, static_cast<CCMenuItemToggler*>(sender), m_allSpecialsToggler);
}

void BIRSelectPopup::onAllSpecialsToggle(CCObject*) {
    onAllToggle(m_specialToggles, m_allSpecialsToggler);
}

void BIRSelectPopup::onColorToggle(CCObject* sender) {
    onToggle(m_colorToggles, static_cast<CCMenuItemToggler*>(sender), m_allColorsToggler);
}

void BIRSelectPopup::onAllColorsToggle(CCObject*) {
    onAllToggle(m_colorToggles, m_allColorsToggler);
}

void BIRSelectPopup::onToggle(CCArray* toggles, CCMenuItemToggler* toggler, CCMenuItemToggler* allToggler) {
    toggler->m_toggled = !toggler->m_toggled;
    auto allToggles = CCArrayExt<CCMenuItemToggler*>(toggles);
    allToggler->toggle(allToggles.size() == std::count_if(allToggles.begin(), allToggles.end(), [](auto toggle) { return toggle->m_toggled; }));
    toggler->m_toggled = !toggler->m_toggled;
}

void BIRSelectPopup::onAllToggle(CCArray* toggles, CCMenuItemToggler* allToggler) {
    for (auto toggler : CCArrayExt<CCMenuItemToggler*>(toggles)) {
        toggler->toggle(!allToggler->m_toggled);
    }
}

void BIRSelectPopup::onRandomize(CCObject*) {
    auto enabledTypes = std::vector<IconType>();

    auto iconToggles = CCArrayExt<CCMenuItemToggler*>(m_iconToggles);
    if (iconToggles[0]->m_toggled) {
        enabledTypes.push_back(IconType::Cube);
        m_garageLayer->m_iconPages[IconType::Cube] = (BetterIconRandomizer::randomize(UnlockType::Cube) - 1) / 36;
    }
    if (iconToggles[1]->m_toggled) {
        enabledTypes.push_back(IconType::Ship);
        m_garageLayer->m_iconPages[IconType::Ship] = (BetterIconRandomizer::randomize(UnlockType::Ship) - 1) / 36;
    }
    if (iconToggles[2]->m_toggled) {
        enabledTypes.push_back(IconType::Ball);
        m_garageLayer->m_iconPages[IconType::Ball] = (BetterIconRandomizer::randomize(UnlockType::Ball) - 1) / 36;
    }
    if (iconToggles[3]->m_toggled) {
        enabledTypes.push_back(IconType::Ufo);
        m_garageLayer->m_iconPages[IconType::Ufo] = (BetterIconRandomizer::randomize(UnlockType::Bird) - 1) / 36;
    }
    if (iconToggles[4]->m_toggled) {
        enabledTypes.push_back(IconType::Wave);
        m_garageLayer->m_iconPages[IconType::Wave] = (BetterIconRandomizer::randomize(UnlockType::Dart) - 1) / 36;
    }
    if (iconToggles[5]->m_toggled) {
        enabledTypes.push_back(IconType::Robot);
        m_garageLayer->m_iconPages[IconType::Robot] = (BetterIconRandomizer::randomize(UnlockType::Robot) - 1) / 36;
    }
    if (iconToggles[6]->m_toggled) {
        enabledTypes.push_back(IconType::Spider);
        m_garageLayer->m_iconPages[IconType::Spider] = (BetterIconRandomizer::randomize(UnlockType::Spider) - 1) / 36;
    }
    if (iconToggles[7]->m_toggled) {
        enabledTypes.push_back(IconType::Swing);
        m_garageLayer->m_iconPages[IconType::Swing] = (BetterIconRandomizer::randomize(UnlockType::Swing) - 1) / 36;
    }
    if (iconToggles[8]->m_toggled) {
        enabledTypes.push_back(IconType::Jetpack);
        m_garageLayer->m_iconPages[IconType::Jetpack] = (BetterIconRandomizer::randomize(UnlockType::Jetpack) - 1) / 36;
    }

    auto specialToggles = CCArrayExt<CCMenuItemToggler*>(m_specialToggles);
    if (specialToggles[0]->m_toggled) {
        BetterIconRandomizer::randomize(UnlockType::Streak);
        BetterIconRandomizer::randomize(UnlockType::ShipFire);
    }
    if (specialToggles[1]->m_toggled) m_garageLayer->m_iconPages[IconType::DeathEffect] = (BetterIconRandomizer::randomize(UnlockType::Death) - 1) / 36;

    auto colorToggles = CCArrayExt<CCMenuItemToggler*>(m_colorToggles);
    if (colorToggles[0]->m_toggled) BetterIconRandomizer::randomize(UnlockType::Col1);
    if (colorToggles[1]->m_toggled) BetterIconRandomizer::randomize(UnlockType::Col2);
    if (colorToggles[2]->m_toggled) BetterIconRandomizer::randomize(UnlockType::Col2, true);

    auto gameManager = GameManager::sharedState();
    auto randomType = enabledTypes.empty() ? gameManager->m_playerIconType : enabledTypes[BetterIconRandomizer::randomNumber(0, enabledTypes.size() - 1)];
    gameManager->m_playerIconType = randomType;
    auto playerFrame = gameManager->activeIconForType(randomType);
    m_garageLayer->updatePlayerColors();
    m_garageLayer->m_playerObject->updatePlayerFrame(playerFrame, randomType);
    m_garageLayer->m_playerObject->setScale(randomType == IconType::Jetpack ? 1.5f : 1.6f);
    m_garageLayer->m_selectedIconType = randomType;
    m_garageLayer->m_iconID = playerFrame;
    m_garageLayer->selectTab(randomType);
    onClose(nullptr);
}

BIRSelectPopup::~BIRSelectPopup() {
    CC_SAFE_RELEASE(m_iconToggles);
    CC_SAFE_RELEASE(m_specialToggles);
    CC_SAFE_RELEASE(m_colorToggles);
}
