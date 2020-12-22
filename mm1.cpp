#include<iostream>

class sim{
private:
	double simclock = 0;
	double at = 0
	double dt = std::numeric_limits<double>::infinity();

public:
	int get_dt(){
		return dt;
	}
}

int main(){
	sim test;
	std::cout<<"test"<<test.get_dt();
	return 0;
}