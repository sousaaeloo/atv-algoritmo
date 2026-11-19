#ifndef ATM_H
#define ATM_H
typedef enum { AGUARDANDO, AUTENTICANDO, MENU, OPERACAO } Estado;
typedef enum { INSERIR_CARTAO, SENHA_CORRETA, SENHA_INCORRETA, SELECIONAR_SAQUE, SELECIONAR_SALDO, CONCLUIR, CANCELAR } Evento;
typedef struct { Estado estado; int tentativas; int saldo; int operacao; } ATM;
void atm_iniciar(ATM *atm);
int atm_evento(ATM *atm, Evento evento);
#endif
