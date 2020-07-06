//
// Created by mathis on 06/07/2020.
//
#pragma once

#include <QLayout>
#include <QtWidgets/QLayoutItem>
#include <QtWidgets/QWidget>

class BorderLayout : public QLayout {
   public:
    enum class Position { West, North, South, East, Center };

    explicit BorderLayout(QWidget *parent, const QMargins &margins = QMargins(), int spacing = -1);
    explicit BorderLayout(int spacing = -1);
    ~BorderLayout() override;

    void addItem(QLayoutItem *item) override;
    void addWidget(QWidget *widget, Position position);
    [[nodiscard]] Qt::Orientations expandingDirections() const override;
    [[nodiscard]] bool hasHeightForWidth() const override;
    [[nodiscard]] int count() const override;
    [[nodiscard]] QLayoutItem *itemAt(int index) const override;
    [[nodiscard]] QSize minimumSize() const override;
    void setGeometry(const QRect &rect) override;
    [[nodiscard]] QSize sizeHint() const override;
    QLayoutItem *takeAt(int index) override;

    void add(QLayoutItem *item, Position position);

    [[nodiscard]] QSize regionSize(Position position) const;

   private:
    struct ItemWrapper {
        ItemWrapper(QLayoutItem *i, Position p) {
            item = i;
            position = p;
        }

        QLayoutItem *item;
        Position position;
    };

    enum SizeType { MinimumSize, SizeHint };
    [[nodiscard]] QSize calculateSize(SizeType sizeType) const;

    QList<ItemWrapper *> list;
};
