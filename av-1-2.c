#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

typedef struct no_AVL { 
/* Estrutura do nodo da �rvore, � poss�vel armazenar diferentes tipos de dado em cada nodo.
Neste caso � feita uma �rvore gen�rica, sem nenhuma informa��o relevante.*/        
        int info; // chave, � utilizada para todas opera��es elementares
        int fb; // Fator de balanceamento da �rvore, 
        //� guardado na estrutura para evitar que o mesmo seja calculado durante o programa.
        //convencao: altura esquerda � negativa.
        struct no_AVL *pai; // ponteiro para o pai do nodo, quando nodo � ra�z ponteiro � nulo. 
        struct no_AVL *esq; // ponteiro para o filho esquerdo do nodo caso houver
        struct no_AVL *dir; // ponteiro para o filho direito do nodo caso houver
} AVL; 
AVL *aloca_no(int chave) { 
/*Aloca memoria para cada nodo novo. Fun��o utilizada para inser��o de um nodo na �rvore*/    
    AVL *temp; 
    temp = (AVL *) malloc(sizeof(AVL)); 
    if (temp) { 
       temp->info = chave; 
       temp->pai = NULL; 
       temp->esq = NULL; 
       temp->dir = NULL; 
       temp->fb = 0; 
       return temp; 
       }   
} 
AVL *rotacao_esquerda(AVL *no) {
/*Rota��o esquerda em um n�. Utilizada para manter a �rvore balanceada durante 
a inser��o ou remo��o de um nodo.*/
 AVL *temp; 
 temp = no->dir; 
 no->dir = temp->esq; 
 if (temp->esq != NULL) {
  (temp->esq)->pai = no; }
 temp->esq = no; 
 temp->pai = no->pai; 
 if (no->pai != NULL) // nao � raiz
 {
   if ((no->pai)->dir==no){
      (no->pai)->dir = temp; 
   }else{
      (no->pai)->esq = temp; 
      }
 }
 no->pai = temp; 
 no->fb = 0; 
return temp; 
} 

AVL *rotacao_direita(AVL *no) {
/*Rota��o direita em um n�. Utilizada para manter a �rvore balanceada durante 
a inser��o ou remo��o de um nodo.*/ 
     AVL *temp; 
    temp = no->esq; 
    no->esq = temp->dir; 
    if (temp->dir != NULL) 
       temp->dir->pai = no; 
    temp->dir = no; 
    temp->pai = no->pai; 
    if (no->pai != NULL)
    {
      if ((no->pai)->dir==no)
         (no->pai)->dir = temp; 
      else
          (no->pai)->esq = temp; 
    }
    no->pai = temp; 
    no->fb = 0; 
    return temp; 
} 

AVL *rotacao_dupla_direita(AVL *no) {
/*Uma rota��o Dupla para direita � uma reta��o para esquerda no filho da esquerda
seguida de uma rota��o para direita no nodo passado como par�metro*/     
    no->esq = rotacao_esquerda(no->esq); 
    no = rotacao_direita(no); 
    return no; 
} 

AVL *rotacao_dupla_esquerda(AVL *no) { 
/*Uma rota��o Dupla para esquerda � uma rota��o para direita no filho da direita
seguida de uma rota��o para esquerda no nodo passado como par�metro*/   
     no->dir = rotacao_direita(no->dir); 
     no = rotacao_esquerda(no); 
return no; 
} 
typedef struct dadosABB{
        int vlr;
        struct dadosABB *esq,
                        *dir;
}sABB;

sABB *inicializa(sABB *L){
     L = NULL;
     return L;
}     

int estaVazia(sABB *L){
     return (L == NULL?1:0);
}


void mostra_em_ordem(sABB *L){
     if (L != NULL){
           mostra_em_ordem(L->esq);
           printf("%d   ",L->vlr);
           mostra_em_ordem(L->dir);
     }
}

void mostra_pos_ordem(sABB *L){
     if (L != NULL){
           mostra_pos_ordem(L->esq);
           mostra_pos_ordem(L->dir);
           printf("%d   ",L->vlr);
     }
}

void mostra_pre_ordem(sABB *L){
     if (L != NULL){
           printf("%d   ",L->vlr);
           mostra_pre_ordem(L->esq);
           mostra_pre_ordem(L->dir);
     }
}

//pesquisa

sABB* pesq(sABB *R, int dadoPesq){
    while (R != NULL && R->vlr != dadoPesq)
       if (dadoPesq < R->vlr)
          R = R->esq;
       else
          R = R->dir;
    return R;
}

char resposta(char *perg){
     char resp;
     printf("\n\n%s : ",perg);
     do{
        resp = toupper(getch());
     }while (resp != 'S' && resp != 'N');
     return resp;
}

sABB *insere (sABB *R, int numero){
      if (R == NULL){
         R = (sABB*) malloc (sizeof(sABB));
         if (R == NULL)
            printf("\n\nDados nao foi inserido com sucesso!\n\n");
         else{
            R->vlr = numero;
            R->esq = NULL;
            R->dir = NULL;
            printf("\n\nDados inserido com sucesso!\n\n");
         }
      }
      else
         if (numero < R->vlr)
            R->esq = insere (R->esq,numero);
         else
            R->dir = insere (R->dir,numero);  
      return R;
}

sABB *inclusao(sABB *L){
     char op;  
     int num;
     do{
        system("cls");
        printf("******* INSERIR DADO *******\n");
        printf("Digite um numero a ser inserido : ");
        scanf("%d",&num);
        L = insere(L,num);
        op = resposta("Deseja realizar nova insercao?(S/N)");
        //fim da inser��o     
     }while(op == 'S');
     return L;
}


