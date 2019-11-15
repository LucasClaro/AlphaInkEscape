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


//a
int JogarFase7Mapa(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* prog) {
	Objeto* SaidaBaixo;
	SaidaBaixo = (Objeto*)malloc(sizeof(Objeto));
	SaidaBaixo->altura = 20;
	SaidaBaixo->largura = 20;
	SaidaBaixo->x = 110 + (LARGURA_TELA / 2) - (SaidaBaixo->largura / 2) - 100;
	SaidaBaixo->y = ALTURA_TELA - (SaidaBaixo->altura / 2);
	SaidaBaixo->bitmap = prog->cenario->cadeado;

	Objeto* SaidaEsquerda;
	SaidaEsquerda = (Objeto*)malloc(sizeof(Objeto));
	SaidaEsquerda->altura = 20;
	SaidaEsquerda->largura = 20;
	SaidaEsquerda->x = 110;
	SaidaEsquerda->y = (ALTURA_TELA / 2) - (SaidaBaixo->altura / 2);
	SaidaEsquerda->bitmap = prog->cenario->setaEsquerda;

	Objeto* SaidaCima;
	SaidaCima = (Objeto*)malloc(sizeof(Objeto));
	SaidaCima->altura = 20;
	SaidaCima->largura = 20;
	SaidaCima->x = 110 + (LARGURA_TELA / 2) - (SaidaCima->largura / 2);
	SaidaCima->y = 1;
	SaidaCima->bitmap = prog->cenario->setaCima;

	Objeto* campo1;
	campo1 = (Objeto*)malloc(sizeof(Objeto));
	campo1->bitmap = al_load_bitmap("Imgs/slide4.png");
	campo1->altura = 250;
	campo1->largura = 500;
	campo1->x = 0;
	campo1->y = ALTURA_TELA - campo1->altura;

	Objeto* campoesquerda;
	campoesquerda = (Objeto*)malloc(sizeof(Objeto));
	campoesquerda->bitmap = NULL;
	campoesquerda->altura = 250;
	campoesquerda->largura = 500;
	campoesquerda->x = 110;
	campoesquerda->y = 350;

	ALLEGRO_BITMAP* btn = al_load_bitmap("Imgs/MapaFase7/cimaMapa.png");
	ALLEGRO_BITMAP* btnPressionado = al_load_bitmap("Imgs/MapaFase7/cimaMapaPressionado.png");

	Objeto* campodireita;
	campodireita = (Objeto*)malloc(sizeof(Objeto));
	campodireita->bitmap = NULL;
	campodireita->altura = 250;
	campodireita->largura = 500;
	campodireita->x = 1100;
	campodireita->y = 350;

	//======================================IMAGENS=======================================================================
	Objeto* brasil;
	brasil = (Objeto*)malloc(sizeof(Objeto));
	brasil->bitmap = al_load_bitmap("Imgs/MapaFase7/Brasil.png");
	brasil->altura = 250;
	brasil->largura = 500;
	brasil->x = 250;
	brasil->y = 50;

	Objeto* toronto;
	toronto = (Objeto*)malloc(sizeof(Objeto));
	toronto->bitmap = al_load_bitmap("Imgs/MapaFase7/toronto.png");
	toronto->altura = 250;
	toronto->largura = 500;
	toronto->x = 750;
	toronto->y = 50;

	Objeto* londres;
	londres = (Objeto*)malloc(sizeof(Objeto));
	londres->bitmap = al_load_bitmap("Imgs/MapaFase7/londres.png");
	londres->altura = 250;
	londres->largura = 500;
	londres->x = 750;
	londres->y = 300;

	Objeto* china;
	china = (Objeto*)malloc(sizeof(Objeto));
	china->bitmap = al_load_bitmap("Imgs/MapaFase7/china.png");
	china->altura = 250;
	china->largura = 500;
	china->x = 250;
	china->y = 300;

	//==============================================CAMPOS===================================================

	Objeto* caixa1;
	caixa1 = (Objeto*)malloc(sizeof(Objeto));
	caixa1->bitmap = al_load_bitmap("Imgs/campo2.png");
	caixa1->altura = 100;
	caixa1->largura = 100;
	caixa1->x = 300;
	caixa1->y = 550;

	Objeto* caixa2;
	caixa2 = (Objeto*)malloc(sizeof(Objeto));
	caixa2->bitmap = al_load_bitmap("Imgs/campo2.png");
	caixa2->altura = 100;
	caixa2->largura = 100;
	caixa2->x = 500;
	caixa2->y = 550;

	Objeto* caixa3;
	caixa3 = (Objeto*)malloc(sizeof(Objeto));
	caixa3->bitmap = al_load_bitmap("Imgs/campo2.png");
	caixa3->altura = 100;
	caixa3->largura = 100;
	caixa3->x = 700;
	caixa3->y = 550;

	Objeto* caixa4;
	caixa4 = (Objeto*)malloc(sizeof(Objeto));
	caixa4->bitmap = al_load_bitmap("Imgs/campo2.png");
	caixa4->altura = 100;
	caixa4->largura = 100;
	caixa4->x = 900;
	caixa4->y = 550;

	//===========================================SETAS=================================================

	Objeto* setacima1;
	setacima1 = (Objeto*)malloc(sizeof(Objeto));
	setacima1->bitmap = NULL;
	setacima1->altura = 20;
	setacima1->largura = 20;
	setacima1->x = 340;
	setacima1->y = 530;

	Objeto* setacima2;
	setacima2 = (Objeto*)malloc(sizeof(Objeto));
	setacima2->bitmap = NULL;
	setacima2->altura = 20;
	setacima2->largura = 20;
	setacima2->x = 540;
	setacima2->y = 530;

	Objeto* setacima3;
	setacima3 = (Objeto*)malloc(sizeof(Objeto));
	setacima3->bitmap = NULL;
	setacima3->altura = 20;
	setacima3->largura = 20;
	setacima3->x = 740;
	setacima3->y = 530;

	Objeto* setacima4;
	setacima4 = (Objeto*)malloc(sizeof(Objeto));
	setacima4->bitmap = NULL;
	setacima4->altura = 20;
	setacima4->largura = 20;
	setacima4->x = 940;
	setacima4->y = 530;
	//-------------------------------------BAIXO----------------------------------------------
	Objeto* setabaixo1;
	setabaixo1 = (Objeto*)malloc(sizeof(Objeto));
	setabaixo1->bitmap = NULL;
	setabaixo1->altura = 20;
	setabaixo1->largura = 20;
	setabaixo1->x = 340;
	setabaixo1->y = 655;

	Objeto* setabaixo2;
	setabaixo2 = (Objeto*)malloc(sizeof(Objeto));
	setabaixo2->bitmap = NULL;
	setabaixo2->altura = 20;
	setabaixo2->largura = 20;
	setabaixo2->x = 540;
	setabaixo2->y = 655;

	Objeto* setabaixo3;
	setabaixo3 = (Objeto*)malloc(sizeof(Objeto));
	setabaixo3->bitmap = NULL;
	setabaixo3->altura = 20;
	setabaixo3->largura = 20;
	setabaixo3->x = 740;
	setabaixo3->y = 655;

	Objeto* setabaixo4;
	setabaixo4 = (Objeto*)malloc(sizeof(Objeto));
	setabaixo4->bitmap = NULL;
	setabaixo4->altura = 20;
	setabaixo4->largura = 20;
	setabaixo4->x = 940;
	setabaixo4->y = 655;

	//---------------------------------------------------SETAS-------------------------------------------------------
	Objeto* item;
	item = (Objeto*)malloc(sizeof(Objeto));
	item->bitmap = NULL;
	item->altura = 100;
	item->largura = 100;
	item->x = 310;
	item->y = 560;

	Objeto* item2;
	item2 = (Objeto*)malloc(sizeof(Objeto));
	item2->bitmap = NULL;
	item2->altura = 100;
	item2->largura = 100;
	item2->x = 510;
	item2->y = 560;

	Objeto* item3;
	item3 = (Objeto*)malloc(sizeof(Objeto));
	item3->bitmap = NULL;
	item3->altura = 100;
	item3->largura = 100;
	item3->x = 710;
	item3->y = 560;

	Objeto* item4;
	item4 = (Objeto*)malloc(sizeof(Objeto));
	item4->bitmap = NULL;
	item4->altura = 100;
	item4->largura = 100;
	item4->x = 910;
	item4->y = 560;

	//=========================================================================================================
	ALLEGRO_BITMAP* seta1 = al_load_bitmap("Imgs/MapaFase7/setaZ.png");
	ALLEGRO_BITMAP* seta2 = al_load_bitmap("Imgs/MapaFase7/setaT.png");
	ALLEGRO_BITMAP* seta3 = al_load_bitmap("Imgs/MapaFase7/setaQ.png");
	ALLEGRO_BITMAP* seta4 = al_load_bitmap("Imgs/MapaFase7/setaN.png");
	ALLEGRO_BITMAP* itens[] = { seta1, seta2, seta3, seta4 };


	ALLEGRO_BITMAP* btn2 = al_load_bitmap("Imgs/MapaFase7/cimaMapa.png");
	ALLEGRO_BITMAP* btnPressionado2 = al_load_bitmap("Imgs/MapaFase7/cimaMapaPressionado.png");

	ALLEGRO_BITMAP* btn3 = al_load_bitmap("Imgs/MapaFase7/cimaMapa.png");
	ALLEGRO_BITMAP* btnPressionado3 = al_load_bitmap("Imgs/MapaFase7/cimaMapaPressionado.png");

	ALLEGRO_BITMAP* btn4 = al_load_bitmap("Imgs/MapaFase7/cimaMapa.png");
	ALLEGRO_BITMAP* btnPressionado4 = al_load_bitmap("Imgs/MapaFase7/cimaMapaPressionado.png");

	//------------------------------------------------------------------------------------------------------------------------
	//a
	ALLEGRO_BITMAP* btn5 = al_load_bitmap("Imgs/MapaFase7/baixoMapa1.png");
	ALLEGRO_BITMAP* btnPressionado5 = al_load_bitmap("Imgs/MapaFase7/baixoMapaPressionado.png");

	ALLEGRO_BITMAP* btn6 = al_load_bitmap("Imgs/MapaFase7/baixoMapa1.png");
	ALLEGRO_BITMAP* btnPressionado6 = al_load_bitmap("Imgs/MapaFase7/baixoMapaPressionado.png");

	ALLEGRO_BITMAP* btn7 = al_load_bitmap("Imgs/MapaFase7/baixoMapa1.png");
	ALLEGRO_BITMAP* btnPressionado7 = al_load_bitmap("Imgs/MapaFase7/baixoMapaPressionado.png");

	ALLEGRO_BITMAP* btn8 = al_load_bitmap("Imgs/MapaFase7/baixoMapa1.png");
	ALLEGRO_BITMAP* btnPressionado8 = al_load_bitmap("Imgs/MapaFase7/baixoMapaPressionado.png");


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
	conta->altura = 500;
	conta->largura = 250;
	conta->x = (LARGURA_TELA / 2) - (conta->largura);
	conta->y = (ALTURA_TELA / 2) - (conta->altura / 2);

	//ALLEGRO_BITMAP* padrao = al_load_bitmap("");
	ALLEGRO_BITMAP* conta1 = al_load_bitmap("Imgs/esquerda.png");
	ALLEGRO_BITMAP* conta2 = al_load_bitmap("Imgs/direita.png");
	ALLEGRO_BITMAP* background = prog->cenario->background;


	int vetorResposta[10] = { 1,1,2,1,1,2,2,1,2,2 }; //"EEDEEDDEDD";


	bool digitado = false;
	bool sair = false;
	bool drawNull = true;
	bool arrastando = false;
	bool pressionado = false;

	setacima1->bitmap = btn;
	setacima2->bitmap = btn2;
	setacima3->bitmap = btn3;
	setacima4->bitmap = btn4;
	setabaixo1->bitmap = btn5;
	setabaixo2->bitmap = btn6;
	setabaixo3->bitmap = btn7;
	setabaixo4->bitmap = btn8;

	int i = 0;
	int j = 2;
	int k = 2;
	int o = 2;
	int g = 2;




	item->bitmap = itens[j];
	item2->bitmap = itens[k];
	item3->bitmap = itens[o];
	item4->bitmap = itens[g];

	while (!sair)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(fila_eventos, &evento);

		ALLEGRO_MOUSE_STATE state;
		al_get_mouse_state(&state);

		if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (evento.keyboard.keycode == ALLEGRO_KEY_F1) {
				j = 0;
				k = 1;
				o = 2;
				g = 3;
				item->bitmap = itens[j];
				item2->bitmap = itens[k];
				item3->bitmap = itens[o];
				item4->bitmap = itens[g];

				prog->Salas[7] = 1;
			}
		}

		if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (IsInside(evento.mouse.x, evento.mouse.y, bola) && !arrastando) {
				arrastando = true;

				bola->cliqueX = MapearDistancia(evento.mouse.x, bola->x);
				bola->cliqueY = MapearDistancia(evento.mouse.y, bola->y);
			}

			else if (IsInside(evento.mouse.x, evento.mouse.y, setacima1) && prog->Salas[7] == 0) {
				if (!pressionado && state.buttons & 1)
				{
					j--;
					if (j == -1) {
						j = 3;
					}
					item->bitmap = itens[j];


					pressionado = false;
					setacima1->bitmap = btnPressionado;
				}


			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, setacima2) && prog->Salas[7] == 0) {
				if (!pressionado && state.buttons & 1)
				{
					k--;
					if (k == -1) {
						k = 3;
					}
					item2->bitmap = itens[k];

					pressionado = true;
					setacima2->bitmap = btnPressionado2;
				}

			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, setacima3) && prog->Salas[7] == 0) {
				if (!pressionado && state.buttons & 1)
				{
					o--;
					if (o == -1) {
						o = 3;
					}
					item3->bitmap = itens[o];
					pressionado = true;
					setacima3->bitmap = btnPressionado3;
				}

			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, setacima4) && prog->Salas[7] == 0) {
				if (!pressionado && state.buttons & 1)
				{
					g--;
					if (g == -1) {
						g = 3;
					}
					item4->bitmap = itens[g];
					pressionado = true;
					setacima4->bitmap = btnPressionado4;
				}

			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, setabaixo1) && prog->Salas[7] == 0) {
				if (!pressionado && state.buttons & 1)
				{
					pressionado = true;
					setabaixo1->bitmap = btnPressionado5;
					j++;
					if (j == 4) {
						j = 0;
					}
					item->bitmap = itens[j];

					//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
										//SE J = 0 && K==1 && O==3 && G == 4
										//OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
				}

			}

			else if (IsInside(evento.mouse.x, evento.mouse.y, setabaixo2) && prog->Salas[7] == 0) {
				if (!pressionado && state.buttons & 1)
				{
					pressionado = true;
					setabaixo2->bitmap = btnPressionado6;
					k++;
					if (k == 4) {
						k = 0;
					}
					item2->bitmap = itens[k];
				}

			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, setabaixo3) && prog->Salas[7] == 0) {
				if (!pressionado && state.buttons & 1)
				{
					o++;
					if (o == 4) {
						o = 0;
					}
					item3->bitmap = itens[o];
					pressionado = true;
					setabaixo3->bitmap = btnPressionado7;
				}

			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, setabaixo4) && prog->Salas[7] == 0) {
				if (!pressionado && state.buttons & 1)
				{
					g++;
					if (g == 4) {
						g = 0;
					}
					item4->bitmap = itens[g];
					pressionado = true;
					setabaixo4->bitmap = btnPressionado8;
				}

			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, SaidaCima))
			{
				prog->proximaSala = 3;
				sair = 1;
			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, SaidaEsquerda))
			{
				prog->proximaSala = 6;
				sair = 1;
			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, SaidaBaixo) && prog->Salas[7])
			{
				prog->proximaSala = 11;
				sair = 1;
			}
			/*else if (IsInside(evento.mouse.x, evento.mouse.y, prog->btnMiniMapa))
			{
				aberto = !aberto;
			}*/
		}
		else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			arrastando = false;
			pressionado = false;
			setacima1->bitmap = btn;
			setacima2->bitmap = btn2;
			setacima3->bitmap = btn3;
			setacima4->bitmap = btn4;
			setabaixo1->bitmap = btn5;
			setabaixo2->bitmap = btn6;
			setabaixo3->bitmap = btn7;
			setabaixo4->bitmap = btn8;

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

		if (j == 0 && k == 1 && o == 2 && g == 3) {
			SaidaBaixo->bitmap = prog->cenario->setaBaixo;
			prog->Salas[7] = 1;
		}




		//===========================================DESENHAR========================================================================
		al_draw_bitmap(background, 0, 0, 0);
		/*if (prog->Salas[0])*/
		al_draw_bitmap(SaidaCima->bitmap, SaidaCima->x, SaidaCima->y, 0);


		al_draw_bitmap(SaidaEsquerda->bitmap, SaidaEsquerda->x, SaidaEsquerda->y, 0);
		al_draw_bitmap(SaidaBaixo->bitmap, SaidaBaixo->x, SaidaBaixo->y, 0);


		//if (!drawNull)
		//	al_draw_bitmap(conta->bitmap, conta->x, conta->y, 0);


		al_draw_bitmap(item4->bitmap, item4->x, item4->y, 0);
		al_draw_bitmap(item3->bitmap, item3->x, item3->y, 0);
		al_draw_bitmap(item2->bitmap, item2->x, item2->y, 0);
		al_draw_bitmap(item->bitmap, item->x, item->y, 0);
		al_draw_bitmap(setabaixo4->bitmap, setabaixo4->x, setabaixo4->y, 0);
		al_draw_bitmap(setabaixo3->bitmap, setabaixo3->x, setabaixo3->y, 0);
		al_draw_bitmap(setabaixo2->bitmap, setabaixo2->x, setabaixo2->y, 0);
		al_draw_bitmap(setabaixo1->bitmap, setabaixo1->x, setabaixo1->y, 0);
		al_draw_bitmap(setacima4->bitmap, setacima4->x, setacima4->y, 0);
		al_draw_bitmap(setacima3->bitmap, setacima3->x, setacima3->y, 0);
		al_draw_bitmap(setacima2->bitmap, setacima2->x, setacima2->y, 0);
		al_draw_bitmap(setacima1->bitmap, setacima1->x, setacima1->y, 0);
		al_draw_bitmap(caixa4->bitmap, caixa4->x, caixa4->y, 0);
		al_draw_bitmap(caixa3->bitmap, caixa3->x, caixa3->y, 0);
		al_draw_bitmap(caixa2->bitmap, caixa2->x, caixa2->y, 0);
		al_draw_bitmap(caixa1->bitmap, caixa1->x, caixa1->y, 0);
		al_draw_bitmap(china->bitmap, china->x, china->y, 0);
		al_draw_bitmap(londres->bitmap, londres->x, londres->y, 0);
		al_draw_bitmap(toronto->bitmap, toronto->x, toronto->y, 0);
		al_draw_bitmap(brasil->bitmap, brasil->x, brasil->y, 0);

		//abrirMapa(prog);
		caregaInventario(prog);
		al_flip_display();
	}

	//al_destroy_bitmap(padrao);
	al_destroy_bitmap(conta1);
	al_destroy_bitmap(conta2);
	al_destroy_bitmap(campo1->bitmap);
	al_destroy_bitmap(campo2->bitmap);
	al_destroy_bitmap(campoesquerda->bitmap);
	al_destroy_bitmap(campodireita->bitmap);
	al_destroy_bitmap(bola->bitmap);
	al_destroy_bitmap(china->bitmap);
	al_destroy_bitmap(brasil->bitmap);
	al_destroy_bitmap(londres->bitmap);
	al_destroy_bitmap(toronto->bitmap);
	al_destroy_bitmap(setacima1->bitmap);
	al_destroy_bitmap(setacima2->bitmap);
	al_destroy_bitmap(setacima3->bitmap);
	al_destroy_bitmap(setacima4->bitmap);
	al_destroy_bitmap(setabaixo1->bitmap);
	al_destroy_bitmap(setabaixo2->bitmap);
	al_destroy_bitmap(setabaixo3->bitmap);
	al_destroy_bitmap(setabaixo4->bitmap);
	al_destroy_bitmap(caixa1->bitmap);
	al_destroy_bitmap(caixa2->bitmap);
	al_destroy_bitmap(caixa3->bitmap);
	al_destroy_bitmap(caixa4->bitmap);
	//al_destroy_bitmap(item->bitmap);
	//al_destroy_bitmap(item2->bitmap);
	//al_destroy_bitmap(item3->bitmap);
	//al_destroy_bitmap(item4->bitmap);


	free(SaidaBaixo);
	free(SaidaCima);
	free(SaidaEsquerda);
	free(campo1);
	free(campo2);
	free(campoesquerda);
	free(campodireita);
	free(bola);
	free(conta);

	free(item);
	free(item2);
	free(item3);
	free(item4);
	free(setabaixo1);
	free(setabaixo2);
	free(setabaixo3);
	free(setabaixo4);
	free(setacima1);
	free(setacima2);
	free(setacima3);
	free(setacima4);
	free(caixa1);
	free(caixa2);
	free(caixa3);
	free(caixa4);
	free(china);
	free(londres);
	free(brasil);
	free(toronto);

	return 0;
}