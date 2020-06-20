//
// Created by mathis on 10/06/2020.
//
#pragma once
#include <API.hpp>

#include "Types.hpp"

/**
 * This files provides casting function between glm and Eigen.
 */
namespace ProjName::Core::Utils {

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

}  // namespace ProjName::Core::Utils

#include "Adapters.inl"