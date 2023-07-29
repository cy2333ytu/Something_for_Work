#ifndef DIFFICULTY_SELECTOR_H
#define DIFFICULTY_SELECTOR_H

#include <string>

namespace oj {

class DifficultySelector {
public:
    static int selectDifficulty();
    static std::pair<std::string, std::string> getTestFiles(int difficulty);
};

} // namespace oj

#endif // DIFFICULTY_SELECTOR_H
