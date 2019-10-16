#include <stdio.h>
// Inclui o arquivo de cabeçalho da biblioteca Allegro 5
#include <allegro5/allegro.h>
// Inclui o cabeçalho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
// Inclui a coisa do mouse
#include <allegro5/allegro_native_dialog.h>

#include "Struct.h"
//#include "Fase0.h"
//#include "Fase1.h"
//#include "Fase2.h"
#include "Fase3Brasil.h"
#include "FaseArco.h"

#ifndef FaseController_H
#define FaseController_H

//Pega por referencia o lugar onde está guardado o progresso do jogo
void selecionaFase(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* progresso)
{
	switch (progresso->proximaSala)
	{
	case 0: 
		JogarFase3Brasil(janela, fila_eventos, progresso);
		return;
	case 1: 
		JogarFaseTeste(janela, fila_eventos, progresso);
		return;
	default: printf("Fase não encontrada"); return;
		break;
	}
}



#endif 
