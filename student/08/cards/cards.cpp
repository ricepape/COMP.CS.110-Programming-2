#include "cards.hh"
#include <iostream>

// TODO: Implement the methods here
Cards::Cards(): top_(nullptr) {
}

void Cards::print_from_top_to_bottom(std::ostream& s){
    int running_number = 1;
        for (Card_data* item_to_be_printed = top_; item_to_be_printed != nullptr;
             item_to_be_printed= item_to_be_printed->next) {
            s << running_number << ". " << item_to_be_printed->data << std::endl;
            ++running_number;
        }
    }


void Cards::print_from_bottom_to_top(std::ostream& s){
    int running_number = 1;

        for (Card_data* item_to_be_printed = top_; item_to_be_printed != nullptr;
             item_to_be_printed= item_to_be_printed->next) {
            s << running_number << ". " << item_to_be_printed->data << std::endl;
            ++running_number;
        }

    }

bool Cards::bottom_to_top(){
   return true;
}

bool Cards::top_to_bottom(){
   return true;
}

void Cards::add(int id){
    if (top_ == nullptr) {
            top_ = new Card_data{id, nullptr};
        } else {
            Card_data* new_card = new Card_data{id, top_};
            top_ = new_card;
        }
    }


Cards::~Cards() {
   while ( top_ != nullptr ) {
      Card_data* item_to_be_released = top_;
      top_ = top_->next;

      delete item_to_be_released;
   }
}

bool Cards::remove(int& id){
    if (top_ == nullptr) {
        return false;
    }

    Card_data* item_to_be_removed = top_;

    id+=1;

    id = item_to_be_removed->data;

    if (top_ == top_->next) {
        top_ = nullptr;
    } else {
        top_ = top_->next;
    }

    delete item_to_be_removed;

    return true;
}
