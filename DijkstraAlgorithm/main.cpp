#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int n; // Tamaño del laberinto (n x n)
vector<string> stringToVectString(std::string Maze)
{
    Maze += '\n';
    vector<string> maze;
    std::string substring;
    for (auto it = Maze.begin(); it != Maze.end(); it++)
    {

        if (*it == '\n')
        {
            maze.push_back(substring);
            substring = "";
            continue;
        }
        substring += *it;
    }
    return maze;
}

// Función para verificar si una celda es transitable (.)
bool isAccessible(vector<string>& maze, int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < n) {
        return maze[x][y] == '.';
    }
    return false;
}

// Función para encontrar la distancia mínima desde (0, 0) a (n-1, n-1) en el laberinto
int path_finder(string maze) {

    vector<string> Maze;
    Maze = stringToVectString(maze);
    n = Maze[0].length();


    int dist[100][100]; // Matriz de distancias mínimas
    bool visited[100][100] = { false }; // Matriz para rastrear las celdas visitadas

    // Direcciones posibles (arriba, abajo, izquierda, derecha)
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = INT_MAX; // Inicializa todas las distancias como infinito
        }
    }

    dist[0][0] = 0; // Distancia desde (0, 0) a sí mismo es 0

    // Bucle principal para buscar la distancia mínima
    for (int k = 0; k < n * n; k++) {
        int minDist = INT_MAX;
        int x=0, y=0;

        // Encuentra la celda con la distancia mínima no visitada
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (!visited[i][j] && dist[i][j] < minDist) {
                    minDist = dist[i][j];
                    x = i;
                    y = j;
                }
            }
        }

        // Marca la celda como visitada
        visited[x][y] = true;

        // Actualiza las distancias de las celdas adyacentes
        for (int dir = 0; dir < 4; dir++) {
            int newX = x + dx[dir];
            int newY = y + dy[dir];

            // Verifica si la celda adyacente es transitable y no ha sido visitada
            if (isAccessible(Maze, newX, newY) && !visited[newX][newY]) {
                dist[newX][newY] = min(dist[newX][newY], dist[x][y] + 1);
            }
        }
    }
    if (dist[n - 1][n - 1] == INT_MAX)
        return -1;
    return dist[n - 1][n - 1]; // Devuelve la distancia mínima a la celda de destino
}

int main() {
    vector<string> maze; // Vector de strings para representar el laberinto

    // Lee el laberinto desde la entrada estándar
    std::string Maze = "......\n......\n......\n......\n.....W\n......";

    int minDistance = path_finder(Maze); // Encuentra la distancia mínima
    cout << "La distancia mínima es: " << minDistance << endl;

    return 0;
}
