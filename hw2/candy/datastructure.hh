// Definition of Datastructure class for UDS/Tiraka homework 2 -


#ifndef DATASTRUCTURE_HH
#define DATASTRUCTURE_HH

#include <string>
#include <vector>
using std::string;

const std::string NOT_AVAILABLE = "Product not in warehouse.";
const std::string NOT_ENOUGH_CANDY = "Not enough candy available.";

class Datastructure
{
    public:

    Datastructure();

    ~Datastructure();

    // Adds candies to the datastructure (command "A")
    void add(const std::string& ID, const std::string& location,
            unsigned int amount, const std::string& name);
          
    // Removes candies from the datastructure (command "D")
    void substract(const std::string& ID, unsigned int amount);

    // Finds candy and prints its status (command "F")
    void find(const std::string& ID) const;

    // Returns how many different types of candy the datastructure contains (command "C")
    size_t count() const;

    // Empties the datastructure (command "E")
    void empty();


    
    // Copy constructor is forbidden (not important for this assignment)
    Datastructure(const Datastructure&) = delete;
    // Assignment operator is forbidden (not important for this assignment)
    Datastructure& operator=(const Datastructure&) = delete;
    
private:
  struct candy{
      std::string ID;
      std::string loc;
      unsigned int amnt;
      std::string name;
      struct candy *next = nullptr;
  };
    // Add your own implementation here
    static const int varasto_size = 1000;
    candy* varasto_[varasto_size];
    size_t counter;
 
};

#endif
