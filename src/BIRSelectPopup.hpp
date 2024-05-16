#include "ButtonColor.hpp"

class BIRSelectPopup : public Popup<> {
public:
    GJGarageLayer* m_garageLayer;
protected:
    CCArray* m_iconToggles;
    CCArray* m_specialToggles;
    CCArray* m_colorToggles;
    CCMenuItemToggler* m_allIconsToggler;
    CCMenuItemToggler* m_allSpecialsToggler;
    CCMenuItemToggler* m_allColorsToggler;
    CCMenu* m_iconMenu;
    CCMenu* m_colorMenu;
    CCMenu* m_allMenu;

    bool setup() override;
    CCMenuItemToggler* createIconToggle(const char*);
    CCMenuItemToggler* createColorToggle(const char*, int);
    CCMenuItemToggler* createAllToggle(SEL_MenuHandler);
    CCLabelBMFont* createAllLabel(const char*, CCMenuItemToggler*);
    void onToggle(CCArray*, CCMenuItemToggler*, CCMenuItemToggler*);
    void onAllToggle(CCArray*, CCMenuItemToggler*);
public:
    static BIRSelectPopup* create();

    void onIconToggle(CCObject*);
    void onAllIconsToggle(CCObject*);
    void onSpecialToggle(CCObject*);
    void onAllSpecialsToggle(CCObject*);
    void onColorToggle(CCObject*);
    void onAllColorsToggle(CCObject*);
    void onRandomize(CCObject*);

    ~BIRSelectPopup();
};
