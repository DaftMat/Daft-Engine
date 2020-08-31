namespace daft::core {

template <int M, int N, typename T>
constexpr glm::mat<M, N, T> toGlm(const Eigen::Matrix<T, M, N, 0, M, N> &mat) noexcept {
    glm::mat<M, N, T> ret;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            ret[i][j] = mat(i, j);
        }
    }
    return ret;
}

template <int M, typename T>
constexpr glm::vec<M, T> toGlm(const Eigen::Matrix<T, M, 1, 0, M, 1> &vec) noexcept {
    glm::vec<M, T> ret;
    for (int i = 0; i < M; ++i) {
        ret[i] = vec(i);
    }
    return ret;
}

template <int M, int N, typename T>
constexpr Eigen::Matrix<T, M, N> toEigen(const glm::mat<M, N, T> &mat) noexcept {
    Eigen::Matrix<T, M, N> ret;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            ret(i, j) = mat[j][i];
        }
    }
    return ret;
}

template <int M, typename T>
constexpr Eigen::Matrix<T, M, 1> toEigen(const glm::vec<M, T> &vec) noexcept {
    Eigen::Matrix<T, M, 1> ret;
    for (int i = 0; i < M; ++i) {
        ret(i) = vec[i];
    }
    return ret;
}

template <typename T>
constexpr auto toUType(T e) noexcept {
    return static_cast<std::underlying_type_t<T>>(e);
}

constexpr GLuint mod1(GLuint x, GLuint m) noexcept { return m == x ? x : x % m; }

}  // namespace daft::core