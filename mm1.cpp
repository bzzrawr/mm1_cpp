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
    double st;                          //temporary value for service time
    int etype;                                      //event type 
    std::string sstatus = "idle";                   //server status
    double tmp2;

  public:
  //scheduling packet arrival
  	void scheduling(){
  		et = std::min(at,dt);
  		st = s_gen();
  		std::cout<<"pid:"<<pid<<std::endl;
  		std::cout<<"Server status: "<<sstatus<<std::endl;
  		std::cout<<"Currently in queue: "<<cqs<<std::endl;
  	    std::cout<<"Packet in server:"<<sink.front()<<std::endl;
  		std::cout<<"Packet in queue:"<<Myqueue.front()<<std::endl;
  		std::cout<<"No of packet arrived: "<<n_arrival<<std::endl;
  		std::cout<<"No of packet departed: "<<n_depart<<std::endl;
  		std::cout<<"No of packet dropped: "<<npdrop<<std::endl;
  		std::cout<<"Event time: "<<et<<std::endl;
  		std::cout<<"arrival time: "<<at<<"\tdeparture time: "<<dt<<std::endl;
  	    std::cout<<"-----------------------------------------"<<std::endl;
  	}
  	void fifo(){
  	    if(cqs<maxque){
  	        pid++;
  	        Myqueue.push(at);                             //push arrival time to Q
  	        if(sink.empty()){
  	            sink.push(Myqueue.front());               //1st el Q push to sink
  	            Myqueue.pop();                            //pop 1st element from Q
  	            if(cqs<=1){
  	                std::cout<<">>>>Service time>>>>"<<st<<std::endl;
  	                dt = simclock + st;
  	            }
  	        }
  	        else{
  	            cqs++;                                    //current Q size increase by 1
  	        }
  	    }
  	    else{
  	        npdrop++;                                     //when reach maxque drop packet
  	    }
  	    
  	}
  	
  //update simulation clock
  	void update_clock(){
  		simclock = et;
  	}
  	
  //determine the eventype
  	void event(){
  	    if(at<=dt){
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
  	    at = simclock + p_gen();
  	}
  	
  //packet departure function
  	void pdf(){
      n_depart++;
      sstatus = "idle";
      sink.pop();
      cqs--;
      if(cqs>=0){
          sink.push(Myqueue.front());
          Myqueue.pop();
          std::cout<<">>>>Service time<<<<"<<st<<std::endl;
          dt = simclock + st;
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
	test.fifo();
	test.event();
// 	test.result();

	}
	

  
}