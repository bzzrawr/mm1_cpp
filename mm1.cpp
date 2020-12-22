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
using namespace std;

class Employee {
  private:
    // Private attribute
    int salary;

  public:
    // Setter
    void setSalary(int s) {
      salary = s;
    }
    // Getter
    int getSalary() {
      return salary;
    }
};

int main() {
  Employee myObj;
  myObj.setSalary(50000);
  cout << myObj.getSalary();
  return 0;
}