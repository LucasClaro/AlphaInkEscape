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

//}int digitarCampo(char *certo, char *digitado, ALLEGRO_EVENT evento, bool sair, Progresso* prog) {
//	char letra[1];
//
//		if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
//			//backspace, volta uma posicao no texto
//			if (digitado[strlen(digitado) - 1] > -1)
//			{
//				digitado[strlen(digitado) - 1] = '\0';
//			}
//
//		}
//		else if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER)
//		{
//			if (strncmp(certo, digitado, 9) == 0) {
//
//				//fundo->bitmap = certo;
//				//al_play_sample(acerto, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
//			}
//			else {
//				//fundo->bitmap = errado;
//				//al_play_sample(erro, 15.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
//			}
//		}
//		if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
//		{
//			sair = true;
//			prog->Gameover = true;
//		}
//		else
//		{
//
//			if (evento.keyboard.keycode == ALLEGRO_KEY_0 || evento.keyboard.keycode == ALLEGRO_KEY_1 || evento.keyboard.keycode == ALLEGRO_KEY_PAD_0 || evento.keyboard.keycode == ALLEGRO_KEY_PAD_1) {
//				if ((strlen(digitado)) < 10) {
//					//*letra = evento.keyboard.unichar;
//					int uni = evento.keyboard.unichar;
//					digitado[strlen(digitado)] = uni;
//
//				}
//			}
//		}
//	
//	
//	
//	return 0;
//}
typedef struct EnigmaStr
{
	ALLEGRO_FONT* fonte;
	char* enigmaText;
	char* enigmaCerto;
	char* digitado;
	int verCampo;
} enigmaStr;

