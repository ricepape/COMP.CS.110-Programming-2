#include "player.hh"
#include <iostream>

Player::Player(const std::string name): name_(name)
{
}

std::string Player::get_name(){
    return name_;
}

int Player::get_points(){
    return points_;
}

bool Player::has_won(){
    if (points_!=50){
        return false;
    }
    else return true;
}

void Player::add_points(unsigned long int pts){
    points_+=pts;
    if (points_>50){
        points_=25;
        std::cout<<name_<<" gets penalty points!"<<std::endl;
    }
}
