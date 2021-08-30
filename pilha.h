#ifndef PILHA_H_
#define PILHA_H_

using namespace std;
template< typename P >

class Pilha{

    int cap; // número de elementos na Pilha
    int topo; // localização do elemento superior (-1 significa vazio)
    P *PilhaPtr; // ponteiro para a representação interna da Pilha

public:

    Pilha(){
        PilhaPtr = nullptr;      
        topo = 0;
        cap = 0;
    }

    Pilha< P > ( int p ){

        topo = 0;  // Pilha inicialmente vazia
        cap = p;
        PilhaPtr = new P[ p ]; // aloca memória para elementos
    }

    ~Pilha(){
    }

    bool Pilha_cheia(){ //determina se a pilha esta cheia

        return (topo == cap);
    }

    bool Pilha_vazia(){ // determina se a Pilha está vazia

        return (topo == 0);
    } // fim da função Pilha_vazia

    void Empilhar( P EmpilharValue ){
        if(topo >= cap) throw -99;

        PilhaPtr[ ++topo ] = EmpilharValue; // insere item em Pilha

    } // fim do template de função Empilhar

    P Desempilhar(){

       if ( cap <= 0 ) throw -99;

       return PilhaPtr[ topo-- ]; // remove item da Pilha 
    }// fim do template de função Desempilhar

    int getPosTopo(){
        if(topo == 0) throw -99;
        return topo - 1;
    }

    void limparPilha(){
        topo = 0;
    }
};
/*
int main(){

    Pilha< int > p(5);
    p.Empilhar(1);
    p.Empilhar(6);
    p.Empilhar(4);
    p.Empilhar(8);
    p.Empilhar(9);

    while(!p.Pilha_vazia() ){
        cout << "Pilha dempilhada: " << p.Desempilhar() << endl;
    }

    return 0;
*/
#endif
