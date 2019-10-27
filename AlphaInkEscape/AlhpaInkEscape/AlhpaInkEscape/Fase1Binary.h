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

typedef struct EnigmaStr
{
	ALLEGRO_FONT* fonte;
	char* enigmaCerto;
	int verCampo;
	bool acertou;
} enigmaStr;

Objeto* postIt4 = NULL;

int JogarFase1Binary(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* prog) {
	//variaveis
	bool sair = false;
	//ponteiros
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_FONT* enigma = NULL;
	ALLEGRO_FONT* digitado = NULL;
	ALLEGRO_FONT* fonte = NULL;


	postIt4 = (Objeto*)malloc(sizeof(Objeto));
	postIt4->altura = 183;
	postIt4->largura = 201;
	postIt4->x = -500;
	postIt4->y = -500;
	postIt4->bitmap = NULL;
	
	postIt4->bitmap = al_load_bitmap("Imgs/postitHomem.png");

	Objeto* conta1;
	conta1 = (Objeto*)malloc(sizeof(Objeto));
	conta1->bitmap = al_load_bitmap("Imgs/slide1.png");
	conta1->altura = 250;
	conta1->largura = 500;
	conta1->x = (LARGURA_TELA / 2) - conta1->largura;
	conta1->y = (ALTURA_TELA / 4) - (conta1->altura / 2);

	Objeto* campo1;
	campo1 = (Objeto*)malloc(sizeof(Objeto));
	campo1->bitmap = al_load_bitmap("Imgs/slide6.png");
	campo1->altura = 250;
	campo1->largura = 500;
	campo1->x = (LARGURA_TELA / 2);
	campo1->y = (ALTURA_TELA / 4) - (campo1->altura / 2);

	Objeto* conta2;
	conta2 = (Objeto*)malloc(sizeof(Objeto));
	conta2->bitmap = al_load_bitmap("Imgs/slide2.png");
	conta2->altura = 250;
	conta2->largura = 500;
	conta2->x = (LARGURA_TELA / 2) - conta2->largura;
	conta2->y = (ALTURA_TELA / 2) - (conta2->altura / 2);


	Objeto* campo2;
	campo2 = (Objeto*)malloc(sizeof(Objeto));
	campo2->bitmap = al_load_bitmap("Imgs/slide4.png");
	campo2->altura = 250;
	campo2->largura = 500;
	campo2->x = (LARGURA_TELA / 2) - campo2->largura + 71;
	campo2->y = (ALTURA_TELA / 2) - (campo2->altura / 2);

	//Objeto* campo2;
	//campo2 = (Objeto*)malloc(sizeof(Objeto));
	//campo2->bitmap = al_load_bitmap("Imgs/campo2.png");
	//campo2->altura = 70;
	//campo2->largura = 400;
	//campo2->x = (LARGURA_TELA / 2);
	//campo2->y = (ALTURA_TELA / 2) - (campo2->altura / 2);

	Objeto* campo3;
	campo3 = (Objeto*)malloc(sizeof(Objeto));
	campo3->bitmap = al_load_bitmap("Imgs/slide6.png");
	campo3->altura = 250;
	campo3->largura = 500;
	campo3->x = (LARGURA_TELA / 2);
	campo3->y = (ALTURA_TELA / 2) - (campo3->altura / 2);
	
	Objeto* xis;
	xis = (Objeto*)malloc(sizeof(Objeto));
	xis->bitmap = al_load_bitmap("Imgs/xis.png");
	xis->altura = 250;
	xis->largura = 500;
	xis->x = (LARGURA_TELA / 2);
	xis->y = (ALTURA_TELA / 4 * 1.5) - (xis->altura / 2);


	Objeto* igual;
	igual = (Objeto*)malloc(sizeof(Objeto));
	igual->bitmap = al_load_bitmap("Imgs/igual.png");
	igual->altura = 250;
	igual->largura = 500;
	igual->x = (LARGURA_TELA / 2);
	igual->y = (ALTURA_TELA / 3 * 2) - (igual->altura / 2) - 40;

	Objeto* campo4;
	campo4 = (Objeto*)malloc(sizeof(Objeto));
	campo4->bitmap = al_load_bitmap("Imgs/slide6.png");
	campo4->altura = 250;
	campo4->largura = 500;
	campo4->x = (LARGURA_TELA / 2);
	campo4->y = (ALTURA_TELA / 3 * 2.2) - (campo4->altura / 2);

	Objeto* fundo;
	fundo = (Objeto*)malloc(sizeof(Objeto));
	fundo->bitmap = al_load_bitmap("Imgs/fundo.png");;
	fundo->altura = 720;
	fundo->largura = 1280;
	fundo->y = 0;
	fundo->x = 0;
	

	//ALLEGRO_BITMAP* background = al_load_bitmap("Imgs/fundo.png");
	//ALLEGRO_BITMAP* certo = al_load_bitmap("ArquivosAux/imagens/acerto.png");
	//ALLEGRO_BITMAP* errado = al_load_bitmap("ArquivosAux/imagens/errou.png");

	Objeto* setaDireita;
	setaDireita = (Objeto*)malloc(sizeof(Objeto));
	setaDireita->bitmap = al_load_bitmap("Imgs/direita.png");
	setaDireita->altura = 20;
	setaDireita->largura = 20;
	setaDireita->x = 1200;
	setaDireita->y = (ALTURA_TELA / 2);

	Objeto* setaBaixo;
	setaBaixo = (Objeto*)malloc(sizeof(Objeto));
	setaBaixo->altura = 20;
	setaBaixo->largura = 20;
	setaBaixo->x = 110 + (LARGURA_TELA / 2) - (setaBaixo->largura / 2);
	setaBaixo->y = ALTURA_TELA - setaBaixo->altura;
	setaBaixo->bitmap = al_load_bitmap("Imgs/direita.png");;
	
	
	Objeto* contaSeta;
	contaSeta = (Objeto*)malloc(sizeof(Objeto));
	contaSeta->altura = 250;
	contaSeta->largura = 500;
	contaSeta->x = (LARGURA_TELA / 2) - (contaSeta->largura / 2) + 20;
	contaSeta->y = (ALTURA_TELA / 3 * 1.3 + 20) - contaSeta->altura;
	contaSeta->bitmap = al_load_bitmap("Imgs/slide3.png");

	

	//Objeto* apagar;
	//apagar = (Objeto*)malloc(sizeof(Objeto));
	//apagar->bitmap = al_load_bitmap("Imgs/apagar.png");
	//apagar->largura = 50;
	//apagar->altura = 50;
	//apagar->x = (LARGURA_TELA / 2) + (campo->largura / 2);
	//apagar->y = (ALTURA_TELA / 2) - (apagar->altura / 2);


	/*Objeto* audio;
	audio = (Objeto*)malloc(sizeof(Objeto));
	audio->bitmap = NULL; 
	audio->altura = 50;
	audio->largura = 50;
	audio->x = 550;
	audio->y = 535;

	ALLEGRO_BITMAP * comAudio = al_load_bitmap("Imgs/comaudio.png");
	ALLEGRO_BITMAP * semAudio = al_load_bitmap("Imgs/semaudio.png");

	audio->bitmap = comAudio;*/

	//ALLEGRO_BITMAP* logo = NULL;

	//ALLEGRO_SAMPLE* musicaon = NULL;
	//ALLEGRO_SAMPLE* musicaoff = NULL;

	//ALLEGRO_SAMPLE* sampleVoltar = NULL;
	//ALLEGRO_AUDIO_STREAM* musica = NULL;
	//ALLEGRO_SAMPLE* musicaFundo = NULL;
	//ALLEGRO_SAMPLE* erro = NULL;
	//ALLEGRO_SAMPLE* botaosample = NULL;

	enigma = al_load_font("ArquivosAux/fonts/Kindergarten.ttf", 60, 0);
	digitado = al_load_font("ArquivosAux/fonts/Kindergarten.ttf", 60, 0);



	//logo = al_load_bitmap("ArquivosAux/imagens/logo.png");

	//musicaoff = al_load_sample("ArquivosAux/sounds/desligada.ogg");
	//musicaon = al_load_sample("ArquivosAux/sounds/ligada.ogg");
	//musica = al_load_sample("ArquivosAux/sounds/musicafundo.ogg");
	//musica = al_load_audio_stream("ArquivosAux/sounds/musicafundo.ogg", 4, 1024);
	//al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
	//al_set_audio_stream_playmode(musica, ALLEGRO_PLAYMODE_LOOP);

	//musicaFundo = al_load_sample("ArquivosAux/sounds/musicafundo.ogg");
	//botaosample = al_load_sample("ArquivosAux/sounds/click.ogg");
	//sampleVoltar = al_load_sample("ArquivosAux/sounds/arrow_hit.ogg");


	al_set_window_title(janela, "Ink Escape - Pagina Inicial");
	bool btnAudio = true;

	enigmaStr* enigma1;
	enigma1 = (enigmaStr*)malloc(sizeof(enigmaStr));
	enigma1->fonte = enigma;
	enigma1->enigmaCerto = "0110";
	enigma1->acertou = false;
	enigma1->verCampo = 1;
	char arrEnigma1[10] = "";


	enigmaStr* enigma2;
	enigma2 = (enigmaStr*)malloc(sizeof(enigmaStr));
	enigma2->fonte = enigma;
	enigma2->enigmaCerto = "0110";
	enigma2->acertou = false;
	enigma2->verCampo = 2;
	char arrEnigma2[10] = "";

	enigmaStr* enigma3;
	enigma3 = (enigmaStr*)malloc(sizeof(enigmaStr));
	enigma3->fonte = enigma;
	enigma3->enigmaCerto = "0100";
	enigma3->acertou = false;
	enigma3->verCampo = 3;
	char arrEnigma3[10] = "";
	
	enigmaStr* enigma4;
	enigma4 = (enigmaStr*)malloc(sizeof(enigmaStr));
	enigma4->fonte = enigma;
	enigma4->enigmaCerto = "00011000";
	enigma4->acertou = false;
	enigma4->verCampo = 4;
	char arrEnigma4[10] = "";


	int pos;
	int verCampo = 0;



	int cor[4];
	while (!sair)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(fila_eventos, &evento);
		al_set_target_bitmap(al_get_backbuffer(janela));
		al_clear_to_color(al_map_rgb(0, 0, 0));

		if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{

			/*if (IsInside(evento.mouse.x, evento.mouse.y, audio)) {
				btnAudio = !btnAudio;
				if (!btnAudio)
				{
					audio->bitmap = semAudio;
					al_set_audio_stream_gain(musica, 0.0);
					al_play_sample(musicaoff, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

				}
				else
				{
					audio->bitmap = comAudio;
					al_set_audio_stream_gain(musica, 1.0);
					al_draw_bitmap(audio->bitmap, audio->x, audio->y, 0);
				}

			}*/
			if (IsInside(evento.mouse.x, evento.mouse.y, setaDireita)) {
				prog->proximaSala = 2;
				//return;
				sair = true;
			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, postIt4) && !prog->Inventario[0])
			{
				prog->Itens[prog->inventCount] = postIt4;
				prog->Inventario[prog->inventCount] = 1;
				prog->inventCount++;
			}
			//else if (IsInside(evento.mouse.x, evento.mouse.y, setaBaixo)) {
			//	prog->proximaSala = 3;
			//	//return;
			//	sair = true;
			//}
			else if (IsInside(evento.mouse.x, evento.mouse.y, campo1))
			{
				verCampo = 1;
				cor[0] = 255;
				cor[1] = 0;
				cor[2] = 0;
				cor[3] = 0;

			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, campo2))
			{
				verCampo = 2;
				cor[0] = 0;
				cor[1] = 255;
				cor[2] = 0;
				cor[3] = 0;
			}
			else if(IsInside(evento.mouse.x, evento.mouse.y, campo3))
			{
				verCampo = 3;
				cor[0] = 0;
				cor[1] = 0;
				cor[2] = 255;
				cor[3] = 0;
			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, campo4))
			{
				verCampo = 4;
				cor[0] = 0;
				cor[1] = 0;
				cor[2] = 0;
				cor[3] = 255;
			}
			else {
				cor[0] = 0;
				cor[1] = 0;
				cor[2] = 0;
				cor[3] = 0;
			}


		}
		if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {
			 if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER)
			{
				 if (strncmp(enigma1->enigmaCerto, arrEnigma1, 5) == 0 && strncmp(enigma2->enigmaCerto, arrEnigma2, 5) == 0 && strncmp(enigma3->enigmaCerto, arrEnigma3, 5) == 0 && strncmp(enigma4->enigmaCerto, arrEnigma4, 9) == 0) {

					enigma1->acertou = true;
					enigma2->acertou = true;
					enigma3->acertou = true;
					enigma4->acertou = true;
					prog->Salas[1] = 1;
					postIt4->x = (LARGURA_TELA / 2) - (postIt4->largura / 2);
					postIt4->y = ALTURA_TELA - postIt4->altura;
					//fundo->bitmap = certo;
					//al_play_sample(acerto, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
			}
			 else if (evento.keyboard.keycode == ALLEGRO_KEY_F1) {
				 enigma1->acertou = true;
				 enigma2->acertou = true;
				 enigma3->acertou = true;
				 enigma4->acertou = true;
				 prog->Salas[1] = 1;
				 prog->Salas[2] = 1;
				 prog->Salas[10] = 1;
				 postIt4->x = (LARGURA_TELA / 2) - (postIt4->largura / 2);
				 postIt4->y = ALTURA_TELA - postIt4->altura;
			 }
			 else {
				if (verCampo == 1)
				{
					digitarCampo(enigma1, arrEnigma1, evento, sair, prog);

				}
				else if (verCampo == 2)
				{
					digitarCampo(enigma2, arrEnigma2, evento, sair, prog);

				}
				else if(verCampo == 3)
				{
					digitarCampo(enigma3, arrEnigma3, evento, sair, prog);
				}
				else if (verCampo == 4)
				{
					digitarCampo(enigma4, arrEnigma4, evento, sair, prog);
				}
			 }
		}


		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			sair = true;
			prog->Gameover = true;
		}

	

			al_draw_bitmap(fundo->bitmap, fundo->x, fundo->y, 0);
			//al_draw_bitmap(apagar->bitmap, apagar->x, apagar->y, 0);
			al_draw_bitmap(campo1->bitmap, campo1->x, campo1->y, 0);
			//al_draw_bitmap(campo2->bitmap, campo2->x, campo2->y, 0);
			al_draw_bitmap(campo3->bitmap, campo3->x, campo3->y, 0);
			al_draw_bitmap(campo4->bitmap, campo4->x, campo4->y, 0);
			al_draw_bitmap(igual->bitmap, igual->x, igual->y, 0);
			al_draw_bitmap(conta1->bitmap, conta1->x, conta1->y, 0);
			al_draw_bitmap(conta2->bitmap, conta2->x, conta2->y, 0);
			al_draw_bitmap(xis->bitmap, xis->x, xis->y, 0);
			al_draw_bitmap(contaSeta->bitmap, contaSeta->x, contaSeta->y, 0);
			al_draw_bitmap(setaDireita->bitmap, setaDireita->x, setaDireita->y, 0);
			
			//al_draw_bitmap(quadrado->bitmap, quadrado->x, quadrado->y, 0);
		if (prog->Salas[1] == 1) {
			//al_draw_text(enigma, al_map_rgb(0,0,0), 170, (ALTURA_TELA / 3) + 100, ALLEGRO_ALIGN_LEFT, enigma2->enigmaText);
			
			al_draw_text(enigma, al_map_rgb(0, 0, 0), campo1->x + 95, (ALTURA_TELA / 4) - 20, 0, "0110");
			al_draw_text(enigma, al_map_rgb(0, 0, 0), campo2->x + campo2->x - 25, (ALTURA_TELA / 3) + 100, 0, "0110");
			al_draw_text(enigma, al_map_rgb(0, 0, 0), campo3->x + 95, (ALTURA_TELA / 3) + 100, 0, "0100");
			al_draw_text(enigma, al_map_rgb(0, 0, 0), campo4->x + 95, (ALTURA_TELA / 3) + 270, 0, "00011000");

		}
		else {
			al_draw_text(enigma, al_map_rgb(cor[0], 0, 0), campo1->x + 95, (ALTURA_TELA / 4) - 20, 0, arrEnigma1);
			al_draw_text(enigma, al_map_rgb(cor[1], 0, 0), campo2->x + campo2->x - 25, (ALTURA_TELA / 3) + 100, 0, arrEnigma2);
			al_draw_text(enigma, al_map_rgb(cor[2], 0, 0), campo3->x + 95, (ALTURA_TELA / 3) + 100, 0, arrEnigma3);
			al_draw_text(enigma, al_map_rgb(cor[3], 0, 0), campo4->x + 95, (ALTURA_TELA / 3) + 270, 0, arrEnigma4);
		}

		if (prog->Salas[4] && !prog->Inventario[0])//arrumar
		{
			al_draw_bitmap(postIt4->bitmap, postIt4->x, postIt4->y, 0);
		}
		caregaInventario(prog);
		al_flip_display();
	}


	/*al_destroy_bitmap(certo);
	al_destroy_bitmap(errado);
	al_destroy_bitmap(background);*/
	//al_destroy_audio_stream(musica);
	//al_destroy_sample(musicaFundo);
	//free(apagar);
	//free(audio);
	//al_destroy_bitmap(setaBaixo->bitmap);
	al_destroy_bitmap(setaDireita->bitmap);
	al_destroy_bitmap(conta1->bitmap);
	al_destroy_bitmap(conta2->bitmap);
	al_destroy_bitmap(campo1->bitmap);
	al_destroy_bitmap(campo2->bitmap);
	al_destroy_bitmap(campo3->bitmap);
	al_destroy_bitmap(campo4->bitmap);
	al_destroy_bitmap(xis->bitmap);
	al_destroy_bitmap(igual->bitmap);
	al_destroy_bitmap(contaSeta->bitmap);

	al_destroy_display(display);
	
	al_destroy_font(enigma);
	al_destroy_font(digitado);
	
	free(campo1);
	free(campo2);
	free(campo3);
	free(campo4);
	free(xis);
	free(igual);
	free(contaSeta);
	free(enigma1);
	free(enigma2);
	free(enigma3);
	free(enigma4);
	free(fundo);
	free(conta1);
	free(conta2);
	//free(setaBaixo);
	free(setaDireita);

	//system("pause");

	return 0;
}

int digitarCampo(enigmaStr* enigma, char arrEnigma[], ALLEGRO_EVENT evento, bool sair, Progresso* prog) {
	char letra[5] = "";

	if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && (enigma->acertou == false)) {
		//backspace, volta uma posicao no texto
		if (arrEnigma[strlen(arrEnigma) - 1] > -1)
		{
			arrEnigma[strlen(arrEnigma) - 1] = '\0';
		}

	}
	
	if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
	{
		sair = true;
		prog->Gameover = true;
	}
	else
	{

		if ((evento.keyboard.keycode == ALLEGRO_KEY_0 || evento.keyboard.keycode == ALLEGRO_KEY_1 || evento.keyboard.keycode == ALLEGRO_KEY_PAD_0 || evento.keyboard.keycode == ALLEGRO_KEY_PAD_1) && (enigma->acertou == false)) {
			if (enigma->verCampo == 4) {
				if ((strlen(arrEnigma)) < 8) {
					int uni = evento.keyboard.unichar;
					letra[0] = (char)uni;
					arrEnigma[strlen(arrEnigma)] = letra[0];
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