
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

	

	Objeto *notaOnca;
	notaOnca = (Objeto*)malloc(sizeof(Objeto));
	notaOnca->bitmap = NULL;
	notaOnca->x = 120;
	notaOnca->y = 100;
	notaOnca->largura = 230;
	notaOnca->altura = 200;

	Objeto* mapa;
	mapa = (Objeto*)malloc(sizeof(Objeto));
	mapa->bitmap = NULL;
	mapa->largura = 650;
	mapa->altura = 650;
	mapa->x = notaOnca->largura + notaOnca->x + 20;
	mapa->y = ALTURA_TELA / 2 - 330;

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

	Objeto* marcaOnca;
	marcaOnca = (Objeto*)malloc(sizeof(Objeto));
	marcaOnca->bitmap = NULL;
	marcaOnca->x = notaOnca->x + notaOnca->largura - 55;
	marcaOnca->y = notaOnca->y + notaOnca->altura - 55;
	marcaOnca->largura = 50;
	marcaOnca->altura = 50;

	Objeto *marcaTatu;
	marcaTatu = (Objeto*)malloc(sizeof(Objeto));
	marcaTatu->bitmap = NULL;
	marcaTatu->x = notaTatu->x + notaTatu->largura - 55;
	marcaTatu->y = notaTatu->y + notaTatu->altura - 55;
	marcaTatu->largura = 50;
	marcaTatu->altura = 50;

	Objeto *marcaJacare;
	marcaJacare = (Objeto*)malloc(sizeof(Objeto));
	marcaJacare->bitmap = NULL;
	marcaJacare->x = notaJacare->x + notaJacare->largura - 55;
	marcaJacare->y = notaJacare->y + notaJacare->altura - 55;
	marcaJacare->largura = 50;
	marcaJacare->altura = 50;

	Objeto *marcaMico;
	marcaMico = (Objeto*)malloc(sizeof(Objeto));
	marcaMico->bitmap = NULL;
	marcaMico->x = notaMico->x + notaMico->largura - 55;
	marcaMico->y = notaMico->y + notaMico->altura - 55;
	marcaMico->largura = 50;
	marcaMico->altura = 50;

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

	notaOnca->bitmap = al_load_bitmap("Imgs/nonca.png");
	notaTatu->bitmap = al_load_bitmap("Imgs/ntatu.png");
	notaJacare->bitmap = al_load_bitmap("Imgs/njacare.png");
	notaMico->bitmap = al_load_bitmap("Imgs/nmico.png");

	marcaOnca->bitmap = al_load_bitmap("Imgs/monca.png");
	marcaTatu->bitmap = al_load_bitmap("Imgs/mtatu.png");
	marcaJacare->bitmap = al_load_bitmap("Imgs/mjacare.png");
	marcaMico->bitmap = al_load_bitmap("Imgs/mmico.png");

	Background = al_load_bitmap("Imgs/fundo.png");

	int gameOver = 0;
	int arrastando = 0;
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
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				if (IsInside(evento.mouse.x, evento.mouse.y, marcaOnca))
				{
					arrastando = 1;
					marcaOnca->cliqueX = MapearDistancia(evento.mouse.x, marcaOnca->x);
					marcaOnca->cliqueY = MapearDistancia(evento.mouse.y, marcaOnca->y);
				}
				else if(IsInside(evento.mouse.x, evento.mouse.y, marcaTatu))
				{
					arrastando = 2;
					marcaTatu->cliqueX = MapearDistancia(evento.mouse.x, marcaTatu->x);
					marcaTatu->cliqueY = MapearDistancia(evento.mouse.y, marcaTatu->y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, marcaJacare))
				{
					arrastando = 3;
					marcaJacare->cliqueX = MapearDistancia(evento.mouse.x, marcaJacare->x);
					marcaJacare->cliqueY = MapearDistancia(evento.mouse.y, marcaJacare->y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, marcaMico))
				{
					arrastando = 4;
					marcaMico->cliqueX = MapearDistancia(evento.mouse.x, marcaMico->x);
					marcaMico->cliqueY = MapearDistancia(evento.mouse.y, marcaMico->y);
				}
				else {
					arrastando = 0;
				}
			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				arrastando = 0;
			}

			ALLEGRO_MOUSE_STATE state;

			al_get_mouse_state(&state);
			if (state.buttons & 1 && arrastando)
			{
				switch (arrastando)
				{
				case 1:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, marcaOnca)) {
						marcaOnca->x = evento.mouse.x - marcaOnca->cliqueX;
						marcaOnca->y = evento.mouse.y - marcaOnca->cliqueY;
					}
					break;
				case 2:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, marcaTatu)) {
						marcaTatu->x = evento.mouse.x - marcaTatu->cliqueX;
						marcaTatu->y = evento.mouse.y - marcaTatu->cliqueY;
					}
					break;
				case 3:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, marcaJacare)) {
						marcaJacare->x = evento.mouse.x - marcaJacare->cliqueX;
						marcaJacare->y = evento.mouse.y - marcaJacare->cliqueY;
					}
					break;
				case 4:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, marcaMico)) {
						marcaMico->x = evento.mouse.x - marcaMico->cliqueX;
						marcaMico->y = evento.mouse.y - marcaMico->cliqueY;
					}
					break;
				default:
					break;
				}
			}
		}

		al_draw_bitmap(Background, 0, 0, 0);
		al_draw_bitmap(mapa->bitmap,mapa->x,mapa->y,0);

		al_draw_bitmap(notaOnca->bitmap, notaOnca->x, notaOnca->y, 0);
		al_draw_bitmap(notaTatu->bitmap, notaTatu->x, notaTatu->y, 0);
		al_draw_bitmap(notaJacare->bitmap, notaJacare->x, notaJacare->y, 0);
		al_draw_bitmap(notaMico->bitmap, notaMico->x, notaMico->y, 0);

		al_draw_bitmap(marcaOnca->bitmap, marcaOnca->x, marcaOnca->y, 0);
		al_draw_bitmap(marcaTatu->bitmap, marcaTatu->x, marcaTatu->y, 0);
		al_draw_bitmap(marcaJacare->bitmap, marcaJacare->x, marcaJacare->y, 0);
		al_draw_bitmap(marcaMico->bitmap, marcaMico->x, marcaMico->y, 0);

		al_flip_display();
	}
}