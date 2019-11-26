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
#include "ctype.h"
#include <string.h>

int JogarFase3Asc(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* prog) {
	//variaveis
	bool sair = false;
	//ponteiros
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_FONT* enigma = al_load_font("ArquivosAux/fonts/Kindergarten.ttf", 60, 0);
	ALLEGRO_FONT* digitado = NULL;
	ALLEGRO_FONT* fonte = NULL;

	enigmaStr* enigma1;
	enigma1 = (enigmaStr*)malloc(sizeof(enigmaStr));
	enigma1->fonte = enigma;
	enigma1->enigmaCerto = "origem";
	enigma1->acertou = false;
	enigma1->verCampo = 1;

	Objeto* setaEsquerda;
	setaEsquerda = (Objeto*)malloc(sizeof(Objeto));
	setaEsquerda->bitmap = prog->cenario->setaEsquerda;
	setaEsquerda->altura = 50;
	setaEsquerda->largura = 50;
	setaEsquerda->x = 110;
	setaEsquerda->y = (ALTURA_TELA / 2) - (setaEsquerda->altura / 2);

	Objeto* setaBaixo;
	setaBaixo = (Objeto*)malloc(sizeof(Objeto));
	setaBaixo->altura = 50;
	setaBaixo->largura = 50;
	setaBaixo->x = 110 + (LARGURA_TELA / 2) - (setaBaixo->largura / 2);
	setaBaixo->y = ALTURA_TELA - setaBaixo->altura;
	setaBaixo->bitmap = prog->cenario->setaBaixo;


	Objeto* campo;
	campo = (Objeto*)malloc(sizeof(Objeto));
	campo->bitmap = al_load_bitmap("Imgs/Binary/slide6.png");
	campo->altura = 250;
	campo->largura = 500;
	campo->x = (LARGURA_TELA / 2) - (campo->largura / 2) + 110;
	campo->y = (ALTURA_TELA / 2) - (campo->altura / 2);

	Objeto* tabela;
	tabela = (Objeto*)malloc(sizeof(Objeto));
	tabela->bitmap = al_load_bitmap("Imgs/Asc/ascii.png");
	tabela->altura = 360;
	tabela->largura = 435;
	tabela->x = 160;
	tabela->y = 150;

	bool arrastando = false;
	char arrEnigma[10] = "";
	bool verDigitado = 0;
	int cor = 0;
	while (!sair)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(fila_eventos, &evento);
		al_set_target_bitmap(al_get_backbuffer(janela));
		al_clear_to_color(al_map_rgb(0, 0, 0));

		if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			limpaClick(prog);

			if (IsInside(evento.mouse.x, evento.mouse.y, setaEsquerda)) {
				coletarAutomatico(prog);
				prog->proximaSala = 2;
				//return;
				al_play_sample(prog->cenario->somSeta, volume, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				sair = true;
			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, setaBaixo)) {
				coletarAutomatico(prog);
				prog->proximaSala = 7;
				//return;
				al_play_sample(prog->cenario->somSeta, volume, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				sair = true;
			}
			//Mute
			else if (IsInside(evento.mouse.x, evento.mouse.y, prog->cenario->btnSom)) {
				tocando = !tocando;
			}
			//Clique no minimapa
			else if (IsInside(evento.mouse.x, evento.mouse.y, prog->cenario->btnMiniMapa))
			{
				aberto = !aberto;
			}
			//Clique na saída
			else if (IsInside(evento.mouse.x, evento.mouse.y, prog->cenario->saida)) {
				coletarAutomatico(prog);
				sair = 1;
				salvar(prog);
			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, campo)) {
				verDigitado = 1;
			}
			else if(IsInside(evento.mouse.x, evento.mouse.y, prog->cenario->sobreBi))
			{
				prog->Inventario[3] = 1;
				prog->inventCount++;
			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, prog->cenario->miniatura) && !prog->Inventario[4] && prog->Salas[3])
			{
				prog->Inventario[4] = 1;
				prog->inventCount++;
			}
			checaClickOrdem(evento.mouse.x, evento.mouse.y, prog);
			
			
			ALLEGRO_MOUSE_STATE state;
			al_get_mouse_state(&state);
			if (state.buttons & 2)
			{
				printf("x: %d; y: %d\n",evento.mouse.x,evento.mouse.y);
			}
		}
		if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {
			if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER && strncmp(enigma1->enigmaCerto, arrEnigma, 7) == 0)
			{
				prog->Salas[3] = 1;			
				cor = 255;
			}
			else if (verDigitado && evento.keyboard.keycode != ALLEGRO_KEY_ENTER) {
				digitarCampoAsc(enigma1, arrEnigma, evento, sair, prog);
			}
		}


		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			sair = true;
			prog->Gameover = true;
		}



		al_draw_bitmap(prog->cenario->background, 0, 0, 0);
		al_draw_bitmap(setaEsquerda->bitmap, setaEsquerda->x, setaEsquerda->y, 0);
		al_draw_bitmap(setaBaixo->bitmap, setaBaixo->x, setaBaixo->y, 0);
		al_draw_bitmap(campo->bitmap, campo->x, campo->y, 0);
		al_draw_bitmap(tabela->bitmap, tabela->x, tabela->y, 0);
		if(!prog->Inventario[3])
			al_draw_bitmap(prog->cenario->sobreBi->bitmap, prog->cenario->sobreBi->x, prog->cenario->sobreBi->y, 0);

		//teste master
		al_draw_text(enigma, al_map_rgb(0, cor,0), LARGURA_TELA/2 - 45, ALTURA_TELA/2 - 25, 0, arrEnigma);

		if (prog->Salas[3] && !prog->Inventario[4])
			al_draw_bitmap(prog->cenario->miniatura->bitmap, prog->cenario->miniatura->x, prog->cenario->miniatura->y, 0);

		al_draw_bitmap(prog->cenario->saida->bitmap, prog->cenario->saida->x, prog->cenario->saida->y, 0);

		//Funções padrões
		caregaInventario(prog);
		abrirMapa(prog);
		abreOrdem(prog);
		som(prog);

		al_flip_display();
	}


	al_destroy_display(display);

	al_destroy_font(enigma);
	al_destroy_font(digitado);

	free(setaEsquerda);


	return 0;
}


int digitarCampoAsc(enigmaStr* enigma, char arrEnigma[], ALLEGRO_EVENT evento, bool sair, Progresso* prog) {
	char letra[5] = "";

	if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && (enigma->acertou == false)) {
		//backspace, volta uma posicao no texto
		if (arrEnigma[strlen(arrEnigma) - 1] > -1)
		{
			arrEnigma[strlen(arrEnigma) - 1] = '\0';
		}

	}
	else if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
	{
		sair = true;
		prog->Gameover = true;
	}
	else
	{
		if ((enigma->acertou == false)) {
			if (enigma->verCampo == 1) {
				if ((strlen(arrEnigma)) < 8) {
					int uni = evento.keyboard.unichar;
					letra[0] = (char)uni;

					char* copy1;

					_strlwr_s(copy1 = letra, strlen(letra) + 1);

					arrEnigma[strlen(arrEnigma)] = copy1[0];
				}
			}
			else if ((strlen(arrEnigma)) < 4) {
				int uni = evento.keyboard.unichar;
				letra[0] = (char)uni;
				arrEnigma[strlen(arrEnigma)] = letra[0];
			}
		}
	}

	return 0;
}
