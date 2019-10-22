#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
#include "Funcoes.h"
#include "Struct.h"


int JogarFase0Conta(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* prog) {
	Objeto* SaidaBaixo;
	SaidaBaixo = (Objeto*)malloc(sizeof(Objeto));
	SaidaBaixo->altura = 20;
	SaidaBaixo->largura = 20;
	SaidaBaixo->x = (LARGURA_TELA / 2) - (SaidaBaixo->largura / 2);
	SaidaBaixo->y = ALTURA_TELA - (SaidaBaixo->altura * 2);
	SaidaBaixo->bitmap = al_load_bitmap("Imgs/baixo.png");

	Objeto* SaidaEsquerda;
	SaidaEsquerda = (Objeto*)malloc(sizeof(Objeto));
	SaidaEsquerda->altura = 20;
	SaidaEsquerda->largura = 20;
	SaidaEsquerda->x = 110;
	SaidaEsquerda->y = (ALTURA_TELA / 2) - (SaidaBaixo->altura / 2);
	SaidaEsquerda->bitmap = al_load_bitmap("Imgs/Esquerda.png");
	
	Objeto* SaidaCima;
	SaidaCima = (Objeto*)malloc(sizeof(Objeto));
	SaidaCima->altura = 20;
	SaidaCima->largura = 20;
	SaidaCima->x =(LARGURA_TELA / 2) - (SaidaCima->largura / 2);
	SaidaCima->y = 1;
	SaidaCima->bitmap = al_load_bitmap("Imgs/cima.png");

	Objeto* campo1;
	campo1 = (Objeto*)malloc(sizeof(Objeto));
	campo1->bitmap = al_load_bitmap("Imgs/slide4.png");
	campo1->altura = 250;
	campo1->largura = 500;
	campo1->x = 0;
	campo1->y = ALTURA_TELA - campo1->altura;

	Objeto* campo2;
	campo2 = (Objeto*)malloc(sizeof(Objeto));
	campo2->bitmap = al_load_bitmap("Imgs/slide4.png");
	campo2->altura = 250;
	campo2->largura = 500;
	campo2->x = LARGURA_TELA - campo2->largura;
	campo2->y = ALTURA_TELA - campo2->altura;	
	
	Objeto* bola;
	bola = (Objeto*)malloc(sizeof(Objeto));
	bola->bitmap = al_load_bitmap("Imgs/monca.png");
	bola->altura = 50;
	bola->largura = 50;
	bola->x = (LARGURA_TELA / 2) - (bola->largura / 2);
	bola->y = (ALTURA_TELA / 4) - (bola->altura / 2);

	Objeto* conta;
	conta = (Objeto*)malloc(sizeof(Objeto));
	conta->bitmap = NULL;
	conta->altura = 50;
	conta->largura = 50;
	conta->x = (LARGURA_TELA / 2) - (conta->largura / 2);
	conta->y = (ALTURA_TELA / 2) - (conta->altura / 2);

	ALLEGRO_BITMAP* padrao = al_load_bitmap("Imgs/mjacare.png");
	ALLEGRO_BITMAP* conta1 = al_load_bitmap("Imgs/mmico.png");
	ALLEGRO_BITMAP* conta2 = al_load_bitmap("Imgs/mtatu.png");
	ALLEGRO_BITMAP* background = al_load_bitmap("Imgs/fundo.png");


	conta->bitmap = padrao;

	bool sair = false;

	bool arrastando = false;
	while (!sair)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(fila_eventos, &evento);

		if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (IsInside(evento.mouse.x, evento.mouse.y, bola) && !arrastando) {
				arrastando = true;
				bola->cliqueX = MapearDistancia(evento.mouse.x, bola->x);
				bola->cliqueY = MapearDistancia(evento.mouse.y, bola->y);
			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, SaidaCima))
			{
				prog->proximaSala = 1;
				sair = 1;
			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, SaidaEsquerda))
			{
				prog->proximaSala = 3;
				sair = 1;
			}
			else if(IsInside(evento.mouse.x, evento.mouse.y, SaidaBaixo))
			{
				prog->proximaSala = 2;
				sair = 1;
			}
		}
		else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			arrastando = false;
		}

		ALLEGRO_MOUSE_STATE state;
		al_get_mouse_state(&state);

		if (arrastando && state.buttons & 1)
		{
			if (!VerificarBordas(evento.mouse.x, evento.mouse.y, bola))
			{
				bola->x = evento.mouse.x - bola->cliqueX;
				bola->y = evento.mouse.y - bola->cliqueY;
			}

			if (IsInsideImagem(bola, campo1))
			{
				conta->bitmap = conta1;
			}
			else if (IsInsideImagem(bola, campo2))
			{
				conta->bitmap = conta2;
			}
			else
			{
				conta->bitmap = padrao;
			}
		}

		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			sair = true;
			prog->Gameover = true;
		}


		al_draw_bitmap(background, 0, 0, 0);
		al_draw_bitmap(SaidaCima->bitmap, SaidaCima->x, SaidaCima->y, 0);
		al_draw_bitmap(SaidaEsquerda->bitmap, SaidaEsquerda->x, SaidaEsquerda->y, 0);
		al_draw_bitmap(SaidaBaixo->bitmap, SaidaBaixo->x, SaidaBaixo->y, 0);
		al_draw_bitmap(conta->bitmap, conta->x, conta->y, 0);
		al_draw_bitmap(campo1->bitmap, campo1->x, campo1->y, 0);
		al_draw_bitmap(campo2->bitmap, campo2->x, campo2->y, 0);
		al_draw_bitmap(bola->bitmap, bola->x, bola->y, 0);

		

		al_flip_display();
	}

	al_destroy_bitmap(background);
	al_destroy_bitmap(SaidaCima->bitmap);
	al_destroy_bitmap(SaidaEsquerda->bitmap);
	al_destroy_bitmap(SaidaBaixo->bitmap);
	al_destroy_bitmap(padrao);
	al_destroy_bitmap(conta1);
	al_destroy_bitmap(conta2);
	al_destroy_bitmap(campo1->bitmap);
	al_destroy_bitmap(campo2->bitmap);
	al_destroy_bitmap(bola->bitmap);

	free(SaidaBaixo);
	free(SaidaCima);
	free(SaidaEsquerda);
	free(campo1);
	free(campo2);
	free(bola);
	free(conta);


	//system("pause");

	return 0;
}
