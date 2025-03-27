/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Ncurses
*/

#pragma once

#include <ncurses.h>
#include <string>
#include <memory>
#include <vector>
#include <map>

/**
 * @brief Wrapper class for the NCurses library
 *
 * This class provides a simplified interface for the NCurses library,
 * offering window management, input handling, and drawing primitives.
 */
class Ncurses {
    public:
        /**
         * @brief Color enumeration for terminal display
         */
        enum class Color {
            BLACK = 0,
            RED,
            GREEN,
            YELLOW,
            BLUE,
            MAGENTA,
            CYAN,
            WHITE,
            DEFAULT
        };

        /**
         * @brief Key enumeration for keyboard input handling
         */
        enum class Key {
            NONE,
            UP,
            DOWN,
            LEFT,
            RIGHT,
            ENTER,
            ESCAPE,
            SPACE,
            BACKSPACE,
            TAB,

            A,
            B,
            C,
            D,
            E,
            F,
            G,
            H,
            I,
            J,
            K,
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            S,
            T,
            U,
            V,
            W,
            X,
            Y,
            Z,

            NUM0,
            NUM1,
            NUM2,
            NUM3,
            NUM4,
            NUM5,
            NUM6,
            NUM7,
            NUM8,
            NUM9,

            F1,
            F2,
            F3,
            F4,
            F5,
            F6,
            F7,
            F8,
            F9,
            F10,
            F11,
            F12
        };

        /**
         * @brief Coordinate structure for 2D points
         */
        struct Coordinate {
            int x;
            int y;
        };

        /**
         * @brief Event type enumeration for mouse events
         */
        enum class EventType {
            NONE,
            BUTTON_PRESS,
            BUTTON_RELEASE,
            BUTTON_CLICK,
            BUTTON_DOUBLE_CLICK,
            BUTTON_TRIPLE_CLICK,
            BUTTON_MOTION
        };

        /**
         * @brief Button enumeration for mouse events
         */
        enum class Button {
            NONE,
            LEFT,
            MIDDLE,
            RIGHT,
            SCROLL_UP,
            SCROLL_DOWN
        };

        /**
         * @brief Mouse event structure
         */
        struct MouseEvent {
            EventType type;
            Button button;
            Coordinate position;
            bool shift;
            bool ctrl;
            bool alt;
        };

        /**
         * @brief Default constructor
         */
        Ncurses();

        /**
         * @brief constructor with initialization and resize
         * @param width Width of the window
         * @param height Height of the window
         *
         */
        Ncurses(int width, int height);

        /**
         * @brief Destructor
         *
         */
        ~Ncurses();

        /**
         * @brief Initialize NCurses library
         */
        void initialize();

        /**
         * @brief Clean up and end NCurses mode
         */
        void cleanup();

        /**
         * @brief Clear the screen
         */
        void clear();

        /**
         * @brief Erase the screen
         */
        void erase();

        /**
         * @brief Refresh the screen to display changes
         */
        void refresh();

        /**
         * @brief Resize the window
         *
         * @param width New width of the window
         * @param height New height of the window
         */
        void resize(int width, int height);

        /**
         * @brief Get the current screen dimensions
         *
         * @return std::pair<int, int> Width and height of the screen
         */
        Coordinate getScreenSize() const;

        /**
         * @brief Get the current keyboard input
         *
         * @return Key The key that was pressed
         */
        Key getInput();

        /**
         * @brief Check if a key has been pressed
         *
         * @return true If a key is pressed
         * @return false If no key is pressed
         */
        bool isKeyPressed();

        /**
         * @brief Draw a single character at the specified position
         *
         * @param xy Coordinate to draw at
         * @param c Character to draw
         * @param fg Foreground color
         * @param bg Background color
         */
        void drawPixel(Coordinate xy, char c, Color fg = Color::WHITE, Color
            bg = Color::BLACK);

        /**
         * @brief Draw text at the specified position
         *
         * @param xy Coordinate to draw at
         * @param text The text to draw
         * @param fg Foreground color
         * @param bg Background color
         */
        void drawText(Coordinate xy, const std::string& text,
            Color fg = Color::WHITE, Color bg = Color::BLACK);

        /**
         * @brief Draw a filled rectangle
         *
         * @param xy Top-left corner of rectangle
         * @param width Width of rectangle
         * @param height Height of rectangle
         * @param c Character to fill rectangle with
         * @param fg Foreground color
         * @param bg Background color
         */
        void drawRect(Coordinate xy, int width, int height, char c, Color
            fg = Color::WHITE, Color bg = Color::BLACK);

        /**
         * @brief Draw a box outline
         *
         * @param xy Top-left corner of box
         * @param width Width ostd::pair<int, int>f box
         * @param height Height of box
         * @param fg Foreground color
         * @param bg Background color
         */
        void drawBox(Coordinate xy, int width, int height, Color fg =
            Color::WHITE, Color bg = Color::BLACK);

        /**
         * @brief Draw a line between two points
         * 
         * @param xy1 First point
         * @param xy2 Second point
         * @param c Character to draw line with
         * @param fg Foreground color
         * @param bg Background color
         */
        void drawLine(Coordinate xy1, Coordinate xy2, char c, Color fg =
            Color::WHITE, Color bg = Color::BLACK);

        /**
         * @brief Initialize color support
         */
        void initColors();

        /**
         * @brief Get the color pair number for a foreground/background combination
         *
         * @param fg Foreground color
         * @param bg Background color
         * @return short Color pair identifier
         */
        short getPairNumber(Color fg, Color bg) const;

        /**
         * @brief Set the input timeout (in milliseconds)
         * @param milliseconds The timeout in milliseconds (-1 for blocking, 0 for non-blocking)
         */
        void setTimeout(int milliseconds);

        /**
         * @brief Define a custom color
         * @param colorIndex The index of the color to define
         * @param r Red component (0-1000)
         * @param g Green component (0-1000)
         * @param b Blue component (0-1000)
         */
        void defineColor(short colorIndex, short r, short g, short b);

        /**
         * @brief Create a new sub-window
         * @param x X position
         * @param y Y position
         * @param width Width of the window
         * @param height Height of the window
         * @return A new Ncurses window instance
         */
        std::unique_ptr<Ncurses> createSubWindow(int x, int y, int width, int
            height);

        /**
         * @brief Enable/disable mouse events
         * @param enable True to enable, false to disable
         */
        void enableMouse(bool enable);

        /**
         * @brief Get a mouse event
         * @return A struct containing mouse event information
         */
        MouseEvent getMouseEvent();

    private:
        WINDOW* _window;
        bool _initialized;
        std::map<int, Key> _keyMap;

        /**
         * @brief Initialize color pairs for the terminal
         */
        void initColorPairs();

        std::map<std::pair<Color, Color>, short> _colorPairs;
        short _nextPairId;

        /**
         * @brief Initialize the key mapping
         */
        void initKeyMap();

        /**
         * @brief Map an NCurses key code to our Key enum
         *
         * @param key NCurses key code
         * @return Key Mapped key enum value
         */
        Key mapKey(int key) const;
};
