/* Implement connect 4 on a 5 (columns) x 4 (rows) board. */
#include <stdio.h>
#include <assert.h>

#define WINNING_STREAK 4

typedef char Player;
typedef char Board[4][5];

void initializeBoard(Board board)
{
    for (int row=0; row<4; ++row) {
        for (int col=0; col < 5; ++col) {
            board[row][col] = '.';
        }
    }
}

int hasWon(Board board, Player player)
{
    int count = 0;
    for (int i=0; i<4; i++) {
        count = 0;
        for (int j=0; j < 4; j++) {
            if (board[i][j] == player) {
                count++;
            }
        }
        if (count == WINNING_STREAK) {
            return 1;
        }
        count = 0;
        for (int j = 1; j < 5; j++) {
            if (board[i][j] == player) {
                count++;
            }
        }
        if (count==WINNING_STREAK) {
            return 1;
        }
    }
    for (int j = 0; j < 5; j++) {
        count = 0;
        for (int i = 0; i < 4; i++) {
            if (board[i][j]==player) {
                count++;
            }
        }
        if (count == WINNING_STREAK) {
            return 1;
        }
    }
    count = 0;
    for (int i = 0; i < 4; i++) {
        if (board[i][i] == player) {
            count++;
        }
    }
    if (count == WINNING_STREAK) {
        return 1;
    }
    count = 0;
    for (int i = 0; i < 4; i++) {
        if (board[i][i + 1] == player) {
            count++;
        }
    }
    if (count == WINNING_STREAK) {
        return 1;
    }
    count = 0;
    for (int i = 0; i < 4; i++) {
        if (board[i][4 - i] == player) {
            count++;
        }
    }
    if (count == WINNING_STREAK) {
        return 1;
    }
    count = 0;
    for (int i = 0; i < 4; i++) {
        if (board[i][3 - i] == player) {
            count++;
        }
    }
    if (count == WINNING_STREAK) {
        return 1;
    }
    return 0;
}

int isFull(Board board)
{
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (board[row][col] == '.') {
                return 0;
            }
        }
    }
    return 1;
}

Player otherPlayer(Player player)
{
    switch (player) {
    case 'r':
        return 'b';
    case 'b':
        return 'r';
    default:
        assert(0);
    }
}

typedef struct {
    int col;
    int score;
} Move;

void addDisc(Board board, Player player, int col) {
    int row = 0;
    for (int i = 0; i < 4; i++) {
        if (board[i][col]=='.') {
            row = i;
        }
    }
    board[row][col] = player;
}

void removeDisc(Board board, int col) {
    int row = 0;
    for (int i = 0; i < 4; i++) {
        if (board[i][col] != '.') {
            row = i;
            break;
        }
    }
    board[row][col] = '.';
}

Move bestMove(Board board, Player player)
{
    Move response;
    Move candidate;
    int noCandidate = 1;

    assert(!isFull(board));
    assert(!hasWon(board, player));
    assert(!hasWon(board, otherPlayer(player)));

    for (int col = 0; col < 5; ++col) {
        if (board[0][col]=='.') {
            addDisc(board, player, col);
            if (hasWon(board, player)) {
                removeDisc(board, col);
                return (Move) {col, 1};
            }
            removeDisc(board, col);
        }
    }

    for (int col = 0; col < 5; ++col) {
        if (board[0][col] == '.') {
            addDisc(board, player, col);
            if (isFull(board)) {
                removeDisc(board, col);
                return (Move) {col, 0};
            }

            response = bestMove(board, otherPlayer(player));
            removeDisc(board, col);
            if (response.score == -1) {
                return (Move) {.col = col, .score = 1};
            } else if (response.score == 0) {
                candidate = (Move) {.col = col, .score = 0};
                noCandidate = 0;
            } else { /* response.score == +1 */
                if (noCandidate) {
                    candidate = (Move) {.col = col, .score = -1};
                    noCandidate = 0;
                }
            }
        }
    }

    return candidate;
}

void printBoard(Board board)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n---------------\n");
}

int main()
{
    printf("Welcome to the game!\n");
    printf("Let's start the game!\n");
    Board game;
    initializeBoard(game);
    Player player;
    Player AI;
    Player current;
    int temp;
    int column;
    printf("Choose red or blue\n");
    printf("Choose 'r' for Red\n");
    printf("Choose 'b' for Blue\n");
    scanf(" %c", &player);

    if (player == 'r') {
        AI = 'b';
    } else {
        AI = 'r';
    }
    printf("Choose who should play first\n");
    printf("Enter 1 for user\n");
    printf("Enter 2 for computer\n");
    scanf("%d", &temp);
    if (temp == 1) {
        current = player;
    } else {
        current = AI;
    }
    if (current == player) {
        printf("Your turn (enter column 0-4): ");
        scanf("%d", &column);
        addDisc(game, player, column);
        printBoard(game);
        if (column == 0) {
            addDisc(game, AI, 1);
        }
        if (column == 1) {
            addDisc(game, AI, 4);
        }
        if (column == 2) {
            addDisc(game, AI, 4);
        }
        if (column == 3) {
            addDisc(game, AI, 0);
        }
        if (column == 4) {
            addDisc(game, AI, 3);
        }
    } else {
        addDisc(game, AI, 3);
        printBoard(game);
        printf("Your turn (enter column 0-4): ");
        scanf("%d", &column);
        addDisc(game, player, column);
        printBoard(game);
        if (column == 0) {
            addDisc(game, AI, 4);
        }
        if (column == 1) {
            addDisc(game, AI, 1);
        }
        if (column == 2) {
            addDisc(game, AI, 3);
        }
        if (column == 3) {
            addDisc(game, AI, 1);
        }
        if (column == 4) {
            addDisc(game, AI, 4);
        }
        current = player;
    }

    while (1) {
        printBoard(game);
        if (player == current) {
            printf("Your turn (enter column 0-4): ");
            scanf("%d", &column);
            if (column < 0 || column > 4 || game[0][column] != '.') {
                printf("Invalid move. Try again.\n");
                continue;
            }
            addDisc(game, player, column);
            if (hasWon(game, player)) {
                printBoard(game);
                printf("You win! Congratulations!\n");
                break;
            }
        } else {
            Move computerMove = bestMove(game, current);
            printf("Computer's turn: %d\n", computerMove.col);
            addDisc(game, current, computerMove.col);
            if (hasWon(game, current)) {
                printBoard(game);
                printf("Computer wins\n");
                printf("Try again \n");
                break;
            }
        }
        current = otherPlayer(current);
        if (isFull(game)) {
            printBoard(game);
            printf("It's a draw!\n");
            printf("try one more time \n");
            break;
        }
    }

    return 0;
}


