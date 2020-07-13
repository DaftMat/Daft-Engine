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
/**
 * This class is the base class for the widget going to north, south, east or west region of a BorderLayout.
 */
class ENGINE_API BorderWidget : public QWidget {
   public:
    /**
     * Chose between vertical or horizontal layout.
     */
    enum class Orientation {
        VERTICAL,   ///< for west and east regions.
        HORIZONTAL  ///< for north and south regions.
    };

    /**
     * Standard constructor.
     * @param orientation - Orientation of the widget.
     * @param minSize - minimum size of the widget.
     * @param maxSize - maximum size of the widget.
     * @param parent - parent of the widget.
     */
    explicit BorderWidget(Orientation orientation, int minSize = 30, int maxSize = 70, QWidget *parent = nullptr);

    /**
     * Adds a widget in this widget.
     * @param w - widget to add
     */
    void addWidget(QWidget *w) { m_layout->addWidget(w); }

    /**
     * Adds a separator to this widget.
     * Horizontal line for a vertical widget,
     * vertical line for a horizontal widget.
     */
    void addSeparator();

    /**
     * Adds a spacer to this widget.
     */
    void addSpacer();

   private:
    Orientation m_orientation;
    std::unique_ptr<QLayout> m_layout{nullptr};
};
}  // namespace daft::app