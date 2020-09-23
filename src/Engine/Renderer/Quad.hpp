//
// Created by mathis on 02/09/2020.
//
#pragma once
#include <API.hpp>
#include <Engine/Drawables/MeshObject.hpp>

namespace daft::engine {
/**
 * A MeshObject that is used as a screen.
 */
class ENGINE_API Quad : public MeshObject {
   public:
    Quad(float x, float y, float width, float height);

    void setTexture(int id);
};
}  // namespace daft::engine