#include<iostream>

class sim{
private:
	double simclock = 0;
	double at = 0
	double dt = std::numeric_limits<double>::infinity();

public:
	void get_dt(){
		std::cout<<"DT value"<<double dt;
	}
}

int main(){
	sim test;
	test.get_dt();
	return 0;
}