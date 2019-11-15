#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_native_dialog.h>

#include "Struct.h"
#include "Funcoes.h"
// largura 1116
//altura 577

Objeto Tabuleiro[8][8];
Objeto* peao1 = NULL, * peao2 = NULL, * peao3 = NULL, * bispo = NULL, * torre1 = NULL, * torre2 = NULL, * rei = NULL;
int  errado = 0;
int JogarFase11xadrez(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* progresso)
{
	Objeto* SaidaCima = NULL, * SaidaEsquerda = NULL, * SaidaBaixo = NULL,* Reset;
	ALLEGRO_BITMAP* peaoazul1 = NULL, * peaoazul2 = NULL, * peaoazul3 = NULL, * bispoazul = NULL, * torreazul1 = NULL, * torreazul2 = NULL, * reiazul = NULL;
	int Arrastando = 0;

	ALLEGRO_BITMAP* Background = NULL, * tab = NULL,* podeAndar = NULL,* checkmate = NULL, * texto = NULL;

	if(!progresso->Salas[11])
		incializaTabuleiro();

	SaidaCima = (Objeto*)malloc(sizeof(Objeto));
	SaidaCima->largura = 20;
	SaidaCima->altura = 20;
	SaidaCima->x = 110 + (LARGURA_TELA / 2) - (SaidaCima->largura / 2);
	SaidaCima->y = 0;
	SaidaCima->bitmap = NULL;

	SaidaEsquerda = (Objeto*)malloc(sizeof(Objeto));
	SaidaEsquerda->largura = 20;
	SaidaEsquerda->altura = 20;
	SaidaEsquerda->x = 110;
	SaidaEsquerda->y = (ALTURA_TELA / 2) - (SaidaCima->altura / 2);
	SaidaEsquerda->bitmap = NULL;

	SaidaBaixo = (Objeto*)malloc(sizeof(Objeto));
	SaidaBaixo->largura = 20;
	SaidaBaixo->altura = 20;
	SaidaBaixo->x = 110 + (LARGURA_TELA / 2) - (SaidaBaixo->largura / 2);
	SaidaBaixo->y = ALTURA_TELA - SaidaBaixo->altura;
	SaidaBaixo->bitmap = NULL;

	Reset = (Objeto*)malloc(sizeof(Objeto));
	Reset->largura = 100;
	Reset->altura = 100;
	Reset->x = 250;
	Reset->y = 500;
	Reset->bitmap = NULL;

	peao1 = (Objeto*)malloc(sizeof(Objeto));
	peao1->largura = 63;
	peao1->altura = 63;
	peao1->x = Tabuleiro[4][4].x;
	peao1->y = Tabuleiro[4][4].y;
	peao1->bitmap = NULL;

	peao2 = (Objeto*)malloc(sizeof(Objeto));
	peao2->largura = 63;
	peao2->altura = 63;
	peao2->x = Tabuleiro[5][6].x;
	peao2->y = Tabuleiro[5][6].y;
	peao2->bitmap = NULL;

	peao3 = (Objeto*)malloc(sizeof(Objeto));
	peao3->largura = 63;
	peao3->altura = 63;
	peao3->x = Tabuleiro[6][7].x;
	peao3->y = Tabuleiro[6][7].y;
	peao3->bitmap = NULL;

	bispo = (Objeto*)malloc(sizeof(Objeto));
	bispo->largura = 63;
	bispo->altura = 63;
	bispo->x = Tabuleiro[2][7].x;
	bispo->y = Tabuleiro[2][7].y;
	bispo->bitmap = NULL;

	torre1 = (Objeto*)malloc(sizeof(Objeto));
	torre1->largura = 63;
	torre1->altura = 63;
	torre1->x = Tabuleiro[1][1].x;
	torre1->y = Tabuleiro[1][1].y;
	torre1->bitmap = NULL;

	torre2 = (Objeto*)malloc(sizeof(Objeto));
	torre2->largura = 63;
	torre2->altura = 63;
	torre2->x = Tabuleiro[1][6].x;
	torre2->y = Tabuleiro[1][6].y;
	torre2->bitmap = NULL;

	rei = (Objeto*)malloc(sizeof(Objeto));
	rei->largura = 63;
	rei->altura = 63;
	rei->x = Tabuleiro[6][6].x;
	rei->y = Tabuleiro[6][6].y;
	rei->bitmap = NULL;

	SaidaCima->bitmap = al_load_bitmap("Imgs/cima.png");
	SaidaEsquerda->bitmap = al_load_bitmap("Imgs/Esquerda.png");
	SaidaBaixo->bitmap = al_load_bitmap("Imgs/baixo.png");
	Reset->bitmap = al_load_bitmap("Imgs/Sapos/reset.png");

	peao1->bitmap = al_load_bitmap("Imgs/xadrez/peao.png");
	peao2->bitmap = al_load_bitmap("Imgs/xadrez/peao.png");
	peao3->bitmap = al_load_bitmap("Imgs/xadrez/peao.png");
	bispo->bitmap = al_load_bitmap("Imgs/xadrez/bispo.png");
	torre2->bitmap = al_load_bitmap("Imgs/xadrez/torre.png");
	torre1->bitmap = al_load_bitmap("Imgs/xadrez/torre.png");
	rei->bitmap = al_load_bitmap("Imgs/xadrez/rei.png");

	peaoazul1 = al_load_bitmap("Imgs/xadrez/peaoazul.png");
	peaoazul2 = al_load_bitmap("Imgs/xadrez/peaoazul.png");
	peaoazul3 = al_load_bitmap("Imgs/xadrez/peaoazul.png");
	bispoazul = al_load_bitmap("Imgs/xadrez/bispoazul.png");
	torreazul1 = al_load_bitmap("Imgs/xadrez/torreazul.png");
	torreazul2 = al_load_bitmap("Imgs/xadrez/torreazul.png");
	reiazul = al_load_bitmap("Imgs/xadrez/reiazul.png");

	Background = al_load_bitmap("Imgs/fundo.png");
	tab = al_load_bitmap("Imgs/xadrez/tabuleiro3.png");
	podeAndar = al_load_bitmap("Imgs/xadrez/podeandar.png");
	checkmate = al_load_bitmap("Imgs/xadrez/checkmate.png");
	texto = al_load_bitmap("Imgs/xadrez/texto.png");

	if (!SaidaCima->bitmap || !SaidaEsquerda->bitmap || !Background)
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
				progresso->Gameover = 1;
				gameOver = 1;
			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				if (IsInside(evento.mouse.x, evento.mouse.y, SaidaCima))
				{
					progresso->proximaSala = 7;
					gameOver = 1;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, SaidaEsquerda)) //&& progresso->Salas[1]
				{
					progresso->proximaSala = 10;
					gameOver = 1;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, SaidaBaixo))
				{
					progresso->proximaSala = 15;
					gameOver = 1;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, peao1) && !Arrastando && !progresso->Salas[11] && !errado) {
					Arrastando = 1;
					peao1->cliqueX = MapearDistancia(evento.mouse.x, peao1->x);
					peao1->cliqueY = MapearDistancia(evento.mouse.y, peao1->y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, peao2) && !Arrastando && !progresso->Salas[11] && !errado) {
					Arrastando = 2;
					peao2->cliqueX = MapearDistancia(evento.mouse.x, peao2->x);
					peao2->cliqueY = MapearDistancia(evento.mouse.y, peao2->y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, peao3) && !Arrastando && !progresso->Salas[11] && !errado) {
					Arrastando = 3;
					peao3->cliqueX = MapearDistancia(evento.mouse.x, peao3->x);
					peao3->cliqueY = MapearDistancia(evento.mouse.y, peao3->y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, bispo) && !Arrastando && !progresso->Salas[11] && !errado) {
					Arrastando = 4;
					bispo->cliqueX = MapearDistancia(evento.mouse.x, bispo->x);
					bispo->cliqueY = MapearDistancia(evento.mouse.y, bispo->y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, torre1) && !Arrastando && !progresso->Salas[11] && !errado) {
					Arrastando = 5;
					torre1->cliqueX = MapearDistancia(evento.mouse.x, torre1->x);
					torre1->cliqueY = MapearDistancia(evento.mouse.y, torre1->y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, torre2) && !Arrastando && !progresso->Salas[11] && !errado) {
					Arrastando = 6;
					torre2->cliqueX = MapearDistancia(evento.mouse.x, torre2->x);
					torre2->cliqueY = MapearDistancia(evento.mouse.y, torre2->y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, rei) && !Arrastando && !progresso->Salas[11] && !errado) {
					Arrastando = 7;
					rei->cliqueX = MapearDistancia(evento.mouse.x, rei->x);
					rei->cliqueY = MapearDistancia(evento.mouse.y, rei->y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, Reset) && errado)
				{
					reseta();
				}
				else
				{
					Arrastando = 0;
				}
			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				if (IsInsidePos(torre2, Tabuleiro[2][6]))
				{
					progresso->Salas[11] = 1;
					torre2->x = Tabuleiro[2][6].x;
					torre2->y = Tabuleiro[2][6].y;
					Arrastando = 0;
				}
				else 
				{
					switch (Arrastando)
					{
						case 1:
							if (IsInsidePos(peao1, Tabuleiro[3][4]))
							{
								peao1->x = Tabuleiro[3][4].x;
								peao1->y = Tabuleiro[3][4].y;
								Arrastando = 0;
								errado = 1;
							}
							else
							{
								peao1->x = Tabuleiro[4][4].x;
								peao1->y = Tabuleiro[4][4].y;
							}
							break;
						case 2:
							if (IsInsidePos(peao2, Tabuleiro[4][6]))
							{
								peao2->x = Tabuleiro[4][6].x;
								peao2->y = Tabuleiro[4][6].y;
								Arrastando = 0;
								errado = 1;
							}
							else
							{
								peao2->x = Tabuleiro[5][6].x;
								peao2->y = Tabuleiro[5][6].y;
							}
							break;
						case 3:
							if (IsInsidePos(peao3, Tabuleiro[5][7]))
							{
								peao3->x = Tabuleiro[5][7].x;
								peao3->y = Tabuleiro[5][7].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(peao3, Tabuleiro[4][7]))
							{
								peao3->x = Tabuleiro[4][7].x;
								peao3->y = Tabuleiro[4][7].y;
								Arrastando = 0;
								errado = 1;
							}
							else
							{
								peao3->x = Tabuleiro[6][7].x;
								peao3->y = Tabuleiro[6][7].y;
							}
							break;
						case 4:
							if (IsInsidePos(bispo, Tabuleiro[3][6]))
							{
								bispo->x = Tabuleiro[3][6].x;
								bispo->y = Tabuleiro[3][6].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(bispo, Tabuleiro[4][5]))
							{
								bispo->x = Tabuleiro[4][5].x;
								bispo->y = Tabuleiro[4][5].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(bispo, Tabuleiro[5][4]))
							{
								bispo->x = Tabuleiro[5][4].x;
								bispo->y = Tabuleiro[5][4].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(bispo, Tabuleiro[6][3]))
							{
								bispo->x = Tabuleiro[6][3].x;
								bispo->y = Tabuleiro[6][3].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(bispo, Tabuleiro[7][2]))
							{
								bispo->x = Tabuleiro[7][2].x;
								bispo->y = Tabuleiro[7][2].y;
								Arrastando = 0;
								errado = 1;
							}
							else
							{
								bispo->x = Tabuleiro[2][7].x;
								bispo->y = Tabuleiro[2][7].y;
							}
							break;
						case 5:
							if (IsInsidePos(torre1, Tabuleiro[1][0]))
							{
								torre1->x = Tabuleiro[1][0].x;
								torre1->y = Tabuleiro[1][0].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(torre1, Tabuleiro[1][2]))
							{
								torre1->x = Tabuleiro[1][2].x;
								torre1->y = Tabuleiro[1][2].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(torre1, Tabuleiro[1][3]))
							{
								torre1->x = Tabuleiro[1][3].x;
								torre1->y = Tabuleiro[1][3].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(torre1, Tabuleiro[1][4]))
							{
								torre1->x = Tabuleiro[1][4].x;
								torre1->y = Tabuleiro[1][4].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(torre1, Tabuleiro[1][5]))
							{
								torre1->x = Tabuleiro[1][5].x;
								torre1->y = Tabuleiro[1][5].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(torre1, Tabuleiro[0][1]))
							{
								torre1->x = Tabuleiro[0][1].x;
								torre1->y = Tabuleiro[0][1].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(torre1, Tabuleiro[2][1]))
							{
								torre1->x = Tabuleiro[2][1].x;
								torre1->y = Tabuleiro[2][1].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(torre1, Tabuleiro[3][1]))
							{
								torre1->x = Tabuleiro[3][1].x;
								torre1->y = Tabuleiro[3][1].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(torre1, Tabuleiro[4][1]))
							{
								torre1->x = Tabuleiro[4][1].x;
								torre1->y = Tabuleiro[4][1].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(torre1, Tabuleiro[5][1]))
							{
								torre1->x = Tabuleiro[5][1].x;
								torre1->y = Tabuleiro[5][1].y;
								Arrastando = 0;
								errado = 1;
							}

							else if (IsInsidePos(torre1, Tabuleiro[6][1]))
							{
								torre1->x = Tabuleiro[6][1].x;
								torre1->y = Tabuleiro[6][1].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(torre1, Tabuleiro[7][1]))
							{
								torre1->x = Tabuleiro[7][1].x;
								torre1->y = Tabuleiro[7][1].y;
								Arrastando = 0;
								errado = 1;
							}
							else
							{
								torre1->x = Tabuleiro[1][1].x;
								torre1->y = Tabuleiro[1][1].y;
							}
							break;
						case 6:
							if (IsInsidePos(torre2, Tabuleiro[1][2]))
							{
								torre2->x = Tabuleiro[1][2].x;
								torre2->y = Tabuleiro[1][2].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(torre2, Tabuleiro[1][3]))
							{
								torre2->x = Tabuleiro[1][3].x;
								torre2->y = Tabuleiro[1][3].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(torre2, Tabuleiro[1][4]))
							{
								torre2->x = Tabuleiro[1][4].x;
								torre2->y = Tabuleiro[1][4].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(torre2, Tabuleiro[1][5]))
							{
								torre2->x = Tabuleiro[1][5].x;
								torre2->y = Tabuleiro[1][5].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(torre2, Tabuleiro[0][6]))
							{
								torre2->x = Tabuleiro[0][6].x;
								torre2->y = Tabuleiro[0][6].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(torre2, Tabuleiro[2][6]))
							{
								torre2->x = Tabuleiro[2][6].x;
								torre2->y = Tabuleiro[2][6].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(torre2, Tabuleiro[3][6]))
							{
								torre2->x = Tabuleiro[3][6].x;
								torre2->y = Tabuleiro[3][6].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(torre2, Tabuleiro[4][6]))
							{
								torre2->x = Tabuleiro[4][6].x;
								torre2->y = Tabuleiro[4][6].y;
								Arrastando = 0;
								errado = 1;
							}
							else
							{
								torre2->x = Tabuleiro[1][6].x;
								torre2->y = Tabuleiro[1][6].y;
							}
							break;
						case 7:
							if (IsInsidePos(rei, Tabuleiro[7][5]))
							{
								rei->x = Tabuleiro[7][5].x;
								rei->y = Tabuleiro[7][5].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(rei, Tabuleiro[7][6]))
							{
								rei->x = Tabuleiro[7][6].x;
								rei->y = Tabuleiro[7][6].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(rei, Tabuleiro[7][7]))
							{
								rei->x = Tabuleiro[7][7].x;
								rei->y = Tabuleiro[7][7].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(rei, Tabuleiro[6][5]))
							{
								rei->x = Tabuleiro[6][5].x;
								rei->y = Tabuleiro[6][5].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(rei, Tabuleiro[5][5]))
							{
								rei->x = Tabuleiro[5][5].x;
								rei->y = Tabuleiro[5][5].y;
								Arrastando = 0;
								errado = 1;
							}
							else if (IsInsidePos(rei, Tabuleiro[5][7]))
							{
								rei->x = Tabuleiro[5][7].x;
								rei->y = Tabuleiro[5][7].y;
								Arrastando = 0;
								errado = 1;
							}
							else
							{
								rei->x = Tabuleiro[6][6].x;
								rei->y = Tabuleiro[6][6].y;
							}
							break;
						default: Arrastando = 0;
							break;
					}
					Arrastando = 0;
				}
			}

			ALLEGRO_MOUSE_STATE state;
			al_get_mouse_state(&state);
			/*if (state.buttons & 2)
			{
				printf("x: %d; y: %d\n",evento.mouse.x,evento.mouse.y);
			}
			*/
			if (state.buttons & 1 && Arrastando) {
				switch (Arrastando)
				{
					case 1:
							if (!VerificarBordas(evento.mouse.x, evento.mouse.y, peao1)) {
								peao1->x = evento.mouse.x - peao1->cliqueX;
								peao1->y = evento.mouse.y - peao1->cliqueY;
							}
						break;
					case 2:
							if (!VerificarBordas(evento.mouse.x, evento.mouse.y, peao2)) {
								peao2->x = evento.mouse.x - peao2->cliqueX;
								peao2->y = evento.mouse.y - peao2->cliqueY;
							}
						break;
					case 3:
							if (!VerificarBordas(evento.mouse.x, evento.mouse.y, peao3)) {
								peao3->x = evento.mouse.x - peao3->cliqueX;
								peao3->y = evento.mouse.y - peao3->cliqueY;
							}
						break;
					case 4:
							if (!VerificarBordas(evento.mouse.x, evento.mouse.y, bispo)) {
								bispo->x = evento.mouse.x - bispo->cliqueX;
								bispo->y = evento.mouse.y - bispo->cliqueY;
							}
						break;
					case 5:
							if (!VerificarBordas(evento.mouse.x, evento.mouse.y, torre1)) {
								torre1->x = evento.mouse.x - torre1->cliqueX;
								torre1->y = evento.mouse.y - torre1->cliqueY;
							}
						break;
					case 6:
							if (!VerificarBordas(evento.mouse.x, evento.mouse.y, torre2)) {
								torre2->x = evento.mouse.x - torre2->cliqueX;
								torre2->y = evento.mouse.y - torre2->cliqueY;
							}
						break;
					case 7:
							if (!VerificarBordas(evento.mouse.x, evento.mouse.y, rei)) {
								rei->x = evento.mouse.x - rei->cliqueX;
								rei->y = evento.mouse.y - rei->cliqueY;
							}
						break;
					default: Arrastando = 0;
						break;
				}
			}
		}

		al_draw_bitmap(Background, 0, 0, 0);
		al_draw_bitmap(tab, 135, 98, 0);
		al_draw_bitmap(texto, 110 + (LARGURA_TELA/2) - (688/2) , 20, 0);

		al_draw_bitmap(SaidaEsquerda->bitmap, SaidaEsquerda->x, SaidaEsquerda->y, 0);
		al_draw_bitmap(SaidaCima->bitmap, SaidaCima->x, SaidaCima->y, 0);
		al_draw_bitmap(SaidaBaixo->bitmap, SaidaBaixo->x, SaidaBaixo->y, 0);

		desenharAndar(Arrastando, podeAndar);

		if(progresso->Salas[11])
			al_draw_bitmap(checkmate, Tabuleiro[0][5].x, Tabuleiro[0][5].y, 0);

		al_draw_bitmap(peaoazul1, Tabuleiro[2][0].x, Tabuleiro[2][0].y, 0);
		al_draw_bitmap(peaoazul2, Tabuleiro[3][2].x, Tabuleiro[3][2].y, 0);
		al_draw_bitmap(peaoazul3, Tabuleiro[1][7].x, Tabuleiro[1][7].y, 0);
		al_draw_bitmap(bispoazul, Tabuleiro[6][0].x, Tabuleiro[6][0].y, 0);
		al_draw_bitmap(torreazul1, Tabuleiro[2][2].x, Tabuleiro[2][2].y, 0);
		al_draw_bitmap(torreazul2, Tabuleiro[0][4].x, Tabuleiro[0][4].y, 0);
		al_draw_bitmap(reiazul, Tabuleiro[0][5].x, Tabuleiro[0][5].y, 0);

		al_draw_bitmap(peao1->bitmap, peao1->x, peao1->y, 0);
		al_draw_bitmap(peao2->bitmap, peao2->x, peao2->y, 0);
		al_draw_bitmap(peao3->bitmap, peao3->x, peao3->y, 0);
		al_draw_bitmap(bispo->bitmap, bispo->x, bispo->y, 0);
		al_draw_bitmap(torre1->bitmap, torre1->x, torre1->y, 0);
		al_draw_bitmap(torre2->bitmap, torre2->x, torre2->y, 0);
		al_draw_bitmap(rei->bitmap, rei->x, rei->y, 0);

		if(errado)
			al_draw_bitmap(Reset->bitmap, Reset->x, Reset->y, 0);

		caregaInventario(progresso);
		al_flip_display();
	}

	//Desalocação das coisas
	al_destroy_bitmap(SaidaCima->bitmap);
	al_destroy_bitmap(SaidaEsquerda->bitmap);
	al_destroy_bitmap(SaidaBaixo->bitmap);

	al_destroy_bitmap(peao1->bitmap);
	al_destroy_bitmap(peao2->bitmap);
	al_destroy_bitmap(peao3->bitmap);
	al_destroy_bitmap(bispo->bitmap);
	al_destroy_bitmap(torre1->bitmap);
	al_destroy_bitmap(torre2->bitmap);
	al_destroy_bitmap(rei->bitmap);

	al_destroy_bitmap(peaoazul1);
	al_destroy_bitmap(peaoazul2);
	al_destroy_bitmap(peaoazul3);
	al_destroy_bitmap(bispoazul);
	al_destroy_bitmap(torreazul1);
	al_destroy_bitmap(torreazul2);
	al_destroy_bitmap(reiazul);

	al_destroy_bitmap(Background);
	al_destroy_bitmap(tab);
	al_destroy_bitmap(podeAndar);
	al_destroy_bitmap(checkmate);
	al_destroy_bitmap(texto);

	//al_destroy_bitmap(item->bitmap);

	free(peao1);
	free(peao2);
	free(peao3);
	free(bispo);
	free(torre1);
	free(torre2);
	free(rei);

	free(SaidaCima);
	free(SaidaEsquerda);
	free(SaidaBaixo);

	//free(item);

	return 0;
}

