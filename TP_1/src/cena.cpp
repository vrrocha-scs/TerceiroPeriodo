#include "cena.hpp"
#include "objeto.hpp"
#include "minheap.hpp" 
#include "insertion.hpp" 
#include <iostream>

#define MaxTam 1000 

Cena::Cena():id(0),comeco(0.0),fim(0.0){};

int processa_cena(Cena saida[], Objeto objeto[], int tamanho) {
    MinHeap heap(objeto, tamanho); //Constrói inicio_segmento_atual Fila de Prioridade com todos os objetos

    Cena saida_visiveis[MaxTam]; //armazena os segmentos finais visíveis
    int visiveis_count = 0;

    while (!heap.esta_vazia()) { //Processa os objetos, do mais próximo (menor eixo_y) para o mais distante
        Objeto ocluido = heap.extrair_minimo(); 

       // Os segmentos do objeto atual que ainda estão visíveis
        double visiveis_inicio[MaxTam], visiveis_fim[MaxTam];
        int current_visiveis_count = 1;
        visiveis_inicio[0] = ocluido.inicio;
        visiveis_fim[0] = ocluido.final;

        for (int k = 0; k < visiveis_count; k++) { // Itera sobre os segmentos já determinados como visíveis e mais proximos
            double inicio_oclusor = saida_visiveis[k].comeco;// Segmento oclusor (já visível e mais próximo)
            double fim_oclusor = saida_visiveis[k].fim;
            
            int novos_count = 0;
            double novos_inicio[MaxTam], novos_fim[MaxTam];
            
            // Para cada parte visível do objeto atual, verifica oclusão contra o segmento na posição 'k'
            for (int v = 0; v < current_visiveis_count; v++) {
                double inicio_segmento_atual = visiveis_inicio[v]; // Início da parte visível
                double fim_segmento_atual = visiveis_fim[v];   // Fim da parte visível
                
                // Se não há sobreposição, inicio_segmento_atual parte visível é mantida
                if (fim_segmento_atual <= inicio_oclusor || inicio_segmento_atual >= fim_oclusor) {
                    if(novos_count<MaxTam){
                        novos_inicio[novos_count] = inicio_segmento_atual;
                        novos_fim[novos_count] = fim_segmento_atual;
                        novos_count++;
                    }
                    else
                        std::cerr<<"Limite Maximo Atingido"<<std::endl;

                } else {
                    // Há sobreposição, verifica as partes que sobram.
                    if (inicio_segmento_atual < inicio_oclusor) { // Parte antes do oclusor
                        if(novos_count<MaxTam){
                            novos_inicio[novos_count] = inicio_segmento_atual;
                            novos_fim[novos_count] = inicio_oclusor;
                            novos_count++;
                        }
                        else
                            std::cerr<<"Limite Maximo Atingido"<<std::endl;
                    }
                    if (fim_segmento_atual > fim_oclusor) { // Parte depois do oclusor
                        if(novos_count<MaxTam){
                            novos_inicio[novos_count] = fim_oclusor;
                            novos_fim[novos_count] = fim_segmento_atual;
                            novos_count++;
                        }
                        else
                            std::cerr<<"Limite Maximo Atingido"<<std::endl;
                    }
                }
            }
            
            // Atualiza os intervalos visíveis do objeto atual para inicio_segmento_atual próxima iteração
            current_visiveis_count = novos_count;
            for (int v = 0; v < novos_count; v++) {
                visiveis_inicio[v] = novos_inicio[v];
                visiveis_fim[v] = novos_fim[v];
            }
            
            // Se o objeto atual foi completamente ocluído, não precisa checar o resto
            if (current_visiveis_count == 0) break;
        }

        // Adiciona as partes que sobraram (visíveis) à lista final de segmentos
        for (int v = 0; v < current_visiveis_count; v++) {
            if (visiveis_inicio[v] < visiveis_fim[v]) { // Garante que é um segmento válido
                if(visiveis_count<MaxTam){
                    saida_visiveis[visiveis_count].id = ocluido.identificador;
                    saida_visiveis[visiveis_count].comeco = visiveis_inicio[v];
                    saida_visiveis[visiveis_count].fim = visiveis_fim[v];
                    visiveis_count++;
                }
                else
                    std::cerr<<"Limite Maximo Atingido"<<std::endl;

            }
        }
    }

    // Copia os segmentos finais de volta para o array de saída
    for (int i = 0; i < visiveis_count; i++) {
        saida[i] = saida_visiveis[i];
    }
    
    // Ordena os segmentos visíveis finais por id para uma saída ordenada
    Insertion_id(saida, visiveis_count);

    return visiveis_count;
}