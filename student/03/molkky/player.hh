#ifndef PLAYER_HH
#define PLAYER_HH

# include <string>

class Player
{
public:
    //Constructor
    Player(const std::string name);
    void add_points(unsigned long int pts);
    bool has_won();
    const std::string& get_name();
    int get_points();

private:
    std::string name_;
    int points_=0;
    bool has_won_ = false ;


};



#endif // PLAYER_HH
