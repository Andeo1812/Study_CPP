#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cassert>

#include <algorithm>

struct Node {
    std::string data;
    int i;
    int weight;

    Node(const Node&) = default;

    Node(const std::string data, const int i, const int weight) : data(data), i(i), weight(weight) {}
};

struct WeightedListGraph {
    ~WeightedListGraph() = default;

    WeightedListGraph();

    void Resize();

    void AddEdge(int from, int to);

    size_t CheckEdge(int from, int to) const;

    void UpdateEdge(int from, int to);

    size_t VerticesCount() const;

    std::vector<std::pair<int, int>> GetNextVertices(int vertex) const;

    std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const;

    WeightedListGraph(const std::vector <std::string> arr_str);

private:
    std::vector<std::vector<std::pair<int, int>>> adjacency_lists;
};

WeightedListGraph::WeightedListGraph() : adjacency_lists(8) {}

void WeightedListGraph::AddEdge(int from, int to) {
    adjacency_lists[from].push_back({1, to});
}

size_t WeightedListGraph::CheckEdge(int from, int to) const {
   for (size_t i = 0; i < adjacency_lists[from].size(); ++i) {
       if (adjacency_lists[from][i].second == to) {
           return i;
       }
   }

    return 0;
}

void WeightedListGraph::UpdateEdge(int from, int to) {
    ++adjacency_lists[from][to].first;
}

size_t WeightedListGraph::VerticesCount() const {
    return adjacency_lists.size();
}

std::vector<std::pair<int, int>> WeightedListGraph::GetNextVertices(int vertex) const {
    std::vector<std::pair<int, int>> next_vertices(adjacency_lists[vertex].size());

    for (size_t i = 0; i < adjacency_lists[vertex].size(); ++i) {
        next_vertices[i] = adjacency_lists[vertex][i];
    }

    return next_vertices;
}

std::vector<std::pair<int, int>> WeightedListGraph::GetPrevVertices(int vertex) const {
    std::vector<std::pair<int, int>> prev_vertices;

    for (size_t i = 0; i < adjacency_lists.size(); ++i) {
        for (const auto &value : adjacency_lists[i]) {
            if (vertex == value.second) {

                prev_vertices.push_back(adjacency_lists[vertex][i]);

                break;
            }
        }
    }

    return prev_vertices;
}


WeightedListGraph::WeightedListGraph(const std::vector <std::string> arr_str) {
    std::vector<std::string> table;

    for (const auto &str: arr_str) {
        for (size_t i = 0; i < str.size() - 3; ++i) {
            std::string buf_first = str.substr(i, 3);

            std::string buf_next = str.substr(i + 1, 3);

            std::string buf;

            if (!table.empty()) {
                auto res = std::find(table.begin(), table.end(), buf_next);

                if (res == table.end()) {
                    table.push_back(buf_next);

                    adjacency_lists.push_back({});
                } else {
                    auto node_table_from = std::find(table.begin(), table.end(), buf_first);

                    size_t index_from = std::distance(table.begin(), node_table_from);

                    size_t index_to = std::distance(table.begin(), res);

                    auto res = CheckEdge(index_from, index_to);

                    if (!res) {
                        AddEdge(index_from, index_to);
                    } else {
                        UpdateEdge(index_from, res);
                    }

                }
            } else {
                table.push_back(buf_first);

                adjacency_lists.push_back({});
            }

        }
    }

    for (size_t i = 0; i < adjacency_lists.size(); ++i) {
        for (size_t j = 0; j < adjacency_lists[i].size(); ++j) {
            std::cout << adjacency_lists[i][j].first << std::endl;
        }
    }

    std::cout << std::endl;
    for (auto n: table) {
        std::cout << n << std::endl;
    }

    std::cout << adjacency_lists.size() << std::endl;
}


void run(std::istream &input, std::ostream &output) {
    size_t count = 0;

    input >> count;

    std::vector<std::string> arr_str;

    std::string buf;

    for (size_t i = 0; i < count; ++i) {
        input >> buf;

        arr_str.push_back(buf);
    }

    WeightedListGraph graph(arr_str);
}


int main() {
    run(std::cin, std::cout);

    return EXIT_SUCCESS;
}