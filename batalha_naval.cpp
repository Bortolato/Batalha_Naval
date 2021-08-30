#include <string>
#include <iostream>
#include <ostream>
#include <time.h>
#include "batalha_naval.h"

using namespace std;


int main(){
	int op, dif;
	Inicio();
	cout << "\n\n\n--->Por favor, escolha o modo do jogo: \n\n\n__Digite 1 para derrotar o computador\n__Digite 2 para acabar com outro jogador\n";
	cin >> op;
	//Caso o jogador digite uma opção invalida
	while (Verifica_opcao(op)==-1){
		cout << "Opcao invalida. Digite novamente\n";
		cin >> op;
	}
	cin.ignore(1,'\n');
	system("clear");
	cout << "\nPor favor, escolha a dificuldade de jogo:\n\n--->Digite 1 para nivel Facil:\n\n_Podera voltar quantas jogadas quiser e seguir o jogo a partir desse ponto.\n_Os navios poderao estar apenas na vertical ou na horizontal.\n\n\n--->Digite 2 para nivel Medio:\n\n_Nao podera voltar jogadas.\n_Os navios poderao estar na vertical e/ou na horizontal.\n\n\n--->Digite 3 para nivel Dificil:\n\n_Nao podera voltar jogadas.\n_Os navios poderao estar na vertical e/ou na horizontal e/ou na diagonal.\n";
	cin >> dif;
	//Caso o jogador digite uma dif invalida
	while (Verifica_dificuldade(dif)==-1){
		cout << "Dificuldade invalida. Digite novamente\n";
		cin >> dif;
	}
	cin.ignore(1,'\n');

	Batalha_atual batalha(dif,op);

	batalha.Start();
	
	return 0;
}