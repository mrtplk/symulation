#pragma once
#include <stdio.h>
#include <iostream>

using namespace std;

struct event{
public:
    char type;
    double time;
    event *next;
    event();
    ~event();
};

struct event_list{
public:
    event *first;
    void add_event(char type, double time);
    void delete_event(double time);
    void display_event_list();
    void delete_list();
    char get_earliest_event_type();
    double get_earliest_event_time();
    double get_earliest_d_event_time();
    event_list();
    ~event_list();
};



