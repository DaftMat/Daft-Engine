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

    explicit BorderWidget(Orientation orientation, int minSize = 30, int maxSize = 70, QWidget *parent = nullptr);

    void addWidget(QWidget *w) { m_layout->addWidget(w); }

    void addSeparator();

    void addSpacer();

   private:
    Orientation m_orientation;
    std::unique_ptr<QLayout> m_layout{nullptr};
};
}  // namespace daft::app