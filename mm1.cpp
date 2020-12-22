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
// #include <iostream>
// #include <limits>
// // using namespace std;

// class Simulation {
//   private:
//     // Private attribute
//     double dt = std::numeric_limits<double>::max();
//     double at = 0;
//   public:
//     // Setter
//     void setDt(double s) {
//       dt = s;
//     }
//     // Getter
//     int getDt() {
//       return dt;
//     }
//     int getAt(){
//     	return at;
//     }
// };

// int main() {
//   Simulation myObj;
//   if(myObj.getDt()>myObj.getAt()){
//   	myObj.setDt(50000);
//   	std::cout << myObj.getDt();
//   }
  
  
// }

#include <iostream>
#include <limits>

double inf = std::numeric_limits<double>::infinity();

int get(){
    return inf;
}
int main()
{
    double max = std::numeric_limits<double>::max();
    
    
 
    if(get() > max){
        std::cout << get() << " is greater than " << max << '\n';
        }
}