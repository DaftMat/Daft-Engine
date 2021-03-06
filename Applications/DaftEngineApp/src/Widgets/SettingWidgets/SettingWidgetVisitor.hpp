//
// Created by mathis on 26/07/2020.
//
#pragma once

#include <Core/Utils/DrawableVisitor.hpp>
#include <Engine/Drawables/Drawable.hpp>

#include "SettingWidget.hpp"

namespace daft::app {
/**
 * A visitor that creates the right SettingWidget according to the selected object.
 */
class SettingWidgetVisitor : public core::DrawableVisitor {
   public:
    /**
     * visits an Object .
     * @param object - object to visit.
     */
    void visit(engine::Object *object) override;

    /**
     * Visits a Sphere .
     * @param sphere - sphere to visit.
     */
    void visit(engine::Sphere *sphere) override;

    /**
     * Visits a Torus .
     * @param torus - torus to visit.
     */
    void visit(engine::Torus *torus) override;

    /**
     * Visits a Cube .
     * @param cube - cube to visit.
     */
    void visit(engine::Cube *cube) override;

    /**
     * Visits a BSpline .
     * @param bspline - bspline to visit.
     */
    void visit(engine::BSpline *bspline) override;

    /**
     * Visits a BSpline2D .
     * @param bspline - bspline to visit.
     */
    void visit(engine::BSpline2D *bspline) override;

    /**
     * Visits a Cylinder .
     * @param cylinder - cylinder to visit.
     */
    void visit(engine::Cylinder *cylinder) override;

    /**
     * Visits a Metaballs .
     * @param metaballs - metaballs to visit.
     */
    void visit(engine::Metaballs *metaballs) override;

    /**
     * Visits a Caves .
     * @param caves - caves to visit.
     */
    void visit(engine::Caves *caves) override;

    /**
     * Visits a PointLight .
     * @param pointLight - point light to visit.
     */
    void visit(engine::PointLight *pointLight) override;

    /**
     * Visits a SpotLight .
     * @param spotLight - spot light to visit.
     */
    void visit(engine::SpotLight *spotLight) override;

    /**
     * Visits a DirLight .
     * @param dirLight - dir light to visit.
     */
    void visit(engine::DirLight *dirLight) override;

    /**
     * Visits a QuadLight .
     * @param quadLight - quad light to visit.
     */
    void visit(engine::QuadLight *quadLight) override;

    /**
     * visits a Composite .
     * @param composite - composite to visit.
     */
    void visit(engine::Composite *composite) override;

    /**
     * Created widget getter.
     * @return pointer to the created widget.
     */
    SettingWidget *widget() { return m_widget; }

   private:
    static TransformSettings *createTransformWidget(core::SettingManager sm, bool enablePos = true,
                                                    bool enableRot = true, bool enableSca = true) {
        return new TransformSettings(std::move(sm), enablePos, enableRot, enableSca);
    }

    SettingWidget *m_widget{nullptr};
};
}  // namespace daft::app