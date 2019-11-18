#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
#include "Funcoes.h"
#include "Struct.h"
#include <string.h>

Objeto* title, * jogar, * sair, * linha;
ALLEGRO_BITMAP* hist1, * hist2, * hist3, * hist4;
ALLEGRO_BITMAP* Background;


int JogarMenu(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* prog) {

	Background = al_load_bitmap("Imgs/fundo.png");
	hist1 = al_load_bitmap("Imgs/menu/hist1.png");
	hist2 = al_load_bitmap("Imgs/menu/hist2.png");
	hist3 = al_load_bitmap("Imgs/menu/hist3.png");
	hist4 = al_load_bitmap("Imgs/menu/hist4.png");

	title = (Objeto*)malloc(sizeof(Objeto));
	title->altura = 200;
	title->largura = 600;
	title->x = (LARGURA_TELA / 2) - (title->largura / 2);
	title->y = 50;
	title->bitmap = al_load_bitmap("Imgs/menu/title.png");

	jogar = (Objeto*)malloc(sizeof(Objeto));
	jogar->altura = 150;
	jogar->largura = 300;
	jogar->x = (LARGURA_TELA / 2) - (jogar->largura / 2);
	jogar->y = 300;
	jogar->bitmap = al_load_bitmap("Imgs/menu/jogar.png");

	sair = (Objeto*)malloc(sizeof(Objeto));
	sair->altura = 150;
	sair->largura = 300;
	sair->x = (LARGURA_TELA / 2) - (sair->largura / 2);
	sair->y = jogar->y + 170;
	sair->bitmap = al_load_bitmap("Imgs/menu/sair.png");

	linha = (Objeto*)malloc(sizeof(Objeto));
	linha->altura = 150;
	linha->largura = 300;
	linha->x = (LARGURA_TELA / 2) - (linha->largura / 2);
	linha->y = jogar->y + 170;
	linha->bitmap = al_load_bitmap("Imgs/menu/linha.png");

	int gameOver = 0;
	int Dentro = 0;
	int Hist = 0;
	while (!gameOver)
	{
		while (!al_is_event_queue_empty(fila_eventos))
		{
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);

			ALLEGRO_MOUSE_STATE state;
			al_get_mouse_state(&state);

			if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				gameOver = 1;
				prog->Gameover = 1;
			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				if (Hist > 0) {
					Hist++;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, jogar) && Hist == 0)
				{
					Hist++;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, sair) && Hist == 0) {
					gameOver = 1;
					prog->Gameover = 1;
				}
			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
				if (IsInside(evento.mouse.x, evento.mouse.y, jogar))
				{
					Dentro = 1;
					linha->y = jogar->y;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, sair)) {
					Dentro = 1;
					linha->y = sair->y;
				}
				else
				{
					Dentro = 0;
				}
			}

			if (Hist > 4) {
				prog->proximaSala = 6;
				al_play_sample(prog->cenario->somSeta, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				gameOver = 1;
			}
		}		

			   		 
		al_draw_bitmap(Background, 0, 0, 0);
		
		if (Hist <= 0) {
			al_draw_bitmap(title->bitmap, title->x, title->y, 0);
			al_draw_bitmap(jogar->bitmap, jogar->x, jogar->y, 0);
			al_draw_bitmap(sair->bitmap, sair->x, sair->y, 0);
			if (Dentro)
				al_draw_bitmap(linha->bitmap, linha->x, linha->y, 0);
		}		
		if (Hist == 1)
			al_draw_bitmap(hist1, 0, 0, 0);
		if (Hist == 2)
			al_draw_bitmap(hist2, 0, 0, 0);
		if (Hist == 3)
			al_draw_bitmap(hist3, 0, 0, 0);
		if (Hist == 4)
			al_draw_bitmap(hist4, 0, 0, 0);


		al_flip_display();
	}

	al_destroy_bitmap(Background);
	al_destroy_bitmap(jogar->bitmap);
	al_destroy_bitmap(sair->bitmap);
	al_destroy_bitmap(linha->bitmap);
	al_destroy_bitmap(title->bitmap);


	return 0;
}