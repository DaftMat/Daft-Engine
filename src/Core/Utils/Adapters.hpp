//
// Created by mathis on 10/06/2020.
//
#pragma once
#include <API.hpp>

#include "Types.hpp"

/**
 * This files provides casting function between glm and Eigen.
 */
namespace daft::core {

/**
 * Casts from Eigen::Matrix to glm::mat.
 * @tparam M - number of rows of the matrix.
 * @tparam N - number of columns of the matrix.
 * @tparam T - type of the elements in the matrix.
 * @param mat - Eigen::Matrix to be casted.
 * @return matrix as a glm::mat.
 */
template <int M, int N, typename T>
constexpr glm::mat<M, N, T> toGlm(const Eigen::Matrix<T, M, N, 0, M, N> &mat) noexcept;

/**
 * Casts from Eigen::Vector to glm::vec.
 * @tparam M - number of elements of the vector
 * @tparam T - type of the elements in the vector.
 * @param vec - Eigen::Vector to be casted.
 * @return vector as a glm::vec.
 */
template <int M, typename T>
constexpr glm::vec<M, T> toGlm(const Eigen::Matrix<T, M, 1, 0, M, 1> &vec) noexcept;

/**
 * Casts from glm::mat to Eigen::Matrix.
 * @tparam M - number of rows of the matrix.
 * @tparam N - number of columns of the matrix.
 * @tparam T - type of the elements in the matrix.
 * @param mat - glm::mat to be casted.
 * @return matrix as an Eigen::Matrix.
 */
template <int M, int N, typename T>
constexpr Eigen::Matrix<T, M, N> toEigen(const glm::mat<M, N, T> &mat) noexcept;

/**
 * Casts from glm::vec to Eigen::Vector.
 * @tparam M - number of elements of the vector.
 * @tparam T - type of the elements in the vector.
 * @param vec - glm::vec to be casted.
 * @return vector as an Eigen::Vector.
 */
template <int M, typename T>
constexpr Eigen::Matrix<T, M, 1> toEigen(const glm::vec<M, T> &vec) noexcept;

/**
 * Casts any scoped enum value to any underlying type.
 * @tparam T - underlying type.
 * @param e - enum value.
 * @return enum value with type T.
 */
template <typename T>
constexpr auto toUType(T e) noexcept;

/**
 * apply the mod operator + 1
 * @param x - first operand
 * @param m - second operand
 * @return (x % m) + 1
 */
constexpr int mod1(int x, int m) noexcept;

/**
 * Calculates the tangent and bi-tangent using the normal
 * @param n - normal
 * @param u - tangent
 * @param v - bi-tangent
 */
void orthoVectors(glm::vec3 n, glm::vec3 &u, glm::vec3 &v);

/**
 * Calculates a linear interpolation.
 * @tparam T - genType.
 * @param a - first operand.
 * @param b - second operand.
 * @param u - factor.
 * @return interpolation between a and b, using u.
 */
template <typename T>
constexpr T lerp(T a, T b, float u);

/**
 * Return the x y z world axis.
 * @return xyz.
 */
std::vector<glm::vec3> axis();

/**
 * Map a value to range 0-1 given its initial range.
 * @tparam T - genType.
 * @param umin - minimum value.
 * @param umax - maximum value.
 * @param u - value to map.
 * @return mapped value.
 */
template <typename T>
constexpr T toPercent(T umin, T umax, T u) {
    return (u - umin) / (umax - umin);
}

/**
 * Map a value to its initial range.
 * @tparam T - genType
 * @param umin - minimum value.
 * @param umax - maximum value.
 * @param u - value to map.
 * @return initial value.
 */
template <typename T>
constexpr T toValue(T umin, T umax, T u) {
    return umin + u * (umax - umin);
}

}  // namespace daft::core

#include "Adapters.inl"