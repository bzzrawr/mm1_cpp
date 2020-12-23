#include <iostream>
#include <limits>
#include <array>
#include <algorithm>
#include <random>
#include <queue>
#include <string>

//  random generator using exponential distribution
std::default_random_engine generator;
std::exponential_distribution<double>arrivalrate(6.0); //arrival rate lambda is 6
std::exponential_distribution<double>servicetime(3.0); //service rate u is 3

class Simulation {
  private:
    // initialize private attribute
    double dt = std::numeric_limits<double>::max(); //set departure time as infinity
    double at = p_gen();                            //set first arrival time 
    double simclock = 0;                            //set simulation clock
    double et = 0;                                  //set event time
    std::queue<double> sink;                        //array for server
    int n_arrival = 0;                              //no of packet arrive
    int n_depart = 0;                               //no of packet depart
    int npdrop = 0;                                 //no of packet drop
    int pid = 0;                                    //packet id
    int maxque;                                     //maximum queue size
    int cqs = 0;                                    //current queue size
    std::queue<double> Myqueue;                     //array for packet queue
    double tmp1 = s_gen();                          //temporary value for service time
    int etype;                                      //event type 
    std::string sstatus = "idle";                   //server status
    double tmp2;

  public:
  //scheduling packet arrival
  	void scheduling(){
  		et = std::min(at,dt);
  		std::cout<<"pid:"<<pid<<std::endl;
  		std::cout<<"Server status: "<<sstatus<<std::endl;
  	    std::cout<<"Packet in server:"<<sink.front()<<std::endl;
  		std::cout<<"Packet in queue:"<<Myqueue.front()<<std::endl;
  		std::cout<<"Event time: "<<et<<std::endl;
  		std::cout<<"arrival time: "<<at<<"\tdeparture time: "<<dt<<std::endl;
  	    std::cout<<"-----------------------------------------"<<std::endl;
  	    
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
  	}
  	
  //update simulation clock
  	void update_clock(){
  		simclock = et;
  	}
  	
  //determine the eventype
  	void event(){
  	    if(etype == 0){
  	        pgf();
  	    }
  	    else{
  	        pdf();
  	    }
  	}
  	
  //packet generation function
  	void pgf(){
  	    n_arrival++;
  	    sstatus = "busy";
  	    tmp1 = s_gen();
  	    std::cout<<">>>>Service time>>>>"<<tmp1<<std::endl;
  	    dt = simclock + tmp1;
  	    at = simclock + p_gen();
  	    etype = 1;
  	}
  	
  //packet departure function
  void pdf(){
      cqs--;
      sstatus = "idle";
      n_depart++;
      sink.pop();
      if(cqs>=0){
          sink.push(Myqueue.front());
          Myqueue.pop();
          tmp2 = s_gen();
          std::cout<<">>>>Service time<<<<"<<tmp2<<std::endl;
          dt = simclock + tmp2;
          
      }
      else{
          cqs++;
          dt = std::numeric_limits<double>::max();
      }
      
  }

//   	void result(){
  	    	
//   	}

    //function for generating interarrival time
  	double p_gen(){
  		double nRandom = arrivalrate(generator);
  		return nRandom;
  	}
  	//function for generating service time
  	double s_gen(){
  		double nRandom2 = servicetime(generator);
  		return nRandom2;
  	}
  	
  	//function to set maximum queue size
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
// 	test.result();

	}
	

  
}