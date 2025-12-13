#ifndef LAB2_H
#define LAB2_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXLEN 100
void bubble_sort(int arr[], int n);
void shell_sort(int arr[], int n);
void print_array(int arr[], int n);
void generate_random(int arr[], int n);
int read_from_file(int arr[]);
int main2();
#endif