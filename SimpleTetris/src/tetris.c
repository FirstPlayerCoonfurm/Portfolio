#include "tetris.h"
#include <stdlib.h>

#ifndef TETRIS_C
#define TETRIS_C

TetFiguresT* createFiguresT(int count, int figures_size, TetBlock* figure_template){
    TetFiguresT* tetf = (TetFiguresT*)malloc(sizeof(TetFiguresT));
    tetf->count = count;
    tetf->size = figures_size;
    tetf->blocks = figure_template;
    return tetf;
};

void freeTetFiguresT(TetFiguresT* tetft){
    if(tetft)
        free(tetft);
};

TetField* createField(int width, int height){
    TetField* tetf = (TetField*)malloc(sizeof(TetField));
    tetf->width = width;
    tetf->height = height;
    tetf->blocks = (TetBlock*)malloc(sizeof(TetBlock)*width*height);
    for (int i = 0; i < width; i++)
        tetf->blocks[i].b = 0;
    return tetf;
};

void freeTetFiled(TetField* tetf){
    if(tetf){
        if(tetf->blocks)
            free(tetf->blocks);
        free(tetf);
    }
};

TetGame* createTetGame(int field_width, int field_height, int figures_size,
int count, TetBlock* figure_template){
    TetGame* tetg = (TetGame*)malloc(sizeof(TetGame));
    tetg->field = createField(field_width, field_height);
    tetg->figurest = createFiguresT(count, figures_size, figure_template);

    tetg->ticks = TET_TICKS_START;
    tetg->ticks_left = TET_TICKS_START;
    tetg->score = 0;
    tetg->playing = TET_PLAYING;

    return tetg;
};

void freeTetGame(TetGame* tetg){
    if(tetg){
        freeTetFiled(tetg->field);
        freeTetFiguresT(tetg->figurest);
        free(tetg);
    };
};

void moveFidureDown(TetGame* tetg){
    tetg->figure->y++;
};

void moveFidureUP(TetGame* tetg){
    tetg->figure->y--;
};

void moveFidureRight(TetGame* tetg){
    tetg->figure->x++;
};

void moveFidureLeft(TetGame* tetg){
    tetg->figure->x--;
};

int collisionTet(TetGame* tetg){
    TetFigure* t = tetg->figure;
    TetField* tf = tetg->field;
    for(int i=0; i<t->size; i++){
        for(int j = 0; j<t->size; j++){
            if(t->blocks[i*t->size+j].b!=0){
                int fx = t->x + j;
                int fy = t->y + i;
                if(tf->blocks[fy*tf->width+fx].b !=0)
                    return 1;
                
                if(fx<0 || fx >= tf->width || fy < 0 || fy>=tf->height)
                    return 1;

            };
        };
    };
    return 0;
};

void plantFigure(TetGame* tetg){
    TetFigure* t = tetg->figure;
    for(int i=0; i<t->size; i++){
        for(int j=0; j<t->size; j++){
            if(t->blocks[i*t->size+j].b != 0){
                int fx = t->x+j;
                int fy = t->y+i;
                tetg->field->blocks[fy*tetg->field->width+fx].b = t->blocks[i*t->size+j].b;
            };         
        };
    };
};

int lineFieldTest(int i,TetField* tfl){
    for(int j = 0; j < tfl->width; j++){
        if(tfl->blocks[i*tfl->width+j].b == 0)
            return 0;
    return 1;
    };
};

void dropLine(int i,TetField* tfl){
    if(i == 0){
        for(int j = 0; j <tfl->width; j++){
            tfl->blocks[j].b = 0;
        };
    }else {
        for(int k = i; k > 0; k--)
            for(int j=0; j<tfl->width; j++)
                tfl->blocks[k*tfl->width+j].b = tfl->blocks[(k-1)*tfl->width+j].b;
    };
};

int eraseLineTet(TetGame* tetg){
    TetField* tfl = tetg->field;
    int count = 0;
    for(int i = tfl->height-1; i>=0; i--){
        while(lineFieldTest(i, tfl)){
            dropLine(i, tfl);
            count++;
        };
    };
    return count;
};

TetFigure* createTetFigure(TetGame* tetg){
    TetFigure* t = (TetFigure*)malloc(sizeof(TetFigure));
    t->x = 0;
    t->y = 0;
    t->size = tetg->figurest->size;
    t->blocks = (TetBlock*)malloc(sizeof(TetBlock)*t->size*t->size);
    return t;
};

void freeTetFigure(TetFigure* tf){
    if(tf){
        if(tf->blocks)
            free(tf->blocks);
        free(tf);
    };
};

void dropNewFigure(TetGame* tetg){
    TetFigure* t = createTetFigure(tetg);
    t->x = tetg->field->width/2 - t->size/2;
    t->y = 0;
    int fnum = rand() % tetg->figurest->count;
    for(int i = 0; i < t->size; i++)
        for (int j = 0; j<t->size; j++){
            t->blocks[i*t->size+j].b = tetg->figurest->blocks[fnum*t->size*t->size+i*t->size+j].b;
        };
    freeTetFigure(tetg->figure);
    tetg->figure = t;
};

TetFigure* rotTetFigure(TetGame* tetg){
    TetFigure* t = createTetFigure(tetg);
    TetFigure* told = tetg->figure;
    t->x = told->x;
    t->y = told->y;
    for(int i = 0; i < t->size; i++)
        for (int j = 0; j<t->size; j++){
            t->blocks[i*t->size+j].b = told->blocks[j*t->size+t->size-1-i].b;
        };
    return t;
};

void calculateTet(TetGame* tetg){
    if(tetg->ticks_left<=0){
        tetg->ticks_left = tetg->ticks;
        moveFidureDown(tetg);
        if(collisionTet(tetg)){
            moveFidureUP(tetg);
            plantFigure(tetg);
            tetg->score += eraseLineTet(tetg);
            dropNewFigure(tetg);
            if(collisionTet(tetg)){
                tetg->playing = TET_GAMEOVER;
                return;
            };
        };
    };

    switch(tetg->player->action) {
        case TET_PLAYER_RIGHT:
            moveFidureRight(tetg);
            if(collisionTet(tetg))
                moveFidureLeft(tetg);
            break;
        
        case TET_PLAYER_LEFT:
            moveFidureLeft(tetg);
            if(collisionTet(tetg))
                moveFidureRight(tetg);
            break;
        
        case TET_PLAYER_DOWN:
            moveFidureDown(tetg);
            if(collisionTet(tetg))
                moveFidureUP(tetg);
            break;

        case TET_PLAYER_UP: {
            TetFigure* t = rotTetFigure(tetg);
            TetFigure* told = tetg->figure;
            tetg->figure = t;
            if(collisionTet(tetg)){
                tetg->figure = told;
                freeTetFigure(t);
            }
            else {
                freeTetFigure(told);
            };
        };
        break;
        case TET_PLAYER_NOP:
            default:
                break;
    };
    tetg->ticks_left--;
};

#endif