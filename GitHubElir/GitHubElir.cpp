#include <iostream>
#include <vector>
#include <stack>
#include <iomanip>
#include <chrono>

using namespace std;
// Функция для проверки графа на эйлеров путь
bool isEulerianPath(const vector<vector<int>>& graph, int vertices) {
    for (int i = 0; i < vertices; ++i) {
        int inDegree = 0, outDegree = 0;
        for (int j = 0; j < vertices; ++j) {
            inDegree += (graph[j][i] % 2 == 1);
            outDegree += (graph[i][j] % 2 == 1);
        }
        if (inDegree != outDegree) {
            return false;
        }
    }
    return true;
}

// Функция для нахождения эйлерова пути и вывода суммы рёбер
void findEulerianPath(vector<vector<int>>& graph, int startVertex) {
    int vertices = graph.size();
    stack<int> st;
    vector<int> path;
    int totalEdgeSum = 0;

    st.push(startVertex);

    while (!st.empty()) {
        int u = st.top();

        for (int v = 0; v < vertices; ++v) {
            if (graph[u][v] > 0) {
                st.push(v);
                totalEdgeSum += graph[u][v]; // добавляем вес ребра к сумме
                graph[u][v]--; // уменьшаем вес ребра на 1
                break;
            }
        }

        if (u == st.top()) {
            st.pop();
            path.insert(path.begin(), u);
        }
    }

    //Вывод найденного эйлерова пути
    cout << "Эйлеров путь: ";
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i] + 1;
        if (i < path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;

    // Вывод суммы всех пройденных рёбер
    cout << "Сумма всех пройденных рёбер: " << totalEdgeSum << endl;
}

int generateRandomNumber() {
    return rand() % 21;
}
// Оптимизированная функция исправления графа
void fixGraph(vector<vector<int>>& graph, int& SumRoud, int& LostStreats) {
    int vertices = graph.size();
    int random_number = 0;
    cout << "Исправленная матрица смежности:" << endl;
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            if (i != j && graph[i][j] == 0) {
                graph[i][j] = graph[j][i];
                if (graph[i][j] > 0) {
                    random_number = generateRandomNumber();
                    cout << "\x1b[31m" << graph[i][j] + random_number << "\x1b[0m" << " ";
                    SumRoud += random_number + 1;
                    LostStreats++;
                }
                else {
                    cout << "\x1b[32m" << graph[i][j] << "\x1b[0m" << " ";
                }
            }
            else {
                cout << graph[i][j] << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int YourTime;
    cout << "Через сколько автобус отправляется в путь? (В минутах): ";
    cin >> YourTime;
    // Ввод количества вершин
    int vertices;
    cout << "Введите количество вершин: ";
    cin >> vertices;
    int SumRoud = 0;
    int LostStreats = 0;
    // Ввод матрицы смежности с весами рёбер
    cout << "Введите матрицу смежности с весами рёбер (размер " << vertices << "x" << vertices << "):" << endl;
    vector<vector<int>> graph(vertices, vector<int>(vertices, 0));
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            cin >> graph[i][j];
            SumRoud += graph[i][j];
            if (i == j) {
                if (graph[i][j] > 0) {
                    cerr << "Ошибка: Вершина " << i + 1 << " идет в саму себя с весом " << graph[i][j] << "." << endl;
                    exit(1);
                }
            }
            if (graph[i][j] > 0) {
                graph[i][j] = 1;  // если вес ребра > 0, присваиваем 1
            }
        }
    }

    // Проверка наличия эйлерова пути
    if (!isEulerianPath(graph, vertices)) {
        cout << "Данный граф не имеет эйлерового цикла. (Вы забыли про несколько улиц!)" << endl;

        // Исправление графа
        fixGraph(graph, SumRoud, LostStreats);
        cout << "Я добавил их в ваш маршрут! (Кол-во улиц: " << LostStreats << ")" << endl;
    }

    // Ввод начальной вершины
    int startVertex;
    cout << "Введите начальную вершину: ";
    cin >> startVertex;


    // Поиск и вывод эйлерова пути
    findEulerianPath(graph, startVertex - 1);


    // Вывод суммы введенных значений
    cout << "Сколько времени займет пройти весь район: " << SumRoud << " Мин." << endl;

    if (YourTime > SumRoud) {
        cout << "Вы успеваите, у вас даже останется время: " << YourTime - SumRoud << " Мин." << endl;
    }
    else if (YourTime == SumRoud) {
        cout << "Вы успеваете впритык! " << endl;
    }
    else if (YourTime < SumRoud) {
        cout << "Вы не успеваете! " << endl;
    }

    return 0;
}
