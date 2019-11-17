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
ALLEGRO_BITMAP* usado = NULL, * textoitens = NULL, * ordemBrasil = NULL, * ordemObras = NULL, * ordemElem = NULL, * ordemPaises = NULL;
// Vereifica se as coordenadas (X,Y) est�o dentro de uma imagem
int IsInside(int x, int y, Objeto *objeto) {
	if (x >= objeto->x && x <= (objeto->x + objeto->largura) && y >= objeto->y && y <= (objeto->y + objeto->altura)) {
		return 1;
	}
	return 0;
}

// Mapeia a dist�ncia entre o lugar do clique e o canto da imagem
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

int loadFotosGlobais()
{
	usado = al_load_bitmap("Imgs/jausada.png");
	textoitens = al_load_bitmap("Imgs/textoitens.png");
	ordemBrasil = al_load_bitmap("Imgs/Clicavel/ordemAni.png");
	ordemObras = al_load_bitmap("Imgs/Clicavel/ordemObras.png");
	ordemElem = al_load_bitmap("Imgs/Clicavel/ordemElem.png");
	ordemPaises = al_load_bitmap("Imgs/Clicavel/ordemPaises.png");
}

int destroyFotosGlobais()
{
	al_destroy_bitmap(usado);
	al_destroy_bitmap(textoitens);
	al_destroy_bitmap(ordemBrasil);
	al_destroy_bitmap(ordemObras);
	al_destroy_bitmap(ordemElem);
	al_destroy_bitmap(ordemPaises);
}

int abreOrdem(Progresso* prog)
{
	if (prog->inventClick[4])
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

int checaClickOrdem(int x, int y,Progresso* prog)
{
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

int limpaClick(Progresso* prog)
{
	if (prog->inventClick[4] || prog->inventClick[5] || prog->inventClick[6] || prog->inventClick[7])
	{
		prog->inventClick[4] = 0;
		prog->inventClick[5] = 0;
		prog->inventClick[6] = 0;
		prog->inventClick[7] = 0;
	}
}

#endif
