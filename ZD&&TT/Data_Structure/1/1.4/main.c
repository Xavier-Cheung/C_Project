#include <stdio.h>

#define SIZE 19

int checkWin(int board[SIZE][SIZE], int row, int col) {
    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
    int i, j, count;

    for (i = 0; i < 4; i++) {
        count = 1; // 开始时计数为1，包括当前的棋子
        // 向一个方向检查
        for (j = 1; j < 5; j++) {
            int newRow = row + directions[i][0] * j;
            int newCol = col + directions[i][1] * j;
            if (newRow < 0 || newRow >= SIZE || newCol < 0 || newCol >= SIZE || board[newRow][newCol] != board[row][col])
                break;
            count++;
        }
        // 向相反方向检查
        for (j = 1; j < 5; j++) {
            int newRow = row - directions[i][0] * j;
            int newCol = col - directions[i][1] * j;
            if (newRow < 0 || newRow >= SIZE || newCol < 0 || newCol >= SIZE || board[newRow][newCol] != board[row][col])
                break;
            count++;
        }
        if (count >= 5) return board[row][col]; // 找到五子连线
    }
    return 0; // 没有找到
}

int main() {
    int board[SIZE][SIZE];
    int i, j, result = 0;

    // 读取棋盘状态
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            scanf("%d", &board[i][j]);
        }
    }

    // 检查每个棋子
    for (i = 0; i < SIZE && result == 0; i++) {
        for (j = 0; j < SIZE && result == 0; j++) {
            if (board[i][j] != 0) {
                result = checkWin(board, i, j);
                if (result) {
                    printf("%d:%d,%d\n", result, i + 1, j + 1);
                }
            }
        }
    }

    if (result == 0) {
        printf("No\n");
    }

    return 0;
}
