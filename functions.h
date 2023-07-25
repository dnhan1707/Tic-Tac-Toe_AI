//
// Created by ASUS on 3/28/2023.
//

#ifndef TIC_TAC_TOE_FUNCTIONS_H
#define TIC_TAC_TOE_FUNCTIONS_H

#include <iostream>
#include "string"

void tic_tac_toe();
void original_board(char board[][3]);
void change_player(char & cur_player);

bool check_if_win(char board[][3], char cur_player, int row, int column);
bool check_vertically(char board[][3], char cur_player, int col);
bool check_horizontally(char board[][3], char cur_player, int row);
bool check_diagonally(char board[][3], char cur_player);
bool draw(char board[][3]);

void human_and_bot(char board[][3], char cur_player, int &row, int &column, int turn);
bool check_if_not_blank(char board[][3], int row, int column);

void outPut(char board[][3]);

void ai_move(char board[][3], char cur_player, int& real_row, int &real_col);
int minimax(char board[][3], char cur_player, int row, int col);

void computer_turn(char board[][3], char cur_player, int & row, int & column);
#endif //TIC_TAC_TOE_FUNCTIONS_H
