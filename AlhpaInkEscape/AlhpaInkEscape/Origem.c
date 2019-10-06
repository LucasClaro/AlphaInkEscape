#include <stdio.h>
// Inclui o arquivo de cabeçalho da biblioteca Allegro 5
#include <allegro5/allegro.h>
// Inclui o cabeçalho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
// Inclui a coisa do mouse
#include <allegro5/allegro_native_dialog.h>

#include "Funcoes.h"
#include "Struct.h"
#include "FaseController.h"

int main(void) {
	ALLEGRO_DISPLAY* janela = NULL;

	//declara a fila de eventos
	ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;

	if (!al_init()) {
		fprintf(stderr, "Falha ao iniciar Allegro\n");
		return -1;
	}

	// Inicializa o add-on para utilização de imagens e fontes
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	// Cria a nossa janela
	janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
	if (!janela) {
		fprintf(stderr, "Falha ao iniciar janela\n");
		return -1;
	}
	// Configura o título da janela
	al_set_window_title(janela, "Ink Escape Alhpa");

	// Cria a Fila de eventos
	fila_eventos = al_create_event_queue();
	if (!fila_eventos) {
		fprintf(stderr, "Falha ao criar fila de evento\n");
		al_destroy_display(janela);

		return -1;
	}

	// Torna apto o uso de mouse na aplicação
	if (!al_install_mouse()) {
		fprintf(stderr, "Falha ao iniciar o mouse\n");
		al_destroy_display(janela);
		al_destroy_event_queue(fila_eventos);

		return -1;
	}
	// Atribui o cursor padrão do sistema para ser usado
	if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)) {
		fprintf(stderr, "Falha ao atribur ponteiro ao mouse\n");
		al_destroy_display(janela);

		return -1;
	}

	// Registra eventos da janela em fila_eventos
	al_register_event_source(fila_eventos, al_get_display_event_source(janela));
	// Registra eventos da janela em fila_eventos
	al_register_event_source(fila_eventos, al_get_mouse_event_source());

	// Preenche o objeto de progresso
	Progresso progresso;
	progresso.proximaSala = 0;
	progresso.Gameover = 0;
	progresso.Sala1 = 0;
	progresso.Sala2 = 0;
	progresso.Sala3 = 0;
	progresso.Item1 = 0;

	// Cria o ponteiro para progresso que será mandado para o resto do programa
	Progresso* prog = &progresso;
	// Looping central do jogo
	while (!prog->Gameover)
	{
		selecionaFase(janela, fila_eventos, prog);
	}

	al_destroy_event_queue(fila_eventos);
	al_destroy_display(janela);
}