#include "atm.h"
void atm_iniciar(ATM *a) { a->estado=AGUARDANDO; a->tentativas=0; a->saldo=100; a->operacao=0; }
int atm_evento(ATM *a, Evento e) {
    if (e==CANCELAR && a->estado!=AGUARDANDO) { a->estado=AGUARDANDO; a->tentativas=0; a->operacao=0; return 1; }
    switch(a->estado) {
        case AGUARDANDO:
            if(e==INSERIR_CARTAO) { a->estado=AUTENTICANDO; return 1; } break;
        case AUTENTICANDO:
            if(e==SENHA_CORRETA) { a->estado=MENU; a->tentativas=0; return 1; }
            if(e==SENHA_INCORRETA) { a->tentativas++; if(a->tentativas>=3) { a->estado=AGUARDANDO; a->tentativas=0; } return 1; } break;
        case MENU:
            if(e==SELECIONAR_SAQUE && a->saldo>=20) { a->operacao=1; a->estado=OPERACAO; return 1; }
            if(e==SELECIONAR_SALDO) { a->operacao=2; a->estado=OPERACAO; return 1; } break;
        case OPERACAO:
            if(e==CONCLUIR) { if(a->operacao==1) a->saldo-=20; a->operacao=0; a->estado=MENU; return 1; } break;
    }
    return 0;
}
