#include <stdio.h>
// Inclui o arquivo de cabe�alho da biblioteca Allegro 5
#include <allegro5/allegro.h>
// Inclui o cabe�alho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
// Inclui a coisa do mouse
#include <allegro5/allegro_native_dialog.h>

#include "Struct.h"
#include "tabelaPeri.h"
#include "Fase4Binary.h"
#include "Fase0Conta.h"
//#include "Fase1.h"
//#include "Fase2.h"
#include "Fase5Brasil.h"
#include "Fase10Arco.h"

#ifndef FaseController_H
#define FaseController_H

//Pega por referencia o lugar onde est� guardado o progresso do jogo
void selecionaFase(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* progresso)
{
	switch (progresso->proximaSala)
	{
	case 0: JogarFase0Conta(janela, fila_eventos, progresso);
		return;
	case 1: JogarTabelaPeri(janela, fila_eventos, progresso);
		return;
	case 2: //JogarFaseArco(janela, fila_eventos, progresso);
		return;
	case 3: //JogarFase3Brasil(janela, fila_eventos, progresso);
		return;
	case 4: 
		JogarFase4Binary(janela, fila_eventos, progresso);
		return;
	case 5:
		JogarFaseBrasil(janela, fila_eventos, progresso);
		return;
	case 10:
		JogarFaseArco(janela, fila_eventos, progresso);
		return;
	default: printf("Fase n�o encontrada"); return;
		break;
	}
}



#endif 
