#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_native_dialog.h>

#include "Struct.h"
#include "Funcoes.h"

int JogarFase11xadrez(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* progresso)
{

	Objeto* SaidaCima = NULL, * SaidaEsquerda = NULL, * SaidaBaixo = NULL;
	Objeto* fundoA = NULL, * fundoB = NULL, * fundoC = NULL, * fundoD = NULL;
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

	SaidaBaixo = (Objeto*)malloc(sizeof(Objeto));
	SaidaBaixo->largura = 20;
	SaidaBaixo->altura = 20;
	SaidaBaixo->x = 110 + (LARGURA_TELA / 2) - (SaidaBaixo->largura / 2);
	SaidaBaixo->y = ALTURA_TELA - SaidaBaixo->altura;
	SaidaBaixo->bitmap = NULL;

	SaidaCima->bitmap = al_load_bitmap("Imgs/cima.png");
	SaidaEsquerda->bitmap = al_load_bitmap("Imgs/Esquerda.png");
	SaidaBaixo->bitmap = al_load_bitmap("Imgs/baixo.png");

	Background = al_load_bitmap("Imgs/fundo.png");

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

			/*ALLEGRO_MOUSE_STATE state;
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

		al_draw_bitmap(SaidaEsquerda->bitmap, SaidaEsquerda->x, SaidaEsquerda->y, 0);
		al_draw_bitmap(SaidaCima->bitmap, SaidaCima->x, SaidaCima->y, 0);
		al_draw_bitmap(SaidaBaixo->bitmap, SaidaBaixo->x, SaidaBaixo->y, 0);

		caregaInventario(progresso);
		al_flip_display();
	}

	//Desalocação das coisas
	al_destroy_bitmap(SaidaCima->bitmap);
	al_destroy_bitmap(SaidaEsquerda->bitmap);
	al_destroy_bitmap(SaidaBaixo->bitmap);

	al_destroy_bitmap(Background);
	//al_destroy_bitmap(item->bitmap);

	free(SaidaCima);
	free(SaidaEsquerda);
	free(SaidaBaixo);

	//free(item);

	return 0;
}