#include "ButtonColor.hpp"

class BIRSelectPopup : public geode::Popup<> {
public:
    inline static std::vector<std::vector<int>> unlocked = {};

    GJGarageLayer* m_garageLayer;
    CCMenuItemToggler* m_iconToggler;
    CCMenuItemToggler* m_shipToggler;
    CCMenuItemToggler* m_ballToggler;
    CCMenuItemToggler* m_birdToggler;
    CCMenuItemToggler* m_dartToggler;
    CCMenuItemToggler* m_robotToggler;
    CCMenuItemToggler* m_spiderToggler;
    CCMenuItemToggler* m_swingToggler;
    CCMenuItemToggler* m_jetpackToggler;
    CCMenuItemToggler* m_streakToggler;
    CCMenuItemToggler* m_explosionToggler;
    CCMenuItemToggler* m_colorToggler1;
    CCMenuItemToggler* m_colorToggler2;
    CCMenuItemToggler* m_colorToggler3;

    static int randomNumber(int, int);
    static void setupUnlocked();
    static BIRSelectPopup* create();
    bool setup() override;
    void randomize(UnlockType unlockType) {
        randomize(unlockType, false);
    }
    void randomize(UnlockType, bool);
    void onRandomize(CCObject*);
    void onToggle(CCObject*) {}
};
