#include "../include/tree_maker.hpp"

int main() {
    std::string inp_filename = "../io_files/text.txt";
    std::string out_filename = "../io_files/textout.txt";

    file_read(inp_filename);

    std::vector<Point> points = file_read(inp_filename);

    if (points.empty()) {
        std::cerr << "Input file not found/failed to open";
        return 1;
    }

    auto mst = kruskal_tree_algorithm(points);
    bool write_success = file_write(out_filename, mst);

    if (!write_success) {
        return 1;
    }

    return 0;
}
