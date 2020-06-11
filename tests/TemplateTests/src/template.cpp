//
// Created by mathis on 12/06/2020.
//

/// your includes...
#include <Test.hpp>
#include <algorithm>

/**
 * Unit testing template file :
 * Just write the unit test you need and add the name of the file in the CMakeLists.txt of the testing dir by
 * calling the cmake function : add_test_file(fileName) (don't put the ".cpp").
 */
namespace ProjName::Testing {
/**
 * The run function : will be call by the test's main function a certain number of times (in parallel).
 *
 * - To create your own unit test directory : create a directory in "tests" from the root, for
 * example, EngineTests then create a "src" where all the test files will be created.
 * Then, add an empty CMakeLists.txt in your newly created folder
 *
 * - To create your own unit test file : create a new C++ file in the source folder of your test directory,
 * for example, EngineTest/src/renderer.cpp, copy and paste this template file, include the code you're testing,
 * and start writing yout unit tests in the run() function.
 * \attention Don't touch the main() function ! don't even look at it.
 * (you can remove those nasty comments too)
 *
 * - For a more complete example, see the directory "CoreTests" in the tests dirs.
 */
void run() {
    /// unit test example
    UNIT_VERIFY(true, "dumpy test");
    /// ...
}
}  // namespace ProjName::Testing

int main(int argc, const char **argv) {
    using namespace ProjName;
    if (!Testing::init_testing(1, argv)) {
        return EXIT_FAILURE;
    }

#pragma omp parallel for
    for (int i = 0; i < Testing::g_repeat; ++i) {
        CALL_SUBTEST((Testing::run()));
    }

    return EXIT_SUCCESS;
}