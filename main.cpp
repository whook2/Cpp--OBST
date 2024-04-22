// Will Hooker CS317-02
// Project 2
// This program recieves an input file, with the first line containing the number of elements, and each line thereafter containing the number of times that element is searched.
// It then generates an optimal binary search tree for the given keys and number of times each key is searched.
// The program outputs the dynamic programming table (both values and roots), and an optimal binary search tree.
// The pseudocode function from the textbook for creating the binary search tree was used

#include <iostream>
#include <fstream>

using namespace std;

void printTable(int ** S, int** R, int size, ofstream& fout);
void DP_OptimalBinarySearchTree(int p[], int size, int** S, int** R);
void printTree(int** R, int i, int j, int space, ofstream& fout);

int main() {

	ifstream fin("input.txt");  //Creating the file input and output variables
	ofstream fout("wjh0011.txt");

	int size = 0; //Reading in the size from the file
	fin >> size;

	int* array = new int[size + 1]; //Dynamically creating an array of ints

	for (int i = 1; i < (size + 1); i++) { //Reading in the elements from the file
		fin >> array[i];
	}
	
	int** S = new int* [size + 2]; //Dynamically creating 2d arrays of ints
	int** R = new int* [size + 2];
	for (int i = 0; i < size + 2; i++) {
		S[i] = new int[size + 2];
		R[i] = new int[size + 2];
	}
	for (int i = 0; i <= size + 1; i++) { //initializing the array values as 0
		for (int j = 0; j <= size + 1; j++) {
			S[i][j] = 0;
			R[i][j] = 0;
		}
	}
	
	DP_OptimalBinarySearchTree(array, size, S, R);
	printTable(S, R, size, fout);
	printTree(R, 1, size, 0, fout);

	for (int i = 0; i < size; i++) { //Deleting the inner arrays
		delete[] S[i];
		delete[] R[i];
	}
	delete[] S; //Deleting the outer array which held the pointers of the inner arrays
	delete[] R;
	delete[] array; //De-allocating the array memory and closing the text files
	fin.close();
	fout.close();
	return 0;
}

void DP_OptimalBinarySearchTree(int p[], int size, int** S, int** R) {
	
	for (int i = 1; i <= size; i++) {
		S[i][i - 1] = 0;
	}
	for (int i = 1; i <= size; i++) {
		S[i][i] = p[i];
		R[i][i] = i;
	}

	for (int d = 1; d <= (size - 1); d++) {
		for (int i = 1; i <= (size - d); i++) {
			int j = i + d;
			int sum_p = 0, min_value = 9999999999, min_root = 0;
			for (int k = i; k <= j; k++) {
				sum_p += p[k];
				int value = S[i][k - 1] + S[k + 1][j];
				if (value < min_value) {
					min_value = value;
					min_root = k;
				}
			}
			S[i][j] = sum_p + min_value;
			R[i][j] = min_root;
		}
	}
	
}

void printTable(int ** S, int** R, int size, ofstream& fout) {

	fout << "   " << "1\t2\t3\t4\t5\t6\t7\t8" << endl;
	for (int i = 1; i <= size; i++) {
		fout << i << "  ";
		for (int j = 1; j <= size; j++) {
			fout << S[i][j] << ":" << R[i][j] << "\t";
		}
		fout << endl;
	}
	fout << endl;
	return;
}

void printTree(int** R, int i, int j, int space, ofstream& fout) {

	if (i <= j) {
	
		for (int i = 0; i < space; i++) { 
			fout << "\t";
		}
		fout << R[i][j] << endl;
		space++;
		printTree(R, i, R[i][j] - 1, space, fout);
		printTree(R, R[i][j] + 1, j, space, fout);
	}
}