int JogarFase4Binary(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* prog) {
	//variaveis
	bool sair = false;
	//ponteiros
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_FONT* enigma = NULL;
	ALLEGRO_FONT* digitado = NULL;
	ALLEGRO_FONT* fonte = NULL;


	Objeto* campo;
	campo = (Objeto*)malloc(sizeof(Objeto));
	campo->bitmap = al_load_bitmap("Imgs/campo2.png");
	campo->altura = 70;
	campo->largura = 400;
	campo->x = (LARGURA_TELA / 2);
	campo->y = (ALTURA_TELA / 4) - (campo->altura / 2);
		
	Objeto* campo2;
	campo2 = (Objeto*)malloc(sizeof(Objeto));
	campo2->bitmap = al_load_bitmap("Imgs/campo2.png");
	campo2->altura = 70;
	campo2->largura = 400;
	campo2->x = (LARGURA_TELA / 2);
	campo2->y = (ALTURA_TELA / 2) - (campo2->altura / 2);

	Objeto* fundo;
	fundo = (Objeto*)malloc(sizeof(Objeto));
	fundo->bitmap = NULL;
	fundo->altura = 720;
	fundo->largura = 1280;
	fundo->y = 0;
	fundo->x = 0;


	ALLEGRO_BITMAP* background = al_load_bitmap("Imgs/fundo.png");
	ALLEGRO_BITMAP* certo = al_load_bitmap("ArquivosAux/imagens/acerto.png");
	ALLEGRO_BITMAP* errado = al_load_bitmap("ArquivosAux/imagens/errou.png");
	
	Objeto* setaDireita;
	setaDireita = (Objeto*)malloc(sizeof(Objeto));
	setaDireita->bitmap = al_load_bitmap("Imgs/direita.png");
	setaDireita->altura = 20;
	setaDireita->largura = 20;
	setaDireita->x = 1200;
	setaDireita->y = (ALTURA_TELA / 2);

	Objeto* apagar;
	apagar = (Objeto*)malloc(sizeof(Objeto));
	apagar->bitmap = al_load_bitmap("Imgs/apagar.png");
	apagar->largura = 50;
	apagar->altura = 50;
	apagar->x = (LARGURA_TELA/2) + (campo->largura/2);
	apagar->y = (ALTURA_TELA/2) - (apagar->altura/2);



	Objeto* audio;
	audio = (Objeto*)malloc(sizeof(Objeto));
	audio->bitmap = al_load_bitmap("Imgs/comaudio.png");
	audio->altura = 50;
	audio->largura = 50;
	audio->x = 550;
	audio->y = 535;

	Objeto* semAudio;
	semAudio = (Objeto*)malloc(sizeof(Objeto));
	semAudio->bitmap = al_load_bitmap("Imgs/semaudio.png");
	semAudio->altura = 50;
	semAudio->largura = 50;
	semAudio->x = 550;
	semAudio->y = 535;
	
	


	ALLEGRO_BITMAP* logo = NULL;

	ALLEGRO_SAMPLE* musicaon = NULL;
	ALLEGRO_SAMPLE* musicaoff = NULL;

	ALLEGRO_SAMPLE* sampleVoltar = NULL;
	ALLEGRO_AUDIO_STREAM* musica = NULL;
	ALLEGRO_SAMPLE* musicaFundo = NULL;
	ALLEGRO_SAMPLE* erro = NULL;
	ALLEGRO_SAMPLE* botaosample = NULL;
	ALLEGRO_EVENT_QUEUE* eventQueue = NULL;

	enigma = al_load_font("ArquivosAux/fonts/Kindergarten.ttf", 90, 0);
	digitado = al_load_font("ArquivosAux/fonts/Kindergarten.ttf", 80, 0);



	logo = al_load_bitmap("ArquivosAux/imagens/logo.png");

	musicaoff = al_load_sample("ArquivosAux/sounds/desligada.ogg");
	musicaon = al_load_sample("ArquivosAux/sounds/ligada.ogg");
	musica = al_load_sample("ArquivosAux/sounds/musicafundo.ogg");
	musica = al_load_audio_stream("ArquivosAux/sounds/musicafundo.ogg", 4, 1024);
	al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
	al_set_audio_stream_playmode(musica, ALLEGRO_PLAYMODE_LOOP);

	musicaFundo = al_load_sample("ArquivosAux/sounds/musicafundo.ogg");
	botaosample = al_load_sample("ArquivosAux/sounds/click.ogg");
	sampleVoltar = al_load_sample("ArquivosAux/sounds/arrow_hit.ogg");

	
	al_set_window_title(janela, "Ink Escape - Pagina Inicial");
	bool btnAudio = true;

	enigmaStr* enigma1;
	enigma1 = (enigmaStr*)malloc(sizeof(enigmaStr));
	enigma1->fonte = enigma;
	enigma1->enigmaCerto = "0000 1000";
	enigma1->enigmaText = "0100 X 0010";
	enigma1->verCampo = 1;
	char arrEnigma1[10] = "";
	
	enigmaStr* enigma2;
	enigma2 = (enigmaStr*)malloc(sizeof(enigmaStr));
	enigma2->fonte = enigma;
	enigma2->enigmaCerto = "0001 1110";
	enigma2->enigmaText = "0110 X 0101";
	enigma2->verCampo = 2;
	char arrEnigma2[10] = "";

	
	int pos;
	int verCampo = 0;



	fundo->bitmap = background;
	while (!sair)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(fila_eventos, &evento);
		al_set_target_bitmap(al_get_backbuffer(janela));
		al_clear_to_color(al_map_rgb(0,0,0));		

		if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{

			if (IsInside(evento.mouse.x, evento.mouse.y, audio)) {
				btnAudio = !btnAudio;
				if (!btnAudio)
				{
					al_set_audio_stream_gain(musica, 0.0);
					al_play_sample(musicaoff, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

				}
				else
				{
					al_set_audio_stream_gain(musica, 1.0);
					al_draw_bitmap(audio->bitmap, audio->x, audio->y, 0);
				}

			}
			/*else if (IsInside(evento.mouse.x, evento.mouse.y, apagar)) {
					al_draw_bitmap(fundo->bitmap, fundo->x, fundo->y, 0);
					for (int j = strlen(digitadoText); 0 <= j; j--)
					{
						digitadoText[j] = 0;
					}
					fundo->bitmap = background;
			}*/
			else if (IsInside(evento.mouse.x, evento.mouse.y, setaDireita)) {
				prog->proximaSala = 1;
				//return;
				sair = true;
			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, campo))
			{
				verCampo = 1;
			}
			else if (IsInside(evento.mouse.x, evento.mouse.y, campo2))
			{
				verCampo = 2;
			}
			else {
				verCampo = 0;
			}
			

		}
		if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {			
			if (verCampo == 1)
			{
				digitarCampo(enigma1, arrEnigma1, evento, sair, prog);
				//digitarCampo(enigma1->enigmaCerto, enigma1->digitado, evento, sair, prog);

			}
			else if(verCampo == 2)
			{ 
				//digitarCampo(enigma2->enigmaCerto, enigma2->digitado, evento, sair, prog);
				digitarCampo(enigma2, arrEnigma2, evento, sair, prog);

			}
		}
			
		
		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			sair = true;
			prog->Gameover = true;
		}

		
		al_draw_bitmap(fundo->bitmap, fundo->x, fundo->y, 0);
		al_draw_bitmap(apagar->bitmap, apagar->x, apagar->y, 0);
		al_draw_bitmap(campo->bitmap, campo->x, campo->y, 0);
		al_draw_bitmap(campo2->bitmap, campo2->x, campo2->y, 0);
		al_draw_text(enigma, al_map_rgb(0, 0, 0), campo->x , (ALTURA_TELA / 4) - 10, 0, arrEnigma1);
		al_draw_text(enigma, al_map_rgb(0, 0, 0), campo->x , (ALTURA_TELA / 3) + 100, 0, arrEnigma2);
		al_draw_text(enigma, al_map_rgb(0, 0, 0), 170, (ALTURA_TELA/4) - 10, ALLEGRO_ALIGN_LEFT, enigma1->enigmaText);
		al_draw_text(enigma, al_map_rgb(0, 0, 0), 170, (ALTURA_TELA / 3) + 100, ALLEGRO_ALIGN_LEFT, enigma2->enigmaText);
		al_draw_bitmap(setaDireita->bitmap, setaDireita->x, setaDireita->y, 0);
		
		
		
		switch (btnAudio)
		{
		case true:
			al_draw_bitmap(audio->bitmap, audio->x, audio->y, 0);
			break;
		case false:
			al_draw_bitmap(semAudio->bitmap, semAudio->x, semAudio->y, 0);
			break;
		}

		al_flip_display();
	}


	al_destroy_bitmap(certo);
	al_destroy_bitmap(errado);
	al_destroy_bitmap(background);
	al_destroy_display(display);
	al_destroy_audio_stream(musica);
	al_destroy_sample(musicaFundo);
	al_destroy_font(enigma);
	al_destroy_font(digitado);

	free(apagar);
	free(campo);
	free(fundo);
	free(semAudio);
	free(audio);
	
	//system("pause");

	return 0;
}

