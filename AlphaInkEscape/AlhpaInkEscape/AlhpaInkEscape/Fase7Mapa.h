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

//Função Main da fase
int JogarFase7Mapa(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* prog) {	

	//Cria Objs
	Objeto* SaidaBaixo;
	SaidaBaixo = (Objeto*)malloc(sizeof(Objeto));
	SaidaBaixo->altura = 50;
	SaidaBaixo->largura = 50;
	SaidaBaixo->x = 110 + (LARGURA_TELA / 2) - (SaidaBaixo->largura / 2);
	SaidaBaixo->y = ALTURA_TELA - SaidaBaixo->altura;
	SaidaBaixo->bitmap = prog->cenario->cadeado;

	Objeto* SaidaEsquerda;
	SaidaEsquerda = (Objeto*)malloc(sizeof(Objeto));
	SaidaEsquerda->altura = 50;
	SaidaEsquerda->largura = 50;
	SaidaEsquerda->x = 110;
	SaidaEsquerda->y = (ALTURA_TELA / 2) - (SaidaBaixo->altura / 2);
	SaidaEsquerda->bitmap = prog->cenario->setaEsquerda;

	Objeto* SaidaCima;
	SaidaCima = (Objeto*)malloc(sizeof(Objeto));
	SaidaCima->altura = 50;
	SaidaCima->largura = 20;
	SaidaCima->x = 110 + (LARGURA_TELA / 2) - (SaidaCima->largura / 2);
	SaidaCima->y = 1;
	SaidaCima->bitmap = prog->cenario->setaCima;	

	//======================================IMAGENS=======================================================================
	Objeto* tabela;
	tabela = (Objeto*)malloc(sizeof(Objeto));
	tabela->bitmap = al_load_bitmap("Imgs/MapaFase7/tabela.png");
	tabela->altura = 200;
	tabela->largura = 310;
	tabela->x = 250;
	tabela->y = 50;

	Objeto* brasil;
	brasil = (Objeto*)malloc(sizeof(Objeto));
	brasil->bitmap = al_load_bitmap("Imgs/MapaFase7/brasil.png");
	brasil->altura = 200;
	brasil->largura = 310;
	brasil->x = 750;
	brasil->y = 50;

	Objeto* mundo;
	mundo = (Objeto*)malloc(sizeof(Objeto));
	mundo->bitmap = al_load_bitmap("Imgs/MapaFase7/mundo.png");
	mundo->altura = 200;
	mundo->largura = 310;
	mundo->x = 750;
	mundo->y = 300;

	Objeto* europa;
	europa = (Objeto*)malloc(sizeof(Objeto));
	europa->bitmap = al_load_bitmap("Imgs/MapaFase7/europa.png");
	europa->altura = 200;
	europa->largura = 310;
	europa->x = 250;
	europa->y = 300;

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
	Objeto* item1;
	item1 = (Objeto*)malloc(sizeof(Objeto));
	item1->bitmap = NULL;
	item1->altura = 100;
	item1->largura = 100;
	item1->x = 310;
	item1->y = 560;

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

	Objeto* exemplo1;
	exemplo1 = (Objeto*)malloc(sizeof(Objeto));
	exemplo1->bitmap = NULL;
	exemplo1->altura = 40;
	exemplo1->largura = 40;
	exemplo1->x = tabela->x + tabela->largura / 2 - 120;
	exemplo1->y = tabela->y + tabela->altura / 2 - 40;

	Objeto* exemplo2;
	exemplo2 = (Objeto*)malloc(sizeof(Objeto));
	exemplo2->bitmap = NULL;
	exemplo2->altura = 100;
	exemplo2->largura = 100;
	exemplo2->x = brasil->x + brasil->largura / 2 - 40;
	exemplo2->y = brasil->y + brasil->altura / 2 - 40;

	Objeto* exemplo3;
	exemplo3 = (Objeto*)malloc(sizeof(Objeto));
	exemplo3->bitmap = NULL;
	exemplo3->altura = 100;
	exemplo3->largura = 100;
	exemplo3->x = europa->x + europa->largura / 2 - 120;
	exemplo3->y = europa->y + europa->altura / 2 - 40;

	Objeto* exemplo4;
	exemplo4 = (Objeto*)malloc(sizeof(Objeto));
	exemplo4->bitmap = NULL;
	exemplo4->altura = 100;
	exemplo4->largura = 100;
	exemplo4->x = mundo->x + mundo->largura / 2 - 90;
	exemplo4->y = mundo->y + mundo->altura / 2 - 50;

	//Preenche as imagens===============================================================================
	ALLEGRO_BITMAP* seta1 = al_load_bitmap("Imgs/MapaFase7/setaZ.png");
	ALLEGRO_BITMAP* seta2 = al_load_bitmap("Imgs/MapaFase7/setaT.png");
	ALLEGRO_BITMAP* seta3 = al_load_bitmap("Imgs/MapaFase7/setaQ.png");
	ALLEGRO_BITMAP* seta4 = al_load_bitmap("Imgs/MapaFase7/setaN.png");
	ALLEGRO_BITMAP* itens[] = { seta1, seta2, seta3, seta4 };

	ALLEGRO_BITMAP* btnB = al_load_bitmap("Imgs/MapaFase7/baixoMapa.png");
	ALLEGRO_BITMAP* btnC = al_load_bitmap("Imgs/MapaFase7/cimaMapa.png");
	ALLEGRO_BITMAP* btnPressionadoB = al_load_bitmap("Imgs/MapaFase7/baixoMapaPressionado.png");
	ALLEGRO_BITMAP* btnPressionadoC = al_load_bitmap("Imgs/MapaFase7/cimaMapaPressionado.png");

	ALLEGRO_BITMAP* exemploZ = al_load_bitmap("Imgs/MapaFase7/exemploZ.png");
	ALLEGRO_BITMAP* exemploT = al_load_bitmap("Imgs/MapaFase7/exemploT.png");
	ALLEGRO_BITMAP* exemploQ = al_load_bitmap("Imgs/MapaFase7/exemploQ.png");
	ALLEGRO_BITMAP* exemploN = al_load_bitmap("Imgs/MapaFase7/exemploN.png");
	ALLEGRO_BITMAP* exemplos[] = { exemploZ, exemploT, exemploQ, exemploN };

	setacima1->bitmap = btnC;
	setacima2->bitmap = btnC;
	setacima3->bitmap = btnC;
	setacima4->bitmap = btnC;
	setabaixo1->bitmap = btnB;
	setabaixo2->bitmap = btnB;
	setabaixo3->bitmap = btnB;
	setabaixo4->bitmap = btnB;

	//vars de controle
	int j = 2;
	int k = 2;
	int o = 2;
	int g = 2;

	//Coloca as imagens da "roda" nos elementos 
	item1->bitmap = itens[j];
	item2->bitmap = itens[k];
	item3->bitmap = itens[o];
	item4->bitmap = itens[g];

	exemplo1->bitmap = exemplos[j];
	exemplo2->bitmap = exemplos[k];
	exemplo3->bitmap = exemplos[o];
	exemplo4->bitmap = exemplos[g];

	//Controle da fase
	bool sair = false;
	//Loop da fase
	while (!sair)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(fila_eventos, &evento);

		ALLEGRO_MOUSE_STATE state;
		al_get_mouse_state(&state);

		if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
			//Konami Code
			if (evento.keyboard.keycode == ALLEGRO_KEY_F1) {
				j = 0;
				k = 1;
				o = 2;
				g = 3;
				item1->bitmap = itens[j];
				item2->bitmap = itens[k];
				item3->bitmap = itens[o];
				item4->bitmap = itens[g];

				prog->Salas[7] = 1;
			}
		}

		if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			//Função do Inventário
			limpaClick(prog);

			//Mute
			if (IsInside(evento.mouse.x, evento.mouse.y, prog->cenario->btnSom)) {
				tocando = !tocando;
			}
			//Clique no minimapa
			else if (IsInside(evento.mouse.x, evento.mouse.y, prog->cenario->btnMiniMapa))
			{
				aberto = !aberto;
			}
			//Clique na saída
			else if (IsInside(evento.mouse.x, evento.mouse.y, prog->cenario->saida)) {
				sair = 1;
				salvar(prog);
			}
			//SetaUp primeiro bloco
			else if (IsInside(evento.mouse.x, evento.mouse.y, setacima1) && !prog->Salas[7]) {

				j--;//Muda o valor da "roda" de imgs
				if (j == -1)
					j = 3;

				setacima1->bitmap = btnPressionadoC;//Muda o desenho do btn
			}
			//SetaUp segundo bloco
			else if (IsInside(evento.mouse.x, evento.mouse.y, setacima2) && !prog->Salas[7]) {
				k--;
				if (k == -1)
					k = 3;

				setacima2->bitmap = btnPressionadoC;
			}
			//SetaUp terceiro bloco
			else if (IsInside(evento.mouse.x, evento.mouse.y, setacima3) && !prog->Salas[7]) {
				o--;
				if (o == -1)
					o = 3;

				setacima3->bitmap = btnPressionadoC;
			}
			//SetaUp quarto bloco
			else if (IsInside(evento.mouse.x, evento.mouse.y, setacima4) && !prog->Salas[7]) {
				g--;
				if (g == -1)
					g = 3;

				setacima4->bitmap = btnPressionadoC;
			}
			//SetaBaixo primeiro bloco
			else if (IsInside(evento.mouse.x, evento.mouse.y, setabaixo1) && !prog->Salas[7]) {					
				j++;
				if (j == 4)
					j = 0;

				setabaixo1->bitmap = btnPressionadoB;
			}
			//SetaBaixo segundo bloco
			else if (IsInside(evento.mouse.x, evento.mouse.y, setabaixo2) && !prog->Salas[7]) {
				k++;
				if (k == 4)
					k = 0;

				setabaixo2->bitmap = btnPressionadoB;
			}
			//SetaBaixo terceiro bloco
			else if (IsInside(evento.mouse.x, evento.mouse.y, setabaixo3) && !prog->Salas[7]) {
				o++;
				if (o == 4)
					o = 0;

				setabaixo3->bitmap = btnPressionadoB;
			}
			//SetaBaixo quarto bloco
			else if (IsInside(evento.mouse.x, evento.mouse.y, setabaixo4) && !prog->Salas[7]) {
					g++;
					if (g == 4)
						g = 0;

					setabaixo4->bitmap = btnPressionadoB;
			}
			//Saida Cima
			else if (IsInside(evento.mouse.x, evento.mouse.y, SaidaCima))
			{
				prog->proximaSala = 3;
				al_play_sample(prog->cenario->somSeta, volume, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				sair = 1;
			}
			//Saida Esquerda
			else if (IsInside(evento.mouse.x, evento.mouse.y, SaidaEsquerda))
			{
				prog->proximaSala = 6;
				al_play_sample(prog->cenario->somSeta, volume, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				sair = 1;
			}
			//Saida Baixo
			else if (IsInside(evento.mouse.x, evento.mouse.y, SaidaBaixo) && prog->Salas[7])
			{
				prog->proximaSala = 11;
				al_play_sample(prog->cenario->somSeta, volume, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				sair = 1;
			}
			//Item
			else if (IsInside(evento.mouse.x, evento.mouse.y, prog->cenario->miniaturaObras) && !prog->Itens[5])
			{
				prog->Inventario[5] = 1;
			}

			//Atribui as imagens aos blocos
			item1->bitmap = itens[j];
			item2->bitmap = itens[k];
			item3->bitmap = itens[o];
			item4->bitmap = itens[g];

			exemplo1->bitmap = exemplos[j];
			exemplo2->bitmap = exemplos[k];
			exemplo3->bitmap = exemplos[o];
			exemplo4->bitmap = exemplos[g];

			//Função do inventário
			checaClickOrdem(evento.mouse.x, evento.mouse.y, prog);
		}
		else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			//Volta o desenho padrão dos btns
			setacima1->bitmap = btnC;
			setacima2->bitmap = btnC;
			setacima3->bitmap = btnC;
			setacima4->bitmap = btnC;
			setabaixo1->bitmap = btnB;
			setabaixo2->bitmap = btnB;
			setabaixo3->bitmap = btnB;
			setabaixo4->bitmap = btnB;

		}

		//X do Windows
		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			sair = true;
			prog->Gameover = true;
		}

		//Verefica condição de vitória
		if (j == 0 && k == 1 && o == 2 && g == 3) {
			SaidaBaixo->bitmap = prog->cenario->setaBaixo;
			prog->Salas[7] = 1;
		}

		//===========================================DESENHAR========================================================================
		al_draw_bitmap(prog->cenario->background, 0, 0, 0);

		al_draw_bitmap(SaidaCima->bitmap, SaidaCima->x, SaidaCima->y, 0);
		al_draw_bitmap(SaidaEsquerda->bitmap, SaidaEsquerda->x, SaidaEsquerda->y, 0);
		al_draw_bitmap(SaidaBaixo->bitmap, SaidaBaixo->x, SaidaBaixo->y, 0);

		al_draw_bitmap(item4->bitmap, item4->x, item4->y, 0);
		al_draw_bitmap(item3->bitmap, item3->x, item3->y, 0);
		al_draw_bitmap(item2->bitmap, item2->x, item2->y, 0);
		al_draw_bitmap(item1->bitmap, item1->x, item1->y, 0);

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

		al_draw_bitmap(europa->bitmap, europa->x, europa->y, 0);
		al_draw_bitmap(mundo->bitmap, mundo->x, mundo->y, 0);
		al_draw_bitmap(brasil->bitmap, brasil->x, brasil->y, 0);
		al_draw_bitmap(tabela->bitmap, tabela->x, tabela->y, 0);

		al_draw_bitmap(exemplo1->bitmap, exemplo1->x, exemplo1->y, 0);
		al_draw_bitmap(exemplo2->bitmap, exemplo2->x, exemplo2->y, 0);
		al_draw_bitmap(exemplo3->bitmap, exemplo3->x, exemplo3->y, 0);
		al_draw_bitmap(exemplo4->bitmap, exemplo4->x, exemplo4->y, 0);

		if(!prog->Inventario[5])
			al_draw_bitmap(prog->cenario->miniaturaObras->bitmap, prog->cenario->miniaturaObras->x, prog->cenario->miniaturaObras->y, 0);

		al_draw_bitmap(prog->cenario->saida->bitmap, prog->cenario->saida->x, prog->cenario->saida->y, 0);

		//Funções padrões
		abrirMapa(prog);
		som(prog);
		caregaInventario(prog);
		abreOrdem(prog);


		al_flip_display();
	}

	//al_destroy_bitmap(padrao);
	al_destroy_bitmap(europa->bitmap);
	al_destroy_bitmap(tabela->bitmap);
	al_destroy_bitmap(mundo->bitmap);
	al_destroy_bitmap(brasil->bitmap);
	al_destroy_bitmap(btnB);
	al_destroy_bitmap(btnC);
	al_destroy_bitmap(btnPressionadoB);
	al_destroy_bitmap(btnPressionadoC);
	al_destroy_bitmap(caixa1->bitmap);
	al_destroy_bitmap(caixa2->bitmap);
	al_destroy_bitmap(caixa3->bitmap);
	al_destroy_bitmap(caixa4->bitmap);


	free(SaidaBaixo);
	free(SaidaCima);
	free(SaidaEsquerda);

	free(item1);
	free(item2);
	free(item3);
	free(item4);
	free(caixa1);
	free(caixa2);
	free(caixa3);
	free(caixa4);
	free(europa);
	free(mundo);
	free(tabela);
	free(brasil);

	return 0;
}