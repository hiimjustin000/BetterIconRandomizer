#include <Geode/Geode.hpp>

using namespace geode::prelude;

class BetterIconRandomizer {
public:
    inline static std::map<UnlockType, std::vector<int>> unlocked = {
        { UnlockType::Cube, {} },
        { UnlockType::Col1, {} },
        { UnlockType::Col2, {} },
        { UnlockType::Ship, {} },
        { UnlockType::Ball, {} },
        { UnlockType::Bird, {} },
        { UnlockType::Dart, {} },
        { UnlockType::Robot, {} },
        { UnlockType::Spider, {} },
        { UnlockType::Streak, {} },
        { UnlockType::Death, {} },
        { UnlockType::Swing, {} },
        { UnlockType::Jetpack, {} },
        { UnlockType::ShipFire, {} }
    };

    static int randomNumber(int, int);
    static void setupUnlocked();
    static UnlockType iconTypeToUnlockType(IconType);
    static void setupUnlockedIcons(int, IconType);
    static void setupUnlockedColors(UnlockType);
    static int randomize(UnlockType, bool);
};
