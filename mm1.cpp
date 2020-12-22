#include<iostream>

class sim{
private:
	double simclock = 0;
	double at = 0
	double dt;

public:
	void set_dt(double s){
		dt = s;
	}
	int get_dt(){
		return dt;
	}
}

int main(){
	sim test;
	test.set_dt(100.1);
	std::cout<<"test"<<test.get_dt();
	return 0;
}