#include "boardLayoutFactory.h"

std::vector<std::shared_ptr<Vertex>> BoardLayoutFactory::createVertices(View* view) {
    std::vector<std::shared_ptr<Vertex>> vertices;
    for (int i = 0; i < 2; i++) {
        std::vector<int> temp = {0, i + 1};
        vertices.push_back(std::make_shared<Vertex>(view, temp));
    }
    for (int i = 2; i < 6; i++) {
        std::vector<int> temp = {i - 2, (i - 2) / 2 + 3, i + 3};
        vertices.push_back(std::make_shared<Vertex>(view, temp));
    }
    for (int i = 6; i < 42; i++) {
        int base = 0;
        bool level = true;
        int mid = 0;
        if (i % 12 == 0) {
            int m = vertices.back()->getadjacentEdgeIndices()[2];
            std::vector<int> temp = {m - 5, m, m + 3};
            vertices.push_back(std::make_shared<Vertex>(view, temp));
            base = m - 5;
            mid = m;
            level = true;
            mid += i % 2;
        } else if (i % 6 == 0) {
            int m = vertices.back()->getadjacentEdgeIndices()[1];
            std::vector<int> temp = {m, m + 6, m + 9};
            vertices.push_back(std::make_shared<Vertex>(view, temp));
            base = m;
            mid = m + 6;
            level = false;
            mid += i % 2;
        } else {
            if (level) {
                std::vector<int> temp = {base, mid, base + 9};
                vertices.push_back(std::make_shared<Vertex>(view, temp));
                mid += i % 2;
            } else {
                std::vector<int> temp = {base, mid, base + 8};
                vertices.push_back(std::make_shared<Vertex>(view, temp));
                mid += (i + 1) % 2;
            }
        }
        base++; 
    }
    for (int i = 42; i < 48; i++) {
        std::vector<int> temp = {i + 12, (i - 42) / 2 + 60, i + 20};
        vertices.push_back(std::make_shared<Vertex>(view, temp));
    }
    for (int i = 48; i < 52; i++) {
        std::vector<int> temp = {i + 15, (i - 48) / 2 + 67, i + 20};
        vertices.push_back(std::make_shared<Vertex>(view, temp));
    }
    for (int i = 52; i < 54; i++) {
        std::vector<int> temp = {i + 17, 71};
        vertices.push_back(std::make_shared<Vertex>(view, temp));
    }
    
    vertices[2]->getadjacentEdgeIndices().erase(vertices[2]->getadjacentEdgeIndices().begin());
    vertices[5]->getadjacentEdgeIndices().erase(vertices[5]->getadjacentEdgeIndices().begin());
    vertices[6]->getadjacentEdgeIndices().erase(vertices[6]->getadjacentEdgeIndices().begin());
    vertices[11]->getadjacentEdgeIndices().erase(vertices[11]->getadjacentEdgeIndices().begin());
    vertices[42]->getadjacentEdgeIndices().erase(vertices[42]->getadjacentEdgeIndices().end() - 1);
    vertices[47]->getadjacentEdgeIndices().erase(vertices[47]->getadjacentEdgeIndices().end() - 1);
    vertices[48]->getadjacentEdgeIndices().erase(vertices[48]->getadjacentEdgeIndices().end() - 1);
    vertices[51]->getadjacentEdgeIndices().erase(vertices[51]->getadjacentEdgeIndices().end() - 1);
    for (int i = 12; i < 42; i += 6) {
        vertices[i]->getIndices().erase(vertices[i]->getadjacentEdgeIndices().begin() + 1);
        vertices[i + 5]->getIndices().erase(vertices[i + 5]->getadjacentEdgeIndices().begin() + 1);
    }
    return vertices;
}

std::vector<std::shared_ptr<Edge>> BoardLayoutFactory::createEdges(View* view,
                                                                   std::vector<std::shared_ptr<Vertex>>* vertices) {
    std::vector<int> edgeVertices[71];
    std::vector<std::shared_ptr<Edge>> edges;
    for (int i = 0; i < vertices->size(); i++) {
        for (auto n : vertices->at(i)->getadjacentEdgeIndices()) {
            edgeVertices[n].push_back(i);
        }
    }
    for (int i = 0; i < 71; i++) {
        edges.push_back(std::make_shared<Edge>(view, edgeVertices[i]));
    }
    return edges;
}

std::vector<std::vector<int>> BoardLayoutFactory::createTileVertices() {
    std::vector<std::vector<int>> tileVertices;
    tileVertices.push_back({0, 1, 3, 4, 8, 9});
    tileVertices.push_back({2, 3, 7, 8, 13, 14});
    tileVertices.push_back({4, 5, 9, 10, 15, 16});
    tileVertices.push_back({6, 7, 12, 13, 18, 19});
    for (int i = 4; i < 18; i++) {
        std::vector<int> v;
        int base = 0;
        if ((i - 3) % 5 == 0 || (i - 6) % 5 == 0) {
            base = tileVertices[i - 1][1] + 2;
        } else {
            base = tileVertices[i - 1][1] + 1;
        }
        tileVertices.push_back({base, base + 1, base + 6, base + 7, base + 12, base + 13});
    }
    tileVertices.push_back({44, 45, 49, 50, 52, 53});
    return tileVertices;
}

int BoardLayoutFactory::getParkIndex(View *view, std::vector<std::shared_ptr<Tile>> tiles) {
    for (auto it : tiles) {
        if (it->getType() == Park) {
            return it->getIndex();
        }
    }
    return 0;
}
