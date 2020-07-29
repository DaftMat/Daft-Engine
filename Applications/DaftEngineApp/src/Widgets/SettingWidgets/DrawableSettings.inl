namespace daft::app {
template <typename T>
void DrawableSettings::setVector(const T &elem) {
    for (int i = 0; i < 3; ++i) m_settings.get<glm::vec3>(elem.first)[i] = elem.second[i]->value();
}
}  // namespace daft::app