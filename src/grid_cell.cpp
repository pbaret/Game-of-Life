#include "grid_cell.h"
#include "global.h"

using namespace gol;

Cell::Cell()
{
    m_current_state = CellState::DEAD;
    m_evolution = CellEvolution::DEATH;
}

Cell::~Cell()
{

}

sf::Color Cell::GetStateColor() const
{
    sf::Color color = dead_color;
    if (m_current_state == CellState::ALIVE)
    {
        color = alive_color;
    }

    return color;
}
