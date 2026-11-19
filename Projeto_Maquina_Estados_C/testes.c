#include <assert.h>
#include <stdio.h>
#include "atm.h"
static int verificacoes=0;
#define CHECK(x) do { assert(x); verificacoes++; } while(0)
static void estados(void) {
 ATM a; atm_iniciar(&a); CHECK(a.estado==AGUARDANDO);
 CHECK(atm_evento(&a,INSERIR_CARTAO)); CHECK(a.estado==AUTENTICANDO);
 CHECK(atm_evento(&a,SENHA_CORRETA)); CHECK(a.estado==MENU);
 CHECK(atm_evento(&a,SELECIONAR_SALDO)); CHECK(a.estado==OPERACAO);
}
static void transicoes(void) {
 ATM a; atm_iniciar(&a);
 CHECK(atm_evento(&a,INSERIR_CARTAO)); CHECK(atm_evento(&a,SENHA_INCORRETA)); CHECK(a.estado==AUTENTICANDO);
 CHECK(atm_evento(&a,SENHA_CORRETA)); CHECK(atm_evento(&a,SELECIONAR_SAQUE)); CHECK(atm_evento(&a,CONCLUIR)); CHECK(a.saldo==80);
 CHECK(atm_evento(&a,SELECIONAR_SALDO)); CHECK(atm_evento(&a,CONCLUIR)); CHECK(a.saldo==80);
 CHECK(atm_evento(&a,CANCELAR)); CHECK(a.estado==AGUARDANDO);
 atm_iniciar(&a); CHECK(atm_evento(&a,INSERIR_CARTAO));
 CHECK(atm_evento(&a,SENHA_INCORRETA)); CHECK(atm_evento(&a,SENHA_INCORRETA)); CHECK(atm_evento(&a,SENHA_INCORRETA)); CHECK(a.estado==AGUARDANDO);
 for(int i=0;i<3;i++) { atm_iniciar(&a); CHECK(atm_evento(&a,INSERIR_CARTAO));
   if(i==0) CHECK(atm_evento(&a,CANCELAR));
   if(i==1) { CHECK(atm_evento(&a,SENHA_CORRETA)); CHECK(atm_evento(&a,CANCELAR)); }
   if(i==2) { CHECK(atm_evento(&a,SENHA_CORRETA)); CHECK(atm_evento(&a,SELECIONAR_SALDO)); CHECK(atm_evento(&a,CANCELAR)); }
   CHECK(a.estado==AGUARDANDO);
 }
}
static void caminhos(void) {
 ATM a;
 atm_iniciar(&a); CHECK(!atm_evento(&a,CONCLUIR)); CHECK(a.estado==AGUARDANDO);
 atm_iniciar(&a); CHECK(atm_evento(&a,INSERIR_CARTAO)); CHECK(atm_evento(&a,SENHA_INCORRETA)); CHECK(atm_evento(&a,SENHA_CORRETA)); CHECK(a.estado==MENU);
 atm_iniciar(&a); CHECK(atm_evento(&a,INSERIR_CARTAO)); CHECK(atm_evento(&a,SENHA_CORRETA)); CHECK(atm_evento(&a,SELECIONAR_SAQUE)); CHECK(atm_evento(&a,CONCLUIR)); CHECK(a.saldo==80);
 atm_iniciar(&a); a.saldo=10; CHECK(atm_evento(&a,INSERIR_CARTAO)); CHECK(atm_evento(&a,SENHA_CORRETA)); CHECK(!atm_evento(&a,SELECIONAR_SAQUE)); CHECK(a.estado==MENU);
}
int main(void) { estados(); transicoes(); caminhos(); printf("OK: %d verificacoes automatizadas aprovadas\n",verificacoes); return 0; }
