#include <iostream>
using namespace std;
class Node{
public:
	int value;
	Node* next;
};
void BubbleSort(Node* head) {
    int troca;
	Node *ptr1;
    Node *lptr=NULL;
    if (head==NULL){//verifica se a lista está vazia
		return;
	}
    do{
        troca=0;
        ptr1=head;
        while (ptr1->next != lptr) {
            if (ptr1->value > ptr1->next->value) {//verifica se o valor do primeiro é maior que o próximo, se sim trocam de posição
                int temp = ptr1->value;
                ptr1->value = ptr1->next->value;
                ptr1->next->value = temp;
                troca = 1;
            }
            ptr1 = ptr1->next;//vai para o próximo número
        }
        lptr = ptr1;
    } while (troca);
}
void InsertionSort(Node** head) {
    Node* ordena = NULL;//Inicia uma lista inicialmente vazia(ordenada) 
    Node* atual = *head;
    while (atual != NULL) {
        Node* next = atual->next;// Insere o nó atual na posição correta da lista ordenada
        if (ordena == NULL || ordena->value >= atual->value) {
            atual->next = ordena;
			ordena= atual;
        } else {
            Node* temp = ordena;
            while (temp->next!=NULL && temp->next->value < atual->value) {
                temp = temp->next;
            }
            atual->next = temp->next;
            temp->next = atual;
        }
        atual = next; // Move para o próximo nó da lista original 
    }
    *head = ordena;// Atualiza o ponteiro da lista original para a lista ordenada
}
void SplitList(Node* head, Node** primeira, Node** segunda) {//Função para dividir as listas
    Node* slow = head;
    Node* fast = head->next;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }//Código para encontrar o meio da lista mais rápido
    }
    *primeira = head;
    *segunda = slow->next;
    slow->next = NULL;
}
Node* MergeLists(Node* a, Node* b) {//Função para juntar duas listas ordenadas em uma
    if (a == NULL){
		return b;
	}
    if (b == NULL) {
		return a;
	}//verifica se alguma lista está vazia
    Node* result = NULL;
    if (a->value <= b->value) {
        result = a;
        result->next = MergeLists(a->next, b);
    } else {
        result = b;
        result->next = MergeLists(a, b->next);
    }//confere os valores dos nós e coloca na lista resultante
    return result;
}
void MergeSort(Node** headref) {//Função principal que integra as outras
    Node* head = *headref;
    if (head == NULL || head->next == NULL) {
        return;
    }
    Node* a;
    Node* b;
    SplitList(head, &a, &b);//divide a lista em duas metades
    MergeSort(&a);//ordena as metades
    MergeSort(&b);
    *headref = MergeLists(a, b);//junta ordenadas
}
Node* partition(Node* low, Node* high) {//Função para dividir em partes a lista
    int pivo = high->value;// Define o valor do pivô como o valor do último nó da lista ou sublista
    Node* i = low;//inicia os ponteiros de comparação no inicio da lista
    Node* j = low;
    for (Node* atual = low; atual != high; atual = atual->next) {//faz um loop de low ate high tirando o pivô
        if (atual->value < pivo) {//verifica se o valor atual é menor que o pivô e realiza a troca
            int temp = i->value;
            i->value = atual->value;
            atual->value = temp;
            j = i;
            i = i->next;
        }
    }
    int temp = i->value;
    i->value = high->value;
    high->value = temp;//coloca o pivo na posição correta
    return j;
}
void quickSort(Node* low, Node* high) {
    if (high != NULL && low != high && low != high->next) {
        Node* pi = partition(low, high);//obtem a posição do pivo
        quickSort(low, pi);
        quickSort(pi->next, high);//aplica quicksort antes e depois do pivo
    }
}
Node* getLast(Node* n) {
    while (n->next != NULL) {
        n = n->next;
    }
    return n;
}
void printList(Node* n){
	while(n!=NULL){
        cout<<n->value<<endl;
        n=n->next;
    }
}
int main(){
	Node* head=new Node();
	Node* second=new Node();
	Node* third=new Node();
	Node* four=new Node();
	Node* fifth=new Node();
	head->value=5;
	head->next=second;
	second->value=3;
	second->next=third;
	third->value=8;
	third->next=four;
	four->value=4;
	four->next=fifth;
	fifth->value=6;
	fifth->next=NULL;
	Node* last = getLast(head);
    quickSort(head, last);
	printList(head);
    return 0;
}