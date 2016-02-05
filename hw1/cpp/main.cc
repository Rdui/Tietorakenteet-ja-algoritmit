// Main program for first 

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>

#include "datastructure.hh"

// Command symbols
const char READ = 'R';
const char PRINT = 'P';
const char ALPHA = 'A';
const char EMPTY = 'E';
const char QUIT = 'Q';
const char MINMAX = 'X';
const char ADD = 'D';
//const char BEST = 'B';
//const char WORST = 'W';
const char NAME = 'S';
const char GEN = 'G';
const char EFF = 'F';

// Other constants
const std::string PROMPT = "> ";
//const std::string LOWSCORE = "Lowest score";
const char FSEP = ';';

// Error constants
const std::string E_FNF = "Error: file not found\n";
const std::string E_INT = "Error: bus count and passenger count must be integers";
//const std::string E_PNF = "Person not found";



void readFile(std::string const& filename, Datastructure& ds);
void generate(Datastructure& ds, unsigned int amount);
void efficiencyTest(Datastructure& ds, unsigned int amount);


int main()
{

  Datastructure ds;

  std::string name = "";

  char command = QUIT;

  // Reads command and possible parameters.
  // Executes commands.
  
  do
    {
      std::cout << PROMPT;
      std::cin >> command;

      if(command == READ)
	{
	  std::string filename;
	  std::cin >> filename;
	  std::cout << READ << " " << filename << std::endl;
	  readFile(filename, ds);
	}
      else if (command == PRINT)
	{
	  std::cout << PRINT << std::endl;
	  ds.printLeaderBoard();
	}
      else if (command == ALPHA)
	{
	  std::cout << ALPHA << std::endl;
          ds.printAlphabetically(); 
	}
      else if (command == EMPTY)
	{
	  std::cout << EMPTY << std::endl;
	  ds.empty();
	}
      else if (command == MINMAX)
	{
	  std::string param = "";
	  std::cin >> param;
	  std::cout << MINMAX << " " << param << std::endl;
	  if (param == "best")
	    {
	      ds.bestPlayer();
	    }
	  else if (param == "worst")
	    {
	      ds.worstPlayer();
	    }
	}
      else if (command == NAME)
	{
	  
	  std::string searchTerm = "";
	  char space;
	  std::cin.get(space);
	  std::getline(std::cin, searchTerm);
	  std::cout << NAME << " " << searchTerm << std::endl;
	  // std::cerr << "Etsitaan " << searchTerm << std::endl;

	  ds.findPerson(searchTerm);

	}
      else if (command == GEN)
	{
	  
	  unsigned int amount = 0;
	  std::cin >> amount;
	  std::cout << GEN << " " << amount << std::endl;
	  generate(ds, amount);
	}
      else if (command == EFF)
	{
	  
	  unsigned int amount = 0;
	  std::cin >> amount;
	  std::cout << EFF << " " << amount << std::endl;
	  efficiencyTest(ds, amount);
	}
      else if (command == ADD)
	{
	  std::string input = "";
	  char space;
	  std::cin.get(space);
	  std::getline(std::cin, input );
	  std::string name = "";
	  std::string temp = "";
	  unsigned int brokenNysse = 0;
	  unsigned int sufferingPeople = 0;
	  std::istringstream linestream(input);
	  std::getline(linestream, name, FSEP);
	  std::getline(linestream, temp, FSEP);
	  
	  std::istringstream nyssestream(temp);
	  if (!(nyssestream >> brokenNysse))
	    {
	      std::cout << E_INT << std::endl;
	    }
	  if (!(linestream >> sufferingPeople))
	    {
	      std::cout << E_INT << std::endl;
	    }
	  std::cout << ADD << " " << input << std::endl;
	  //linestream >> name >> brokenNysse >> sufferingPeople;
	  ds.add(name, brokenNysse, sufferingPeople);
	}
    }
  while(command != QUIT);
  
  std::cout << QUIT << std::endl;
 
  return EXIT_SUCCESS;
    

}

void readFile(std::string const& filename, Datastructure& ds)
{
  std::ifstream file(filename.c_str());

  if(!file)
    {
      file.close();
      std::cout << E_FNF;
      return;
    }
  
  std::string line = "";
  std::string name = "";
  unsigned int brokenNysse = 0;
  unsigned int sufferingPeople = 0;
  std::string temp = "";

  while(std::getline(file, line))
    {
      std::istringstream linestream(line);
      std::getline(linestream, name, FSEP);
      std::getline(linestream, temp, FSEP);
      //std::getline(line, sufferingPeople);
      std::istringstream nyssestream(temp);
      if (!(nyssestream >> brokenNysse))
	{
	  std::cout << E_INT << std::endl;
	}
      if (!(linestream >> sufferingPeople))
	{
	  std::cout << E_INT << std::endl;
	}
      //linestream >> name >> brokenNysse >> sufferingPeople;
      ds.add(name, brokenNysse, sufferingPeople);
    }
  
  file.close();
}

void generate(Datastructure& ds, unsigned int amount)
{
  static const char alphas[] = "abcdefghijklmnopqrstuvwxyz";

  for ( unsigned int j = 0; j < amount; j++)
    {
      std::string name(10, ' ');
      for ( size_t i = 0; i < 10; ++i)
	{
	  name[i] = alphas[(unsigned int)std::rand() % (sizeof(alphas) - 1)];
	}

      unsigned int bNysse= (unsigned int)std::rand() % 200000;
      unsigned int sPeople = (unsigned int)std::rand() % 200000;

      ds.add(name, bNysse, sPeople);
    }

}

void efficiencyTest(Datastructure& ds, unsigned int amount)
{
  std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
  start = std::chrono::system_clock::now();

  generate(ds, amount);
  ds.add("Testi", 234508, 3452612);

  ds.printLeaderBoard();
  ds.printAlphabetically();
  ds.worstPlayer();
  ds.bestPlayer();
  ds.findPerson("Testi");
  ds.printLeaderBoard();
  ds.printLeaderBoard();
  ds.printAlphabetically();
  ds.printLeaderBoard();
  ds.printAlphabetically();
  ds.printLeaderBoard();
  ds.printAlphabetically();

  end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed = end-start;
  std::cerr << elapsed.count() << std::endl;
  
}

