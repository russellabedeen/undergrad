#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<iomanip>
using namespace std;

class Vertex
{
    public:
    string site;
    double rank;
    vector<string> links;
    Vertex(string _site);
};

Vertex::Vertex(string _site) {

    site = _site;
}

class AdjacencyList
{
    private:
    vector<Vertex> graph;
    vector<vector<double>> matrix;

    public:
    void insertEdge(string from, string to);
    void pageRank(int iteration);
    void genMatrix();
    void powerIter();
    void printList();
    void printRanks();
    vector<Vertex> sort();
};

void AdjacencyList::insertEdge(string from, string to) {
    bool fromExists = false;
    bool toExists = false;
    int fromIndex = -1;
    for (int i = 0; i < graph.size(); i++) {
        if (graph[i].site == from) {
            fromExists = true;
            fromIndex = i;
        }
        if (graph[i].site == to) {
            toExists = true;
        }
    }

    if (!fromExists) {
        graph.push_back(Vertex(from));
        graph[graph.size() - 1].links.push_back(to);
    }
    else {
        graph[fromIndex].links.push_back(to);
    }

    if (!toExists) {
        graph.push_back(Vertex(to));
    }

}

void AdjacencyList::pageRank(int iteration) {
    for (int i = 0; i < graph.size(); i++) {
        graph[i].rank = double(1) / double(graph.size());
    }
    genMatrix();

    for (int i = 1; i < iteration; i++) {
        powerIter();
    }

}

void AdjacencyList::genMatrix() {
    for (int i = 0; i < graph.size(); i++) {
        vector<double> toAdd;
        for (int j = 0; j < graph.size(); j++) {
            bool isLinked = false;
            for (int k = 0; k < graph[j].links.size(); k++) {
                if (graph[j].links[k] == graph[i].site) {
                    isLinked = true;
                }
            }
            if (isLinked) {
                toAdd.push_back(double(1) / double(graph[j].links.size()));
            }
            else {
                toAdd.push_back(0);
            }
        }
        matrix.push_back(toAdd);
    }
}

void AdjacencyList::powerIter() {
    vector<Vertex> array = graph;
    for (int i = 0; i < matrix.size(); i++) {
        double rank = 0;
        for (int j = 0; j < matrix[i].size(); j++) {
            rank += array[j].rank * matrix[i][j];
        }
        graph[i].rank = rank;
    }
}

void AdjacencyList::printList() {
    for (int i = 0; i < graph.size(); i++) {
        cout << graph[i].site << " | ";
        for (int j = 0; j < graph[i].links.size(); j++) {
            cout << graph[i].links[j] << " ";
        }
        cout << "\n";
    }
}

void AdjacencyList::printRanks() {
    vector<Vertex> array = sort();
    for (int i = 0; i < array.size(); i++) {
        cout << array[i].site << " " << array[i].rank << "\n";
    }
}

vector<Vertex> AdjacencyList::sort() {
    vector<Vertex> array = graph;
    Vertex key = Vertex("");
    int k;
    for (int i = 1; i < array.size(); i++) {
        key = array[i];
        k = i;
        while (k > 0 && array[k - 1].site.compare(key.site) > 0) {
            array[k] = array[k - 1];
            k--;
        }
        array[k] = key;
    }
    return array;
}

int main()
{
    cout << fixed;
    cout << setprecision(2);
    AdjacencyList a;
    int lineNo, iterNo;
    cin >> lineNo;
    cin >> iterNo;
    for (int i = 0; i < lineNo; i++) {
        string arg1, arg2;
        cin >> arg1;
        cin >> arg2;
        a.insertEdge(arg1, arg2);
    }
    a.pageRank(iterNo);
    a.printRanks();
}