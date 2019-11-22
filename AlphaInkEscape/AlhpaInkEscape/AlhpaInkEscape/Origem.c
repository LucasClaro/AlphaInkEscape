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
	progresso.proximaSala = 0;
	progresso.Gameover = 0;
	//prog de todas as salas
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
	progresso.Salas[12] = 0;
	progresso.Salas[13] = 0;
	progresso.Salas[14] = 0;
	progresso.Salas[15] = 0;
	progresso.Salas[16] = 0;

	//posisçoes do inventario
	progresso.Inventario[0] = 0;
	progresso.Inventario[1] = 0;
	progresso.Inventario[2] = 0;
	progresso.Inventario[3] = 0;
	progresso.Inventario[4] = 0;
	progresso.Inventario[5] = 0;
	progresso.Inventario[6] = 0;
	progresso.Inventario[7] = 0;

	progresso.Itens[0] = NULL;
	progresso.Itens[1] = NULL;
	progresso.Itens[2] = NULL;
	progresso.Itens[3] = NULL;
	progresso.Itens[4] = NULL;
	progresso.Itens[5] = NULL;
	progresso.Itens[6] = NULL;
	progresso.Itens[7] = NULL;
	
	//quantidade de itens no inventario
	progresso.inventCount = 0;

	//manipulção das posiçoes do inventario
	progresso.inventClick[0] = 0;
	progresso.inventClick[1] = 0;
	progresso.inventClick[2] = 0;
	progresso.inventClick[3] = 0;
	progresso.inventClick[4] = 0;
	progresso.inventClick[5] = 0;
	progresso.inventClick[6] = 0;
	progresso.inventClick[7] = 0;

	progresso.linhaInGame = 0;

	//populando objetos que serão usados como cenario
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

	//Saida cenario
	progresso.cenario->saida = (Objeto*)malloc(sizeof(Objeto));
	progresso.cenario->saida->bitmap = al_load_bitmap("Imgs/exit.png");
	progresso.cenario->saida->altura = 50;
	progresso.cenario->saida->largura = 50;
	progresso.cenario->saida->x = LARGURA_TELA - progresso.cenario->saida->largura - 5;
	progresso.cenario->saida->y = ALTURA_TELA / 4 - progresso.cenario->saida->altura * 2 - 30;

	//som cenario
	progresso.cenario->btnSom = (Objeto*)malloc(sizeof(Objeto));
	progresso.cenario->btnSom->altura = 50;
	progresso.cenario->btnSom->largura = 50;
	progresso.cenario->btnSom->x = progresso.cenario->saida->x - progresso.cenario->saida->largura - 10;
	progresso.cenario->btnSom->y = progresso.cenario->saida->y;
	progresso.cenario->btnSom->bitmap = progresso.cenario->comSom;
	progresso.cenario->musica = al_load_audio_stream("sounds/musica.ogg", 4, 1024);
	al_attach_audio_stream_to_mixer(progresso.cenario->musica, al_get_default_mixer());
	al_set_audio_stream_playmode(progresso.cenario->musica, ALLEGRO_PLAYMODE_LOOP);
	
	//miniMapa cenario
	progresso.cenario->miniMapa = (Objeto*)malloc(sizeof(Objeto));
	progresso.cenario->miniMapa->bitmap = al_load_bitmap("Imgs/Minimapa/mapa.png");
	progresso.cenario->miniMapa->altura = 453;
	progresso.cenario->miniMapa->largura = 626;
	progresso.cenario->miniMapa->x = (LARGURA_TELA / 2) - (progresso.cenario->miniMapa->largura / 2);
	progresso.cenario->miniMapa->y = (ALTURA_TELA / 2) - (progresso.cenario->miniMapa->altura / 2);

	progresso.cenario->btnMiniMapa = (Objeto*)malloc(sizeof(Objeto));
	progresso.cenario->btnMiniMapa->bitmap = al_load_bitmap("Imgs/Minimapa/mapaicon.png");
	progresso.cenario->btnMiniMapa->altura = 50;
	progresso.cenario->btnMiniMapa->largura = 50;
	progresso.cenario->btnMiniMapa->x = progresso.cenario->btnSom->x - progresso.cenario->btnMiniMapa->largura - 10;
	progresso.cenario->btnMiniMapa->y = progresso.cenario->btnSom->y;

	progresso.cenario->xMiniMapa = (Objeto*)malloc(sizeof(Objeto));
	progresso.cenario->xMiniMapa->bitmap = al_load_bitmap("Imgs/xis.png");
	progresso.cenario->xMiniMapa->altura = 83;
	progresso.cenario->xMiniMapa->largura = 83;
	progresso.cenario->xMiniMapa->x = 110 + (LARGURA_TELA / 4 * 3) - (progresso.cenario->xMiniMapa->largura / 2);
	progresso.cenario->xMiniMapa->y = progresso.cenario->xMiniMapa->altura / 4;
	progresso.cenario->fonte = al_load_font("ArquivosAux/fonts/Kindergarten.ttf", 60, 0);	

	loadFotosGlobais();//Fotos para o inventário

	progresso.cenario->PostIt2 = (Objeto*)malloc(sizeof(Objeto));
	progresso.cenario->PostIt2->altura = 183;
	progresso.cenario->PostIt2->largura = 201;
	progresso.cenario->PostIt2->x = -500;
	progresso.cenario->PostIt2->y = -500;
	progresso.cenario->PostIt2->bitmap = al_load_bitmap("Imgs/PostIts/postDali.png");
	progresso.Itens[2] = progresso.cenario->PostIt2;

	progresso.cenario->postIt3 = (Objeto*)malloc(sizeof(Objeto));
	progresso.cenario->postIt3->altura = 183;
	progresso.cenario->postIt3->largura = 201;
	progresso.cenario->postIt3->x = -500;
	progresso.cenario->postIt3->y = -500;
	progresso.cenario->postIt3->bitmap = NULL;
	progresso.cenario->postIt3->bitmap = al_load_bitmap("Imgs/PostIts/postMonet.png");
	progresso.Itens[1] = progresso.cenario->postIt3;

	progresso.cenario->postIt4 = (Objeto*)malloc(sizeof(Objeto));
	progresso.cenario->postIt4->altura = 183;
	progresso.cenario->postIt4->largura = 201;
	progresso.cenario->postIt4->x = -500;
	progresso.cenario->postIt4->y = -500;
	progresso.cenario->postIt4->bitmap = al_load_bitmap("Imgs/PostIts/postVan.png");
	progresso.Itens[0] = progresso.cenario->postIt4;

	progresso.cenario->sobreBi = (Objeto*)malloc(sizeof(Objeto));
	progresso.cenario->sobreBi->altura = 183;
	progresso.cenario->sobreBi->largura = 201;
	progresso.cenario->sobreBi->x = 110;
	progresso.cenario->sobreBi->y = 0;
	progresso.cenario->sobreBi->bitmap = al_load_bitmap("Imgs/ASc/miniaturaBin.png");
	progresso.Itens[3] = progresso.cenario->sobreBi;

	progresso.cenario->miniatura = (Objeto*)malloc(sizeof(Objeto));
	progresso.cenario->miniatura->largura = 140;
	progresso.cenario->miniatura->altura = 200;
	progresso.cenario->miniatura->x = 700;
	progresso.cenario->miniatura->y = 100;
	progresso.cenario->miniatura->bitmap = al_load_bitmap("Imgs/Clicavel/miniaturaAni.png");
	progresso.Itens[4] = progresso.cenario->miniatura;

	progresso.cenario->miniaturaObras = (Objeto*)malloc(sizeof(Objeto));
	progresso.cenario->miniaturaObras->largura = 95;
	progresso.cenario->miniaturaObras->altura = 136;
	progresso.cenario->miniaturaObras->x = 700;
	progresso.cenario->miniaturaObras->y = 100;
	progresso.cenario->miniaturaObras->bitmap = al_load_bitmap("Imgs/Clicavel/miniaturaObras.png");
	progresso.Itens[5] = progresso.cenario->miniaturaObras;

	progresso.cenario->miniaturaElem = (Objeto*)malloc(sizeof(Objeto));
	progresso.cenario->miniaturaElem->largura = 137;
	progresso.cenario->miniaturaElem->altura = 100;
	progresso.cenario->miniaturaElem->x = 700;
	progresso.cenario->miniaturaElem->y = 100;
	progresso.cenario->miniaturaElem->bitmap = al_load_bitmap("Imgs/Clicavel/miniaturaElem.png");
	progresso.Itens[6] = progresso.cenario->miniaturaElem;

	progresso.cenario->miniaturaPaises = (Objeto*)malloc(sizeof(Objeto));
	progresso.cenario->miniaturaPaises->largura = 95;
	progresso.cenario->miniaturaPaises->altura = 136;
	progresso.cenario->miniaturaPaises->x = 700;
	progresso.cenario->miniaturaPaises->y = 100;
	progresso.cenario->miniaturaPaises->bitmap = al_load_bitmap("Imgs/Clicavel/miniaturaPaises.png");
	progresso.Itens[7] = progresso.cenario->miniaturaPaises;

	// Cria o ponteiro para progresso que ser� mandado para o resto do programa
	Progresso* prog = &progresso;
	
	// Looping central do jogo
	while (!prog->Gameover)
	{
		selecionaFase(janela, fila_eventos, prog);
	}


	al_destroy_event_queue(fila_eventos);
	al_shutdown_image_addon();
	al_shutdown_font_addon();
	al_shutdown_native_dialog_addon();
	al_uninstall_audio();
	al_uninstall_keyboard();
	al_stop_samples();
	al_destroy_display(janela);
	destroyFotosGlobais();
}
