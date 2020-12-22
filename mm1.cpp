#include<iostream>

class sim{
private:
	double simclock = 0;
	double at = 0
	int salary;

public:
	void set_dt(double s){
		salary = s;
	}
	int get_dt(){
		return salary;
	}
}

int main(){
	sim test;
	test.set_dt(100.1);
	std::cout<<"test"<<test.get_dt();
	return 0;
}