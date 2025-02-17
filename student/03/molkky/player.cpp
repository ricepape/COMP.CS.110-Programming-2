#include "player.hh"
#include <iostream>

Player::Player(const std::string name): name_(name)
{
}

const std::string& Player::get_name(){
    return name_;
}

int Player::get_points(){
    return points_;
}

bool Player::has_won()
{
    return has_won_;
    }


void Player::add_points(unsigned long int pts){
    if (points_+pts>50){
        points_=25;
        std::cout << name_ <<" gets penalty points!" <<std::endl;
        has_won_=false;
    } else if(points_+pts==50){
        points_=50;
        has_won_=true;
    }else{
        points_+=pts;

    }

}
