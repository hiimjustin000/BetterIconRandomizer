#include "ButtonColor.hpp"

class BIRSelectPopup : public Popup<GJGarageLayer*> {
protected:
    GJGarageLayer* m_garageLayer;
    CCArray* m_iconToggles;
    CCArray* m_specialToggles;
    CCArray* m_colorToggles;
    CCMenuItemToggler* m_allIconsToggler;
    CCMenuItemToggler* m_allSpecialsToggler;
    CCMenuItemToggler* m_allColorsToggler;
    CCMenu* m_iconMenu;
    CCMenu* m_colorMenu;
    CCMenu* m_allMenu;

    bool setup(GJGarageLayer*) override;
    CCMenuItemToggler* createIconToggle(const char*);
    CCMenuItemToggler* createColorToggle(const char*, ccColor3B);
    CCMenuItemToggler* createAllToggle(SEL_MenuHandler);
    CCLabelBMFont* createAllLabel(const char*, CCMenuItemToggler*);
    void onToggle(CCArray*, CCMenuItemToggler*, CCMenuItemToggler*);
    void onAllToggle(CCArray*, CCMenuItemToggler*);
public:
    static BIRSelectPopup* create(GJGarageLayer*);

    void onIconToggle(CCObject*);
    void onAllIconsToggle(CCObject*);
    void onSpecialToggle(CCObject*);
    void onAllSpecialsToggle(CCObject*);
    void onColorToggle(CCObject*);
    void onAllColorsToggle(CCObject*);
    void onRandomize(CCObject*);

    ~BIRSelectPopup();
};
