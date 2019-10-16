
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

#define PI 3.14159265

Objeto* saidaDireita, * saidaBaixo, * saidaCima;
Objeto* arco, *barraV, *barraH, *marcaV, *marcaH, *btn, *bala;
Objeto* alvo1, * alvo2, * alvo3;

int JogarFaseTeste(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* prog) {

	arco = (Objeto*)malloc(sizeof(Objeto));
	arco->bitmap = NULL;
	arco->x = 160;
	arco->y = ALTURA_TELA - 150;
	arco->largura = 100;
	arco->altura = 100;

	bala = (Objeto*)malloc(sizeof(Objeto));
	bala->bitmap = NULL;
	bala->x = 0;
	bala->y = 0;
	bala->largura = 20;
	bala->altura = 20;

	alvo1 = (Objeto*)malloc(sizeof(Objeto));
	alvo1->bitmap = NULL;
	alvo1->x = 600;
	alvo1->y = 200;
	alvo1->largura = 50;
	alvo1->altura = 50;

	alvo2 = (Objeto*)malloc(sizeof(Objeto));
	alvo2->bitmap = NULL;
	alvo2->x = 600;
	alvo2->y = 400;
	alvo2->largura = 50;
	alvo2->altura = 50;

	alvo3 = (Objeto*)malloc(sizeof(Objeto));
	alvo3->bitmap = NULL;
	alvo3->x = 600;
	alvo3->y = 600;
	alvo3->largura = 50;
	alvo3->altura = 50;

	btn = (Objeto*)malloc(sizeof(Objeto));
	btn->bitmap = NULL;
	btn->x = 160;
	btn->y = ALTURA_TELA - 190;
	btn->largura = 100;
	btn->altura = 30;

	barraH = (Objeto*)malloc(sizeof(Objeto));
	barraH->bitmap = NULL;
	barraH->x = arco->x;
	barraH->y = arco->y + arco->altura + 20;
	barraH->largura = 100;
	barraH->altura = 10;

	barraV = (Objeto*)malloc(sizeof(Objeto));
	barraV->bitmap = NULL;
	barraV->x = arco->x - 30;
	barraV->y = arco->y;
	barraV->largura = 10;
	barraV->altura = 100;

	marcaH = (Objeto*)malloc(sizeof(Objeto));
	marcaH->bitmap = NULL;
	marcaH->x = barraH->x;
	marcaH->y = barraH->y - 10;
	marcaH->largura = 10;
	marcaH->altura = 30;

	marcaV = (Objeto*)malloc(sizeof(Objeto));
	marcaV->bitmap = NULL;
	marcaV->x = barraV->x - 10;
	marcaV->y = barraV->y + barraV->altura/2 - 5;
	marcaV->largura = 30;
	marcaV->altura = 10;

	saidaDireita = (Objeto*)malloc(sizeof(Objeto));
	saidaDireita->bitmap = NULL;
	saidaDireita->x = LARGURA_TELA - 20;
	saidaDireita->y = ALTURA_TELA / 2 - 10;
	saidaDireita->largura = 20;
	saidaDireita->altura = 20;

	saidaCima = (Objeto*)malloc(sizeof(Objeto));
	saidaCima->bitmap = NULL;
	saidaCima->x = LARGURA_TELA / 2 - 10;
	saidaCima->y = 0;
	saidaCima->largura = 20;
	saidaCima->altura = 20;

	saidaBaixo = (Objeto*)malloc(sizeof(Objeto));
	saidaBaixo->bitmap = NULL;
	saidaBaixo->x = LARGURA_TELA / 2 - 10;
	saidaBaixo->y = ALTURA_TELA - 20;
	saidaBaixo->largura = 20;
	saidaBaixo->altura = 20;

	ALLEGRO_BITMAP* Background = al_load_bitmap("Imgs/fundo.png");

	saidaBaixo->bitmap = al_load_bitmap("Imgs/baixo.png");
	saidaCima->bitmap = al_load_bitmap("Imgs/cima.png");
	saidaDireita->bitmap = al_load_bitmap("Imgs/direita.png");

	barraH->bitmap = al_load_bitmap("Imgs/barraH.png");
	barraV->bitmap = al_load_bitmap("Imgs/barraV.png");

	marcaH->bitmap = al_load_bitmap("Imgs/marcaH.png");
	marcaV->bitmap = al_load_bitmap("Imgs/marcaV.png");

	btn->bitmap = al_load_bitmap("Imgs/btn.png");
	arco->bitmap = al_load_bitmap("Imgs/arco.png");
	bala->bitmap = al_load_bitmap("Imgs/x.png");
	alvo1->bitmap = al_load_bitmap("Imgs/alvo.png");
	alvo2->bitmap = al_load_bitmap("Imgs/alvo.png");
	alvo3->bitmap = al_load_bitmap("Imgs/alvo.png");

	int gameOver = 0;
	int arrastando = 0;
	int angulo = 0;
	int velocidade = 0;
	int contador = 0;
	int acertos[] = { 0, 0, 0};

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
				if (IsInside(evento.mouse.x, evento.mouse.y, saidaBaixo))
				{
					prog->proximaSala = 1;////////////////////////////////
					gameOver = 1;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, saidaCima))
				{
					prog->proximaSala = 0;////////////////////////////////
					gameOver = 1;
					
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, saidaDireita))
				{
					prog->proximaSala = 1;////////////////////////////////
					gameOver = 1;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, btn)) {
					angulo = 90 + (barraV->y - marcaV->y);
					velocidade = (marcaH->x - barraH->x)/3;
					contador = 1;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, marcaH))
				{
					arrastando = 1;
					marcaH->cliqueX = MapearDistancia(evento.mouse.x, marcaH->x);
					marcaH->cliqueY = MapearDistancia(evento.mouse.y, marcaH->y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, marcaV))
				{
					arrastando = 2;
					marcaV->cliqueX = MapearDistancia(evento.mouse.x, marcaV->x);
					marcaV->cliqueY = MapearDistancia(evento.mouse.y, marcaV->y);
				}
				else {
					arrastando = 0;
				}
			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				arrastando = 0;
			}

			ALLEGRO_MOUSE_STATE state;

			al_get_mouse_state(&state);
			if (state.buttons & 1 && arrastando)
			{
				switch (arrastando)
				{
				case 1:
					if (evento.mouse.x - marcaH->cliqueX <= barraH->x) {
						//Passou pra esquerda
						marcaH->x = barraH->x;
					}
					else if(evento.mouse.x - marcaH->cliqueX + marcaH->largura >= barraH->x + barraH->largura)
					{
						//Passou pra direita
						marcaH->x = barraH->x + barraH->largura - marcaH->largura;
					}
					else {
						marcaH->x = evento.mouse.x - marcaH->cliqueX;
					}
					break;
				case 2:
					if (evento.mouse.y - marcaV->cliqueY <= barraV->y) {
						//Passou pra esquerda
						marcaV->y = barraV->y;
					}
					else if (evento.mouse.y - marcaV->cliqueY + marcaV->altura >= barraV->y + barraV->altura)
					{
						//Passou pra direita
						marcaV->y = barraV->y + barraV->altura - marcaV->altura;
					}
					else {
						marcaV->y = evento.mouse.y - marcaV->cliqueY;
					}
					break;
				default:
					break;
				}
			}
		}

		al_draw_bitmap(Background, 0, 0, 0);

		contador = CalcularTiro(angulo, velocidade, contador, acertos);
		
		al_draw_bitmap(saidaBaixo->bitmap, saidaBaixo->x, saidaBaixo->y, 0);
		al_draw_bitmap(saidaCima->bitmap, saidaCima->x, saidaCima->y, 0);
		al_draw_bitmap(saidaDireita->bitmap, saidaDireita->x, saidaDireita->y, 0);

		al_draw_bitmap(barraH->bitmap, barraH->x, barraH->y, 0);
		al_draw_bitmap(barraV->bitmap, barraV->x, barraV->y, 0);

		al_draw_bitmap(marcaH->bitmap, marcaH->x, marcaH->y, 0);
		al_draw_bitmap(marcaV->bitmap, marcaV->x, marcaV->y, 0);

		al_draw_bitmap(btn->bitmap, btn->x, btn->y, 0);

		al_draw_bitmap(arco->bitmap, arco->x, arco->y, 0);

		if(!acertos[0])
			al_draw_bitmap(alvo1->bitmap, alvo1->x, alvo1->y, 0);
		if(!acertos[1])
			al_draw_bitmap(alvo2->bitmap, alvo2->x, alvo2->y, 0);
		if(!acertos[2])
			al_draw_bitmap(alvo3->bitmap, alvo3->x, alvo3->y, 0);


		al_flip_display();
	}
	al_destroy_bitmap(Background);

	al_destroy_bitmap(saidaBaixo->bitmap);
	al_destroy_bitmap(saidaCima->bitmap);
	al_destroy_bitmap(saidaDireita->bitmap);
	free(saidaBaixo);
	free(saidaCima);
	free(saidaDireita);

	return;
}

int CalcularTiro(int angulo, int velocidade, int cont, int *acertos) {	
	if (!velocidade == 0)
	{
		float VelVertical = sin(angulo * PI / 180) * velocidade;
		VelVertical *= -1;
		float VelHorizontal = cos(angulo * PI / 180) * velocidade;
		int t;
		int posX = arco->x + arco->largura;
		int posY = arco->y;

		for (t = 0; t <= cont; t++)
		{
			posX += VelHorizontal;
			posY += VelVertical;
			VelVertical += 0.5;

			
			if (IsInside(posX, posY, alvo1) && !acertos[0])
				acertos[0] = 1;
			if (IsInside(posX, posY, alvo2) && !acertos[1])
				acertos[1] = 1;
			if (IsInside(posX, posY, alvo3) && !acertos[2])
				acertos[2] = 1;
			
			
			al_draw_bitmap(bala->bitmap, posX, posY, 0);
		}
	}

	return cont += 1;
}
