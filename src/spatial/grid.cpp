#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

int comparison = 0;

class Point {
public:
    int x;
    int y;
    int index;
    Point(int _index, ii _xy) {
        index = _index;
        x = _xy.first;
        y = _xy.second;
    }
    Point(int _index, int _x, int _y) {
        index = _index;
        x = _x;
        y = _y;
    }
};

class Grid {
private:
    static const int GRID_SIZE = 2;
    static const int NUM_GRID = 108;
    static const int MIN_POINT = -102;
    static const int MAX_POINT = 102;
    vector<Point> grid[NUM_GRID][NUM_GRID];
    double dist(Point a, Point b) {
        comparison++;
        return hypot(a.x-b.x, a.y-b.y);
    }
    vector<ii> detectCollisionsInGrid(int x, int y, double collisionDistance) {
        vector<ii> results;
        for (int i=0; i<grid[x][y].size(); i++) {
            for (int j=i+1; j<grid[x][y].size(); j++) {
                if (dist(grid[x][y][i], grid[x][y][j]) <= collisionDistance) {
                    results.push_back(ii(grid[x][y][i].index, grid[x][y][j].index));
                }
            }
        }
        return results;
    }
    vector<ii> detectCollisionsInGrid(int x1, int y1, int x2, int y2, double collisionDistance) {
        vector<ii> results;
        for (int i=0; i<grid[x1][y1].size(); i++) {
            for (int j=0; j<grid[x2][y2].size(); j++) {
                if (dist(grid[x1][y1][i], grid[x2][y2][j]) <= collisionDistance) {
                    results.push_back(ii(grid[x1][y1][i].index, grid[x2][y2][j].index));
                }
            }
        }
        return results;
    }
public:
    Grid() {

    }
    void addPoint(int index, int x, int y) {
        int gridX = (x - MIN_POINT) / GRID_SIZE;
        int gridY = (y - MIN_POINT) / GRID_SIZE;
        grid[gridX][gridY].push_back(Point(index, x, y));
    }
    vector<ii> detectCollisions(double collisionDistance) {
        vector<ii> results;
        vector<ii> res;
        for (int i=0; i<NUM_GRID; i++) {
            for (int j=0; j<NUM_GRID; j++) {
                res = detectCollisionsInGrid(i, j, collisionDistance);
                for (int k=0; k<res.size(); k++) {
                    results.push_back(res[k]);
                }
                res = detectCollisionsInGrid(i, j, i-1, j, collisionDistance);
                for (int k=0; k<res.size(); k++) {
                    results.push_back(res[k]);
                }
                res = detectCollisionsInGrid(i, j, i-1, j-1, collisionDistance);
                for (int k=0; k<res.size(); k++) {
                    results.push_back(res[k]);
                }
                res = detectCollisionsInGrid(i, j, i, j-1, collisionDistance);
                for (int k=0; k<res.size(); k++) {
                    results.push_back(res[k]);
                }
                res = detectCollisionsInGrid(i, j, i+1, j-1, collisionDistance);
                for (int k=0; k<res.size(); k++) {
                    results.push_back(res[k]);
                }
            }
        }
        return results;
    }
};

Grid *grid;

int main() {
    int n, temp;
    int x[1010], y[1010];
    grid = new Grid();
    vector<ii> v;
    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> x[i] >> y[i];
        grid->addPoint(i, x[i], y[i]);
    }
    v = grid->detectCollisions(2.0f);
    for (int i=0; i<v.size(); i++) {
        temp = max(v[i].first, v[i].second);
        v[i].first = min(v[i].first, v[i].second);
        v[i].second = temp;
    }
    sort(v.begin(), v.end());
    cout << comparison << endl;
    cout << v.size() << endl;
    for (int i=0; i<v.size(); i++) {
        cout << v[i].first << " " << v[i].second << endl;
    } 
    return 0;
}
