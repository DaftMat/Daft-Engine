//
// Created by mathis on 06/07/2020.
//
#pragma once

#include <Engine/Drawables/Object/Sphere.hpp>
#include <Layouts/BorderLayout.hpp>
#include <QFrame>
#include <QtWidgets/QWidget>
#include <src/Widgets/SettingWidgets/SettingWidget.hpp>
#include <src/Widgets/TreeWidget/TreeWidget.hpp>

#include "BorderWidget.hpp"
#include "OpenGLWidget.hpp"

QT_BEGIN_NAMESPACE
class QLabel;
class QSpacerItem;
class QDoubleSpinBox;
QT_END_NAMESPACE

namespace daft::app {
class ENGINE_API MainWidget : public QWidget {
    Q_OBJECT

   public:
    /**
     * Standard and default constructor.
     * @param parent - parent of the widget.
     */
    explicit MainWidget(QWidget *parent = nullptr);

    /**
     * Destructor.
     */
    ~MainWidget() override;

    /**
     * OpenGLWidget reference.
     * @return ref to glWidget.
     */
    OpenGLWidget &glWidget() { return *m_glWidget; }

    /**
     * OpenGLWidget constant reference.
     * @return const ref to glWidget.
     */
    [[nodiscard]] const OpenGLWidget &glWidget() const { return *m_glWidget; }

    /**
     * BorderLayout reference.
     * @return ref to layout.
     */
    BorderLayout &borderLayout() { return *m_layout; }

    /**
     * BorderLayout constant reference.
     * @return const ref to layout.
     */
    [[nodiscard]] const BorderLayout &borderLayout() const { return *m_layout; }

    /**
     * Creates a line.
     * @param shape - shape of the line (HLine/VLine)
     * @return created line as QFrame .
     */
    [[nodiscard]] static QFrame *createLine(QFrame::Shape shape);

    /**
     * Creates a horizontal spacer.
     * @param size - minimum size of the spacer.
     * @return created QSpacerItem .
     */
    [[nodiscard]] static QSpacerItem *createHSpacer(int size = 20);

    /**
     * Creates a vertical spacer.
     * @param size - minimum size of the spacer.
     * @return created QSpacerItem .
     */
    [[nodiscard]] static QSpacerItem *createVSpacer(int size = 20);

    /**
     * Creates a QDoubleSpinBox from parameters.
     * @param val - initial value of the spin box.
     * @param min - minimal value of the spin box.
     * @param max - maximal value of the spin box.
     * @param step - step between two values in the spin box.
     * @param decs - number of printed decimals in the spin box.
     * @return created QDoubleSpinBox .
     */
    [[nodiscard]] static QDoubleSpinBox *createDoubleSpinBox(double val = 1.0, double min = -999, double max = 999,
                                                             double step = 1.0, int decs = 2);

   public slots:
    void on_selectionChanged();
    void on_settingChanged();
    void on_selectionSettingsChanged() { m_glWidget->emitNextFrame(); }
    void on_treeSelectionChanged();
    void on_treeItemChanged();
    void on_sceneTreeChanged();
    void on_glInitialized();

    void on_addGroupButtonPressed() {
        m_glWidget->addDrawable(new engine::Composite{});
        m_glWidget->update();
    }
    void on_addSphereButtonPressed() {
        m_glWidget->addDrawable(new engine::Sphere{});
        m_glWidget->update();
    }
    void on_removeButtonPressed() {
        m_glWidget->removeSelection();
        m_glWidget->update();
    }

   private:
    void connectSceneTreeEvents();

    std::unique_ptr<OpenGLWidget> m_glWidget{nullptr};
    std::unique_ptr<BorderWidget> m_southWidget{nullptr};
    std::unique_ptr<BorderWidget> m_eastWidget{nullptr};
    std::unique_ptr<SettingWidget> m_settingWidget{nullptr};
    std::unique_ptr<TreeWidget> m_treeWidget{nullptr};

    std::unique_ptr<BorderLayout> m_layout{nullptr};
};
}  // namespace daft::app