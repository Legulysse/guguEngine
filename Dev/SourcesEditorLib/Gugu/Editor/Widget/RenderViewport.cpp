////////////////////////////////////////////////////////////////
// Header

#include "Gugu/Common.h"
#include "Gugu/Editor/Widget/RenderViewport.h"

////////////////////////////////////////////////////////////////
// Includes

#include "Gugu/Engine.h"
#include "Gugu/Window/Renderer.h"
#include "Gugu/Element/Element.h"
#include "Gugu/System/SystemUtility.h"

#include <SFML/Graphics/RenderTexture.hpp>

#include <imgui.h>
#include <imgui-SFML.h>

////////////////////////////////////////////////////////////////
// File Implementation

namespace gugu {

RenderViewport::RenderViewport(bool fillAvailableArea)
    : m_renderTexture(nullptr)
    , m_root(nullptr)
    , m_size(100, 100)
    , m_zoomMultiplier(1.f)
    , m_fillAvailableArea(fillAvailableArea)
{
    m_renderTexture = new sf::RenderTexture;
    m_renderTexture->create(m_size.x, m_size.y);

    m_root = new Element;
}

RenderViewport::~RenderViewport()
{
    SafeDelete(m_root);
    SafeDelete(m_renderTexture);
}

void RenderViewport::BeginRender()
{
    // Compute canvas size and area size.
    Vector2u canvas_sz((uint32)((float)m_size.x * m_zoomMultiplier), (uint32)((float)m_size.y * m_zoomMultiplier));
    Vector2u areaSize = m_fillAvailableArea ? Vector2u(0, 0) : canvas_sz;

    // Begin imgui area.
    ImGuiWindowFlags flags = ImGuiWindowFlags_HorizontalScrollbar;
    ImGui::BeginChild("RenderViewport", areaSize, false, flags);

    // Using InvisibleButton() as a convenience 1) it will advance the layout cursor and 2) allows us to use IsItemHovered()/IsItemActive()
    Vector2f canvas_p0 = ImGui::GetCursorScreenPos();      // ImDrawList API uses screen coordinates!
    //ImVec2 canvas_sz = ImGui::GetContentRegionAvail();   // Resize canvas to what's available
    //if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
    //if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;

    //ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);

    // Draw border and background color
    //ImGuiIO& io = ImGui::GetIO();
    //ImDrawList* draw_list = ImGui::GetWindowDrawList();
    //draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(50, 50, 50, 255));
    //draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(255, 255, 255, 255));

    // This will catch our interactions
    ImGui::InvisibleButton("RenderViewportInvisibleButton", canvas_sz, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
    //const bool is_hovered = ImGui::IsItemHovered(); // Hovered
    //const bool is_active = ImGui::IsItemActive();   // Held
    ////const ImVec2 origin(canvas_p0.x + scrolling.x, canvas_p0.y + scrolling.y); // Lock scrolled origin
    ////const ImVec2 mouse_pos_in_canvas(io.MousePos.x - origin.x, io.MousePos.y - origin.y);
    //const ImVec2 origin(canvas_p0.x, canvas_p0.y); // Lock scrolled origin
    //const ImVec2 mouse_pos_in_canvas(io.MousePos.x - origin.x, io.MousePos.y - origin.y);

    // Little trick : draw an invisible button the size of the texture, then draw the texture all over it.
    ImGui::SetCursorScreenPos(canvas_p0);

    // Reset render target.
    if (m_renderTexture->getSize() != canvas_sz)
    {
        m_renderTexture->create(canvas_sz.x, canvas_sz.y);
    }

    m_root->SetSize(Vector2f(m_size));

    sf::View view;
    view.reset(sf::FloatRect(Vector2f(0, 0), Vector2f(m_size)));
    m_renderTexture->setView(view);
}

void RenderViewport::FinalizeRender()
{
    // Prepare render.
    m_renderTexture->clear(sf::Color(128, 128, 128, 255));

    sf::FloatRect viewport;
    viewport.left = m_renderTexture->getView().getCenter().x - m_renderTexture->getView().getSize().x / 2.f;
    viewport.top = m_renderTexture->getView().getCenter().y - m_renderTexture->getView().getSize().y / 2.f;
    viewport.width = m_renderTexture->getView().getSize().x;
    viewport.height = m_renderTexture->getView().getSize().y;

    RenderPass renderPass;
    renderPass.pass = GUGU_RENDERPASS_DEFAULT;
    renderPass.target = m_renderTexture;
    renderPass.rectViewport = viewport;

    // Render elements.
    m_root->Render(renderPass, sf::Transform());

    // Render the scene.
    m_renderTexture->display();
    ImGui::Image(*m_renderTexture);

    // Finalize imgui area.
    ImGui::EndChild();
}

void RenderViewport::SetSize(Vector2u size)
{
    m_size = size;
}

void RenderViewport::SetZoom(float zoomMultiplier)
{
    m_zoomMultiplier = zoomMultiplier;
}

Vector2f RenderViewport::GetPickedPosition(const Vector2i& pixelCoords) const
{
    return m_renderTexture->mapPixelToCoords(pixelCoords, m_renderTexture->getView());
}

Element* RenderViewport::GetRoot() const
{
    return m_root;
}

}   //namespace gugu
