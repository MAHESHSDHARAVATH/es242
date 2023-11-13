#include <cstdio>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <tuple>
#include <iostream>
#include <queue>
#include <math.h>
#include <assert.h>
#include <utility>
using namespace std;

struct Board {
    int elements[7];
};

struct ColorBoard {
    char colors[6][4];
};

Board translate(const ColorBoard& colorBoard) {
    Board result;
    string str;
    string colorArray[21] = {"rgw", "wrg", "gwr", "rwb", "brw", "wbr", "ryg", "gry", "ygr", "rby", "yrb", "byr", "owg", "gow", "wgo", "obw", "wob", "bwo", "oyb", "boy", "ybo"};
    
    str.push_back(colorBoard.colors[0][0]);
    str.push_back(colorBoard.colors[3][1]);
    str.push_back(colorBoard.colors[4][2]);
    
    for (int i = 0; i < 21; i++) {
        if (str == colorArray[i]) {
            result.elements[i / 3] = (0) * 3 + (i % 3);
        }
    }
    str.clear();
    str.push_back(colorBoard.colors[0][1]);
    str.push_back(colorBoard.colors[4][3]);
    str.push_back(colorBoard.colors[1][0]);
    
    for (int i = 0; i < 21; i++) {
        if (str == colorArray[i]) {
            result.elements[i / 3] = (1) * 3 + (i % 3);
        }
    }
    
    str.clear();
    str.push_back(colorBoard.colors[0][2]);
    str.push_back(colorBoard.colors[5][0]);
    str.push_back(colorBoard.colors[3][3]);
    
    for (int i = 0; i < 21; i++) {
        if (str == colorArray[i]) {
            result.elements[i / 3] = (2) * 3 + (i % 3);
        }
    }
    
    str.clear();
    str.push_back(colorBoard.colors[0][3]);
    str.push_back(colorBoard.colors[1][2]);
    str.push_back(colorBoard.colors[5][1]);
    
    for (int i = 0; i < 21; i++) {
        if (str == colorArray[i]) {
            result.elements[i / 3] = (3) * 3 + (i % 3);
        }
    }
    
    str.clear();
    str.push_back(colorBoard.colors[2][0]);
    str.push_back(colorBoard.colors[4][0]);
    str.push_back(colorBoard.colors[3][0]);
    
    for (int i = 0; i < 21; i++) {
        if (str == colorArray[i]) {
            result.elements[i / 3] = (4) * 3 + (i % 3);
        }
    }
    
    str.clear();
    str.push_back(colorBoard.colors[2][1]);
    str.push_back(colorBoard.colors[1][1]);
    str.push_back(colorBoard.colors[4][1]);
    
    for (int i = 0; i < 21; i++) {
        if (str == colorArray[i]) {
            result.elements[i / 3] = (5) * 3 + (i % 3);
        }
    }
    
    str.clear();
    str.push_back(colorBoard.colors[2][3]);
    str.push_back(colorBoard.colors[5][3]);
    str.push_back(colorBoard.colors[1][3]);
    
    for (int i = 0; i < 21; i++) {
        if (str == colorArray[i]) {
            result.elements[i / 3] = (6) * 3 + (i % 3);
        }
    }
    return result;
}

void printBoard(const Board& board)
{
    for (int r = 0; r < 7; ++r) {
        printf("%3d", board.elements[r]);
    }
    printf("\n");
}

void readBoard(ColorBoard& colorBoard)
{
    for (int r = 0; r < 6; ++r) {
        for(int cl = 0; cl < 4; ++cl){
            scanf("%s", &colorBoard.colors[r][cl]);
            if(colorBoard.colors[r][cl]=='r'){
                colorBoard.colors[r][cl]='o';
            } else if(colorBoard.colors[r][cl]=='o'){
                colorBoard.colors[r][cl]='r';
            }
        }
    }
}

