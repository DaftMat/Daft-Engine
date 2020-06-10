namespace ProjName::Core::Utils {

template <int M, int N, typename T>
inline glm::mat<M, N, T> toGlm(const Eigen::Matrix<T, M, N> &mat) {
    glm::mat<M, N, T> ret;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            ret[i][j] = mat(i, j);
        }
    }
    return ret;
}

template <int M, typename T>
inline glm::vec<M, T> toGlm(const Eigen::Matrix<T, M, 1> &vec) {
    glm::vec<M, T> ret;
    for (int i = 0; i < M; ++i) {
        ret[i] = vec(i);
    }
    return ret;
}

template <int M, int N, typename T>
inline Eigen::Matrix<T, M, N> toEigen(const glm::mat<M, N, T> &mat) {
    Eigen::Matrix<T, M, N> ret;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            ret(i, j) = mat[j][i];
        }
    }
    return ret;
}

template <int M, typename T>
inline Eigen::Matrix<T, M, 1> toEigen(const glm::vec<M, T> &vec) {
    Eigen::Matrix<T, M, 1> ret;
    for (int i = 0; i < M; ++i) {
        ret(i) = vec[i];
    }
    return ret;
}

}  // namespace ProjName::Core::Utils