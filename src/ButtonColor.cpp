#include "ButtonColor.hpp"

bool ButtonColorSettingValue::load(matjson::Value const& json) {
    if (!json.is_number()) return false;
    auto value = json.as_int();
    m_value = value >= 0 && value <= 7 ? static_cast<ButtonColor>(value) : ButtonColor::Random;
    return true;
}

bool ButtonColorSettingValue::save(matjson::Value& json) const {
    json = static_cast<int>(m_value);
    return true;
}

SettingNode* ButtonColorSettingValue::createNode(float width) {
    return ButtonColorSettingNode::create(this, width);
}

ButtonColor ButtonColorSettingValue::getValue() const {
    return m_value;
}

void ButtonColorSettingValue::setValue(ButtonColor value) {
    m_value = value;
}

ButtonColorSettingNode* ButtonColorSettingNode::create(ButtonColorSettingValue* value, float width) {
    auto ret = new ButtonColorSettingNode();
    if (ret->init(value, width)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool ButtonColorSettingNode::init(ButtonColorSettingValue* value, float width) {
    if (!SettingNode::init(value)) return false;

    setContentSize({ width, 40.0f });
    m_uncommittedValue = static_cast<int>(value->getValue());

    m_nameLabel = CCLabelBMFont::create("Randomize Button Color", "bigFont.fnt");
    m_nameLabel->setAnchorPoint({ 0.0f, 0.5f });
    m_nameLabel->limitLabelWidth(width * 0.5f - 50.0f, 0.5f, 0.1f);
    m_nameLabel->setPosition(20.0f, 20.0f);
    addChild(m_nameLabel);

    auto menu = CCMenu::create();
    menu->setPosition(width - 20.0f, 20.0f);
    addChild(menu);

    auto infoSpr = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
    infoSpr->setScale(0.6f);
    auto infoBtn = CCMenuItemExt::createSpriteExtra(infoSpr, [this](auto) {
        FLAlertLayer::create("Randomize Button Color", "The color of the randomize button.", "OK")->show();
    });
    infoBtn->setPositionX(m_nameLabel->getScaledContentSize().width - width + 55.0f);
    menu->addChild(infoBtn);

    auto resetBtnSpr = CCSprite::createWithSpriteFrameName("geode.loader/reset-gold.png");
    resetBtnSpr->setScale(0.5f);
    m_resetBtn = CCMenuItemExt::createSpriteExtra(resetBtnSpr, [this](auto) {
        createQuickPopup("Reset", "Are you sure you want to <cr>reset</c> <cl>Randomize Button Color</c> to <cy>default</c>?", "Cancel", "Reset",
            [this](auto, bool btn2) { if (btn2) resetToDefault(); });
    });
    m_resetBtn->setPositionX(m_nameLabel->getScaledContentSize().width - width + 75.0f);
    menu->addChild(m_resetBtn);

    auto bgSprite = CCScale9Sprite::create("square02b_001.png", { 0.0f, 0.0f, 80.0f, 80.0f });
    bgSprite->setScale(0.325f);
    bgSprite->setColor({ 0, 0, 0 });
    bgSprite->setOpacity(75);
    bgSprite->setContentSize({ width - 140.0f, 60.0f });
    bgSprite->setPositionX(35.0f - width * 0.25f);
    menu->addChild(bgSprite);

    m_label = CCLabelBMFont::create("", "chatFont.fnt");
    m_label->setScale(0.39f);
    m_label->setPositionX(35.0f - width * 0.25f);
    menu->addChild(m_label);

    auto decArrowSpr = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
    decArrowSpr->setFlipX(true);
    decArrowSpr->setScale(0.3f);
    auto decArrow = CCMenuItemExt::createSpriteExtra(decArrowSpr, [this](auto) {
        m_uncommittedValue -= 1;
        if (m_uncommittedValue < 0) m_uncommittedValue = 7;
        valueChanged();
    });
    decArrow->setPositionX(80.0f - width * 0.5f);
    menu->addChild(decArrow);

    auto incArrowSpr = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
    incArrowSpr->setScale(0.3f);
    auto incArrow = CCMenuItemExt::createSpriteExtra(incArrowSpr, [this](auto) {
        m_uncommittedValue += 1;
        if (m_uncommittedValue > 7) m_uncommittedValue = 0;
        valueChanged();
    });
    incArrow->setPositionX(-10.f);
    menu->addChild(incArrow);

    menu->setTouchEnabled(true);
    valueChanged();
    return true;
}

void ButtonColorSettingNode::valueChanged() {
    if (hasUncommittedChanges()) m_nameLabel->setColor({ 17, 221, 0 });
    else m_nameLabel->setColor({ 255, 255, 255 });
    m_resetBtn->setVisible(hasNonDefaultValue());
    dispatchChanged();
    auto buttonColor = static_cast<ButtonColor>(m_uncommittedValue);
    if (buttonColor != ButtonColor::Random) {
        auto fontSprites = reinterpret_cast<CCSprite**>(m_label->getChildren()->data->arr);
        for (int i = 0; i < m_label->getChildrenCount(); i++) {
            fontSprites[i]->setColor({ 255, 255, 255 });
        }
    }
    switch (buttonColor) {
        case ButtonColor::Random: {
            m_label->setString("Random");
            m_label->setColor({ 255, 255, 255 });
            auto fontSprites = reinterpret_cast<CCSprite**>(m_label->getChildren()->data->arr);
            fontSprites[0]->setColor({ 255, 0, 0 });
            fontSprites[1]->setColor({ 255, 127, 0 });
            fontSprites[2]->setColor({ 255, 255, 0 });
            fontSprites[3]->setColor({ 0, 255, 0 });
            fontSprites[4]->setColor({ 0, 0, 255 });
            fontSprites[5]->setColor({ 127, 0, 255 });
            break;
        }
        case ButtonColor::Green:
            m_label->setString("Green");
            m_label->setColor({ 102, 204, 17 });
            break;
        case ButtonColor::Pink:
            m_label->setString("Pink");
            m_label->setColor({ 255, 113, 255 });
            break;
        case ButtonColor::Blue:
            m_label->setString("Blue");
            m_label->setColor({ 10, 180, 255 });
            break;
        case ButtonColor::Cyan:
            m_label->setString("Cyan");
            m_label->setColor({ 19, 213, 234 });
            break;
        case ButtonColor::Gray:
            m_label->setString("Gray");
            m_label->setColor({ 151, 153, 151 });
            break;
        case ButtonColor::DarkPurple:
            m_label->setString("Dark Purple");
            m_label->setColor({ 47, 41, 55 });
            break;
        case ButtonColor::DarkAqua:
            m_label->setString("Dark Aqua");
            m_label->setColor({ 31, 52, 65 });
            break;
        default:
            m_label->setString("Unknown");
            m_label->setColor({ 255, 255, 255 });
            break;
    }
}

void ButtonColorSettingNode::commit() {
    auto settingValue = static_cast<ButtonColorSettingValue*>(m_value);
    settingValue->setValue(static_cast<ButtonColor>(m_uncommittedValue));
    ButtonColorSettingValue::BUTTON_COLOR = settingValue->getValue();
    valueChanged();
    dispatchCommitted();
}

bool ButtonColorSettingNode::hasUncommittedChanges() {
    return static_cast<ButtonColor>(m_uncommittedValue) != static_cast<ButtonColorSettingValue*>(m_value)->getValue();
}

bool ButtonColorSettingNode::hasNonDefaultValue() {
    return static_cast<ButtonColor>(m_uncommittedValue) != ButtonColor::Random;
}

void ButtonColorSettingNode::resetToDefault() {
    m_uncommittedValue = 0;
    valueChanged();
}

ButtonColor SettingValueSetter<ButtonColor>::get(SettingValue* setting) {
    return static_cast<ButtonColorSettingValue*>(setting)->getValue();
}

void SettingValueSetter<ButtonColor>::set(SettingValue* setting, ButtonColor const& value) {
    static_cast<ButtonColorSettingValue*>(setting)->setValue(value);
}
