#include <iostream>
#include <limits>
#include <array>
#include <algorithm>
// using namespace std;

class Simulation {
  private:
    // Private attribute
    double dt = std::numeric_limits<double>::max();
    double at = 1.1;
    double simclock = 0;
    double et = 0.0;
    std::array<double,1> sink;
    int n_arrival = 0;
    int n_depart = 0;
    int npdrop = 0;
    int pid = 0;
    int maxque = 0;

  public:
  	int scheduling(){
  		et = std::min(at,dt);
  	}
  	void result(){
  		std::cout<<"event time:"<<et<<std::endl;
  	}

};

int main() {
	Simulation test;
	test.scheduling();
	test.result();

  
}