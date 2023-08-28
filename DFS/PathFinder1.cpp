/*
Autor: Lagunez Nestor
El algoritmo implementado en el código es un ejemplo de Depth-First Search (DFS) o "Búsqueda en Profundidad". 
Es un enfoque de búsqueda en grafos que explora tan lejos como sea posible a lo largo de cada rama antes de retroceder. 
La recursión se utiliza para explorar diferentes caminos en el laberinto, lo que es característico de DFS. 
También se utiliza la técnica de "backtracking" dentro de la función recorre para deshacer 
los movimientos cuando se llega a un punto sin salida.

El algoritmo implementado es un ejemplo de DFS con uso de "backtracking" 
para resolver un problema de búsqueda de camino en un laberinto.

*/
#include <iostream>
#include <string>


char** StringToCad(std::string& Maze, int& rows)
{
	int caracteres = 0;
	for (auto it = Maze.begin(); *it != '\n'; ++it)
		caracteres++;

	rows = caracteres;
	char** matrix = new char* [rows];
	for (int i = 0; i < rows; ++i) {
		matrix[i] = new char[caracteres];
	}
	int j = 0, i = 0;
	for (char a : Maze) {
		if (a == '\n') {
			i++;
			j = 0;
		}
		else {
			matrix[i][j] = (char)a;
			j++;
		}
	}
	return matrix;
}
const int DIR_ARRIBA = 0;
const int DIR_DERECHA = 1;
const int DIR_ABAJO = 2;
const int DIR_IZQUIERDA = 3;
struct posicion {
	int fila;
	int columna;
};
posicion nueva(int op)
{
	posicion paso;
	switch (op)
	{
	case DIR_ARRIBA:
		paso.fila = -1;
		paso.columna = 0;
		break;
	case DIR_DERECHA:
		paso.fila = 0;
		paso.columna = 1;
		break;
	case DIR_ABAJO:
		paso.fila = 1;
		paso.columna = 0;
		break;
	case DIR_IZQUIERDA:
		paso.fila = 0;
		paso.columna = -1;
		break;
	case 4:
		paso.fila = 0;
		paso.columna = 0;
		break;
	default:
		break;
	}
	return paso;
}

bool dentro(int fila, int colu, int n)
{
	return fila >= 0 && fila < n && colu >= 0 && colu < n;
}

bool valido(posicion hijo,char** mapa, int rows)
{
	return bool(dentro(hijo.fila, hijo.columna, rows) && (mapa[hijo.fila][hijo.columna] != 'W') && (mapa[hijo.fila][hijo.columna] != '-'));
}


bool recorre(char** mapa, posicion actual,int next,int rows)
{
	if(next !=4)
		mapa[actual.fila][actual.columna] = '-';

	bool fin=0;
	posicion siguiente;
	siguiente = nueva(next);
	
	actual.fila += siguiente.fila;
	actual.columna += siguiente.columna;

	if (actual.fila == rows-1 && actual.columna == rows-1)
	{	
		//std::cout << "\n fin \n";
		return 1;
	}

	if (valido(actual, mapa, rows))
	{
		for (int i = 0; i < 4; i++)
		{
			fin = recorre(mapa, actual, i, rows);
			if (fin)
				break;
		}
	}
	return fin;
}

bool path_finder(std::string maze) {

	char** mapa;
	int N;
	mapa = StringToCad(maze, N);

	bool fin;
	posicion actual;
	actual.fila = 0;
	actual.columna = 0;
	fin = recorre(mapa,actual,4, N);

	// Imprimir la matriz
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cout << mapa[i][j] << " ";
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < N; ++i) {
		delete[] mapa[i];
	}
	delete[] mapa;

	return fin;
}



int main() {

	std::string Maze = "......\n......\n......\n......\n......\n......";

	std::cout << path_finder(Maze);
	return 0;
}

