#include "test.hpp"
#include <string>
#include <vector>

using namespace _CHRIS_MONOREPO_CPP_TEST;

static std::vector<Test> tests = {
    {"should pass", []() { expect(1, 1); }},
    {"should fail", []() { expect(1, 2); }},
    {"should fail compare strings",
     []() {
       auto s1 = std::string("ONE");
       auto s2 = std::string("0N3");
       expect(s1, s2);
     }},
};

int main() { return Runner(tests).run(); }
