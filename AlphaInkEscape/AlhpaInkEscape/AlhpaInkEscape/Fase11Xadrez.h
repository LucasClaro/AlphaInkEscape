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
int JogarFase11xadrez(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* progresso)
{
	Objeto* SaidaCima = NULL, * SaidaEsquerda = NULL, * SaidaBaixo = NULL;
	Objeto* peao1 = NULL, * peao2 = NULL, * peao3 = NULL, * bispo = NULL,* torre1 = NULL,* torre2 = NULL,* rei = NULL;
	int Arrastando = 0;

	ALLEGRO_BITMAP* Background = NULL, * tab = NULL;

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

	peao1->bitmap = al_load_bitmap("Imgs/xadrez/peao.png");
	peao2->bitmap = al_load_bitmap("Imgs/xadrez/peao.png");
	peao3->bitmap = al_load_bitmap("Imgs/xadrez/peao.png");
	bispo->bitmap = al_load_bitmap("Imgs/xadrez/bispo.png");
	torre1->bitmap = al_load_bitmap("Imgs/xadrez/torre.png");
	torre2->bitmap = al_load_bitmap("Imgs/xadrez/torre.png");
	rei->bitmap = al_load_bitmap("Imgs/xadrez/rei.png");

	Background = al_load_bitmap("Imgs/fundo.png");
	tab = al_load_bitmap("Imgs/xadrez/tabuleiro.png");

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
				/*if (IsInside(evento.mouse.x, evento.mouse.y, SaidaCima))
				{
					progresso->proximaSala = 10;
					gameOver = 1;
				}*/
				//else if (IsInside(evento.mouse.x, evento.mouse.y, SaidaEsquerda)) //&& progresso->Salas[1]
				//{
				//	progresso->proximaSala = 4;
				//	gameOver = 1;
				//}
				/*else if (IsInside(evento.mouse.x, evento.mouse.y, SaidaBaixo))
				{
					progresso->proximaSala = 2;
					gameOver = 1;
				}*/
				
				/*else if (IsInside(evento.mouse.x, evento.mouse.y, progresso->Itens[0]) && !Arrastando) {
					Arrastando = 1;
					progresso->Itens[0]->cliqueX = MapearDistancia(evento.mouse.x, progresso->Itens[0]->x);
					progresso->Itens[0]->cliqueY = MapearDistancia(evento.mouse.y, progresso->Itens[0]->y);
				}
				
				else
				{
					Arrastando = 0;
				}*/
			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				Arrastando = 0;
			}

			ALLEGRO_MOUSE_STATE state;
			al_get_mouse_state(&state);
			if (state.buttons & 2)
			{
				printf("x: %d; y: %d\n",evento.mouse.x,evento.mouse.y);
			}
			/*
			if (state.buttons & 1 && Arrastando) {
				switch (Arrastando)
				{
				case 1:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, progresso->Itens[0])) {
						progresso->Itens[0]->x = evento.mouse.x - progresso->Itens[0]->cliqueX;
						progresso->Itens[0]->y = evento.mouse.y - progresso->Itens[0]->cliqueY;
					}
					break;
				
				default: Arrastando = 0;
					break;
				}
			}*/
			/*else if (state.buttons & 2)
			{
				printf("x: %d - y: %d\n",evento.mouse.x,evento.mouse.y);
			}*/

		}

		al_draw_bitmap(Background, 0, 0, 0);
		al_draw_bitmap(tab, 135, 98, 0);

		al_draw_bitmap(SaidaEsquerda->bitmap, SaidaEsquerda->x, SaidaEsquerda->y, 0);
		al_draw_bitmap(SaidaCima->bitmap, SaidaCima->x, SaidaCima->y, 0);
		al_draw_bitmap(SaidaBaixo->bitmap, SaidaBaixo->x, SaidaBaixo->y, 0);

		al_draw_bitmap(peao1->bitmap, peao1->x, peao1->y, 0);
		al_draw_bitmap(peao2->bitmap, peao2->x, peao2->y, 0);
		al_draw_bitmap(peao3->bitmap, peao3->x, peao3->y, 0);
		al_draw_bitmap(bispo->bitmap, bispo->x, bispo->y, 0);
		al_draw_bitmap(torre1->bitmap, torre1->x, torre1->y, 0);
		al_draw_bitmap(torre2->bitmap, torre2->x, torre2->y, 0);
		al_draw_bitmap(rei->bitmap, rei->x, rei->y, 0);

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


	al_destroy_bitmap(Background);
	al_destroy_bitmap(tab);
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