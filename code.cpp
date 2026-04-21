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

void bfs(int n, int m, const vector<vector<int>>& grid, int start_r, int start_c, vector<vector<int>>& dist) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            dist[i][j] = INF;
        }
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

    vector<vector<int>> dist2(m, vector<int>(n));
    vector<vector<int>> dist3(m, vector<int>(n));

    bfs(n, m, grid, start_r, start_c, dist2);
    bfs(n, m, grid, end_r, end_c, dist3);

    int min_dist = INF;
    for (const auto& shop : shops) {
        if (dist2[shop.r][shop.c] != INF && dist3[shop.r][shop.c] != INF) {
            min_dist = min(min_dist, dist2[shop.r][shop.c] + dist3[shop.r][shop.c]);
        }
    }

    if (min_dist == INF) {
        cout << -1 << endl;
    } else {
        cout << min_dist << endl;
    }

    return 0;
}
