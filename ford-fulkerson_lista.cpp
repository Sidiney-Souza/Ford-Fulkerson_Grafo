#include <bits/stdc++.h>

using namespace std;

void leituraGrafo(vector<vector<pair<int, int>>> &, int);
void escritaGrafo(vector<vector<pair<int, int>>> &);
bool bfs(vector<vector<int>> &residualGraph, int s, int t, vector<int> &parent);
int fordFulkerson(vector<vector<int>> &graph, int s, int t);

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> Grafo;
    Grafo.assign(n, vector<pair<int, int>>());
    leituraGrafo(Grafo, m);
    escritaGrafo(Grafo);
    cout << "Total Vértices: " << n << endl;
    cout << "Total Arestas: " << m << endl;

    // Convertendo o grafo de lista de adjacência para matriz de adjacência
    vector<vector<int>> graph(n, vector<int>(n, 0));
    for (int u = 0; u < n; u++)
    {
        for (auto v : Grafo[u])
        {
            graph[u][v.first] = v.second;
        }
    }

    int source = 0, sink = n - 1;
    cout << "O fluxo máximo é: " << fordFulkerson(graph, source, sink) << endl;

    return 0;
}

void leituraGrafo(vector<vector<pair<int, int>>> &G, int m)
{
    int a, b;
    double c;
    while (m--)
    {
        cin >> a >> b >> c;
        G[a].push_back(make_pair(b, c));
        // G[b].push_back(make_pair(a, c)); // Descomentar se o grafo for não-direcionado
    }
}

void escritaGrafo(vector<vector<pair<int, int>>> &G)
{
    int n = G.size();
    cout << "Lista de Adjacência:" << endl;
    for (int u = 0; u < n; u++)
    {
        cout << u << ": ";
        for (auto v : G[u])
        {
            cout << "[(" << u << "," << v.first << ") w: " << v.second << "] ";
        }
        cout << endl;
    }
}

bool bfs(vector<vector<int>> &residualGraph, int s, int t, vector<int> &parent)
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

int fordFulkerson(vector<vector<int>> &graph, int s, int t)
{
    int n = graph.size();
    vector<vector<int>> residualGraph = graph;
    vector<int> parent(n);
    int maxFlow = 0;

    while (bfs(residualGraph, s, t, parent))
    {
        int pathFlow = INT_MAX;
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
