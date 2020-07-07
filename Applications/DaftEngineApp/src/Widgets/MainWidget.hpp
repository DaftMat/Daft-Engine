//
// Created by mathis on 06/07/2020.
//
#pragma once

#include <Layouts/BorderLayout.hpp>
#include <QtWidgets/QWidget>

#include "OpenGLWidget.hpp"

QT_BEGIN_NAMESPACE
class QLabel;
class QSpacerItem;
QT_END_NAMESPACE

class MainWidget : public QWidget {
    Q_OBJECT

   public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget() override;

    OpenGLWidget &glWidget() { return *m_glWidget; }
    [[nodiscard]] const OpenGLWidget &glWidget() const { return *m_glWidget; }

    BorderLayout &borderLayout() { return *m_layout; }
    [[nodiscard]] const BorderLayout &borderLayout() const { return *m_layout; }

   private:
    std::unique_ptr<OpenGLWidget> m_glWidget{nullptr};
    std::unique_ptr<BorderLayout> m_layout{nullptr};

    [[nodiscard]] static QLabel *createLabel(const QString &text);
    [[nodiscard]] static QSpacerItem *createHSpacer(int vsize = 20);
    [[nodiscard]] static QSpacerItem *createVSpacer(int hsize = 20);
};
