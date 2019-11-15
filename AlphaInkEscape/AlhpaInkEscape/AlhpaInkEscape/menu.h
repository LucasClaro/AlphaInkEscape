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


//a
int JogarMenu(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* prog) {



	ALLEGRO_BITMAP* btn = al_load_bitmap("Imgs/MapaFase7/cimaMapa.png");
	ALLEGRO_BITMAP* btnPressionado = al_load_bitmap("Imgs/MapaFase7/cimaMapaPressionado.png");


	//ALLEGRO_BITMAP* padrao = al_load_bitmap("");
	ALLEGRO_BITMAP* conta1 = al_load_bitmap("Imgs/esquerda.png");
	ALLEGRO_BITMAP* conta2 = al_load_bitmap("Imgs/direita.png");
	ALLEGRO_BITMAP* background = al_load_bitmap("Imgs/fundo.png");



	//a
	bool sair = false;
	bool drawNull = true;



	while (!sair)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(fila_eventos, &evento);

		ALLEGRO_MOUSE_STATE state;
		al_get_mouse_state(&state);

		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			sair = true;
			prog->Gameover = true;
		}




		//===========================================DESENHAR========================================================================
		al_draw_bitmap(background, 0, 0, 0);
		 if (prog->Salas[0])





			//if (!drawNull)
			//    al_draw_bitmap(conta->bitmap, conta->x, conta->y, 0);



			//abrirMapa(prog);
			caregaInventario(prog);
		al_flip_display();
	}

	al_destroy_bitmap(background);
	al_destroy_bitmap(conta1);
	al_destroy_bitmap(conta2);


	return 0;
}