int incializaTabuleiro()
{
	int i,j;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			Tabuleiro[i][j].largura = 63;
			Tabuleiro[i][j].altura = 63;
			Tabuleiro[i][j].x = 456 + j * 63;
			Tabuleiro[i][j].y = 100 + i * 63;
			Tabuleiro[i][j].bitmap = NULL;
		}
	}
}

int desenharAndar(int Arrastando, ALLEGRO_BITMAP* podeAndar)
{
	switch (Arrastando)
	{
		case 1:
				al_draw_bitmap(podeAndar, Tabuleiro[3][4].x, Tabuleiro[3][4].y, 0);
			break;
		case 2:
				al_draw_bitmap(podeAndar, Tabuleiro[4][6].x, Tabuleiro[4][6].y, 0);
			break;
		case 3:
				al_draw_bitmap(podeAndar, Tabuleiro[5][7].x, Tabuleiro[5][7].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[4][7].x, Tabuleiro[4][7].y, 0);
			break;
		case 4:
				al_draw_bitmap(podeAndar, Tabuleiro[7][2].x, Tabuleiro[7][2].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[6][3].x, Tabuleiro[6][3].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[5][4].x, Tabuleiro[5][4].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[4][5].x, Tabuleiro[4][5].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[3][6].x, Tabuleiro[3][6].y, 0);
			break;
		case 5:
				al_draw_bitmap(podeAndar, Tabuleiro[1][0].x, Tabuleiro[1][0].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[1][2].x, Tabuleiro[1][2].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[1][3].x, Tabuleiro[1][3].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[1][4].x, Tabuleiro[1][4].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[1][5].x, Tabuleiro[1][5].y, 0);

				al_draw_bitmap(podeAndar, Tabuleiro[0][1].x, Tabuleiro[0][1].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[2][1].x, Tabuleiro[2][1].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[3][1].x, Tabuleiro[3][1].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[4][1].x, Tabuleiro[4][1].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[5][1].x, Tabuleiro[5][1].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[6][1].x, Tabuleiro[6][1].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[7][1].x, Tabuleiro[7][1].y, 0);
			break;
		case 6:
				al_draw_bitmap(podeAndar, Tabuleiro[1][2].x, Tabuleiro[1][2].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[1][3].x, Tabuleiro[1][3].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[1][4].x, Tabuleiro[1][4].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[1][5].x, Tabuleiro[1][5].y, 0);

				al_draw_bitmap(podeAndar, Tabuleiro[0][6].x, Tabuleiro[0][6].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[2][6].x, Tabuleiro[2][6].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[3][6].x, Tabuleiro[3][6].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[4][6].x, Tabuleiro[4][6].y, 0);
			break;
		case 7:
				al_draw_bitmap(podeAndar, Tabuleiro[7][5].x, Tabuleiro[7][5].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[7][6].x, Tabuleiro[7][6].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[7][7].x, Tabuleiro[7][7].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[6][5].x, Tabuleiro[6][5].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[5][5].x, Tabuleiro[5][5].y, 0);
				al_draw_bitmap(podeAndar, Tabuleiro[5][7].x, Tabuleiro[5][7].y, 0);
			break;
		default: Arrastando = 0;
			break;
	}
}

int IsInsidePos(Objeto* menor, Objeto maior) {
	int margem = 10;
	if (menor->x >= maior.x-margem && menor->x + menor->largura <= maior.x + maior.largura + margem && menor->y >= maior.y-margem && menor->y + menor->altura <= maior.y + maior.altura + margem) {
		return 1;
	}
	return 0;
}

int reseta()
{
	errado = 0;
	peao1->x = Tabuleiro[4][4].x;
	peao1->y = Tabuleiro[4][4].y;
	peao2->x = Tabuleiro[5][6].x;
	peao2->y = Tabuleiro[5][6].y;
	peao3->x = Tabuleiro[6][7].x;
	peao3->y = Tabuleiro[6][7].y;
	bispo->x = Tabuleiro[2][7].x;
	bispo->y = Tabuleiro[2][7].y;
	torre1->x = Tabuleiro[1][1].x;
	torre1->y = Tabuleiro[1][1].y;
	torre2->x = Tabuleiro[1][6].x;
	torre2->y = Tabuleiro[1][6].y;
	rei->x = Tabuleiro[6][6].x;
	rei->y = Tabuleiro[6][6].y;
}