#include <stdio.h>
#include <assert.h>

/*
 * The status of a line.
 */
enum {
    NO_LINE = 0, /* No line */
    RED_LINE = 1,
    BLUE_LINE = 2
};

/*
 * The board records the colors of the lines.
 * board[0] = color of 12
 * board[1] = color of 13
 * ...
 * board[14] = color of 56
 */
typedef char BoardType[15];
typedef char PlayerType; /* A player should be RED or BLUE. */

void Initialize(BoardType board) {
    for (int i = 0; i < 15; i++) {
        board[i] = 0;
    }
}

PlayerType Opponent(PlayerType player) {
    switch (player) {
        case RED_LINE: return BLUE_LINE; break;
        case BLUE_LINE: return RED_LINE; break;
    }
}

int HasWon(BoardType board, PlayerType player) {
    PlayerType opponent = Opponent(player);
    int all[20][3] = {
        {0, 1, 5},
        {0, 2, 6},
        {0, 3, 7},
        {0, 4, 8},
        {1, 2, 9},
        {1, 3, 10},
        {1, 4, 11},
        {2, 3, 12},
        {2, 4, 13},
        {3, 4, 14},
        {5, 6, 9},
        {5, 7, 10},
        {5, 8, 11},
        {6, 7, 12},
        {6, 8, 13},
        {7, 8, 14},
        {9, 10, 12},
        {9, 11, 13},
        {10, 11, 14},
        {12, 13, 14}
    };
    for (int i = 0; i < 20; i++) {
        int count = 0;
        for (int j = 0; j < 3; j++) {
            if (board[all[i][j]] == opponent) {
                count++;
            }
        }
        if (count == 3) {
            return 1;
        }
    }
    return 0;
}

int IsFull(BoardType board) {
    for (int i = 0; i < 15; i++) {
        if (board[i] == 0) {
            return 0;
        }
    }
    return 1;
}

typedef struct {
    int line; /* 0 for 12, 1 for 13, ..., 14 for 56. */
    int score; /* -1 for loss, 0 for draw, 1 for win. */
} MoveType;

MoveType BestMove(BoardType board, PlayerType player) {
    PlayerType opponent = Opponent(player);
    MoveType bestMove = { .line = -1, .score = -1 };
    int temp1 = 10;
    for (int i = 0; i < 15; i++) {
        if (board[i] == 0) {
            board[i] = player;
            if (HasWon(board, opponent)) {
                board[i] = 0;
                if (bestMove.score == -1) {
                    bestMove.line = i;
                }
                continue;
            }
            MoveType response = BestMove(board, opponent);
            if (response.score < 0) {
                bestMove.line = i;
                bestMove.score = 1 - response.score;
                board[i] = 0;
                return bestMove;
            } else {
                int temp = -1 - response.score;
                if (temp < temp1) {
                    bestMove.score = temp;
                    temp1 = temp;
                    bestMove.line = i;
                }
            }
            board[i] = 0;
        }
    }
    return bestMove;
}

void PrintBoard(BoardType board) {
    for (int i = 0; i < 15; ++i) {
        switch (board[i]) {
            case NO_LINE: printf(".  "); break;
            case RED_LINE: printf("R  "); break;
            case BLUE_LINE: printf("B  "); break;
        }
    }
    printf("\n");
}

int main() {
    BoardType game;
    Initialize(game);

    printf("Welcome to the game!\nLet's start the game\n");
    printf("Choose your player:\n 1 for Red\n 2 for Blue\n ");
    int bot;
    int gameOver = 0;
    PlayerType currentPlayer;
    PlayerType userPlayer;
    PlayerType computerPlayer;
    scanf("%d", &bot);
    if (bot == 1) {
        userPlayer = RED_LINE;
        computerPlayer = BLUE_LINE;
        currentPlayer = userPlayer; 
    } else {
        userPlayer = BLUE_LINE;
        computerPlayer = RED_LINE; 
        currentPlayer = computerPlayer; 
    }

    printf("Who should play first?\n");
    printf("Enter 1 for user\n");
    printf("Enter 2 for Computer\n");

    scanf("%d", &bot);

    if (bot == 1) {
        currentPlayer = userPlayer;
    } else {
        currentPlayer = computerPlayer;
    }

    while (!gameOver) {
        if (currentPlayer == userPlayer) {
            int userMove;
            printf("Your move (Enter a number between 0 and 14): ");
            scanf("%d", &userMove);

            game[userMove] = userPlayer;
        } else {
            MoveType computerMove = BestMove(game, computerPlayer);
            game[computerMove.line] = computerPlayer;
            printf("Computer's move: %d\n", computerMove.line);
        }

        PrintBoard(game);

        if (HasWon(game, userPlayer)) {
            printf("User has won!\n");
            gameOver = 1;
            break;
        } else if (HasWon(game, computerPlayer)) {
            printf("Computer has won!\nTry again!\n");

            gameOver = 1;
            break;
        } else if (IsFull(game)) {
            printf("It's a draw!\n");
            gameOver = 1;
            break;
        }

        currentPlayer = Opponent(currentPlayer);
    }

    printf("Game over.\n");

    return 0;
}
