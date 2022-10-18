#include "MinesweeperBoard.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>

MinesweeperBoard::MinesweeperBoard(int width, int height,GameMode mode):width(width),height(height)
{
//Generuje plansze o wymiarach width x height
    for (int column = 0; column < width; column++)
    {
        board.emplace_back();

        for (int row = 0; row < height; row++)
        {

            board[column].push_back({false, false, false});

        }
    }
//Tryb planszy w GameMode DEBUG
    if (mode == GameMode::DEBUG)
    {
        for (int i=0; i<height; i++)
        {
            board[0][i].hasMine = true;
            for (int j=0; j<width; j++)
            {
                if ( i == j)
                    board[i][j].hasMine = true;
                if ((j%2) == 0)
                    board[j][0].hasMine = true;
            }
        }
    }
//Tryb planszy w GameMode EASY
    if (mode == GameMode::EASY){
        int ClNum, RwNum;
        int Mines = int((width*height)*0.1);

        for (int i=0;i<=Mines;){
            ClNum = rand()%width;
            RwNum = rand()%height;
            if (!board[ClNum][RwNum].hasMine) {
                board[ClNum][RwNum].hasMine = true;
                i++;
            }
        }
    }
//Tryb planszy w GameMode NORMAL
    if (mode == GameMode::NORMAL)
    {
        int ClNum, RwNum;
        int Mines = int((width*height)*0.2);

        srand(time(0));
        for (int i=0;i<=Mines;)
        {
            ClNum = rand()%height;
            RwNum = rand()%width;
            if (!board[ClNum][RwNum].hasMine) {
                board[ClNum][RwNum].hasMine = true;
                i++;
            }
        }
    }
//Tryb planszy w GameMode HARD
    if (mode == GameMode::HARD)
    {
        int ClNum, RwNum;
        int Mines = int((width*height)*0.3);

        srand(time(0));
        for (int i=0;i<=Mines;)
        {
            ClNum = rand()%height;
            RwNum = rand()%width;
            if (!board[ClNum][RwNum].hasMine) {
                board[ClNum][RwNum].hasMine = true;
                i++;
            }
        }
    }
}
GameState State = GameState::RUNNING;

