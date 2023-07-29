#ifndef SIMPLE_OJ_H
#define SIMPLE_OJ_H

#include <string>

namespace oj {

class SimpleOJ {
public:
    SimpleOJ();
    ~SimpleOJ();
    bool compileUserCode(const std::string& language);
    bool runUserCode(const std::string& expectedOutputFileName);
    void run();

private:
    std::string sourceCode;
    std::string m_language;
    std::string codeFileName;
    std::string inputFileName;
    std::string expectedOutputFileName;
    bool enforceSecurityLimits();
    bool enforceSecurityLimitsWrapper(); // Helper function to access enforceSecurityLimits
};

} // namespace oj

#endif // SIMPLE_OJ_H
