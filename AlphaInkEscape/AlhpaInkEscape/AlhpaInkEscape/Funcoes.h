#include <stdio.h>
// Inclui o arquivo de cabe�alho da biblioteca Allegro 5
#include <allegro5/allegro.h>
// Inclui o cabe�alho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
// Inclui a coisa do mouse
#include <allegro5/allegro_native_dialog.h>

#include "Struct.h"

#ifndef Funcoes_H
#define Funcoes_H

//Controle da música
bool tocando = true;
//Controle do minimapa
bool aberto = false;

//Imagens inventário
ALLEGRO_BITMAP* usado = NULL, * textoitens = NULL, * ordemBrasil = NULL, * ordemObras = NULL, * ordemElem = NULL, * ordemPaises = NULL, * fundoAsc = NULL, * semAcesso =  NULL;

// Vereifica se as coordenadas (X,Y) estão dentro de uma imagem
int IsInside(int x, int y, Objeto *objeto) {
	if (x >= objeto->x && x <= (objeto->x + objeto->largura) && y >= objeto->y && y <= (objeto->y + objeto->altura)) {
		return 1;
	}
	return 0;
}

// Mapeia a distância entre o lugar do clique e o canto da imagem
int MapearDistancia(int ponto, int c) {
	return ponto - c;
}

// Verifica se uma imagem sendo arrastada ultrapassou as bordas da tela
int VerificarBordas(int x, int y, Objeto *imagem) {
	if (x - imagem->cliqueX <= 0 || x - imagem->cliqueX + imagem->largura >= LARGURA_TELA || y - imagem->cliqueY <= 0 || y - imagem->cliqueY + imagem->altura >= ALTURA_TELA) {
		return 1;
	}
	return 0;
}

// Verifica se uma imagem est� dentro da outra
int IsInsideImagem(Objeto *menor, Objeto *maior) {
	if (menor->x >= maior->x && menor->x + menor->largura <= maior->x + maior->largura && menor->y >= maior->y && menor->y + menor->altura <= maior->y + maior->altura) {
		return 1;
	}
	return 0;
}

//Desenha os itens do inventário na tela
int caregaInventario(Progresso *prog)
{
	int i;
	float scale = 0.5;
	al_draw_bitmap(textoitens, 5, 70, 0);
	for (i = 0; i < TAMANHO_INVENTARIO; i++)
	{
		if (prog->Inventario[i])
		{
			//bitmap, come�oX, come�oY, larg, alt, posX, posY, novaLarg, novaAlt, flags
			al_draw_scaled_bitmap(prog->Itens[i]->bitmap, 0, 0, prog->Itens[i]->largura, prog->Itens[i]->altura, 0, 95 + (i * ALTURA_TELA / 10), prog->Itens[i]->largura * scale, prog->Itens[i]->altura * scale, 0);
			if (prog->inventClick[i])
				al_draw_bitmap(usado, 25, 95 + ((i * ALTURA_TELA / 10) + 25), 0);
		}		
	}
}

//Desenha o marcador de som e muta o jogo
void som(Progresso *prog) {

	al_draw_bitmap(prog->cenario->btnSom->bitmap, prog->cenario->btnSom->x, prog->cenario->btnSom->y,0);
	if (tocando) {
		prog->cenario->btnSom->bitmap = prog->cenario->comSom;
		al_set_audio_stream_gain(prog->cenario->musica, 1.0);
	}
	else {
		prog->cenario->btnSom->bitmap = prog->cenario->semSom;
		al_set_audio_stream_gain(prog->cenario->musica, 0.0);
	} 
}

//Controla o minimapa
void abrirMapa(Progresso* prog) {
	//Desenha o ícone e o X caso ele esteja aberto
	al_draw_bitmap(prog->cenario->btnMiniMapa->bitmap, prog->cenario->btnMiniMapa->x, prog->cenario->btnMiniMapa->y, 0);
	if(aberto)
		al_draw_bitmap(usado, prog->cenario->btnMiniMapa->x, prog->cenario->btnMiniMapa->y, 0);

	int x = 0;
	int y = 0;

	if (prog->proximaSala < 4)
		y = 185;
	else if (prog->proximaSala < 8)
		y = 285;
	else if (prog->proximaSala < 12)
		y = 375;
	else if (prog->proximaSala < 16)
		y = 470;

	if (prog->proximaSala == 1 || prog->proximaSala == 5 || prog->proximaSala == 9 || prog->proximaSala == 13)
		x = 372;
	else if (prog->proximaSala == 2 || prog->proximaSala == 6 || prog->proximaSala == 10 || prog->proximaSala == 14)
		x = 548;
	else if (prog->proximaSala == 3 || prog->proximaSala == 7 || prog->proximaSala == 11 || prog->proximaSala == 15)
		x = 760;

	//Desenha o mapa
	if (aberto) {
		//mapa
		al_draw_bitmap(prog->cenario->miniMapa->bitmap, prog->cenario->miniMapa->x, prog->cenario->miniMapa->y, 0);
			//(548, 181)
			//(762, 177)

			//(760, 292)
			//(550, 291)
			//(372, 292)

			//(369, 380)
			//(549, 380)
			//(762, 380)

			//(367, 470)
			//(549, 471)
			//(760, 471)

		//linha 1
		if(!prog->Salas[2])
			al_draw_bitmap(semAcesso, 355, 185, 0);
		if (!prog->Salas[6]) {
			al_draw_bitmap(semAcesso, 550, 185, 0);
			al_draw_bitmap(semAcesso, 744, 185, 0);
		}

		//linha 2
		if (!prog->Salas[6]) {
			al_draw_bitmap(semAcesso, 355, 285, 0);
			al_draw_bitmap(semAcesso, 744, 285, 0);
		}


		//linha 3
		if(!prog->Salas[10])
			al_draw_bitmap(semAcesso, 355, 375, 0);
		if (!prog->Salas[6]) {
			al_draw_bitmap(semAcesso, 550, 375, 0);
		}
		if(!prog->Salas[7])
			al_draw_bitmap(semAcesso, 744, 375, 0);
		
		
		//linha4
		if (!prog->Salas[10]) {
			al_draw_bitmap(semAcesso, 355, 470, 0);			
			al_draw_bitmap(semAcesso, 550, 470, 0);
		}			
		if(!prog->Salas[14])
			al_draw_bitmap(semAcesso, 744, 470, 0);
		
		
		//x
		al_draw_bitmap(prog->cenario->localizacao, x+80, y+30, 0);
	}
}

