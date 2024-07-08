#include <hiimjustin000.icon_randomizer_api/include/IconRandomizer.hpp>
#include "BIRSelectPopup.hpp"

$on_mod(Loaded) {
    Mod::get()->addCustomSetting<ButtonColorSettingValue>("randomize-button-color", ButtonColor::Random);
}

#include <Geode/modify/GJGarageLayer.hpp>
class $modify(BIRGarageLayer, GJGarageLayer) {
    bool init() override {
        if (!GJGarageLayer::init()) return false;

        if (ButtonColorSettingValue::BUTTON_COLOR == ButtonColor::Random) {
            auto color = Mod::get()->getSettingValue<ButtonColor>("randomize-button-color");
            ButtonColorSettingValue::BUTTON_COLOR = color == ButtonColor::Random ? static_cast<ButtonColor>(IconRandomizer::random(1, 7)) : color;
        }

        auto randomizeBtn = CCMenuItemExt::createSpriteExtra(CCSprite::createWithSpriteFrameName(fmt::format("BIR_randomBtn_{:02d}_001.png"_spr,
            static_cast<int>(ButtonColorSettingValue::BUTTON_COLOR)).c_str()), [this](auto) { BIRSelectPopup::create(this)->show(); });
        randomizeBtn->setID("select-randomize-button"_spr);
        auto shardsMenu = getChildByID("shards-menu");
        shardsMenu->addChild(randomizeBtn);
        shardsMenu->updateLayout();

        IconRandomizer::init();
        return true;
    }
};
