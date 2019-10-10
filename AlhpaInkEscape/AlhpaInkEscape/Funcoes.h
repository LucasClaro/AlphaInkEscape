#include <stdio.h>
// Inclui o arquivo de cabeçalho da biblioteca Allegro 5
#include <allegro5/allegro.h>
// Inclui o cabeçalho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
// Inclui a coisa do mouse
#include <allegro5/allegro_native_dialog.h>

#include "Struct.h"

#ifndef Funcoes_H
#define Funcoes_H

// Desenha um bitmap dado um Objeto
void DesenharImagem(Objeto objeto) {
	al_draw_bitmap(objeto.bitmap, objeto.x, objeto.y, 0);
}

// Verifica se as coordenadas (X,Y) estão dentro de uma imagem
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

// Verifica se uma imagem está dentro da outra
int IsInsideImagem(Objeto *menor, Objeto *maior) {
	if (menor->x >= maior->x && menor->x + menor->largura <= maior->x + maior->largura && menor->y >= maior->y && menor->y + menor->altura <= maior->y + maior->altura) {
		return 1;
	}
	return 0;
}

int caregaInventario(Progresso *prog)
{
	int i;
	float scale = 0.7;
	for (i = 0; i < TAMANHO_INVENTARIO; i++)
	{
		if (prog->Inventário[i])
		{
			//bitmap, começoX, começoY, larg, alt, posX, posY, novaLarg, novaAlt, flags
			al_draw_scaled_bitmap(prog->Itens[i].bitmap, 0, 0, prog->Itens[i].largura, prog->Itens[i].altura, 0, i * ALTURA_TELA / 10, prog->Itens[i].largura * scale, prog->Itens[i].altura * scale, 0);
		}		
	}
}

#endif
