namespace ProjName::Core::Utils {

template <int M, int N, typename T>
inline constexpr glm::mat<M, N, T> toGlm(const Eigen::Matrix<T, M, N> &mat) noexcept {
    glm::mat<M, N, T> ret;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            ret[i][j] = mat(i, j);
        }
    }
    return ret;
}

template <int M, typename T>
inline constexpr glm::vec<M, T> toGlm(const Eigen::Matrix<T, M, 1> &vec) noexcept {
    glm::vec<M, T> ret;
    for (int i = 0; i < M; ++i) {
        ret[i] = vec(i);
    }
    return ret;
}

template <int M, int N, typename T>
inline constexpr Eigen::Matrix<T, M, N> toEigen(const glm::mat<M, N, T> &mat) noexcept {
    Eigen::Matrix<T, M, N> ret;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            ret(i, j) = mat[j][i];
        }
    }
    return ret;
}

template <int M, typename T>
inline constexpr Eigen::Matrix<T, M, 1> toEigen(const glm::vec<M, T> &vec) noexcept {
    Eigen::Matrix<T, M, 1> ret;
    for (int i = 0; i < M; ++i) {
        ret(i) = vec[i];
    }
    return ret;
}

template <typename T>
inline constexpr auto toUType(T e) noexcept {
    return static_cast<std::underlying_type_t<T>>(e);
}

}  // namespace ProjName::Core::Utils