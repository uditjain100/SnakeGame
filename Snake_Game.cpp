#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
using namespace std ;

const int width = 20 , height = 20 ;
int snake_pos_x , snake_pos_y ;
int fruit_pos_x , fruit_pos_y ;
int tail_arr_x[100] , tail_arr_y[100] ;
int count_tail = 0 ;
int game_over = 0 , flag = 0 ;
int score = 0;
enum eDirection {STOP = 0, LEFT , RIGHT , UP , DOWN};
eDirection dir ;

void setup(){

    game_over = 0 ;
    dir = STOP ;

    snake_pos_x = width / 2 ;
    snake_pos_y = height / 2 ;

    fruit_pos_x = rand() % (height - 5);
    fruit_pos_y = rand() % (width - 5);

    score = 0 ;

    if(fruit_pos_x == 0){
        while(fruit_pos_x != 0){
            fruit_pos_x = rand() % (height - 5);
        }
    }

    if(fruit_pos_y == 0){
        while(fruit_pos_y != 0){
            fruit_pos_y = rand() % (width - 5);
        }
    }
}

void draw() {

    system("cls") ;

    for(int i = 0 ; i < height ; i++){
        for(int j = 0 ; j < width ; j++){
            if(i == 0 || i == height - 1 || j == 0 ||  j == width - 1){
                cout << "*" ;
            }else if(j == snake_pos_x && i == snake_pos_y){
                cout << "@" ;
            }else if(i == fruit_pos_x && j == fruit_pos_y){
                cout << "F" ;
            }else{
                int var = 0 ;
                for(int k = 0 ; k < count_tail ; k++){
                    if(j == tail_arr_x[k] && i == tail_arr_y[k]){
                        cout << "o" ;
                        var = 1 ;
                    }
                }
                if(var == 0){
                    cout << " " ;
                }
            }
        }
        cout << endl ;
    }

    cout << "SCORE : " << score << endl ;

}

void input(){

    if(_kbhit()){
        switch(_getch()){
        case 'a':
            dir = LEFT ;
            break ;
        case 'd':
            dir = RIGHT ;
            break ;
        case 'w':
            dir = UP ;
            break ;
        case 's':
            dir = DOWN ;
            break ;
        case 'x':
            game_over = 1 ;
            break ;
        }
    }
}

void Logic(){

    int prev_pos_x = tail_arr_x[0] ;
    int prev_pos_y = tail_arr_y[0] ;

    int prev_to_prev_pos_x , prev_to_prev_pos_y ;

    tail_arr_x[0] = snake_pos_x ;
    tail_arr_y[0] = snake_pos_y ;

    for(int i = 1 ; i < count_tail ; i++){

        prev_to_prev_pos_x = tail_arr_x[i] ;
        prev_to_prev_pos_y = tail_arr_y[i] ;

        tail_arr_x[i] = prev_pos_x ;
        tail_arr_y[i] = prev_pos_y ;

        prev_pos_x = prev_to_prev_pos_x ;
        prev_pos_y = prev_to_prev_pos_y ;

    }

    switch(dir){

        case LEFT:
            snake_pos_x--;
            break ;
        case RIGHT:
            snake_pos_x++;
            break ;
        case UP:
            snake_pos_y--;
            break ;
        case DOWN:
            snake_pos_y++;
            break ;
        default:
            break ;

    }

    /*if(snake_pos_x < 0 || snake_pos_x > width || snake_pos_y < 0 || snake_pos_y > height){
        game_over = 1 ;
    }*/

    if(snake_pos_x >= width){
        snake_pos_x = 0 ;
    }else if(snake_pos_x < 0){
        snake_pos_x = width - 1 ;
    }


    if(snake_pos_y >= width){
        snake_pos_y = 0 ;
    }else if(snake_pos_y < 0){
        snake_pos_y = height - 1 ;
    }


    for(int i = 0 ; i < count_tail ; i++){
        if(tail_arr_x[i] == snake_pos_y && tail_arr_y[i] == snake_pos_x){
            game_over = 1 ;
        }
    }

    if(snake_pos_x == fruit_pos_y && snake_pos_y == fruit_pos_x){

        score += 10 ;

        fruit_pos_x = rand() % (height - 5);
        fruit_pos_y = rand() % (width - 5);

        if(fruit_pos_x == 0){
            while(fruit_pos_x != 0){
                fruit_pos_x = rand() % height;
            }
        }

        if(fruit_pos_y == 0){
            while(fruit_pos_y != 0){
                fruit_pos_y = rand() % width;
            }
        }
        count_tail++ ;
    }

}

int main(){

    setup() ;
    while(game_over == 0){

        draw() ;
        input() ;
        Logic() ;
        Sleep(10);

    }

    return 0 ;


}
