#include <stdio.h>
// Inclui o arquivo de cabeçalho da biblioteca Allegro 5
#include <allegro5/allegro.h>
// Inclui o cabeçalho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
// Inclui a coisa do mouse
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#ifndef Struct_H
#define Struct_H

// Tamanho da tela
#define LARGURA_TELA 1280
#define ALTURA_TELA 720
// Tamanho do Inventário
#define TAMANHO_INVENTARIO 8

// Struct para imagens
typedef struct Obj
{
	ALLEGRO_BITMAP* bitmap;
	int x;
	int y;
	int largura;
	int altura;
	int cliqueX;
	int cliqueY;

} Objeto;

typedef struct scene {
	ALLEGRO_BITMAP* setaCima;
	ALLEGRO_BITMAP* setaBaixo;
	ALLEGRO_BITMAP* setaEsquerda;
	ALLEGRO_BITMAP* setaDireita;
	ALLEGRO_BITMAP* cadeado;
	ALLEGRO_BITMAP* background;
	ALLEGRO_BITMAP* comSom;
	ALLEGRO_BITMAP* semSom;
	ALLEGRO_SAMPLE* somSeta;
	ALLEGRO_AUDIO_STREAM* musica;
	Objeto* btnSom;
	Objeto* miniMapa;
	Objeto* btnMiniMapa;
	Objeto* xMiniMapa;
	Objeto* saida;
	ALLEGRO_FONT* fonte;
	Objeto* PostIt2;
	Objeto* postIt3;
	Objeto* postIt4;
	Objeto* sobreBi;
	Objeto* miniatura;
	Objeto* miniaturaObras;
	Objeto* miniaturaElem;
	Objeto* miniaturaPaises;
} Cenario;

// Struct de progresso
typedef struct prog
{
	int proximaSala;
	int Gameover;
	int Salas[17];// Progresso de cada sala. Deixei 17 pois a fase 0 vai ser o menu. 
	int Inventario[TAMANHO_INVENTARIO];// Ter ou não o item
	Objeto* Itens[TAMANHO_INVENTARIO];// Item propriamente dito
	int inventCount;//contador de itens no  inventario
	int inventClick[TAMANHO_INVENTARIO];//saber qual item ja foi usado no inventario
	int linhaInGame;
	Cenario* cenario;
	
} Progresso;

typedef struct fila {
	int vetor[11];
	int tamanho, inicio, fim, total;
}Fila;


#endif
