#include "grid.h"
#include "global.h"
#include <iostream>

using namespace gol;

Grid::Grid()
{
    DrawPulsar();
}


Grid::~Grid()
{
    
}


void Grid::ResetGrid()
{
    for (auto l = 0; l < height; l++)
    {
        for (auto c = 0; c < width; c++)
        {
            Cell current_cell = Cell();
            current_cell.SetState(CellState::DEAD);

            m_grid[l][c] = current_cell;
        }
    }
}

CellState pulsar[13][13] = 
{
    {CellState::DEAD, CellState::DEAD, CellState::ALIVE, CellState::ALIVE, CellState::ALIVE, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::ALIVE, CellState::ALIVE, CellState::ALIVE,CellState::DEAD,CellState::DEAD },
    {CellState::DEAD},
    {CellState::ALIVE, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::ALIVE, CellState::DEAD, CellState::ALIVE, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::ALIVE},
    {CellState::ALIVE, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::ALIVE, CellState::DEAD, CellState::ALIVE, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::ALIVE},
    {CellState::ALIVE, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::ALIVE, CellState::DEAD, CellState::ALIVE, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::ALIVE},
    {CellState::DEAD, CellState::DEAD, CellState::ALIVE, CellState::ALIVE, CellState::ALIVE, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::ALIVE, CellState::ALIVE, CellState::ALIVE,CellState::DEAD,CellState::DEAD },
    {CellState::DEAD},
    {CellState::DEAD, CellState::DEAD, CellState::ALIVE, CellState::ALIVE, CellState::ALIVE, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::ALIVE, CellState::ALIVE, CellState::ALIVE,CellState::DEAD,CellState::DEAD },
    {CellState::ALIVE, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::ALIVE, CellState::DEAD, CellState::ALIVE, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::ALIVE},
    {CellState::ALIVE, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::ALIVE, CellState::DEAD, CellState::ALIVE, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::ALIVE},
    {CellState::ALIVE, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::ALIVE, CellState::DEAD, CellState::ALIVE, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::ALIVE},
    {CellState::DEAD},
    {CellState::DEAD, CellState::DEAD, CellState::ALIVE, CellState::ALIVE, CellState::ALIVE, CellState::DEAD, CellState::DEAD, CellState::DEAD, CellState::ALIVE, CellState::ALIVE, CellState::ALIVE,CellState::DEAD,CellState::DEAD }
};

void Grid::DrawPulsar()
{
    ResetGrid();

    uint32_t c_x = width/2;
    uint32_t c_y = height/2;

    for (auto y = c_y - 6; y <= c_y + 6; y++)
    {
        for (auto x = c_x - 6; x <= c_x + 6; x++)
        {
            m_grid[y][x].SetState(pulsar[y + 6 - c_y][x + 6 - c_x]);
        }
    }
}

uint32_t Grid::CountLivingNeighbors(int x, int y)
{
    uint32_t res = 0;

    for (auto idx = x - 1; idx <= x + 1; idx++)
    {
        for (auto idy = y - 1; idy <= y + 1; idy++)
        {
            if (idy != y || idx != x)
            {
                int neigb_x = (idx < 0) ? width - 1 : idx % width;
                int neigb_y = (idy < 0) ? height - 1 : idy % height;

                if (m_grid[neigb_y][neigb_x].GetState() == CellState::ALIVE)
                {
                    res++;
                }
            }
        }
    }
    return res;
}

void Grid::UpdateGrid()
{
    PredictGrid();

    for (auto l = 0; l < height; l++)
    {
        for (auto c = 0; c < width; c++)
        {
            using enum CellEvolution;
            using enum CellState;
            switch (m_grid[l][c].GetEvo())
            {
            case DEATH:
                m_grid[l][c].SetState(DEAD);
                break;            
            case BORN:
                m_grid[l][c].SetState(ALIVE);
                break;
            case LIVE:
                m_grid[l][c].SetState(ALIVE);
                break;
            default:
                m_grid[l][c].SetState(DEAD);
                break;
            }
        }
    }
}

void Grid::PredictGrid()
{
    for (auto l = 0; l < height; l++)
    {
        for (auto c = 0; c < width; c++)
        {
            CellState current_state = m_grid[l][c].GetState();
            uint32_t nb_living_neighbors = CountLivingNeighbors(static_cast<int>(c), static_cast<int>(l));

            if (current_state == CellState::ALIVE && ((nb_living_neighbors == 2) || (nb_living_neighbors == 3)))
            {
                m_grid[l][c].SetEvolve(CellEvolution::LIVE); // Cell survive
            }
            else if (current_state == CellState::DEAD && (nb_living_neighbors == 3))
            {
                m_grid[l][c].SetEvolve(CellEvolution::BORN); // Cell will be alive
            }
            else
            {
                m_grid[l][c].SetEvolve(CellEvolution::DEATH); // Cell will be dead
            }
        }
    } 
}

void Grid::DrawGrid(sf::RenderWindow * m_pt_display_window)
{
    sf::RectangleShape shape = sf::RectangleShape(sf::Vector2f(scale, scale));

    for (auto l = 0; l < height; l++)
    {
        for (auto c = 0; c < width; c++)
        {
            shape.setFillColor(m_grid[l][c].GetStateColor());
            shape.setPosition(ToFloatVector(sf::Vector2u(c, l), scale));
            m_pt_display_window->draw(shape);
        }
    }
}