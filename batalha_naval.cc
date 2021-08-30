#include <string>
#include <iostream>
#include <random>
#include <time.h>
#include <stdlib.h>
#include "batalha_naval.h"
#include "pilha.h"

using namespace std;

    void Inicio(){
        system("clear");
        cout<<"\n\n\n\n\n\n\n";
        cout <<"                                     ||||||||  ||||||||  ||||||||  ||||||||  ||        ||    ||  ||||||||\n"; 
        cout <<"                                     ||    ||  ||    ||     ||     ||    ||  ||        ||    ||  ||    ||\n";
        cout <<"                                     ||||||||  ||||||||     ||     ||||||||  ||        ||||||||  ||||||||\n";
        cout <<"                                     ||    ||  ||    ||     ||     ||    ||  ||        ||    ||  ||    ||\n";
        cout <<"                                     ||||||||  ||    ||     ||     ||    ||  ||||||||  ||    ||  ||    ||\n";
        cout<<"\n\n\n\n\n";
        cout <<"                                             |||   ||  ||||||||  ||    ||  ||||||||  ||      \n"; 
        cout <<"                                             ||||  ||  ||    ||   ||  ||   ||    ||  ||      \n";
        cout <<"                                             || || ||  ||||||||   ||  ||   ||||||||  ||      \n";
        cout <<"                                             ||  ||||  ||    ||    ||||    ||    ||  ||      \n";
        cout <<"                                             ||   |||  ||    ||     ||     ||    ||  ||||||||\n";      
    }
    int Verifica_opcao(int op){
        if (op > 2 || op < 1){return -1;}
        else{return 0;}
    }
    int Verifica_dificuldade(int dif){
        if (dif > 3 || dif < 1){return -1;}
        else{return 0;}
    }


    //!!FUNÇOES JOGADOR!!
    Jogador::Jogador(){
        for(int i=0; i<15; i++){
            for(int j=0; j<15; j++){
                meu_tabuleiro[i][j]= '~';
                tabuleiro_inimigo[i][j]= '~';
            }
        }}
    Jogador::~Jogador(){}

    void Jogador::Printar_layout(){
        int i, j;
        cout << "\n\n\n                           SEU TABULEIRO:                        \t                             TABULEIRO INIMIGO:\n\n";
        cout << "        A | B | C | D | E | F | G | H | I | J | K | L | M | N | O |\t     A | B | C | D | E | F | G | H | I | J | K | L | M | N | O | "<<endl;
        for(i=0; i<15; i++){
            if (i<9){cout << "     "<< (i+1) << "  ";}
            if (i>=9){cout << "    "<< (i+1) << "  ";}
            for(j=0; j<15; j++){
                cout << meu_tabuleiro[i][j] << " | ";
            }
            cout << "\t";
            if (i<9){cout << "  "<< (i+1) << "  ";}
            if (i>=9){cout << " "<< (i+1) << "  ";}
            for(j=0; j<15; j++){
                cout << tabuleiro_inimigo[i][j] << " | ";
            }
            cout << "\n";
        }
        cout <<"\n        LEGENDA:"<<endl;
        cout <<"        | ~ | Água"<<endl;
        cout <<"        | $ | Acertou um navio"<<endl;
        cout <<"        | o | Acertou água"<<endl;
        cout <<"        | X | Navio naufragado"<<endl;}

    char Jogador::Posicao(int l, int c, int q){
        if(q==1)return tabuleiro_inimigo[l][c];
        if(q==0)return meu_tabuleiro[l][c];
        return '~';
    }

    int Jogador::Verifica(int l, int c, int tam, char direcao){

        //caso tenha passado do tamanho do meu_tabuleiro
        if ((l+tam)>14 || (c+tam)>14) return 0;
        switch(direcao){

            //verifica horizontal:
            case 'H':    
             for(int i=c; i < (c+tam); i++){
                    if (meu_tabuleiro[l][i] != '~' || meu_tabuleiro[l][i] == 'F' || meu_tabuleiro[l][i] == 'B' || meu_tabuleiro[l][i] == 'C' || meu_tabuleiro[l][i] == 'T' || meu_tabuleiro[l][i] == 'P'){
                       return 0;
                    }
             }return 1;

            //verifica vertical:
             case 'V':
             for(int i=l; i < (l+tam); i++){
                    if (meu_tabuleiro[i][c] != '~' || meu_tabuleiro[i][c] == 'F' || meu_tabuleiro[i][c] == 'B' || meu_tabuleiro[i][c] == 'C' || meu_tabuleiro[i][c] == 'T' || meu_tabuleiro[i][c] == 'P'){
                        return 0;
                    }
             }return 1;

            //verifica diagonal superior
             case 'S':    
             for(int i=l; i > (l-tam); i--){
                if (meu_tabuleiro[i][c]!= '~' || meu_tabuleiro[i][c] == 'F' || meu_tabuleiro[i][c] == 'B' || meu_tabuleiro[i][c] == 'C' || meu_tabuleiro[i][c] == 'T' || meu_tabuleiro[i][c] == 'P'){
                    return 0;
                }
                c++;
             }return 1;

            //verifica diagonal inferior
             case 'I':    
             for(int i=l; i < (l+tam); i++){
                if (meu_tabuleiro[i][c] != '~' || meu_tabuleiro[i][c] == 'F' || meu_tabuleiro[i][c] == 'B' || meu_tabuleiro[i][c] == 'C' || meu_tabuleiro[i][c] == 'T' || meu_tabuleiro[i][c]  == 'P'){
                    return 0;
                }
                c++;
             }return 1;
        }    
        return 1;}

    void Jogador::Insere(int l, int c, int tam, char direcao, char n){
        
        linhas[contador] = l;
        colunas[contador] = c;
        direcoes[contador] = direcao;
        contador++;

        switch(direcao){

            //insere horizontal:
            case 'H':    
             for(int i=c; i < (c+tam); i++){
                meu_tabuleiro[l][i] = n;
                     
             }break;

            //insere vertical:
             case 'V':
             for(int i=l; i < (l+tam); i++){
                meu_tabuleiro[i][c] = n;
             }break;

            //insere diagonal superior
             case 'S':    
             for(int i=l; i > (l-tam); i--){
                    meu_tabuleiro[i][c] = n;
                    c++;
             }break;

            //insere diagonal inferior
             case 'I':    
             for(int i=l; i < (l+tam); i++){
                    meu_tabuleiro[i][c] = n;
                    c++;
             }break;
        }    }

    void Jogador::Printar_naufragio(){
        cout <<"\n        Naufragaram:\n\n";
        cout <<"        ->" <<fragata << " de 3 Fragatas \n";
        cout <<"        ->" <<balizador << " de 3 Balizadores\n";
        cout <<"        ->" <<contratorpedeiro << " de 2 Contratorpedeiros\n";
        cout <<"        ->" <<cruzador << " de 2 Cruzadores\n";
        cout <<"        ->" <<porta << " de 1 Porta-avioes\n";}

    void Jogador::Naufrago(){
        int tamanho;
        char navio;
        for (int i =0; i<11; i++){
            if(i<3){tamanho=2;navio='F';}
            if(i>2 && i<6){tamanho=2;navio='B';}
            if(i>5 && i<8){tamanho=3;navio='T';}
            if(i>7 && i<9){tamanho=3;navio='C';}
            if(i==10){tamanho=4;navio='P';}
            int l = linhas[i];
            int c = colunas[i];
            int contador=0;

        switch(direcoes[i]){
            //verifica horizontal:
            case 'H':    
             for(int i=c; i < (c+tamanho); i++){
                    if (meu_tabuleiro[l][i] == '$'){
                        contador++;
                    }
             }if (contador == tamanho){
                switch(navio){
                    case 'F':
                        for(int i=c; i < (c+tamanho); i++){meu_tabuleiro[l][i] = 'X';}
                        fragata++;break;
                    case 'B':
                        for(int i=c; i < (c+tamanho); i++){meu_tabuleiro[l][i] = 'X';}
                        balizador++;break;
                    case 'T':
                        for(int i=c; i < (c+tamanho); i++){meu_tabuleiro[l][i] = 'X';}
                        contratorpedeiro++;break;
                    case 'C':
                        for(int i=c; i < (c+tamanho); i++){meu_tabuleiro[l][i] = 'X';}
                        cruzador++;break;
                    case 'P':
                        for(int i=c; i < (c+tamanho); i++){meu_tabuleiro[l][i] = 'X';}
                        porta++;break;
                }
             }break;
            //verifica vertical:
             case 'V':
             for(int i=l; i < (l+tamanho); i++){
                    if (meu_tabuleiro[i][c] == '$'){
                        contador++;
                    }
             }if (contador == tamanho){
                switch(navio){
                    case 'F':
                        for(int i=l; i < (l+tamanho); i++){meu_tabuleiro[i][c] = 'X';}
                        fragata++;break;
                    case 'B':
                        for(int i=l; i < (l+tamanho); i++){meu_tabuleiro[i][c] = 'X';}
                        balizador++;break;
                    case 'T':
                        for(int i=l; i < (l+tamanho); i++){meu_tabuleiro[i][c] = 'X';}
                        contratorpedeiro++;break;
                    case 'C':
                        for(int i=l; i < (l+tamanho); i++){meu_tabuleiro[i][c] = 'X';}
                        cruzador++;break;
                    case 'P':
                        for(int i=l; i < (l+tamanho); i++){meu_tabuleiro[i][c] = 'X';}
                        porta++;break;
                }
             }break;
            //verifica diagonal superior
             case 'S':    
             for(int i=l; i > (l-tamanho); i--){
                if (meu_tabuleiro[i][c] == '$'){
                    contador++;
                }
                c++;
             }if (contador == tamanho){
                switch(navio){
                    case 'F':
                        c-=tamanho;
                        for(int i=l; i > (l-tamanho); i--){meu_tabuleiro[i][c] = 'X';c++;}
                        fragata++;break;
                    case 'B':
                        c-=tamanho;
                        for(int i=l; i > (l-tamanho); i--){meu_tabuleiro[i][c] = 'X';c++;}
                        balizador++;break;
                    case 'T':
                        c-=tamanho;
                        for(int i=l; i > (l-tamanho); i--){meu_tabuleiro[i][c] = 'X';c++;}
                        contratorpedeiro++;break;
                    case 'C':
                        c-=tamanho;
                        for(int i=l; i > (l-tamanho); i--){meu_tabuleiro[i][c] = 'X';c++;}
                        cruzador++;break;
                    case 'P':
                        c-=tamanho;
                        for(int i=l; i > (l-tamanho); i--){meu_tabuleiro[i][c] = 'X';c++;}
                        porta++;break;
                }
             }break;
             //verifica diagonal inferior
             case 'I':    
             for(int i=l; i < (l+tamanho); i++){
                if (meu_tabuleiro[i][c] == '$'){
                    contador++;
                }
                c++;
             }if (contador == tamanho){
                switch(navio){
                    case 'F':
                        c-=tamanho;
                        for(int i=l; i < (l+tamanho); i++){meu_tabuleiro[i][c] = 'X';c++;}
                        fragata++;break;
                    case 'B':
                        c-=tamanho;
                        for(int i=l; i < (l+tamanho); i++){meu_tabuleiro[i][c] = 'X';c++;}
                        balizador++;break;
                    case 'T':
                        c-=tamanho;
                        for(int i=l; i < (l+tamanho); i++){meu_tabuleiro[i][c] = 'X';c++;}
                        contratorpedeiro++;break;
                    case 'C':
                        c-=tamanho;
                        for(int i=l; i < (l+tamanho); i++){meu_tabuleiro[i][c] = 'X';c++;}
                        cruzador++;break;
                    case 'P':
                        c-=tamanho;
                        for(int i=l; i < (l+tamanho); i++){meu_tabuleiro[i][c] = 'X';c++;}
                        porta++;break;
                }
             }break;
        }
        }}

    int Jogador::Quantidade_tiros(){
        return numero_tiros;}

    void Jogador::Atirou(int l, int c, int a){
        if (a == 0){
            tabuleiro_inimigo[l][c] = 'o';
        }else{
            tabuleiro_inimigo[l][c] = '$';
        }
        numero_tiros++;
        cout<<"Numero de tiros:  "<<numero_tiros<<endl; }

    //Se acertar em algum barco a funcao retorna 1, caso contrario 0
    int Jogador::Recebe(int l, int c){
        if (meu_tabuleiro[l][c] == '~'){
            meu_tabuleiro[l][c] = 'o';
            return 0;
        }else{
            meu_tabuleiro[l][c] = '$';
            return 1;
        }
        return 32;}

    //Se o metodo retornar 1 significa que todos os navios naufragaram e o outro jogador ganhou
    int Jogador::Confere(){
        int soma=0;
        soma = (fragata+balizador+contratorpedeiro+cruzador+porta);
        if (soma == 11){
            return 1;
        }else{
            return 0;
        }}

    void Jogador::Troca(int l, int c, char n,int q){
        if (q == 0){
            meu_tabuleiro[l][c] = n;
        }
        if (q == 1){
            tabuleiro_inimigo[l][c] = n;
        }}
















    //!!FUNÇÕES JOGO!!
    Jogo::Jogo(int dif, int op):dificuldade(dif), option(op){}

    char Jogo::Sorteio(){
        char direcao[4]={'V','H','S','I'};
        int sorteio;
        if(dificuldade == 1 || dificuldade == 2){
            sorteio = rand() %2;
            return direcao[sorteio];
        }
        if(dificuldade == 3){
            sorteio = rand() %4;
            return direcao[sorteio];
        }
        return 'p';
    }
        
    void Jogo::Modo_1(){

        //stack pilhal = new 
        bool flag = false;
        int linha=0, coluna=0, tamanho;
        char navio;
        char dir;
        string continuar, tiro;
        char aux_linha[2];
        Pilha< int > p1l(50);
        Pilha< int > p1c(50);
        Pilha< char > p1t(50);
        Pilha< int > p2l(50);
        Pilha< int > p2c(50);
        Pilha< char > p2t(50);
        srand(time(NULL));      
//insere apenas na vertical ou horizontal
        if (dificuldade == 1){

            dir = Sorteio();
            for (int i =0; i<11; i++){
                if(i<3){tamanho=2;navio='F';}
                if(i>2 && i<6){tamanho=2;navio='B';}
                if(i>5 && i<8){tamanho=3;navio='T';}
                if(i>7 && i<9){tamanho=3;navio='C';}
                if(i==10){tamanho=4;navio='P';}
                
                do{
                linha = rand() %15;
                coluna = rand() %15;
                }while((j1.Verifica(linha, coluna, tamanho, dir)) == 0);
                j1.Insere(linha, coluna, tamanho, dir, navio);

                do{
                linha = rand() %15;
                coluna = rand() %15;
                }while((j2.Verifica(linha, coluna, tamanho, dir)) == 0);
                j2.Insere(linha, coluna, tamanho, dir, navio);
            }
        }
//insere na vertical e/ou horizontal
        if (dificuldade == 2){

            for (int i =0; i<11; i++){

                dir = Sorteio();

                if(i<3){tamanho=2;navio='F';}
                if(i>2 && i<6){tamanho=2;navio='B';}
                if(i>5 && i<8){tamanho=3;navio='T';}
                if(i>7 && i<9){tamanho=3;navio='C';}
                if(i==10){tamanho=4;navio='P';}
                
                do{
                linha = rand() %15;
                coluna = rand() %15;
                }while((j1.Verifica(linha, coluna, tamanho, dir)) == 0);
                j1.Insere(linha, coluna, tamanho, dir, navio);

                do{
                linha = rand() %15;
                coluna = rand() %15;
                }while((j2.Verifica(linha, coluna, tamanho, dir)) == 0);
                j2.Insere(linha, coluna, tamanho, dir, navio);
            }
        }
//insere na vertical e/ou horizontal e/ou diagonal
        if (dificuldade == 3){

            for (int i =0; i<11; i++){

                dir = Sorteio();

                if(i<3){tamanho=2;navio='F';}
                if(i>2 && i<6){tamanho=2;navio='B';}
                if(i>5 && i<8){tamanho=3;navio='T';}
                if(i>7 && i<9){tamanho=3;navio='C';}
                if(i==10){tamanho=4;navio='P';}
                do{
                linha = rand() %15;
                coluna = rand() %15;
                }while((j1.Verifica(linha, coluna, tamanho, dir)) == 0);
                j1.Insere(linha, coluna, tamanho, dir, navio);

                do{
                linha = rand() %15;
                coluna = rand() %15;
                }while((j2.Verifica(linha, coluna, tamanho, dir)) == 0);
                j2.Insere(linha, coluna, tamanho, dir, navio);
            }
        }
//guerra
        int t;
        system("clear");       
        while( j1.Quantidade_tiros() <=50 ){
            cout << "----------JOGADOR 1----------"<<endl;
            cout <<"\nDeseja continuar o jogo?[S/N]  ";
//leitura e verificacao de continuar
            do{
                if(flag){cout << "Entrada invalida. Deseja continuar o jogo?[S/N]  ";}
                getline(cin, continuar);
            //    cout << "\n"<< continuar;
                if(continuar[0] != 'N' || continuar[0] != 'S' || continuar[0] != 'n' || continuar[0] != 's'){flag = true;}
                if(continuar[0] == 'N' || continuar[0] == 'S' || continuar[0] == 'n' || continuar[0] == 's'){flag = false;}
            }while(flag);
            if(continuar[0] == 'N' || continuar[0] == 'n'){
                system("clear");
                cout << "\n\n\n\n----------Quem sabe na proxima jogador 1----------\n";
                cout << "----------Computador Venceu!----------\n\n\n\n\n\n";
                break;
            }
//segue a guerra
            system("clear");
            j1.Printar_layout();
            cout <<"\nOnde voce quer atirar?  ";
            do{ 
                if(flag){cout << "Entrada invalida. Onde voce quer atirar?  ";}
                getline(cin,tiro);  
                aux_linha[0] = tiro[1];
                aux_linha[1] = tiro[2];
                linha = atoi(aux_linha);
                coluna = tiro[0];
                coluna-= 65;
                linha--;
                cout << "coluna: "<< coluna <<endl;
                if(linha <0 || linha>14 || coluna <0 || coluna >14){flag=true;}
                if(linha >=0 && linha<=14 && coluna >=0 && coluna <=14){flag=false;}
                if(!flag && j1.Posicao(linha,coluna,1) != '~'){flag=true;}
            }while(flag);

            p1l.Empilhar(linha);
            p1c.Empilhar(coluna);
            navio = j2.Posicao(linha,coluna,0);
            p1t.Empilhar(navio);

            t = j2.Recebe(linha, coluna);
            j1.Atirou(linha,coluna,t);
            j2.Naufrago();
            if(t){
                system("clear");
                j1.Printar_layout();
                j2.Printar_naufragio();
                cout<<"        \nAcertou um navio!\n";
                system("sleep 3");
            }else{
                system("clear");
                j1.Printar_layout();
                j2.Printar_naufragio();                
            }
            if (j2.Confere() == 1){
                system("clear");
                cout << "\n\t----------Todas as embarcacoes foram abatidas----------";
                cout << "\n\n\t----------PARABENS VOCE VENCEU----------\n";
                break;   
            }
//salvar jogadas
            if(dificuldade == 1){
                cout << "        Deseja voltar jogada?[S/N]";
                do{
                if(flag){cout << "Entrada invalida. Deseja voltar jogada?[S/N]  ";}
                getline(cin, continuar);
                if(continuar[0] != 'N' || continuar[0] != 'S' || continuar[0] != 'n' || continuar[0] != 's'){flag = true;}
                if(continuar[0] == 'N' || continuar[0] == 'S' || continuar[0] == 'n' || continuar[0] == 's'){flag = false;}
                }while(flag);
                if(continuar[0] == 's' || continuar[0] == 'S'){
                    Voltar_Jogada(1,1);
                }
            }
            linha = rand() %15;
            coluna = rand() %15;

            p2l.Empilhar(linha);
            p2c.Empilhar(coluna);
            navio = j1.Posicao(linha,coluna,0);
            p2t.Empilhar(navio);

            t = j1.Recebe(linha, coluna);
            j2.Atirou(linha,coluna,t);
            j1.Naufrago();
            if (j1.Confere() == 1){
                system("clear");
                cout << "\n\n\n\n----------Quem sabe na proxima jogador 1----------\n";
                cout << "----------Computador Venceu----------\n\n\n\n\n\n";
                break;
            }
            system("clear");
            j1.Printar_layout();
        }
    }

    void Jogo::Modo_2(){
        //j1.Printar_layout();
        bool flag = false;
        int linha=0, coluna=0, tamanho;
        char navio;
        char dir;
        string continuar, tiro;
        char aux_linha[2];
        Pilha< int > p1l(50);
        Pilha< int > p1c(50);
        Pilha< char > p1t(50);
        Pilha< int > p2l(50);
        Pilha< int > p2c(50);
        Pilha< char > p2t(50);  
        srand(time(NULL));      
//insere apenas na vertical ou horizontal
        if (dificuldade == 1){

            dir = Sorteio();
            for (int i =0; i<11; i++){
                if(i<3){tamanho=2;navio='F';}
                if(i>2 && i<6){tamanho=2;navio='B';}
                if(i>5 && i<8){tamanho=3;navio='T';}
                if(i>7 && i<9){tamanho=3;navio='C';}
                if(i==10){tamanho=4;navio='P';}
                
                do{
                linha = rand() %15;
                coluna = rand() %15;
                }while((j1.Verifica(linha, coluna, tamanho, dir)) == 0);
                j1.Insere(linha, coluna, tamanho, dir, navio);

                do{
                linha = rand() %15;
                coluna = rand() %15;
                }while((j2.Verifica(linha, coluna, tamanho, dir)) == 0);
                j2.Insere(linha, coluna, tamanho, dir, navio);
            }
        }
//insere na vertical e/ou horizontal
        if (dificuldade == 2){

            for (int i =0; i<11; i++){

                dir = Sorteio();

                if(i<3){tamanho=2;navio='F';}
                if(i>2 && i<6){tamanho=2;navio='B';}
                if(i>5 && i<8){tamanho=3;navio='T';}
                if(i>7 && i<9){tamanho=3;navio='C';}
                if(i==10){tamanho=4;navio='P';}
                
                do{
                linha = rand() %15;
                coluna = rand() %15;
                }while((j1.Verifica(linha, coluna, tamanho, dir)) == 0);
                j1.Insere(linha, coluna, tamanho, dir, navio);

                do{
                linha = rand() %15;
                coluna = rand() %15;
                }while((j2.Verifica(linha, coluna, tamanho, dir)) == 0);
                j2.Insere(linha, coluna, tamanho, dir, navio);
            }
        }
//insere na vertical e/ou horizontal e/ou diagonal
        if (dificuldade == 3){

            for (int i =0; i<11; i++){

                dir = Sorteio();

                if(i<3){tamanho=2;navio='F';}
                if(i>2 && i<6){tamanho=2;navio='B';}
                if(i>5 && i<8){tamanho=3;navio='T';}
                if(i>7 && i<9){tamanho=3;navio='C';}
                if(i==10){tamanho=4;navio='P';}
                do{
                linha = rand() %15;
                coluna = rand() %15;
                }while((j1.Verifica(linha, coluna, tamanho, dir)) == 0);
                j1.Insere(linha, coluna, tamanho, dir, navio);

                do{
                linha = rand() %15;
                coluna = rand() %15;
                }while((j2.Verifica(linha, coluna, tamanho, dir)) == 0);
                j2.Insere(linha, coluna, tamanho, dir, navio);
            }
        } 
//guerra
        int t;       
        while( j1.Quantidade_tiros() <=50 ){
            system("clear");
            cout << "----------JOGADOR 1----------"<<endl;
            cout <<"\nDeseja continuar o jogo?[S/N]  ";
//leitura e verificacao de continuar
            do{
                if(flag){cout << "Entrada invalida. Deseja continuar o jogo?[S/N]  ";}
                getline(cin, continuar);
            //    cout << "\n"<< continuar;
                if(continuar[0] != 'N' || continuar[0] != 'S' || continuar[0] != 'n' || continuar[0] != 's'){flag = true;}
                if(continuar[0] == 'N' || continuar[0] == 'S' || continuar[0] == 'n' || continuar[0] == 's'){flag = false;}
            }while(flag);
            if(continuar[0] == 'N' || continuar[0] == 'n'){
                system("clear");
                cout << "\n\n----------Quem sabe na proxima jogador 1----------\n";
                cout << "----------PARABENS JOGADOR 2    VOCE VENCEU----------\n";
                break;
            }
//segue a guerra
            system("clear");
            j1.Printar_layout();
            cout <<"\nOnde voce quer atirar?  ";
            do{ 
                if(flag){cout << "Entrada invalida. Onde voce quer atirar?  ";}
                getline(cin,tiro);  
                aux_linha[0] = tiro[1];
                aux_linha[1] = tiro[2];
                linha = atoi(aux_linha);
                coluna = tiro[0];
                coluna-= 65;
                linha--;
                if(linha <0 || linha>14 || coluna <0 || coluna >14){flag=true;}
                if(linha >=0 && linha<=14 && coluna >=0 && coluna <=14){flag=false;}
                if(!flag && j1.Posicao(linha,coluna,1) != '~'){flag=true;}
            }while(flag);

            t = j2.Recebe(linha, coluna);
            j1.Atirou(linha,coluna,t);
            j2.Naufrago();
            if (j2.Confere() == 1){
                system("clear");
                cout << "\n\n\n\n----------Quem sabe na proxima jogador 2----------\n\n";
                cout << "----------PARABENS JOGADOR 1    VOCE VENCEU----------\n";   
            }
            system("clear");
            j1.Printar_layout();
            j2.Printar_naufragio();
            if(dificuldade == 1){
                cout << "        Deseja voltar jogada?[S/N]";
                do{
                if(flag){cout << "Entrada invalida. Deseja voltar jogada?[S/N]  ";}
                getline(cin, continuar);
                if(continuar[0] != 'N' || continuar[0] != 'S' || continuar[0] != 'n' || continuar[0] != 's'){flag = true;}
                if(continuar[0] == 'N' || continuar[0] == 'S' || continuar[0] == 'n' || continuar[0] == 's'){flag = false;}
                }while(flag);
                if(continuar[0] == 's' || continuar[0] == 'S'){
                    Voltar_Jogada(1,2);
                }
            }
            system("sleep 4");
            system("clear");
            cout << "----------JOGADOR 2----------"<<endl;
            cout <<"\nDeseja continuar o jogo?[S/N]  ";
//leitura e verificacao de continuar
            do{
                if(flag){cout << "Entrada invalida. Deseja continuar o jogo?[S/N]  ";}
                getline(cin, continuar);
            //    cout << "\n"<< continuar;
                if(continuar[0] != 'N' || continuar[0] != 'S' || continuar[0] != 'n' || continuar[0] != 's'){flag = true;}
                if(continuar[0] == 'N' || continuar[0] == 'S' || continuar[0] == 'n' || continuar[0] == 's'){flag = false;}
            }while(flag);
            if(continuar[0] == 'N' || continuar[0] == 'n'){
                system("clear");
                cout << "\n\n\n\n----------Quem sabe na proxima jogador 2----------\n\n";
                cout << "----------PARABENS JOGADOR 1    VOCE VENCEU----------\n";
                break;
            }
//segue a batalha
            system("clear");
            j2.Printar_layout();
            cout <<"\nOnde voce quer atirar?  ";
            do{ 
                if(flag){cout << "Entrada invalida. Onde voce quer atirar?  ";}
                getline(cin,tiro);  
                aux_linha[0] = tiro[1];
                aux_linha[1] = tiro[2];
                linha = atoi(aux_linha);
                coluna = tiro[0];
                coluna-= 65;
                linha--;
                if(linha <0 || linha>14 || coluna <0 || coluna >14){flag=true;}
                if(linha >=0 && linha<=14 && coluna >=0 && coluna <=14){flag=false;}
                if(!flag && j2.Posicao(linha,coluna,1) != '~'){flag=true;}
            }while(flag);
            t = j1.Recebe(linha, coluna);
            j2.Atirou(linha,coluna,t);
            j1.Naufrago();
            if (j1.Confere() == 1){
                system("clear");
                cout << "\n\n\n\n----------Quem sabe na proxima jogador 1----------\n\n";
                cout << "----------PARABENS JOGADOR 2 VOCE VENCEU----------\n\n\n\n";   
            }
            system("clear");
            j2.Printar_layout();
            j1.Printar_naufragio();
            if(dificuldade == 1){
                cout << "        Deseja voltar jogada?[S/N]";
                do{
                if(flag){cout << "Entrada invalida. Deseja voltar jogada?[S/N]  ";}
                getline(cin, continuar);
                if(continuar[0] != 'N' || continuar[0] != 'S' || continuar[0] != 'n' || continuar[0] != 's'){flag = true;}
                if(continuar[0] == 'N' || continuar[0] == 'S' || continuar[0] == 'n' || continuar[0] == 's'){flag = false;}
                }while(flag);
                if(continuar[0] == 's' || continuar[0] == 'S'){
                    Voltar_Jogada(2,2);
                }
            }
            system("sleep 4");

        }
    }

    void Jogo::Voltar_Jogada(int j, int modo){

        Pilha< int > p1l(50);
        Pilha< int > p1c(50);
        Pilha< char > p1t(50);
        Pilha< int > p2l(50);
        Pilha< int > p2c(50);
        Pilha< char > p2t(50);

        int linha, coluna;
        char n;

        if (modo == 1){
            linha = p1l.Desempilhar();
            coluna = p1c.Desempilhar();
            n = p1t.Desempilhar();
            j1.Troca(linha, coluna, '~',1);
            j2.Troca(linha,coluna, n,0);
            if(!p2l.Pilha_vazia()){
                linha = p2l.Desempilhar();
                coluna = p2c.Desempilhar();
                n = p2t.Desempilhar();
                j2.Troca(linha, coluna, '~',1);
                j1.Troca(linha,coluna, n,0);
            }
        }
        if(modo == 2){
            if(j==1){
                linha = p1l.Desempilhar();
                coluna = p1c.Desempilhar();
                n = p1t.Desempilhar();
                j1.Troca(linha, coluna, '~',1);
                j2.Troca(linha,coluna, n,0);
                if(!p2l.Pilha_vazia()){
                    linha = p2l.Desempilhar();
                    coluna = p2c.Desempilhar();
                    n = p2t.Desempilhar();
                    j2.Troca(linha, coluna, '~',1);
                    j1.Troca(linha,coluna, n,0);
                }
            }
            if(j==2){
                linha = p2l.Desempilhar();
                coluna = p2c.Desempilhar();
                n = p2t.Desempilhar();
                j2.Troca(linha, coluna, '~',1);
                j1.Troca(linha,coluna, n,0);
                if(!p1l.Pilha_vazia()){                
                    linha = p1l.Desempilhar();
                    coluna = p1c.Desempilhar();
                    n = p1t.Desempilhar();
                    j1.Troca(linha, coluna, '~',1);
                    j2.Troca(linha,coluna, n,0);
                }
            }
        }
    }
    Jogo::~Jogo(){}













    //!!FUNÇÕES BATALHA!!
    Batalha_atual::Batalha_atual(int dif, int op):Jogo(dif,op){}

    void Batalha_atual::Start(){
        if (option == 1){Modo_1();}
        if (option == 2){Modo_2();}
    }