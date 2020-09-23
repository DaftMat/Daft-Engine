//
// Created by mathis on 12/06/2020.
//

#include <Core/Utils/Adapters.hpp>
#include <Test.hpp>
#include <algorithm>

namespace daft::testing {

void run() {
    using namespace core;
    /// toGlm
    /// Vector2
    UNIT_VERIFY(toGlm(Vector2f(1.f, 5.f)) == glm::vec2(1.f, 5.f), "toGlm fails with Vector2f");
    UNIT_VERIFY(toGlm(Vector2d(4.0, 1.0)) == glm::dvec2(4.0, 1.0), "toGlm fails with Vector2d");
    UNIT_VERIFY(toGlm(Vector2i(-7, 2)) == glm::ivec2(-7, 2), "toGlm fails with Vector2i");
    /// Vector3
    UNIT_VERIFY(toGlm(Vector3f(1.f, 5.f, 2.f)) == glm::vec3(1.f, 5.f, 2.f), "toGlm fails with Vector3f");
    UNIT_VERIFY(toGlm(Vector3d(4.0, 1.0, 8.0)) == glm::dvec3(4.0, 1.0, 8.0), "toGlm fails with Vector3d");
    UNIT_VERIFY(toGlm(Vector3i(-7, 2, -4)) == glm::ivec3(-7, 2, -4), "toGlm fails with Vector3i");
    /// Vector4
    UNIT_VERIFY(toGlm(Vector4f(1.f, 5.f, 2.f, -5.f)) == glm::vec4(1.f, 5.f, 2.f, -5.f), "toGlm fails with Vector4f");
    UNIT_VERIFY(toGlm(Vector4d(4.0, 1.0, 8.0, -7.0)) == glm::dvec4(4.0, 1.0, 8.0, -7.0), "toGlm fails with Vector4d");
    UNIT_VERIFY(toGlm(Vector4i(-7, 2, -4, 6)) == glm::ivec4(-7, 2, -4, 6), "toGlm fails with Vector4i");

    /// toEigen
    /// Vector2
    UNIT_VERIFY(Vector2f(1.f, 5.f) == toEigen(glm::vec2(1.f, 5.f)), "toEigen fails with Vector2f");
    UNIT_VERIFY(Vector2d(4.0, 1.0) == toEigen(glm::dvec2(4.0, 1.0)), "toEigen fails with Vector2d");
    UNIT_VERIFY(Vector2i(-7, 2) == toEigen(glm::ivec2(-7, 2)), "toEigen fails with Vector2i");
    /// Vector3
    UNIT_VERIFY(Vector3f(1.f, 5.f, 2.f) == toEigen(glm::vec3(1.f, 5.f, 2.f)), "toEigen fails with Vector3f");
    UNIT_VERIFY(Vector3d(4.0, 1.0, 8.0) == toEigen(glm::dvec3(4.0, 1.0, 8.0)), "toEigen fails with Vector3d");
    UNIT_VERIFY(Vector3i(-7, 2, -4) == toEigen(glm::ivec3(-7, 2, -4)), "toEigen fails with Vector3i");
    /// Vector4
    UNIT_VERIFY(Vector4f(1.f, 5.f, 2.f, -5.f) == toEigen(glm::vec4(1.f, 5.f, 2.f, -5.f)),
                "toEigen fails with Vector4f");
    UNIT_VERIFY(Vector4d(4.0, 1.0, 8.0, -7.0) == toEigen(glm::dvec4(4.0, 1.0, 8.0, -7.0)),
                "toEigen fails with Vector4d");
    UNIT_VERIFY(Vector4i(-7, 2, -4, 6) == toEigen(glm::ivec4(-7, 2, -4, 6)), "toEigen fails with Vector4i");
}

}  // namespace daft::testing

int main(int argc, const char **argv) {
    using namespace daft;
    if (!testing::init_testing(argc, argv)) {
        return EXIT_FAILURE;
    }

#pragma omp parallel for
    for (int i = 0; i < testing::g_repeat; ++i) {
        CALL_SUBTEST((testing::run()));
    }

    return EXIT_SUCCESS;
}