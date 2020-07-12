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
class MainWidget : public QWidget {
    Q_OBJECT

   public:
    explicit MainWidget(QWidget *parent = nullptr);

    ~MainWidget() override;

    OpenGLWidget &glWidget() { return *m_glWidget; }

    [[nodiscard]] const OpenGLWidget &glWidget() const { return *m_glWidget; }

    BorderLayout &borderLayout() { return *m_layout; }

    [[nodiscard]] const BorderLayout &borderLayout() const { return *m_layout; }

   public:
    [[nodiscard]] static QLabel *createLabel(const QString &text);

    [[nodiscard]] static QFrame *createLine(QFrame::Shape shape);

    [[nodiscard]] static QSpacerItem *createHSpacer(int size = 20);
    [[nodiscard]] static QSpacerItem *createVSpacer(int size = 20);

    [[nodiscard]] static QDoubleSpinBox *createDoubleSpinBox(double val = 1.0, double min = 0.0, double max = 9999.0,
                                                             double step = 1.0, int decs = 2);

   private:
    std::unique_ptr<OpenGLWidget> m_glWidget{nullptr};
    std::unique_ptr<BorderLayout> m_layout{nullptr};
};
}  // namespace daft::app