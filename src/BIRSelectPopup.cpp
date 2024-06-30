#include "BIRSelectPopup.hpp"

BIRSelectPopup* BIRSelectPopup::create(GJGarageLayer* garageLayer) {
    auto ret = new BIRSelectPopup();
    if (ret->initAnchored(350.0f, 150.0f, garageLayer)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool BIRSelectPopup::setup(GJGarageLayer* garageLayer) {
    setTitle("Select Icons to Randomize");

    m_garageLayer = garageLayer;
    m_separateDualIcons = Loader::get()->getLoadedMod("weebify.separate_dual_icons");
    m_dual = m_separateDualIcons ? m_separateDualIcons->getSavedValue("2pselected", false) : false;

    m_iconMenu = CCMenu::create();
    m_iconMenu->setLayout(RowLayout::create()->setGap(6.0f));
    m_iconMenu->setContentSize({ 340.0f, 30.0f });
    m_iconMenu->setPosition(175.0f, 100.0f);
    m_mainLayer->addChild(m_iconMenu);

    m_iconToggles = CCArray::create();
    m_iconToggles->retain();
    createIconToggle("gj_iconBtn_off_001.png", "gj_iconBtn_on_001.png");
    createIconToggle("gj_shipBtn_off_001.png", "gj_shipBtn_on_001.png");
    createIconToggle("gj_ballBtn_off_001.png", "gj_ballBtn_on_001.png");
    createIconToggle("gj_birdBtn_off_001.png", "gj_birdBtn_on_001.png");
    createIconToggle("gj_dartBtn_off_001.png", "gj_dartBtn_on_001.png");
    createIconToggle("gj_robotBtn_off_001.png", "gj_robotBtn_on_001.png");
    createIconToggle("gj_spiderBtn_off_001.png", "gj_spiderBtn_on_001.png");
    createIconToggle("gj_swingBtn_off_001.png", "gj_swingBtn_on_001.png");
    createIconToggle("gj_jetpackBtn_off_001.png", "gj_jetpackBtn_on_001.png");

    m_specialToggles = CCArray::create();
    m_specialToggles->retain();
    createSpecialToggle("gj_streakBtn_off_001.png", "gj_streakBtn_on_001.png");
    createSpecialToggle("gj_explosionBtn_off_001.png", "gj_explosionBtn_on_001.png");

    m_iconMenu->updateLayout();

    m_colorMenu = CCMenu::create();
    m_colorMenu->setLayout(RowLayout::create()->setGap(20.0f));
    m_colorMenu->setContentSize({ 150.0f, 40.0f });
    m_colorMenu->setPosition(175.0f, 65.0f);
    m_mainLayer->addChild(m_colorMenu);

    auto gameManager = GameManager::sharedState();
    m_colorToggles = CCArray::create();
    m_colorToggles->retain();
    createColorToggle("1", gameManager->colorForIdx(m_dual ? m_separateDualIcons->getSavedValue("color1", 0) : gameManager->getPlayerColor()));
    createColorToggle("2", gameManager->colorForIdx(m_dual ? m_separateDualIcons->getSavedValue("color2", 0) : gameManager->getPlayerColor2()));
    createColorToggle("G", gameManager->colorForIdx(m_dual ? m_separateDualIcons->getSavedValue("colorglow", 0) : gameManager->getPlayerGlowColor()));

    m_colorMenu->updateLayout();

    auto allMenu = CCMenu::create();
    allMenu->setLayout(ColumnLayout::create()->setGap(6.0f)->setAxisReverse(true));
    allMenu->setContentSize({ 30.0f, 80.0f });
    allMenu->setPosition(332.5f, 45.0f);
    m_mainLayer->addChild(allMenu);

    m_allIconsToggler = CCMenuItemExt::createTogglerWithStandardSprites(0.6f, [this](auto sender) { onAllToggle(m_iconToggles, sender); });
    allMenu->addChild(m_allIconsToggler);
    m_allSpecialsToggler = CCMenuItemExt::createTogglerWithStandardSprites(0.6f, [this](auto sender) { onAllToggle(m_specialToggles, sender); });
    allMenu->addChild(m_allSpecialsToggler);
    m_allColorsToggler = CCMenuItemExt::createTogglerWithStandardSprites(0.6f, [this](auto sender) { onAllToggle(m_colorToggles, sender); });
    allMenu->addChild(m_allColorsToggler);

    allMenu->updateLayout();

    auto allLabels = CCNode::create();
    allLabels->setLayout(ColumnLayout::create()->setGap(8.35f)->setCrossAxisLineAlignment(AxisAlignment::End)->setAxisReverse(true)->setAutoScale(false));
    allLabels->setContentSize({ 70.0f, 70.0f });
    allLabels->setAnchorPoint({ 1.0f, 0.5f });
    allLabels->setPosition(320.0f, 45.0f);
    m_mainLayer->addChild(allLabels);

    auto iconsLabel = CCLabelBMFont::create("Icons", "bigFont.fnt");
    iconsLabel->setScale(0.5f);
    allLabels->addChild(iconsLabel);
    auto specialsLabel = CCLabelBMFont::create("Special", "bigFont.fnt");
    specialsLabel->setScale(0.5f);
    allLabels->addChild(specialsLabel);
    auto colorsLabel = CCLabelBMFont::create("Colors", "bigFont.fnt");
    colorsLabel->setScale(0.5f);
    allLabels->addChild(colorsLabel);

    allLabels->updateLayout();

    auto randomizeButton = CCMenuItemExt::createSpriteExtra(ButtonSprite::create("Randomize", "goldFont.fnt", "GJ_button_01.png", 0.8f), [this](auto) { randomize(); });
    randomizeButton->setPosition(175.0f, 25.0f);
    m_buttonMenu->addChild(randomizeButton);

    return true;
}

void BIRSelectPopup::createIconToggle(const char* offFrame, const char* onFrame) {
    auto toggler = CCMenuItemExt::createTogglerWithFrameName(onFrame, offFrame, 0.75f, [this](auto sender) { onToggle(m_iconToggles, sender, m_allIconsToggler); });
    m_iconMenu->addChild(toggler);
    m_iconToggles->addObject(toggler);
}

void BIRSelectPopup::createSpecialToggle(const char* offFrame, const char* onFrame) {
    auto toggler = CCMenuItemExt::createTogglerWithFrameName(onFrame, offFrame, 0.75f, [this](auto sender) { onToggle(m_specialToggles, sender, m_allSpecialsToggler); });
    m_iconMenu->addChild(toggler);
    m_specialToggles->addObject(toggler);
}

void BIRSelectPopup::createColorToggle(const char* label, ccColor3B color) {
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
    auto toggler = CCMenuItemExt::createToggler(colorSpriteOff, colorSpriteOn, [this](auto sender) { onToggle(m_colorToggles, sender, m_allColorsToggler); });
    colorLabelOff->setPosition(colorSpriteOff->getPosition());
    colorLabelOn->setPosition(colorSpriteOn->getPosition());
    m_colorMenu->addChild(toggler);
    m_colorToggles->addObject(toggler);
}

void BIRSelectPopup::onToggle(CCArray* toggles, CCMenuItemToggler* toggler, CCMenuItemToggler* allToggler) {
    toggler->m_toggled = !toggler->m_toggled;
    auto toggled = true;
    auto allToggles = reinterpret_cast<CCMenuItemToggler**>(toggles->data->arr);
    for (int i = 0; i < toggles->count(); i++) {
        if (!allToggles[i]->m_toggled) {
            toggled = false;
            break;
        }
    }
    allToggler->toggle(toggled);
    toggler->m_toggled = !toggler->m_toggled;
}

void BIRSelectPopup::onAllToggle(CCArray* toggles, CCMenuItemToggler* allToggler) {
    auto allToggles = reinterpret_cast<CCMenuItemToggler**>(toggles->data->arr);
    for (int i = 0; i < toggles->count(); i++) {
        allToggles[i]->toggle(!allToggler->m_toggled);
    }
}

void BIRSelectPopup::randomize() {
    auto enabledTypes = std::vector<IconType>();

    auto iconToggles = reinterpret_cast<CCMenuItemToggler**>(m_iconToggles->data->arr);
    if (iconToggles[0]->m_toggled) {
        enabledTypes.push_back(IconType::Cube);
        m_garageLayer->m_iconPages[IconType::Cube] = (BetterIconRandomizer::randomize(UnlockType::Cube, m_separateDualIcons) - 1) / 36;
    }
    if (iconToggles[1]->m_toggled) {
        enabledTypes.push_back(IconType::Ship);
        m_garageLayer->m_iconPages[IconType::Ship] = (BetterIconRandomizer::randomize(UnlockType::Ship, m_separateDualIcons) - 1) / 36;
    }
    if (iconToggles[2]->m_toggled) {
        enabledTypes.push_back(IconType::Ball);
        m_garageLayer->m_iconPages[IconType::Ball] = (BetterIconRandomizer::randomize(UnlockType::Ball, m_separateDualIcons) - 1) / 36;
    }
    if (iconToggles[3]->m_toggled) {
        enabledTypes.push_back(IconType::Ufo);
        m_garageLayer->m_iconPages[IconType::Ufo] = (BetterIconRandomizer::randomize(UnlockType::Bird, m_separateDualIcons) - 1) / 36;
    }
    if (iconToggles[4]->m_toggled) {
        enabledTypes.push_back(IconType::Wave);
        m_garageLayer->m_iconPages[IconType::Wave] = (BetterIconRandomizer::randomize(UnlockType::Dart, m_separateDualIcons) - 1) / 36;
    }
    if (iconToggles[5]->m_toggled) {
        enabledTypes.push_back(IconType::Robot);
        m_garageLayer->m_iconPages[IconType::Robot] = (BetterIconRandomizer::randomize(UnlockType::Robot, m_separateDualIcons) - 1) / 36;
    }
    if (iconToggles[6]->m_toggled) {
        enabledTypes.push_back(IconType::Spider);
        m_garageLayer->m_iconPages[IconType::Spider] = (BetterIconRandomizer::randomize(UnlockType::Spider, m_separateDualIcons) - 1) / 36;
    }
    if (iconToggles[7]->m_toggled) {
        enabledTypes.push_back(IconType::Swing);
        m_garageLayer->m_iconPages[IconType::Swing] = (BetterIconRandomizer::randomize(UnlockType::Swing, m_separateDualIcons) - 1) / 36;
    }
    if (iconToggles[8]->m_toggled) {
        enabledTypes.push_back(IconType::Jetpack);
        m_garageLayer->m_iconPages[IconType::Jetpack] = (BetterIconRandomizer::randomize(UnlockType::Jetpack, m_separateDualIcons) - 1) / 36;
    }

    auto specialToggles = reinterpret_cast<CCMenuItemToggler**>(m_specialToggles->data->arr);
    if (specialToggles[0]->m_toggled) {
        m_garageLayer->m_iconPages[IconType::Special] = (BetterIconRandomizer::randomize(UnlockType::Streak, m_separateDualIcons) - 1) / 36;
        m_garageLayer->m_iconPages[IconType::ShipFire] = (BetterIconRandomizer::randomize(UnlockType::ShipFire, m_separateDualIcons) - 1) / 36;
        BetterIconRandomizer::randomize(UnlockType::GJItem, m_separateDualIcons);
    }
    if (specialToggles[1]->m_toggled) m_garageLayer->m_iconPages[IconType::DeathEffect] = (BetterIconRandomizer::randomize(UnlockType::Death, m_separateDualIcons) - 1) / 36;

    auto colorToggles = reinterpret_cast<CCMenuItemToggler**>(m_colorToggles->data->arr);
    if (colorToggles[0]->m_toggled) BetterIconRandomizer::randomize(UnlockType::Col1, m_separateDualIcons);
    if (colorToggles[1]->m_toggled) BetterIconRandomizer::randomize(UnlockType::Col2, m_separateDualIcons);
    if (colorToggles[2]->m_toggled) BetterIconRandomizer::randomize(UnlockType::Col2, m_separateDualIcons, true);

    auto gameManager = GameManager::sharedState();
    auto randomType = enabledTypes.empty() ? m_dual ? (IconType)m_separateDualIcons->getSavedValue("lasttype", 0) : gameManager->m_playerIconType :
        enabledTypes[(size_t)BetterIconRandomizer::randomNumber(0, enabledTypes.size() - 1)];
    if (m_dual) m_separateDualIcons->setSavedValue("lasttype", (int)randomType);
    else gameManager->m_playerIconType = randomType;
    auto playerFrame = BetterIconRandomizer::activeIconForType(randomType, m_separateDualIcons);
    auto simplePlayer = m_dual ? static_cast<SimplePlayer*>(m_garageLayer->getChildByID("player2-icon")) : m_garageLayer->m_playerObject;
    simplePlayer->setScale(randomType == IconType::Jetpack ? 1.5f : 1.6f);
    simplePlayer->setColor(gameManager->colorForIdx(m_dual ? m_separateDualIcons->getSavedValue("color1", 0) : gameManager->getPlayerColor()));
    simplePlayer->setSecondColor(gameManager->colorForIdx(m_dual ? m_separateDualIcons->getSavedValue("color2", 0) : gameManager->getPlayerColor2()));
    simplePlayer->setGlowOutline(gameManager->colorForIdx(m_dual ? m_separateDualIcons->getSavedValue("colorglow", 0) : gameManager->getPlayerGlowColor()));
    if (m_dual ? !m_separateDualIcons->getSavedValue("glow", false) : !gameManager->getPlayerGlow()) simplePlayer->disableGlowOutline();
    simplePlayer->updatePlayerFrame(playerFrame, randomType);
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
