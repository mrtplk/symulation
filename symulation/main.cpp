#include <iostream>
#include "M_M_1.hpp"
#include "event_list.hpp"
#include "calculator.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    double lambda, mi;
    cout<<"Enter lambda"<<endl;
    cin>>lambda;
    cout<<"Enter mi"<<endl;
    cin>>mi;
    M_M_1 system(1.0/lambda, 1.0/mi);
    calculator(lambda, mi);
    try
    {
        system.initialization_algorithm();
       while(system.num_of_served_packets<1000000)
        {
            system.time_algorithm();
            system.event_algorithm();
        }
        system.raport_generator();
        
     }
    catch(const std::exception&)
    {
        return EXIT_FAILURE;
    }
    
    
}
