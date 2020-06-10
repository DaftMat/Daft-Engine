//
// Created by mathis on 10/06/2020.
//
#pragma once
#include <API.hpp>

namespace ProjName::Core {

/** base class for any non-copyable object.
 *
 */
class ENGINE_API NonCopyable
{
  public:
    /**
     * Constructor.
     */
    constexpr NonCopyable() noexcept = default;

    /**
     * Destructor.
     */
    ~NonCopyable() noexcept = default;

    /**
     * Move Constructor.
     */
    NonCopyable( NonCopyable&& ) noexcept = default;

    /**
     * Move assignment operator.
     * @return this
     */
    NonCopyable& operator=( NonCopyable&& ) noexcept = default;

    ///\exclude
    NonCopyable( const NonCopyable& ) noexcept = delete;

    ///\exclude
    void operator=( const NonCopyable& ) noexcept = delete;
};

} // namespace ProjName::Core