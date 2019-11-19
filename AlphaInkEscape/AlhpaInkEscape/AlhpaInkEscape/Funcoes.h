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
ALLEGRO_BITMAP* usado = NULL, * textoitens = NULL;
bool tocando = true;
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

void abrirMapa(Progresso* prog) {
	al_draw_bitmap(prog->cenario->btnMiniMapa->bitmap, prog->cenario->btnMiniMapa->x, prog->cenario->btnMiniMapa->y, 0);
	int x = 0;
	int y = 0;
	ALLEGRO_BITMAP* semAcesso = al_load_bitmap("Imgs/Minimapa/bloc.png");
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
			al_draw_bitmap(semAcesso, 378, 178, 0);
		if (!prog->Salas[6]) {
			al_draw_bitmap(semAcesso, 548, 181, 0);
			al_draw_bitmap(semAcesso, 762, 177, 0);
		}

		//linha 2
		if (!prog->Salas[6]) {
			al_draw_bitmap(semAcesso, 372, 292, 0);
			al_draw_bitmap(semAcesso, 760, 291, 0);
		}


		//linha 3
		if(!prog->Salas[10])
			al_draw_bitmap(semAcesso, 369, 380, 0);
		if (!prog->Salas[6]) {
			al_draw_bitmap(semAcesso, 549, 380, 0);
		}
		if(!prog->Salas[7])
			al_draw_bitmap(semAcesso, 762, 380, 0);
		
		
		//linha4
		if (!prog->Salas[10]) {
			al_draw_bitmap(semAcesso, 367, 470, 0);			
			al_draw_bitmap(semAcesso, 549, 471, 0);
		}			
		if(!prog->Salas[14])
			al_draw_bitmap(semAcesso, 760, 471, 0);
		
		
		//x
		al_draw_text(prog->cenario->fonte, al_map_rgb(0, 0, 0), x, y, 0, "X");
	}
}



int loadFotoInvent()
{
	usado = al_load_bitmap("Imgs/jausada.png");
	textoitens = al_load_bitmap("Imgs/textoitens.png");
}

#endif
