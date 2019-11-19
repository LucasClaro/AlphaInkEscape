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


Objeto* arco, * barraV, * barraH, * marcaV, * marcaH, * bala;
Objeto* alvo1, * alvo2, * alvo3, * alvo4, * alvo5;

int JogarFase10Arco(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* prog) {

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
	alvo1->x = 550;
	alvo1->y = 100;
	alvo1->largura = 50;
	alvo1->altura = 50;

	alvo2 = (Objeto*)malloc(sizeof(Objeto));
	alvo2->bitmap = NULL;
	alvo2->x = 650;
	alvo2->y = 300;
	alvo2->largura = 50;
	alvo2->altura = 50;

	alvo3 = (Objeto*)malloc(sizeof(Objeto));
	alvo3->bitmap = NULL;
	alvo3->x = 600;
	alvo3->y = 500;
	alvo3->largura = 50;
	alvo3->altura = 50;

	alvo4 = (Objeto*)malloc(sizeof(Objeto));
	alvo4->bitmap = NULL;
	alvo4->x = 900;
	alvo4->y = 450;
	alvo4->largura = 50;
	alvo4->altura = 50;

	alvo5 = (Objeto*)malloc(sizeof(Objeto));
	alvo5->bitmap = NULL;
	alvo5->x = 950;
	alvo5->y = 150;
	alvo5->largura = 50;
	alvo5->altura = 50;

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
	marcaH->x = barraH->x + barraH->largura - 10;
	marcaH->y = barraH->y - 10;
	marcaH->largura = 10;
	marcaH->altura = 30;

	marcaV = (Objeto*)malloc(sizeof(Objeto));
	marcaV->bitmap = NULL;
	marcaV->x = barraV->x - 10;
	marcaV->y = barraV->y + barraV->altura / 2 - 5;
	marcaV->largura = 30;
	marcaV->altura = 10;

	Objeto* saidaEsquerda;
	saidaEsquerda = (Objeto*)malloc(sizeof(Objeto));
	saidaEsquerda->bitmap = prog->cenario->cadeado;
	saidaEsquerda->x = 110;
	saidaEsquerda->y = ALTURA_TELA / 2 - 10;
	saidaEsquerda->largura = 20;
	saidaEsquerda->altura = 20;

	Objeto* saidaCima;
	saidaCima = (Objeto*)malloc(sizeof(Objeto));
	saidaCima->bitmap = prog->cenario->setaCima;
	saidaCima->x = 110 + LARGURA_TELA / 2 - 10;
	saidaCima->y = 0;
	saidaCima->largura = 20;
	saidaCima->altura = 20;

	Objeto* saidaBaixo;
	saidaBaixo = (Objeto*)malloc(sizeof(Objeto));
	saidaBaixo->bitmap = prog->cenario->cadeado;
	saidaBaixo->x = 110 + LARGURA_TELA / 2 - 10;
	saidaBaixo->y = ALTURA_TELA - 20;
	saidaBaixo->largura = 20;
	saidaBaixo->altura = 20;

	barraH->bitmap = al_load_bitmap("Imgs/Arco/barraH.png");
	barraV->bitmap = al_load_bitmap("Imgs/Arco/barraV.png");

	marcaH->bitmap = al_load_bitmap("Imgs/Arco/marcaH.png");
	marcaV->bitmap = al_load_bitmap("Imgs/Arco/marcaV.png");

	arco->bitmap = al_load_bitmap("Imgs/Arco/arco.png");
	bala->bitmap = al_load_bitmap("Imgs/Arco/x.png");
	alvo1->bitmap = al_load_bitmap("Imgs/Arco/alvo.png");
	alvo2->bitmap = al_load_bitmap("Imgs/Arco/alvo.png");
	alvo3->bitmap = al_load_bitmap("Imgs/Arco/alvo.png");
	alvo4->bitmap = al_load_bitmap("Imgs/Arco/alvo.png");
	alvo5->bitmap = al_load_bitmap("Imgs/Arco/alvo.png");

	int gameOver = 0;
	int arrastando = 0;
	int angulo = 0;
	int anguloArco = 45;
	int velocidade = 0;
	int contador = 0;
	int acertos[] = { 0, 0, 0, 0, 0 };

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
				if (IsInside(evento.mouse.x, evento.mouse.y, saidaBaixo) && prog->Salas[10])
				{
					prog->proximaSala = 14;////////////////////////////////
					al_play_sample(prog->cenario->somSeta, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					gameOver = 1;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, prog->cenario->btnSom)) {
					tocando = !tocando;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, saidaCima))
				{
					prog->proximaSala = 6;////////////////////////////////
					al_play_sample(prog->cenario->somSeta, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					gameOver = 1;

				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, saidaEsquerda) && prog->Salas[10])
				{
					prog->proximaSala = 9;////////////////////////////////
					al_play_sample(prog->cenario->somSeta, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					gameOver = 1;
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
				else if (IsInside(evento.mouse.x, evento.mouse.y, barraV))//Deixa o user clicar na barra pra mover a marca
				{					
					marcaV->y = evento.mouse.y - marcaV->altura / 2;					
					if (evento.mouse.y - marcaV->altura / 2 < barraV->y)
						marcaV->y = barraV->y;
					else if (evento.mouse.y - marcaV->altura / 2 > barraV->y + barraV->altura - marcaV->altura)
						marcaV->y = barraV->y + barraV->altura - marcaV->altura;
					arrastando = 2;
					marcaV->cliqueX = MapearDistancia(evento.mouse.x, marcaV->x);
					marcaV->cliqueY = MapearDistancia(evento.mouse.y, marcaV->y);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, barraH))//Deixa o user clicar na barra pra mover a marca
				{					
					marcaH->x = evento.mouse.x - marcaH->largura / 2;					
					if (evento.mouse.x - marcaH->largura / 2 < barraH->x)
						marcaH->x = barraH->x;
					else if (evento.mouse.x - marcaH->largura / 2 > barraH->x + barraH->largura - marcaH->largura)
						marcaH->x = barraH->x + barraH->largura - marcaH->largura;
					
					arrastando = 1;
					marcaH->cliqueX = MapearDistancia(evento.mouse.x, marcaH->x);
					marcaH->cliqueY = MapearDistancia(evento.mouse.y, marcaH->y);
				}
				else {
					arrastando = 0;
				}
			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				anguloArco = 90 + (barraV->y - marcaV->y);
				if (arrastando == 1) {					
					angulo = 90 + (barraV->y - marcaV->y);
					velocidade = 30 + (barraH->x - marcaH->x) / 3;
					contador = 1;
				}
				marcaH->x = barraH->x + barraH->largura - 10;

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
					else if (evento.mouse.x - marcaH->cliqueX + marcaH->largura >= barraH->x + barraH->largura)
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

		al_draw_bitmap(prog->cenario->background, 0, 0, 0);

		contador = CalcularTiro(angulo, velocidade, contador, acertos);

		if (acertos[0] && acertos[1] && acertos[2])
		{
			prog->Salas[10] = 1;
		}
		if (prog->Salas[10]){
			saidaBaixo->bitmap = prog->cenario->setaBaixo;
			saidaEsquerda->bitmap = prog->cenario->setaEsquerda;
		}

		al_draw_bitmap(saidaBaixo->bitmap, saidaBaixo->x, saidaBaixo->y, 0);
		al_draw_bitmap(saidaCima->bitmap, saidaCima->x, saidaCima->y, 0);
		al_draw_bitmap(saidaEsquerda->bitmap, saidaEsquerda->x, saidaEsquerda->y, 0);

		al_draw_bitmap(barraH->bitmap, barraH->x, barraH->y, 0);
		al_draw_bitmap(barraV->bitmap, barraV->x, barraV->y, 0);

		al_draw_bitmap(marcaH->bitmap, marcaH->x, marcaH->y, 0);
		al_draw_bitmap(marcaV->bitmap, marcaV->x, marcaV->y, 0);

		al_draw_rotated_bitmap(arco->bitmap, arco->largura/2, arco->altura/2, arco->x + arco->largura / 2, arco->y + arco->altura / 2, 44.7 - anguloArco * PI / 180, 0);
		//al_draw_bitmap(arco->bitmap,arco->x,arco->y,0);

		if (!acertos[0])
			al_draw_bitmap(alvo1->bitmap, alvo1->x, alvo1->y, 0);
		if (!acertos[1])
			al_draw_bitmap(alvo2->bitmap, alvo2->x, alvo2->y, 0);
		if (!acertos[2])
			al_draw_bitmap(alvo3->bitmap, alvo3->x, alvo3->y, 0);
		if (!acertos[2])
			al_draw_bitmap(alvo3->bitmap, alvo3->x, alvo3->y, 0);
		if (!acertos[3])
			al_draw_bitmap(alvo4->bitmap, alvo4->x, alvo4->y, 0);
		if (!acertos[4])
			al_draw_bitmap(alvo5->bitmap, alvo5->x, alvo5->y, 0);

		som(prog);
		caregaInventario(prog);
		al_flip_display();
	}

	//al_destroy_bitmap(saidaDireita->bitmap);
	//free(saidaBaixo);
	//free(saidaDireita);

	return;
}

int CalcularTiro(int angulo, int velocidade, int cont, int* acertos) {
	if (!velocidade == 0)
	{
		float VelVertical = sin(angulo * PI / 180) * velocidade;
		VelVertical *= -1;
		float VelHorizontal = cos(angulo * PI / 180) * velocidade;
		int t;
		int posX = arco->x + arco->largura/2 - 10;
		int posY = arco->y + arco->altura/2 - 10;

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
			if (IsInside(posX, posY, alvo4) && !acertos[3])
				acertos[3] = 1;
			if (IsInside(posX, posY, alvo5) && !acertos[4])
				acertos[4] = 1;

			al_draw_bitmap(bala->bitmap, posX, posY, 0);
		}
	}

	return cont += 1;
}
