// Programa en C para el algoritmo de Huffman


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
 
// Esta variable se puede evitar calculando la altura del �rbol de Huffman
#define MAX_TREE_HT 100
 
// MinHeapNode: Nodo del �rbol de Huffman
struct MinHeapNode
{
    char data;  // Caracter de entrada
    unsigned freq;  // Frecuencia del caracter
    struct MinHeapNode *left, *right; // Izquierda o derecha del nodo Ni�o
};
 
// MinHeap: Colecci�n de nodos o �rbol
struct MinHeap
{
    unsigned size;    // Tama�o actual
    unsigned capacity;   // Capacidad
    struct MinHeapNode **array;  // Matriz de punteros a los nodos
};
 
// Utilizamos la funcion para asignar un nuevo nodo con su caracter dado
// y la frecuencia del caracter
struct MinHeapNode* newNode(char data, unsigned freq)
{
    struct MinHeapNode* temp =
          (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}
 
// Uilizamos esta funcion para crear la capacidad de la colecc�on de nodos
struct MinHeap* createMinHeap(unsigned capacity)
{
    struct MinHeap* minHeap =
         (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->size = 0;  // Tama�o actual es 0
    minHeap->capacity = capacity;
    minHeap->array =
     (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}
 
// Utilizamos esta funcion para cambiar 2 nodos de la colecc�on de nodos
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
 
// La funcion estandar de minheapify
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
 
    if (left < minHeap->size &&
        minHeap->array[left]->freq < minHeap->array[smallest]->freq)
      smallest = left;
 
    if (right < minHeap->size &&
        minHeap->array[right]->freq < minHeap->array[smallest]->freq)
      smallest = right;
 
    if (smallest != idx)
    {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}
 
// Utilizamos esta funcion para comprobar si el tama�o de la colecc�on de nodos es 1 o no
int isSizeOne(struct MinHeap* minHeap)
{
    return (minHeap->size == 1);
}
 
// Funcion estandar para extraer el nodo de menor valor de la colecc�on de nodos
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}
 
// Utilizamos esta funcion para inserter un nodo en la colecc�on de nodos
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode)
{
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1)/2]->freq)
    {
        minHeap->array[i] = minHeap->array[(i - 1)/2];
        i = (i - 1)/2;
    }
    minHeap->array[i] = minHeapNode;
}
 
// Funcion estandar para construir un MinHeap
void buildMinHeap(struct MinHeap* minHeap)
{
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}
 
// Utilizamos esta funcion para imprimir una matriz de tama�o n
void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}
 
// Utilizamos esta funcion para comprobar que el nodo es hoja
int isLeaf(struct MinHeapNode* root)
{
    return !(root->left) && !(root->right) ;
}
 
// Crea un min mont�n de la misma capacidad y tama�o e inserta todos los caracteres de
// data[] en minheap. Inicialmente minheap es igual a la capacidad
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size)
{
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}
 // La funcion principal para construir el �rbol de Huffman
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size)
{
    struct MinHeapNode *left, *right, *top;
 
    // paso 1: crear un minheap (coleccion de nodos) de igual capacidad y tama�o que inicialmente ahy
    // Nodos igual al tama�o
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);
 
    // Reiterar mientras que el tama�o de almacenamiento din�mico no se convierte en 1
    while (!isSizeOne(minHeap))
    {
        // Paso 2: Extraiga los dos elementos con menor frecuencia de min heap
        left = extractMin(minHeap);
        right = extractMin(minHeap);
 
        // Paso 3: Crear un nuevo nodo interno con una frecuencia igual a la 
        // Suma de las dos frecuencias de nodos. Hacer los dos nodos extra�do como 
        // Ni�os de derecha de este nuevo nodo a la izquierda y. A�adir este nodo a minheap
        // '$' Es un valor especial para los nodos internos, no se utiliza
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
 
    // Paso 4: El nodo restante es el nodo ra�z y el �rbol esta completo.
    return extractMin(minHeap);
}
 
// Imprime c�digos Huffman de la ra�z del �rbol de Huffman. Utiliza arr [] para 
// C�digos de tienda
void printCodes(struct MinHeapNode* root, int arr[], int top)
{
    // Asigna 0 en la izquierda y repite
    if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
 
    // Asigna 1 en la derecha y repite
    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
 
    // Si esto es un nodo de hoja, entonces contiene una de las entradas 
    // Caracteres, imprimen el car�cter y su c�digo de arr[]
    if (isLeaf(root))
    {
        printf("%c: ", root->data);
        printArr(arr, top);
    }
}
 
// La funci�n principal que construye un �rbol de Huffman y c�digos de impresi�n por la que atraviesa 
// Incorporado el �rbol de Huffman
void HuffmanCodes(char data[], int freq[], int size)
{
   //  Construir el a�rbol de Huffman
   struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
 
   // Imprimir los codigos de Huffman usando el �rbol de Huffman
   int arr[MAX_TREE_HT], top = 0;
   printCodes(root, arr, top);
}
 
// Programa para probar y controlar las funciones anteriores
int main()
{
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 8, 16, 45};
    int size = sizeof(arr)/sizeof(arr[0]);
    HuffmanCodes(arr, freq, size);
    getch();
}
