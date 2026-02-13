#pragma once

#include <cstdio>

// we should be testing for __cpp_lib_format, but
// https://github.com/llvm/llvm-project/issues/77773 with -std=c++20
#if __cplusplus < 202002L
#error "the test.hpp library requires C++ >= 20"
#else
#include <format>
#endif

#include <functional>
#include <stdexcept>
#include <string>
#include <type_traits> // for is_same
#include <vector>

namespace _CHRIS_MONOREPO_CPP_TEST {

typedef std::function<void()> VoidFunc;

template <typename T> inline void expect(T first, T second) {
  if (first == second) {
    return;
  }

  std::string msg;
  if constexpr (std::is_same<T, std::string>::value) {
    msg = std::format("`{}` != `{}`", first, second);
  } else {
    msg = std::format("`{}` != `{}`", std::to_string(first),
                                  std::to_string(second));
    throw std::runtime_error("nay");
  }
  throw std::runtime_error(msg);
}

template <> inline void expect(std::string first, std::string second) {
  if (first == second) {
    return;
  }
  std::string msg = std::format("`{}` != `{}`", first, second);
  throw std::runtime_error(msg);
}

class Test {
public:
  Test(std::string n, VoidFunc t) : test(t), name(n) {}
  std::function<void()> test;
  std::string name;
};

class Runner {
public:
  Runner(std::vector<Test> tests) : tests(tests) { printf("Running tests: "); }
  ~Runner() {
    size_t total = tests.size();
    printf("\n\n%ld out of %ld tests passed.\n", total - failures, total);
  }

  inline int run() {
    for (size_t i = 0; i < tests.size(); i++) {
      try {
        tests[i].test();
        printf("\u2713");
      } catch (const std::runtime_error &e) {
        fprintf(stderr, "[Failure] %s => %s\n", tests[i].name.data(), e.what());
        printf("\u2717");
        failures++;
      }
    }
    return failures == 0 ? 0 : 1;
  }

private:
  std::vector<Test> tests;
  int failures = 0;
};

} // namespace _CHRIS_MONOREPO_CPP_TEST
