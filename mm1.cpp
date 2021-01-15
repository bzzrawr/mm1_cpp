#include <iostream>
#include <limits>
#include <array>
#include <algorithm>
#include <random>
#include <queue>
#include <string>
#include <math.h>

//  random generator using exponential distribution
int seed = 0;
std::default_random_engine generator (seed);
std::exponential_distribution<double>arrivalrate(8); //arrival rate lambda is 8
std::exponential_distribution<double>servicetime(9); //service rate u is 9

class Simulation {
  private:
    // initialize private attribute
    double dt = std::numeric_limits<double>::max(); //set departure time as infinity
    double at = testvalue;                            //set first arrival time 
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
    double st;                                //temporary value for service time
    int etype;                                      //event type 
    std::string sstatus = "idle";                   //server status
    double st2;                   //temporary value for service time
    double plr = 0;                 //packet loss ratio
    double delay = 0;               //delay
    double tmp1;                  //temporary value for calculating delay
    double avgdelay;                //average delay
    int npdelay = 1;                //no of packet delayed
    double totalbusy = 0;           //total busy time
    double prevEvent = 0;           //prev event time
    double totalQ = 0;              //total packet in the queue
    double totalS = 0;              //total packet in the system
    double meanQ = 0;               //average packet in the queue
    double meanS = 0;               //average packet in the system
    double meanQW = 0;              //average waiting in the queue
    double meanSW = 0;              //average waiting in the system
    double rho = 0;

  public:
  //scheduling packet arrival
  double meanarrivalrate;
  double testvalue;
    void scheduling(){
      et = std::min(at,dt);
      // std::cout<<"pid:"<<pid<<std::endl;
      // std::cout<<"Server status: "<<sstatus<<std::endl;
      // std::cout<<"Currently in queue: "<<cqs<<std::endl;
      // std::cout<<"Packet in server:"<<sink.front()<<std::endl;
      // std::cout<<"Packet in queue:"<<Myqueue.front()<<std::endl;
      // std::cout<<"No of packet arrived: "<<n_arrival<<std::endl;
      // std::cout<<"No of packet departed: "<<n_depart<<std::endl;
      // std::cout<<"No of packet dropped: "<<npdrop<<std::endl;
      // std::cout<<"Event time: "<<et<<std::endl;
      // std::cout<<"arrival time: "<<at<<"\tdeparture time: "<<dt<<std::endl;
      // std::cout<<"-----------------------------------------"<<std::endl;
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
            totalbusy += (simclock + prevEvent);
          }

        }
        else{
          npdrop++;
          
        }
        at = simclock + testvalue;
        totalQ += ((simclock - prevEvent)*cqs);
        totalS += (((simclock - prevEvent)*cqs)+(dt - simclock));
        prevEvent = simclock;
      }
    
  //packet departure function
    void pdf(){
      sstatus = "idle";
      sink.pop();
      n_depart++;
      cqs--;
      totalbusy += (simclock - prevEvent);
      totalQ += ((simclock - prevEvent)*cqs);
      totalS += (((simclock - prevEvent)*cqs)+(dt - simclock));
      prevEvent =simclock;

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
      rho = totalbusy/simclock;
      meanQ = totalQ/simclock;
      meanS = totalS/simclock;
      meanSW = meanS/meanarrivalrate;
      meanQW = meanQ/meanarrivalrate;
      std::cout<<"No of packet sent: "<<n_arrival<<std::endl;
      std::cout<<"No of packet depart: "<<n_depart<<std::endl;
      std::cout<<"packet loss rate: "<<plr<<std::endl;
      std::cout<<"Total delay: "<<delay<<std::endl;
      std::cout<<"Packet intensity: "<<rho<<std::endl;
      std::cout<<"Average packet in system: "<<meanS<<std::endl;
      std::cout<<"Average packet in queue: "<<meanQ<<std::endl;
      std::cout<<"Average waiting in system: "<<meanSW<<std::endl;
      std::cout<<"Average waiting in queue: "<<meanQW<<std::endl;
   }

    //function for generating interarrival time
    // double p_gen(){
    //   double nRandom = arrivalrate(generator);
    //   return nRandom;
    // }
    //function for generating service time
    double s_gen(){
      double nRandom2 = servicetime(generator);
      return nRandom2;
    }
    
    double p_gen(double x){
        double z; 
    // a uniform RV (0 < z < 1)
 do 
 {
 z = ((double) std::rand()/RAND_MAX);
 }
 while ((z==0) || (z==1));
 return((-1/x)*std::log(z));// formula for exponential Random Variable
}

    
    //function to set maximum queue size
    void ggwp(){
        std::cout<<"Enter arrival rate: ";
        std::cin>>meanarrivalrate;
        std::cout<<"Enter maximum queue size: ";
        std::cin>>maxque;

    }

};

int main() {
  Simulation test;
  test.ggwp();
  test.testvalue = test.p_gen(8);
  for(int i=0;i<100000;++i){
  test.scheduling();
  test.update_clock();
  test.event();
  }
  test.result();
  

  
}