#include <Geode/Geode.hpp>

using namespace geode::prelude;

class BetterIconRandomizer {
public:
    inline static std::vector<std::vector<int>> unlocked = {};

    static int randomNumber(int, int);
    static void setupUnlocked();
    static void setupUnlockedIcons(int, IconType);
    static void setupUnlockedColors(UnlockType);
    static int randomize(UnlockType, bool);
};
