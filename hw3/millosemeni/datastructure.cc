// Definition of Datastructure class, hw3 of TIE-20100/TIE-20106
#include "iostream"
#include "datastructure.hh"


Datastructure::Datastructure()
{
}

Datastructure::~Datastructure()
{
}

void Datastructure::add_stop(int stop_id, std::string stop_name)
{
    stop_data_ *stop = new stop_data_;
    // vai stop_data_ *rip = new stop_data_(); ????

    stop->stop_id_ = stop_id;
    stop->stop_name_ = stop_name;

    stops.push_back(stop);

    /*for (stop_data_ *loop : stops){
        std::cout<< loop->stop_name_<< std::endl;
    }
    std::cout<< "end               end"<< std::endl;*/
}

void Datastructure::add_route(int route_id, std::string route_name)
{
    route_data_ *route = new route_data_;

    route->route_id_ = route_id;
    route->route_name_ = route_name;
    route->connections = {};
    route->buses = {};

    routes.push_back(route);

}

void Datastructure::add_stop_to_route(int route_id, int stop_id, unsigned int minutes)
{

    for(route_data_ *iter : routes){
        if (iter->route_id_ == route_id){
            connection * conn = new connection;
            conn->minutes = minutes;
            conn->stop_id = stop_id;
            iter->connections.insert(iter->connections.begin(), conn);
            //std::cout<< iter->connections.size() << std::endl;
            break;
        }
    }

    stop_data_ *ss = new stop_data_;
    ss->stop_id_ = 3;
    ss->stop_name_  = "dd";
    Datastructure::edge *e = new Datastructure::edge;
    ss->edges.push_back(e);

    for(route_data_ *iter : routes){
        struct stop_data_ *next_stop = nullptr;
        for(connection *conn : iter->connections){
            for(struct Datastructure::stop_data_ *stop : stops){
                std::cout << stop->stop_id_ << std::endl;
                std::cout << conn->stop_id << std::endl;
                if(stop->stop_id_ == conn->stop_id){
                    edge* edg = new edge;
                    if (next_stop != nullptr){
                        *edg->ptr = &next_stop;
                    }
                    stop->edges.push_back(edg);
                    next_stop = stop;
                    std::cout<< stop->edges.size() << std::endl;
                }
            }
        }
    }

}

void Datastructure::add_bus(int bus_id, int route_id, unsigned int start_hours, unsigned int start_minutes)
{
    for(route_data_ *iter : routes){
        if (iter->route_id_ == route_id){
            bus* b = new bus;
            b->bus_id = bus_id;
            b->start_hours = start_hours;
            b->start_minutes = start_minutes;
            //std::cout<< b->bus_id << std::endl;
            break;
        }
    }
}

void Datastructure::empty()
{
}

void Datastructure::print_stop(int stop_id)
{
}

void Datastructure::print_buses(int stop_id)
{
}

void Datastructure::print_statistics()
{
}

void Datastructure::print_fastest_journey(int start_stop, int end_stop, unsigned int hours, unsigned int minutes)
{
}
