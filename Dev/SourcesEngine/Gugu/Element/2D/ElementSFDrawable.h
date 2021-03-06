#pragma once

////////////////////////////////////////////////////////////////
// Includes

#include "Gugu/Element/Element.h"

////////////////////////////////////////////////////////////////
// Forward Declarations

namespace sf
{
    class Drawable;
}

////////////////////////////////////////////////////////////////
// File Declarations

namespace gugu {
    
class ElementSFDrawable : public Element
{
public:

    using DelegateElementSizeChanged = std::function<void (ElementSFDrawable*)>;

public:

    ElementSFDrawable();
    virtual ~ElementSFDrawable();

    void            SetSFDrawable   (sf::Drawable* _pSFDrawable);
    sf::Drawable*   GetSFDrawable   () const;

    void SetCallbackOnSizeChanged(DelegateElementSizeChanged callbackOnSizeChanged);

private:

    virtual void RenderImpl(RenderPass& _kRenderPass, const sf::Transform& _kTransformSelf) override;
    virtual void OnSizeChanged(Vector2f _kOldSize) override;
    
protected:

    sf::Drawable* m_sfDrawable;
    DelegateElementSizeChanged m_callbackOnSizeChanged;
};

}   // namespace gugu
