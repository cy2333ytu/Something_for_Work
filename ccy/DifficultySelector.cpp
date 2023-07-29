#include "DifficultySelector.h"
#include <iostream>

namespace oj {

int DifficultySelector::selectDifficulty() {
    int difficulty;

    std::cout << "Select the difficulty level:" << std::endl;
    std::cout << "1. Easy" << std::endl;
    std::cout << "2. Medium" << std::endl;
    std::cout << "3. Hard" << std::endl;
    std::cin >> difficulty;

    return difficulty;
}

std::pair<std::string, std::string> DifficultySelector::getTestFiles(int difficulty) {
    std::string testInputFile;
    std::string expectedOutputFile;

    if (difficulty == 1) {
        testInputFile = "test/test_input_easy.txt";
        expectedOutputFile = "test/expected_output_easy.txt";
    } else if (difficulty == 2) {
        testInputFile = "test/test_input_medium.txt";
        expectedOutputFile = "test/expected_output_medium.txt";
    } else if (difficulty == 3) {
        testInputFile = "test/test_input_hard.txt";
        expectedOutputFile = "test/expected_output_hard.txt";
    } else {
        std::cerr << "Invalid difficulty level." << std::endl;
        throw std::runtime_error("Invalid difficulty level.");
    }

    return std::make_pair(testInputFile, expectedOutputFile);
}

} // namespace oj
