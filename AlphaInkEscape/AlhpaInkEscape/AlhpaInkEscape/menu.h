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

//Cria os obj
Objeto* title, * jogar, * sair, * linha, * novo, * cont;
ALLEGRO_BITMAP* hist1, * hist2, * hist3, * hist4;
ALLEGRO_BITMAP* Background;
float volume;

//Função main do menu
int JogarMenu(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* prog) {

	//vars de controle para ler arquivo
	int podeContinuar = 0;
	int leitor = 0;
	int tamanho;
	FILE* file;
	int i;

	//abre o arquivo
	fopen_s(&file, "save.txt", "r");
	
	//percorre o arquivo procurando chars
	fseek(file, 0, SEEK_END);
	tamanho = ftell(file);

	//se o arquivo n estiver vazio é possível continuar um save
	if (tamanho > 0) {
		podeContinuar = 1;
	}
	//fecha o arquivo
	fclose(file);
	
	//Imagens que ocupam a tela toda
	Background = al_load_bitmap("Imgs/fundo.png");
	hist1 = al_load_bitmap("Imgs/menu/hist1.png");
	hist2 = al_load_bitmap("Imgs/menu/hist2.png");
	hist3 = al_load_bitmap("Imgs/menu/hist3.png");
	hist4 = al_load_bitmap("Imgs/menu/hist4.png");

	//Objs
	title = (Objeto*)malloc(sizeof(Objeto));
	title->altura = 200;
	title->largura = 600;
	title->x = (LARGURA_TELA / 2) - (title->largura / 2);
	title->y = 50;
	title->bitmap = al_load_bitmap("Imgs/menu/title.png");

	novo = (Objeto*)malloc(sizeof(Objeto));
	novo->altura = 150;
	novo->largura = 600;
	novo->x = (LARGURA_TELA / 2) - (title->largura / 2);
	novo->y = 300;
	novo->bitmap = al_load_bitmap("Imgs/menu/new.png");

	cont = (Objeto*)malloc(sizeof(Objeto));
	cont->altura = 150;
	cont->largura = 600;
	cont->x = (LARGURA_TELA / 2) - (title->largura / 2);
	cont->y = novo->y + 130;
	//muda a cor do btn caso ele n esteja habilitado
	if(podeContinuar)
		cont->bitmap = al_load_bitmap("Imgs/menu/cont.png");
	else
		cont->bitmap = al_load_bitmap("Imgs/menu/ncont.png");

	sair = (Objeto*)malloc(sizeof(Objeto));
	sair->altura = 150;
	sair->largura = 300;
	sair->x = (LARGURA_TELA / 2) - (sair->largura / 2);
	sair->y = cont->y + 130;
	sair->bitmap = al_load_bitmap("Imgs/menu/sair.png");

	linha = (Objeto*)malloc(sizeof(Objeto));
	linha->altura = 150;
	linha->largura = 300;
	linha->x = (LARGURA_TELA / 2) - (linha->largura / 2);
	linha->y = novo->y + 130;
	linha->bitmap = al_load_bitmap("Imgs/menu/linha.png");

	//Vars de controle
	int gameOver = 0;
	int Dentro = 0;
	int Hist = 0;

	//Prieiro Desenho pra teal n surgir preta
	al_draw_bitmap(Background, 0, 0, 0);
	al_draw_bitmap(title->bitmap, title->x, title->y, 0);
	al_draw_bitmap(novo->bitmap, novo->x, novo->y, 0);
	al_draw_bitmap(cont->bitmap, cont->x, cont->y, 0);
	//al_draw_bitmap(jogar->bitmap, jogar->x, jogar->y, 0);
	al_draw_bitmap(sair->bitmap, sair->x, sair->y, 0);

	//loop do game
	while (!gameOver)
	{
		//loop eventos
		while (!al_is_event_queue_empty(fila_eventos))
		{
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);

			ALLEGRO_MOUSE_STATE state;
			al_get_mouse_state(&state);

			//X do Windows
			if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				gameOver = 1;
				prog->Gameover = 1;
			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				//Mute do som
				if (IsInside(evento.mouse.x, evento.mouse.y, prog->cenario->btnSom)) {
				tocando = !tocando;
				}
				//passando a história
				else if (Hist > 0) {
					Hist++;
				}
				//Novo Jogo
				else if(IsInside(evento.mouse.x, evento.mouse.y, novo) && Hist == 0)
				{
					fopen_s(&file, "save.txt", "w");

					for (i = 0; i < 17; i++) {
						prog->Salas[i] = 0;
						fprintf_s(file, "0 ");
					}						

					for (i = 0; i < 8; i++) {
						prog->Inventario[i] = 0;
						fprintf_s(file, "0 ", prog->Inventario[i]);
					}						

					prog->inventCount = 0;
					fprintf_s(file, "0 ");

					for (i = 0; i < 8; i++) {
						prog->inventClick[i] = 0;
						fprintf_s(file, "0 ");
					}						

					prog->cenario->PostIt2->x = (LARGURA_TELA / 2) - (prog->cenario->PostIt2->largura / 2);
					prog->cenario->PostIt2->y = ALTURA_TELA - prog->cenario->PostIt2->altura;
					prog->cenario->postIt3->x = (LARGURA_TELA / 2) - (prog->cenario->postIt3->largura / 2);
					prog->cenario->postIt3->y = ALTURA_TELA - prog->cenario->postIt3->altura;
					prog->cenario->postIt4->x = (LARGURA_TELA / 2) - (prog->cenario->postIt4->largura / 2);
					prog->cenario->postIt4->y = ALTURA_TELA - prog->cenario->postIt4->altura;

					prog->linhaInGame = 0;
					fprintf_s(file, "0 ");

					prog->proximaSala = 6;
					fprintf_s(file, "6 ");

					fclose(file);

					Hist++;

					//Validador
					printf("\n");
					for (i = 0; i < 17; i++) {
						printf("%d", prog->Salas[i]);
					}
					printf("\n");
					for (i = 0; i < 8; i++) {
						printf("%d", prog->Inventario[i]);
					}
					printf("\n%d", prog->inventCount);
					for (i = 0; i < 8; i++) {
						printf("%d", prog->inventClick[i]);
					}
					printf("\n%d", prog->linhaInGame);
					printf("\n%d", prog->proximaSala);
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, cont) && Hist == 0 && podeContinuar) {
					//preenche o progresso 
					fopen_s(&file, "save.txt", "r");
					i = 1;

					fscanf_s(file, "%d", &leitor);
					prog->Salas[0] = leitor;
					while (!feof(file))
					{
						fscanf_s(file, "%d", &leitor);
						if (i < 17)
							prog->Salas[i] = leitor;
						else if (i < 25)
							prog->Inventario[i - 17] = leitor;
						else if (i < 26)
							prog->inventCount = leitor;
						else if (i < 34)
							prog->inventClick[i - 26] = leitor;
						else if (i < 35)
							prog->linhaInGame = leitor;
						else if (i < 36)
							prog->proximaSala = leitor;
						else if (i < 37)
							tocando = leitor;

						i++;
					}

					//Validador
					/*printf("\n");
					for (i = 0; i < 17; i++) {
						printf("%d", prog->Salas[i]);
					}
					printf("\n");
					for (i = 0; i < 8; i++) {
						printf("%d", prog->Inventario[i]);
					}
					printf("\n%d", prog->inventCount);
					for (i = 0; i < 8; i++) {
						printf("%d", prog->inventClick[i]);
					}
					printf("\n%d", prog->linhaInGame);
					printf("\n%d", prog->proximaSala);*/
					
					fclose(file);

					gameOver = 1;
				}
				//Sair			
				else if (IsInside(evento.mouse.x, evento.mouse.y, sair) && Hist == 0) {
					gameOver = 1;
					prog->Gameover = 1;
				}	
			}
			//Controla a linha de seleção
			else if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
				if (IsInside(evento.mouse.x, evento.mouse.y, novo))
				{
					Dentro = 1;
					linha->y = novo->y;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, cont) && podeContinuar)
				{
					Dentro = 1;
					linha->y = cont->y;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, sair)) {
					Dentro = 1;
					linha->y = sair->y;
				}
				else
				{
					Dentro = 0;
				}
			}

			//Inicia o jogo depois da história
			if (Hist > 4) {
				prog->proximaSala = 6;
				al_play_sample(prog->cenario->somSeta, volume, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				gameOver = 1;
			}
		}		

		//Desenhos
		al_draw_bitmap(Background, 0, 0, 0);
		
		if (Hist <= 0) {
			al_draw_bitmap(title->bitmap, title->x, title->y, 0);
			//al_draw_bitmap(jogar->bitmap, jogar->x, jogar->y, 0);
			al_draw_bitmap(novo->bitmap, novo->x, novo->y, 0);
			al_draw_bitmap(cont->bitmap, cont->x, cont->y, 0);
			al_draw_bitmap(sair->bitmap, sair->x, sair->y, 0);
			if (Dentro)
				al_draw_bitmap(linha->bitmap, linha->x, linha->y, 0);
		}		
		if (Hist == 1)
			al_draw_bitmap(hist1, 0, 0, 0);
		if (Hist == 2)
			al_draw_bitmap(hist2, 0, 0, 0);
		if (Hist == 3)
			al_draw_bitmap(hist3, 0, 0, 0);
		if (Hist == 4)
			al_draw_bitmap(hist4, 0, 0, 0);

		som(prog);


		al_flip_display();
	}

	al_destroy_bitmap(Background);
	//al_destroy_bitmap(jogar->bitmap);
	al_destroy_bitmap(novo->bitmap);
	al_destroy_bitmap(cont->bitmap);
	al_destroy_bitmap(sair->bitmap);
	al_destroy_bitmap(linha->bitmap);
	al_destroy_bitmap(title->bitmap);


	return 0;
}