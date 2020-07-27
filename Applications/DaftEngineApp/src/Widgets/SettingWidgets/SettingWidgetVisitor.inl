namespace daft::app {
template <typename D>
TransformSettings* SettingWidgetVisitor::getTransforms(D* drawable) {
    daft::core::mat::SettingManager settings;
    settings.add("Position", drawable->position());
    settings.add("Rotations", drawable->rotations());
    settings.add("Scale", drawable->scale());
    return new TransformSettings(settings);
}
}  // namespace daft::app