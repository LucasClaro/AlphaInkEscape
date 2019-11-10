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
ALLEGRO_BITMAP * usado = NULL;
bool aberto = false;



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
	for (i = 0; i < TAMANHO_INVENTARIO; i++)
	{
		if (prog->Inventario[i])
		{
			//bitmap, come�oX, come�oY, larg, alt, posX, posY, novaLarg, novaAlt, flags
			al_draw_scaled_bitmap(prog->Itens[i]->bitmap, 0, 0, prog->Itens[i]->largura, prog->Itens[i]->altura, 0, i * ALTURA_TELA / 10, prog->Itens[i]->largura * scale, prog->Itens[i]->altura * scale, 0);
			if (prog->inventClick[i])
				al_draw_bitmap(usado, 25, ((i * ALTURA_TELA / 10) + 25), 0);
		}		
	}
}

int abrirMapa(Progresso* prog) {
	al_draw_bitmap(prog->btnMiniMapa->bitmap, prog->btnMiniMapa->x, prog->btnMiniMapa->y, 0);
	int x = 0;
	int y = 0;


	if (aberto) {
		switch (prog->proximaSala) {
			case 1:
				break;
			case 2:
				x = LARGURA_TELA / 2 - 60;
				y = ALTURA_TELA / 4;
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				x = LARGURA_TELA / 2 - 60;
				y = ALTURA_TELA / 2;
				break;
			case 7:
				break;
			case 8:
				break;
		}
		al_draw_bitmap(prog->miniMapa->bitmap, prog->miniMapa->x, prog->miniMapa->y, 0);
		al_draw_text(prog->fonte, al_map_rgb(0,0,0), x,y,0, "X" );
	}
}

int loadFotoInvent()
{
	usado = al_load_bitmap("Imgs/apagar.png");
}

#endif
