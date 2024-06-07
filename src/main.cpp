#include "BIRSelectPopup.hpp"

$on_mod(Loaded) {
    Mod::get()->addCustomSetting<ButtonColorSettingValue>("randomize-button-color", ButtonColor::Random);
}

#include <Geode/modify/GJGarageLayer.hpp>
class $modify(BIRGarageLayer, GJGarageLayer) {
    bool init() override {
        if (!GJGarageLayer::init()) return false;

        if (ButtonColorSettingValue::randomColor == ButtonColor::Random) {
            auto color = Mod::get()->getSettingValue<ButtonColor>("randomize-button-color");
            ButtonColorSettingValue::randomColor = color == ButtonColor::Random ? static_cast<ButtonColor>(BetterIconRandomizer::randomNumber(1, 5)) : color;
        }

        auto randomizeBtn = CCMenuItemExt::createSpriteExtra(CCSprite::createWithSpriteFrameName(Mod::get()->expandSpriteName(fmt::format("BIR_randomBtn_{:02d}_001.png",
            static_cast<int>(ButtonColorSettingValue::randomColor)).c_str())), [this](auto) { BIRSelectPopup::create(this)->show(); });
        randomizeBtn->setID("select-randomize-button"_spr);
        auto shardsMenu = getChildByID("shards-menu");
        shardsMenu->addChild(randomizeBtn);
        shardsMenu->updateLayout();

        BetterIconRandomizer::setupUnlocked();
        return true;
    }
};
