#include "M_M_1.hpp"
#include "event_list.hpp"

M_M_1::M_M_1(double l, double m){
    mean_in=l;
    mean_out=m;
    e= *new event_list;
}

M_M_1::~M_M_1(){
    //cout<<"System destroyed!"<<endl;
    e.delete_list();
    
}

void M_M_1:: initialization_algorithm(){
    //cout<<"Initialization algorithm says hello!"<<endl;
    clock = 0.0;
    server_status=IDLE;
    number_in_queue=0;
    for(int i=0; i<QUEUE_SIZE;i++){arrival_time_list[i]=0.0;};
    last_event_time=0.0;
    num_of_delays=0;
    total_delay=0.0;
    q=0.0;
    b=0.0;
    planned_arrival_time=clock+random_variables_generator(mean_in);//czas przybycia pierwszego klienta
    e.add_event('a',  planned_arrival_time); //inicjalizujemy listę zdarzeń
    num_of_served_packets=0;
    avg_waiting_time_by_n_clients=0.0;
    avg_clients_in_queue=0.0;
    avg_server_use = 0.0;
    
}

void M_M_1::time_algorithm(){
    //cout<<"Time algorithm says hello!"<<" ";
    next_event_type = e.get_earliest_event_type();  //określ kolejny typ zdarzenia.
    last_event_time=clock;
    clock = e.get_earliest_event_time(); //zwiększ czas zegara.
}

void M_M_1::arrival(){
   // cout<<"<EA> Arrival algorithm says hello!"<<endl;
    planned_arrival_time = clock+random_variables_generator(mean_in);
    e.add_event('a',  planned_arrival_time); //zaplanowanie kolejnego zdarzenia przybycia
    if(server_status==IDLE) //czy serwer jest wolny?
    {
        //cout<<"<EA Arrival> Server: IDLE!"<<endl;
        total_delay+=0.0; //ustaw opóźnienie 0 dla tego klienta i zbierz statystyki
        num_of_delays++;//dodaj 1 do licznika opóźnień klientów
        prev_server_status=server_status;
        server_status=BUSY;//ustaw stan serwera na zajęty
        e.add_event('d', clock+random_variables_generator(mean_out)); //zaplanuj zdarzenie zakończenia obsługi klienta
        if(prev_server_status==BUSY)
        {
            b+=(clock-last_event_time);
        }
    }
    else
    {
        if((number_in_queue+1)>= QUEUE_SIZE)//czy kolejka jest pełna?
        {
            //cout<<"<EA Arrival> Queue is full!"<<endl;
            throw exception();
        }
        else
        {
           //cout<<"<EA Arrival> Queue has "<<QUEUE_SIZE-number_in_queue<<"/"<<QUEUE_SIZE<<" free space!"<<endl;
            arrival_time_list[number_in_queue]=clock; //zachowaj czas przybycia klienta event_time
            q+=((number_in_queue)*(clock-last_event_time));
            b+=(clock-last_event_time);
            number_in_queue+=1; //dodaj 1 do liczby klientów w kolejce
        }
        
    }
}

void M_M_1::completion(){
    ++num_of_served_packets;
   //cout<<"<EA> Completion algorithm says hello!"<<endl;
   if(number_in_queue==0)//czy kolejka jest pusta
   {
       //cout<<"<EA Completion> Queue: empty!"<<endl;
       prev_server_status=server_status;
       server_status=IDLE; //ustaw stan serwera na wolny
      
       if(prev_server_status==BUSY)
       {
           b+=(clock-last_event_time);
       }
   }
   else
   {
       //cout<<"<EA Completion> Queue: not empty!"<<endl;
       //oblicz opóźnienie klienta przechodzącego do obsługi i zbierz statystyki
       total_delay+=(clock-arrival_time_list[0]);
       q+=(number_in_queue*(clock-last_event_time));
       b+=(clock-last_event_time);
       num_of_delays++;//dodaj jeden do licznika opóźnień klientów
       e.add_event('d', clock+random_variables_generator(mean_out));//zaplanuj zdarzenie zakończenia obsługi klienta 
       for(int i=0; i<QUEUE_SIZE;i++)
       {
           if(i!=QUEUE_SIZE-1)
           {
           arrival_time_list[i]=arrival_time_list[i+1];
           }
           else
           {
               arrival_time_list[i]=0.0;
           }
           
       }//przesuń każdego klienta z kolejki o jedno miejsce
       number_in_queue-=1; //odejmij jeden od liczby klientów w kolejce
   }
}

void M_M_1::event_algorithm(){
    //cout<<"Event algorithm says hello!"<<endl;
    e.delete_event(clock);
    switch (next_event_type) {
        case 'a':
            arrival();
            break;
        case 'd':
            completion();
            break;
        default:
            //cout<<"Not defined event!"<<endl;
            break;
    }
}

double M_M_1::random_variables_generator(double mean){
    double RND;
    do {RND = double (rand())/RAND_MAX;}while (RND == 0);
    return -mean * log(RND);
}

void M_M_1::raport_generator(){
    //cout<<"Całkowita liczba opoznien: "<<num_of_delays<<endl;
    //cout<<"Całkowite opoznienie: "<<total_delay<<endl;
    //cout<<"Liczba klientów w czasie symulacji: "<<q<<endl;
    //cout<<"Status serwera w czasie symulacji: "<<b<<endl;
    avg_waiting_time_by_n_clients=total_delay/num_of_delays;
    avg_clients_in_queue=q/clock;
    avg_server_use = b/clock;
    cout<<"Sredni czas oczekiwania przez "<<num_of_delays<<" klientow: "<<avg_waiting_time_by_n_clients<<endl;
    cout<<"Liczba klientow w kolejce oszacowana w czasie ciągłym: "<<avg_clients_in_queue <<endl;
    cout<<"Wykorzystanie serwera obsługi: "<<avg_server_use<<endl;
}



