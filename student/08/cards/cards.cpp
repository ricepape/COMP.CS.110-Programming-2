#include "cards.hh"
#include <iostream>
#include <stack>

// TODO: Implement the methods here
Cards::Cards(): top_(nullptr) {
}

void Cards::print_from_top_to_bottom(std::ostream& s){
    if (top_!=nullptr){
       Card_data* item_to_be_printed = top_;
       int running_number = 1;

       while ( item_to_be_printed != nullptr ) {
          s << running_number << ". " << item_to_be_printed->data << std::endl;
          ++running_number;
          item_to_be_printed = item_to_be_printed->next;
   }}
}

void Cards::print_from_bottom_to_top(std::ostream& s){
    if (top_ != nullptr){
            std::stack<Card_data*> card_stack;
            Card_data* item_to_be_printed = top_;

            while (item_to_be_printed != nullptr) {
                card_stack.push(item_to_be_printed);
                item_to_be_printed = item_to_be_printed->next;
            }

            int running_number = 1;
            while (!card_stack.empty()) {
                item_to_be_printed = card_stack.top();
                s << running_number << ". " << item_to_be_printed->data << std::endl;
                ++running_number;
                card_stack.pop();
            }
        }
    }

bool Cards::bottom_to_top(){
    if (top_ != nullptr){
        std::stack<Card_data*> card_stack;
        Card_data* item_to_be_printed = top_;
        card_stack.push(item_to_be_printed);

        while (item_to_be_printed->next != nullptr) {
            item_to_be_printed = item_to_be_printed->next;
            card_stack.push(item_to_be_printed);
        }


        item_to_be_printed = card_stack.top();
        card_stack.pop();


        while (!card_stack.empty()) {
            Card_data* item = card_stack.top();
            card_stack.pop();
            item->next = item_to_be_printed->next;
            item_to_be_printed->next = item;
            top_=item_to_be_printed;
        }
        return true;

    }

   else return false;
}

bool Cards::top_to_bottom(){
    if (top_ != nullptr) {
        std::stack<Card_data*> card_stack;
        Card_data* item_to_be_printed = top_;

        while (item_to_be_printed != nullptr) {
            card_stack.push(item_to_be_printed);
            item_to_be_printed = item_to_be_printed->next;
        }

        item_to_be_printed = card_stack.top();
        card_stack.pop();
        top_ = item_to_be_printed;

        while (!card_stack.empty()) {
            Card_data* item = card_stack.top();
            card_stack.pop();
            item_to_be_printed->next = item;
            item_to_be_printed = item;
        }

        item_to_be_printed->next = nullptr;
        return true;
    } else {
        return false;
    }

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

Card_data* Cards::get_topmost(){
    return top_;
}
