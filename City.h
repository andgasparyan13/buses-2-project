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

  int min_time_required(const string& src, const string& dest) {
    int u = station_indices[src];
    int v = station_indices[dest];
    return dist[u][v];
  }

  void add_bus(const string& A, const string& B) {
    if(crossroads.find(A) == crossroads.end() || crossroads.find(B) == crossroads.end()) {
        cout << "invalid stations" << endl;
        return;
    }
    int min_time =  min_time_required(A, B);
    if(min_time == INF) {
        cout << "No connection" << endl;
        return ;
    }
    buses[buses.size()] = {A, B};
    cout << "Bus added with ID: " << buses.size() - 1 << ". Minimum time required for the bus to reach from " << A << " to " << B << ": " << min_time << " minutes" << endl;
  }

  void construct_street(const string& A, const string& B, int duration) {
    if(crossroads.find(A) != crossroads.end() && crossroads.find(B) != crossroads.end()) {
        if(dist[station_indices[A]][station_indices[B]] >= duration){
            int src = get_station_index(A);
            int dest = get_station_index(B);
            dist[src][dest] = duration;
            dist[dest][src] = duration;
          //change duration in the list
            for(auto& edge : adjacency_list[A]){
                if(edge.first == B){
                    edge.second = duration;
                    break;
                }
            }
            for(auto& edge : adjacency_list[B]){
                if(edge.first == A){
                    edge.second = duration;
                    break;
                }
            }
        }
    }
    else {
        cout << "Invalid crossroad(s)" << endl;
        return;
    }
    cout << "Street constructed between " << A << " and " << B << " with duration " << duration << " minutes." << endl;
    cout << "Minimum durations for all buses after constructing street:" << endl;
    floyd_warshall_update(station_indices.size(), A, B, duration);

    for (auto& bus : buses) {
        auto start = bus.second.first;
        auto destination = bus.second.second;
        int busID = bus.first;
        int new_duration = min_time_required(start, destination);
        cout << "Bus ID: " << busID << ", Updated Duration: " << new_duration << " minutes" << endl;
    }
  }

  void floyd_warshall_update(int num_vertices, const string& A, const string& B, int duration) {
    int u = station_indices[A];
    int v = station_indices[B];
    dist[u][v] = duration;
    dist[v][u] = duration;

    for (int i = 0; i < num_vertices; ++i) {
        if (dist[u][i] != INF && dist[i][v] != INF) {
            dist[u][i] = min(dist[u][i], duration + dist[v][i]);
            dist[i][u] = dist[u][i]; 
        }
        if (dist[v][i] != INF && dist[i][u] != INF) {
            dist[v][i] = min(dist[v][i], duration + dist[u][i]);
            dist[i][v] = dist[v][i]; 
        }
    }
  }

  void details(int bus_ID) {
    if (buses.find(bus_ID) != buses.end()) {
        auto start = buses[bus_ID].first;
        auto destination = buses[bus_ID].second;
        vector<vector<string>> shortest_paths = all_shortest_paths(start, destination);

        if (shortest_paths.empty()) {
            cout << "No shortest path found between " << start << " and " << destination << endl;
        } 
        else {
            cout << "Shortest path(s) between " << start << " and " << destination << ":" << endl;
            for (const auto& path : shortest_paths) {
                for (const auto& node : path) {
                    cout << node << " ";
                }
                cout << endl;
            }
        }
    } 
    else {
        cout << "Bus ID not found!" << endl;
    }
  }

  vector<vector<string>> all_shortest_paths(const string& start, const string& end) {
    vector<vector<string>> shortest_paths;
    int shortest_distance = INF; 
    queue<pair<vector<string>, int>> q;
    vector<string> initial_path;
    initial_path.push_back(start);
    q.push({initial_path, 0});

    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        string last = current.first.back();
        int current_distance = current.second;

        if (last == end) {
            if (current_distance < shortest_distance) {
                shortest_distance = current_distance;
                shortest_paths.clear();
                shortest_paths.push_back(current.first);
            } 
            else if (current_distance == shortest_distance) {
                  shortest_paths.push_back(current.first);
            }
        } 
        else {
            for (const auto& neighbor : adjacency_list[last]) {
                if (find(current.first.begin(), current.first.end(), neighbor.first) == current.first.end()) {
                    vector<string> new_path(current.first);
                    new_path.push_back(neighbor.first);
                    q.push({new_path, current_distance + neighbor.second});
                }
            }
        }
    }
    return shortest_paths;
  }

};
#endif //SIMPLE_CITY_CITY_H
