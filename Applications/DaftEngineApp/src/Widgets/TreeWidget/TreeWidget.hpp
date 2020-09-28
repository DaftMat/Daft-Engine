//
// Created by mathis on 01/09/2020.
//
#pragma once
#include <API.hpp>
#include <Engine/Drawables/Composite.hpp>
#include <Engine/Drawables/Object/BSpline.hpp>
#include <QStandardItem>
#include <QTreeView>

namespace daft::app {
/**
 * A Tree View Widget that shows the scene tree.
 */
class ENGINE_API TreeWidget : public QTreeView {
    Q_OBJECT

   public:
    /**
     * Standard constructor.
     * Creates a tree view using a Composite .
     * @param root - root composite.
     * @param parent - parent of the tree view widget.
     */
    explicit TreeWidget(engine::Composite *root, QWidget *parent = nullptr) : QTreeView(parent) { resetTree(root); }

    /**
     * Resets the elements of the tree view according to the root.
     * @param root - root composite.
     */
    void resetTree(engine::Composite *root);

    /**
     * Adds the children of a Composite to the node created from this composite.
     * @param parent - the composite as a QStandardItem .
     * @param node - the composite itself.
     */
    void addNode(QStandardItem *parent, engine::Composite *node);
};
}  // namespace daft::app