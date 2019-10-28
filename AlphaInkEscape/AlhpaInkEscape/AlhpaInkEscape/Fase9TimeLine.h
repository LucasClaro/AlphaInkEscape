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
Objeto* eventos;

int JogarFaseTimeLine(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* prog) {
	int i,j;

	linha1 = (Objeto*)malloc(sizeof(Objeto));
	linha1->bitmap = NULL;
	linha1->x = LARGURA_TELA/2 - 500;
	linha1->y = 500;
	linha1->largura = 1000;
	linha1->altura = 100;

	eventos = (Objeto*)malloc(sizeof(Objeto)*6);

	for (i = 0; i < 6; i++) {//Percorre do 1º ao 6º elemento de uma linha do tempo
		for (j = 0; j < 4; j++) {//Percorre as 4 linhas do tempo
			//printf("(%d,%d)", i, j);
			eventos[i + 6 * j].bitmap = NULL;
			eventos[i + 6 * j].x = linha1->x + 60*(i/2);//Divide os 6 elementos da linha do tempo em 3 colunas
			eventos[i + 6 * j].y = 100 + 60 * (i / 3);//Divide os 6 elementos da linha do tempo em 2 linhas
			eventos[i + 6 * j].largura = 50;
			eventos[i + 6 * j].altura = 50;
		}		
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
				
			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				
			}			
		}

		al_draw_bitmap(Background, 0, 0, 0);


		//al_draw_bitmap(saidaBaixo->bitmap, saidaBaixo->x, saidaBaixo->y, 0);
		//al_draw_bitmap(saidaCima->bitmap, saidaCima->x, saidaCima->y, 0);
		//al_draw_bitmap(saidaDireita->bitmap, saidaDireita->x, saidaDireita->y, 0);

		
		al_draw_bitmap(linha1->bitmap, linha1->x, linha1->y, 0);
		for (i = 0; i < 6/*----*/; i++) {
			al_draw_bitmap(eventos[i].bitmap, eventos[i].x, eventos[i].y, 0);
		}

		caregaInventario(prog);
		al_flip_display();
	}
}