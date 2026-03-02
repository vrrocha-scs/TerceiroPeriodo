#include <string>
#include <iostream>
#include <sstream>
#include <cctype>
#include "minheap.hpp"
#include "hash.hpp"
#include "endereco.hpp"
#include "logradouro.hpp"
#include "palavra.hpp"

using namespace std;

int main(){
    int numEndereco=0, numeroLogradores=0;
    cin>>numEndereco;
    cin.ignore();
    Endereco* enderecos = new Endereco[numEndereco];
    Logradouro* logradouros = new Logradouro[numEndereco];
    IndicePalavras* indicePalavras = new IndicePalavras();
    TabelaHash tabelaAuxiliar(20011);

    for(int i = 0; i<numEndereco; i++){//inicializacao dos logradouros e enderecos 
        string linhaDados, campo;
        getline(cin, linhaDados);
        stringstream ss(linhaDados);

        long long auxIdEnd;
        int auxIdLog, auxNum, auxCep;
        double auxLatitude, auxLongitude;
        string auxBairro,auxTipoLog, auxNome, auxRegiao;

        getline(ss, campo, ';'); auxIdEnd = stoll(campo);
        getline(ss, campo, ';'); auxIdLog = stoi(campo);
        getline(ss, auxTipoLog, ';');
        getline(ss,auxNome,';'); 
        getline(ss, campo, ';'); auxNum = stoi(campo);
        getline(ss, auxBairro, ';');
        getline(ss, auxRegiao, ';');
        getline(ss, campo, ';'); auxCep = stoi(campo); 
        getline(ss, campo, ';'); auxLatitude = stod(campo);
        getline(ss, campo, ';'); auxLongitude = stod(campo); 

        enderecos[i] = Endereco(auxIdEnd,auxIdLog,auxNum,auxCep,auxLatitude,auxLongitude,auxTipoLog,auxNome,auxBairro,auxRegiao);
        int indiceEncontrado = tabelaAuxiliar.buscar(auxIdLog);//verifica se o logradouro ja foi cadastrado

        if(indiceEncontrado != -1){//caso em que logradouro já existe
            logradouros[indiceEncontrado].AdicionaEndereco(auxLatitude,auxLongitude);
        } else{//caso em que o logradouro é novo
            logradouros[numeroLogradores] = Logradouro(auxIdLog, auxNome, auxTipoLog);
            logradouros[numeroLogradores].AdicionaEndereco(auxLatitude, auxLongitude);

            stringstream st(auxNome);
            while(getline(st,campo,' ')){//insere as palavras na arvore
                if(campo != ""){//verifica se a string nao é vazia, pode causar problemas de comparacao
                    indicePalavras->inserir(campo,&logradouros[numeroLogradores]);
                }
            }
            tabelaAuxiliar.inserir(auxIdLog,numeroLogradores);
            numeroLogradores++;
           }
    }

    int numeroConsultas=0, qtdSaidas=0;;
  
    cin>>numeroConsultas>>qtdSaidas;
    cin.ignore();

    cout<<numeroConsultas<<endl;
    
    for(int i=0;i<numeroConsultas;i++){//Segunda parte: consulta das ruas
        string linhaDados, campo;
        int idConsulta=0;
        double latOrigem, longOrigem;
        string consulta;

        NoLista** palavrasConsulta = new NoLista*[numeroLogradores];
        int numPalavrasConsulta=0;
        bool palavraInexistente = 0;

        getline(cin, linhaDados);
        stringstream ss(linhaDados);

        getline(ss, campo, ';'); idConsulta = stoi(campo);
        getline(ss, consulta, ';');
        getline(ss, campo, ';'); latOrigem = stod(campo);
        getline(ss, campo, ';'); longOrigem = stod(campo);
        
        stringstream st(consulta);
        while(getline(st,campo,' ')){//separação das palavras a serem consultadas
            if(campo!=""){
                palavrasConsulta[numPalavrasConsulta]=indicePalavras->buscar(campo);//busca a lista de logradouros que possuem esta palavra
                if(palavrasConsulta[numPalavrasConsulta] != nullptr){
                    numPalavrasConsulta++;
                }else{
                    palavraInexistente=true;
                }
            }
        }

        if(palavraInexistente || numPalavrasConsulta == 0){
            cout << idConsulta << ";0" << endl;
            delete[] palavrasConsulta; 
            continue; 
        }

        Logradouro** logradourosTocados = new Logradouro*[numeroLogradores]; //marca os logradouros "tocados" pelas palavras
        int qtdTocados = 0;

        for(int k=0; k < numPalavrasConsulta; k++){//varre as listas retornadas pela arvore
            NoLista* Atual = palavrasConsulta[k];
            
            while(Atual != nullptr){
                Logradouro* log = Atual->logradouro;
                if(log->contadorIntersecao == k){
                    if(log->contadorIntersecao == 0){//primeira vez que o logradouro é visto na consulta
                        logradourosTocados[qtdTocados] = log;
                        qtdTocados++;
                    }
                    log->contadorIntersecao++;//incrementa para contar quantas palavras na consulta aparecem neste logradouros
                }
                Atual = Atual->proximo;
            }
        }

        Logradouro** candidatos = new Logradouro*[qtdTocados]; //Candidatos confirmados (possuem todas as palavras)
        int qtdCandidatos = 0;

        for(int k=0; k < qtdTocados; k++) {
            Logradouro* log = logradourosTocados[k];

            if(log->contadorIntersecao == numPalavrasConsulta){//se o logradouro apareceu em todas as palavras buscadas
                // Calcula Distância Euclidiana
                double dLat = log->latMedia - latOrigem;
                double dLon = log->longMedia - longOrigem;
                log->distanciaCache = (dLat*dLat) + (dLon*dLon);
                candidatos[qtdCandidatos] = log;
                qtdCandidatos++;
            }
            log->contadorIntersecao = 0; 
        }
        int limite = qtdSaidas;//define o limite de impressão
        if(qtdCandidatos<qtdSaidas)
            limite = qtdCandidatos;

        MinHeap heap(candidatos,qtdCandidatos);
        cout << idConsulta << ";" << limite << endl;

        for(int k=0; k < limite; k++) {
            Logradouro* proximo = heap.extrair_minimo();
            cout << proximo->idLog << ";" << proximo->nome << endl;
        }
        delete[] logradourosTocados;
        delete[] candidatos;
        delete[] palavrasConsulta;
    }

    delete indicePalavras;
    delete[] enderecos;
    delete[] logradouros;
}