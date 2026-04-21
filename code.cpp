#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct Point {
    int r, c;
};

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

/**
 * Performs a Breadth-First Search to find the shortest distance from (start_r, start_c)
 * to all other reachable cells in the grid, avoiding construction sites (1).
 */
void bfs(int n, int m, const vector<vector<int>>& grid, int start_r, int start_c, vector<vector<int>>& dist) {
    for (int i = 0; i < m; ++i) {
        fill(dist[i].begin(), dist[i].end(), INF);
    }
    if (start_r == -1 || start_c == -1) return;

    queue<Point> q;
    dist[start_r][start_c] = 0;
    q.push({start_r, start_c});

    while (!q.empty()) {
        Point curr = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nr = curr.r + dr[i];
            int nc = curr.c + dc[i];

            if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] != 1) {
                if (dist[nr][nc] == INF) {
                    dist[nr][nc] = dist[curr.r][curr.c] + 1;
                    q.push({nr, nc});
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> grid(m, vector<int>(n));
    int start_r = -1, start_c = -1;
    int end_r = -1, end_c = -1;
    vector<Point> shops;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(cin >> grid[i][j])) break;
            if (grid[i][j] == 2) {
                start_r = i;
                start_c = j;
            } else if (grid[i][j] == 3) {
                end_r = i;
                end_c = j;
            } else if (grid[i][j] == 4) {
                shops.push_back({i, j});
            }
        }
    }

    // dist_from_start[i][j] stores the shortest distance from the starting position (2) to (i, j)
    vector<vector<int>> dist_from_start(m, vector<int>(n));
    // dist_from_home[i][j] stores the shortest distance from the home (3) to (i, j)
    vector<vector<int>> dist_from_home(m, vector<int>(n));

    bfs(n, m, grid, start_r, start_c, dist_from_start);
    bfs(n, m, grid, end_r, end_c, dist_from_home);

    int min_dist = INF;
    // Find an umbrella shop (4) that minimizes the total distance: start -> shop -> home
    for (const auto& shop : shops) {
        if (dist_from_start[shop.r][shop.c] != INF && dist_from_home[shop.r][shop.c] != INF) {
            min_dist = min(min_dist, dist_from_start[shop.r][shop.c] + dist_from_home[shop.r][shop.c]);
        }
    }

    if (min_dist == INF) {
        cout << -1 << endl;
    } else {
        cout << min_dist << endl;
    }

    return 0;
}
