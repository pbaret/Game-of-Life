#include "game_manager.h"
#include "font-arial.h"
#include "global.h"

#include <iostream>
#include <string>

using namespace gol;

GameManager::GameManager(sf::RenderWindow * pt_display_window) :
    m_pt_display_window(pt_display_window),
    m_edit_mode(true),
    m_editing(false),
    m_state_to_set(CellState::DEAD),
    m_nb_iteration(0),
    m_grid()
{
    if (!m_txt_font.loadFromMemory(&arial_ttf, arial_ttf_len))
    {
        std::cerr << "problem with font" << std::endl;
    }

    m_txt_title = sf::Text("Game of Life", m_txt_font, 50);
    SetTextLocalOrigin(m_txt_title, LocalOrigin::Top);
    m_txt_title.setPosition(GridPositionToWindowCoordinate((width)/2, 0));
    m_txt_title.setStyle(sf::Text::Bold);
    m_txt_title.setFillColor(sf::Color::Red);

    m_txt_footer = sf::Text("Developped by Pierre BARET - WTFPL License", m_txt_font, 20);
    SetTextLocalOrigin(m_txt_footer, LocalOrigin::Bottom);
    m_txt_footer.setPosition(GridPositionToWindowCoordinate((width)/2, (height - 1)));
    m_txt_footer.setFillColor(sf::Color(128,0,255));

    
    m_txt_stats = sf::Text(std::to_string(m_nb_iteration), m_txt_font, 20);
    SetTextLocalOrigin(m_txt_stats, LocalOrigin::TopRight);
    m_txt_stats.setPosition(GridPositionToWindowCoordinate((width-2), 4));
    m_txt_stats.setFillColor(sf::Color(128,255,255));
}


GameManager::~GameManager()
{
}


inline bool GameManager::IsMouseInWindow(sf::Vector2i & mouse_pos) const
{
    return ((mouse_pos.x > 0) && (mouse_pos.x < width * scale) && (mouse_pos.y > 0) && (mouse_pos.y < height * scale));
}

void GameManager::ProcessUserInputs()
{
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (m_pt_display_window->pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
                // Toggle Edit Mode
                case sf::Keyboard::Enter:
                {
                    m_edit_mode = !m_edit_mode;
                    m_editing = false;
                    m_nb_iteration = 0;
                }
                break;
                // Reset Grid (and so go to edit mode)
                case sf::Keyboard::R:
                {
                    m_edit_mode = true;
                    m_editing = false;
                    m_nb_iteration = 0;
                    m_grid.ResetGrid();
                }
                break;
                // Quit
                case sf::Keyboard::Q:
                {
                    m_pt_display_window->close();
                }
                break;
                default:
                break;
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            m_edit_mode = true;
            m_editing = true;
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(*m_pt_display_window);
            if (IsMouseInWindow(mouse_pos))
            {
                const uint32_t x = static_cast<uint32_t>(WindowToGridCoord(mouse_pos.x));
                const uint32_t y = static_cast<uint32_t>(WindowToGridCoord(mouse_pos.y));
                m_grid.ToggleCell(x, y);
                m_state_to_set = m_grid.GetState(x, y);
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased)
        {
            m_editing = false;
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            if (m_editing)
            {
                sf::Vector2i mouse_pos = sf::Mouse::getPosition(*m_pt_display_window);
                if (IsMouseInWindow(mouse_pos))
                {
                    const uint32_t x = static_cast<uint32_t>(WindowToGridCoord(mouse_pos.x));
                    const uint32_t y = static_cast<uint32_t>(WindowToGridCoord(mouse_pos.y));
                    m_grid.SetState(x, y, m_state_to_set);
                }
            }            
        }

        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
        {
            m_pt_display_window->close();
        }

        // Increase Framerate Limit in edit mode for reactivity but decrease when running iterations of the game so user have time for observations
        if(m_edit_mode)
        {
            m_pt_display_window->setFramerateLimit(30);
        }
        else
        {
            m_pt_display_window->setFramerateLimit(5);
        }
    }
}

void GameManager::UpdateGameState()
{
    if (m_edit_mode == false)
    {
        m_nb_iteration++;
        m_txt_stats.setString(std::to_string(m_nb_iteration));
        m_grid.UpdateGrid();
    }
}

void GameManager::UpdateDisplay()
{
    m_pt_display_window->clear(sf::Color::Black);

    m_grid.DrawGrid(m_pt_display_window);
    m_pt_display_window->draw(m_txt_title);
    m_pt_display_window->draw(m_txt_footer);
    m_pt_display_window->draw(m_txt_stats);

    m_pt_display_window->display();
}

