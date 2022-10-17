#pragma once

#include "global.h"
#include "grid_cell.h"
#include <array>
#include <random>
#include <SFML/Graphics.hpp>

/**
 * @brief Holds the game grid
 */
class Grid
{
private:
    std::array<std::array<Cell, gol::width>, gol::height> m_grid; /**< @brief Game of Life 2D grid */

public:
    /**
     * @brief Construct a new Grid object
     */
    Grid();

    /**
     * @brief Default destructor
     */
    ~Grid();

    /**
     * @brief Toggle a cell of the grid.(see: @ref Cell::ToggleCell)
     * 
     * @param x : x position in the grid of the cell to Toggle
     * @param y : y position in the grid of the cell to Toggle
     */
    void ToggleCell(uint32_t x, uint32_t y) { m_grid[y][x].ToggleCell(); }

    /**
     * @brief Set a new state for a giving cell of the grid
     * 
     * @param x : x position in the grid of the cell to modify
     * @param y : y position in the grid of the cell to modify
     * @param new_state : new state to set
     */
    void SetState(uint32_t x, uint32_t y, CellState new_state) { m_grid[y][x].SetState(new_state); }

    /**
     * @brief Get the State of a giving cell of the grid
     * 
     * @param x : x position in the grid of the cell
     * @param y : y position in the grid of the cell
     * @return CellState of the cell
     */
    CellState GetState(uint32_t x, uint32_t y) const { return m_grid[y][x].GetState(); }

    /**
     * @brief Count how many cell are living in the neighborhood of a giving cell 
     * 
     * @param x : x position in the grid of the cell
     * @param y : y position in the grid of the cell
     * @return uint32_t the number of living cell in the neighborhood (8 cell neighborhood : horizontal, vertical and diagonal)
     */
    uint32_t CountLivingNeighbors(int x, int y);

    /**
     * @brief Uses the rules of Game of life to dertermine for each cell of the grid how it's going to Evolve in the next iteration.
     */
    void PredictGrid();

    /**
     * @brief Updates the grid by running an iteration of the game
     */
    void UpdateGrid();

    /**
     * @brief Draw the grid on the window
     * 
     * @param m_pt_display_window : pointer to the window on which to draw (no check on nullptr, responsability of the caller)
     */
    void DrawGrid(sf::RenderWindow * m_pt_display_window);

    /**
     * @brief Draw a Pulsar @ref https://conwaylife.com/wiki/Pulsar 
     */
    void DrawPulsar();

    /**
     * @brief Empty the grid.
     */
    void ResetGrid();

};