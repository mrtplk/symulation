#pragma once
#include <iostream>
#include <tgmath.h>

#include "event_list.hpp"


const int BUSY=1;
const int IDLE=0;
const int QUEUE_SIZE = 1000;

class M_M_1 {
public:
    //constructor 1
    M_M_1(double l, double m);
    //constructor 2
    //M_M_1()
    //destructor
    ~M_M_1();
    //
    int
    server_status,
    prev_server_status,
    number_in_queue,
    num_of_delays,
    num_of_served_packets;
    double
    mean_in,
    mean_out,
    clock,
    last_event_time,
    event_time,
    planned_arrival_time,
    total_delay,
    q,
    b,
    arrival_time_list [QUEUE_SIZE],
    avg_waiting_time_by_n_clients,
    avg_clients_in_queue,
    avg_server_use;
    event_list e;
    char
    next_event_type;
    
    //new system parameters
    double
    capacity_in, //[bit/s]
    capacity_out; //[bit/s]
    int
    buffer_size;
    char system_type;
    
    //methods
    void initialization_algorithm();
    void time_algorithm();
    void arrival();
    void completion();
    void event_algorithm();
    double random_variables_generator(double mean);
    void raport_generator();

private:
    
};
