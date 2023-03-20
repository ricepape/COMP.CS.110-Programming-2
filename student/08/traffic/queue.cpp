#include "queue.hh"
#include <iostream>
#include <string>

Queue::Queue(unsigned int cycle): first_(nullptr), last_(nullptr), cycle_(cycle){
}

Queue::~Queue() {
   while ( first_ != nullptr ) {
      Vehicle* item_to_be_released = first_;
      first_ = first_->next;

      delete item_to_be_released;
   }
}

void Queue::enqueue(string const& reg){
    if (is_green_==false){
        Vehicle* new_vehicle= new Vehicle{reg, nullptr};
        if ( first_ == nullptr ) {
            first_ = new_vehicle;
            last_ = new_vehicle;
    }   else {
            last_->next = new_vehicle;
            last_ = new_vehicle;
    }
    } else {
            cout <<"GREEN: The vehicle "  << reg << " need not stop to wait"<< endl;
        }
}

void Queue::dequeue_() {
   if (first_!=nullptr) {
   if ( first_ == last_ ) {
      first_ = nullptr;
      last_ =nullptr;
   } else {
      first_ = first_->next;
   }
}
}

void Queue::switch_light(){
    if (!is_green_){
        if(first_!=nullptr){
            is_green_=true;
            int count = cycle_;
            print();
            while (count!=0 && first_!=nullptr){
                dequeue_();
                --count;
        }
            is_green_=false;
        }
        else {
            is_green_=true;
            print();
        }
        }
    else {
        is_green_=false;
        print();
    }
}






void Queue::reset_cycle(unsigned int cycle){
    cycle_=cycle;
}


void Queue::print() const{
    if (is_green_){
        if(first_!=nullptr){
            Vehicle* vehicles_to_be_printed = first_;
            int running_number = 0;
            int cycle=cycle_;
            cout << "GREEN: Vehicle(s) ";
            while (vehicles_to_be_printed !=nullptr && running_number < cycle ) {
               cout << vehicles_to_be_printed ->reg_num <<" ";
               ++running_number;
               vehicles_to_be_printed = vehicles_to_be_printed->next;
            }
            cout << "can go on" << endl;
         } else
        cout <<"GREEN: No vehicles waiting in traffic lights"<< endl;
    } else {
        if(first_!=nullptr){
            Vehicle* vehicles_to_be_printed = first_;
            cout << "RED: Vehicles(s) ";
            while (vehicles_to_be_printed !=nullptr) {
               cout << vehicles_to_be_printed ->reg_num <<" ";
               vehicles_to_be_printed = vehicles_to_be_printed->next;
            }
            cout << "waiting in traffic lights" << endl;
        } else
        cout <<"RED: No vehicles waiting in traffic lights"<< endl;
    }
}

