#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_native_dialog.h>

#include "Struct.h"
#include "Funcoes.h"

//Posições corretas
/*
Na -> (201,208)
Ba -> (250,373)
Co -> (591,262)
C -> (835,150)
N -> (882,150)
Se -> (930,261)
*/

int JogarTabelaPeri(ALLEGRO_DISPLAY *janela, ALLEGRO_EVENT_QUEUE * fila_eventos, Progresso * progresso)
{
	Objeto* SaidaBaixo = NULL, * SaidaEsquerda = NULL, * Ba = NULL, * Co = NULL, * N = NULL, * Se = NULL, * Na = NULL, * C = NULL;
	Objeto* fundoBa = NULL, * fundoCo = NULL, * fundoN = NULL, * fundoSe = NULL, * fundoNa = NULL, * fundoC = NULL;
	int Arrastando = 0;
	
	SaidaBaixo = (Objeto*)malloc(sizeof(Objeto));
	SaidaBaixo->altura = 20;
	SaidaBaixo->largura = 20;
	SaidaBaixo->x = 110 + (LARGURA_TELA / 2) - (SaidaBaixo->largura / 2);
	SaidaBaixo->y = ALTURA_TELA - SaidaBaixo->altura;
	SaidaBaixo->bitmap = NULL;

	SaidaEsquerda = (Objeto*)malloc(sizeof(Objeto));
	SaidaEsquerda->altura = 20;
	SaidaEsquerda->largura = 20;
	SaidaEsquerda->x = 110;
	SaidaEsquerda->y = (ALTURA_TELA/2) - (SaidaBaixo->altura/2);
	SaidaEsquerda->bitmap = NULL;

	Ba = (Objeto*)malloc(sizeof(Objeto));
	Ba->altura = 61;
	Ba->largura = 54;
	Ba->x = 110;
	Ba->y = ALTURA_TELA - Ba->altura;
	Ba->bitmap = NULL;

	Co = (Objeto*)malloc(sizeof(Objeto));
	Co->altura = 61;
	Co->largura = 54;
	Co->x = 165;
	Co->y = ALTURA_TELA - Co->altura;
	Co->bitmap = NULL;

	N = (Objeto*)malloc(sizeof(Objeto));
	N->altura = 61;
	N->largura = 54;
	N->x = 220;
	N->y = ALTURA_TELA - N->altura;
	N->bitmap = NULL;

	Se = (Objeto*)malloc(sizeof(Objeto));
	Se->altura = 61;
	Se->largura = 54;
	Se->x = LARGURA_TELA - Se->largura;
	Se->y = 100;
	Se->bitmap = NULL;

	Na = (Objeto*)malloc(sizeof(Objeto));
	Na->altura = 61;
	Na->largura = 54;
	Na->x = LARGURA_TELA - Na->largura;
	Na->y = 162;
	Na->bitmap = NULL;

	C = (Objeto*)malloc(sizeof(Objeto));
	C->altura = 61;
	C->largura = 54;
	C->x = LARGURA_TELA - C->largura;
	C->y = 224;
	C->bitmap = NULL;

	//////////////////
	fundoBa = (Objeto*)malloc(sizeof(Objeto));
	fundoBa->altura = 61;
	fundoBa->largura = 54;
	fundoBa->x = 250;
	fundoBa->y = 370;
	fundoBa->bitmap = NULL;

	fundoCo = (Objeto*)malloc(sizeof(Objeto));
	fundoCo->altura = 61;
	fundoCo->largura = 54;
	fundoCo->x = 590;
	fundoCo->y = 260;
	fundoCo->bitmap = NULL;

	fundoN = (Objeto*)malloc(sizeof(Objeto));
	fundoN->altura = 61;
	fundoN->largura = 54;
	fundoN->x = 882;
	fundoN->y = 150;
	fundoN->bitmap = NULL;

	fundoSe = (Objeto*)malloc(sizeof(Objeto));
	fundoSe->altura = 61;
	fundoSe->largura = 54;
	fundoSe->x = 930;
	fundoSe->y = 260;
	fundoSe->bitmap = NULL;

	fundoNa = (Objeto*)malloc(sizeof(Objeto));
	fundoNa->altura = 61;
	fundoNa->largura = 54;
	fundoNa->x = 201;
	fundoNa->y = 205;
	fundoNa->bitmap = NULL;

	fundoC = (Objeto*)malloc(sizeof(Objeto));
	fundoC->altura = 61;
	fundoC->largura = 54;
	fundoC->x = 835;
	fundoC->y = 150;
	fundoC->bitmap = NULL;
	///////////////////

	SaidaBaixo->bitmap = al_load_bitmap("Imgs/baixo.png");
	SaidaEsquerda->bitmap = al_load_bitmap("Imgs/Esquerda.png");

	Ba->bitmap = al_load_bitmap("Imgs/Ba.png");
	Co->bitmap = al_load_bitmap("Imgs/Co.png");
	N->bitmap = al_load_bitmap("Imgs/N.png");
	Se->bitmap = al_load_bitmap("Imgs/Se.png");
	Na->bitmap = al_load_bitmap("Imgs/Na.png");
	C->bitmap = al_load_bitmap("Imgs/C.png");

	fundoBa->bitmap = al_load_bitmap("Imgs/Ba.png");
	fundoCo->bitmap = al_load_bitmap("Imgs/Ba.png");
	fundoN->bitmap = al_load_bitmap("Imgs/Ba.png");
	fundoSe->bitmap = al_load_bitmap("Imgs/Ba.png");
	fundoNa->bitmap = al_load_bitmap("Imgs/Ba.png");
	fundoC->bitmap = al_load_bitmap("Imgs/Ba.png");

	ALLEGRO_BITMAP* Background = al_load_bitmap("Imgs/fundo.png");
	ALLEGRO_BITMAP* Tabela = al_load_bitmap("Imgs/tab2.png");

	if (!SaidaBaixo->bitmap || !SaidaEsquerda->bitmap || !Background || ! Tabela || !Ba->bitmap || !Co->bitmap || !N->bitmap || !Se->bitmap || !Na->bitmap || !C->bitmap)
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
				if (IsInside(evento.mouse.x, evento.mouse.y, SaidaBaixo))
				{
					//progresso->proximaSala = 1;
					//return;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, SaidaEsquerda))
				{
					//progresso->proximaSala = 1;
					//return;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, Ba) && !Arrastando) {
					Arrastando = 1;
					Ba->cliqueX = MapearDistancia(evento.mouse.x, Ba->x);
					Ba->cliqueY = MapearDistancia(evento.mouse.y, Ba->y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, Co) && !Arrastando) {
					Arrastando = 2;
					Co->cliqueX = MapearDistancia(evento.mouse.x, Co->x);
					Co->cliqueY = MapearDistancia(evento.mouse.y, Co->y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, N) && !Arrastando) {
					Arrastando = 3;
					N->cliqueX = MapearDistancia(evento.mouse.x, N->x);
					N->cliqueY = MapearDistancia(evento.mouse.y, N->y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, Se) && !Arrastando) {
					Arrastando = 4;
					Se->cliqueX = MapearDistancia(evento.mouse.x, Se->x);
					Se->cliqueY = MapearDistancia(evento.mouse.y, Se->y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, Na) && !Arrastando) {
					Arrastando = 5;
					Na->cliqueX = MapearDistancia(evento.mouse.x, Na->x);
					Na->cliqueY = MapearDistancia(evento.mouse.y, Na->y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, C) && !Arrastando) {
					Arrastando = 6;
					C->cliqueX = MapearDistancia(evento.mouse.x, C->x);
					C->cliqueY = MapearDistancia(evento.mouse.y, C->y);
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
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, Ba)) {
						Ba->x = evento.mouse.x - Ba->cliqueX;
						Ba->y = evento.mouse.y - Ba->cliqueY;
					}
					break;
				case 2: 
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, Co)) {
						Co->x = evento.mouse.x - Co->cliqueX;
						Co->y = evento.mouse.y - Co->cliqueY;
					}
					break;
				case 3:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, N)) {
						N->x = evento.mouse.x - N->cliqueX;
						N->y = evento.mouse.y - N->cliqueY;
					}
					break;
				case 4:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, Se)) {
						Se->x = evento.mouse.x - Se->cliqueX;
						Se->y = evento.mouse.y - Se->cliqueY;
					}
					break;
				case 5:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, Na)) {
						Na->x = evento.mouse.x - Na->cliqueX;
						Na->y = evento.mouse.y - Na->cliqueY;
					}
					break;
				case 6: 
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, C)) {
						C->x = evento.mouse.x - C->cliqueX;
						C->y = evento.mouse.y - C->cliqueY;
					}
					break;

				default: Arrastando = 0;
					break;
				}
			}
		}

		al_draw_bitmap(Background, 0, 0, 0);
		al_draw_bitmap(Tabela, (LARGURA_TELA / 2) - ( 887/ 2), 90, 0);


		al_draw_bitmap(SaidaBaixo->bitmap, SaidaBaixo->x, SaidaBaixo->y, 0);
		al_draw_bitmap(SaidaEsquerda->bitmap, SaidaEsquerda->x, SaidaEsquerda->y, 0);

		al_draw_bitmap(fundoBa->bitmap, fundoBa->x, fundoBa->y, 0);
		al_draw_bitmap(fundoCo->bitmap, fundoCo->x, fundoCo->y, 0);
		al_draw_bitmap(fundoN->bitmap, fundoN->x, fundoN->y, 0);
		al_draw_bitmap(fundoSe->bitmap, fundoSe->x, fundoSe->y, 0);
		al_draw_bitmap(fundoNa->bitmap, fundoNa->x, fundoNa->y, 0);
		al_draw_bitmap(fundoC->bitmap, fundoC->x, fundoC->y, 0);

		al_draw_bitmap(Ba->bitmap, Ba->x, Ba->y, 0);
		al_draw_bitmap(Co->bitmap, Co->x, Co->y, 0);
		al_draw_bitmap(N->bitmap, N->x, N->y, 0);
		al_draw_bitmap(Se->bitmap, Se->x, Se->y, 0);
		al_draw_bitmap(Na->bitmap, Na->x, Na->y, 0);
		al_draw_bitmap(C->bitmap, C->x, C->y, 0);
		
		//caregaInventario(progresso);
		al_flip_display();
	}

	//Desalocação das coisas
	al_destroy_bitmap(SaidaBaixo->bitmap);
	al_destroy_bitmap(SaidaEsquerda->bitmap);

	al_destroy_bitmap(Background);
	al_destroy_bitmap(Tabela);

	al_destroy_bitmap(Ba->bitmap);
	al_destroy_bitmap(Co->bitmap);
	al_destroy_bitmap(N->bitmap);
	al_destroy_bitmap(Se->bitmap);
	al_destroy_bitmap(Na->bitmap);
	al_destroy_bitmap(C->bitmap);

	al_destroy_bitmap(fundoBa->bitmap);
	al_destroy_bitmap(fundoCo->bitmap);
	al_destroy_bitmap(fundoN->bitmap);
	al_destroy_bitmap(fundoSe->bitmap);
	al_destroy_bitmap(fundoNa->bitmap);
	al_destroy_bitmap(fundoC->bitmap);

	free(SaidaBaixo);
	free(SaidaEsquerda);
	free(Ba);
	free(Co);
	free(N);
	free(Se);
	free(Na);
	free(C);
	
	free(fundoBa);
	free(fundoCo);
	free(fundoN);
	free(fundoSe);
	free(fundoNa);
	free(fundoC);

	return 0;
}