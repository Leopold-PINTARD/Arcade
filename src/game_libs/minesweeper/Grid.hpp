/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Grid
*/

#pragma once

#include <string>
#include <vector>

class Grid {
 public:
    enum CellType {
        EMPTY,
        MINE,
        FLAGGED,
        REVEALED
    };

    struct Cell {
        CellType type;
        int adjacentMines;
        bool isRevealed;
        bool isFlagged;
    };

    using GridCells = std::vector<std::vector<Cell>>;

    Grid(int width, int height, int mines);
    ~Grid();

    Cell getCell(int x, int y) const;
    void setCell(int x, int y, CellType cell);
    GridCells getCells() const { return cells; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getMines() const { return mines; }
    bool isGenerated() const { return generated; }
    CellType revealCell(int x, int y);
    void revealAllCells();
    void revealAdjacentCells(int x, int y);
    void flagCell(int x, int y);
    void unflagCell(int x, int y);

 private:
    GridCells cells;
    int width;
    int height;
    int mines;
    bool generated;

    void generateGrid();
    void generateMines(int x, int y);
    void calculateAdjacentMines();
    void checkAdjacentMines(int x, int y);
};