Board front(const Board& board)
{
    Board result = board;
    int arr[21] = {3, 4, 5, 9, 10, 11, 0, 1, 2, 6, 7, 8, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    for (int i = 0; i < 7; i++) {
        result.elements[i] = arr[result.elements[i]];
    }
    return result;
}

Board right(const Board& board)
{
    Board result = board;
    int arr[21] = {0, 1, 2, 17, 15, 16, 6, 7, 8, 4, 5, 3, 12, 13, 14, 19, 20, 18, 11, 9, 10};
    for (int i = 0; i < 7; i++) {
        result.elements[i] = arr[result.elements[i]];
    }
    return result;
}

Board up(const Board& board)
{
    Board result = board;
    int arr[21] = {14, 12, 13, 1, 2, 0, 6, 7, 8, 9, 10, 11, 16, 17, 15, 5, 3, 4, 18, 19, 20};
    for (int i = 0; i < 7; i++) {
        result.elements[i] = arr[result.elements[i]];
    }
    return result;
}

enum Move { R=1, U=2, F=3, R2=4, U2=5, F2=6, R1=7, U1=8, F1=9};

/*
 * Return a shortest path from src to dest.
 */

int order(const Board& board){
    int value = 0;
    int k = 6;
    for (int r = 0; r < 7; ++r) {
        int v = board.elements[r];
        value += v * pow(21, k);
        k -= 1;
    }
    return value;
}

Board decode(int order){
    Board node;
    int temp = order;
    
    for (int r = 6; r >=0; r--) {
        node.elements[r] = temp % 21;
        temp = temp / 21;
    }
    return node;
}

#define maximum (1800000000) 
std::vector<int> solve(const Board& src, const Board& dest)
{ 
    queue <int> q;
    int visited[maximum];
    int parent[maximum];
    int initial = order(src);
    int final = order(dest);
    q.push(order(src));
    visited[order(src)] = U;
    int temp = 0;
    while (!q.empty()) {
        int child = q.front();
        q.pop();
        Board u = decode(child);
        if (child == final) {
            /* return the moves to get to u from src. */
            std::vector<int> moves;
            while (child != initial) {
                moves.push_back(visited[child]);
                child = parent[child];
            }
            std::reverse(moves.begin(), moves.end());
            std::vector<int> result;
            int prev = 0;
            for (auto cur : moves) {
                auto temp = cur;
                if (cur == prev) {
                    int flag = result.back();
                    result.pop_back();
                    if (flag == cur) {
                        temp += 3;
                    } else {
                        temp += 6;
                    }
                }
                prev = cur;
                result.push_back(temp);
            }
            return result;
        }

        Board a = front(u);
        Board b = right(u);
        Board c = up(u);

        int aOrder = order(a);
        int bOrder = order(b);
        int cOrder = order(c);

        if (!visited[aOrder]) {
            visited[aOrder] = F;
            parent[aOrder] = child;
            q.push(aOrder);
        }
        if (!visited[bOrder]) {
            visited[bOrder] = R;
            parent[bOrder] = child;
            q.push(bOrder);
        }
        if (!visited[cOrder]) {
            visited[cOrder] = U;
            parent[cOrder] = child;
            q.push(cOrder);
        }
        temp += 1;
    }
    
    return std::vector<int>();
}

void printMoves(const std::vector<int>& moves)
{
    for (auto m: moves) {
        switch (m) {
        case U: printf("U "); break;
        case F: printf("F "); break;
        case R: printf("R "); break;
        case U1: printf("U' "); break;
        case F1: printf("F' "); break;
        case R1: printf("R' "); break;
        case U2: printf("U2 "); break;
        case F2: printf("F2 "); break;
        case R2: printf("R2 "); break;
        }
    }
    printf("\n");
}

int main()
{   
    Board destination;
    ColorBoard sourceBoard;

    readBoard(sourceBoard);
    Board source = translate(sourceBoard);

    for (int i = 0; i < 7; i++) {
        destination.elements[i] = i * 3;
    }

    printBoard(source);
    printBoard(destination);

    auto moves = solve(source, destination);
    printMoves(moves);

    return 0;
}

