
#include "include/pieces/pawn.hpp"


using namespace std;

Pawn::Pawn(string cor){
    Piece(cor);
    _name= "Pawn";
     //  _image = "./" 
}

//No caso do pe�o define os movimentos possiveis como duas casas a frente caso seja seu primeiro movimento ou uma casa a frente caso n�o seja
void Pawn::def_possible_movements(int* spot){

    // Rezeta a Matriz de movimentos possiveis
    for (int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            _possibles_movements[i][j]=0;
        }
    };

    if(this->get_color() == "Black" && _first_time == true){
        _possibles_movements[*spot][*(spot+1) - 1] = 1;
        _possibles_movements[*spot][*(spot+1) - 2] = 1;
        if(*spot <7){
            _possibles_movements[*spot+1][*(spot+1) - 1] = 1;
        }
        if(*spot >0){
            _possibles_movements[*spot -1][*(spot+1) - 1] = 1;
        }

    }
    if(this->get_color() == "Black" && _first_time == false){
        _possibles_movements[*spot][*(spot+1) - 1] = 1;
         if(*spot <7){
            _possibles_movements[*spot+1][*(spot+1) - 1] = 1;
        }
        if(*spot >0){
            _possibles_movements[*spot -1][*(spot+1) - 1] = 1;
        }

    }
    if(this->get_color() == "white" && _first_time == true){
        _possibles_movements[*spot][*(spot+1) + 1] = 1;
        _possibles_movements[*spot][*(spot+1) + 2] = 1;
         if(*spot <7){
            _possibles_movements[*spot+1][*(spot+1) + 1] = 1;
        }
        if(*spot >0){
            _possibles_movements[*spot -1][*(spot+1) + 1] = 1;
        }
    }
    if(this->get_color() == "White" && _first_time == false){
        _possibles_movements[*spot][*(spot+1) + 1] = 1;
        if(*spot <7){
            _possibles_movements[*spot+1][*(spot+1) + 1] = 1;
        }
        if(*spot >0){
            _possibles_movements[*spot -1][*(spot+1) + 1] = 1;
        }
    }

    //Zera a casa da posição atual das peças:
    _possibles_movements[*spot][*(spot+1)]= 0; 




}

