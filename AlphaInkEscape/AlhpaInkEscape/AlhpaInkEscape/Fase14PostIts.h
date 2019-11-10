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

	ALLEGRO_BITMAP* Background = NULL, * mural = NULL;

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

	SaidaDireita = (Objeto*)malloc(sizeof(Objeto));
	SaidaDireita->largura = 20;
	SaidaDireita->altura = 20;
	SaidaDireita->x = LARGURA_TELA - SaidaDireita->largura;
	SaidaDireita->y = (ALTURA_TELA / 2) - (SaidaDireita->altura / 2);
	SaidaDireita->bitmap = NULL;

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

	SaidaCima->bitmap = al_load_bitmap("Imgs/cima.png");
	SaidaEsquerda->bitmap = al_load_bitmap("Imgs/Esquerda.png");
	SaidaDireita->bitmap = al_load_bitmap("Imgs/Direita.png");
	PostIt->bitmap = al_load_bitmap("Imgs/postitHomem.png");

	Background = al_load_bitmap("Imgs/fundo.png");
	mural = al_load_bitmap("Imgs/Separacao.png");

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
					gameOver = 1;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, SaidaEsquerda)) //&& progresso->Salas[1]
				{
					progresso->proximaSala = 13;
					gameOver = 1;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, SaidaDireita))
				{
					progresso->proximaSala = 15;
					gameOver = 1;
				}
				else if (evento.mouse.x >= 0 && evento.mouse.x <= progresso->Itens[0]->largura && evento.mouse.y >=0 && evento.mouse.y <= ((0 * ALTURA_TELA / 10) + progresso->Itens[0]->altura * 0.5) && !progresso->inventClick[0])
				{
					//i* ALTURA_TELA / 10 
					progresso->inventClick[0] = 1;
				}
				else if (evento.mouse.x >= 0 && evento.mouse.x <= progresso->Itens[1]->largura && evento.mouse.y >= ((0 * ALTURA_TELA / 10) + progresso->Itens[0]->altura * 0.5) && evento.mouse.y <= ((1 * ALTURA_TELA / 10) + progresso->Itens[1]->altura * 0.5) && !progresso->inventClick[1])
				{
					//i* ALTURA_TELA / 10 
					progresso->inventClick[1] = 1;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, progresso->Itens[0]) && !Arrastando) {
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
				else if (IsInside(evento.mouse.x, evento.mouse.y, progresso->btnMiniMapa))
				{
					aberto = !aberto;
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
				
				default: Arrastando = 0;
					break;
				}
			}
			/*else if (state.buttons & 2)
			{
				printf("x: %d - y: %d\n",evento.mouse.x,evento.mouse.y);
			}*/

			if (IsInsideImagem(progresso->Itens[0], fundoA) && IsInsideImagem(progresso->Itens[1], fundoB))
			{
				printf("OK");
			}

		}

		al_draw_bitmap(Background, 0, 0, 0);
		al_draw_bitmap(mural, (LARGURA_TELA/2) - 400, 0, 0);

		al_draw_bitmap(SaidaEsquerda->bitmap, SaidaEsquerda->x, SaidaEsquerda->y, 0);
		al_draw_bitmap(SaidaCima->bitmap, SaidaCima->x, SaidaCima->y, 0);
		al_draw_bitmap(SaidaDireita->bitmap, SaidaDireita->x, SaidaDireita->y, 0);

		al_draw_bitmap(PostIt->bitmap, PostIt->x, PostIt->y, 0);

		if(progresso->inventClick[0])
			al_draw_bitmap(progresso->Itens[0]->bitmap, progresso->Itens[0]->x, progresso->Itens[0]->y, 0);

		if (progresso->inventClick[1])
			al_draw_bitmap(progresso->Itens[1]->bitmap, progresso->Itens[1]->x, progresso->Itens[1]->y, 0);

		abrirMapa(progresso);
		caregaInventario(progresso);
		al_flip_display();
	}

	//Desalocação das coisas
	al_destroy_bitmap(SaidaCima->bitmap);
	al_destroy_bitmap(SaidaEsquerda->bitmap);
	al_destroy_bitmap(SaidaDireita->bitmap);
	al_destroy_bitmap(PostIt->bitmap);

	al_destroy_bitmap(Background);
	al_destroy_bitmap(mural);
	//al_destroy_bitmap(item->bitmap);

	free(SaidaCima);
	free(SaidaEsquerda);
	free(SaidaDireita);
	free(PostIt);
	free(fundoA);
	free(fundoB);
	free(fundoC);
	free(fundoD);
	
	//free(item);

	return 0;
}