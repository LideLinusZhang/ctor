#include "boardFactory.h"

std::vector<std::shared_ptr<Vertex>> BoardFactory::createVertices(View* view) {
    std::vector<std::shared_ptr<Vertex>> vertices;
    for (int i = 0; i < 2; i++) {
        vertices.push_back(std::make_shared<Vertex>(view, {0, i + 1}));
    }
    for (int i = 2; i < 6; i++) {
        vertices.push_back(std::make_shared<Vertex>(view, {i - 2, (i - 2) / 2 + 3, i + 3}));
    }
    for (int i = 6; i < 42; i++) {
        int base = 0;
        bool level = true;
        int mid = 0;
        if (i % 12 == 0) {
            int m = vertices.back()->getIndices()[2];
            vertices.push_back(std::make_shared<Vertex>(view, {m - 5, m, m + 3}));
            base = m - 5;
            mid = m;
            level = true;
            mid += i % 2;
        } else if (i % 6 == 0) {
            int m = vertices.back().getIndices()[1];
            vertices.push_back(std::make_shared<Vertex>(view, {m, m + 6, m + 9}));
            base = m;
            mid = m + 6
            level = false;
            mid += i % 2;
        } else {
            if (level) {
                vertices.push_back(std::make_shared<Vertex>(view, {base, mid, base + 9}));
                mid += i % 2;
            } else {
                vertices.push_back(std::make_shared<Vertex>(view, {base, mid, base + 8}));
                mid += (i + 1) % 2;
            }
        }
        base++; 
    }
    for (int i = 42; i < 48; i++) {
        vertices.push_back(std::make_shared<Vertex>(view, {i + 12, (i - 42) / 2 + 60, i + 20}));
    }
    for (int i = 48; i < 52; i++) {
        vertices.push_back(std::make_shared<Vertex>(view, {i + 15, (i - 48) / 2 + 67, i + 20}));
    }
    for (int i = 52; i < 54; i++) {
        vertices.push_back(std::make_shared<Vertex>(view, {i + 17, 71}));
    }
    
    vertices[2]->getIndices().erase(vertices[2]->getIndices().begin());
    vertices[5]->getIndices().erase(vertices[5]->getIndices().begin());
    vertices[6]->getIndices().erase(vertices[6]->getIndices().begin());
    vertices[11]->getIndices().erase(vertices[11]->getIndices().begin());
    vertices[42]->getIndices().erase(vertices[42]->getIndices().end() - 1);
    vertices[47]->getIndices().erase(vertices[47]->getIndices().end() - 1);
    vertices[48]->getIndices().erase(vertices[48]->getIndices().end() - 1);
    vertices[51]->getIndices().erase(vertices[51]->getIndices().end() - 1);
    for (int i = 12; i < 42; i += 6) {
        vertices[i]->getIndices().erase(vertices[i]->getIndices().begin() + 1);
        vertices[i + 5]->getIndices().erase(vertices[i + 5]->getIndices().begin() + 1);
    }
    return vertices;
}

std::vector<std::shared_ptr<Edge>> BoardFactory::createEdges(View* view, 
                                                            std::vector<std::shared_ptr<Vertex>>* vertices) {
    std::vector<int> edgeVertices[71];
    std::vector<Edge> edges;
    for (int i = 0; i < vertices->size(); i++) {
        for (auto n : vertices->at(i)->getIndices()) {
            edgeVertices[n].push_back(i);
        }
    }
    for (int i = 0; i < 71; i++) {
        edges.push_back(std::make_shared<Edge>(view, edgeVertices[i]));
    }
    return edges;
}

std::vector<std::vector<int>> BoardFactory::createTileVertices() {
    std::vector<std::vector<int>> tileVertices;
    tileVertices.push_back({0, 1, 3, 4, 8, 9});
    tileVertices.push_back({2, 3, 7, 8, 13, 14});
    tileVertices.push_back({4, 5, 9, 10, 15, 16});
    tileVertices.push_back({6, 7, 12, 13, 18, 19});
    for (int i = 4; i < 18; i++) {
        vector<int> v;
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

int getParkIndex(View *view, std::vector<std::shared_ptr<Tile>> tiles) {
    for (auto it : tiles) {
        if (it->getType() == Park) {
            return it->getIndex();
        }
    }
    view->printError(ErrorType::InvalidOperation);
    return 0;
}
