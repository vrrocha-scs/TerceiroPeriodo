#include <iostream>
#include <cstdlib>
using namespace std;
    
    typedef struct {
		int chave;
	} Item;


#define Troca(A, B) { \
  Item c = A; \
  A = B; \
  B = c; \
}

void Bolha (Item *v, int n, int *comparacoes, int *trocas) 
{
	int i, j;
  for(i = 0; i < n-1; i++){
    for(j = 1; j < n-i; j++){
      (*comparacoes)++;
      if (v[j].chave < v[j-1].chave) {
        (*trocas)++;
        Troca(v[j-1], v[j]);
      }
    }
  }
}

void Selecao (Item *v, int n,int *comparacoes, int *trocas){ 
  int i, j, Min;
  for (i = 0; i < n - 1; i++){ 
    Min = i;
    for (j = i + 1 ; j < n; j++){
      (*comparacoes)++;
      if (v[j].chave < v[Min].chave){ 
        (*trocas)++;
        Min = j;
      }
    }
    Troca(v[i], v[Min]);
  }
}

void Insercao(Item *v, int n, int *comparacoes, int *trocas) {
    int i, j;
    Item aux;
    *comparacoes = 0;
    *trocas = 0;
    for (i = 1; i < n; i++) {
        aux = v[i];
        j = i - 1;
        // Conta a primeira comparação do while
        while (j >= 0 && (++(*comparacoes), aux.chave < v[j].chave)) {
            v[j + 1] = v[j];
            j--;
            (*trocas)++; // Conta deslocamento
        }
        v[j + 1] = aux;
        (*trocas)++; // Conta a "troca" final (inserção do aux)
    }
}

void shellSort(Item *v, int n, int *comparacoes, int *trocas) {
  for (int h = n / 2; h > 0; h /= 2) {
    for (int i = h; i < n; i += 1) {
      Item temp = v[i];
      int j;
      for (j = i; j >= h && (++(*comparacoes),v[j-h].chave > temp.chave); j-= h) {
        v[j] = v[j - h];
        (*trocas)++;
      }
      v[j] = temp;
      (*trocas)++;
    }
  }
}



void merge(Item *left, int nl, Item *right, int nr, Item *result, int *comparacoes, int *trocas) {
    int i = 0, j = 0, k = 0;
    while (i < nl && j < nr) {
        (*comparacoes)++;
        if (left[i].chave < right[j].chave) {
            result[k++] = left[i++];
            (*trocas)++;
        } else {
            result[k++] = right[j++];
            (*trocas)++;
        }
    }
    while (i < nl) {
        result[k++] = left[i++];
        (*trocas)++;
    }
    while (j < nr) {
        result[k++] = right[j++];
        (*trocas)++;
    }
}

void mergeSort(Item *v, int n, int *comparacoes, int *trocas) {
    if (n <= 1) return;

    int nl = n / 2;
    int nr = n - nl;

    // Aloca vetores auxiliares
    Item *left = (Item*) malloc(nl * sizeof(Item));
    Item *right = (Item*) malloc(nr * sizeof(Item));

    // Copia os elementos para os vetores auxiliares
    for (int i = 0; i < nl; i++) left[i] = v[i];
    for (int i = 0; i < nr; i++) right[i] = v[nl + i];

    int compL = 0, compR = 0, trocaL = 0, trocaR = 0;

    // Ordena recursivamente as duas metades
    mergeSort(left, nl, &compL, &trocaL);
    mergeSort(right, nr, &compR, &trocaR);

    // Mescla as duas metades ordenadas
    merge(left, nl, right, nr, v, comparacoes, trocas);

    // Soma as comparações e trocas das recursões
    *comparacoes += compL + compR;
    *trocas += trocaL + trocaR;

    free(left);
    free(right);
}




void preenche_vetor(int tamanho,Item *v){
  for(int i=0;i<tamanho;i++){
     v[i].chave = tamanho-i-1;
  }
}

void imprime(Item *v,int tamanho,int iteracoes){
  for(int i=0;i<tamanho;i++){
    cout<<v[i].chave<<" ";
  }
  cout<<endl<<"numero trocas: "<<iteracoes<<endl;
}


void quickSortRec(Item *v, int Esq, int Dir, int *comparacoes, int *trocas) {
    int i = Esq, j = Dir;
    Item x = v[(Esq + Dir) / 2];
    do {
        while ((++(*comparacoes)), v[i].chave < x.chave) i++;
        while ((++(*comparacoes)), v[j].chave > x.chave) j--;
        if (i <= j) {
            Troca(v[i], v[j]);
            (*trocas)++;
            i++; j--;
        }
    } while (i <= j);
    if (Esq < j) quickSortRec(v, Esq, j, comparacoes, trocas);
    if (i < Dir) quickSortRec(v, i, Dir, comparacoes, trocas);
}

void quickSort(Item *v, int n, int *comparacoes, int *trocas) {
    *comparacoes = 0;
    *trocas = 0;
    if (n > 1)
        quickSortRec(v, 0, n - 1, comparacoes, trocas);
}

int main(){
    char tipo;
    int tamanho=0,trocas=0,comparacoes=0;
    Item *v;
    cout<<"qual o tipo de operação?"<<endl;
    cin>>tipo;
    cout<<"Qual o tamanho do vetor?"<<endl;
    cin>>tamanho;
    v= (Item*) malloc(tamanho*sizeof(Item));
    preenche_vetor(tamanho,v);
    imprime(v,tamanho,trocas);
    if(tipo =='b'){
     Bolha(v,tamanho,&comparacoes,&trocas);
    }
    else if(tipo=='s'){
      Selecao ( v, tamanho, &comparacoes,&trocas);
    }
    else if(tipo=='i'){
      Insercao( v, tamanho, &comparacoes,&trocas);
    }
    else if(tipo=='h'){
      shellSort(v, tamanho, &comparacoes,&trocas);
    }
    else if(tipo=='m'){
      mergeSort(v, tamanho, &comparacoes,&trocas);
    }
    else if(tipo=='q'){
      quickSort(v, tamanho, &comparacoes,&trocas);
    }

  imprime(v,tamanho,trocas);
  cout<<"numero de comparacoes: "<<(comparacoes)<<endl;
  free(v);
}
