#ifndef TREE_TREE_MAKER_HPP
#define TREE_TREE_MAKER_HPP

#include <iostream>
#include <vector>
#include <numeric>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

class Point {
    double x;
    double y;
public:

    Point(int id, double x_coord, double y_coord);
    int point_id;
    double calculate_distance(Point& other) const;
};

class Edge {
    int u, v;
    double weight;

public:
    Edge(int point_1, int point_2, double edge_weight);
    int get_point_u() const;
    int get_point_v() const;
    double get_weight() const;

    bool operator<(const Edge& other) const;
};

class Union_set {
    std::vector<int> parent;
    std::vector<int> rank;
public:
    Union_set(int n);

    int find(int u);

    bool unite_sets(int u, int v);
};

std::vector<Edge> kruskal_tree_algorithm(std::vector<Point>& points);

std::vector<Point> file_read(std::string& filename);
bool file_write(std::string& filename, const std::vector<Edge>& mst);

#endif //TREE_TREE_MAKER_HPP
