//
// Created by mathis on 01/09/2020.
//
#pragma once
#include <API.hpp>
#include <Engine/Drawables/Composite.hpp>
#include <QStandardItem>
#include <QTreeView>

namespace daft::app {
class ENGINE_API TreeWidget : public QTreeView {
    Q_OBJECT

   public:
    explicit TreeWidget(engine::Composite *root, QWidget *parent = nullptr) : QTreeView(parent) { reset(root); }

    void reset(engine::Composite *root);

    void addNode(QStandardItem *parent, engine::Composite *node);
};
}  // namespace daft::app