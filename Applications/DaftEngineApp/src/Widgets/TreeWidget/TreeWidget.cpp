//
// Created by mathis on 01/09/2020.
//
#include "TreeWidget.hpp"

namespace daft::app {
void TreeWidget::resetTree(engine::Composite *root) {
    // setModel(nullptr);

    auto *standardModel = new QStandardItemModel();
    QStandardItem *rootNode = standardModel->invisibleRootItem();

    addNode(rootNode, root);

    setModel(standardModel);
    expandAll();
}

void TreeWidget::addNode(QStandardItem *parent, engine::Composite *node) {
    for (auto &drawable : node->drawables()) {
        /// add drawable
        auto *item = new QStandardItem(drawable->name().c_str());
        parent->appendRow(item);
        /// add elements if the current drawable is a node
        if (drawable->isComposite()) addNode(item, (engine::Composite *)drawable.get());
    }
}
}  // namespace daft::app