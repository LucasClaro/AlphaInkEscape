#include <stdio.h>
// Inclui o arquivo de cabe�alho da biblioteca Allegro 5
#include <allegro5/allegro.h>
// Inclui o cabe�alho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
// Inclui a coisa do mouse
#include <allegro5/allegro_native_dialog.h>

#include "Funcoes.h"
#include "Struct.h"

Objeto* A1, * A2, * A3, * A4;
Objeto* Foto1, * Foto2, * Foto3, * Foto4;
Objeto* Livro1, * Livro2, * Livro3, * Livro4;
Objeto* Pais1, * Pais2, * Pais3, * Pais4;

Objeto* SendoArrastado, * UltimoArrastado;

int JogarFase15Classico(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* prog) {
	int x0 = 140;
	int y0 = 50;

	ALLEGRO_BITMAP* Background = al_load_bitmap("Imgs/fundo.png");


	A1 = (Objeto*)malloc(sizeof(Objeto));
	A1->bitmap = al_load_bitmap("Imgs/Classico/Dante.png");
	A1->x = x0;
	A1->y = y0;
	A1->largura = 250;
	A1->altura = 150;

	A2 = (Objeto*)malloc(sizeof(Objeto));
	A2->bitmap = al_load_bitmap("Imgs/Classico/Miguel.png");
	A2->x = x0;
	A2->y = 160 + y0;
	A2->largura = 250;
	A2->altura = 150;

	A3 = (Objeto*)malloc(sizeof(Objeto));
	A3->bitmap = al_load_bitmap("Imgs/Classico/Shakespeare.png");
	A3->x = 120;
	A3->y = 160*2 + y0;
	A3->largura = 250;
	A3->altura = 150;

	A4 = (Objeto*)malloc(sizeof(Objeto));
	A4->bitmap = al_load_bitmap("Imgs/Classico/Luis.png");
	A4->x = x0;
	A4->y = 160*3 + y0;
	A4->largura = 250;
	A4->altura = 150;

	Livro2 = (Objeto*)malloc(sizeof(Objeto));
	Livro2->bitmap = al_load_bitmap("Imgs/Classico/Quixote.png");
	Livro2->x = 260 + x0;
	Livro2->y = y0;
	Livro2->largura = 250;
	Livro2->altura = 150;

	Livro3 = (Objeto*)malloc(sizeof(Objeto));
	Livro3->bitmap = al_load_bitmap("Imgs/Classico/Romeu.png");
	Livro3->x = 260 + x0;
	Livro3->y = y0 + 160;
	Livro3->largura = 250;
	Livro3->altura = 150;

	Livro4 = (Objeto*)malloc(sizeof(Objeto));
	Livro4->bitmap = al_load_bitmap("Imgs/Classico/Luziadas.png");
	Livro4->x = 260 + x0;
	Livro4->y = y0 + 160*2;
	Livro4->largura = 250;
	Livro4->altura = 150;

	Livro1 = (Objeto*)malloc(sizeof(Objeto));
	Livro1->bitmap = al_load_bitmap("Imgs/Classico/Comedia.png");
	Livro1->x = 260 + x0;
	Livro1->y = y0 + 160*3;
	Livro1->largura = 250;
	Livro1->altura = 150;

	Pais4 = (Objeto*)malloc(sizeof(Objeto));
	Pais4->bitmap = al_load_bitmap("Imgs/Classico/Portugal.png");
	Pais4->x = 260*2 + x0;
	Pais4->y = y0;
	Pais4->largura = 250;
	Pais4->altura = 150;

	Pais1 = (Objeto*)malloc(sizeof(Objeto));
	Pais1->bitmap = al_load_bitmap("Imgs/Classico/Italia.png");
	Pais1->x = 260 * 2 + x0;
	Pais1->y = y0 + 160;
	Pais1->largura = 250;
	Pais1->altura = 150;

	Pais2 = (Objeto*)malloc(sizeof(Objeto));
	Pais2->bitmap = al_load_bitmap("Imgs/Classico/Espanha.png");
	Pais2->x = 260 * 2 + x0;
	Pais2->y = y0 + 160*2;
	Pais2->largura = 250;
	Pais2->altura = 150;

	Pais3 = (Objeto*)malloc(sizeof(Objeto));
	Pais3->bitmap = al_load_bitmap("Imgs/Classico/Inglaterra.png");
	Pais3->x = 260 * 2 + x0;
	Pais3->y = y0 + 160 * 3;
	Pais3->largura = 250;
	Pais3->altura = 150;

	Foto3 = (Objeto*)malloc(sizeof(Objeto));
	Foto3->bitmap = al_load_bitmap("Imgs/Classico/ShakespeareI.png");
	Foto3->x = 260 * 3 + x0;
	Foto3->y = y0;
	Foto3->largura = 250;
	Foto3->altura = 150;

	Foto4 = (Objeto*)malloc(sizeof(Objeto));
	Foto4->bitmap = al_load_bitmap("Imgs/Classico/LuisI.png");
	Foto4->x = 260 * 3 + x0;
	Foto4->y = y0 + 160;
	Foto4->largura = 250;
	Foto4->altura = 150;

	Foto1 = (Objeto*)malloc(sizeof(Objeto));
	Foto1->bitmap = al_load_bitmap("Imgs/Classico/DanteI.png");
	Foto1->x = 260 * 3 + x0;
	Foto1->y = y0 + 160*2;
	Foto1->largura = 250;
	Foto1->altura = 150;

	Foto2 = (Objeto*)malloc(sizeof(Objeto));
	Foto2->bitmap = al_load_bitmap("Imgs/Classico/MiguelI.png");
	Foto2->x = 260 * 3 + x0;
	Foto2->y = y0 + 160 * 3;
	Foto2->largura = 250;
	Foto2->altura = 150;

	UltimoArrastado = A1;

	int gameOver = 0;
	int arrastando = 0;
	int aux = 0;
	while (!gameOver)
	{
		while (!al_is_event_queue_empty(fila_eventos))
		{
			//Cria um evento
			ALLEGRO_EVENT evento;
			//espero por um evento da fila, e guarda em evento
			al_wait_for_event(fila_eventos, &evento);

			//se teve eventos e foi um evento de fechar janela, encerra repeti��o			
			if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				prog->Gameover = 1;
				gameOver = 1;
			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				if (!prog->Salas[15]) {
					if (IsInside(evento.mouse.x, evento.mouse.y, Livro1))
					{
						arrastando = 1;
						Livro1->cliqueX = MapearDistancia(evento.mouse.x, Livro1->x);
						Livro1->cliqueY = MapearDistancia(evento.mouse.y, Livro1->y);
						SendoArrastado = Livro1;
						//UltimoArrastado
						aux = Livro1->y;
					}
					else if (IsInside(evento.mouse.x, evento.mouse.y, Livro2))
					{
						arrastando = 2;
						Livro2->cliqueX = MapearDistancia(evento.mouse.x, Livro2->x);
						Livro2->cliqueY = MapearDistancia(evento.mouse.y, Livro2->y);
						SendoArrastado = Livro2;
						aux = Livro2->y;
					}
					else if (IsInside(evento.mouse.x, evento.mouse.y, Livro3))
					{
						arrastando = 3;
						Livro3->cliqueX = MapearDistancia(evento.mouse.x, Livro3->x);
						Livro3->cliqueY = MapearDistancia(evento.mouse.y, Livro3->y);
						SendoArrastado = Livro3;
						aux = Livro3->y;
					}
					else if (IsInside(evento.mouse.x, evento.mouse.y, Livro4))
					{
						arrastando = 4;
						Livro4->cliqueX = MapearDistancia(evento.mouse.x, Livro4->x);
						Livro4->cliqueY = MapearDistancia(evento.mouse.y, Livro4->y);
						SendoArrastado = Livro4;
						aux = Livro4->y;
					}
					else if (IsInside(evento.mouse.x, evento.mouse.y, Pais1))
					{
						arrastando = 5;
						Pais1->cliqueX = MapearDistancia(evento.mouse.x, Pais1->x);
						Pais1->cliqueY = MapearDistancia(evento.mouse.y, Pais1->y);
						SendoArrastado = Pais1;
						aux = Pais1->y;
					}
					else if (IsInside(evento.mouse.x, evento.mouse.y, Pais2))
					{
						arrastando = 6;
						Pais2->cliqueX = MapearDistancia(evento.mouse.x, Pais2->x);
						Pais2->cliqueY = MapearDistancia(evento.mouse.y, Pais2->y);
						SendoArrastado = Pais2;
						aux = Pais2->y;
					}
					else if (IsInside(evento.mouse.x, evento.mouse.y, Pais3))
					{
						arrastando = 7;
						Pais3->cliqueX = MapearDistancia(evento.mouse.x, Pais3->x);
						Pais3->cliqueY = MapearDistancia(evento.mouse.y, Pais3->y);
						SendoArrastado = Pais3;
						aux = Pais3->y;
					}
					else if (IsInside(evento.mouse.x, evento.mouse.y, Pais4))
					{
						arrastando = 8;
						Pais4->cliqueX = MapearDistancia(evento.mouse.x, Pais4->x);
						Pais4->cliqueY = MapearDistancia(evento.mouse.y, Pais4->y);
						SendoArrastado = Pais4;
						aux = Pais4->y;
					}
					else if (IsInside(evento.mouse.x, evento.mouse.y, Foto1))
					{
						arrastando = 9;
						Foto1->cliqueX = MapearDistancia(evento.mouse.x, Foto1->x);
						Foto1->cliqueY = MapearDistancia(evento.mouse.y, Foto1->y);
						SendoArrastado = Foto1;
						aux = Foto1->y;
					}
					else if (IsInside(evento.mouse.x, evento.mouse.y, Foto2))
					{
						arrastando = 10;
						Foto2->cliqueX = MapearDistancia(evento.mouse.x, Foto2->x);
						Foto2->cliqueY = MapearDistancia(evento.mouse.y, Foto2->y);
						SendoArrastado = Foto2;
						aux = Foto2->y;
					}
					else if (IsInside(evento.mouse.x, evento.mouse.y, Foto3))
					{
						arrastando = 11;
						Foto3->cliqueX = MapearDistancia(evento.mouse.x, Foto3->x);
						Foto3->cliqueY = MapearDistancia(evento.mouse.y, Foto3->y);
						SendoArrastado = Foto3;
						aux = Foto3->y;
					}
					else if (IsInside(evento.mouse.x, evento.mouse.y, Foto4))
					{
						arrastando = 12;
						Foto4->cliqueX = MapearDistancia(evento.mouse.x, Foto4->x);
						Foto4->cliqueY = MapearDistancia(evento.mouse.y, Foto4->y);
						SendoArrastado = Foto4;
						aux = Foto4->y;
					}
				}				
				else {
					arrastando = 0;
					SendoArrastado = NULL;
				}
			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				if (IsInside(evento.mouse.x, evento.mouse.y, Livro1) && arrastando != 1 && arrastando < 5 && arrastando > 0) {
					SendoArrastado->y = Livro1->y;
					Livro1->y = aux;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, Livro2) && arrastando != 2 && arrastando < 5 && arrastando > 0) {
					SendoArrastado->y = Livro2->y;
					Livro2->y = aux;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, Livro3) && arrastando != 3 && arrastando < 5 && arrastando > 0) {
					SendoArrastado->y = Livro3->y;
					Livro3->y = aux;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, Livro4) && arrastando != 4 && arrastando < 5 && arrastando > 0) {
					SendoArrastado->y = Livro4->y;
					Livro4->y = aux;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, Pais1) && arrastando != 5 && arrastando < 9 && arrastando > 4) {
					SendoArrastado->y = Pais1->y;
					Pais1->y = aux;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, Pais2) && arrastando != 6 && arrastando < 9 && arrastando > 4) {
					SendoArrastado->y = Pais2->y;
					Pais2->y = aux;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, Pais3) && arrastando != 7 && arrastando < 9 && arrastando > 4) {
					SendoArrastado->y = Pais3->y;
					Pais3->y = aux;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, Pais4) && arrastando != 8 && arrastando < 9 && arrastando > 4) {
					SendoArrastado->y = Pais4->y;
					Pais4->y = aux;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, Foto1) && arrastando != 9 && arrastando < 13 && arrastando > 8) {
					SendoArrastado->y = Foto1->y;
					Foto1->y = aux;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, Foto2) && arrastando != 10 && arrastando < 13 && arrastando > 8) {
					SendoArrastado->y = Foto2->y;
					Foto2->y = aux;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, Foto3) && arrastando != 11 && arrastando < 13 && arrastando > 8) {
					SendoArrastado->y = Foto3->y;
					Foto3->y = aux;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, Foto4) && arrastando != 12 && arrastando < 13 && arrastando > 8) {
					SendoArrastado->y = Foto4->y;
					Foto4->y = aux;
				}
				else {
					if(SendoArrastado)
						SendoArrastado->y = aux;
				}
				SendoArrastado = NULL;
				arrastando = 0;
			}

			ALLEGRO_MOUSE_STATE state;

			al_get_mouse_state(&state);
			if (state.buttons & 1 && arrastando)
			{
				switch (arrastando)
				{
				case 1:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, Livro1)) {
						Livro1->y = evento.mouse.y - Livro1->cliqueY;
					}
					break;
				case 2:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, Livro2)) {
						Livro2->y = evento.mouse.y - Livro2->cliqueY;
					}
					break;
				case 3:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, Livro3)) {
						Livro3->y = evento.mouse.y - Livro3->cliqueY;
					}
					break;
				case 4:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, Livro4)) {
						Livro4->y = evento.mouse.y - Livro4->cliqueY;
					}
					break;
				case 5:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, Pais1)) {
						Pais1->y = evento.mouse.y - Pais1->cliqueY;
					}
					break;
				case 6:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, Pais2)) {
						Pais2->y = evento.mouse.y - Pais2->cliqueY;
					}
					break;
				case 7:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, Pais3)) {
						Pais3->y = evento.mouse.y - Pais3->cliqueY;
					}
					break;
				case 8:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, Pais4)) {
						Pais4->y = evento.mouse.y - Pais4->cliqueY;
					}
					break;
				case 9:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, Foto1)) {
						Foto1->y = evento.mouse.y - Foto1->cliqueY;
					}
					break;
				case 10:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, Foto2)) {
						Foto2->y = evento.mouse.y - Foto2->cliqueY;
					}
					break;
				case 11:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, Foto3)) {
						Foto3->y = evento.mouse.y - Foto3->cliqueY;
					}
					break;
				case 12:
					if (!VerificarBordas(evento.mouse.x, evento.mouse.y, Foto4)) {
						Foto4->y = evento.mouse.y - Foto4->cliqueY;
					}
					break;
				default:
					break;
				}
			}
		}

		if (A1->y == Foto1->y && A1->y == Pais1->y && A1->y == Livro1->y && A2->y == Foto2->y && A2->y == Pais2->y && A2->y == Livro2->y && A3->y == Foto3->y && A3->y == Pais3->y && A3->y == Livro3->y) {
			prog->Salas[15] = 1;
		}

		al_draw_bitmap(Background, 0, 0, 0);

		al_draw_bitmap(A1->bitmap, A1->x, A1->y, 0);
		al_draw_bitmap(A2->bitmap, A2->x, A2->y, 0);
		al_draw_bitmap(A3->bitmap, A3->x, A3->y, 0);
		al_draw_bitmap(A4->bitmap, A4->x, A4->y, 0);

		al_draw_bitmap(Pais1->bitmap, Pais1->x, Pais1->y, 0);
		al_draw_bitmap(Pais2->bitmap, Pais2->x, Pais2->y, 0);
		al_draw_bitmap(Pais3->bitmap, Pais3->x, Pais3->y, 0);
		al_draw_bitmap(Pais4->bitmap, Pais4->x, Pais4->y, 0);

		al_draw_bitmap(Livro1->bitmap, Livro1->x, Livro1->y, 0);
		al_draw_bitmap(Livro2->bitmap, Livro2->x, Livro2->y, 0);
		al_draw_bitmap(Livro3->bitmap, Livro3->x, Livro3->y, 0);
		al_draw_bitmap(Livro4->bitmap, Livro4->x, Livro4->y, 0);

		al_draw_bitmap(Foto1->bitmap, Foto1->x, Foto1->y, 0);
		al_draw_bitmap(Foto2->bitmap, Foto2->x, Foto2->y, 0);
		al_draw_bitmap(Foto3->bitmap, Foto3->x, Foto3->y, 0);
		al_draw_bitmap(Foto4->bitmap, Foto4->x, Foto4->y, 0);

		caregaInventario(prog);
		al_flip_display();
	}
}