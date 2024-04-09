#include <iostream>
#include <vector>
#include "City.h"

using namespace std;

void test1();

void test2();

void test3();



int main() {

  test1();

  test2();

  test3();

  City city;
  int N = 0, M = 0;
  cout << "Enter the number of stations (vertices): ";
  city.int_checker(N);
  cout << "Enter the stations: " << endl;

  for(int i = 0; i < N; i++){
     string station;
     cin >> station;
     if(city.get_crossroads().find(station) != city.get_crossroads().end()){
       cout << "Station already exists. Enter again: " << endl;
       i--;
     }
     else {
       city.get_crossroads().insert(station);
     }
  }
  
  cout << "Enter the number of edges: ";
  city.int_checker(M);
  cout << "Enter the edges in format (u v k), u and v are stations,k is duration: " << endl;
  
  for (int i = 0; i < M; ++i) {
      string u, v;
      int k;
      cin >> u >> v >> k;
      bool edge_added = city.add_edge(u, v, k);
      if(!edge_added) {
        i--;
      }
  }
  
  city.initialize(N);
  city.floyd_warshall(N);
  city.fill_dist_matrix();
  city.fill_station_indices();

  while (true) {
      cout << "Operations:" << endl;
      cout << "1. Add Bus" << endl;
      cout << "2. Construct Street" << endl;
      cout << "3. Details" << endl;
      cout << "4. Quit" << endl;

      int choice;
      cout << "Enter your choice: ";
      cin >> choice;

      if (choice == 1) {
          string A, B;
          cout << "Enter source and destination for the bus route (Ex. A B): ";
          cin >> A >> B;
            city.add_bus(A, B);
      } 
      else if(choice == 2){
          string A, B;
          int dist;
          cout << "Enter source and destination for the street (Ex. A B 3): ";
          cin >> A >> B >> dist;
          city.construct_street(A, B, dist);
      } 
      else if(choice == 3){
          int busID;
          cout << "Enter Bus ID: ";
          cin >> busID;
            city.details(busID);
      } 
      else if(choice == 4){
          break;
      } 
      else {
          cout << "Invalid choice. Please try again." << endl;
      }
  }

  return 0;
}

void test1(){
  cout << "____________________START OF TEST1__________________" << endl;

  City city1;

  cout << "Adding a stations: A, B, C" << endl;
  city1.get_crossroads().insert("A");
  city1.get_crossroads().insert("B");
  city1.get_crossroads().insert("C");
  
  int N = city1.get_crossroads().size();

  cout << "Adding an edge: (A, B, 3)" << endl;
  city1.add_edge("A", "B", 3);
  cout << "Adding an edge: (A, C, 2)" << endl;
  city1.add_edge("A", "C", 2);
  cout << "Adding an edge: (B, C, 1)" << endl;
  city1.add_edge("B", "C", 1);
  cout << "Adding an edge: (Q, W, 4)" << endl;
  city1.add_edge("Q", "W", 4);
  cout << "Adding an edge: (A, a, 12)" << endl;
  city1.add_edge("A", "a", 12);
  cout << endl;

  city1.initialize(N);
  city1.floyd_warshall(N);
  city1.fill_dist_matrix();
  city1.fill_station_indices();

  cout << "Adding a bus route: (A, B)" << endl;
  city1.add_bus("A", "B");
  cout << "Adding a bus route: (A, C)" << endl;
  city1.add_bus("A", "C");
  cout << "Adding a bus route: (B, P)" << endl;
  city1.add_bus("B", "P");
  cout << endl;

  cout << "1rt bus details" << endl;
  city1.details(1);
  cout << "0s bus details" << endl;
  city1.details(0);
  cout << "2rd bus details" << endl;
  city1.details(2);
  cout << endl;

  cout << "Constructing a street: (A, C, 1)" << endl;
  city1.construct_street("A", "C", 1);
  cout << endl;

  cout << "____________________END OF TEST1__________________" << endl;
  cout << endl;

}

void test2(){
  cout << "____________________START OF TEST2__________________" << endl;

  City city2;

  cout << "Adding a stations: e r t" << endl;

  city2.get_crossroads().insert("e");
  city2.get_crossroads().insert("r");
  city2.get_crossroads().insert("t");

  int N = city2.get_crossroads().size();

  cout << "Adding an edge: (e, r, 27)" << endl;
  city2.add_edge("e", "r", 3);
  cout << "Adding an edge: (e, t, 20)" << endl;
  city2.add_edge("e", "t", 2);
  cout << "Adding an edge: (r, t, 17)" << endl;

  city2.initialize(N);
  city2.floyd_warshall(N);
  city2.fill_dist_matrix();
  city2.fill_station_indices();

  cout << "Adding a bus route: (e, t)" << endl;
  city2.add_bus("e", "t");
  cout << "Adding a bus route: (e, r)" << endl;
  city2.add_bus("e", "r");
  cout << endl;


  cout << "Constructing a street: (r, t, 100)" << endl;
  city2.construct_street("r", "t", 100);
  cout << "Constructing a street: (e, r, 15)" << endl;
  city2.construct_street("e", "r", 15);
  cout << "Constructing a street: (e, f, 12)" << endl;
  city2.construct_street("e", "f", 12);
  cout << endl;

  cout << "____________________END OF TEST2__________________" << endl;
  cout << endl;
  
}


void test3(){
  cout << "____________________START OF TEST3__________________" << endl;

  City city3;

  cout << "Adding a stations: b1 b2 b3 b4 b5" << endl;

  city3.get_crossroads().insert("b1");
  city3.get_crossroads().insert("b2");
  city3.get_crossroads().insert("b3");
  city3.get_crossroads().insert("b4");
  city3.get_crossroads().insert("b5");

  int N = city3.get_crossroads().size();

  cout << "Adding an edge: (b1, b5, 207)" << endl;
  city3.add_edge("b1", "b5", 207);
  cout << "Adding an edge: (b2, b5, 455)" << endl;
  city3.add_edge("b2", "b5", 455);
  cout << "Adding an edge: (b2, b3, 187)" << endl;
  city3.add_edge("b2", "b3", 187);

  city3.initialize(N);
  city3.floyd_warshall(N);
  city3.fill_dist_matrix();
  city3.fill_station_indices();

  cout << "Constructing a street: (b1, b4, 100)" << endl;
  city3.construct_street("b1", "b4", 100);
  cout << "Constructing a street: (b2, b5, 150)" << endl;
  city3.construct_street("b2", "b5", 150);
  cout << "Constructing a street: (b4, b5, 120)" << endl;
  city3.construct_street("b4", "b5", 120);
  cout << endl;

  cout << "____________________END OF TEST3__________________" << endl;
  cout << endl;

}



