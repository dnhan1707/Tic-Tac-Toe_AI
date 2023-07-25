//
// Created by ASUS on 3/28/2023.
//

#include "functions.h"
#include "ctime"


void tic_tac_toe() {
    char board[3][3];
    bool play;
    int column, row;
    int turn = 0;
    char cur_player = 'O';

    original_board(board);
    outPut(board);

    do {
        turn++;
        change_player(cur_player);
        human_and_bot(board, cur_player, row, column, turn);
        outPut(board);
        play = check_if_win(board, cur_player, row, column);
    } while (!play && !draw(board));

    if (play) {
        std::cout << cur_player << " Win";
    } else {
        std::cout << "Draw";
    }
}


void change_player(char &cur_player) {
    if (cur_player == 'X') {
        cur_player = 'O';
    } else {
        cur_player = 'X';
    }
}


bool check_if_win(char board[][3], char cur_player, int row, int col) {
    if (check_vertically(board, cur_player, col) || check_horizontally(board, cur_player, row) ||
        check_diagonally(board, cur_player)) {
        return true;
    } else {
        return false;
    }
}


bool check_vertically(char board[][3], char cur_player, int col) {
    bool win = true;
    for (int i = 0; i < 3; ++i) {
        if (board[i][col] != cur_player) {
            win = false;
            break;
        }
    }
    if (win) {
        return true;
    }
    return false;
}


bool check_horizontally(char board[][3], char cur_player, int row) {
    bool win = true;

    for (int i = 0; i < 3; ++i) {
        if (board[row][i] != cur_player) {
            win = false;
            break;
        }
    }
    if (win) {
        return true;
    }
    return false;
}


bool check_diagonally(char board[][3], char cur_player) {
    // Check from top left to bottom right
    bool win = true;
    for (int i = 0; i < 3; i++) {
        if (board[i][i] != cur_player) {
            win = false;
            break;
        }
    }
    if (win) {
        return true;
    }

    // Check from top right to bottom left
    win = true;
    for (int i = 0; i < 3; i++) {
        if (board[i][2 - i] != cur_player) {
            win = false;
            break;
        }
    }
    if (win) {
        return true;
    }
    return false;
}


bool draw(char board[][3]) {
    int count = 0;
    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            if (board[row][column] != '_') {
                count++;
            }
        }
    }
    if (count == 9) {
        return true;
    }
    return false;
}


void human_and_bot(char board[][3], char cur_player, int &row, int &column, int turn) {
    if (cur_player == 'X') {
        do {
            std::cout << "It is your turn\n";
            std::cout << "Enter the location\n";

            std::cout << "Row:\n";
            std::cin >> row;
            std::cout << "Column:\n";
            std::cin >> column;
        } while (check_if_not_blank(board, row, column) && row < 3 && column < 3);
        board[row][column] = cur_player;
    } else {
        if (turn == 1) {
            computer_turn(board, cur_player, row, column);
        } else {
            ai_move(board, cur_player, row, column);
        }

    }
}


void computer_turn(char board[][3], char cur_player, int &row, int &column) {
    srand(time(0));
    do {
        row = rand() % 3;
        column = rand() % 3;
    } while (board[row][column] != '_');
    board[row][column] = cur_player;
}


void outPut(char board[][3]) {
    for (int i = 0; i < 3; ++i)
    {
        std::cout << "|";
        for (int j = 0; j < 3; ++j)
        {
            std::cout << board[i][j] << "|";
        }
        std::cout << std::endl;
    }
}


void original_board(char board[][3]) {
    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            board[row][column] = '_';
        }
    }
}


bool check_if_not_blank(char board[][3], int row, int column) {
    if (board[row][column] == '_') {
        return false;
    } else {
        std::cout << "Please choose another box\n";
        return true;
    }
}


void ai_move(char board[][3], char cur_player, int& real_row, int &real_col) {
    int best_score = -100;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (board[row][col] == '_') {
                board[row][col] = cur_player;
                int score = minimax(board, cur_player, row, col);
                board[row][col] = '_';
                if (score > best_score) {
                    best_score = score;
                    real_row = row;
                    real_col = col;
                }
            }
        }
    }
    board[real_row][real_col] = cur_player;
}


int  minimax(char board[][3], char cur_player, int row, int col) {
    if (check_if_win(board, 'X', row, col)) {
        return -1;
    } else if (check_if_win(board, 'O', row, col)) {
        return 1;
    } else if (draw(board)) {
        return 0;
    } else {
        change_player(cur_player);
        if (cur_player == 'O' && !check_if_win(board, 'O', row, col)) {
            int best_score = -100;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (board[i][j] == '_') {
                        board[i][j] = 'O';
                        int score = minimax(board, 'O', i, j);
                        board[i][j] = '_';

                        if (score > best_score) {
                            best_score = score;
                        }
                    }
                }
            }
            return best_score;
        } else {
            int best_score = 100;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (board[i][j] == '_') {
                        board[i][j] = 'X';
                        int score = minimax(board, 'X', i, j);
                        board[i][j] = '_';

                        if (score < best_score) {
                            best_score = score;
                        }
                    }
                }
            }
            return best_score;
        }
    }
}
