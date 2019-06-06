#include "event_list.hpp"

event::event(){
    next=0;
}
event::~event(){
  // cout<<"event destroyed!"<<endl;
}

event_list::event_list(){
    first=0;
}
event_list::~event_list(){
   
}

void event_list::add_event(char t, double at){
    event *e = new event;
    e->type=t;
    e->time=at;
    
    if(first==0)
    {
        first=e;
    }
    else
    {
        event *temp = first;
        while(temp->next)
        {
            temp = temp->next;
        }
        temp->next = e;
        e->next=0;
    }
}

void event_list::delete_event(double time){
    event *temp = first;
    event *prev_temp = temp;
    int i=0;
    while(temp)
    {
        if(temp->time == time)
        {
            if(i==0) //jesli znajdujemy sie na poczatku listy
            {
                first = temp->next;
                delete temp; //~event()
                temp=NULL;
                break;
            }
            else
            {
                if(prev_temp->next->next==NULL) {/*zmieniam!*/delete (prev_temp->next) /*zmieniam!*/; prev_temp->next= NULL; } //jezeli wskaznik wskazuje na przedostatni element listy gubimy wskaznik na ostatni element
                else
                {
                    delete (prev_temp->next);
                    prev_temp->next = prev_temp->next->next;
                }
                break;
            }
        }
        prev_temp=temp;
        temp=temp->next;
        i++;
    }
}

void event_list::display_event_list(){
    event *temp = first;
    while(temp){
        cout<<temp->type<<" "<<temp->time<<endl;
        temp = temp->next;
    }
}

char event_list::get_earliest_event_type(){
    char type='n';
    double t = std::numeric_limits<double>::infinity();
    event *temp = first;
    while(temp){
        if(temp->time<t)
        {
            type = temp->type;
            t = temp->time;
        }
        temp = temp->next;
    }
    return type;
}

double event_list:: get_earliest_event_time(){
    double t = std::numeric_limits<double>::infinity();
    event *temp = first;
    while(temp){
        if(temp->time<t)
        {
            t = temp->time;
        }
        temp = temp->next;
    }
    return t;
}

double event_list:: get_earliest_d_event_time(){
    double t = std::numeric_limits<double>::infinity();
    event *temp = first;
    while(temp){
        if(temp->type=='d' && temp->time<t)
        {
            t = temp->time;
        }
        temp = temp->next;
    }
    
    return t;
}

//zrobić usuwanie całej listy i zastosować to w destruktorze!!!!
void event_list:: delete_list() {
    event* temp = first;
    event* another_one;
    while(temp!=NULL)
    {
        another_one = temp->next;
        delete temp; //~event();
        //first=NULL;
        temp = another_one;
        
    }
   // cout<<"queue is destroyed!"<<endl;
    }



