#include <Geode/modify/GJGarageLayer.hpp>
#include "BIRSelectPopup.hpp"

CircleBaseColor toCircleBaseColor(ButtonColor color) {
    switch (color) {
        case ButtonColor::Green: return CircleBaseColor::Green;
        case ButtonColor::Pink: return CircleBaseColor::Pink;
        case ButtonColor::Blue: return CircleBaseColor::Blue;
        case ButtonColor::Cyan: return CircleBaseColor::Cyan;
        case ButtonColor::Gray: return CircleBaseColor::Gray;
        default: return CircleBaseColor::Geode;
    }
}

$on_mod(Loaded) {
    Mod::get()->addCustomSetting<ButtonColorSettingValue>("randomize-button-color", ButtonColor::Random);
}

class $modify(BIRGarageLayer, GJGarageLayer) {
    bool init() override {
        if (!GJGarageLayer::init()) return false;

        if (ButtonColorSettingValue::randomColor == ButtonColor::Random) {
            auto color = Mod::get()->getSettingValue<ButtonColor>("randomize-button-color");
            ButtonColorSettingValue::randomColor = color == ButtonColor::Random ? static_cast<ButtonColor>(BetterIconRandomizer::randomNumber(1, 5)) : color;
        }

        auto shardsMenu = getChildByID("shards-menu");
        auto buttonSprite = CircleButtonSprite::createWithSprite("BIR_randomBtn_001.png"_spr, 1.0f,
            toCircleBaseColor(ButtonColorSettingValue::randomColor), CircleBaseSize::Small);
        buttonSprite->getTopNode()->setScale(1.0f);
        auto randomizeBtn = CCMenuItemSpriteExtra::create(buttonSprite, this, menu_selector(BIRGarageLayer::onSelectRandomize));
        randomizeBtn->setID("select-randomize-button"_spr);
        shardsMenu->addChild(randomizeBtn);
        shardsMenu->updateLayout();

        BetterIconRandomizer::setupUnlocked();

        return true;
    }

    void onSelectRandomize(CCObject*) {
        auto popup = BIRSelectPopup::create();
        popup->m_garageLayer = this;
        popup->show();
    }
};