int digitarCampo(enigmaStr* enigma, char arrEnigma[], ALLEGRO_EVENT evento, bool sair, Progresso* prog) {
	char letra[5] = "";
	if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
		//backspace, volta uma posicao no texto
		if (arrEnigma[strlen(arrEnigma) - 1] > -1)
		{
			arrEnigma[strlen(arrEnigma) - 1] = '\0';
		}

	}
	else if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER)
	{
		if (strncmp(enigma->enigmaCerto, arrEnigma, 9) == 0) {

			//fundo->bitmap = certo;
			//al_play_sample(acerto, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
		else {
			//fundo->bitmap = errado;
			//al_play_sample(erro, 15.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
	}
	if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
	{
		sair = true;
		prog->Gameover = true;
	}
	else
	{

		if (evento.keyboard.keycode == ALLEGRO_KEY_0 || evento.keyboard.keycode == ALLEGRO_KEY_1 || evento.keyboard.keycode == ALLEGRO_KEY_PAD_0 || evento.keyboard.keycode == ALLEGRO_KEY_PAD_1) {
			if ((strlen(arrEnigma)) < 10) {
				//printf("%c \n", arrEnigma);
				
				int uni = evento.keyboard.unichar;
				//printf("%c \n", uni);
				letra[0] = (char) uni;
				arrEnigma[strlen(arrEnigma)] = letra[0];
				//printf("%c == ", arrEnigma);

			}
		}
	}

	return 0;
}