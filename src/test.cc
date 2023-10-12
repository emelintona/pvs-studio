#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int ct_op = 0;
int range = 0;

void swap(int &a, int &b) {
  int t = a;
  a = b;
  b = t;
  // ct_op++;
}

void stampa(int *A, int n) {
  int i;
  for (i = 0; i < n; ++i) {
    printf("%d ", A[i]);
    ct_op++;
  }
  printf("\n");
}
void swap_arr(int *A, int n) {
  int i;
  int j = n - 1;
  for (i = n / 2; i < n; ++i) {
    ct_op++;
    if (j >= i) {
      swap(A[i], A[j]);
      j--;
    } else
      break;
  }
}

void merge(int *A, int p, int q, int r, int *L, int *R) {

  /// copia valori delle due meta p..q e q+1..r
  int i = 0;
  int j = 0;
  int k = 0;

  for (i = 0; i < q - p + 1; i++) {
    ct_op++;
    L[i] = A[p + i];
  }

  ct_op++;
  L[i] = 1000000; /// un numero grande

  for (i = 0; i < r - q; i++) {
    ct_op++;
    R[i] = A[q + 1 + i];
  }

  ct_op++;
  R[i] = 1000000; /// un numero grande

  i = 0; /// usato per gestire array L
  j = 0; /// usato per gestire array R

  for (k = p; k <= r; k++) {
    if (L[i] <= R[j]) {
      ct_op++;
      A[k] = L[i];
      i++;
    } else {
      ct_op++;
      A[k] = R[j];
      j++;
    }
  }
}

void merge_sort(int *A, int p, int r, int *L, int *R) {
  /// gli array L e R sono utilizzati come appoggio per copiare i valori: evita
  /// le allocazioni nella fase di merge
  if (p < r) {
    int q = (p + r) / 2;
    merge_sort(A, p, q, L, R);
    merge_sort(A, q + 1, r, L, R);
    merge(A, p, q, r, L, R);
  }
}



int main(int argc, char **argv) {
  int i;
  srand((unsigned)time(NULL));

  // dim array da ordinare
  int n = atoi(argv[1]);


  // il massimo numero che la prima parte dell'array puo avere
  int stop = n / 10;

  int *A = new int[n];
  int *L = new int[n + 1];
  int *R = new int[n + 1];
  // int* R=new int[n];

  // inizializzazione
  for (i = 0; i < n / 2; ++i) {
    A[i] = rand() % (n / 10);
    ct_op++;
  }

  for (i = n / 2; i < n; ++i) {
    A[i] = (n - i) * (n - i);
    // conta quanti numeri sono nel range della prima parte dell'array
    if (A[i] <= stop)
    {
      ct_op++;
      range++;
    }
      
    ct_op++;
  }
  // std::cout << "Input: \n";
  // stampa(A, n);

  // sort seconda parte
  swap_arr(A, n);

  // sort prima parte
  merge_sort(A, 0, n / 2 + range, L, R);

  // insertion_sort(A, n, range);

  std::cout << "Output: \n";
  stampa(A, n);

  std::ofstream file1;
  file1.open("test.txt");
  file1 << ct_op;

  return 0;
}
