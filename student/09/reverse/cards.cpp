#include <iostream>
#include <memory>
#include "cards.hh"


Cards::Cards(): top_( nullptr ) {
}


void Cards::add(int id) {
    std::shared_ptr<Card_data> new_card 
            = std::make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

bool Cards::remove(int &id){
    if (top_ == nullptr) {
        return false;
    }
    std::shared_ptr<Card_data> item_to_be_removed = top_;
    id+=1;
    id = item_to_be_removed->data;
    if (top_ == top_->next) {
        top_ = nullptr;
    } else {
        top_ = top_->next;
    }
    return true;
}



void Cards::reverse()
{if (top_ != nullptr && top_->next != nullptr) {
        std::shared_ptr<Card_data> prev_item = nullptr;
        std::shared_ptr<Card_data> curr_item = top_;
        std::shared_ptr<Card_data> next_item = nullptr;

        while (curr_item != nullptr) {
            next_item = curr_item->next;
            curr_item->next = prev_item;
            prev_item = curr_item;
            curr_item = next_item;
        }
        top_ = prev_item;
    }

}