void listar(sABB *L){
     system("cls");
     printf("******* LISTAR DADOS *******\n");
     if (estaVazia(L))
        printf("\nLista Vazia!\n\n");
     else{
        //in�cio da listagem  
        printf("\n\nEM-ORDEM = ");
        mostra_em_ordem(L);

        printf("\n\nPOS-ORDEM = ");
        mostra_pos_ordem(L);

        printf("\n\nPRE-ORDEM = ");
        mostra_pre_ordem(L);
        //fim da listagem
     }
     printf("\n\n");
     system("pause");
}


void pesquisar(sABB *L){
     int dadoPesq;
     sABB *aux;
     if (estaVazia(L)){
          system("cls");
          printf("******* PESQUISAR DADO *******\n\nLista Vazia!\n\n");    
          system("pause");
     }else
          do{
              system("cls");            
              printf("******* PESQUISAR DADO *******\n\n");
              printf("Digite o numero a ser pesquisado : ");
              scanf("%d",&dadoPesq);
              aux = pesq(L,dadoPesq);
              if (aux == NULL)
                  printf("\n\nDado inexiste na lista!\n\n");
              else
                  printf("\n\n%d existe na lista.\n\n",dadoPesq);
          }while (resposta("\nDeseja realizar nova pesquisa?(S/N)") == 'S');
}

sABB *minimo(sABB *A){// procura o n� com valor m�nimo   
	if(estaVazia(A))   
       return NULL;   
    else   
          if( estaVazia(A->esq) )  {
          	 system("cls");
          printf("******* MINIMO *******\n");
										printf("O menor numero:%d\n",A->vlr); 
										printf("\naperte enter......\n");
										getchar(); 
										 return A;   
										} 
             
          else  
              return minimo(A->esq);   
} 


sABB *maximo(sABB *A){// procura o n� com valor m�ximo   
     if(estaVazia(A) ){
          return NULL;   
     }else{
          if( estaVazia(A->dir) ) {
          system("cls");
          printf("******* MAXIMO *******\n");
										printf("O maior numero:%d\n",A->vlr); 
										printf("\naperte enter......\n");
										getchar(); 
              return A; 
													}
          else  
              return maximo(A->dir);   
				}
}  

sABB *remover(sABB *raiz, int valor){   
    sABB *aux;   
    if(!estaVazia(raiz))  
       if(valor < raiz->vlr)   
           raiz->esq = remover(raiz->esq, valor);  
       else 
            if(valor > raiz->vlr)   
                 raiz->dir = remover(raiz->dir, valor);    
            else{
                if(!estaVazia(raiz->esq) && !estaVazia(raiz->dir) ){    
                     aux = maximo(raiz->esq);    //ou aux = minimo(raiz->dir);
                     raiz->vlr = aux->vlr;   
                     raiz->esq = remover(raiz->esq, raiz->vlr);   //se trocar a observa��o acima, deve-se trocar esta por raiz->dir = remover(raiz->dir, raiz->vlr);   
                }
                else{    
                       aux = raiz;    
                       if(estaVazia(raiz->esq))    
                           raiz = raiz->dir;   
                       else   
                           raiz = raiz->esq;
					   free(aux);                          
                }   

            }
    return raiz;
}


sABB* excluir(sABB *L){
     int dadoExc;
     sABB *aux;
     if (estaVazia(L)){
         system("cls");
         printf("******* EXCLUIR DADO *******\n");
         printf("\n\nLista VAZIA!\n\n");
         system("pause");
     }else{
         do{
            system("cls");
            printf("******* EXCLUIR DADO *******\n");
            printf("\nListagem Em-Ordem = ");
            mostra_em_ordem(L);
            printf("\nDigite o dado a ser excluido : ");
            scanf("%d",&dadoExc);

            aux = pesq(L,dadoExc);

            if (aux == NULL)
                printf("\n\nDado inexiste na lista!\n\n");
            else{
                printf("\n\n%d existe na lista.\n\n",dadoExc);
                if (resposta("Deseja realmente exclui-lo? (S/N)") == 'S'){
                   //in�cio da exclus�o                  
                   remover(L, dadoExc);
                   //fim da exclus�o
                   printf("\n\nDado excluido com sucesso!\n\n");
                }else
                   printf("\n\nDado NAO foi excluido!\n\n");
            }
         }while(!estaVazia(L) && resposta("\nDeseja realizar nova exclusao?(S/N)") != 'N');
     }//termina o else
     return L;
}

void menu(sABB *L){
     char op;
     do{
         system("cls");
         printf("\n******* MENU ********\n");
         printf("\n[ I ] Inserir dado");
         printf("\n[ L ] Listas dados");
         printf("\n[ P ] Pesquisar/alterar dado");
         printf("\n[ E ] Excluir dado");
         printf("\n[ M ] Maximo");
         printf("\n[ N ] Menor");
         printf("\n[ S ] Sair do sistema");
         printf("\n\nOpcao : ");
         op = toupper(getch());
         switch (op){
                case 'I' : L = inclusao(L);getchar(); break;
                case 'L' : listar(L); break;
                case 'P' : pesquisar(L); break;
                case 'E' : L = excluir(L);break;
                case 'M' : maximo(L);break;
                case 'N' : minimo(L);break;
         }

     }while (op != 'S');
}


int main(){
    sABB *arvore;
    arvore = inicializa(arvore);
    menu(arvore);
}
