#include "cards.hh"
#include <iostream>

// TODO: Implement the methods here
Cards::Cards(): top_(nullptr) {
}

void Cards::print_from_top_to_bottom(std::ostream& s){
    if (top_!=nullptr){
       Card_data* item_to_be_printed = top_;
       int running_number = 1;

       while ( item_to_be_printed != nullptr ) {
          s << running_number << ": " << item_to_be_printed->data << std::endl;
          ++running_number;
          item_to_be_printed = item_to_be_printed->next;
   }}
}

void Cards::print_from_bottom_to_top(std::ostream& s){ 
    if (top_ != nullptr) {
    int num_items = 0;
    Card_data* current_item = top_;
    while (current_item != nullptr) {
    ++num_items;
    current_item = current_item->next;
    }

    current_item = top_;
    int t=1;
    for (int i = num_items; i > 0; --i) {
        Card_data* item_to_be_printed = current_item;
        for (int j = 1; j < i; ++j) {
            item_to_be_printed = item_to_be_printed->next;
        }

        s << t << ": " << item_to_be_printed->data << std::endl;
        t+=1;
    }
}
}

bool Cards::bottom_to_top() {
    if (top_ != nullptr && top_->next != nullptr) {
        Card_data* last_item = top_;
        Card_data* second_last_item = nullptr;

        while (last_item->next != nullptr) {
            second_last_item = last_item;
            last_item = last_item->next;
        }

        if (second_last_item != nullptr) {
            second_last_item->next = nullptr;
        }

        last_item->next = top_;
        top_ = last_item;

        return true;
    } else {
        return false;
    }}

bool Cards::top_to_bottom(){
    if (top_ != nullptr && top_->next != nullptr) {
        Card_data* first_item = top_;
        Card_data* second_item = top_->next;
        Card_data* last_item = top_;

        while (last_item->next != nullptr) {
            last_item = last_item->next;
        }

        // Move the first item to the last position
        last_item->next = first_item;

        // Shift all other items to the left by one position
        top_ = second_item;
        last_item->next->next = nullptr;

        return true;
    } else {
        return false;
    }}




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

Card_data* Cards::get_topmost(){
    return top_;
}
