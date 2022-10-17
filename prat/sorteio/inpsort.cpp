/*
 * main.cpp
 *
 *  Created on: 19 de set de 2022
 *      Author: Emanuel Staub Araldi
 */

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
// Imprime conteúdos de um vetor<int> em ordem
void disp_vec(vector<int> input){
	auto iter = input.begin();
	cout << *iter;
	for (iter++ ; iter != input.end() ; iter++)
		cout << " " << *iter;
	cout << endl;
}

int main(){
	vector<int> input;
	int num; // número que será entrado no vetor

	cout << "Entre com uma série de números (pode ser um por vez, ou separados por espaços) com uma letra para terminar" << endl;

	while (cin>>num) // Avalia como "True" qualquer número i32, crasha caso (INT_MIN>num>INT_MAX)
		input.push_back(num);

	cout << "Números entrados em ordem de entrada" << endl;
	disp_vec(input);
	// Ordena o vetor em ordem crescente
	sort(input.begin(), input.end());
	// Como o vetor já está ordenado, o último elemento é o maior e o primeiro elemento é o menor
	cout << "Maior elemento: " << input.back() << endl;
	cout << "Menor elemento: " << input.front() << endl;
	cout << "Números entrados em ordem crescente" << endl;

	disp_vec(input);
}
