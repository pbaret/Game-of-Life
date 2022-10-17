#pragma once

#include <stdint.h>
#include <SFML/Graphics.hpp>

/**
 * @brief Grid cell possible state
 */
enum class CellState 
{
    DEAD,   /**< @brief Dead cell */
    ALIVE,  /**< @brief Alive cell */
};

/**
 * @brief Describe how the cell is going to evolve
 */
enum class CellEvolution
{
    DEATH, /**< @brief Cell will be dead */
    BORN,  /**< @brief Cell will be born */
    LIVE   /**< @brief Cell will live */
};

/**
 * @brief @brief Cell of the game of life
 */
class Cell
{
private:
    CellState m_current_state; /**< @brief Current state of the cell. */
    CellEvolution m_evolution; /**< @brief Evolution of the cell. Used for coloring cell that will change state. */

public:

    /**
     * @brief Default constructor
     */
    Cell();

    /**
     * @brief Default destructor
     */
    ~Cell();

    /**
     * @brief Returns the color to use to draw the cell (color depends on its state)
     */
    sf::Color GetStateColor() const;

    /**
     * @brief Returns the current state of the cell
     */
    CellState GetState() const { return m_current_state; }

    /**
     * @brief Returns to predicted state evolution for the current cell
     */
    CellEvolution GetEvo() const { return m_evolution; }

    /**
     * @brief Invert Cell state. (Set living Cell to dead cell, and dead cell to living cell)
     */
    void ToggleCell() { m_current_state = (m_current_state == CellState::ALIVE) ? CellState::DEAD : CellState::ALIVE; }

    /**
     * @brief Set the State of the cell
     * 
     * @param new_state : new state to set
     */
    void SetState(CellState new_state) { m_current_state = new_state; }

    /**
     * @brief Defines the cell evolution
     * 
     * @param evo : evolution to set
     */
    void SetEvolve(CellEvolution evo) { m_evolution = evo; }

};