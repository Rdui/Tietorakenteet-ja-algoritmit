// Definition of Datastructure class, hw3 of TIE-20100/TIE-20106

#ifndef DATASTRUCTURE_HH
#define DATASTRUCTURE_HH

#include <string>
#include <vector>
#include <memory>



const std::string NO_ROUTE = "Error: No route!";
const std::string NO_SUCH_STOP = "Error: No such stop!";

class Datastructure
{
public:
    Datastructure();

    ~Datastructure();

    // Add a new bus stop
    void add_stop(int stop_id, std::string stop_name);

    // Add a new bus route
    void add_route(int route_id, std::string route_name);

    // Add a new stop to a route (both the route and the stop have already been added
    // using add_route and add_stop)
    void add_stop_to_route(int route_id, int stop_id, unsigned int minutes);

    // Add a new bus driving a route (the route has already been added using add_route) leaving at a certain
    // time from the terminus (first stop on route)
    void add_bus(int bus_id, int route_id, unsigned int start_hours, unsigned int start_minutes);

    // Empty the datastructure
    void empty();

    // Print information on a bus stop
    void print_stop(int stop_id);

    // Print buses leaving from a stop
    void print_buses(int stop_id);

    // Print the number of stops, bus routes, and buses
    void print_statistics();

    // Print out the fastest journey leaving from stop start_stop to stop end_stop. Journey starts at the given time
    // and the whole journey must be done within the same day (before midnight).
    void print_fastest_journey(int start_stop, int end_stop, unsigned int hours, unsigned int minutes);

    // Copy constructor is forbidden
    Datastructure(const Datastructure&) = delete;
    // Assignment operator is forbidden
    Datastructure& operator=(const Datastructure&) = delete;

private:
    // Add your own implementation here

    int calculate_starting_minutes(int stop);

    struct stop_data_;
    struct gray_nodes;

    struct bus{
        int bus_id;
        int start_hours;
        int start_minutes;
    };

    struct connection{
        int minutes;
        int stop_id;
    };

    struct edge{
        unsigned int minutes;
        int route_number;
        std::shared_ptr<struct stop_data_> ptr = nullptr;
        int weight = -1;
        int route_nro;
    };

    struct stop_data_{
        std::string colour;
        int stop_id_;
        std::string stop_name_;
        std::vector<std::shared_ptr<edge>> edges;
        int weight = INT8_MAX;
        std::shared_ptr<stop_data_> last_stop = nullptr;

        int route_nro;
    };






    struct route_data_{
        int route_id_;
        std::string route_name_;
        std::vector<std::shared_ptr<connection>> connections;
        std::vector<std::shared_ptr<bus>> buses;
    };

    struct route_stop{
        int stop_id;
        int last_stop;
        int time;
        std::string colour;
    };

    std::vector<std::shared_ptr<stop_data_>> stops;
    std::vector<std::shared_ptr<route_data_>> routes;

    std::vector<std::shared_ptr<stop_data_>> gray_nodes;
    std::vector<std::shared_ptr<stop_data_>> dijkstra;
    std::shared_ptr<stop_data_> begin_point;


    bool new_edge;
    std::vector<std::shared_ptr<stop_data_>> shortest_route;
    std::shared_ptr<stop_data_>  last;
    std::shared_ptr<stop_data_> first_stop;

    int waiting_time = 0;
    int waiting_time_hours = 0;

    //calculates the waiting time at a stop
    int calculate_waiting_time(int stop, int route,int hours, int minutes);

};

#endif // DATASTRUCTURE_HH
