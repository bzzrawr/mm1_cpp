// #include<iostream>
// using namespace std;

// class sim{
// private:
// 	double simclock = 0;
// 	double at = 0
// 	int salary;

// public:
// 	void set_dt(double s){
// 		salary = s;
// 	}
// 	int get_dt(){
// 		return salary;
// 	}
// }

// int main(){
// 	sim test;
// 	test.set_dt(100.1);
// 	std::cout<<"test"<<test.get_dt();
// 	return 0;
// }
#include <iostream>
#include <limits>
// using namespace std;

class Simulation {
  private:
    // Private attribute
    double dt = std::numeric_limits<double>::infinity();

  public:
    // Setter
    void setSalary(double s) {
      dt = s;
    }
    // Getter
    int getSalary() {
      return dt;
    }
};

int main() {
  Simulation myObj;
  if(myObj.getSalary()>100){
  	myObj.setSalary(50000);
  }
  std::cout << myObj.getSalary();
  return 0;
}