#include "Matrix_button.h"

const int row = 3;
const int colo = 3;

char matrix[row][colo] = {
    {'0', 'T', '0'},
    {'L', '=', 'R'},
    {'0', 'B', '0'},
};

const int rows[row] = {39, 38, 37};
const int colos[colo] = {36, 35, 45};

void initMatrix(){
    for(int r = 0; r < row; r++){
        pinMode(rows[r], OUTPUT);
        digitalWrite(rows[r], HIGH);
    }
    for(int c = 0; c < colo; c++){
        pinMode(colos[c], INPUT_PULLUP);
    }
}
char scanMatrix(){
    for(int r = 0; r < row; r++){
        digitalWrite(rows[r], LOW);
        for(int c = 0; c < colo; c++){
            if(digitalRead(colos[c]) == LOW){
                digitalWrite(rows[r], HIGH);
                return matrix[r][c];
            }
        }
        digitalWrite(rows[r], HIGH);
    }
    return '0';
}