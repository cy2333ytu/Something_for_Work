#include "SimpleOJ.h"
#include "DifficultySelector.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include <ctime>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <sys/resource.h> 
#include <future>
#include <sstream>
#include <cstdio>

namespace oj {

// 构造函数
SimpleOJ::SimpleOJ():
    sourceCode {""}, m_language {""}{

}

// 析构函数
SimpleOJ::~SimpleOJ() {
    // 在析构函数中删除临时文件 (none since we are using in-memory compilation)
}

// 函数：编译用户代码
bool SimpleOJ::compileUserCode(const std::string& language) {
    // Generate a temporary file name for the user's source code
    codeFileName = "temp_code." + language;
    
    // Save user source code to the temporary file
    std::ofstream codeFile(codeFileName);

    if (!codeFile) {
        std::cerr << "Failed to save source code." << std::endl;
        return false;
    }

    codeFile << sourceCode;
    codeFile.close();

    if (language == "cpp") {
        std::string compileCommand = "g++ -x c++ " + codeFileName + " -o temp_executable";
        int result = std::system(compileCommand.c_str());
        return (result == 0);
    } else if (language == "python") {
        // Python code does not need compilation, return true
        return true;
    } else {
        // Unsupported language type, return false
        return false;
    }
}
// 函数：执行用户代码并比较输出结果
bool SimpleOJ::runUserCode(const std::string& expectedOutputFileName) {
    // Execute user code using stdin and stdout redirection
    std::istringstream inputStream(""); // Empty input stream
    std::ostringstream outputStream; // Output stream to capture the program's output

    if (m_language == "cpp") {
        std::string executeCommand = "./temp_executable"; // Execute the compiled program
        FILE* pipe = popen(executeCommand.c_str(), "w");
        if (!pipe) {
            return false;
        }

        // Write the input to the pipe (program's stdin)
        std::string line;
        while (std::getline(inputStream, line)) {
            fputs(line.c_str(), pipe);
            fputc('\n', pipe);
        }

        // Close the input pipe
        pclose(pipe);
    } else if (m_language == "python") {
        // Python code execution using stdin and stdout redirection
        std::string executeCommand = "python"; // Python interpreter
        FILE* pipe = popen(executeCommand.c_str(), "w");
        if (!pipe) {
            return false;
        }

        // Write the input to the pipe (program's stdin)
        std::string line;
        while (std::getline(inputStream, line)) {
            fputs(line.c_str(), pipe);
            fputc('\n', pipe);
        }

        // Close the input pipe
        pclose(pipe);
    } else {
        // Unsupported language type, return false
        return false;
    }

    // Compare the actual output and the expected output
    return (outputStream.str() == expectedOutputFileName);
}

// 函数：执行安全限制（限制执行时间）
bool SimpleOJ::enforceSecurityLimits() {
    const int maxExecutionTimeInSeconds = 5; // 最大允许执行时间为5秒
    const long long maxMemoryUsageInBytes = 100 * 1024 * 1024; // 最大允许内存占用为100MB

    auto startTime = std::chrono::system_clock::now();

    while (true) {
        auto currentTime = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsedSeconds = currentTime - startTime;

        if (elapsedSeconds.count() > maxExecutionTimeInSeconds) {
            // 超过时间限制，返回 true 表示时间超限
            return true;
        }

        // 获取进程的资源使用情况
        struct rusage usage;
        getrusage(RUSAGE_SELF, &usage);

        // 获取进程的用户空间内存占用（以字节为单位）
        long long memoryUsageInBytes = usage.ru_maxrss * 1024;

        if (memoryUsageInBytes > maxMemoryUsageInBytes) {
            // 超过内存限制，返回 true 表示内存超限
            return true;
        }

        // 休眠一小段时间，避免过度消耗 CPU 时间
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return false;
}

// Helper function to run enforceSecurityLimits
bool SimpleOJ::enforceSecurityLimitsWrapper() {
    return enforceSecurityLimits();
}

// 函数：运行OJ程序
void SimpleOJ::run() {
    // 友好的用户界面
    std::cout << "Welcome to the Simple OJ!" << std::endl;

    while (true) {
        // 选择 难度
        int difficulty = DifficultySelector::selectDifficulty();
        std::pair<std::string, std::string> testFiles = DifficultySelector::getTestFiles(difficulty);
        std::string testInputFile = "test/" + testFiles.first;
        std::string expectedOutputFile = "test/" + testFiles.second;

        std::cout << "Please enter your source code (type 'end' in a new line to finish input): " << std::endl;

        // 获取用户输入的源代码和编程语言
        sourceCode = ""; // Reset the source code for each test
        std::string line;
        while (std::getline(std::cin, line) && line != "end") {
            sourceCode += line + "\n";
        }

        if (line == "end") {
            std::cout << "Please enter the programming language (cpp/python): ";
            std::getline(std::cin, m_language);
        }

        // 编译用户代码
        if (compileUserCode(m_language)) {
            // 使用 std::async 在新线程中执行安全限制（限制执行时间等）
            std::future<bool> securityFuture = std::async(std::launch::async, &SimpleOJ::enforceSecurityLimitsWrapper, this);

            // 等待安全限制检查的结果
            bool timeLimitExceeded = securityFuture.get();

            if (timeLimitExceeded) {
                std::cout << "Execution time limit exceeded!" << std::endl;
            } else {
                // 执行用户代码并比较输出结果
                if (runUserCode(expectedOutputFile)) {
                    std::cout << "Test passed!" << std::endl;
                } else {
                    std::cout << "Test failed! Please try again." << std::endl;
                }
            }
            
        } else {
            std::cout << "Compilation error!" << std::endl;
        }
    }
}

} // namespace oj