//Salva o jogo
FILE* tm;
void salvar(Progresso *prog) {
	int i;

	//Mostra p progresso antes de salvar
	/*for (i = 0; i < 17; i++) {
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

	fopen_s(&tm, "save.txt", "w");

	for (i = 0; i < 17; i++)
		fprintf_s(tm,"%d ", prog->Salas[i]);

	for (i = 0; i < 8; i++)
		fprintf_s(tm, "%d ", prog->Inventario[i]);

	fprintf_s(tm, "%d ", prog->inventCount);

	for (i = 0; i < 8; i++)
		fprintf_s(tm, "%d ", prog->inventClick[i]);

	fprintf_s(tm, "%d ", prog->linhaInGame);

	fprintf_s(tm, "%d ", prog->proximaSala);
	
	fclose(tm);
	prog->proximaSala = 0;
}

//Carrega as fotos do inventário
int loadFotosGlobais()
{
	usado = al_load_bitmap("Imgs/jausada.png");
	textoitens = al_load_bitmap("Imgs/textoitens.png");
	ordemBrasil = al_load_bitmap("Imgs/Clicavel/ordemAni.png");
	ordemObras = al_load_bitmap("Imgs/Clicavel/ordemObras.png");
	ordemElem = al_load_bitmap("Imgs/Clicavel/ordemElem.png");
	ordemPaises = al_load_bitmap("Imgs/Clicavel/ordemPaises.png");
	fundoAsc = al_load_bitmap("Imgs/Asc/fundoAsc4.png");
	semAcesso = al_load_bitmap("Imgs/Minimapa/bloc.png");
}

//Destroi as fotos do inventário/
int destroyFotosGlobais()
{
	al_destroy_bitmap(usado);
	al_destroy_bitmap(textoitens);
	al_destroy_bitmap(ordemBrasil);
	al_destroy_bitmap(ordemObras);
	al_destroy_bitmap(ordemElem);
	al_destroy_bitmap(ordemPaises);
	al_destroy_bitmap(fundoAsc);
	al_destroy_bitmap(semAcesso);
}

//Exibe os itens que podem ser abertos
int abreOrdem(Progresso* prog)
{
	if (prog->inventClick[3])
	{
		al_draw_bitmap(fundoAsc, 0, 0, 0);
	}
	else if (prog->inventClick[4])
	{
		al_draw_bitmap(ordemBrasil, 0, 0, 0);
	}
	else if (prog->inventClick[5])
	{
		al_draw_bitmap(ordemObras, 0, 0, 0);
	}
	else if (prog->inventClick[6])
	{
		al_draw_bitmap(ordemElem, 0, 0, 0);
	}
	else if (prog->inventClick[7])
	{
		al_draw_bitmap(ordemPaises, 0, 0, 0);
	}
}

//Vê qual item do inventário foi clicado
int checaClickOrdem(int x, int y,Progresso* prog)
{
	if (prog->Itens[3])
	{
		if (x >= 0 && x <= prog->Itens[3]->largura * 0.5 && y >= 310 && y <= 395) {
			prog->inventClick[3] = 1;
		}
	}
	if (prog->Itens[4] != NULL)
	{
		if (x >= 0 && x <= prog->Itens[4]->largura * 0.5 && y >= 385 && y <= 435)
		{
			//printf("certo");
			prog->inventClick[4] = 1;
		}
	}
	if (prog->Itens[5] != NULL)
	{
		if (x >= 0 && x <= prog->Itens[5]->largura * 0.5 && y >= 458 && y <= 458 + 136 / 2)
		{
			//printf("certo");
			prog->inventClick[5] = 1;
		}
	}
	if (prog->Itens[6] != NULL)
	{
		if (x >= 0 && x <= prog->Itens[6]->largura * 0.5 && y >= 528 && y <= 528 + 100 / 2)
		{
			//printf("certo");
			prog->inventClick[6] = 1;
		}
	}
	if (prog->Itens[7] != NULL)
	{
		if (x >= 0 && x <= prog->Itens[7]->largura * 0.5 && y >= 600 && y <= 600 + 136 / 2)
		{
			//printf("certo");
			prog->inventClick[7] = 1;
		}
	}
}

//Zera as vars de controle do inventário
int limpaClick(Progresso* prog)
{
	if (prog->inventClick[3] || prog->inventClick[4] || prog->inventClick[5] || prog->inventClick[6] || prog->inventClick[7])
	{
		prog->inventClick[3] = 0;
		prog->inventClick[4] = 0;
		prog->inventClick[5] = 0;
		prog->inventClick[6] = 0;
		prog->inventClick[7] = 0;
	}
}

#endif
