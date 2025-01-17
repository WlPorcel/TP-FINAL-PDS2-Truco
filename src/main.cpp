#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <iostream>

#include "../include/match.hpp"
#include "../include/pieces/rook.hpp"
#include "../include/pieces/piece.hpp"
#include "../include/board.hpp"


void array_to_pixel(int* spot, int pixel[0]);
void pixel_to_array(int* pixel, int* spot);
void drawn_board(Match &mat);

const int SC_W = 600;
const int SC_H = 700;
const float FPS = 10;

Rook *r = new Rook("Black");


using namespace std;
int main(){
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    
	//inicia o allegro:
	if(!al_init()){
		fprintf(stderr, "failed");
		return -1;
	}
	
	//cria uma tela:
	display = al_create_display(SC_W, SC_H);
    al_set_window_title(display, "Xess");
	
    //cria um temporizador que incrementa uma unidade a cada 1.0/FPS segundos:
    timer = al_create_timer(1.0/FPS);
    
    //instala teclado e mouse:
    al_install_mouse();
    al_install_keyboard();

    //inicializa imagens:
    al_init_image_addon();
    ALLEGRO_BITMAP *fundo = al_load_bitmap("images/Chess_Menu.png");
    ALLEGRO_BITMAP *image = al_load_bitmap("images/B_Queen.png");

	//cria fila de eventos:
	event_queue = al_create_event_queue();

	//registra na fila eventos de tela:
	al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
	
	int run = 1;
    int meme = 0;
    int movtype = 0;

    //inicia o temporizador
    al_start_timer(timer);
    while(run){
        
        Match *match = new Match();
        while(run){
            ALLEGRO_EVENT ev;
            //espera por um evento e o armazena em ev
            al_wait_for_event(event_queue, &ev);
            
            if(match->getwinner() != ""){
                    break;
            }

            match->refresh_imagespices();

            //evento de passo no relógio
            if(ev.type == ALLEGRO_EVENT_TIMER){
                if(meme == 1){
                    ALLEGRO_BITMAP *im = al_load_bitmap("images/Poootter.png");
                    al_draw_bitmap(im, 0, 0, 0);
                    al_destroy_bitmap(im);
                }else{
                    al_draw_bitmap(fundo, 0, 0, 0);
                    ALLEGRO_BITMAP *mov;
                    switch (movtype){
                    case 1:
                        mov = al_load_bitmap("images/Invalid Movement.png");
                        al_draw_bitmap(mov, 0, 0, 0);
                        al_destroy_bitmap(mov);
                        break;
                    case 2:
                        mov = al_load_bitmap("images/Movement Canceled.png");
                        al_draw_bitmap(mov, 0, 0, 0);
                        al_destroy_bitmap(mov);
                        break;
                    case 3:
                        mov = al_load_bitmap("images/Blocked Piece.png");
                        al_draw_bitmap(mov, 0, 0, 0);
                        al_destroy_bitmap(mov);
                        break;
                    case 4:
                        mov = al_load_bitmap("images/Not this piece's turn.png");
                        al_draw_bitmap(mov, 0, 0, 0);
                        al_destroy_bitmap(mov);
                        break;
                    case 5:
                        mov = al_load_bitmap("images/Empty Spot.png");
                        al_draw_bitmap(mov, 0, 0, 0);
                        al_destroy_bitmap(mov);
                        break;
                    default:
                    break;
                    }
                    
                    if(match->get_turn() == "White"){
                        ALLEGRO_BITMAP *image = al_load_bitmap("images/White's_Turn.png");
                        al_draw_bitmap(image, 0, 0, 0);
                        al_destroy_bitmap(image);
                    }
                    if(match->get_turn() == "Black"){
                        ALLEGRO_BITMAP *image = al_load_bitmap("images/Black's_Turn.png");
                        al_draw_bitmap(image, 0, 0, 0);
                        al_destroy_bitmap(image);
                    }
                
                    drawn_board(*match);
                }    
                
                al_flip_display();
                
            }
            
            else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                run = 0;
                break;
            }
            //detecta a posição do mouse:::::IMPORTANTISSIMO:::::::
            else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                if(movtype != 0){
                    movtype = 0;
                }
                int click[2] = {ev.mouse.x, ev.mouse.y};
                int sp[2];
                    try{
                        pixel_to_array(click, sp);
                    }
                    catch(ButtonSpotExeption &e){//quando clica no botao
                        cout<<e.what();
                        match->p_gaveup();
                        break;
                    }catch(OutOfTableExeption &e){// quando clica fora do tabuleiro
                        cout<< e.what()<<"\n";
                        movtype = 1;
                        continue;
                    }
                
                    try{
                        match->game(sp);
                    
                    }catch(VoidSpotExeption &e){// Clicou no vazio
                        movtype = 5;
                        cout<< e.what()<<"\n";
                        continue;
                    }catch(VoidMovimentExeption &e){//quando a matriz de movimentos validos é nula
                        cout<< e.what()<<"\n";
                        movtype = 3;
                        continue;
                    }catch(MovNotValidExeption &e){// Clicou em um lugar que nao pode mecher
                        movtype = 2;
                        cout<< e.what()<<"\n";
                        continue;
                    }catch(NotTurnExeption &e){// clicou na peça da vez do oponente
                        movtype = 4;
                        cout<< e.what()<<"\n";
                        continue;
                    }           

            }
            //detecta codigo da tecla pressionado
            else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
                switch (ev.keyboard.keycode){
                    case ALLEGRO_KEY_ESCAPE:
                        run = 0;
                        break;
                    case ALLEGRO_KEY_P:
                        if(meme == 0){
                            meme = 1;
                        }else{
                            meme = 0;
                        }
                        break;
                }
                
            }


        }
    
       
        
        if(run == 0){
            break;
        }
        if(match->getwinner() == "White"){
            ALLEGRO_BITMAP *image = al_load_bitmap("images/White's_Victory.png");
            al_draw_bitmap(image, 0, 0, 0);
            al_destroy_bitmap(image);
            al_flip_display();
        }
        if(match->getwinner() == "Black"){
            ALLEGRO_BITMAP *image = al_load_bitmap("images/Black's_Victory.png");
            al_draw_bitmap(image, 0, 0, 0);
            al_destroy_bitmap(image);
            al_flip_display();
        }

        while(1){
     
            ALLEGRO_EVENT ev;
            //espera por um evento e o armazena em ev
            al_wait_for_event(event_queue, &ev);
            if(ev.type == ALLEGRO_EVENT_TIMER){
                
            }
           
            //detecta a posição do mouse
            if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                break;

            }else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                run = 0;
                break;
            }
        }
        
   

        // delete match;
	}
    al_destroy_event_queue(event_queue);
}

