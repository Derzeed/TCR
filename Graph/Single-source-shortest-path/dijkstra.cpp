
vi Dijkstra(vvii &con, int s) {
  vi dis(con.size(), -1);
  priority_queue<ii> q;
  q.push({0, s});

  while(!q.empty()) {
    int v, d; // d is negative
    tie(v, d) = q.top();
    q.pop();
    if(dis[v] != -1) continue;
    dis[v] = -d;
    for(auto e : con[v]) {
      q.push({d-e.F, e.S});
    }
  }
  return dis;
}

int main() {
  return 0;
}
