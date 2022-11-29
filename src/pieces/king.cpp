//#define NDEBUG
#include "../../include/pieces/king.hpp"
// #include <c////assert>

using namespace std;

King::King(string color):Piece(color){
    _name= "King";
    
    if(color == "White"){
        _image = "src/images/W_King.png";
    }else if(color == "Black"){
        _image = "src/images/B_King.png";
    };
}

void King::def_possible_movements(int* spot){

    // Rezeta a Matriz de movimentos possiveis
    for (int i=0; i<8; i++){
        ////assert(0 <= i && i >= 8);
        for(int j=0; j<8; j++){
            ////assert(0 <= j && j >= 8);
            _possibles_movements[i][j]=0;
        }
    };

// Primeira implementação de try/catch e ////assert juntos

    for (int i=(spot[0])-1; i< (spot[0])+1; i++){
        for(int j= spot[1]-1 ; j< spot[1]+1; j++){
            if(i>=0 && i<8 &&
               j>= 0 && j<8){
                    _possibles_movements[i][j]=1;
               }        
        }
    };

    //Zera a casa da posição atual das peças:
    _possibles_movements[spot[0]][spot[1]]= 0;

}
/*
    if(this->get_color() == "white"){
        //Possibilidades Cima;
        for(int ed = spot[0], cb = spot[1], count = 0; ed > -1 && count < 2; ed--, count++){
        _possibles_movements[ed][cb] = 1;
        }

        //Possibilidades Baixo;
        for(int ed = spot[0], cb = spot[1], count  = 0; ed < 8 && count < 2; ed++, count++){
        _possibles_movements[ed][cb] = 1;
        }

        //Possibilidades Direita;
        for(int ed = spot[0], cb = spot[1], count = 0; cb < 8 && count < 2;cb++, count++){
        _possibles_movements[ed][cb] = 1;
        }

        //Possibilidades Esquerda;
        for(int ed = spot[0], cb = spot[1], count = 0; cb > -1 && count < 2; cb--, count++){
        _possibles_movements[ed][cb] = 1;
        }

         //Possibilidades Diagonal pra Direita e pra Baixo;
        for(int ed = spot[0], cb = spot[1], count = 0; ed < 8 && cb < 8 && count < 2; ed++, cb++, count++){
        _possibles_movements[ed][cb] = 1;
        }

        //Possibilidades Diagonal pra Direita e pra Cima;
        for(int ed = spot[0], cb = spot[1], count = 0; ed > -1 && cb < 8 && count < 2; ed--, cb++, count++){
        _possibles_movements[ed][cb] = 1;
        }
        //Possibilidades Diagonal pra Esquerda e pra Baixo;
        for(int ed = spot[0], cb = spot[1], count = 0; ed < 8 && cb > -1 && count < 2; ed++, cb--, count++){
        _possibles_movements[ed][cb] = 1;
        }
        //Possibilidades Diagonal pra Esquerda e pra Cima;
        for(int ed = spot[0], cb = spot[1], count = 0; ed > -1 && cb > -1 && count < 2; ed--, cb--, count++){
        _possibles_movements[ed][cb] = 1;
        }
    }

    if(this->get_color() == "black"){
        //Possibilidades Cima;
        for(int ed = spot[0], cb = spot[1], count = 0; ed > -1 && count < 2; ed--, count++){
        _possibles_movements[ed][cb] = 1;
        }

        //Possibilidades Baixo;
        for(int ed = spot[0], cb = spot[1], count  = 0; ed < 8 && count < 2; ed++, count++){
        _possibles_movements[ed][cb] = 1;
        }

        //Possibilidades Direita;
        for(int ed = spot[0], cb = spot[1], count = 0; cb < 8 && count < 2;cb++, count++){
        _possibles_movements[ed][cb] = 1;
        }

        //Possibilidades Esquerda;
        for(int ed = spot[0], cb = spot[1], count = 0; cb > -1 && count < 2; cb--, count++){
        _possibles_movements[ed][cb] = 1;
        }

         //Possibilidades Diagonal pra Direita e pra Baixo;
        for(int ed = spot[0], cb = spot[1], count = 0; ed < 8 && cb < 8 && count < 2; ed++, cb++, count++){
        _possibles_movements[ed][cb] = 1;
        }

        //Possibilidades Diagonal pra Direita e pra Cima;
        for(int ed = spot[0], cb = spot[1], count = 0; ed > -1 && cb < 8 && count < 2; ed--, cb++, count++){
        _possibles_movements[ed][cb] = 1;
        }
        //Possibilidades Diagonal pra Esquerda e pra Baixo;
        for(int ed = spot[0], cb = spot[1], count = 0; ed < 8 && cb > -1 && count < 2; ed++, cb--, count++){
        _possibles_movements[ed][cb] = 1;
        }
        //Possibilidades Diagonal pra Esquerda e pra Cima;
        for(int ed = spot[0], cb = spot[1], count = 0; ed > -1 && cb > -1 && count < 2; ed--, cb--, count++){
        _possibles_movements[ed][cb] = 1;
        } 
    }
 */   
   



