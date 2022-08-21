#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cassert>

#include <algorithm>

struct WeightedListGraph {
    ~WeightedListGraph() = default;

    WeightedListGraph();

    void AddEdge(int from, int to);

    ssize_t CheckEdge(int from, int to) const;

    void UpdateEdge(int from, int to);

    size_t VerticesCount() const;

    std::vector <std::pair<int, int>> GetNextVertices(int vertex) const;

    std::vector <std::pair<int, int>> GetPrevVertices(int vertex) const;

    WeightedListGraph(const std::vector <std::string> arr_str);

    void WorkSubstr(std::string first, std::string next);

    void Print() const;

    void PrintTable() const;

    void CreateTable(std::string word);

private:
    size_t count_edges;

    std::vector <std::string> table;

    std::vector <std::vector<std::pair < int, int>>>
    adjacency_lists;
};

void WeightedListGraph::AddEdge(int from, int to) {
    //  std::cout << "add edge " << from << " " << to << " " << adjacency_lists[from].size() << std::endl;

    //  std::cout << table[from] << " " << table[to] << " " << std::endl;

    adjacency_lists[from].push_back({1, to});
    //  std::cout << "add edge " << adjacency_lists[from].size() << " " << adjacency_lists[from][adjacency_lists[from].size() - 1].second << std::endl;

    ++count_edges;
}

ssize_t WeightedListGraph::CheckEdge(int from, int to) const {
    for (ssize_t i = 0; i < adjacency_lists[from].size(); ++i) {
        //  std::cout << "check " << adjacency_lists[from][i].second << " " << i << " " << to << std::endl;

        if (adjacency_lists[from][i].second == to) {
            //  std::cout << "check " << adjacency_lists[from][i].second << " " << i << " " << to << std::endl;

            return i;
        }
    }

    return -1;
}

void WeightedListGraph::UpdateEdge(int from, int to) {
    ++adjacency_lists[from][to].first;
}

size_t WeightedListGraph::VerticesCount() const {
    return adjacency_lists.size();
}

std::vector <std::pair<int, int>> WeightedListGraph::GetNextVertices(int vertex) const {
    std::vector <std::pair<int, int>> next_vertices(adjacency_lists[vertex].size());

    for (size_t i = 0; i < adjacency_lists[vertex].size(); ++i) {
        next_vertices[i] = adjacency_lists[vertex][i];
    }

    return next_vertices;
}

std::vector <std::pair<int, int>> WeightedListGraph::GetPrevVertices(int vertex) const {
    std::vector <std::pair<int, int>> prev_vertices;

    for (size_t i = 0; i < adjacency_lists.size(); ++i) {
        for (const auto &value: adjacency_lists[i]) {
            if (vertex == value.second) {

                prev_vertices.push_back(adjacency_lists[vertex][i]);

                break;
            }
        }
    }

    return prev_vertices;
}

void WeightedListGraph::WorkSubstr(std::string first, std::string next) {
    auto node_table_from = std::find(table.begin(), table.end(), first);

    size_t index_from = std::distance(table.begin(), node_table_from);

    auto node_table_to = std::find(table.begin(), table.end(), next);

    size_t index_to = std::distance(table.begin(), node_table_to);

    auto index_edge = CheckEdge(index_from, index_to);

    if (index_edge == -1) {
        AddEdge(index_from, index_to);
    } else {
        UpdateEdge(index_from, index_edge);
    }

}

void WeightedListGraph::CreateTable(std::string word) {
    if (!table.empty()) {
        auto node_table = std::find(table.begin(), table.end(), word);

        if (node_table == table.end()) {
            table.push_back(word);

            adjacency_lists.push_back({});

        }
    } else {
        table.push_back(word);

        adjacency_lists.push_back({});
    }
}


WeightedListGraph::WeightedListGraph(const std::vector <std::string> arr_str) {
    count_edges = 0;

    for (size_t k = 0; k < arr_str.size(); ++k) {
        for (size_t i = 0; i < arr_str[k].size() - 2; ++i) {
            std::string word = arr_str[k].substr(i, 3);
            CreateTable(word);
        }
    }

    //  PrintTable();

    for (size_t k = 0; k < arr_str.size(); ++k) {
        std::string buf_first;

        std::string buf_next;

        for (size_t i = 0; i < arr_str[k].size() - 3; ++i) {
            buf_first = arr_str[k].substr(i, 3);

            buf_next = arr_str[k].substr(i + 1, 3);

            //  std::cout << buf_first << " " << buf_next << std::endl;
            //  std::cout << i << std::endl;

            WorkSubstr(buf_first, buf_next);
        }

//        if (k != arr_str.size() - 1) {
//            buf_first = arr_str[k].substr(0, 3);
//
//            WorkSubstr(buf_next, buf_next);
//        }
    }

    Print();

    //  PrintTable();
}

void WeightedListGraph::PrintTable() const {
    std::cout << "-----------Table--------" << std::endl;
    for (auto n: table) {
        std::cout << n << std::endl;
    }
}

void WeightedListGraph::Print() const {
    std::cout << adjacency_lists.size() << std::endl;

    std::cout << count_edges << std::endl;

    for (size_t i = 0; i < adjacency_lists.size(); ++i) {
        //  std::cout << i << std::endl;
        for (size_t j = 0; j < adjacency_lists[i].size(); ++j) {
            std::cout << table[i] << " " << table[adjacency_lists[i][j].second] << " " << adjacency_lists[i][j].first
                      << std::endl;
        }
    }
}

void run(std::istream &input, std::ostream &output) {
    size_t count = 0;

    input >> count;

    std::vector <std::string> arr_str;

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