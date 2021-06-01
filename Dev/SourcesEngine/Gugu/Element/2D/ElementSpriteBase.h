#pragma once

////////////////////////////////////////////////////////////////
// Includes

#include "Gugu/Element/Element.h"

#include <SFML/Graphics/VertexArray.hpp>

////////////////////////////////////////////////////////////////
// Forward Declarations

namespace gugu
{
    class Texture;
}

////////////////////////////////////////////////////////////////
// File Declarations

namespace gugu {
    
class ElementSpriteBase : public Element
{
public:

    ElementSpriteBase();
    virtual ~ElementSpriteBase();

    void SetSubRect(const sf::IntRect& _oRect);
    sf::IntRect GetSubRect() const;

    void SetRepeatTexture(bool repeatTexture);

    void SetFlipTextureX(bool _bFlipTextureX);  // Flip Top-Bottom
    void SetFlipTextureY(bool _bFlipTextureY);  // Flip Left-Right
    void SetFlipTexture(bool _bFlipTextureX, bool _bFlipTextureY);  // Flip Top-Bottom and Left-Right

    void SetColor(const sf::Color& _oColor);
    sf::Color GetColor() const;

protected:

    size_t GetRequiredVertexCount() const;
    void RecomputeVerticesPositionAndTextureCoords(sf::Vertex* vertices) const;
    void RecomputeVerticesColor(sf::Vertex* vertices, size_t count) const;

    virtual void OnSizeChanged(sf::Vector2f _kOldSize) override;

protected:

    sf::IntRect m_subRect;
    sf::Color m_color;

    // TODO: replace by a virtual RaiseDirtyVertices ?
    bool m_dirtyVertices;

    // TODO: Split into m_repeatTextureX and m_repeatTextureY ?
    // TODO: Add m_repeatTextureSize as a UDim2 to stretch the tiling quads ?
    bool m_repeatTexture;
    bool m_flipTextureX;
    bool m_flipTextureY;
};

}   // namespace gugu