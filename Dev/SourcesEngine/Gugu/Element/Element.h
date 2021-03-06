#pragma once

////////////////////////////////////////////////////////////////
// Includes

#include "Gugu/System/Types.h"
#include "Gugu/Core/DeltaTime.h"
#include "Gugu/Core/Callback.h"
#include "Gugu/Math/UDim.h"
#include "Gugu/Math/Vector2.h"
#include "Gugu/Element/ElementInteractions.h"

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Event.hpp>

#include <vector>
#include <list>

////////////////////////////////////////////////////////////////
// Forward Declarations

namespace gugu
{
    struct RenderPass;
}

namespace pugi
{
    class xml_node;
}

////////////////////////////////////////////////////////////////
// File Declarations

namespace gugu {
    
class Element
{
public:

    Element();
    virtual ~Element();

    //----------------------------------------------
    // Hierarchy

    template<typename T>
    T* AddChild()
    {
        T* child = new T;
        AddChild(child);
        return child;
    }

    void AddChild(Element* child);
    void RemoveChild(Element* child);
    void DeleteAllChildren();

    // Set the Element's parent, without registering it in the parent's children list.
    void SetParent(Element* parent);

    Element* GetParent() const;
    Element* GetTopParent() const;

    size_t GetChildCount() const;
    const std::vector<Element*>& GetChildren() const;

    //----------------------------------------------
    // Position

    void SetPositionX(float _fPosX);
    void SetPositionY(float _fPosY);
    void SetPosition(float _fPosX, float _fPosY);
    void SetPosition(const Vector2f& _kPosition);

    void Move(float _fOffsetX, float _fOffsetY);
    void Move(const Vector2f& _kOffset);

    const Vector2f& GetPosition() const;

    //----------------------------------------------
    // Rotation

    void SetRotation(float _fAngle);
    void Rotate(float _fAngle);

    float GetRotation() const;

    //----------------------------------------------
    // Scale

    void SetScaleX(float _fScaleX);
    void SetScaleY(float _fScaleY);
    void SetScale(float _fScale);
    void SetScale(float _fScaleX, float _fScaleY);
    void SetScale(const Vector2f& _kScale);

    void Scale(float factorX, float factorY);
    void Scale(const Vector2f& factor);

    Vector2f GetScale() const;

    //----------------------------------------------
    // Origin

    void SetOriginX(float _fOriginX);
    void SetOriginY(float _fOriginY);
    void SetOrigin(float _fOriginX, float _fOriginY);
    void SetOrigin(const Vector2f& _kOrigin);

    const Vector2f& GetOrigin() const;

    //----------------------------------------------
    // Size

    void SetSizeX(float _fNewSizeX);
    void SetSizeY(float _fNewSizeY);
    void SetSize(float _fNewSizeX, float _fNewSizeY);
    void SetSize(Vector2f _kNewSize);

    const Vector2f& GetSize() const;       // Get Element Size
    Vector2f GetSizeScaled() const;        // Get Element Size, with its scale applied (TODO: Useless ?)
    Vector2f GetSizeOnScreen() const;      // Get Element Size, with all its upper hierarchy's scales applied (TODO: Useless ?)

    //----------------------------------------------
    // Flip

    void SetFlipV(bool _bFlip);  // Flip Top-Bottom
    void SetFlipH(bool _bFlip);  // Flip Left-Right
    void SetFlip(bool _bFlipV, bool _bFlipH);

    bool GetFlipV() const;
    bool GetFlipH() const;

    //----------------------------------------------
    // Transform

    virtual bool IsPicked(const Vector2f& _kGlobalCoords) const;

    Vector2f TransformToLocalFull(const Vector2f& _oPoint) const;    // TODO: rename as TransformToLocal and TransformToGlobal, maybe add TransformToParent.
    Vector2f TransformToGlobalFull(const Vector2f& _oPoint) const;

    const sf::Transform& GetTransform() const;
    const sf::Transform& GetInverseTransform() const;

    //----------------------------------------------
    // Z-Index

    void SetZIndex(int32 _iZIndex);
    int32 GetZIndex() const;

    void SortOnZIndex();   // recursive

    //----------------------------------------------
    // Visibility

    void SetVisible(bool visible);
    bool IsVisible(bool checkParents = false) const;

