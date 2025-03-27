#include <iostream>
#include "wrapper/ncurses/Ncurses.hpp"
#include <chrono>
#include <thread>
#include <string>

int main() {
    // Initialize Ncurses
    Ncurses ncurses;
    
    // Enable mouse events
    ncurses.enableMouse(true);
    
    // Get screen size
    Ncurses::Coordinate screenSize = ncurses.getScreenSize();
    
    // Draw title and instructions
    ncurses.drawText({2, 1}, "Ncurses Mouse Event Test", Ncurses::Color::GREEN);
    ncurses.drawText({2, 3}, "Move mouse or click buttons to see events", Ncurses::Color::WHITE);
    ncurses.drawText({2, 4}, "Press 'q' to quit", Ncurses::Color::WHITE);
    
    // Draw a border
    ncurses.drawBox({1, 0}, screenSize.x - 2, screenSize.y - 2);
    
    // Track last event line
    int eventLine = 6;
    bool running = true;
    
    while (running) {
        // Check for keyboard input
        if (ncurses.isKeyPressed()) {
            Ncurses::Key key = ncurses.getInput();
            if (key == Ncurses::Key::Q || key == Ncurses::Key::ESCAPE) {
                running = false;
                break;
            }
        }
        
        // Get and display mouse events
        Ncurses::MouseEvent event = ncurses.getMouseEvent();
        
        if (event.type != Ncurses::EventType::NONE) {
            // Clear the event display area if it's getting full
            if (eventLine > screenSize.y - 4) {
                for (int i = 6; i < screenSize.y - 2; i++) {
                    ncurses.drawText({2, i}, std::string(screenSize.x - 4, ' '));
                }
                eventLine = 6;
            }
            
            // Convert event type to string
            std::string eventType;
            switch (event.type) {
                case Ncurses::EventType::BUTTON_PRESS: eventType = "PRESS"; break;
                case Ncurses::EventType::BUTTON_RELEASE: eventType = "RELEASE"; break;
                case Ncurses::EventType::BUTTON_CLICK: eventType = "CLICK"; break;
                case Ncurses::EventType::BUTTON_DOUBLE_CLICK: eventType = "DOUBLE_CLICK"; break;
                case Ncurses::EventType::BUTTON_TRIPLE_CLICK: eventType = "TRIPLE_CLICK"; break;
                case Ncurses::EventType::BUTTON_MOTION: eventType = "MOTION"; break;
                default: eventType = "UNKNOWN"; break;
            }
            
            // Convert button type to string
            std::string buttonType;
            switch (event.button) {
                case Ncurses::Button::LEFT: buttonType = "LEFT"; break;
                case Ncurses::Button::MIDDLE: buttonType = "MIDDLE"; break;
                case Ncurses::Button::RIGHT: buttonType = "RIGHT"; break;
                case Ncurses::Button::SCROLL_UP: buttonType = "SCROLL_UP"; break;
                case Ncurses::Button::SCROLL_DOWN: buttonType = "SCROLL_DOWN"; break;
                default: buttonType = "NONE"; break;
            }
            
            // Display event details
            std::string eventInfo = "Event: " + eventType + ", Button: " + buttonType + 
                                   ", Position: (" + std::to_string(event.position.x) + 
                                   ", " + std::to_string(event.position.y) + ")";
            
            if (event.shift || event.ctrl || event.alt) {
                eventInfo += " Modifiers:";
                if (event.shift) eventInfo += " SHIFT";
                if (event.ctrl) eventInfo += " CTRL";
                if (event.alt) eventInfo += " ALT";
            }
            
            // Draw the event info
            ncurses.drawText({2, eventLine++}, eventInfo);
            
            // Draw a cursor at the mouse position if it's not a motion event (to reduce flicker)
            if (event.type != Ncurses::EventType::BUTTON_MOTION) {
                // Refresh the screen to clear previous markers
                ncurses.refresh();
                
                // Draw X at mouse position
                if (event.position.x > 0 && event.position.x < screenSize.x - 1 &&
                    event.position.y > 0 && event.position.y < screenSize.y - 1) {
                    ncurses.drawPixel(event.position, 'X', Ncurses::Color::RED);
                }
            }
        }
        
        // Refresh screen
        ncurses.refresh();
        
        // Add a small delay to prevent excessive CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    
    // Disable mouse and clean up
    ncurses.enableMouse(false);
    ncurses.cleanup();
    
    return 0;
}