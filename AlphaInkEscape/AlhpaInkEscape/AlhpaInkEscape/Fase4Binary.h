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


int JogarFase4Binary(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* prog) {
	//variaveis
	bool sair = false;
	//ponteiros
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_FONT* enigma = NULL;
	ALLEGRO_FONT* digitado = NULL;
	ALLEGRO_FONT* fonte = NULL;


	Objeto* apagar;
	apagar = (Objeto*)malloc(sizeof(Objeto));
	apagar->bitmap = al_load_bitmap("ArquivosAux/imagens/apagar.png");
	apagar->largura = 50;
	apagar->altura = 50;
	apagar->x = 600;
	apagar->y = 257;

	Objeto* campo;
	campo = (Objeto*)malloc(sizeof(Objeto));
	campo->bitmap = al_load_bitmap("ArquivosAux/imagens/campo2.png");
	campo->altura = 70;
	campo->largura = 400;
	campo->x = (LARGURA_TELA / 2) - (campo->largura / 2);
	campo->y = (ALTURA_TELA / 2) - (campo->altura / 2);

	Objeto* fundo;
	fundo = (Objeto*)malloc(sizeof(Objeto));
	fundo->bitmap = NULL;
	fundo->altura = 720;
	fundo->largura = 1280;
	fundo->y = 0;
	fundo->x = 0;

	ALLEGRO_BITMAP* background = al_load_bitmap("ArquivosAux/imagens/background2.png");
	ALLEGRO_BITMAP* certo = al_load_bitmap("ArquivosAux/imagens/acerto.png");
	ALLEGRO_BITMAP* errado = al_load_bitmap("ArquivosAux/imagens/errou.png");
	
	/*Objeto* errado;
	errado = (Objeto*)malloc(sizeof(Objeto));
	errado->bitmap = al_load_bitmap("ArquivosAux/imagens/errou.png");
	errado->altura = 720;
	errado->largura = 1280;
	errado->y = 0;
	errado->x = 0;*/

	Objeto* audio;
	audio = (Objeto*)malloc(sizeof(Objeto));
	audio->bitmap = al_load_bitmap("ArquivosAux/imagens/comaudio.png");
	audio->altura = 50;
	audio->largura = 50;
	audio->x = 550;
	audio->y = 535;

	Objeto* semAudio;
	semAudio = (Objeto*)malloc(sizeof(Objeto));
	semAudio->bitmap = al_load_bitmap("ArquivosAux/imagens/semaudio.png");
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

	//definir valores
	//display = al_create_display(800, 600);
	enigma = al_load_font("ArquivosAux/fonts/Kindergarten.ttf", 30, 0);
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


	al_register_event_source(fila_eventos, al_get_display_event_source(janela));
	al_register_event_source(fila_eventos, al_get_mouse_event_source());
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());
	al_set_window_title(janela, "Ink Escape - Pagina Inicial");
	bool btnAudio = true;
	char enigmaText[] = "0100";
	char enigmaText2[] = "0010";
	char enigmaCerto[] = "0110";
	char digitadoText[50] = "";
	char letra[2];
	int pos;

	fundo->bitmap = background;
	while (!sair)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(fila_eventos, &evento);
		al_set_target_bitmap(al_get_backbuffer(janela));
		al_clear_to_color(al_map_rgb(0,0,0));		

		if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{

			if (IsInside(evento.mouse.x, evento.mouse.y, *audio)) {
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
			else if (IsInside(evento.mouse.x, evento.mouse.y, *apagar)) {
					al_draw_bitmap(fundo->bitmap, fundo->x, fundo->y, 0);
					for (int j = strlen(digitadoText); 0 <= j; j--)
					{
						digitadoText[j] = 0;
					}
					fundo->bitmap = background;
			}

		}
		if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {
			
				if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
					//backspace, volta uma posicao no texto
					if (digitadoText[strlen(digitadoText) - 1] > -1)
					{
						digitadoText[strlen(digitadoText) - 1] = '\0';
					}

				}
				else if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER)
				{
					if (strncmp(enigmaCerto, digitadoText, 6) == 0) {

						fundo->bitmap = certo;
						//al_play_sample(acerto, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					}
					else {
						fundo->bitmap = errado;
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
						if ((strlen(digitadoText)) < 10) {
							pos = strlen(digitadoText);
							*letra = evento.keyboard.unichar;
							digitadoText[strlen(digitadoText)] = letra[0];
						}
					}
				}
			
			//al_flip_display();
		}

		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			sair = true;
			prog->Gameover = true;
		}

		
		al_draw_bitmap(fundo->bitmap, fundo->x, fundo->y, 0);
		al_draw_bitmap(apagar->bitmap, apagar->x, apagar->y, 0);
		al_draw_bitmap(campo->bitmap, campo->x, campo->y, 0);
		al_draw_text(digitado, al_map_rgb(0, 0, 0), campo->x , campo->y, 0, digitadoText);
		al_draw_text(enigma, al_map_rgb(0, 0, 0), 40, 145, ALLEGRO_ALIGN_LEFT, enigmaText);
		al_draw_text(enigma, al_map_rgb(0, 0, 0), 40, 175, ALLEGRO_ALIGN_LEFT, enigmaText2);

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
	al_uninstall_keyboard();
	al_uninstall_mouse();
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