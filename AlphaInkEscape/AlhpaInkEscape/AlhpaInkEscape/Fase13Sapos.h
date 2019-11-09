#include <stdio.h>
// Inclui o arquivo de cabe�alho da biblioteca Allegro 5
#include <allegro5/allegro.h>
// Inclui o cabe�alho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
// Inclui a coisa do mouse
#include <allegro5/allegro_native_dialog.h>

#include "Funcoes.h"
#include "Struct.h"

Objeto* D1, * D2, * D3, * E4, * E5, * E6;
Objeto* saidaDireita, * saidaCima;
Objeto* Reset;

int JogarFase13Sapos(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* prog) {
	
	Reset = (Objeto*)malloc(sizeof(Objeto));
	Reset->bitmap = al_load_bitmap("Imgs/Sapos/reset.png");
	Reset->x = LARGURA_TELA/2 - 50 + 100;
	Reset->y = 500;
	Reset->largura = 100;
	Reset->altura = 100;

	D1 = (Objeto*)malloc(sizeof(Objeto));
	D1->bitmap = al_load_bitmap("Imgs/Sapos/D.png");
	D1->x = 120;
	D1->y = 300;
	D1->largura = 150;
	D1->altura = 100;/*
	Direita1.objeto = D1;
	Direita1.esquerda = 0;*/

	D2 = (Objeto*)malloc(sizeof(Objeto));
	D2->bitmap = al_load_bitmap("Imgs/Sapos/D.png");
	D2->x = D1->x + D1->largura;
	D2->y = 300;
	D2->largura = 150;
	D2->altura = 100;/*
	Direita2.objeto = D2;
	Direita2.esquerda = 0;*/

	D3 = (Objeto*)malloc(sizeof(Objeto));
	D3->bitmap = al_load_bitmap("Imgs/Sapos/D.png");
	D3->x = D2->x + D2->largura;
	D3->y = 300;
	D3->largura = 150;
	D3->altura = 100;

	E4 = (Objeto*)malloc(sizeof(Objeto));
	E4->bitmap = al_load_bitmap("Imgs/Sapos/E.png");
	E4->x = D3->x + D3->largura * 2;
	E4->y = 300;
	E4->largura = 150;
	E4->altura = 100;

	E5 = (Objeto*)malloc(sizeof(Objeto));
	E5->bitmap = al_load_bitmap("Imgs/Sapos/E.png");
	E5->x = E4->x + E4->largura;
	E5->y = 300;
	E5->largura = 150;
	E5->altura = 100;

	E6 = (Objeto*)malloc(sizeof(Objeto));
	E6->bitmap = al_load_bitmap("Imgs/Sapos/E.png");
	E6->x = E5->x + E5->largura;
	E6->y = 300;
	E6->largura = 150;
	E6->altura = 100;

	ALLEGRO_BITMAP* Background = al_load_bitmap("Imgs/fundo.png");

	int gameOver = 0;
	int i;
	int casas[7] = { 1,2,3,0,4,5,6 };
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
				if (IsInside(evento.mouse.x, evento.mouse.y, Reset)) {
					for (i = 0; i < 7; i++) {
						casas[i] = i + 1;
						if (i == 3)
							casas[i] = 0;
						if (i > 3)
							casas[i] = i;
					}
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, D1)) {
					i = IndexOf(1,casas);
					if (i < 4 && casas[i + 1] == 0) {
						casas[i + 1] = 1;
						casas[i] = 0;
					}
					else if (i < 3 && casas[i + 2] == 0) {
						casas[i + 2] = 1;
						casas[i] = 0;
					}
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, D2)) {
					i = IndexOf(2, casas);
					if (i < 5 && casas[i + 1] == 0) {
						casas[i + 1] = 2;
						casas[i] = 0;
					}
					else if (i < 4 && casas[i + 2] == 0) {
						casas[i + 2] = 2;
						casas[i] = 0;
					}
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, D3)) {
					i = IndexOf(3, casas);
					if (i < 6 && casas[i + 1] == 0) {
						casas[i + 1] = 3;
						casas[i] = 0;
					}
					else if (i < 5 && casas[i + 2] == 0) {
						casas[i + 2] = 3;
						casas[i] = 0;
					}
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, E4)) {
					i = IndexOf(4, casas);
					if (i > 0 && casas[i - 1] == 0) {
						casas[i - 1] = 4;
						casas[i] = 0;
					}
					else if (i > 1 && casas[i - 2] == 0) {
						casas[i - 2] = 4;
						casas[i] = 0;
					}
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, E5)) {
					i = IndexOf(5, casas);
					if (i > 1 && casas[i - 1] == 0) {
						casas[i - 1] = 5;
						casas[i] = 0;
					}
					else if (i > 2 && casas[i - 2] == 0) {
						casas[i - 2] = 5;
						casas[i] = 0;
					}
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, E6)) {
					i = IndexOf(6, casas);
					if (i > 2 && casas[i - 1] == 0) {
						casas[i - 1] = 6;
						casas[i] = 0;
					}
					else if (i > 3 && casas[i - 2] == 0) {
						casas[i - 2] = 6;
						casas[i] = 0;
					}
				}
				for (i = 0; i < 7; i++) { printf("%d ", casas[i]); }printf("\n");
			}
		}

		D1->x = 120 + 170 * IndexOf(1, casas);
		D2->x = 120 + 170 * IndexOf(2, casas);
		D3->x = 120 + 170 * IndexOf(3, casas);
		E4->x = 120 + 170 * IndexOf(4, casas);
		E5->x = 120 + 170 * IndexOf(5, casas);
		E6->x = 120 + 170 * IndexOf(6 , casas);

		al_draw_bitmap(Background, 0, 0, 0);

		al_draw_bitmap(D1->bitmap, D1->x, D1->y, 0);
		al_draw_bitmap(D2->bitmap, D2->x, D2->y, 0);
		al_draw_bitmap(D3->bitmap, D3->x, D3->y, 0);

		al_draw_bitmap(E4->bitmap, E4->x, E4->y, 0);
		al_draw_bitmap(E5->bitmap, E5->x, E5->y, 0);
		al_draw_bitmap(E6->bitmap, E6->x, E6->y, 0);

		al_draw_bitmap(Reset->bitmap, Reset->x, Reset->y, 0);

		caregaInventario(prog);
		al_flip_display();
	}

	//Destroys	
}

int IndexOf(int x, int v[]) {
	int i;
	for (i = 0; i < 7; i++ ) {
		if (v[i] == x)
			return i;
	}
}

