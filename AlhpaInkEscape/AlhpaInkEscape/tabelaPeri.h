#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_native_dialog.h>

#include "Struct.h"
#include "Funcoes.h"

int JogarTabelaPeri(ALLEGRO_DISPLAY *janela, ALLEGRO_EVENT_QUEUE * fila_eventos, Progresso * progresso)
{
	Objeto* SaidaBaixo = NULL, * SaidaEsquerda = NULL, * Ba = NULL, * Co = NULL, * N = NULL, * Se = NULL, * Na = NULL, * C = NULL;
	int Arrastando = 0;
	
	SaidaBaixo = (Objeto*)malloc(sizeof(Objeto));
	SaidaBaixo->altura = 100;
	SaidaBaixo->largura = 100;
	SaidaBaixo->x = 110 + (LARGURA_TELA / 2) - (SaidaBaixo->largura / 2);
	SaidaBaixo->y = ALTURA_TELA - SaidaBaixo->altura;
	SaidaBaixo->bitmap = NULL;

	SaidaEsquerda = (Objeto*)malloc(sizeof(Objeto));
	SaidaEsquerda->altura = 100;
	SaidaEsquerda->largura = 100;
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
	Se->x = 280;
	Se->y = ALTURA_TELA - Se->altura;
	Se->bitmap = NULL;

	Na = (Objeto*)malloc(sizeof(Objeto));
	Na->altura = 61;
	Na->largura = 54;
	Na->x = 335;
	Na->y = ALTURA_TELA - Na->altura;
	Na->bitmap = NULL;

	C = (Objeto*)malloc(sizeof(Objeto));
	C->altura = 61;
	C->largura = 54;
	C->x = 390;
	C->y = ALTURA_TELA - C->altura;
	C->bitmap = NULL;

	SaidaBaixo->bitmap = al_load_bitmap("Imgs/baixo.png");
	SaidaEsquerda->bitmap = al_load_bitmap("Imgs/Esquerda.png");

	Ba->bitmap = al_load_bitmap("Imgs/Ba.png");
	Co->bitmap = al_load_bitmap("Imgs/Co.png");
	N->bitmap = al_load_bitmap("Imgs/N.png");
	Se->bitmap = al_load_bitmap("Imgs/Se.png");
	Na->bitmap = al_load_bitmap("Imgs/Na.png");
	C->bitmap = al_load_bitmap("Imgs/C.png");

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
				else if (IsInside(evento.mouse.x, evento.mouse.y, Ba && !Arrastando) ) {
					Arrastando = 1;
					Ba->cliqueX = MapearDistancia(evento.mouse.x, Ba->x);
					Ba->cliqueY = MapearDistancia(evento.mouse.y, Ba->y);
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
				/* Primary (e.g. left) mouse button is held. */
				if (!VerificarBordas(evento.mouse.x, evento.mouse.y, Ba)) {
					Ba->x = evento.mouse.x - Ba->cliqueX;
					Ba->y = evento.mouse.y - Ba->cliqueY;
				}
			}
		}

		al_draw_bitmap(Background, 0, 0, 0);
		al_draw_bitmap(Tabela, 115, 0, 0);


		al_draw_bitmap(SaidaBaixo->bitmap, SaidaBaixo->x, SaidaBaixo->y, 0);
		al_draw_bitmap(SaidaEsquerda->bitmap, SaidaEsquerda->x, SaidaEsquerda->y, 0);

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

	free(SaidaBaixo);
	free(SaidaEsquerda);
	free(Ba);
	free(Co);
	free(N);
	free(Se);
	free(Na);
	free(C);

	return 0;
}