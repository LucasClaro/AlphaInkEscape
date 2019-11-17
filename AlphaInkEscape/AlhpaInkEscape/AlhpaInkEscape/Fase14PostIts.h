#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_native_dialog.h>

#include "Struct.h"
#include "Funcoes.h"

int JogarFase14PostIts(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* progresso)
{
	Objeto* SaidaCima = NULL, * SaidaEsquerda = NULL, * SaidaDireita = NULL;
	Objeto* PostIt = NULL, *fundoA = NULL, * fundoB = NULL, * fundoC = NULL, * fundoD = NULL;
	int Arrastando = 0;

	ALLEGRO_BITMAP* mural = NULL, *posicionado = NULL;

	SaidaCima = (Objeto*)malloc(sizeof(Objeto));
	SaidaCima->largura = 20;
	SaidaCima->altura = 20;
	SaidaCima->x = 110 + (LARGURA_TELA / 2) - (SaidaCima->largura / 2);
	SaidaCima->y = 0;
	SaidaCima->bitmap = progresso->cenario->setaCima;

	SaidaEsquerda = (Objeto*)malloc(sizeof(Objeto));
	SaidaEsquerda->largura = 20;
	SaidaEsquerda->altura = 20;
	SaidaEsquerda->x = 110;
	SaidaEsquerda->y = (ALTURA_TELA / 2) - (SaidaCima->altura / 2);
	SaidaEsquerda->bitmap = progresso->cenario->setaEsquerda;

	SaidaDireita = (Objeto*)malloc(sizeof(Objeto));
	SaidaDireita->largura = 20;
	SaidaDireita->altura = 20;
	SaidaDireita->x = LARGURA_TELA - SaidaDireita->largura;
	SaidaDireita->y = (ALTURA_TELA / 2) - (SaidaDireita->altura / 2);
	SaidaDireita->bitmap = progresso->cenario->cadeado;

	PostIt = (Objeto*)malloc(sizeof(Objeto));
	PostIt->altura = 183;
	PostIt->largura = 201;
	PostIt->x = 730;
	PostIt->y = 220;
	PostIt->bitmap = NULL;

	fundoA = (Objeto*)malloc(sizeof(Objeto));
	fundoA->largura = 220;
	fundoA->altura = 230;
	fundoA->x = 330;
	fundoA->y = 86;
	fundoA->bitmap = NULL;

	fundoB = (Objeto*)malloc(sizeof(Objeto));
	fundoB->largura = 220;
	fundoB->altura = 230;
	fundoB->x = 730;
	fundoB->y = 86;
	fundoB->bitmap = NULL;

	fundoC = (Objeto*)malloc(sizeof(Objeto));
	fundoC->largura = 220;
	fundoC->altura = 230;
	fundoC->x = 330;
	fundoC->y = 485;
	fundoC->bitmap = NULL;

	fundoD = (Objeto*)malloc(sizeof(Objeto));
	fundoD->largura = 220;
	fundoD->altura = 230;
	fundoD->x = 730;
	fundoD->y = 485;
	fundoD->bitmap = NULL;

	
	PostIt->bitmap = al_load_bitmap("Imgs/PostIts/postdaVinci.png");

	mural = al_load_bitmap("Imgs/PostIts/Separacao.png");
	posicionado = al_load_bitmap("Imgs/PostIts/posicionado.png");

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
					progresso->proximaSala = 10;
					al_play_sample(progresso->cenario->somSeta, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					gameOver = 1;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, progresso->cenario->btnSom)) {
					tocando = !tocando;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, SaidaEsquerda)) //&& progresso->Salas[1]
				{
					progresso->proximaSala = 13;
					al_play_sample(progresso->cenario->somSeta, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					gameOver = 1;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, SaidaDireita) && progresso->Salas[14])
				{
					progresso->proximaSala = 15;
					al_play_sample(progresso->cenario->somSeta, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					gameOver = 1;
				}
				else if (evento.mouse.x >= 0 && evento.mouse.x <= progresso->Itens[0]->largura && evento.mouse.y >= 95 && evento.mouse.y <= 95 + ((0 * ALTURA_TELA / 10) + progresso->Itens[0]->altura * 0.5) && !progresso->inventClick[0])
				{
					//i* ALTURA_TELA / 10 
					progresso->inventClick[0] = 1;
				}
				else if (evento.mouse.x >= 0 && evento.mouse.x <= progresso->Itens[1]->largura && evento.mouse.y >= 95 + ((0 * ALTURA_TELA / 10) + progresso->Itens[0]->altura * 0.5) && evento.mouse.y <= 95 + ((1 * ALTURA_TELA / 10) + progresso->Itens[1]->altura * 0.5) && !progresso->inventClick[1])
				{
					//i* ALTURA_TELA / 10 
					progresso->inventClick[1] = 1;
				}
				else if (progresso->Itens[2] != NULL)
				{
					if (evento.mouse.x >= 0 && evento.mouse.x <= progresso->Itens[2]->largura && evento.mouse.y >= 95 + ((1 * ALTURA_TELA / 10) + progresso->Itens[1]->altura * 0.5) && evento.mouse.y <= 95 + ((2 * ALTURA_TELA / 10) + progresso->Itens[2]->altura * 0.5) && !progresso->inventClick[2])
					{
						//i* ALTURA_TELA / 10 
						progresso->inventClick[2] = 1;
					}
				}

				if (IsInside(evento.mouse.x, evento.mouse.y, progresso->Itens[0]) && !Arrastando) {
					Arrastando = 1;
					progresso->Itens[0]->cliqueX = MapearDistancia(evento.mouse.x, progresso->Itens[0]->x);
					progresso->Itens[0]->cliqueY = MapearDistancia(evento.mouse.y, progresso->Itens[0]->y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, progresso->Itens[1]) && !Arrastando) {
					Arrastando = 2;
					progresso->Itens[1]->cliqueX = MapearDistancia(evento.mouse.x, progresso->Itens[1]->x);
					progresso->Itens[1]->cliqueY = MapearDistancia(evento.mouse.y, progresso->Itens[1]->y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, PostIt) && !Arrastando) {
					Arrastando = 3;
					PostIt->cliqueX = MapearDistancia(evento.mouse.x, PostIt->x);
					PostIt->cliqueY = MapearDistancia(evento.mouse.y, PostIt->y);
				}
				else if (progresso->Itens[2] != NULL)
				{
					if (IsInside(evento.mouse.x, evento.mouse.y, progresso->Itens[2]) && !Arrastando) {
						Arrastando = 4;
						progresso->Itens[2]->cliqueX = MapearDistancia(evento.mouse.x, progresso->Itens[2]->x);
						progresso->Itens[2]->cliqueY = MapearDistancia(evento.mouse.y, progresso->Itens[2]->y);
					}
				}
				else
				{
					Arrastando = 0;
				}
			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				Arrastando = 0;
			}

			ALLEGRO_MOUSE_STATE state;
			al_get_mouse_state(&state);

			if (state.buttons & 1 && Arrastando) {
				switch (Arrastando)
				{
				case 1:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, progresso->Itens[0])) {
						progresso->Itens[0]->x = evento.mouse.x - progresso->Itens[0]->cliqueX;
						progresso->Itens[0]->y = evento.mouse.y - progresso->Itens[0]->cliqueY;
					}
					break;
				case 2:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, progresso->Itens[1])) {
						progresso->Itens[1]->x = evento.mouse.x - progresso->Itens[1]->cliqueX;
						progresso->Itens[1]->y = evento.mouse.y - progresso->Itens[1]->cliqueY;
					}
					break;
				case 3:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, PostIt)) {
						PostIt->x = evento.mouse.x - PostIt->cliqueX;
						PostIt->y = evento.mouse.y - PostIt->cliqueY;
					}
					break;
				case 4:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, progresso->Itens[2])) {
						progresso->Itens[2]->x = evento.mouse.x - progresso->Itens[2]->cliqueX;
						progresso->Itens[2]->y = evento.mouse.y - progresso->Itens[2]->cliqueY;
					}
					break;
				default: Arrastando = 0;
					break;
				}
			}
			/*else if (state.buttons & 2)
			{
				printf("x: %d - y: %d\n",evento.mouse.x,evento.mouse.y);
			}*/
			if (progresso->Itens[2] != NULL)
			{
				if (IsInsideImagem(progresso->Itens[1], fundoA) && IsInsideImagem(progresso->Itens[0], fundoB) && IsInsideImagem(progresso->Itens[2], fundoC) && IsInsideImagem(PostIt, fundoD))
				{
					progresso->Salas[14] = 1;
					SaidaDireita->bitmap = progresso->cenario->setaDireita;
				}
			}

			if (IsInsideImagem(progresso->Itens[0], fundoA) || IsInsideImagem(progresso->Itens[1], fundoA) || IsInsideImagem(PostIt, fundoA))  
				fundoA->bitmap = posicionado;
			else
				fundoA->bitmap = NULL;

			if (IsInsideImagem(progresso->Itens[0], fundoB) || IsInsideImagem(progresso->Itens[1], fundoB) || IsInsideImagem(PostIt, fundoB))
				fundoB->bitmap = posicionado;
			else
				fundoB->bitmap = NULL;

			if (IsInsideImagem(progresso->Itens[0], fundoC) || IsInsideImagem(progresso->Itens[1], fundoC) || IsInsideImagem(PostIt, fundoC))
				fundoC->bitmap = posicionado;
			else
				fundoC->bitmap = NULL;

			if (IsInsideImagem(progresso->Itens[0], fundoD) || IsInsideImagem(progresso->Itens[1], fundoD) || IsInsideImagem(PostIt, fundoD))// ||  IsInsideImagem(progresso->Itens[2], fundoA)
				fundoD->bitmap = posicionado;
			else
				fundoD->bitmap = NULL;

			if (progresso->Itens[2] != NULL)
			{
				if(IsInsideImagem(progresso->Itens[2], fundoA))
					fundoA->bitmap = posicionado;
				else
					fundoA->bitmap = NULL;

				if (IsInsideImagem(progresso->Itens[2], fundoB))
					fundoB->bitmap = posicionado;
				else
					fundoB->bitmap = NULL;

				if (IsInsideImagem(progresso->Itens[2], fundoC))
					fundoC->bitmap = posicionado;
				else
					fundoC->bitmap = NULL;

				if (IsInsideImagem(progresso->Itens[2], fundoD))
					fundoD->bitmap = posicionado;
				else
					fundoD->bitmap = NULL;
			}
		}

		al_draw_bitmap(progresso->cenario->background, 0, 0, 0);
		al_draw_bitmap(mural, (LARGURA_TELA/2) - 400, 0, 0);

		al_draw_bitmap(SaidaEsquerda->bitmap, SaidaEsquerda->x, SaidaEsquerda->y, 0);
		al_draw_bitmap(SaidaCima->bitmap, SaidaCima->x, SaidaCima->y, 0);
		al_draw_bitmap(SaidaDireita->bitmap, SaidaDireita->x, SaidaDireita->y, 0);

		if (fundoA->bitmap != NULL)
			al_draw_bitmap(fundoA->bitmap, fundoA->x+5, fundoA->y+5, 0);

		if (fundoB->bitmap != NULL)
			al_draw_bitmap(fundoB->bitmap, fundoB->x + 5, fundoB->y + 5, 0);

		if (fundoC->bitmap != NULL)
			al_draw_bitmap(fundoC->bitmap, fundoC->x + 5, fundoC->y + 5, 0);

		if (fundoD->bitmap != NULL)
			al_draw_bitmap(fundoD->bitmap, fundoD->x + 5, fundoD->y + 5, 0);

		if (!progresso->Salas[14])
		{
			al_draw_bitmap(PostIt->bitmap, PostIt->x, PostIt->y, 0);

			if (progresso->inventClick[0])
				al_draw_bitmap(progresso->Itens[0]->bitmap, progresso->Itens[0]->x, progresso->Itens[0]->y, 0);

			if (progresso->inventClick[1])
				al_draw_bitmap(progresso->Itens[1]->bitmap, progresso->Itens[1]->x, progresso->Itens[1]->y, 0);

			if (progresso->inventClick[2])
				al_draw_bitmap(progresso->Itens[2]->bitmap, progresso->Itens[2]->x, progresso->Itens[2]->y, 0);
		}
		else
		{
			al_draw_bitmap(PostIt->bitmap, fundoD->x + 5, fundoD->y + 5, 0);

			if (progresso->inventClick[0])
				al_draw_bitmap(progresso->Itens[0]->bitmap, fundoB->x  + 5, fundoB->y + 5, 0);

			if (progresso->inventClick[1])
				al_draw_bitmap(progresso->Itens[1]->bitmap, fundoA->x + 5, fundoA->y + 5, 0);

			if (progresso->inventClick[2])
				al_draw_bitmap(progresso->Itens[2]->bitmap, fundoC->x + 5, fundoC->y + 5, 0);
		}
		
		som(progresso);
		caregaInventario(progresso);
		al_flip_display();
	}

	//Desalocação das coisas
	al_destroy_bitmap(PostIt->bitmap);

	/*al_destroy_bitmap(fundoA->bitmap);
	al_destroy_bitmap(fundoB->bitmap);
	al_destroy_bitmap(fundoC->bitmap);
	al_destroy_bitmap(fundoD->bitmap);*/
	al_destroy_bitmap(mural);
	al_destroy_bitmap(posicionado);
	//al_destroy_bitmap(item->bitmap);

	free(SaidaCima);
	free(SaidaEsquerda);
	free(SaidaDireita);
	//free(PostIt);
	free(fundoA);
	free(fundoB);
	free(fundoC);
	free(fundoD);
	
	//free(item);

	return 0;
}