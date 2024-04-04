#include <Geode/modify/GJGarageLayer.hpp>
#include "BIRSelectPopup.hpp"

class $modify(BIRGarageLayer, GJGarageLayer) {
    bool init() override {
        if (!GJGarageLayer::init()) return false;

        auto shardsMenu = getChildByID("shards-menu");
        auto randomizeBtn = CCMenuItemSpriteExtra::create(CCSprite::create("BIR_randomBtn_001.png"_spr), this, menu_selector(BIRGarageLayer::onSelectRandomize));
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
