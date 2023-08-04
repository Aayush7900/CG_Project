#include <iostream>
#include <conio.h>
#include <graphics.h>
using namespace std;

const int WINDOW_SIZE = 300;
const int CELL_SIZE = WINDOW_SIZE / 3;

void drawBoard() {
	setcolor(WHITE);
    line(CELL_SIZE, 0, CELL_SIZE, WINDOW_SIZE);
    line(2 * CELL_SIZE, 0, 2 * CELL_SIZE, WINDOW_SIZE);
    line(0, CELL_SIZE, WINDOW_SIZE, CELL_SIZE);
    line(0, 2 * CELL_SIZE, WINDOW_SIZE, 2 * CELL_SIZE);
}

char checkWin(char board[3][3], int& x1, int& y1, int& x2, int& y2) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            x1 = 0;
            y1 = i * CELL_SIZE + CELL_SIZE / 2;
            x2 = WINDOW_SIZE;
            y2 = i * CELL_SIZE + CELL_SIZE / 2;
            return board[i][0];
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            x1 = i * CELL_SIZE + CELL_SIZE / 2;
            y1 = 0;
            x2 = i * CELL_SIZE + CELL_SIZE / 2;
            y2 = WINDOW_SIZE;
            return board[0][i];
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        x1 = 0;
        y1 = 0;
        x2 = WINDOW_SIZE;
        y2 = WINDOW_SIZE;
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        x1 = WINDOW_SIZE;
        y1 = 0;
        x2 = 0;
        y2 = WINDOW_SIZE;
        return board[0][2];
    }

    // Check for draw
    bool draw = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                draw = false;
                break;
            }
        }
        if (!draw){
            break;
        }
    }
    if (draw){
        return 'D';
	}
    // Game still ongoing
    return ' ';
}

void drawMove(int row, int col, char player) {
    int x = col * CELL_SIZE + CELL_SIZE / 2;
    int y = row * CELL_SIZE + CELL_SIZE / 2;

    if (player == 'X') {
        // Draw 'X'
        setcolor(RED);
        line(x - 25, y - 25, x + 25, y + 25);
        line(x - 25, y + 25, x + 25, y - 25);
    } else if (player == 'O') {
        // Draw 'O'
        setcolor(RED);
        circle(x, y, 25);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    char currentPlayer = 'X';
    char result;
    int x1, y1, x2, y2; // Coordinates for the line
    int lastRow, lastCol;
    
    while (true) {
        cleardevice();
        drawBoard();

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] != ' ') {
                    drawMove(i, j, board[i][j]);
                }
            }
        }

        int mouseClick = 0;
        while (!mouseClick) {
            if (ismouseclick(WM_LBUTTONDOWN)) {
                int x, y;
                getmouseclick(WM_LBUTTONDOWN, x, y);
                int row = y / CELL_SIZE;
                int col = x / CELL_SIZE;

                if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
                    board[row][col] = currentPlayer;
                    mouseClick = 1;
                    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                    lastRow = row;
                    lastCol = col;
                }
            }
        }

        // Check for win or draw
        result = checkWin(board, x1, y1, x2, y2);
        if (result == 'X') {
            line(x1, y1, x2, y2); // Draw the winning line
        	drawMove(lastRow, lastCol, board[lastRow][lastCol]);
			setcolor(RED);
            settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
            outtextxy((WINDOW_SIZE-textwidth("Player 1 wins!"))/2, WINDOW_SIZE / 2 + 150,(char*)"Player 1 wins!");
			break;
        } 
        else if(result == 'O') {
        	line(x1, y1, x2, y2); // Draw the winning line
			drawMove(lastRow, lastCol, board[lastRow][lastCol]);
			setcolor(RED);
            settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
            outtextxy((WINDOW_SIZE-textwidth("Player 2 wins!"))/2, WINDOW_SIZE / 2 + 150,(char*)"Player 2 wins!");
			break;
		}
		else if (result == 'D') {
			drawMove(lastRow, lastCol, board[lastRow][lastCol]);
			setcolor(RED);
			outtextxy((WINDOW_SIZE-textwidth("Its a Draw!"))/2, WINDOW_SIZE / 2 + 150,(char*)"Its a Draw!");
            break;
        }

        delay(200);
    }

    getch(); // Wait for a key press before closing the graphics window
    closegraph();
    return 0;
}

