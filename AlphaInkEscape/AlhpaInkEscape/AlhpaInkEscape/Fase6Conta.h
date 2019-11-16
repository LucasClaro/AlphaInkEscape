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
#include <string.h>


int FilaCheia(Fila* f) {
	if (f->total >= f->tamanho) {
		return 1;
	}
	return 0;
}

int FilaVazia(Fila* f) {
	if (f->total <= 0) {
		return 1;
	}
	return 0;
}

void CriarFila(Fila* f) {
	f->tamanho = 10;
	f->inicio = 0;
	f->fim = 0;
	f->total = 0;
}

void EmQueue(Fila* f, int x) {
	if (!FilaCheia(f)) {
		f->vetor[f->fim] = x;
		f->fim++;
		f->total++;
	}
}

int VerificaFila(int *fila, int *resp) {
	if (FilaCheia(fila)) {
		int i;
		for (i = 0; i < 10; i++) {
			printf("%d, %d\n",fila[i],resp[i]);
			if (fila[i] != resp[i])
				return 0;
		}
		return 1;
	}	
}

int DeQueue(Fila* f) {
	int x;
	if (!FilaVazia(f)) {
		x = f->vetor[f->inicio];
		f->inicio++;
		f->total--;
		if (f->fim >= f->tamanho)
			f->fim = 0;
		if (f->inicio >= f->tamanho)
			f->inicio = 0;
		return x;
	}
}
//a
int JogarFase6Conta(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* prog) {
	Objeto* SaidaBaixo;
	SaidaBaixo = (Objeto*)malloc(sizeof(Objeto));
	SaidaBaixo->altura = 20;
	SaidaBaixo->largura = 20;
	SaidaBaixo->x = 110 + (LARGURA_TELA / 2) - (SaidaBaixo->largura / 2);
	SaidaBaixo->y = ALTURA_TELA - (SaidaBaixo->altura * 2);
	SaidaBaixo->bitmap = prog->cenario->cadeado;

	Objeto* SaidaEsquerda;
	SaidaEsquerda = (Objeto*)malloc(sizeof(Objeto));
	SaidaEsquerda->altura = 20;
	SaidaEsquerda->largura = 20;
	SaidaEsquerda->x = 110;
	SaidaEsquerda->y = (ALTURA_TELA / 2) - (SaidaBaixo->altura / 2);
	SaidaEsquerda->bitmap = prog->cenario->cadeado;

	Objeto* SaidaDireita;
	SaidaDireita = (Objeto*)malloc(sizeof(Objeto));
	SaidaDireita->altura = 20;
	SaidaDireita->largura = 20;
	SaidaDireita->x = LARGURA_TELA - SaidaDireita->largura;
	SaidaDireita->y = (ALTURA_TELA / 2) - (SaidaDireita->altura / 2);
	SaidaDireita->bitmap = prog->cenario->cadeado;
	

	Objeto* SaidaCima;
	SaidaCima = (Objeto*)malloc(sizeof(Objeto));
	SaidaCima->altura = 20;
	SaidaCima->largura = 20;
	SaidaCima->x = 110 + (LARGURA_TELA / 2) - (SaidaCima->largura / 2);
	SaidaCima->y = 1;
	SaidaCima->bitmap = prog->cenario->cadeado;

	Objeto* campo1;
	campo1 = (Objeto*)malloc(sizeof(Objeto));
	campo1->bitmap = al_load_bitmap("Imgs/Conta/slide4.png");
	campo1->altura = 150;
	campo1->largura = 300;
	campo1->x = 120;
	campo1->y = ALTURA_TELA - campo1->altura - 5;

	Objeto* campoesquerda;
	campoesquerda = (Objeto*)malloc(sizeof(Objeto));
	campoesquerda->bitmap = NULL;
	campoesquerda->altura = 83;
	campoesquerda->largura = 83;
	campoesquerda->x = 175;
	campoesquerda->y = 350;

	ALLEGRO_BITMAP* btn = al_load_bitmap("Imgs/Conta/botao.png");
	ALLEGRO_BITMAP* btnPressionado = al_load_bitmap("Imgs/Conta/botaopressed.png");

	Objeto* campodireita;
	campodireita = (Objeto*)malloc(sizeof(Objeto));
	campodireita->bitmap = NULL;
	campodireita->altura = 83;
	campodireita->largura = 83;
	campodireita->x = 1100;
	campodireita->y = 350;

	ALLEGRO_BITMAP* btn2 = al_load_bitmap("Imgs/Conta/botao.png");
	ALLEGRO_BITMAP* btnPressionado2 = al_load_bitmap("Imgs/Conta/botaopressed.png");


	Objeto* campo2;
	campo2 = (Objeto*)malloc(sizeof(Objeto));
	campo2->bitmap = al_load_bitmap("Imgs/Conta/slide4.png");
	campo2->altura = 150;
	campo2->largura = 300;
	campo2->x = LARGURA_TELA - campo2->largura - 5;
	campo2->y = ALTURA_TELA - campo2->altura - 5;	
	
	Objeto* bola;
	bola = (Objeto*)malloc(sizeof(Objeto));
	bola->bitmap = al_load_bitmap("Imgs/Conta/cursor.png");
	bola->altura = 50;
	bola->largura = 50;
	bola->x = (LARGURA_TELA / 2) - (bola->largura / 2);
	bola->y = (ALTURA_TELA / 4) - (bola->altura / 2);

	Objeto* conta;
	conta = (Objeto*)malloc(sizeof(Objeto));
	conta->bitmap = NULL;
	conta->altura =  325;
	conta->largura = 650;
	conta->x = (LARGURA_TELA / 2) - (conta->largura / 2) +115;
	conta->y = (ALTURA_TELA / 2) - (conta->altura);

	//ALLEGRO_BITMAP* padrao = al_load_bitmap("");
	ALLEGRO_BITMAP* conta1 = al_load_bitmap("Imgs/Conta/DicaEsquerda.png");
	ALLEGRO_BITMAP* conta2 = al_load_bitmap("Imgs/Conta/DicaDireita.png");
	ALLEGRO_BITMAP* background = prog->cenario->background;
	ALLEGRO_BITMAP* saida = al_load_bitmap("Imgs/Esquerda.png");

	int vetorResposta[10] = { 1,1,2,1,1,2,2,1,2,2 }; //"EEDEEDDEDD";
	

	bool digitado = false;
	bool sair = false;
	bool drawNull = true;
	bool arrastando = false;
	bool pressionado = false;

	campoesquerda->bitmap = btn;
	campodireita->bitmap = btn2;

	int i = 0;

	Fila fila;
	Fila* f = &fila;
	CriarFila(f);
	while (!sair)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(fila_eventos, &evento);
		
		ALLEGRO_MOUSE_STATE state;
		al_get_mouse_state(&state);

		if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (IsInside(evento.mouse.x, evento.mouse.y, bola) && !arrastando) {
				arrastando = true;
			
					bola->cliqueX = MapearDistancia(evento.mouse.x, bola->x);
					bola->cliqueY = MapearDistancia(evento.mouse.y, bola->y);
			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, campoesquerda)) {
				if (!pressionado && state.buttons & 1)
				{
					pressionado = false;
					campoesquerda->bitmap = btnPressionado;
				}

				if (FilaCheia(f)) {
					DeQueue(f);
				}
				EmQueue(f,1);
				if (VerificaFila(f, vetorResposta))
					prog->Salas[6] = 1;
			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, campodireita)) {
				if (!pressionado && state.buttons & 1)
				{
					pressionado = true;
					campodireita->bitmap = btnPressionado2;
				}
				if (FilaCheia(f)) {
					DeQueue(f, vetorResposta);
				}
				EmQueue(f, 2);
				if (VerificaFila(f, vetorResposta)) {
					printf("Acertou!");
					prog->Salas[6] = 1;
				}
			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, prog->cenario->btnSom)) {
				tocando = !tocando;
			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, SaidaCima) && prog->Salas[6])
			{
				prog->proximaSala = 2;
				al_play_sample(prog->cenario->somSeta, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				sair = 1;
			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, SaidaEsquerda) && prog->Salas[6])
			{
				prog->proximaSala = 5;
				al_play_sample(prog->cenario->somSeta, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				sair = 1;
			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, SaidaDireita) && prog->Salas[6])
			{
				prog->proximaSala = 7;
				al_play_sample(prog->cenario->somSeta, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				sair = 1;
			}
			else if(IsInside(evento.mouse.x, evento.mouse.y, SaidaBaixo) && prog->Salas[6])
			{
				prog->proximaSala = 10;
				al_play_sample(prog->cenario->somSeta, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				sair = 1;
			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, prog->cenario->btnMiniMapa))
			{
				aberto = !aberto;
			}
		}
		else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			arrastando = false;
			pressionado = false;
			campoesquerda->bitmap = btn;
			campodireita->bitmap = btn2;


		}

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
				drawNull = false;
			}
			else if (IsInsideImagem(bola, campo2))
			{
				conta->bitmap = conta2;
				drawNull = false;
			}
			else
			{
				drawNull = true;

			}
		}

		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			sair = true;
			prog->Gameover = true;
		}


		if (prog->Salas[6]) {
			SaidaEsquerda->bitmap = prog->cenario->setaEsquerda;
			SaidaDireita->bitmap = prog->cenario->setaDireita;
			SaidaCima->bitmap = prog->cenario->setaCima;
			SaidaBaixo->bitmap = prog->cenario->setaBaixo;
		}

		al_draw_bitmap(background, 0, 0, 0);
		if(prog->Salas[0])
			al_draw_bitmap(SaidaCima->bitmap, SaidaCima->x, SaidaCima->y, 0);
		
		
		al_draw_bitmap(SaidaEsquerda->bitmap, SaidaEsquerda->x, SaidaEsquerda->y, 0);
		al_draw_bitmap(SaidaCima->bitmap, SaidaCima->x, SaidaCima->y, 0);
		al_draw_bitmap(SaidaBaixo->bitmap, SaidaBaixo->x, SaidaBaixo->y, 0);
		al_draw_bitmap(SaidaDireita->bitmap, SaidaDireita->x, SaidaDireita->y, 0);

		if(!drawNull)
			al_draw_bitmap(conta->bitmap, conta->x, conta->y, 0);
		
		
		al_draw_bitmap(campo1->bitmap, campo1->x, campo1->y, 0);
		al_draw_bitmap(campo2->bitmap, campo2->x, campo2->y, 0);
		al_draw_bitmap(campoesquerda->bitmap, campoesquerda->x, campoesquerda->y, 0);
		al_draw_bitmap(campodireita->bitmap, campodireita->x, campodireita->y, 0);
		al_draw_bitmap(bola->bitmap, bola->x, bola->y, 0);

		abrirMapa(prog);
		som(prog);	  	   	
		caregaInventario(prog);
		al_flip_display();
	}


	/*al_destroy_bitmap(padrao);*/
	al_destroy_bitmap(conta1);
	al_destroy_bitmap(conta2);
	al_destroy_bitmap(campo1->bitmap);
	al_destroy_bitmap(campo2->bitmap);
	al_destroy_bitmap(campoesquerda->bitmap);
	al_destroy_bitmap(campodireita->bitmap);
	al_destroy_bitmap(bola->bitmap);

	free(SaidaBaixo);
	free(SaidaCima);
	free(SaidaEsquerda);
	free(campo1);
	free(campo2);
	free(campoesquerda);
	free(campodireita);
	free(bola);
	free(conta);


	//system("pause");

	return 0;
}
