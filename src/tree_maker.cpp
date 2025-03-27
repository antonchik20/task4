
#include "../include/tree_maker.hpp"

Point::Point(int id, double x_coord, double y_coord) {
    point_id = id;
    x = x_coord;
    y = y_coord;
}

double Point::calculate_distance(Point& other) const {
    double dx = other.x - x;
    double dy = other.y - y;

    return sqrt(dx * dx + dy * dy);
}

Edge::Edge(int point_1, int point_2, double edge_weight)  {
    u = point_1;
    v = point_2;
    weight = edge_weight;
}

bool Edge::operator<(const Edge& other) const {
    return weight < other.weight;
}

int Edge::get_point_u() const {
    return u;
}

int Edge::get_point_v() const {
    return v;
}

double Edge::get_weight() const {
    return weight;
}

Union_set::Union_set(int n) {
    parent.resize(n + 1);
    rank.resize(n + 1);
    std::iota(parent.begin(), parent.end(), 0);
}

int Union_set::find(int u) {
    if (parent[u] != u) {
        parent[u] = Union_set::find(parent[u]);
    }

    return parent[u];
}

bool Union_set::unite_sets(int u, int v) {
    int root_u = find(u);
    int root_v = find(v);

    if(root_u == root_v) {
        return false;
    }

    if (rank[root_u] > rank[root_v]) {
        parent[root_v] = root_u;
    }
    else if (rank[root_v] > rank[root_u]) {
        parent[root_u] = root_v;
    }
    else {
        parent[root_v] = root_u;
        ++rank[root_u];
    }

    return true;
}

std::vector<Edge> kruskal_tree_algorithm(std::vector<Point>& points) {
    int n = points.size();
    std::vector<Edge> edges;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double weight = points[i].calculate_distance(points[j]);
            edges.push_back({points[i].point_id, points[j].point_id, weight});
        }
    }

    std::sort(edges.begin(), edges.end());

    Union_set u_set(n);

    std::vector<Edge> mst;

    for (Edge& edge : edges) {
        if(u_set.unite_sets(edge.get_point_u(), edge.get_point_v())) {
            mst.push_back(edge);

            if (mst.size() == n - 1) {
                break;
            }

        }
    }

    return mst;
}

std::vector<Point> file_read(std::string& filename) {

    std::ifstream inp(filename);
    std::vector<Point> points;

    std::string line;

    while (std::getline(inp, line)){
        std::stringstream iss(line);
        int id;
        double x, y;
        char comma;

        if(iss >> id>> comma>> x>> comma >> y) {
            points.push_back({id, x, y});
        }
    }

    inp.close();
    return points;
}

bool file_write(std::string& filename, const std::vector<Edge>& mst) {

    std::ofstream out(filename);

    if(!out) {
        std::cerr << "Output file not found";
        return false;
    }

    for (const Edge& edge : mst) {
        out << edge.get_point_u() << " - " << edge.get_point_v() << std::endl;
    }

    out.close();
    return true;
}
