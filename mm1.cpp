#include <iostream>
#include <limits>
#include <array>
#include <algorithm>
#include <random>
#include <queue>
#include <string>

//  random generator using exponential distribution
int seed =0;
std::default_random_engine generator (seed);
std::exponential_distribution<double>arrivalrate(8); //arrival rate lambda is 8
std::exponential_distribution<double>servicetime(9); //service rate u is 9

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
    double st;                          			//temporary value for service time
    int etype;                                      //event type 
    std::string sstatus = "idle";                   //server status
    double st2;										//temporary value for service time
    double plr = 0;									//packet loss ratio
    double delay = 0;								//delay
    double tmp1;									//temporary value for calculating delay
    double avgdelay;								//average delay
    int npdelay = 1;								//no of packet delayed

  public:
  //scheduling packet arrival
    void scheduling(){
      et = std::min(at,dt);
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
        if(cqs<maxque){
          Myqueue.push(at);
          at = simclock + p_gen();
          
          if(sink.empty()){
            sink.push(Myqueue.front());
            Myqueue.pop();
            if(cqs<=1){
              st = s_gen();
              dt = simclock + st;
            }

          }
          else{
            cqs++;
          }

        }
        else{
          npdrop++;
          at = simclock + p_gen();
        }
      }
    
  //packet departure function
    void pdf(){
      sstatus = "idle";
      sink.pop();
      n_depart++;
      cqs--;
      if(cqs>=0){
      	npdelay++;
        sink.push(Myqueue.front());
        tmp1 = Myqueue.front();
        delay = delay + (dt - tmp1);
        Myqueue.pop();
        st2 = s_gen();
        dt = simclock + st2;
      }
      else{
        cqs++;
        dt = std::numeric_limits<double>::max();
      }
    }

   void result(){
   		plr = (double)npdrop / (double)n_arrival;
   		avgdelay = delay/(double)npdelay;
   		std::cout<<"packet loss rate: "<<plr<<std::endl;
   		std::cout<<"Total delay: "<<delay<<std::endl;
   		std::cout<<"Average delay: "<<avgdelay<<std::endl;
   }

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
  }
  test.result();
  

  
}