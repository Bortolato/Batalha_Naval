#ifndef BATALHA_NAVAL_H_
#define BATALHA_NAVAL_H_
#include <string>
#include "pilha.h"

    void Inicio();
    int Verifica_opcao(int op);
    int Verifica_dificuldade(int dif);



class Jogador {

    //string nome;
public:
    char meu_tabuleiro[15][15];
    char tabuleiro_inimigo[15][15];
    int numero_tiros = 0;
    char direcoes[11];
    int linhas[11];
    int colunas[11];
    int contador=0;
    int fragata=0, balizador=0, contratorpedeiro=0, cruzador=0, porta=0;
    
    // Construtor
    Jogador();
    char Posicao(int l, int c, int q);
    void Printar_layout();
    int Verifica(int l, int c, int tam, char direcao);
    void Insere(int l, int c, int tam, char direcao, char n);
    void Printar_naufragio();
    void Naufrago();
    int Quantidade_tiros();
    void Atirou(int l, int c, int a);
    int Recebe(int l, int c);
    int Confere();
    void Troca(int l, int c, char n,int q);
    ~Jogador();
};



class Jogo : public Jogador{

    Jogador j1, j2;

protected:
    //variável que seleciona o adversário: computador ou outro usuário
    int option;
    int dificuldade;

public:

    Jogo(int dif, int op);

    char Sorteio();

    void Modo_1();
    void Modo_2();
    void Voltar_Jogada(int j, int modo);
    ~Jogo();
};



class Batalha_atual: public Jogo{
    
public:
        Batalha_atual(int dif, int op);

        void Start();
};




#endif