    //----------------------------------------------
    // Step and Update

    virtual void Step(const DeltaTime& dt); //TODO: Remove ? let Actors handle step related stuff ?
    virtual void Update(const DeltaTime& dt); //TODO: Call this from Render instead of additional loop ?

    //----------------------------------------------
    // Render

    void Render(RenderPass& _kRenderPass, const sf::Transform& _kTransformParent);

    void SetRenderPass(int _iPass);
    void AddRenderPass(int _iPass);
    void RemoveRenderPass(int _iPass);

    void SetDebugBoundsVisible(bool showDebugBounds);

    //TODO: Handle shaders properly
    //> Need to share shaders between objects ?
    //> Where/how do I manage/load/delete them ?
    //> It should probably only appear in the same places where I use textures.
    //> Maybe it would be a good occasion to add a Material pipeline.
    //void SetShader (sf::Shader* _pShader);

    //----------------------------------------------
    // UI

    void SetUnifiedOrigin(UDim2 _oNewDimOrigin);
    void SetUnifiedPosition(UDim2 _oNewDimPos);
    void SetUnifiedSize(UDim2 _oNewDimSize);

    UDim2 GetUnifiedOrigin() const;
    UDim2 GetUnifiedPosition() const;
    UDim2 GetUnifiedSize() const;

    void OnParentResized(Vector2f _kOldSize, Vector2f _kNewSize);
    void ComputeUnifiedOrigin();
    void ComputeUnifiedDimensions();

    //----------------------------------------------
    // Interactions

    void SetInteractionFlags(int _iFlags);
    void AddInteractionFlag(EInteraction::Type _eFlag);
    void RemoveInteractionFlag(EInteraction::Type _eFlag);

    int GetInteractionFlags() const;
    bool HasInteractionFlags() const;   //Return true if Interaction flags are set besides Disabled and Absorb
    bool HasInteractionFlag(EInteraction::Type _eFlag) const;

    virtual void GetPropagationList(std::vector<Element*>& _vecPropagationList) {} //Return Elements that are not Children but should have Interactions (like Items)

    void InitInteractions();
    ElementInteractions* GetInteractions() const;

    //----------------------------------------------
    // Events

    virtual void OnMouseEnter() {}
    virtual void OnMouseLeave() {}

    virtual bool OnMousePressed() { return true; }
    virtual bool OnMouseReleased() { return true; }

    virtual bool OnMouseSelected() { return true; }
    virtual bool OnMouseDeselected() { return true; }

    virtual void OnMouseDragStart() {}
    virtual void OnMouseDragStop() {}
    virtual void OnMouseDragMove() {}

    virtual void OnMouseScrolled(int _iDelta) {}

    virtual bool OnSFEvent(const sf::Event& _oSFEvent) { return true; }     //Return true : allow event to be propagated.

    //----------------------------------------------
    // Loading

    virtual bool LoadFromXml(const pugi::xml_node& _oNodeElement);

protected:

    //----------------------------------------------
    // Render

    virtual void RenderImpl(RenderPass& _kRenderPass, const sf::Transform& _kTransformSelf) {}

    //----------------------------------------------
    // Internal Events

    virtual void OnTransformChanged() {}
    virtual void OnVisibleChanged() {}
    virtual void OnSizeChanged(Vector2f _kOldSize) {}   // TODO: remove the oldSize param ?

    //----------------------------------------------
    // Z-Index

    static bool CompareZIndex(Element* _pLeft, Element* _pRight);

protected:

    //----------------------------------------------
    // Hierarchy

    Element* m_parent;
    std::vector<Element*> m_children;

    //----------------------------------------------
    // Render

    sf::Transformable m_transform;
    Vector2f m_size;
    bool m_flipV;
    bool m_flipH;

    int m_renderPass;
    bool m_isVisible;
    int32 m_zIndex;

    bool m_showDebugBounds;

    //sf::Shader* m_pShader;

    //----------------------------------------------
    // UI

    bool m_useDimOrigin;
    UDim2 m_dimOrigin;
    bool m_useDimPosition;
    UDim2 m_dimPosition;
    bool m_useDimSize;
    UDim2 m_dimSize;

    //----------------------------------------------
    // Interactions

    ElementInteractions* m_interactions;
};

}   // namespace gugu
