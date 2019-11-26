#include <stdio.h>
// Inclui o arquivo de cabe�alho da biblioteca Allegro 5
#include <allegro5/allegro.h>
// Inclui o cabe�alho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
// Inclui a coisa do mouse
#include <allegro5/allegro_native_dialog.h>

#include "Funcoes.h"
#include "Struct.h"

//Cria Objs
Objeto* D1, * D2, * D3, * E4, * E5, * E6;
Objeto* Reset;

//Função main da fase
int JogarFase13Sapos(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* prog) 
{
	//Preenche Objs
	Objeto* saidaDireita;
	saidaDireita = (Objeto*)malloc(sizeof(Objeto));
	saidaDireita->bitmap = prog->cenario->setaDireita;
	saidaDireita->largura = 50;
	saidaDireita->altura = 50;
	saidaDireita->x = LARGURA_TELA - saidaDireita->largura;;
	saidaDireita->y = (ALTURA_TELA / 2) - (saidaDireita->altura / 2);

	Objeto* saidaCima;
	saidaCima = (Objeto*)malloc(sizeof(Objeto));
	saidaCima->bitmap = prog->cenario->setaCima;
	saidaCima->largura = 50;
	saidaCima->altura = 50;
	saidaCima->y = 1;
	saidaCima->x = 110 + (LARGURA_TELA / 2) - (saidaCima->largura / 2);

	Reset = (Objeto*)malloc(sizeof(Objeto));
	Reset->bitmap = al_load_bitmap("Imgs/Sapos/reset.png");
	Reset->x = LARGURA_TELA/2 - 50 + 70;
	Reset->y = 500;
	Reset->largura = 100;
	Reset->altura = 100;

	D1 = (Objeto*)malloc(sizeof(Objeto));
	D1->bitmap = al_load_bitmap("Imgs/Sapos/D.png");
	D1->x = 110;
	D1->y = 300;
	D1->largura = 125;
	D1->altura = 83;

	D2 = (Objeto*)malloc(sizeof(Objeto));
	D2->bitmap = al_load_bitmap("Imgs/Sapos/D.png");
	D2->x = D1->x + D1->largura;
	D2->y = 300;
	D2->largura = 125;
	D2->altura = 83;

	D3 = (Objeto*)malloc(sizeof(Objeto));
	D3->bitmap = al_load_bitmap("Imgs/Sapos/D.png");
	D3->x = D2->x + D2->largura;
	D3->y = 300;
	D3->largura = 152;
	D3->altura = 83;

	E4 = (Objeto*)malloc(sizeof(Objeto));
	E4->bitmap = al_load_bitmap("Imgs/Sapos/E.png");
	E4->x = D3->x + D3->largura * 2;
	E4->y = 300;
	E4->largura = 125;
	E4->altura = 83;

	E5 = (Objeto*)malloc(sizeof(Objeto));
	E5->bitmap = al_load_bitmap("Imgs/Sapos/E.png");
	E5->x = E4->x + E4->largura;
	E5->y = 300;
	E5->largura = 125;
	E5->altura = 83;

	E6 = (Objeto*)malloc(sizeof(Objeto));
	E6->bitmap = al_load_bitmap("Imgs/Sapos/E.png");
	E6->x = E5->x + E5->largura;
	E6->y = 300;
	E6->largura = 125;
	E6->altura = 83;	
	
	//Vars de controle
	int gameOver = 0;
	int i;
	//Vetor inicial e que é usado para mover os elementos// vertor com a resposta
	int casas[7] = { 1,2,3,0,4,5,6 }, correto[7] = { 4,5,6,0,1,2,3 };

	//loop central do jogo
	while (!gameOver)
	{
		while (!al_is_event_queue_empty(fila_eventos))
		{
			//Cria um evento
			ALLEGRO_EVENT evento;
			//espero por um evento da fila, e guarda em evento
			al_wait_for_event(fila_eventos, &evento);

			//X do Windows	
			if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				prog->Gameover = 1;
				gameOver = 1;
			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {	

				//Função do inventário
				limpaClick(prog);

				//Saída Cima
				if (IsInside(evento.mouse.x, evento.mouse.y, saidaCima))
				{
					prog->proximaSala = 9;
					gameOver = 1;
				}
				//Saída Direita
				else if (IsInside(evento.mouse.x, evento.mouse.y, saidaDireita))
				{
					prog->proximaSala = 14;
					al_play_sample(prog->cenario->somSeta, volume, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					gameOver = 1;
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
					gameOver = 1;
					salvar(prog);
				}
				//Restart
				else if (IsInside(evento.mouse.x, evento.mouse.y, Reset) && !prog->Salas[13]) {
					for (i = 0; i < 7; i++) {//Percorre as sete casas
						
						casas[i] = i + 1;//coloca o código de cada elemento
						
						if (i == 3)//Pula o buraco do meio
							casas[i] = 0;
						
						if (i > 3)//Arruma os três depois do buraco
							casas[i] = i;
					}
				}
				//Primeiro elemento >-- ---
				else if (IsInside(evento.mouse.x, evento.mouse.y, D1)) {
					
					i = IndexOf(1,casas);//Busca em qual posição do vetor a peça está

					if (i < 4 && casas[i + 1] == 0) {//Vê se a próxima casa está livre caso ela ainda esteja no "tabuleiro"
						casas[i + 1] = 1;
						casas[i] = 0;
					}
					else if (i < 3 && casas[i + 2] == 0) {//Vê se a casa a 2 de distância está livre caso ela ainda esteja no "tabuleiro"
						casas[i + 2] = 1;
						casas[i] = 0;
					}
				}
				//Segundo elemento ->- ---
				else if (IsInside(evento.mouse.x, evento.mouse.y, D2)) {
					i = IndexOf(2, casas);
					if (i < 5 && casas[i + 1] == 0) {
						casas[i + 1] = 2;
						casas[i] = 0;
					}
					else if (i < 4 && casas[i + 2] == 0) {
						casas[i + 2] = 2;
						casas[i] = 0;
					}
				}
				//Terceiro elemento --> ---
				else if (IsInside(evento.mouse.x, evento.mouse.y, D3)) {
					i = IndexOf(3, casas);
					if (i < 6 && casas[i + 1] == 0) {
						casas[i + 1] = 3;
						casas[i] = 0;
					}
					else if (i < 5 && casas[i + 2] == 0) {
						casas[i + 2] = 3;
						casas[i] = 0;
					}
				}
				//Quarto elemento --- <--
				else if (IsInside(evento.mouse.x, evento.mouse.y, E4)) {
					i = IndexOf(4, casas);
					if (i > 0 && casas[i - 1] == 0) {
						casas[i - 1] = 4;
						casas[i] = 0;
					}
					else if (i > 1 && casas[i - 2] == 0) {
						casas[i - 2] = 4;
						casas[i] = 0;
					}
				}
				//Quinto elemento --- -<-
				else if (IsInside(evento.mouse.x, evento.mouse.y, E5)) {
					i = IndexOf(5, casas);
					if (i > 1 && casas[i - 1] == 0) {
						casas[i - 1] = 5;
						casas[i] = 0;
					}
					else if (i > 2 && casas[i - 2] == 0) {
						casas[i - 2] = 5;
						casas[i] = 0;
					}
				}
				//Sexto elemento --- --<
				else if (IsInside(evento.mouse.x, evento.mouse.y, E6)) {
					i = IndexOf(6, casas);
					if (i > 2 && casas[i - 1] == 0) {
						casas[i - 1] = 6;
						casas[i] = 0;
					}
					else if (i > 3 && casas[i - 2] == 0) {
						casas[i - 2] = 6;
						casas[i] = 0;
					}
				}
				//Item do invêntário
				else if (IsInside(evento.mouse.x, evento.mouse.y, prog->cenario->PostIt2) && !prog->Inventario[2])
				{
					prog->Inventario[2] = 1;
					prog->inventCount++;
				}

				//Função do inventário
				checaClickOrdem(evento.mouse.x, evento.mouse.y, prog);


				//for (i = 0; i < 7; i++) { printf("%d ", casas[i]); }printf("\n");
			}

			//Vê se a fase está completa
			if (confere(casas, correto, 7))
			{
				prog->Salas[13] = 1;
				prog->cenario->PostIt2->x = (LARGURA_TELA / 2) - (prog->cenario->PostIt2->largura / 2);
				prog->cenario->PostIt2->y = ALTURA_TELA - prog->cenario->PostIt2->altura;
			}
		}

		//Define a posição de cada peça dada sua posição no vetor
		D1->x = 250 + 130 * IndexOf(1, casas);
		D2->x = 250 + 130 * IndexOf(2, casas);
		D3->x = 250 + 130 * IndexOf(3, casas);
		E4->x = 250 + 130 * IndexOf(4, casas);
		E5->x = 250 + 130 * IndexOf(5, casas);
		E6->x = 250 + 130 * IndexOf(6, casas);

		//Desenhos
		al_draw_bitmap(prog->cenario->background, 0, 0, 0);


		al_draw_bitmap(D1->bitmap, D1->x, D1->y, 0);
		al_draw_bitmap(D2->bitmap, D2->x, D2->y, 0);
		al_draw_bitmap(D3->bitmap, D3->x, D3->y, 0);

		al_draw_bitmap(E4->bitmap, E4->x, E4->y, 0);
		al_draw_bitmap(E5->bitmap, E5->x, E5->y, 0);
		al_draw_bitmap(E6->bitmap, E6->x, E6->y, 0);


		al_draw_bitmap(saidaDireita->bitmap, saidaDireita->x, saidaDireita->y, 0);
		al_draw_bitmap(saidaCima->bitmap, saidaCima->x, saidaCima->y, 0);
		
		al_draw_bitmap(Reset->bitmap, Reset->x, Reset->y, 0);

		if (prog->Salas[13] && !prog->Inventario[2])
		{
			al_draw_bitmap(prog->cenario->PostIt2->bitmap, prog->cenario->PostIt2->x, prog->cenario->PostIt2->y, 0);
		}

		al_draw_bitmap(prog->cenario->saida->bitmap, prog->cenario->saida->x, prog->cenario->saida->y, 0);

		//Funções padrões
		som(prog);
		caregaInventario(prog);
		abreOrdem(prog);
		abrirMapa(prog);

		al_flip_display();
	}

	//Destroys	

	free(saidaCima);
	free(saidaDireita);
}

//Retorna a posição de um inteiro no vetor
//Aqui é usado pra saber em qual casa está uma peça
int IndexOf(int x, int v[]) {
	int i;
	for (i = 0; i < 7; i++ ) {
		if (v[i] == x)
			return i;
	}
}

//Vê se as casas estão nas posições certas
int confere(int *v, int *c, int tam)
{
	int i = 0;
	while (v[i] == c[i] && i < tam)
	{
		i++;
	}
	if (i == tam)
		return 1;

	return 0;
}