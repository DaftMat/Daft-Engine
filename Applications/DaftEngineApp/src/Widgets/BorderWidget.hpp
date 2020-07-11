//
// Created by mathis on 10/07/2020.
//
#pragma once
#include <API.hpp>
#include <QLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QWidget>
#include <memory>

QT_BEGIN_NAMESPACE
class QSpacerItem;
QT_END_NAMESPACE

namespace daft::app {
class ENGINE_API BorderWidget : public QWidget {
   public:
    /**
     * Chose between vertical or horizontal layout.
     */
    enum class Orientation {
        VERTICAL,   ///< for west and est regions.
        HORIZONTAL  ///< for north and south regions.
    };

    explicit BorderWidget(Orientation orientation, int minSize = 70, QWidget *parent = nullptr);

    void addWidget(QWidget *w) { m_layout->addWidget(w); }

    void addSeparator();

    void addSpacer();

   private:
    [[nodiscard]] static QFrame *createLine(QFrame::Shape shape);

    [[nodiscard]] static QSpacerItem *createHSpacer(int size = 20);
    [[nodiscard]] static QSpacerItem *createVSpacer(int size = 20);

    Orientation m_orientation;
    std::unique_ptr<QLayout> m_layout{nullptr};
};
}  // namespace daft::app