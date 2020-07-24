//
// Created by mathis on 06/07/2020.
//
#pragma once

#include <Layouts/BorderLayout.hpp>
#include <QFrame>
#include <QtWidgets/QWidget>

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

   public:
    /**
     * Creates a label with frame styles.
     * @param text - text of the label.
     * @return created QLabel .
     */
    [[nodiscard]] static QLabel *createLabel(const QString &text);

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
    [[nodiscard]] static QDoubleSpinBox *createDoubleSpinBox(double val = 1.0, double min = 0.0, double max = 9999.0,
                                                             double step = 1.0, int decs = 2);

   private:
    std::unique_ptr<OpenGLWidget> m_glWidget{nullptr};
    std::unique_ptr<BorderLayout> m_layout{nullptr};
};
}  // namespace daft::app