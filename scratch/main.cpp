#include "pch.h"
#include <assert.h>

template <typename T>
struct qi; // replaces impl::require

struct __declspec(empty_bases) IUnknown { size_t value{ 1 }; };

struct Visual : IUnknown
{
    // methods that live on Visual vtable

    void VisualMethod()
    {
        // call abi->Method();
    }
};

template<> struct qi<Visual> : qi<IVisual>, qi<
{
    // methods that live on Visual vtable but need a QI to call

    void VisualMethod()
    {
        // QI
        auto base = reinterpret_cast<IUnknown*>(this);
        base->value += 1;
        // call Visual->Method()
    }
};

struct SpriteVisual : IUnknown, qi<Visual>
{

};

static_assert(sizeof(SpriteVisual) == sizeof(size_t));

int main()
{
    auto s = SpriteVisual();
    s.VisualMethod();
    s.VisualMethod();
}