//Funções:

void drawn_board(Match &mat){
    mat.refresh_imagespices();
     for(int i=0 ; i<8; i++){
       for(int j=0 ; j<8; j++){
            //Se houver uma string de endereço na matriz ele printa a imagem
            if(mat.image_pices[i][j] != ""){
                const char *c = mat.image_pices[i][j].c_str();
                ALLEGRO_BITMAP *image = al_load_bitmap(c);
                
                //define a posição das peças no tabuleiro:
                int place[2];
                int sp[2] = {i, j};
                array_to_pixel(sp, place);
                
                //desenha imagem no local correto
                al_draw_bitmap(image, place[0], place[1], 0);
                al_destroy_bitmap(image);
            }

            if(mat.image_dots[i][j] != ""){
                const char *c = mat.image_dots[i][j].c_str();
                
                ALLEGRO_BITMAP *image = al_load_bitmap(c);
                
                //define a posição das peças no tabuleiro:
                int place[2];
                int sp[2] = {i, j};
                array_to_pixel(sp, place);
                
                //desenha imagem no local correto
                al_draw_bitmap(image, place[0], place[1], 0);
                al_destroy_bitmap(image);
            }
        
        
        } 
    }
}

void array_to_pixel(int* spot, int pixel[0]){ 
    pixel[0] = 26 + (*(spot + 1) * 69); 
    pixel[1] = 127 + (*(spot) * 69);
      
}

void pixel_to_array(int* pixel, int* spot){
    
    if(pixel[0] >= 27 && pixel[0] <= 575 &&
       pixel[1] >= 127 && pixel[1]<= 675 ){
       
            //eixo x
            pixel[0] -= 26; //tira 26 pq as casas começam a partir do pixel 26
            *(spot + 1) = (pixel[0]/69); //a cada 68 pixels, pula uma casa (pega só parte inteira da divisão)
            //eixo y
            pixel[1] -= 127; //tira 26 pq as casas começam a partir do pixel 26
            *spot = (pixel[1]/69); //a cada 68 pixels, pula uma casa (pega só parte inteira da divisão)
            
    }else{
        
        if(pixel[0] >= 420 && pixel[0] <= 530 &&
        pixel[1]>= 40 &&  pixel[1]<= 85 ){
            throw ButtonSpotExeption();
        }else{
            throw OutOfTableExeption();
        }

    }
    //se x27 y127
    //sd x575 y127
    //id x575 y677
    //ie x28 y675
    
}

