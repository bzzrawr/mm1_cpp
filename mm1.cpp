#include <iostream>
#include <limits>
#include <array>
#include <algorithm>
#include <random>
#include <queue>

//  random generator using exponential distribution
std::default_random_engine generator;
std::exponential_distribution<double>arrivalrate(6.0);
std::exponential_distribution<double>servicetime(3.0);

class Simulation {
  private:
    // Private attribute
    double dt = std::numeric_limits<double>::max();
    double at = p_gen();
    double simclock = 0;
    double et = 0.0;
    std::queue<double> sink;
    int n_arrival = 0;
    int n_depart = 0;
    int npdrop = 0;
    int pid = 0;
    int maxque;
    int cqs = 0;
    std::queue<double> Myqueue;
    double tmp1 = s_gen();
    int etype;

  public:
  	void scheduling(){
  		et = std::min(at,dt);
  		if(cqs < maxque){
  			pid++;
  			Myqueue.push(at);
  			if(sink.size()==0){
  			    sink.push(Myqueue.front());
  			    Myqueue.pop();
  			    etype = 0;
  			}
  			else{
  			    cqs++;
  			    at = simclock + p_gen();
  			}
  		}
  		else{
  			npdrop++;
  			at = simclock + p_gen();
  		}
  		std::cout<<"pid:"<<pid<<std::endl;
  		std::cout<<"Currently in queue:"<<Myqueue.front()<<std::endl;
  		std::cout<<"Currently in sink:"<<sink.front()<<std::endl;
  		std::cout<<"arrival time"<<at<<std::endl;
  	}
  	void event(){
  	    if(etype == 0){
  	        tmp1 = s_gen();
  	        std::cout<<">>>>Service time>>>>"<<tmp1<<std::endl;
  	        dt = simclock + tmp1;
  	    }
  	}

  	void update_clock(){
  		simclock = et;
  	}
  	void result(){
  		std::cout<<"departure time:"<<dt<<std::endl;
  	}

  	double p_gen(){
  		double nRandom = arrivalrate(generator);
  		return nRandom;
  	}
  	double s_gen(){
  		double nRandom2 = servicetime(generator);
  		return nRandom2;
  	}
  	double get_et(){
  		return et;
  	}
  	
  	void ggwp(){
  	    std::cout<<"Enter maximum queue size: ";
  	    std::cin>>maxque;
  	}

};

int main() {
	Simulation test;
	test.ggwp();
	for(int i=0;i<10;++i){
	test.scheduling();
	test.update_clock();
	test.event();
	test.result();

	}
	

  
}