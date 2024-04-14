#include <Geode/modify/GJGarageLayer.hpp>
#include "BIRSelectPopup.hpp"

$on_mod(Loaded) {
    Mod::get()->addCustomSetting<ButtonColorSettingValue>("randomize-button-color", ButtonColor::Random);
}

class $modify(BIRGarageLayer, GJGarageLayer) {
    bool init() override {
        if (!GJGarageLayer::init()) return false;

        if (ButtonColorSettingValue::randomColor == ButtonColor::Random) {
            auto color = Mod::get()->getSettingValue<ButtonColor>("randomize-button-color");
            ButtonColorSettingValue::randomColor = color == ButtonColor::Random ? static_cast<ButtonColor>(BIRSelectPopup::randomNumber(1, 5)) : color;
        }

        auto shardsMenu = getChildByID("shards-menu");
        auto randomizeBtn = CCMenuItemSpriteExtra::create(
            CCSprite::create(Mod::get()->expandSpriteName(("BIR_randomBtn_00" + std::to_string(static_cast<int>(ButtonColorSettingValue::randomColor)) + ".png").c_str())),
            this,
            menu_selector(BIRGarageLayer::onSelectRandomize)
        );
        randomizeBtn->setID("select-randomize-button"_spr);
        shardsMenu->addChild(randomizeBtn);
        shardsMenu->updateLayout();

        BIRSelectPopup::setupUnlocked();

        return true;
    }

    void onSelectRandomize(CCObject*) {
        auto popup = BIRSelectPopup::create();
        popup->m_garageLayer = this;
        popup->show();
    }
};
