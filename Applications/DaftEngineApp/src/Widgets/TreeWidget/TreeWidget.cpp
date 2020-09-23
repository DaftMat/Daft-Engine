//
// Created by mathis on 01/09/2020.
//
#include "TreeWidget.hpp"

#include <QtWidgets/QLabel>

namespace daft::app {
void TreeWidget::resetTree(engine::Composite *root) {
    // setModel(nullptr);

    auto *standardModel = new QStandardItemModel();
    QStandardItem *rootNode = standardModel->invisibleRootItem();
    QStringList labels;
    labels.append("Scene");
    standardModel->setHorizontalHeaderLabels(labels);
    standardModel->setHeaderData(0, Qt::Horizontal, QColor(0xf2f2f2), Qt::TextColorRole);

    addNode(rootNode, root);

    setModel(standardModel);
    expandAll();
}

void TreeWidget::addNode(QStandardItem *parent, engine::Composite *node) {
    for (auto &drawable : node->drawables()) {
        /// add drawable
        auto *item = new QStandardItem(drawable->name().c_str());
        /// set the item's text color
        item->setData(QColor(0xf2f2f2), Qt::TextColorRole);
        parent->appendRow(item);
        /// add elements if the current drawable is a node
        if (drawable->isComposite()) addNode(item, (engine::Composite *)drawable.get());
    }
}
}  // namespace daft::app