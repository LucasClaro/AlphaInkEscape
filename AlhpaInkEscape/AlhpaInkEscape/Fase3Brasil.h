
#include <stdio.h>
// Inclui o arquivo de cabeçalho da biblioteca Allegro 5
#include <allegro5/allegro.h>
// Inclui o cabeçalho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
// Inclui a coisa do mouse
#include <allegro5/allegro_native_dialog.h>

#include "Funcoes.h"
#include "Struct.h"

int JogarFase3Brasil(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* prog) {

	Objeto *mapa;
	mapa = (Objeto*)malloc(sizeof(Objeto));
	mapa->bitmap = NULL;
	mapa->x = LARGURA_TELA/2 - 450;
	mapa->y = ALTURA_TELA/2 - 450;
	mapa->largura = 900;
	mapa->altura = 900;

	Objeto *notaOnça;
	notaOnça = (Objeto*)malloc(sizeof(Objeto));
	notaOnça->bitmap = NULL;
	notaOnça->x = 120;
	notaOnça->y = 100;
	notaOnça->largura = 230;
	notaOnça->altura = 200;

	Objeto* notaTatu;
	notaTatu = (Objeto*)malloc(sizeof(Objeto));
	notaTatu->bitmap = NULL;
	notaTatu->x = 120;
	notaTatu->y = ALTURA_TELA - 220;
	notaTatu->largura = 230;
	notaTatu->altura = 200;

	Objeto* notaJacare;
	notaJacare = (Objeto*)malloc(sizeof(Objeto));
	notaJacare->bitmap = NULL;
	notaJacare->x = LARGURA_TELA - 240;
	notaJacare->y = 100;
	notaJacare->largura = 230;
	notaJacare->altura = 200;

	Objeto* notaMico;
	notaMico = (Objeto*)malloc(sizeof(Objeto));
	notaMico->bitmap = NULL;
	notaMico->x = LARGURA_TELA - 240;
	notaMico->y = ALTURA_TELA - 220;
	notaMico->largura = 230;
	notaMico->altura = 200;

	Objeto marcaOnça;
	marcaOnça.bitmap = NULL;
	//mapa.x = LARGURA_TELA - 100;
	//mapa.y = ALTURA_TELA / 2 - 50;
	//mapa.largura = 100;
	//mapa.altura = 100;

	Objeto marcaTatu;
	marcaTatu.bitmap = NULL;
	//mapa.x = LARGURA_TELA - 100;
	//mapa.y = ALTURA_TELA / 2 - 50;
	//mapa.largura = 100;
	//mapa.altura = 100;

	Objeto marcaJacare;
	marcaJacare.bitmap = NULL;
	//mapa.x = LARGURA_TELA - 100;
	//mapa.y = ALTURA_TELA / 2 - 50;
	//mapa.largura = 100;
	//mapa.altura = 100;

	Objeto marcaMico;
	marcaMico.bitmap = NULL;
	//mapa.x = LARGURA_TELA - 100;
	//mapa.y = ALTURA_TELA / 2 - 50;
	//mapa.largura = 100;
	//mapa.altura = 100;

	Objeto saidaDireita;
	saidaDireita.bitmap = NULL;
	//mapa.x = LARGURA_TELA - 100;
	//mapa.y = ALTURA_TELA / 2 - 50;
	//mapa.largura = 100;
	//mapa.altura = 100;

	Objeto saidaCima;
	saidaDireita.bitmap = NULL;
	//mapa.x = LARGURA_TELA - 100;
	//mapa.y = ALTURA_TELA / 2 - 50;
	//mapa.largura = 100;
	//mapa.altura = 100;

	Objeto saidaBaixo;
	saidaDireita.bitmap = NULL;
	//mapa.x = LARGURA_TELA - 100;
	//mapa.y = ALTURA_TELA / 2 - 50;
	//mapa.largura = 100;
	//mapa.altura = 100;

	ALLEGRO_BITMAP* Background = al_load_bitmap("Imgs/fundo.png");

	mapa->bitmap = al_load_bitmap("Imgs/mapabrasil.png");

	notaOnça->bitmap = al_load_bitmap("Imgs/bloco.png");
	notaTatu->bitmap = al_load_bitmap("Imgs/bloco.png");
	notaJacare->bitmap = al_load_bitmap("Imgs/bloco.png");
	notaMico->bitmap = al_load_bitmap("Imgs/bloco.png");

	Background = al_load_bitmap("Imgs/fundo.png");

	if (!mapa->bitmap || !Background)
	{
		fprintf(stderr, "Falha ao iniciar imagem\n");
		al_destroy_display(janela);
		return -1;
	}

	int gameOver = 0;

	while (!gameOver)
	{
		while (!al_is_event_queue_empty(fila_eventos))
		{
			//Cria um evento
			ALLEGRO_EVENT evento;
			//espero por um evento da fila, e guarda em evento
			al_wait_for_event(fila_eventos, &evento);

			//se teve eventos e foi um evento de fechar janela, encerra repetição			
			if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				prog->Gameover = 1;
				gameOver = 1;
			}
		}

		al_draw_bitmap(Background, 0, 0, 0);
		al_draw_bitmap(mapa->bitmap,mapa->x,mapa->y,0);

		al_draw_bitmap(notaOnça->bitmap, notaOnça->x, notaOnça->y, 0);
		al_draw_bitmap(notaTatu->bitmap, notaTatu->x, notaTatu->y, 0);
		al_draw_bitmap(notaJacare->bitmap, notaJacare->x, notaJacare->y, 0);
		al_draw_bitmap(notaMico->bitmap, notaMico->x, notaMico->y, 0);

		al_flip_display();
	}
}