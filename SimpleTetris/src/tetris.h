#ifndef TETRIS_H
#define TETRIS_H
#define TET_TICKS_START 30


typedef struct TetBlock{
    int b;
}TetBlock;

typedef struct TetFigure{
    int x;
    int y;
    int size;
    TetBlock* blocks;
}TetFigure;

typedef struct TetFiguresT{
    int count;
    int size;
    TetBlock* blocks;
}TetFiguresT;

typedef struct TetField{
    int width;
    int height;
    TetBlock* blocks;
}TetField;

enum{
    TET_GAMEOVER = 0,
    TET_PLAYING
};

enum {
    TET_PLAYER_NOP = 0,
    TET_PLAYER_UP,
    TET_PLAYER_DOWN,
    TET_PLAYER_RIGHT,
    TET_PLAYER_LEFT
};

typedef struct TetPlayer{
    int action;
}TetPlayer;

typedef struct TetGame{
    TetField* field;
    TetFigure* figure;
    TetFiguresT* figurest;
    TetPlayer* player;
    int ticks;
    int ticks_left;
    int playing;
    int score;
} TetGame;

TetFiguresT* createFiguresT(int count, int figures_size, TetBlock* figure_template);
void freeTetFiguresT(TetFiguresT* tetft);
TetField* createField(int width, int height);
void freeTetFiled(TetField* tetf);
TetGame* createTetGame(int field_width, int field_height, int figures_size, int count, TetBlock* figures_template);
void dropNewFigure(TetGame* tetg);
void freeTetGame(TetGame* tetg);
void moveFidureDown(TetGame* tetg);
void moveFidureUP(TetGame* tetg);
void moveFidureRight(TetGame* tetg);
void moveFidureLeft(TetGame* tetg);
int collisionTet(TetGame* tetg);
void plantFigure(TetGame* tetg);
int lineFieldTest(int i,TetField* tfl);
void dropLine(int i,TetField* tfl);
int eraseLineTet(TetGame* tetg);
TetFigure* createTetFigure(TetGame* tetg);
void freeTetFigure(TetFigure* tf);
TetFigure* rotTetFigure(TetGame* tetg);
void calculateTet(TetGame* tetg);

#endif