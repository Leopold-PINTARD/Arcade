/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Grid
*/

#include <random>
#include <stdexcept>

#include "Grid.hpp"

Grid::Grid(int width, int height, int mines)
    : width(width), height(height), mines(mines), generated(false) {
    generateGrid();
}

Grid::~Grid() {
}

Grid::Cell Grid::getCell(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Invalid cell coordinates");
    }
    return cells[y][x];
}

void Grid::setCell(int x, int y, CellType cell) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Invalid cell coordinates");
    }
    cells[y][x].type = cell;
}

Grid::CellType Grid::revealCell(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Invalid cell coordinates");
    }
    cells[y][x].isRevealed = true;
    if (!generated)
        generateMines(x, y);
    return cells[y][x].type;
}

void Grid::flagCell(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Invalid cell coordinates");
    }
    cells[y][x].isFlagged = true;
}

void Grid::unflagCell(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Invalid cell coordinates");
    }
    cells[y][x].isFlagged = false;
}

void Grid::generateGrid() {
    cells.resize(height, std::vector<Cell>(width, {EMPTY, 0, false, false}));
}

void Grid::generateMines(int x, int y) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> randomNumber(0, width * height - 1);

    for (int i = 0; i < mines; ++i) {
        int randomX = randomNumber(gen) % width;
        int randomY = randomNumber(gen) % height;

        if (cells[randomY][randomX].type == EMPTY && (randomX != x ||
            randomY != y)) {
            cells[randomY][randomX].type = MINE;
        } else {
            i--;
        }
    }
    calculateAdjacentMines();
    generated = true;
}

void Grid::checkAdjacentMines(int x, int y) {
    int adjacentMines = 0;

    if (cells[y][x].type == MINE) {
        return;
    }
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) {
                continue;
            }
            int newX = x + dx;
            int newY = y + dy;
            if (newX >= 0 && newX < width && newY >= 0 && newY < height &&
                cells[newY][newX].type == MINE) {
                adjacentMines++;
            }
        }
    }
    cells[y][x].adjacentMines = adjacentMines;
}

void Grid::calculateAdjacentMines() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            checkAdjacentMines(x, y);
        }
    }
}
