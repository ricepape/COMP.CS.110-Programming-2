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
    std::string get_name();
    int get_points();

private:
    std::string name_;
    int points_;


};



#endif // PLAYER_HH
