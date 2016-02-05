#ifndef DATASTRUCTURE_HH
#define DATASTRUCTURE_HH

#include <string>

class Datastructure
{
public:
  Datastructure();
  ~Datastructure();

  // Add value to the datastructure
  void add(std::string name, unsigned int brokenNysse, 
	   unsigned int sufferingPeople);

  // Prints leaderboard in descending order
  void printLeaderBoard();
  
  // Prints player data in alphabetical order.
  void printAlphabetically();

  // Print person with lowest score
  void worstPlayer();
  
  // Print person with highest score
  void bestPlayer();

  void findPerson(std::string searchTerm);
  
  // Empty the datastructure
  void empty();

  // Copy constructor is forbidden
  //Datastructre(const Datastructure&) = delete;
  // Assignment operator is forbidden
  //Datastructure& operator=(const Datastructure&) = delete;
  
private:

};

#endif
