#include <stdio.h>
// Inclui o arquivo de cabe�alho da biblioteca Allegro 5
#include <allegro5/allegro.h>
// Inclui o cabe�alho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
// Inclui a coisa do mouse
#include <allegro5/allegro_native_dialog.h>

#include "Struct.h"
#include "Fase1Binary.h"
#include "Fase2tabelaPeri.h"
#include "Fase5Brasil.h"
#include "Fase6Conta.h"
#include "Fase9TimeLine.h"
#include "Fase10Arco.h"
#include "Fase14PostIts.h"

#ifndef FaseController_H
#define FaseController_H

//Pega por referencia o lugar onde est� guardado o progresso do jogo
void selecionaFase(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, Progresso* progresso)
{
	switch (progresso->proximaSala)
	{
	case 0: 
		return;
	case 1: JogarFase1Binary(janela, fila_eventos, progresso);
		return;
	case 2: JogarFase2TabelaPeri(janela, fila_eventos, progresso);
		return;
	case 3: //
		return;
	case 4: //
		return;
	case 5: JogarFase5Brasil(janela, fila_eventos, progresso);
		return;
	case 6: JogarFase6Conta(janela, fila_eventos, progresso);
		return;
	case 7: //
		return;
	case 8: //
		return;
	case 9:
		JogarFase9TimeLine(janela, fila_eventos, progresso);
		return;
	case 10:
		JogarFase10Arco(janela, fila_eventos, progresso);
		return;
	case 14: JogarFase14PostIts(janela, fila_eventos, progresso);
		return;
	default: printf("Fase n�o encontrada"); return;
		break;
	}
}



#endif 
