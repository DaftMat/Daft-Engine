//
// Created by mathis on 24/05/2020.
//
#pragma once
#include <API.hpp>

#include <Core/NonCopyable.hpp>
#include <Minimal-Engine/Renderer.hpp>
#include <memory>

namespace ProjName::Core {

/**
 * This class is a base class for any application abstraction of the engine
 * @tparam WindowType - type of window to to create - see the examples
 * GLFWExample and GLFWWindow
 */
template <typename WindowType>
class ENGINE_API BaseApplication : public NonCopyable
{
  public:
    /**
     * Default constructor.
     */
    BaseApplication() = default;

    /**
     * Virtual destructor.
     */
    virtual ~BaseApplication() {
        m_renderer.reset();
        m_window.reset();
    }

    /**
     * draw method - pure virtual
     * @param deltatime - time elapsed since last frame.
     */
    virtual void draw( double deltatime ) = 0;

  protected:
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<WindowType> m_window;

    double m_lastTime { 0 };

    void init( int width, int height ) {
        m_window   = std::make_unique<WindowType>( width, height );
        m_renderer = std::make_unique<Renderer>( width, height );
    }
};

} // namespace ProjName::Core