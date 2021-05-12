#pragma once

////////////////////////////////////////////////////////////////
// Includes

#include <Gugu/Utility/Vector2.h>

#include <vector>

////////////////////////////////////////////////////////////////
// File Declarations

namespace gugu {

class SquareGrid
{
public:

    SquareGrid();
    virtual ~SquareGrid();

    void InitSquareGrid(int _iWidth, int _iHeight, float _fCellWidth, float _fCellHeight, bool eightSides);

    sf::Vector2f GetCellPosition(const sf::Vector2i& coords) const;
    sf::Vector2f GetCellCenter(const sf::Vector2i& coords) const;

    bool PickCoords(const sf::Vector2f& position, sf::Vector2i& pickedCoords) const;

    void GetNeighbours(const sf::Vector2i& coords, std::vector<sf::Vector2i>& neighbours) const;

    int GetWidth() const;
    int GetHeight() const;

    float GetCellWidth() const;
    float GetCellHeight() const;

protected:

    int m_width;
    int m_height;
    bool m_eightSides;

    float m_cellWidth;
    float m_cellHeight;
};

}   // namespace gugu
