#pragma once
#include <vector>
#include <string>

enum class GameMode  { DEBUG, EASY, NORMAL, HARD };
enum class GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };

struct Field
{
    bool hasMine;
    bool hasFlag;
    bool isRevealed;
};

class MinesweeperBoard {
public:
    //MinesweeperBoard();
    MinesweeperBoard(int width, int height,GameMode);
    void debug_display();
    int getBoardWidth() const;
    int getBoardHeight() const;
    int getMineCount() const;
    int countMines(int row, int col) const;
    bool hasFlag(int row, int col) const;
    void toggleFlag(int row, int col);
    void revealField(int row, int col);
    bool isRevealed(int row, int col) const;
    GameState getGameState() const;
    std::string getFieldInfo(int row, int col) const;
    std::vector<std::vector<Field>>board;
    bool rowIsValid(int row) const;
    bool colIsValid(int col) const;

private:

    int width;
    int height;
};

//Wyświetla informacje o polach, które powinien widzieć gracz
class MsBoardTextView{
    MinesweeperBoard & board;
public:
    explicit MsBoardTextView(MinesweeperBoard & Board);
    void display();
};

class MsTextController{
    MinesweeperBoard &board;
    MsBoardTextView &InnerView;
public:
    explicit MsTextController ( MinesweeperBoard &Board,MsBoardTextView &view );
    void play();

};
