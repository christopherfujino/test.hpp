#include <string>
#include <vector>
#include "test.hpp"

using namespace _CHRIS_MONOREPO_CPP_TEST;

static std::vector<Test> tests = {
    {"should pass", []() { expect(1, 1); }},
    {"should fail", []() { expect(1, 2); }},
};

int main() { return Runner(tests).run(); }
