#ifndef SPACE_H
#define SPACE_H


class Space{
    public:

    /**
	* @brief constructing a new Space object, default is an empty space
    */
    Space(){type = 0;}

    /**
	* @brief an asscessor function of Space to return the type of space
    * p1k = 1, p2k = 2, p1c = 3, p2c = 4, empty = 0
    */
    int get_type()const{return type;}

    /**
	* @brief a mutator function to change the type of space
    *
    * @param t - an integer
    */
    void set_type(int t){type = t;}

    private:
        int type; 

};

#endif