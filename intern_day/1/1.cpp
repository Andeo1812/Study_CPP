#include <iostream>
#include <vector>
#include <algorithm>

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

    void CreateTable(const std::string &first);

private:
    size_t count_edges;

    std::vector <std::string> table;

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
    if (table.empty()) {
        table.push_back(first);

        adjacency_lists.push_back({});

        if (next != first) {
            table.push_back(next);
            adjacency_lists.push_back({});

            AddEdge(0, 1);
        } else {
            AddEdge(0, 0);
        }

        return;
    }
    const auto node_table_from = std::find(table.begin(), table.end(), first);

    const size_t index_from = std::distance(table.begin(), node_table_from);

    const auto node_table_to = std::find(table.begin(), table.end(), next);

    size_t index_to = 0;

    if (node_table_to == table.end()) {
        table.push_back(next);

        adjacency_lists.push_back({});

        index_to = table.size() - 1;

        //  std::cout << index_from << " " << index_to << std::endl;

        AddEdge(index_from, index_to);

        return;
    }

    index_to = std::distance(table.begin(), node_table_to);

    const auto index_edge = CheckEdge(index_from, index_to);

    if (index_edge == -1) {
        AddEdge(index_from, index_to);
    } else {
        UpdateEdge(index_from, index_edge);
    }
}

void WeightedListGraph::CreateTable(const std::string &first) {
    const auto node_table_from = std::find(table.begin(), table.end(), first);

    if (node_table_from == table.end()) {
        table.push_back(first);

        adjacency_lists.push_back({});
    }
}


WeightedListGraph::WeightedListGraph(const std::vector <std::string> &arr_str) {
    count_edges = 0;

    for (const auto &str: arr_str) {
        std::string buf_first;

        std::string buf_next;

        for (size_t i = 0; i < str.size() - 3; ++i) {
            buf_first = str.substr(i, 3);

            buf_next = str.substr(i + 1, 3);

            WorkSubstr(buf_first, buf_next);
        }

//        if (str != *arr_str.end()) {
//            buf_first = str.substr(0, 3);
//
//            WorkSubstr(buf_next, buf_next);
//        }

        //  WorkSubstr(buf_next, buf_next);
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