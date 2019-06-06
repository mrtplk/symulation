#include "calculator.hpp"

calculator::calculator(double lambda, double mi){
    ro = lambda/mi;
    Lq = pow(ro,2)/(1-ro);
    Wq = Lq/lambda;
    cout<<"------------T-E-O-R-E-T-Y-C-Z-N-E--O-B-L-I-C-Z-E-N-I-A-------------"<<endl;
    cout<<"Teoretyczny czas oczekiwania przez n klientów w kolejce: "<<Wq<<endl;
    cout<<"Teoretyczna liczba klientow w kolejce oszacowana w czasie ciaglym: "<<Lq<<endl;
    cout<<"Teoretyczne wykorzystanie serwera obsługi: "<<ro<<endl;
    cout<<"--------------------------W-Y-N-I-K-I------------------------------"<<endl;
}

calculator::~calculator(){
    
}
