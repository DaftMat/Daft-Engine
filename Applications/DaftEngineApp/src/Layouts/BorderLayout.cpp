//
// Created by mathis on 06/07/2020.
//
#include "BorderLayout.hpp"

BorderLayout::BorderLayout(QWidget *parent, const QMargins &margins, int spacing) : QLayout(parent) {
    setContentsMargins(margins);
    setSpacing(spacing);
}

BorderLayout::BorderLayout(int spacing) { setSpacing(spacing); }

BorderLayout::~BorderLayout() {
    QLayoutItem *l;
    while ((l = takeAt(0))) delete l;
}

void BorderLayout::addItem(QLayoutItem *item) { add(item, Position::West); }

void BorderLayout::addWidget(QWidget *widget, Position position) { add(new QWidgetItem(widget), position); }

Qt::Orientations BorderLayout::expandingDirections() const { return Qt::Horizontal | Qt::Vertical; }

bool BorderLayout::hasHeightForWidth() const { return false; }

int BorderLayout::count() const { return list.size(); }

QLayoutItem *BorderLayout::itemAt(int index) const {
    ItemWrapper *wrapper = list.value(index);
    return wrapper ? wrapper->item : nullptr;
}

QSize BorderLayout::minimumSize() const { return calculateSize(MinimumSize); }

void BorderLayout::setGeometry(const QRect &rect) {
    ItemWrapper *center = nullptr;
    int eastWidth = 0;
    int westWidth = 0;
    int northHeight = 0;
    int southHeight = 0;
    int centerHeight = 0;
    int i;

    QLayout::setGeometry(rect);

    for (i = 0; i < list.size(); ++i) {
        ItemWrapper *wrapper = list.at(i);
        QLayoutItem *item = wrapper->item;
        Position position = wrapper->position;

        if (position == Position::North) {
            item->setGeometry(QRect(rect.x(), northHeight, rect.width(), item->sizeHint().height()));

            northHeight += item->geometry().height() + spacing();
        } else if (position == Position::South) {
            item->setGeometry(
                QRect(item->geometry().x(), item->geometry().y(), rect.width(), item->sizeHint().height()));

            southHeight += item->geometry().height() + spacing();

            item->setGeometry(QRect(rect.x(), rect.y() + rect.height() - southHeight + spacing(),
                                    item->geometry().width(), item->geometry().height()));
        } else if (position == Position::Center) {
            center = wrapper;
        }
    }

    centerHeight = rect.height() - northHeight - southHeight;

    for (i = 0; i < list.size(); ++i) {
        ItemWrapper *wrapper = list.at(i);
        QLayoutItem *item = wrapper->item;
        Position position = wrapper->position;

        if (position == Position::West) {
            item->setGeometry(QRect(rect.x() + westWidth, northHeight, item->sizeHint().width(), centerHeight));

            westWidth += item->geometry().width() + spacing();
        } else if (position == Position::East) {
            item->setGeometry(
                QRect(item->geometry().x(), item->geometry().y(), item->sizeHint().width(), centerHeight));

            eastWidth += item->geometry().width() + spacing();

            item->setGeometry(QRect(rect.x() + rect.width() - eastWidth + spacing(), northHeight,
                                    item->geometry().width(), item->geometry().height()));
        }
    }

    if (center)
        center->item->setGeometry(QRect(westWidth, northHeight, rect.width() - eastWidth - westWidth, centerHeight));
}

QSize BorderLayout::sizeHint() const { return calculateSize(SizeHint); }

QLayoutItem *BorderLayout::takeAt(int index) {
    if (index >= 0 && index < list.size()) {
        ItemWrapper *layoutStruct = list.takeAt(index);
        return layoutStruct->item;
    }
    return nullptr;
}

void BorderLayout::add(QLayoutItem *item, Position position) { list.append(new ItemWrapper(item, position)); }

QSize BorderLayout::calculateSize(SizeType sizeType) const {
    QSize totalSize;

    for (int i = 0; i < list.size(); ++i) {
        ItemWrapper *wrapper = list.at(i);
        Position position = wrapper->position;
        QSize itemSize;

        if (sizeType == MinimumSize)
            itemSize = wrapper->item->minimumSize();
        else  // (sizeType == SizeHint)
            itemSize = wrapper->item->sizeHint();

        if (position == Position::North || position == Position::South || position == Position::Center)
            totalSize.rheight() += itemSize.height();

        if (position == Position::West || position == Position::East || position == Position::Center)
            totalSize.rwidth() += itemSize.width();
    }
    return totalSize;
}

QSize BorderLayout::regionSize(BorderLayout::Position position) const {
    QSize size{0, 0};
    std::for_each(list.begin(), list.end(), [position, &size](ItemWrapper *item) {
        if (item->position == position) {
            switch (position) {
                case Position::East:
                case Position::West:
                    size.setHeight(item->item->sizeHint().height());
                    size.setWidth(size.width() + item->item->sizeHint().width());
                    break;
                case Position::South:
                case Position::North:
                    size.setWidth(item->item->sizeHint().width());
                    size.setHeight(size.height() + item->item->sizeHint().height());
                    break;
                case Position::Center:
                    size.setWidth(item->item->sizeHint().width());
                    size.setHeight(item->item->sizeHint().height());
                    break;
            }
        }
    });
    return size;
}
