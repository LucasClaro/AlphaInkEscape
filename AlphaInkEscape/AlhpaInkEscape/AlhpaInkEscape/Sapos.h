#include <stdio.h>
// Inclui o arquivo de cabe�alho da biblioteca Allegro 5
#include <allegro5/allegro.h>
// Inclui o cabe�alho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
// Inclui a coisa do mouse
#include <allegro5/allegro_native_dialog.h>

#include "Funcoes.h"
#include "Struct.h"

Objeto* D1, * D2, * D3, * E1, * E2, * E3;
Objeto* saidaDireita, * saidaCima;

int JogarFase13Sapos(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* prog) {

	D1 = (Objeto*)malloc(sizeof(Objeto));
	D1->bitmap = al_load_bitmap("Imgs/Sapos/D.png");;
	D1->x = 120;
	D1->y = 100;
	D1->largura = 150;
	D1->altura = 100;

	D2 = (Objeto*)malloc(sizeof(Objeto));
	D2->bitmap = al_load_bitmap("Imgs/Sapos/D.png");;
	D2->x = D1->x + D1->largura + 10;
	D2->y = 100;
	D2->largura = 150;
	D2->altura = 100;

	D3 = (Objeto*)malloc(sizeof(Objeto));
	D3->bitmap = al_load_bitmap("Imgs/Sapos/D.png");;
	D3->x = D2->x + D2->largura + 10;
	D3->y = 100;
	D3->largura = 150;
	D3->altura = 100;

	E1 = (Objeto*)malloc(sizeof(Objeto));
	E1->bitmap = al_load_bitmap("Imgs/Sapos/E.png");;
	E1->x = D3->x + D3->largura * 2 + 20;
	E1->y = 100;
	E1->largura = 150;
	E1->altura = 100;

	E2 = (Objeto*)malloc(sizeof(Objeto));
	E2->bitmap = al_load_bitmap("Imgs/Sapos/E.png");;
	E2->x = E1->x + E1->largura + 10;
	E2->y = 100;
	E2->largura = 150;
	E2->altura = 100;

	E3 = (Objeto*)malloc(sizeof(Objeto));
	E3->bitmap = al_load_bitmap("Imgs/Sapos/E.png");;
	E3->x = E2->x + E2->largura + 10;
	E3->y = 100;
	E3->largura = 150;
	E3->altura = 100;

	ALLEGRO_BITMAP* Background = al_load_bitmap("Imgs/fundo.png");
	Background = al_load_bitmap("Imgs/fundo.png");

	int gameOver = 0;
	while (!gameOver)
	{
		while (!al_is_event_queue_empty(fila_eventos))
		{
			//Cria um evento
			ALLEGRO_EVENT evento;
			//espero por um evento da fila, e guarda em evento
			al_wait_for_event(fila_eventos, &evento);

			//se teve eventos e foi um evento de fechar janela, encerra repeti��o			
			if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				prog->Gameover = 1;
				gameOver = 1;
			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

			}
		}

		al_draw_bitmap(Background, 0, 0, 0);

		al_draw_bitmap(D1->bitmap, D1->x, D1->y, 0);
		al_draw_bitmap(D2->bitmap, D2->x, D2->y, 0);
		al_draw_bitmap(D3->bitmap, D3->x, D3->y, 0);

		al_draw_bitmap(E1->bitmap, E1->x, E1->y, 0);
		al_draw_bitmap(E2->bitmap, E2->x, E2->y, 0);
		al_draw_bitmap(E3->bitmap, E3->x, E3->y, 0);

		caregaInventario(prog);
		al_flip_display();
	}	
}