//Funkcja wyświetla status wszystkich pól
 void MinesweeperBoard::debug_display()
{
    for (int column = 0; column<height; column++)
    {
        for (int row = 0; row < width; row++)
        {
            std::cout << "[";

            if (board[column][row].hasMine)
                std::cout << "M";
            else
                std::cout << ".";
            if (board[column][row].isRevealed)
                std::cout << "o";
            else
                std::cout << ".";
            if (board[column][row].hasFlag)
                std::cout << "F";
            else
               std::cout << ".";

            std::cout << "]";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

//Funkcja zwraca szerokość planszy (ilość kolumn)
int MinesweeperBoard::getBoardWidth() const{
    //std::cout << width << std::endl;
    return width;
}

//Funkcja zwraca wysokość planszy (ilość wierszy)
int MinesweeperBoard::getBoardHeight()const{
    //std::cout << height << std::endl;
    return height;
}

//Funkcja zlicza ilość min na planszy
int MinesweeperBoard::getMineCount() const {
    int Mines=0;
    for( int i=0; i<height;i++)
    {
        for (int j=0; j<width; j++)
            if (board[i][j].hasMine)
                Mines++;
    }
    std::cout << Mines << std::endl;
    return Mines;
}

//Funkcja zlicza ilość min wokół podanego pola
int MinesweeperBoard::countMines(int row, int col) const {
     int Neighbour = 0;

     if (!board[row][col].isRevealed || !colIsValid(col) || !rowIsValid(row) )
         Neighbour = -1;
     if (board[row][col].isRevealed && colIsValid(col) && rowIsValid(row))
     {
         Neighbour = 0;
     if (rowIsValid(row-1) && colIsValid(col-1))
     {
         if (board[row-1][col-1].hasMine){
             Neighbour++;}}
    if (rowIsValid(row-1) && colIsValid(col))
    {
        if (board[row-1][col].hasMine){
            Neighbour++;}}
    if (rowIsValid(row-1) && colIsValid(col+1))
    {
        if (board[row-1][col+1].hasMine){
            Neighbour++;}}
    if (rowIsValid(row) && colIsValid(col-1))
    {
        if (board[row][col-1].hasMine){
            Neighbour++;}}
    if (rowIsValid(row) && colIsValid(col+1))
    {
        if (board[row][col+1].hasMine){
            Neighbour++;}}
    if (rowIsValid(row+1) && colIsValid(col-1))
    {
        if (board[row+1][col-1].hasMine){
            Neighbour++;}}
    if (rowIsValid(row+1) && colIsValid(col))
    {
        if (board[row+1][col].hasMine){
            Neighbour++;}}
    if (rowIsValid(row+1) && colIsValid(col+1))
    {
        if (board[row+1][col+1].hasMine){
            Neighbour++;}}
     }



    //std::cout << "Miny wokol pola "<< row << "," << col << " " << Neighbour << std::endl;
     return Neighbour;
 }

//Funkcja sprawdza, czy na danym polu jest flaga
bool MinesweeperBoard::hasFlag(int row, int col) const{

    if ( !rowIsValid(row) || !colIsValid(col) || !board[row][col].hasFlag || board[row][col].isRevealed){
        std::cout << "Nie ma flagi" << std::endl;
        return false;}
    else if (rowIsValid(row) || colIsValid(col) || board[row][col].hasFlag){
        std::cout << "Jest Flaga" << std::endl;
        return true;}
    return false;
}

//Funkcja ustawia flagę na danym polu (jeśli jest ono nieodkryte i nie ma na nim już flagi)
void MinesweeperBoard::toggleFlag(int row, int col) {
    if (!rowIsValid(row) || !colIsValid(col) || board[row][col].isRevealed || State != GameState::RUNNING)
        return;
    else if (board[row][col].hasFlag)
        board[row][col].hasFlag = false;
    else if (!board[row][col].hasFlag)
        board[row][col].hasFlag = true;


}

//Funkcja odkrywa dane pole
void MinesweeperBoard::revealField(int row, int col) {
     if (!rowIsValid(row) || !colIsValid(col) || board[row][col].isRevealed || board[row][col].hasFlag ||State != GameState::RUNNING)
         return;
     else if (!board[row][col].isRevealed)
         board[row][col].isRevealed = true;
 }

//Funkcja sprawdza, czy dane pole jest odkryte
bool MinesweeperBoard::isRevealed(int row, int col) const {
 if (board[row][col].isRevealed)
     return true;
 else
     return false;
 }

//Funkcja wyświetla informacje na temat danego pola
std::string MinesweeperBoard::getFieldInfo(int row, int col) const
{
     std::string Result[6] = { "#" , "F" , "_" , "X" , " ","bruh"  };
     if (!rowIsValid(row) || !colIsValid(col))
     {
         return Result[0];
     }
     if (!board[row][col].isRevealed && board[row][col].hasFlag)
     {
         return Result[1];
     }
     if(!board[row][col].isRevealed && !board[row][col].hasFlag)
     {
         return Result[2];}

     if(board[row][col].isRevealed && board[row][col].hasMine)
     {
         return Result[3];}

     if(board[row][col].isRevealed && countMines(row,col) == -1)
     {
         return Result[4];}

    if(board[row][col].isRevealed && countMines(row,col) >= -1)
    {
        return std::to_string(countMines(row,col));}

    else return Result[5];

}

//Funkcje sprawdzają, czy dane pole znajduje się na planszy
bool MinesweeperBoard::rowIsValid(int row) const {
    return (row >=0 && row < height);
}
bool MinesweeperBoard::colIsValid(int col) const {
    return (col >=0 && col < width);
}

//Funkcja określa obecny stan gry
GameState MinesweeperBoard::getGameState() const {
     int Mines = 0;
     int HiddenCells = 0;
     //Zliczam ilość ukrytych pól i min
    for (int column = 0; column < width; column++) {
        for (int row = 0; row < height; row++) {
            if (!board[row][column].isRevealed)
                HiddenCells++;
            if (board[row][column].hasMine)
                Mines++;
        }
    }

    //Sprawdzam warunki na stan gry
    for (int column = 0; column < width; column++)
    {
        for (int row = 0; row < height; row++)
        {
            if (board[row][column].hasMine && board[row][column].isRevealed)
                State = GameState::FINISHED_LOSS;
            else if (Mines == HiddenCells)
                State = GameState::FINISHED_WIN;
            else
                State = State;
        }
    }
    return State;
}



// DEKLARACJE MSTEXTVIEW
//Konstruktor
MsBoardTextView::MsBoardTextView(MinesweeperBoard & Board):board(Board){}
//Funkcja wyświetlająca planszę
void MsBoardTextView::display()
{
     int width = board.getBoardWidth();
     int height = board.getBoardHeight();

     std:: cout << "Numery nad plansza to numery kolumn!\n";
     std::cout << "Numery po lewej od planszy to numery wierszy!\n";
     std::cout << "  ";

    for (int wd = 0; wd < width; wd++)
    {
        std::cout <<  wd << " ";
    }
    std::cout<< std::endl;

        for (int wd = 0; wd < width; wd++)
        {   std::cout << wd << " ";
            for (int hg = 0; hg < height; hg++)
            {
                std::cout << board.getFieldInfo(wd,hg) << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

 }

 // DEKLARACJE MSCONTROLLER
 // Konstruktor
 MsTextController::MsTextController(MinesweeperBoard &Board, MsBoardTextView &view):board(Board),InnerView(view){}
 //Funkcja pozwalająca grac
 void MsTextController::play() {
     GameState InnerState = board.getGameState();
     int row;
     int col;
     int value;
     while (InnerState == GameState::RUNNING)
     {

         InnerView.display();
         board.debug_display();
         std::cout << "1. Odkryj pole" << std::endl;
         std::cout << "2. Postaw/Usun Flage" << std::endl;
         std::cout << "Wybierz czynnosc:";
         std::cin >> value;
         //Instrukcja do odkrywania pola
         if (value == 1){
             std::cout << "Podaj numer wiersza:";
             std::cin >> row;
             std:: cout << std::endl;
             std::cout << "Podaj numer kolumny:";
             std::cin >> col;
             std:: cout << std::endl;
             board.revealField(row,col);}
         //Instrukcja do ustawiania flagi
         else if (value == 2){
             std::cout << "Podaj numer wiersza:";
             std::cin >> row;
             std:: cout << std::endl;
             std::cout << "Podaj numer kolumny:";
             std::cin >> col;
             std:: cout << std::endl;
             board.toggleFlag(row,col);}

         InnerState = board.getGameState();
     }
     if (InnerState == GameState::FINISHED_WIN)
     {
         InnerView.display();
         std::cout << "Wszyskie pola bez min odkryte!\n" <<"Wygrales!\n";
     }
     if (InnerState == GameState::FINISHED_LOSS)
     {
         InnerView.display();
         std::cout << "Odkryto bombe !\n" <<"Przegrales!\n";
     }
 }
