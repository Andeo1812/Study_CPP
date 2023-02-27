#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

struct WeightedListGraph {
    ~WeightedListGraph() = default;

    WeightedListGraph();

    void AddEdge(const auto &from, const auto &to);

    ssize_t CheckEdge(const auto &from, const auto &to) const;

    void UpdateEdge(const auto &from, const auto &to);

    size_t VerticesCount() const;

    WeightedListGraph(const std::vector <std::string> &arr_str);

    void WorkSubstr(const std::string &first, const std::string &next);

    void Print() const;

    void PrintTable() const;

private:
    size_t count_edges;

    std::vector <std::string> table;

    std::unordered_map <size_t, std::string> index_map;
    std::unordered_map <std::string, size_t> str_map;

    std::vector <std::vector<std::pair <size_t, size_t>>> adjacency_lists;
};

void WeightedListGraph::AddEdge(const auto &from, const auto &to) {
    adjacency_lists[from].push_back({1, to});

    ++count_edges;
}

ssize_t WeightedListGraph::CheckEdge(const auto &from, const auto &to) const {
    for (ssize_t i = 0; i < adjacency_lists[from].size(); ++i) {
        if (adjacency_lists[from][i].second == to) {
            return i;
        }
    }

    return -1;
}

void WeightedListGraph::UpdateEdge(const auto &from, const auto &to) {
    ++adjacency_lists[from][to].first;
}

size_t WeightedListGraph::VerticesCount() const {
    return adjacency_lists.size();
}


void WeightedListGraph::WorkSubstr(const std::string &first, const std::string &next) {
    const auto node_table_from = str_map.find(first);

    size_t index_from = 0;

    if (node_table_from == str_map.end()) {
        table.push_back(first);

        size_t size = table.size() - 1;

        str_map.insert(std::make_pair(first, size));
        index_map.insert({size, first});

        adjacency_lists.push_back({});

        index_from = size;
    } else {
        index_from = index_map.find(node_table_from->second )->first;
    }

    const auto node_table_to = str_map.find(next);

    size_t index_to = 0;

    if (node_table_to == str_map.end()) {
        table.push_back(next);

        size_t size = table.size() - 1;

        str_map.insert({next, size});
        index_map.insert({size, next});

        adjacency_lists.push_back({});

        index_to = size;
    } else {
        index_to = index_map.find(node_table_to->second)->first;
    }

    const auto index_edge = CheckEdge(index_from, index_to);

    if (index_edge == -1) {
        AddEdge(index_from, index_to);
    } else {
        UpdateEdge(index_from, index_edge);
    }
}

WeightedListGraph::WeightedListGraph(const std::vector <std::string> &arr_str) {
    count_edges = 0;

    str_map = {};
    index_map = {};

    for (const auto &str: arr_str) {
        for (size_t i = 0; i < str.size() - 3; i += 1) {
            WorkSubstr(str.substr(i, 3), str.substr(i + 1, 3));
        }
    }

    Print();
}

void WeightedListGraph::PrintTable() const {
    std::cout << "-----------Table--------" << std::endl;
    for (auto n: table) {
        std::cout << n << std::endl;
    }
}

void WeightedListGraph::Print() const {
    std::cout << VerticesCount() << std::endl;

    std::cout << count_edges << std::endl;

    for (size_t i = 0; i < adjacency_lists.size(); ++i) {
        auto str = table[i];

        for (size_t j = 0; j < adjacency_lists[i].size(); ++j) {
            auto data = adjacency_lists[i][j];

            std::cout << str << " " << table[data.second] << " " << data.first
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
