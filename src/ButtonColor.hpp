#include <Geode/loader/SettingNode.hpp>
#include "BetterIconRandomizer.hpp"

enum class ButtonColor {
    Random,
    Green,
    Pink,
    Blue,
    Cyan,
    Gray,
    DarkPurple,
    DarkAqua
};

class ButtonColorSettingValue : public SettingValue {
protected:
    ButtonColor m_value = ButtonColor::Random;
public:
    inline static ButtonColor BUTTON_COLOR = ButtonColor::Random;

    ButtonColorSettingValue(std::string const& key, std::string const& modID, ButtonColor value) : SettingValue(key, modID), m_value(value) {}
    bool load(matjson::Value const& json) override;
    bool save(matjson::Value& json) const override;
    SettingNode* createNode(float width) override;
    ButtonColor getValue() const;
    void setValue(ButtonColor value);
};

class ButtonColorSettingNode : public SettingNode {
protected:
    int m_uncommittedValue;
    CCLabelBMFont* m_nameLabel;
    CCMenuItemSpriteExtra* m_resetBtn;
    CCLabelBMFont* m_label;
    CCMenuItemSpriteExtra* m_decArrow;
    CCMenuItemSpriteExtra* m_incArrow;

    bool init(ButtonColorSettingValue* value, float width);
public:
    static ButtonColorSettingNode* create(ButtonColorSettingValue* value, float width);
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
