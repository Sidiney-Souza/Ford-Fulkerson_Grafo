#include <bits/stdc++.h>

using namespace std;

void leituraGrafo(vector<vector<double>> &, int);
void escritaGrafo(vector<vector<double>> &);
bool bfs(vector<vector<double>> &residualGraph, int s, int t, vector<int> &parent);
double fordFulkerson(vector<vector<double>> &graph, int s, int t);

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<double>> Grafo;
    Grafo.assign(n, vector<double>(n, 0));
    leituraGrafo(Grafo, m);
    escritaGrafo(Grafo);
    cout << "Total Vértices: " << n << endl;
    cout << "Total Arestas: " << m << endl;

    int source = 0, sink = n - 1;
    cout << "O fluxo máximo é: " << fordFulkerson(Grafo, source, sink) << endl;

    return 0;
}

void leituraGrafo(vector<vector<double>> &G, int m)
{
    int a, b;
    double c;
    while (m--)
    {
        cin >> a >> b >> c;
        G[a][b] = c;
        // G[b][a] = c; // Descomentar se o grafo for não-direcionado
    }
}

void escritaGrafo(vector<vector<double>> &G)
{
    int n = G.size();
    cout << "Matriz de Adjacência:" << endl;
    cout << "   ";
    for (int u = 0; u < n; u++)
    {
        cout << u << " ";
    }
    cout << endl;
    for (int u = 0; u < n; u++)
    {
        cout << u << ": ";
        for (int v = 0; v < n; v++)
        {
            cout << G[u][v] << " ";
        }
        cout << endl;
    }
}

bool bfs(vector<vector<double>> &residualGraph, int s, int t, vector<int> &parent)
{
    int n = residualGraph.size();
    vector<bool> visited(n, false);
    queue<int> q;

    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; v++)
        {
            if (!visited[v] && residualGraph[u][v] > 0)
            {
                if (v == t)
                {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return false;
}

double fordFulkerson(vector<vector<double>> &graph, int s, int t)
{
    int n = graph.size();
    vector<vector<double>> residualGraph = graph;
    vector<int> parent(n);
    double maxFlow = 0;

    while (bfs(residualGraph, s, t, parent))
    {
        double pathFlow = numeric_limits<double>::infinity();
        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }
    return maxFlow;
}