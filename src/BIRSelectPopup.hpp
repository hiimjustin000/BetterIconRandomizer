#include "ButtonColor.hpp"

class BIRSelectPopup : public Popup<> {
public:
    GJGarageLayer* m_garageLayer;
    Ref<CCArray> m_iconToggles;
    Ref<CCArray> m_specialToggles;
    Ref<CCArray> m_colorToggles;
    CCMenuItemToggler* m_allIconsToggler;
    CCMenuItemToggler* m_allSpecialsToggler;
    CCMenuItemToggler* m_allColorsToggler;

    static BIRSelectPopup* create();
    bool setup() override;
    CCMenuItemToggler* createIconToggle(const char*, float);
    CCMenuItemToggler* createColorToggle(const char*, float, int);
    CCMenuItemToggler* createAllToggle(const char*, float, SEL_MenuHandler);
    void randomize(UnlockType, bool);
    void onRandomize(CCObject*);
    void onIconToggle(CCObject*);
    void onAllIconsToggle(CCObject*);
    void onSpecialToggle(CCObject*);
    void onAllSpecialsToggle(CCObject*);
    void onColorToggle(CCObject*);
    void onAllColorsToggle(CCObject*);
};
