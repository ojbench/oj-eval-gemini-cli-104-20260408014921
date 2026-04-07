#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> grid(m, vector<int>(n));
    int start_x = -1, start_y = -1;
    int end_x = -1, end_y = -1;
    vector<pair<int, int>> shops;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) {
                start_x = i;
                start_y = j;
            } else if (grid[i][j] == 3) {
                end_x = i;
                end_y = j;
            } else if (grid[i][j] == 4) {
                shops.push_back({i, j});
            }
        }
    }

    auto bfs = [&](int sx, int sy) {
        vector<vector<int>> dist(m, vector<int>(n, INF));
        if (sx == -1 || sy == -1) return dist;
        queue<pair<int, int>> q;
        q.push({sx, sy});
        dist[sx][sy] = 0;

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] != 1) {
                    if (dist[nx][ny] == INF) {
                        dist[nx][ny] = dist[x][y] + 1;
                        q.push({nx, ny});
                    }
                }
            }
        }
        return dist;
    };

    vector<vector<int>> dist_start = bfs(start_x, start_y);
    vector<vector<int>> dist_end = bfs(end_x, end_y);

    int min_dist = INF;
    for (auto shop : shops) {
        int d1 = dist_start[shop.first][shop.second];
        int d2 = dist_end[shop.first][shop.second];
        if (d1 != INF && d2 != INF) {
            min_dist = min(min_dist, d1 + d2);
        }
    }

    if (min_dist == INF) {
        cout << 0 << "\n";
    } else {
        cout << min_dist << "\n";
    }

    return 0;
}
