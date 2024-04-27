#include "ButtonColor.hpp"

CircleBaseColor ButtonColorSettingValue::toCircleBaseColor(ButtonColor color) {
    switch (color) {
        case ButtonColor::Green: return CircleBaseColor::Green;
        case ButtonColor::Pink: return CircleBaseColor::Pink;
        case ButtonColor::Blue: return CircleBaseColor::Blue;
        case ButtonColor::Cyan: return CircleBaseColor::Cyan;
        case ButtonColor::Gray: return CircleBaseColor::Gray;
        default: return CircleBaseColor::Geode;
    }
}

bool ButtonColorSettingValue::load(matjson::Value const& json) {
    if (!json.is_number()) return false;
    m_value = json.as_int() >= 0 && json.as_int() <= 5 ? static_cast<ButtonColor>(json.as_int()) : ButtonColor::Random;
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

const char* buttonColorToString(ButtonColor color) {
    switch (color) {
        case ButtonColor::Random: return "Random";
        case ButtonColor::Green: return "Green";
        case ButtonColor::Pink: return "Pink";
        case ButtonColor::Blue: return "Blue";
        case ButtonColor::Cyan: return "Cyan";
        case ButtonColor::Gray: return "Gray";
    }
    return "Unknown";
}

ButtonColorSettingNode* ButtonColorSettingNode::create(ButtonColorSettingValue* value, float width) {
    auto ret = new ButtonColorSettingNode();
    if (ret && ret->init(value, width)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool ButtonColorSettingNode::init(ButtonColorSettingValue* value, float width) {
    if (!SettingNode::init(value)) return false;
    m_value = value;

    setContentSize({ width, 40.0f });

    m_uncommittedValue = static_cast<int>(value->getValue());

    m_nameLabel = CCLabelBMFont::create("Randomize Button Color", "bigFont.fnt");
    m_nameLabel->setAnchorPoint({ 0.0f, 0.5f });
    m_nameLabel->limitLabelWidth(width / 2 - 50.0f, 0.5f, 0.1f);
    m_nameLabel->setPosition({ 20.0f, m_obContentSize.height / 2 });
    addChild(m_nameLabel);

    m_menu = CCMenu::create();
    m_menu->setPosition({ m_obContentSize.width - 20.0f, m_obContentSize.height / 2 });
    addChild(m_menu);

    auto infoSpr = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
    infoSpr->setScale(0.6f);
    auto infoBtn = CCMenuItemSpriteExtra::create(infoSpr, this, menu_selector(ButtonColorSettingNode::onDescription));
    infoBtn->setPosition(-m_obContentSize.width + 40.0f + m_nameLabel->getScaledContentSize().width + 15.0f, 0.0f);
    m_menu->addChild(infoBtn);

    auto resetBtnSpr = CCSprite::createWithSpriteFrameName("geode.loader/reset-gold.png");
    resetBtnSpr->setScale(0.5f);
    m_resetBtn = CCMenuItemSpriteExtra::create(resetBtnSpr, this, menu_selector(ButtonColorSettingNode::onReset));
    m_resetBtn->setPosition(-m_obContentSize.width + 40.0f + m_nameLabel->getScaledContentSize().width + 35.0f, 0.0f);
    m_menu->addChild(m_resetBtn);

    m_menu->setTouchEnabled(true);

    auto bgSprite = CCScale9Sprite::create("square02b_001.png", { 0.0f, 0.0f, 80.0f, 80.0f });
    bgSprite->setScale(0.5f);
    bgSprite->setColor({ 0, 0, 0 });
    bgSprite->setOpacity(75);
    bgSprite->setContentSize({ (width / 2 - 70.0f) * 2, 60.0f });
    bgSprite->setPosition(-(width / 2 - 70.0f) / 2, 0.0f);
    m_menu->addChild(bgSprite);

    m_label = CCLabelBMFont::create("", "bigFont.fnt");
    m_label->setPosition({ -(width / 2 - 70.0f) / 2, 0.0f });
    m_label->limitLabelWidth(width / 2 - 70.0f, 0.5f, 0.1f);
    m_menu->addChild(m_label);

    auto decArrowSpr = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
    decArrowSpr->setFlipX(true);
    decArrowSpr->setScale(0.3f);
    auto decArrow = CCMenuItemSpriteExtra::create(decArrowSpr, this, menu_selector(ButtonColorSettingNode::onLeftArrow));
    decArrow->setPosition(-width / 2 + 80.f, 0.0f);
    m_menu->addChild(decArrow);

    auto incArrowSpr = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
    incArrowSpr->setScale(0.3f);
    auto incArrow = CCMenuItemSpriteExtra::create(incArrowSpr, this, menu_selector(ButtonColorSettingNode::onRightArrow));
    incArrow->setPosition(-10.f, 0.0f);
    m_menu->addChild(incArrow);

    m_width = width;
    valueChanged();
    return true;
}

void ButtonColorSettingNode::onDescription(CCObject*) {
    FLAlertLayer::create("Randomize Button Color", "The color of the randomize button.", "OK")->show();
}

void ButtonColorSettingNode::onReset(CCObject*) {
    createQuickPopup("Reset", "Are you sure you want to <cr>reset</c> <cl>Randomize Button Color</c> to <cy>default</c>?", "Cancel", "Reset",
        [this](auto, bool btn2) {
            if (btn2) resetToDefault();
        });
}

void ButtonColorSettingNode::onLeftArrow(CCObject*) {
    m_uncommittedValue -= 1;
    if (m_uncommittedValue < 0) m_uncommittedValue = 5;
    valueChanged();
}

void ButtonColorSettingNode::onRightArrow(CCObject*) {
    m_uncommittedValue += 1;
    if (m_uncommittedValue > 5) m_uncommittedValue = 0;
    valueChanged();
}

void ButtonColorSettingNode::valueChanged() {
    if (hasUncommittedChanges()) m_nameLabel->setColor({ 17, 221, 0 });
    else m_nameLabel->setColor({ 255, 255, 255 });
    m_resetBtn->setVisible(hasNonDefaultValue());
    dispatchChanged();
    m_label->setString(buttonColorToString(static_cast<ButtonColor>(m_uncommittedValue)));
    m_label->limitLabelWidth(m_width / 2 - 70.0f, 0.5f, 0.1f);
}

void ButtonColorSettingNode::commit() {
    m_value->setValue(static_cast<ButtonColor>(m_uncommittedValue));
    ButtonColorSettingValue::randomColor = m_value->getValue();
    m_uncommittedValue = static_cast<int>(ButtonColorSettingValue::randomColor);
    valueChanged();
    dispatchCommitted();
}

bool ButtonColorSettingNode::hasUncommittedChanges() {
    return static_cast<ButtonColor>(m_uncommittedValue) != m_value->getValue();
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