//
// Created by mathis on 12/06/2020.
//
#pragma once

#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

#define DEFAULT_REPEAT 10

#define PP_MAKE_STRING2(S) #S
#define PP_MAKE_STRING(S) PP_MAKE_STRING2(S)

namespace stardust::testing {

static std::vector<std::string> g_test_stack;
static int g_repeat;
static unsigned int g_seed;
static bool g_has_set_repeat, g_has_set_seed;

void verify_impl(bool condition, const char* testname, const char* file, int line, const char* condition_as_string) {
    if (!condition) {
        std::cerr << "Test " << testname << " failed in " << file << " (" << line << ")" << std::endl
                  << "    " << condition_as_string << std::endl;
        abort();
    }
}

template <typename S>
inline bool isApprox(const S& lhs, const S& rhs) {
    return almost_equals(lhs, rhs);
}

#define UNIT_VERIFY(a, DESC)                                                                              \
    stardust::testing::verify_impl(a, stardust::testing::g_test_stack.back().c_str(), __FILE__, __LINE__, \
                                   DESC)  // PP_MAKE_STRING(a))

#if defined(_MSC_VER) && !defined(__INTEL_COMPILER)
#define MYPRAGMA(X) __pragma(X)
#else
#define MYPRAGMA(X) _Pragma(X)
#endif

#define CALL_SUBTEST(FUNC)                                                                               \
    do {                                                                                                 \
        MYPRAGMA("omp critical") { stardust::testing::g_test_stack.emplace_back(PP_MAKE_STRING(FUNC)); } \
        FUNC;                                                                                            \
        MYPRAGMA("omp critical") { stardust::testing::g_test_stack.pop_back(); }                         \
    } while (0)

inline void set_repeat_from_string(const char* str) {
    errno = 0;
    g_repeat = int(strtoul(str, 0, 10));
    if (errno || g_repeat <= 0) {
        std::cout << "Invalid repeat value " << str << std::endl;
        exit(EXIT_FAILURE);
    }
    g_has_set_repeat = true;
}

inline void set_seed_from_string(const char* str) {
    errno = 0;
    g_seed = int(strtoul(str, 0, 10));
    if (errno || g_seed == 0) {
        std::cout << "Invalid seed value " << str << std::endl;
        exit(EXIT_FAILURE);
    }
    g_has_set_seed = true;
}

static bool init_testing(int argc, const char* argv[]) {
    g_has_set_repeat = false;
    g_has_set_seed = false;
    bool need_help = false;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == 'r') {
            if (g_has_set_repeat) {
                std::cout << "Argument " << argv[i] << " conflicting with a former argument" << std::endl;
                return 1;
            }
            set_repeat_from_string(argv[i] + 1);
        } else if (argv[i][0] == 's') {
            if (g_has_set_seed) {
                std::cout << "Argument " << argv[i] << " conflicting with a former argument" << std::endl;
                return false;
            }
            set_seed_from_string(argv[i] + 1);
        } else {
            need_help = true;
        }
    }

    if (need_help) {
        std::cout << "This test application takes the following optional arguments:" << std::endl;
        std::cout << "  rN     Repeat each test N times (default: " << DEFAULT_REPEAT << ")" << std::endl;
        std::cout << "  sN     Use N as seed for random numbers (default: based on current time)" << std::endl;
        std::cout << std::endl;
        std::cout << "If defined, the environment variables REPEAT and SEED" << std::endl;
        std::cout << "will be used as default values for these parameters." << std::endl;
        return false;
    }

    char* env_REPEAT = getenv("REPEAT");
    if (!g_has_set_repeat && env_REPEAT) set_repeat_from_string(env_REPEAT);
    char* env_SEED = getenv("SEED");
    if (!g_has_set_seed && env_SEED) set_seed_from_string(env_SEED);

    if (!g_has_set_seed) g_seed = (unsigned int)time(nullptr);
    if (!g_has_set_repeat) g_repeat = DEFAULT_REPEAT;

    std::cout << "Initializing random number generator with seed " << g_seed << std::endl;
    std::stringstream ss;
    ss << "Seed: " << g_seed;
    g_test_stack.emplace_back(ss.str());
    srand(g_seed);
    std::cout << "Repeating each test " << g_repeat << " times" << std::endl;

    return true;
}

}  // namespace stardust::testing