#include <stdio.h>
#include <math.h>
// Inclui o arquivo de cabeçalho da biblioteca Allegro 5
#include <allegro5/allegro.h>
// Inclui o cabeçalho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
// Inclui a coisa do mouse
#include <allegro5/allegro_native_dialog.h>

#include "Funcoes.h"
#include "Struct.h"

Objeto* linha1;
Objeto* eventos, *notas;

int JogarFaseTimeLine(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* prog) {
	int i,j;

	linha1 = (Objeto*)malloc(sizeof(Objeto));
	linha1->bitmap = NULL;
	linha1->x = LARGURA_TELA/2 - 500;
	linha1->y = 500;
	linha1->largura = 1000;
	linha1->altura = 100;

	eventos = (Objeto*)malloc(sizeof(Objeto)*24);
	notas = (Objeto*)malloc(sizeof(Objeto) * 24);

	int mx = 0;
	int my = 0;
	int count = 1;
	for (i = 0; i < 6; i++) {//Percorre do 1º ao 6º elemento de uma linha do tempo
		for (j = 0; j < 4; j++) {//Percorre as 4 linhas do tempo
			eventos[i + 6 * j].bitmap = NULL;
			eventos[i + 6 * j].x = linha1->x + 100*mx;//Divide os 6 elementos da linha do tempo em 3 colunas
			eventos[i + 6 * j].y = 150 + 100*my;//Divide os 6 elementos da linha do tempo em 2 linhas
			eventos[i + 6 * j].largura = 50;
			eventos[i + 6 * j].altura = 50;
			if (count % 4 == 0)
				mx++;
			if (count % 12 == 0) {
				my++;
				mx = 0;
			}				
			count++;
		}		
	}
	for (i = 0; i < 24; i++) {
		notas[i].bitmap = NULL;
		notas[i].x = 550;
		notas[i].y = 150;
		notas[i].largura = 500;
		notas[i].altura = 300;
	}

	ALLEGRO_BITMAP* Background = al_load_bitmap("Imgs/fundo.png");

	linha1->bitmap = al_load_bitmap("Imgs/Timeline/line.png");

	eventos[0].bitmap = al_load_bitmap("Imgs/Timeline/1.png");
	eventos[1].bitmap = al_load_bitmap("Imgs/Timeline/2.png");
	eventos[2].bitmap = al_load_bitmap("Imgs/Timeline/3.png");
	eventos[3].bitmap = al_load_bitmap("Imgs/Timeline/4.png");
	eventos[4].bitmap = al_load_bitmap("Imgs/Timeline/5.png");
	eventos[5].bitmap = al_load_bitmap("Imgs/Timeline/6.png");
	eventos[6].bitmap = al_load_bitmap("Imgs/Timeline/1.png");
	eventos[7].bitmap = al_load_bitmap("Imgs/Timeline/2.png");
	eventos[8].bitmap = al_load_bitmap("Imgs/Timeline/3.png");
	eventos[9].bitmap = al_load_bitmap("Imgs/Timeline/4.png");
	eventos[10].bitmap = al_load_bitmap("Imgs/Timeline/5.png");
	eventos[11].bitmap = al_load_bitmap("Imgs/Timeline/6.png");
	eventos[12].bitmap = al_load_bitmap("Imgs/Timeline/1.png");
	eventos[13].bitmap = al_load_bitmap("Imgs/Timeline/2.png");
	eventos[14].bitmap = al_load_bitmap("Imgs/Timeline/3.png");
	eventos[15].bitmap = al_load_bitmap("Imgs/Timeline/4.png");
	eventos[16].bitmap = al_load_bitmap("Imgs/Timeline/5.png");
	eventos[17].bitmap = al_load_bitmap("Imgs/Timeline/6.png");
	eventos[18].bitmap = al_load_bitmap("Imgs/Timeline/1.png");
	eventos[19].bitmap = al_load_bitmap("Imgs/Timeline/2.png");
	eventos[20].bitmap = al_load_bitmap("Imgs/Timeline/3.png");
	eventos[21].bitmap = al_load_bitmap("Imgs/Timeline/4.png");
	eventos[22].bitmap = al_load_bitmap("Imgs/Timeline/5.png");
	eventos[23].bitmap = al_load_bitmap("Imgs/Timeline/6.png");

	int gameOver = 0;
	int linhaInGame = 0;////////////////
	int arrastando = 0;
	int Dentro = 0;
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
				if (IsInside(evento.mouse.x, evento.mouse.y, &eventos[0 + 6*linhaInGame]) && !prog->Salas[9])
				{
					arrastando = 1;
					eventos[0 + 6 * linhaInGame].cliqueX = MapearDistancia(evento.mouse.x, marcaOnca->x);
					eventos[0 + 6 * linhaInGame].cliqueY = MapearDistancia(evento.mouse.y, marcaOnca->y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, &eventos[1 + 6 * linhaInGame]) && !prog->Salas[9])
				{
					arrastando = 2;
					eventos[1 + 6 * linhaInGame].cliqueX = MapearDistancia(evento.mouse.x, marcaOnca->x);
					eventos[1 + 6 * linhaInGame].cliqueY = MapearDistancia(evento.mouse.y, marcaOnca->y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, &eventos[2 + 6 * linhaInGame]) && !prog->Salas[9])
				{
					arrastando = 3;
					eventos[2 + 6 * linhaInGame].cliqueX = MapearDistancia(evento.mouse.x, marcaOnca->x);
					eventos[2 + 6 * linhaInGame].cliqueY = MapearDistancia(evento.mouse.y, marcaOnca->y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, &eventos[3 + 6 * linhaInGame]) && !prog->Salas[9])
				{
					arrastando = 4;
					eventos[3 + 6 * linhaInGame].cliqueX = MapearDistancia(evento.mouse.x, marcaOnca->x);
					eventos[3 + 6 * linhaInGame].cliqueY = MapearDistancia(evento.mouse.y, marcaOnca->y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, &eventos[4 + 6 * linhaInGame]) && !prog->Salas[9])
				{
					arrastando = 5;
					eventos[4 + 6 * linhaInGame].cliqueX = MapearDistancia(evento.mouse.x, marcaOnca->x);
					eventos[4 + 6 * linhaInGame].cliqueY = MapearDistancia(evento.mouse.y, marcaOnca->y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, &eventos[5 + 6 * linhaInGame]) && !prog->Salas[9])
				{
					arrastando = 6;
					eventos[5 + 6 * linhaInGame].cliqueX = MapearDistancia(evento.mouse.x, marcaOnca->x);
					eventos[5 + 6 * linhaInGame].cliqueY = MapearDistancia(evento.mouse.y, marcaOnca->y);
				}
				else {
					arrastando = 0;
				}
			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				arrastando = 0;				
			}	
			else if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {////////////////
				for (i = 0; i < 24; i++) {
					if (IsInside(evento.mouse.x, evento.mouse.y, &eventos[i], 0)); {
						Dentro = i;
					}
				}
			}

			ALLEGRO_MOUSE_STATE state;

			al_get_mouse_state(&state);
			if (state.buttons & 1 && arrastando)
			{
				switch (arrastando)
				{
				case 1:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, &eventos[0 + 6 * linhaInGame])) {
						eventos[0 + 6 * linhaInGame].x = evento.mouse.x - eventos[0 + 6 * linhaInGame].cliqueX;
						eventos[0 + 6 * linhaInGame].y = evento.mouse.y - eventos[0 + 6 * linhaInGame].cliqueY;
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


		//al_draw_bitmap(saidaBaixo->bitmap, saidaBaixo->x, saidaBaixo->y, 0);
		//al_draw_bitmap(saidaCima->bitmap, saidaCima->x, saidaCima->y, 0);
		//al_draw_bitmap(saidaDireita->bitmap, saidaDireita->x, saidaDireita->y, 0);

		
		al_draw_bitmap(linha1->bitmap, linha1->x, linha1->y, 0);
		for (i = 0; i < 6; i++) {
			al_draw_bitmap(eventos[i].bitmap, eventos[i].x, eventos[i].y, 0);
		}
		if (linhaInGame >= 1) {
			for (i = 6; i < 12; i++) {
				al_draw_bitmap(eventos[i].bitmap, eventos[i].x, eventos[i].y, 0);
			}
		}
		if (linhaInGame >= 2) {
			for (i = 12; i < 18; i++) {
				al_draw_bitmap(eventos[i].bitmap, eventos[i].x, eventos[i].y, 0);
			}
		}
		if (linhaInGame >= 3) {
			for (i = 18; i < 24; i++) {
				al_draw_bitmap(eventos[i].bitmap, eventos[i].x, eventos[i].y, 0);
			}
		}
		


		caregaInventario(prog);
		al_flip_display();
	}
}