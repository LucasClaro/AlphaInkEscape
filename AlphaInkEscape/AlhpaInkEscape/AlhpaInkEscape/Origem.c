#include <stdio.h>
// Inclui o arquivo de cabe�alho da biblioteca Allegro 5
#include <allegro5/allegro.h>
// Inclui o cabe�alho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
// Inclui a coisa do mouse
#include <allegro5/allegro_native_dialog.h>

#include "Funcoes.h"
#include "Struct.h"
#include "FaseController.h"
#include <allegro5/allegro_audio.h>

int main(void) {
	ALLEGRO_DISPLAY* janela = NULL;

	//declara a fila de eventos
	ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;

	if (!al_init()) {
		fprintf(stderr, "Falha ao iniciar Allegro\n");
		return -1;
	}

	// Inicializa o add-on para utiliza��o de imagens e fontes

	al_init_image_addon();

	al_init_font_addon();

	al_init_ttf_addon();

	al_install_audio();

	al_init_acodec_addon();

	al_reserve_samples(6);

	al_install_mouse();

	al_install_keyboard();

	/*ALLEGRO_DISPLAY_MODE mode;
	al_get_display_mode(al_get_num_display_modes()-1, &mode);*/

	// Cria a nossa janela
	janela = al_create_display(LARGURA_TELA, ALTURA_TELA);

	if (!janela) {
		fprintf(stderr, "Falha ao iniciar janela\n");
		return -1;
	}
	// Configura o t�tulo da janela
	al_set_window_title(janela, "Ink Escape Alhpa");

	// Cria a Fila de eventos
	fila_eventos = al_create_event_queue();
	if (!fila_eventos) {
		fprintf(stderr, "Falha ao criar fila de evento\n");
		al_destroy_display(janela);

		return -1;
	}

	// Torna apto o uso de mouse na aplica��o
	if (!al_install_mouse()) {
		fprintf(stderr, "Falha ao iniciar o mouse\n");
		al_destroy_display(janela);
		al_destroy_event_queue(fila_eventos);

		return -1;
	}
	// Atribui o cursor padr�o do sistema para ser usado
	if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)) {
		fprintf(stderr, "Falha ao atribur ponteiro ao mouse\n");
		al_destroy_display(janela);

		return -1;
	}

	// Registra eventos da janela em fila_eventos
	al_register_event_source(fila_eventos, al_get_display_event_source(janela));
	// Registra eventos da janela em fila_eventos
	al_register_event_source(fila_eventos, al_get_mouse_event_source());

	//regitra teclado
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());

	// Preenche o objeto de progresso
	Progresso progresso;
	progresso.proximaSala = 6;
	progresso.Gameover = 0;
	progresso.Salas[0] = 0;
	progresso.Salas[1] = 0;
	progresso.Salas[2] = 0;
	progresso.Salas[3] = 0;
	progresso.Salas[4] = 0;
	progresso.Salas[5] = 0;
	progresso.Salas[6] = 0;
	progresso.Salas[7] = 0;
	progresso.Salas[8] = 0;
	progresso.Salas[9] = 0;
	progresso.Salas[10] = 0;
	progresso.Salas[11] = 0;
	progresso.Salas[13] = 0;
	progresso.Salas[14] = 0;
	progresso.Salas[15] = 0;

	progresso.Inventario[0] = 0;
	progresso.Inventario[1] = 0;
	progresso.Inventario[2] = 0;
	progresso.Inventario[3] = 0;
	progresso.Inventario[4] = 0;
	progresso.Inventario[5] = 0;
	progresso.Inventario[6] = 0;

	progresso.Itens[2] = NULL;
	progresso.Itens[3] = NULL;
	
	progresso.inventCount = 0;

	progresso.inventClick[0] = 0;
	progresso.inventClick[1] = 0;
	progresso.inventClick[2] = 0;
	progresso.inventClick[3] = 0;
	progresso.inventClick[4] = 0;
	progresso.inventClick[5] = 0;
	progresso.inventClick[6] = 0;

	progresso.linhaInGame = 0;
	progresso.cenario = (Cenario*)malloc(sizeof(Cenario));
	progresso.cenario->somSeta = al_load_sample("sounds/pagina.ogg");
	progresso.cenario->setaBaixo = al_load_bitmap("Imgs/baixo.png");
	progresso.cenario->setaCima = al_load_bitmap("Imgs/cima.png");
	progresso.cenario->setaEsquerda = al_load_bitmap("Imgs/esquerda.png");
	progresso.cenario->setaDireita = al_load_bitmap("Imgs/direita.png");
	progresso.cenario->cadeado = al_load_bitmap("Imgs/cadeado.png");
	progresso.cenario->background = al_load_bitmap("Imgs/fundo.png");
	progresso.cenario->semSom = al_load_bitmap("Imgs/semaudio.png");
	progresso.cenario->comSom = al_load_bitmap("Imgs/comaudio.png");


	progresso.cenario->btnSom = (Objeto*)malloc(sizeof(Objeto));
	progresso.cenario->btnSom->altura = 50;
	progresso.cenario->btnSom->largura = 50;
	progresso.cenario->btnSom->x = 500;
	progresso.cenario->btnSom->y = 500;
	progresso.cenario->btnSom->bitmap = progresso.cenario->comSom;
	progresso.cenario->musica = al_load_audio_stream("sounds/musica.ogg", 4, 1024);


	al_attach_audio_stream_to_mixer(progresso.cenario->musica, al_get_default_mixer());
	al_set_audio_stream_playmode(progresso.cenario->musica, ALLEGRO_PLAYMODE_LOOP);
	

	loadFotoInvent();
	// Cria o ponteiro para progresso que ser� mandado para o resto do programa
	Progresso* prog = &progresso;
	// Looping central do jogo

	while (!prog->Gameover)
	{
		selecionaFase(janela, fila_eventos, prog);
	}

	al_destroy_event_queue(fila_eventos);
	al_destroy_display(janela);
}
