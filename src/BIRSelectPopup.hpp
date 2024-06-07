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

    bool setup(GJGarageLayer*) override;
    void createIconToggle(const char*, const char*);
    void createSpecialToggle(const char*, const char*);
    void createColorToggle(const char*, ccColor3B);
    void onToggle(CCArray*, CCMenuItemToggler*, CCMenuItemToggler*);
    void onAllToggle(CCArray*, CCMenuItemToggler*);
public:
    static BIRSelectPopup* create(GJGarageLayer*);

    void randomize();

    ~BIRSelectPopup();
};
