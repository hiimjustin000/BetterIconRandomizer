#include <Geode/Geode.hpp>
#include <Geode/loader/SettingNode.hpp>

using namespace geode::prelude;

enum class ButtonColor {
    Random,
    Green,
    Pink,
    Blue,
    Cyan,
    Gray
};

class ButtonColorSettingValue : public SettingValue {
    ButtonColor m_value = ButtonColor::Random;

public:
    inline static ButtonColor randomColor = ButtonColor::Random;

    ButtonColorSettingValue(std::string const& key, std::string const& modID, ButtonColor value) : SettingValue(key, modID), m_value(value) {}
    bool load(matjson::Value const& json) override;
    bool save(matjson::Value& json) const override;
    SettingNode* createNode(float width) override;
    ButtonColor getValue() const;
    void setValue(ButtonColor value);
};

class ButtonColorSettingNode : public SettingNode {
    ButtonColorSettingValue* m_value;
    int m_uncommittedValue;
    float m_width;
    CCMenu* m_menu;
    CCLabelBMFont* m_nameLabel;
    CCMenuItemSpriteExtra* m_resetBtn;
    CCLabelBMFont* m_label;
    CCMenuItemSpriteExtra* m_decArrow;
    CCMenuItemSpriteExtra* m_incArrow;

protected:
    bool init(ButtonColorSettingValue* value, float width);

public:
    static ButtonColorSettingNode* create(ButtonColorSettingValue* value, float width);
    void onDescription(CCObject*);
    void onReset(CCObject*);
    void onLeftArrow(CCObject*);
    void onRightArrow(CCObject*);
    void valueChanged();
    void commit() override;
    bool hasUncommittedChanges() override;
    bool hasNonDefaultValue() override;
    void resetToDefault() override;
};

template<>
struct SettingValueSetter<ButtonColor> {
    static ButtonColor get(SettingValue* setting);
    static void set(SettingValue* setting, ButtonColor const& value);
};
