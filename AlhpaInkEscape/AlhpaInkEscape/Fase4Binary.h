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
	ALLEGRO_BITMAP* btnAbrirCampo = NULL;
	ALLEGRO_BITMAP* apagar = NULL;
	ALLEGRO_BITMAP* campo = NULL;
	ALLEGRO_BITMAP* voltar = NULL;
	ALLEGRO_BITMAP* fundo = NULL;
	ALLEGRO_BITMAP* fundo2 = NULL;
	ALLEGRO_BITMAP* logo = NULL;
	ALLEGRO_BITMAP* certo = NULL;
	ALLEGRO_BITMAP* errado = NULL;
	ALLEGRO_BITMAP* audio = NULL;
	ALLEGRO_BITMAP* semaudio = NULL;

	ALLEGRO_SAMPLE* musicaon = NULL;
	ALLEGRO_SAMPLE* musicaoff = NULL;

	ALLEGRO_SAMPLE* sampleVoltar = NULL;
	ALLEGRO_AUDIO_STREAM* musica = NULL;
	ALLEGRO_SAMPLE* musicaFundo = NULL;
	ALLEGRO_SAMPLE* acerto = NULL;
	ALLEGRO_SAMPLE* erro = NULL;
	ALLEGRO_SAMPLE* botaosample = NULL;
	ALLEGRO_EVENT_QUEUE* eventQueue = NULL;


	//inicializar
	/*inicializar();*/
	//al_init();

	al_init_image_addon();

	al_init_font_addon();

	al_init_ttf_addon();

	al_install_audio();

	al_init_acodec_addon();

	al_reserve_samples(6);

	al_install_mouse();

	al_install_keyboard();


	//definir valores
	//display = al_create_display(800, 600);
	enigma = al_load_font("ArquivosAux/fonts/Kindergarten.ttf", 30, 0);
	digitado = al_load_font("ArquivosAux/fonts/Kindergarten.ttf", 80, 0);

	btnAbrirCampo = al_create_bitmap(400, 70);
	al_set_target_bitmap(btnAbrirCampo);
	al_clear_to_color(al_map_rgb(155, 155, 155));


	campo = al_create_bitmap(400, 70);
	al_set_target_bitmap(campo);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	logo = al_load_bitmap("ArquivosAux/imagens/logo.png");



	fundo = al_load_bitmap("ArquivosAux/imagens/background.png");
	campo = al_load_bitmap("ArquivosAux/imagens/campo2.png");
	btnAbrirCampo = al_load_bitmap("ArquivosAux/imagens/botao.png");
	fundo2 = al_load_bitmap("ArquivosAux/imagens/background2.png");

	voltar = al_load_bitmap("ArquivosAux/imagens/voltar.png");
	apagar = al_load_bitmap("ArquivosAux/imagens/apagar.png");


	musicaoff = al_load_sample("ArquivosAux/sounds/desligada.ogg");
	musicaon = al_load_sample("ArquivosAux/sounds/ligada.ogg");
	musica = al_load_sample("ArquivosAux/sounds/musicafundo.ogg");
	musica = al_load_audio_stream("ArquivosAux/sounds/musicafundo.ogg", 4, 1024);
	al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
	al_set_audio_stream_playmode(musica, ALLEGRO_PLAYMODE_LOOP);

	musicaFundo = al_load_sample("ArquivosAux/sounds/musicafundo.ogg");
	botaosample = al_load_sample("ArquivosAux/sounds/click.ogg");
	sampleVoltar = al_load_sample("ArquivosAux/sounds/arrow_hit.ogg");
	acerto = al_load_sample("ArquivosAux/sounds/acertou.ogg");
	erro = al_load_sample("ArquivosAux/sounds/errou.ogg");

	audio = al_load_bitmap("ArquivosAux/imagens/comaudio.png");

	

	eventQueue = al_create_event_queue();
	al_register_event_source(eventQueue, al_get_display_event_source(janela));
	al_register_event_source(eventQueue, al_get_mouse_event_source());
	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	al_set_window_title(janela, "Ink Escape - Pagina Inicial");
	if (btnAbrirCampo) {

	}
	else {

	}
	bool btnJogar = false;
	bool btnAudio = true;
	/*char enigmaText[] = "01110100 01100101 01110011 01110100 01100101 00001010";*/
	char enigmaText[] = "0100";
	char enigmaText2[] = "0010";
	char enigmaCerto[] = "0110";
	char digitadoText[50] = "";
	char letra[2];
	int pos;
	int corR = 0;
	int corG = 0;
	int corB = 0;

	while (!sair)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(eventQueue, &evento);


		al_set_target_bitmap(al_get_backbuffer(janela));
		al_clear_to_color(al_map_rgb(corR, corG, corB));
		al_draw_bitmap(fundo, 0, 0, 0);

		if (!btnJogar)
		{
			/*al_draw_text*/
			al_draw_bitmap(btnAbrirCampo, (800 / 2) - (400 / 2), (600 / 2) - (70 / 2), 0);

		}
		else
		{
			al_draw_bitmap(fundo2, 0, 0, 0);
			al_draw_bitmap(voltar, 25, 25, 0);
			al_draw_bitmap(apagar, 600, 257, 0);
			al_draw_bitmap(campo, (800 / 2) - (400 / 2), (600 / 2) - (100 / 2), 0);
			al_draw_text(digitado, al_map_rgb(0, 0, 0), (800 / 2) - (400 / 2), (600 / 2) - (100 / 2), 0, digitadoText);
			al_draw_text(enigma, al_map_rgb(0, 0, 0), 40, 145, ALLEGRO_ALIGN_LEFT, enigmaText);
			al_draw_text(enigma, al_map_rgb(0, 0, 0), 40, 175, ALLEGRO_ALIGN_LEFT, enigmaText2);

		}
		al_draw_bitmap(audio, 550, 535, 0);

		al_set_display_icon(janela, logo);
		al_flip_display();



		if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (evento.mouse.x >= (800 / 2) - (400 / 2) && evento.mouse.x <= (800 / 2) - (400 / 2) + 400 && evento.mouse.y >= (600 / 2) - (70 / 2) && evento.mouse.y <= (600 / 2) - (70 / 2) + 70)
			{

				if (!btnJogar) {
					btnJogar = !btnJogar;
					al_play_sample(botaosample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					al_set_window_title(janela, "Ink Escape - Pergunta 1");


					for (int j = strlen(digitadoText); 0 <= j; j--)
					{
						digitadoText[j] = 0;
					}



				}
				al_flip_display();

			}
			else if (evento.mouse.x >= 25 && evento.mouse.x <= 75 && evento.mouse.y >= 25 && evento.mouse.y <= 75) {

				if (btnJogar) {
					btnJogar = !btnJogar;
					al_play_sample(sampleVoltar, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					fundo2 = al_load_bitmap("ArquivosAux/imagens/background2.png");
					al_set_window_title(janela, "Ink Escape - Pagina Inicial");
				}
			}

			else if (evento.mouse.x >= 550 && evento.mouse.x <= 600 && evento.mouse.y >= 535 && evento.mouse.y <= 585) {
				btnAudio = !btnAudio;
				if (btnAudio)
				{
					al_set_audio_stream_gain(musica, 0.0);
					audio = al_load_bitmap("ArquivosAux/imagens/semaudio.png");
					al_play_sample(musicaoff, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

				}
				else
				{
					al_set_audio_stream_gain(musica, 1.0);
					al_play_sample(musicaon, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					audio = al_load_bitmap("ArquivosAux/imagens/comaudio.png");
				}

			}
			else if (evento.mouse.x >= 600 && evento.mouse.x <= 650 && evento.mouse.y >= 250 && evento.mouse.y <= 300) {

				if (btnJogar)
				{
					fundo2 = al_load_bitmap("ArquivosAux/imagens/background2.png");
					for (int j = strlen(digitadoText); 0 <= j; j--)
					{
						digitadoText[j] = 0;
					}

				}
			}

		}
		if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {
			if (btnJogar) {
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

						fundo2 = al_load_bitmap("ArquivosAux/imagens/acerto.png");
						al_play_sample(acerto, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					}
					else {
						fundo2 = al_load_bitmap("ArquivosAux/imagens/errou.png");
						al_play_sample(erro, 15.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

					}
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
			}
			//al_flip_display();
		}

		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			sair = true;
		}
	}

	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_sample(musicaFundo);
	al_destroy_sample(acerto);
	al_destroy_sample(erro);
	al_destroy_sample(sampleVoltar);
	al_destroy_event_queue(eventQueue);
	al_destroy_font(enigma);
	al_destroy_font(digitado);
	al_destroy_bitmap(btnAbrirCampo);
	al_destroy_bitmap(campo);
	al_destroy_bitmap(fundo);
	al_destroy_bitmap(fundo2);
	al_destroy_display(display);
	al_destroy_audio_stream(musica);
	system("pause");

	return 0;
}