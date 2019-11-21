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

ALLEGRO_BITMAP* fala1, * fala2, * creditos, *corredor;
ALLEGRO_BITMAP* Background;


int JogarFim(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* prog) {

	Background = al_load_bitmap("Imgs/fundo.png");
	fala1 = al_load_bitmap("Imgs/Fim/fala1.png");
	fala2 = al_load_bitmap("Imgs/Fim/fala2.png");
	creditos = al_load_bitmap("Imgs/Fim/Creditos.png");
	corredor = al_load_bitmap("Imgs/Fim/corredor.png");	

	int gameOver = 0;
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
				Hist++;
			}			
		}


		al_draw_bitmap(Background, 0, 0, 0);

		if (Hist == 0)
			al_draw_bitmap(corredor, 0, 0, 0);
		if (Hist == 1)
			al_draw_bitmap(fala1, 0, 0, 0);
		if (Hist == 2)
			al_draw_bitmap(fala2, 0, 0, 0);
		if (Hist >= 3)
			al_draw_bitmap(creditos, 0, 0, 0);


		al_flip_display();
	}

	al_destroy_bitmap(Background);
	al_destroy_bitmap(corredor);
	al_destroy_bitmap(fala2);
	al_destroy_bitmap(fala1);
	al_destroy_bitmap(creditos);


	return 0;
}