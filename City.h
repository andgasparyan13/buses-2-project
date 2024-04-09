#ifndef SIMPLE_CITY_CITY_H
#define SIMPLE_CITY_CITY_H

#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>
#include <list>
#include <cstring>
#include <string>
#include <iostream>
#include <climits>
#include <algorithm>

const int INF = 10000000;

using namespace std;

class City {
private:

unordered_map<string, list<pair<string, int>>> adjacency_list;
unordered_map<string, int> station_indices;
vector<vector<int>> dist;
unordered_map<int, pair<string, string>> buses;
unordered_set<string> crossroads;

public:

  unordered_map<string, list<pair<string, int>>> get_adjacency_list(){
    return this->adjacency_list;
  }

  unordered_map<string, int> get_station_indices(){
    return this->station_indices;
  }

  vector<vector<int>> get_dist_matrix(){
    return this->dist;
  }

  unordered_map<int, pair<string, string>> get_buses(){
    return this->buses;
  }

  unordered_set<string> get_crossroads(){
    return this->crossroads;
  }

  void int_checker(int &input) {
    while (!(cin >> input)) {
        cout << "Invalid input. Please enter an integer: ";
        cin.clear();  // Clear error flags
        cin.ignore(INF, '\n');  // Discard invalid input
    }
  }

  bool add_edge(const string src, const string dest, int duration) {
    if(crossroads.find(src) != crossroads.end() && crossroads.find(dest) != crossroads.end()){
        if(dist[station_indices[src]][station_indices[dest]] > duration)
        adjacency_list[src].push_back({dest, duration});
        adjacency_list[dest].push_back({src, duration});
    }
    else {
        cout << "Invalid crossroad(s)." << endl;
        return false;
    }
    return true;
  }

void initialize(int N) {
    dist.assign(N, vector<int>(N, INF));
    for (int i = 0; i < N; ++i) {
        dist[i][i] = 0;
    }
  }

  void floyd_warshall(int n) {
  for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
  }

  int get_station_index(const string& station) {
    if (station_indices.find(station) == station_indices.end()) {
        int index = station_indices.size();
        station_indices[station] = index;
    }
    return station_indices[station];
  }

  void fill_dist_matrix(){
    for (const auto& pair : adjacency_list){
        int u = station_indices[pair.first];
        for (const auto& edge : pair.second) {
            int v = station_indices[edge.first];
            dist[u][v] = edge.second;
            dist[v][u] = edge.second;
        }
    }
  }

  void fill_station_indices(){
    for (const auto& pair : adjacency_list){
        get_station_index(pair.first);
    }
  }

};
#endif //SIMPLE_CITY_CITY_H
