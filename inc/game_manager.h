#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "grid.h"

/**
 * @brief Game manager : handles all the application and game logic
 */
class GameManager
{
private:
    sf::RenderWindow * m_pt_display_window;   /**< @brief Pointer to the display window of the game */

    sf::Font m_txt_font;        /**< @brief Font to use for the different texts */
    sf::Text m_txt_title;       /**< @brief Title of the game */
    sf::Text m_txt_stats;       /**< @brief Display stats (number of iterations ...) */
    sf::Text m_txt_footer;      /**< @brief Footer (credits and license) */

    bool m_edit_mode;           /**< @brief Holds if the application is in edit mode */
    bool m_editing;             /**< @brief In edit mode, holds if the user is currently editing (holding mouse button basically). */
    CellState m_state_to_set;   /**< @brief When editing, holds what type of cell the user is setting */
    Grid m_grid;                /**< @brief the instance of the game of life grid */
    uint32_t m_nb_iteration;    /**< @brief holds the number of iterations (reset after each edition by the user) */

public:
    /**
     * @brief Construct a new Game Manager object
     * 
     * @param pt_display_window : pointer to the display window that the game manager will use to display game updates.
     */
    GameManager(sf::RenderWindow * pt_display_window);

    /**
     * @brief Destroy the Game Manager object
     */
    ~GameManager();

    /**
     * @brief Process all the user inputs and events (Keyboard, mouse, window close etc...)
     */
    void ProcessUserInputs();

    /**
     * @brief Update the state of the game
     */
    void UpdateGameState();

    /**
     * @brief Update display by rendering a full frame
     * @note clears the previous window (fill with black)
     */
    void UpdateDisplay();

private:
    /**
     * @brief Check if the input mouse position lands in the game window region of the screen
     * 
     * @param mouse_pos : input mouse position relative to game window
     * @return true if in the window, false otherwise
     */
    inline bool IsMouseInWindow(sf::Vector2i & mouse_pos) const;
};

