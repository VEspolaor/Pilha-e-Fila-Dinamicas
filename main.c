#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <locale.h>

//Autor: Vitor Augusto Espolaor
//R.A:22029168-5
//Atividade: MAPA - ESOFT - ESTRUTURA DE DADOS I 

struct no_fila {
  char nucleotideo;
  struct no_fila *proximo;
};

struct fila {
  struct no_fila *inicio;
  struct no_fila *fim;
};

int validarCaractere(char c) {
  return (c == 'T' || c == 'A' || c == 'C' || c == 'G');
} 

void inserirFila(struct fila *fila, char nucleotideo) {
  struct no_fila *novoNo = (struct no_fila *)malloc(sizeof(struct no_fila));
  novoNo->nucleotideo = nucleotideo;
  novoNo->proximo = NULL;

  if (fila->inicio == NULL) {
    fila->inicio = novoNo;
    fila->fim = novoNo;
  } else {
    fila->fim->proximo = novoNo;
    fila->fim = novoNo;
  }
}

void excluirFila(struct fila *fila) {
  if (fila->inicio == NULL) {
    printf("Fila vazia.\n");
  } else {
    struct no_fila *temp = fila->inicio;
    fila->inicio = fila->inicio->proximo;
    free(temp);
  }
}

void imprimirFila(struct fila *fila) {
  struct no_fila *temp = fila->inicio;
  while (temp != NULL) {
    printf("%c", temp->nucleotideo);
    temp = temp->proximo;
  }
  printf("\n");
}

struct no_pilha {
  char nucleotideo;
  struct no_pilha *proximo;
};

struct pilha {
  struct no_pilha *topo;
};

void inserirPilha(struct pilha *pilha, char nucleotideo) {
  struct no_pilha *novoNo = (struct no_pilha *)malloc(sizeof(struct no_pilha));
  novoNo->nucleotideo = nucleotideo;
  novoNo->proximo = pilha->topo;
  pilha->topo = novoNo;
}

void imprimirPilha(struct pilha *pilha) {
  struct no_pilha *temp = pilha->topo;
  while (temp != NULL) {
    printf("%c", temp->nucleotideo);
    temp = temp->proximo;
  }
  printf("\n");
}

int main() {
  setlocale(LC_ALL, "Portuguese");
  struct fila fila;
  fila.inicio = NULL;
  fila.fim = NULL;

  struct pilha pilha;
  pilha.topo = NULL;
  
  char sequencia[100];
  int escolha;
  
  do {
    printf("\n");
    printf("-_-_-_-_-_Menu de Opções-_-_-_-_-_-\n");
    printf("1-Inserira uma sequência de Nucleotídeos\n");
    printf("2-Excluir um caractere da lista\n");
    printf("3-Inserir um elemento na Pilha\n");
    printf("4-Imprimir a fila e a pilha\n");
    printf("5-Encerrar\n");
    printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n");
    scanf("%d", &escolha);
    fflush(stdin);
    
    switch (escolha) {
      case 1:
		system("cls");
        printf("Digite a sequência de nucleotídeos: ");
        scanf("%s", sequencia);
        int tamanho = strlen(sequencia);
  		int caracteresInvalidos = 0;  

  		for (int i = 0; i < tamanho; i++) {
    		char nucleotideo = sequencia[i];

    	if (validarCaractere(nucleotideo)) {
      		inserirFila(&fila, nucleotideo);
    	}else {
      		caracteresInvalidos++;
    	}
  		}

  		if (caracteresInvalidos > 0) {
    		printf("Foram encontrados %d caracteres inválidos. O programa será encerrado.\n", caracteresInvalidos);
    		return 0;
  		}
		
        struct fila filaCopia; 
        filaCopia.inicio = NULL;
        filaCopia.fim = NULL;

        struct no_fila *temp = fila.inicio;

        while (temp != NULL) {
          inserirFila(&filaCopia, temp->nucleotideo);
          temp = temp->proximo;
        }

        while (fila.inicio != NULL) {
          char nucleotideo = fila.inicio->nucleotideo;
          excluirFila(&fila);

          switch (nucleotideo) {
            case 'A':
              inserirPilha(&pilha, 'T');
              break;
            case 'T':
              inserirPilha(&pilha, 'A');
              break;
            case 'C':
              inserirPilha(&pilha, 'G');
              break;
            case 'G':
              inserirPilha(&pilha, 'C');
              break;
            default:
              break;
          }
        }
		
		printf("Inserido com sucesso \n");
        
        break;
      
      case 2:
        {
        	system("cls");
          	char caractere;
          	printf("Insira o caractere para excluí-lo da fila: ");
          	scanf(" %c", &caractere);
          	
          	struct no_fila *tempFila = filaCopia.inicio;
          	struct no_fila *anteriorFila = NULL;
          	struct no_pilha *tempPilha = pilha.topo;
          	struct no_pilha *anteriorPilha = NULL;

          while (tempFila != NULL) {
            if (tempFila->nucleotideo == caractere) {
              if (anteriorFila == NULL) {
                filaCopia.inicio = tempFila->proximo;
              } else {
                anteriorFila->proximo = tempFila->proximo;
              }
              free(tempFila);
              break;
            }
            anteriorFila = tempFila;
            tempFila = tempFila->proximo;
          }

          while (tempPilha != NULL) {
            if ((caractere == 'A' && tempPilha->nucleotideo == 'T') ||
                (caractere == 'T' && tempPilha->nucleotideo == 'A') ||
                (caractere == 'C' && tempPilha->nucleotideo == 'G') ||
                (caractere == 'G' && tempPilha->nucleotideo == 'C')) {
              if (anteriorPilha == NULL) {
                pilha.topo = tempPilha->proximo;
              } else {
                anteriorPilha->proximo = tempPilha->proximo;
              }
              free(tempPilha);
              break;
            }
            anteriorPilha = tempPilha;
            tempPilha = tempPilha->proximo;
          }
        }
        break;
        
      	case 3:
      		{
			  system("cls");
			  char caractere;
			  printf("Insira um caractere para inserir na pilha: ");
			  scanf(" %c", &caractere);
			
			  if (validarCaractere(caractere)) {
			    inserirPilha(&pilha, caractere);
			    printf("Caractere foi inserido com sucesso na pilha.\n");
			  } else {
			    printf("Caractere que você digitou é inválido. O caractere deve ser T, A, G ou C.\n");
			  }
			}
			break;
		case 4:
			system("cls");
        	printf("Fila atual: ");
        	imprimirFila(&filaCopia);

        	printf("\nPilha atual: ");
        	imprimirPilha(&pilha);
        	break;
			
    	case 5:
    		printf("\nEncerrando...");
        	return 0;
        	break;

      	default:
        	printf("Escolha inválida, escolha de 1 a 5.\n");
        	break;
    }
  } while (escolha != 0);
  
  return 0;
}
