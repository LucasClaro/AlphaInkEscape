#include <stdio.h>
#include <math.h>
// Inclui o arquivo de cabe�alho da biblioteca Allegro 5
#include <allegro5/allegro.h>
// Inclui o cabe�alho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
// Inclui a coisa do mouse
#include <allegro5/allegro_native_dialog.h>

#include "Funcoes.h"
#include "Struct.h"

Objeto* linha1, * linha2, * linha3, * linha4;
Objeto* eventos, * notas, * datas;


int JogarFase9TimeLine(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* prog) {
	int p1 = LARGURA_TELA / 2 - 450, p2 = p1 + 175, p3 = p2 + 175, p4 = p3 + 175, p5 = p4 + 175, p6 = p5 + 175;
	int i, j;

	Objeto* saidaCima;
	saidaCima = (Objeto*)malloc(sizeof(Objeto));
	saidaCima->bitmap = prog->cenario->setaCima;
	saidaCima->x = 110 + LARGURA_TELA / 2 - 10;
	saidaCima->y = 0;
	saidaCima->largura = 20;
	saidaCima->altura = 20;

	linha1 = (Objeto*)malloc(sizeof(Objeto));
	linha1->bitmap = NULL;
	linha1->x = LARGURA_TELA / 2 - 450;
	linha1->y = 300;
	linha1->largura = 1000;
	linha1->altura = 100;

	linha2 = (Objeto*)malloc(sizeof(Objeto));
	linha2->bitmap = NULL;
	linha2->x = LARGURA_TELA / 2 - 450;
	linha2->y = linha1->y + linha1->altura + 10;
	linha2->largura = 1000;
	linha2->altura = 100;

	linha3 = (Objeto*)malloc(sizeof(Objeto));
	linha3->bitmap = NULL;
	linha3->x = LARGURA_TELA / 2 - 450;
	linha3->y = linha2->y + linha2->altura + 10;;
	linha3->largura = 1000;
	linha3->altura = 100;

	linha4 = (Objeto*)malloc(sizeof(Objeto));
	linha4->bitmap = NULL;
	linha4->x = LARGURA_TELA / 2 - 450;
	linha4->y = linha3->y + linha3->altura + 10;;
	linha4->largura = 1000;
	linha4->altura = 100;

	eventos = (Objeto*)malloc(sizeof(Objeto) * 24);
	notas = (Objeto*)malloc(sizeof(Objeto) * 24);
	datas = (Objeto*)malloc(sizeof(Objeto) * 24);

	datas[0].bitmap = al_load_bitmap("Imgs/Timeline/data.png");
	datas[0].x = p3 + 200;
	datas[0].y = linha1->y;
	datas[0].largura = 100;
	datas[0].altura = 100;

	datas[1].bitmap = al_load_bitmap("Imgs/Timeline/data.png");
	datas[1].x = p5+100;
	datas[1].y = linha1->y;
	datas[1].largura = 100;
	datas[1].altura = 100;

	datas[2].bitmap = al_load_bitmap("Imgs/Timeline/data.png");
	datas[2].x = p4 + 200;
	datas[2].y = linha1->y;
	datas[2].largura = 100;
	datas[2].altura = 100;

	datas[3].bitmap = al_load_bitmap("Imgs/Timeline/data.png");
	datas[3].x = p2+200;
	datas[3].y = linha1->y;
	datas[3].largura = 100;
	datas[3].altura = 100;

	datas[4].bitmap = al_load_bitmap("Imgs/Timeline/data.png");
	datas[4].x = p6;
	datas[4].y = linha1->y;
	datas[4].largura = 100;
	datas[4].altura = 100;

	datas[5].bitmap = al_load_bitmap("Imgs/Timeline/data.png");
	datas[5].x = p1;
	datas[5].y = linha1->y;
	datas[5].largura = 100;
	datas[5].altura = 100;

	datas[6].bitmap = al_load_bitmap("Imgs/Timeline/data.png");
	datas[6].x = p5-100;
	datas[6].y = linha2->y;
	datas[6].largura = 100;
	datas[6].altura = 100;

	datas[7].bitmap = al_load_bitmap("Imgs/Timeline/data.png");
	datas[7].x = p3-175+25;
	datas[7].y = linha2->y;
	datas[7].largura = 100;
	datas[7].altura = 100;

	datas[8].bitmap = al_load_bitmap("Imgs/Timeline/data.png");
	datas[8].x = p2-85+25;
	datas[8].y = linha2->y;
	datas[8].largura = 100;
	datas[8].altura = 100;

	datas[9].bitmap = al_load_bitmap("Imgs/Timeline/data.png");
	datas[9].x = p6;
	datas[9].y = linha2->y;
	datas[9].largura = 100;
	datas[9].altura = 100;

	datas[10].bitmap = al_load_bitmap("Imgs/Timeline/data.png");
	datas[10].x = p1;
	datas[10].y = linha2->y;
	datas[10].largura = 100;
	datas[10].altura = 100;

	datas[11].bitmap = al_load_bitmap("Imgs/Timeline/data.png");
	datas[11].x = p4;
	datas[11].y = linha2->y;
	datas[11].largura = 100;
	datas[11].altura = 100;

	datas[12].bitmap = al_load_bitmap("Imgs/Timeline/data.png");
	datas[12].x = p4+150;
	datas[12].y = linha3->y;
	datas[12].largura = 100;
	datas[12].altura = 100;

	datas[13].bitmap = al_load_bitmap("Imgs/Timeline/data.png");
	datas[13].x = p1;
	datas[13].y = linha3->y;
	datas[13].largura = 100;
	datas[13].altura = 100;

	datas[14].bitmap = al_load_bitmap("Imgs/Timeline/data.png");
	datas[14].x = p6;
	datas[14].y = linha3->y;
	datas[14].largura = 100;
	datas[14].altura = 100;

	datas[15].bitmap = al_load_bitmap("Imgs/Timeline/data.png");
	datas[15].x = p2;
	datas[15].y = linha3->y;
	datas[15].largura = 100;
	datas[15].altura = 100;

	datas[16].bitmap = al_load_bitmap("Imgs/Timeline/data.png");
	datas[16].x = p3-25;
	datas[16].y = linha3->y;
	datas[16].largura = 100;
	datas[16].altura = 100;

	datas[17].bitmap = al_load_bitmap("Imgs/Timeline/data.png");
	datas[17].x = p5+100;
	datas[17].y = linha3->y;
	datas[17].largura = 100;
	datas[17].altura = 100;

	datas[18].bitmap = al_load_bitmap("Imgs/Timeline/data.png");
	datas[18].x = p6;
	datas[18].y = linha4->y;
	datas[18].largura = 100;
	datas[18].altura = 100;

	datas[19].bitmap = al_load_bitmap("Imgs/Timeline/data.png");
	datas[19].x = p3;
	datas[19].y = linha4->y;
	datas[19].largura = 100;
	datas[19].altura = 100;

	datas[20].bitmap = al_load_bitmap("Imgs/Timeline/data.png");
	datas[20].x = p2;
	datas[20].y = linha4->y;
	datas[20].largura = 100;
	datas[20].altura = 100;

	datas[21].bitmap = al_load_bitmap("Imgs/Timeline/data.png");
	datas[21].x = p5;
	datas[21].y = linha4->y;
	datas[21].largura = 100;
	datas[21].altura = 100;

	datas[22].bitmap = al_load_bitmap("Imgs/Timeline/data.png");
	datas[22].x = p1;
	datas[22].y = linha4->y;
	datas[22].largura = 100;
	datas[22].altura = 100;

	datas[23].bitmap = al_load_bitmap("Imgs/Timeline/data.png");
	datas[23].x = p4;
	datas[23].y = linha4->y;
	datas[23].largura = 100;
	datas[23].altura = 100;

	int mx = 0;
	int my = 0;
	int count = 1;
	for (i = 0; i < 6; i++) {//Percorre do 1� ao 6� elemento de uma linha do tempo
		for (j = 0; j < 4; j++) {//Percorre as 4 linhas do tempo
			eventos[i + 6 * j].bitmap = NULL;
			eventos[i + 6 * j].x = linha1->x + 100 * mx;//Divide os 6 elementos da linha do tempo em 3 colunas
			eventos[i + 6 * j].y = 100 + 120 * my;//Divide os 6 elementos da linha do tempo em 2 linhas
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
		notas[i].y = 100;
		notas[i].largura = 500;
		notas[i].altura = 300;
	}

	ALLEGRO_BITMAP* Background = prog->cenario->background;

	linha1->bitmap = al_load_bitmap("Imgs/Timeline/line.png");
	linha2->bitmap = al_load_bitmap("Imgs/Timeline/line.png");
	linha3->bitmap = al_load_bitmap("Imgs/Timeline/line.png");
	linha4->bitmap = al_load_bitmap("Imgs/Timeline/line.png");

	eventos[0].bitmap = al_load_bitmap("Imgs/Timeline/3.png");
	eventos[1].bitmap = al_load_bitmap("Imgs/Timeline/5.png");
	eventos[2].bitmap = al_load_bitmap("Imgs/Timeline/4.png");
	eventos[3].bitmap = al_load_bitmap("Imgs/Timeline/2.png");
	eventos[4].bitmap = al_load_bitmap("Imgs/Timeline/6.png");
	eventos[5].bitmap = al_load_bitmap("Imgs/Timeline/1.png");
	eventos[6].bitmap = al_load_bitmap("Imgs/Timeline/11.png");
	eventos[7].bitmap = al_load_bitmap("Imgs/Timeline/9.png");
	eventos[8].bitmap = al_load_bitmap("Imgs/Timeline/8.png");
	eventos[9].bitmap = al_load_bitmap("Imgs/Timeline/12.png");
	eventos[10].bitmap = al_load_bitmap("Imgs/Timeline/7.png");
	eventos[11].bitmap = al_load_bitmap("Imgs/Timeline/10.png");
	eventos[12].bitmap = al_load_bitmap("Imgs/Timeline/16.png");
	eventos[13].bitmap = al_load_bitmap("Imgs/Timeline/13.png");
	eventos[14].bitmap = al_load_bitmap("Imgs/Timeline/18.png");
	eventos[15].bitmap = al_load_bitmap("Imgs/Timeline/14.png");
	eventos[16].bitmap = al_load_bitmap("Imgs/Timeline/15.png");
	eventos[17].bitmap = al_load_bitmap("Imgs/Timeline/17.png");
	eventos[18].bitmap = al_load_bitmap("Imgs/Timeline/24.png");
	eventos[19].bitmap = al_load_bitmap("Imgs/Timeline/21.png");
	eventos[20].bitmap = al_load_bitmap("Imgs/Timeline/20.png");
	eventos[21].bitmap = al_load_bitmap("Imgs/Timeline/23.png");
	eventos[22].bitmap = al_load_bitmap("Imgs/Timeline/19.png");
	eventos[23].bitmap = al_load_bitmap("Imgs/Timeline/22.png");

	notas[0].bitmap = al_load_bitmap("Imgs/Timeline/n3.png");
	notas[1].bitmap = al_load_bitmap("Imgs/Timeline/n5.png");
	notas[2].bitmap = al_load_bitmap("Imgs/Timeline/n4.png");
	notas[3].bitmap = al_load_bitmap("Imgs/Timeline/n2.png");
	notas[4].bitmap = al_load_bitmap("Imgs/Timeline/n6.png");
	notas[5].bitmap = al_load_bitmap("Imgs/Timeline/n1.png");
	notas[6].bitmap = al_load_bitmap("Imgs/Timeline/n11.png");
	notas[7].bitmap = al_load_bitmap("Imgs/Timeline/n9.png");
	notas[8].bitmap = al_load_bitmap("Imgs/Timeline/n8.png");
	notas[9].bitmap = al_load_bitmap("Imgs/Timeline/n12.png");
	notas[10].bitmap = al_load_bitmap("Imgs/Timeline/n7.png");
	notas[11].bitmap = al_load_bitmap("Imgs/Timeline/n10.png");
	notas[12].bitmap = al_load_bitmap("Imgs/Timeline/n16.png");
	notas[13].bitmap = al_load_bitmap("Imgs/Timeline/n13.png");
	notas[14].bitmap = al_load_bitmap("Imgs/Timeline/n18.png");
	notas[15].bitmap = al_load_bitmap("Imgs/Timeline/n14.png");
	notas[16].bitmap = al_load_bitmap("Imgs/Timeline/n15.png");
	notas[17].bitmap = al_load_bitmap("Imgs/Timeline/n17.png");
	notas[18].bitmap = al_load_bitmap("Imgs/Timeline/n24.png");
	notas[19].bitmap = al_load_bitmap("Imgs/Timeline/n21.png");
	notas[20].bitmap = al_load_bitmap("Imgs/Timeline/n20.png");
	notas[21].bitmap = al_load_bitmap("Imgs/Timeline/n23.png");
	notas[22].bitmap = al_load_bitmap("Imgs/Timeline/n19.png");
	notas[23].bitmap = al_load_bitmap("Imgs/Timeline/n22.png");

	int gameOver = 0;
	int arrastando = 0;
	int Dentro = -1;
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
				//if (IsInside(evento.mouse.x, evento.mouse.y, saidaCima) && prog->Salas[9]) {
				if (IsInside(evento.mouse.x, evento.mouse.y, saidaCima)) {
					prog->proximaSala = 5;////////////////////////////////
					al_play_sample(prog->cenario->somSeta, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					gameOver = 1;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, &eventos[0 + 6 * prog->linhaInGame]) && !prog->Salas[9])
				{
					arrastando = 1;
					eventos[0 + 6 * prog->linhaInGame].cliqueX = MapearDistancia(evento.mouse.x, eventos[0 + 6 * prog->linhaInGame].x);
					eventos[0 + 6 * prog->linhaInGame].cliqueY = MapearDistancia(evento.mouse.y, eventos[0 + 6 * prog->linhaInGame].y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, &eventos[1 + 6 * prog->linhaInGame]) && !prog->Salas[9])
				{
					arrastando = 2;
					eventos[1 + 6 * prog->linhaInGame].cliqueX = MapearDistancia(evento.mouse.x, eventos[1 + 6 * prog->linhaInGame].x);
					eventos[1 + 6 * prog->linhaInGame].cliqueY = MapearDistancia(evento.mouse.y, eventos[1 + 6 * prog->linhaInGame].y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, &eventos[2 + 6 * prog->linhaInGame]) && !prog->Salas[9])
				{
					arrastando = 3;
					eventos[2 + 6 * prog->linhaInGame].cliqueX = MapearDistancia(evento.mouse.x, eventos[2 + 6 * prog->linhaInGame].x);
					eventos[2 + 6 * prog->linhaInGame].cliqueY = MapearDistancia(evento.mouse.y, eventos[2 + 6 * prog->linhaInGame].y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, &eventos[3 + 6 * prog->linhaInGame]) && !prog->Salas[9])
				{
					arrastando = 4;
					eventos[3 + 6 * prog->linhaInGame].cliqueX = MapearDistancia(evento.mouse.x, eventos[3 + 6 * prog->linhaInGame].x);
					eventos[3 + 6 * prog->linhaInGame].cliqueY = MapearDistancia(evento.mouse.y, eventos[3 + 6 * prog->linhaInGame].y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, &eventos[4 + 6 * prog->linhaInGame]) && !prog->Salas[9])
				{
					arrastando = 5;
					eventos[4 + 6 * prog->linhaInGame].cliqueX = MapearDistancia(evento.mouse.x, eventos[4 + 6 * prog->linhaInGame].x);
					eventos[4 + 6 * prog->linhaInGame].cliqueY = MapearDistancia(evento.mouse.y, eventos[4 + 6 * prog->linhaInGame].y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, &eventos[5 + 6 * prog->linhaInGame]) && !prog->Salas[9])
				{
					arrastando = 6;
					eventos[5 + 6 * prog->linhaInGame].cliqueX = MapearDistancia(evento.mouse.x, eventos[5 + 6 * prog->linhaInGame].x);
					eventos[5 + 6 * prog->linhaInGame].cliqueY = MapearDistancia(evento.mouse.y, eventos[5 + 6 * prog->linhaInGame].y);
				}
				else {
					arrastando = 0;
				}
			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				arrastando = 0;
				if (VerificarLinha(prog->linhaInGame))
					prog->linhaInGame++;
				if (prog->linhaInGame >= 4) {
					prog->Salas[9] = 1;
				}
			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {////////////////
				if (DentroDe(evento) >= 0)
					Dentro = DentroDe(evento);
			}

			ALLEGRO_MOUSE_STATE state;

			al_get_mouse_state(&state);
			if (state.buttons & 1 && arrastando)
			{
				switch (arrastando)
				{
				case 1:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, &eventos[0 + 6 * prog->linhaInGame])) {
						eventos[0 + 6 * prog->linhaInGame].x = evento.mouse.x - eventos[0 + 6 * prog->linhaInGame].cliqueX;
						eventos[0 + 6 * prog->linhaInGame].y = evento.mouse.y - eventos[0 + 6 * prog->linhaInGame].cliqueY;
					}
					break;
				case 2:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, &eventos[1 + 6 * prog->linhaInGame])) {
						eventos[1 + 6 * prog->linhaInGame].x = evento.mouse.x - eventos[1 + 6 * prog->linhaInGame].cliqueX;
						eventos[1 + 6 * prog->linhaInGame].y = evento.mouse.y - eventos[1 + 6 * prog->linhaInGame].cliqueY;
					}
					break;
				case 3:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, &eventos[2 + 6 * prog->linhaInGame])) {
						eventos[2 + 6 * prog->linhaInGame].x = evento.mouse.x - eventos[2 + 6 * prog->linhaInGame].cliqueX;
						eventos[2 + 6 * prog->linhaInGame].y = evento.mouse.y - eventos[2 + 6 * prog->linhaInGame].cliqueY;
					}
					break;
				case 4:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, &eventos[3 + 6 * prog->linhaInGame])) {
						eventos[3 + 6 * prog->linhaInGame].x = evento.mouse.x - eventos[3 + 6 * prog->linhaInGame].cliqueX;
						eventos[3 + 6 * prog->linhaInGame].y = evento.mouse.y - eventos[3 + 6 * prog->linhaInGame].cliqueY;
					}
					break;
				case 5:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, &eventos[4 + 6 * prog->linhaInGame])) {
						eventos[4 + 6 * prog->linhaInGame].x = evento.mouse.x - eventos[4 + 6 * prog->linhaInGame].cliqueX;
						eventos[4 + 6 * prog->linhaInGame].y = evento.mouse.y - eventos[4 + 6 * prog->linhaInGame].cliqueY;
					}
					break;
				case 6:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, &eventos[5 + 6 * prog->linhaInGame])) {
						eventos[5 + 6 * prog->linhaInGame].x = evento.mouse.x - eventos[5 + 6 * prog->linhaInGame].cliqueX;
						eventos[5 + 6 * prog->linhaInGame].y = evento.mouse.y - eventos[5 + 6 * prog->linhaInGame].cliqueY;
					}
					break;
				default:
					break;
				}
			}
		}


		al_draw_bitmap(Background, 0, 0, 0);

		//al_draw_bitmap(saidaBaixo->bitmap, saidaBaixo->x, saidaBaixo->y, 0);
		/*if (prog->Salas[5])*/
			al_draw_bitmap(saidaCima->bitmap, saidaCima->x, saidaCima->y, 0);
		


		al_draw_bitmap(linha1->bitmap, linha1->x, linha1->y, 0);
		if (prog->linhaInGame >= 1)
			al_draw_bitmap(linha2->bitmap, linha2->x, linha2->y, 0);
		if (prog->linhaInGame >= 2)
			al_draw_bitmap(linha3->bitmap, linha3->x, linha3->y, 0);
		if (prog->linhaInGame >= 3)
			al_draw_bitmap(linha4->bitmap, linha4->x, linha4->y, 0);

		if (Dentro >= 0 && Dentro < (1+ prog->linhaInGame)*6) {
			al_draw_bitmap(notas[Dentro].bitmap, notas[Dentro].x, notas[Dentro].y, 0);
		}

		if (prog->linhaInGame == 0) {
			for (i = 0; i < 6; i++) {
				al_draw_bitmap(datas[i].bitmap, datas[i].x, datas[i].y, 0);
				al_draw_bitmap(eventos[i].bitmap, eventos[i].x, eventos[i].y, 0);
			}
		}	
		if (prog->linhaInGame == 1) {
			for (i = 0; i < 6; i++) {
				al_draw_bitmap(datas[i].bitmap, datas[i].x, datas[i].y, 0);
				al_draw_bitmap(eventos[i].bitmap, datas[i].x+25, datas[i].y+25, 0);
			}			
			for (i = 6; i < 12; i++) {
				al_draw_bitmap(datas[i].bitmap, datas[i].x, datas[i].y, 0);
			}
			for (i = 6; i < 12; i++)
			{
				al_draw_bitmap(eventos[i].bitmap, eventos[i].x, eventos[i].y, 0);
			}
		}
		if (prog->linhaInGame == 2) {
			for (i = 0; i < 12; i++) {
				al_draw_bitmap(datas[i].bitmap, datas[i].x, datas[i].y, 0);
			}
			for (i = 0; i < 12; i++)
			{
				al_draw_bitmap(eventos[i].bitmap, datas[i].x+25, datas[i].y+25, 0);
			}
			for (i = 12; i < 18; i++) {
				al_draw_bitmap(datas[i].bitmap, datas[i].x, datas[i].y, 0);
			}
			for (i = 12; i < 18; i++) {
				al_draw_bitmap(eventos[i].bitmap, eventos[i].x, eventos[i].y, 0);
			}
		}
		if (prog->linhaInGame == 3 && !prog->Salas[9]) {
			for (i = 0; i < 18; i++) {
				al_draw_bitmap(datas[i].bitmap, datas[i].x, datas[i].y, 0);
			}
			for (i = 0; i < 18; i++) {
				al_draw_bitmap(eventos[i].bitmap, datas[i].x+25, datas[i].y+25, 0);
			}
			for (i = 18; i < 24; i++) {
				al_draw_bitmap(datas[i].bitmap, datas[i].x, datas[i].y, 0);
			}
			for (i = 18; i < 24; i++) {
				al_draw_bitmap(eventos[i].bitmap, eventos[i].x, eventos[i].y, 0);
			}
		}
		if (prog->Salas[9]) {
			for (i = 0; i < 24; i++) {
				al_draw_bitmap(datas[i].bitmap, datas[i].x, datas[i].y, 0);
			}
			for (i = 0; i < 24; i++) {
				al_draw_bitmap(eventos[i].bitmap, datas[i].x+25, datas[i].y+25, 0);
			}
		}

		caregaInventario(prog);
		al_flip_display();
	}
	return 0;
}

int DentroDe(ALLEGRO_EVENT evento) {
	int i;
	for (i = 0; i < 24; i++)
	{
		if (IsInside(evento.mouse.x, evento.mouse.y, &eventos[i]))
			return i;
	}
	return -1;
}

int VerificarLinha(int linha) {
	if (IsInsideImagem(&eventos[0 + 6 * linha], &datas[0 + 6 * linha]) && IsInsideImagem(&eventos[1 + 6 * linha], &datas[1 + 6 * linha]) && IsInsideImagem(&eventos[2 + 6 * linha], &datas[2 + 6 * linha]) && IsInsideImagem(&eventos[3 + 6 * linha], &datas[3 + 6 * linha]) && IsInsideImagem(&eventos[4 + 6 * linha], &datas[4 + 6 * linha]) && IsInsideImagem(&eventos[5 + 6 * linha], &datas[5 + 6 * linha]));
}