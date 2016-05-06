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
            std::cout << minutes << std::endl;
            conn->minutes = minutes;
            conn->stop_id = stop_id;
            iter->connections.insert(iter->connections.begin(), conn);
            //
            //std::cout << routes.size() << std::endl;
            //std::cout<< iter->connections.size() << std::endl;
            break;
        }
    }

    for (route_data_ *route : routes){
        stop_data_ *next_stop = nullptr;
        for(connection *conn: route->connections){
            for(stop_data_ *stop : stops){
                if(conn->stop_id == stop->stop_id_){
                    //std::cout<< "match" << std::endl;
                    //std::cout<< conn->stop_id << std::endl;
                    //std::cout<< stop->stop_id_ << std::endl;
                    new_edge = true;

                    if(next_stop != nullptr){
                        for(edge *edg : stop->edges){
                            if (edg->route_number == next_stop->stop_id_){
                                new_edge = false;
                                break;
                            }
                        }
                    }

                    if(next_stop != nullptr && new_edge == true){
                        edge *e = new edge;
                        e->route_number = next_stop->stop_id_;
                        e->ptr = next_stop;
                        e->minutes = conn->minutes;
                        e->weight = (last_connection->minutes) - (conn->minutes);
                        e->route_nro = route_id;
                        /*std::cout<< stop->stop_id_ << std::endl;
                        std::cout<< e->route_number << std::endl;
                        std::cout<< e->weight << std::endl;*/
                        stop->edges.push_back(e);
                        /*std::cout<< stop->stop_name_ << std::endl;
                        std::cout<< stop->edges.size() << std::endl;
                        std::cout<< stop->stop_id_ << std::endl;
                        std::cout<< " " <<std::endl;*/

                        /*for(edge *eg: stop->edges){
                            std::cout << eg->route_number << std::endl;
                        }*/
                    }

                    next_stop = stop;

                }
            }
        last_connection = conn;
        }

    }



    /*for(route_data_ *iter : routes){
        struct stop_data_ *next_stop = nullptr;
        for(connection *conn : iter->connections){
            for(struct Datastructure::stop_data_ *stop : stops){
                std::cout << stop->stop_id_ << std::endl;
                std::cout << conn->stop_id << std::endl;
                if(stop->stop_id_ == conn->stop_id){
                    std::cout << "match" << std::endl;
                    edge* edg = new edge;
                    if (next_stop != nullptr){
                        edg->ptr = next_stop;

                    }
                    stop->edges.push_back(edg);
                    next_stop = stop;
                    std::cout<< stop->edges.size() << std::endl;
                }
            }
        }
    }*/

}

void Datastructure::add_bus(int bus_id, int route_id, unsigned int start_hours, unsigned int start_minutes)
{
    std::cout<< bus_id << std::endl;
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
    bool found_stop = false;
    for (stop_data_ *stop : stops){
        if(stop->stop_id_ == stop_id){
            found_stop = true;
            std::cout<< stop->stop_name_ << std::endl;
            break;
        }
    }
    if (found_stop == false){
        std::cout<< "No such stop!"<< std::endl;
    }
}

void Datastructure::print_buses(int stop_id)
{
    for (route_data_ *route : routes){
        for(connection *conn: route->connections){
            if(conn->stop_id == stop_id){
                std::cout<< route->route_name_ << std::endl;
                break;
            }
        }
    }
}

void Datastructure::print_statistics()
{
}

void Datastructure::print_fastest_journey(int start_stop, int end_stop, unsigned int hours, unsigned int minutes)
{




    for (stop_data_ *stop: stops){
        stop->colour = "white";
        stop->last_stop = nullptr;
    }
    for (stop_data_ *stop: stops){
        if(stop->stop_id_ == start_stop){
            stop->weight = 0;
            begin_point = stop;
            stop->colour = "gray";
            gray_nodes.push_back(stop);
            break;
        }
    }

    bool found_route = false;

    while (gray_nodes.size() != 0) {
        stop_data_ *iter = gray_nodes[0];
        for(edge *e : iter->edges){
            if(e->ptr->colour == "white"){
                e->ptr->colour = "gray";
                gray_nodes.push_back(e->ptr);
            }
            if (e->ptr->weight > e->weight + iter->weight){
                e->ptr->weight = e->weight + iter->weight;
                e->ptr->last_stop = iter;
                e->ptr->route_nro = e->route_nro;

            }
        }
        iter->colour = "black";
        last = iter;
        if (iter->stop_id_ == end_stop){
            found_route = true;
            while(last != nullptr){
                //std::cout<< last->stop_id_ << std::endl;
                shortest_route.insert(shortest_route.begin(), last);
                last = last->last_stop;

            }
            int counter = 0;
            for(stop_data_ *stop : shortest_route){
                counter += 1;
                if (stop->last_stop != nullptr){
                    stop->last_stop->route_nro = stop->route_nro;
                    first_stop = stop->last_stop;
                    //std::cout<< first_stop->stop_id_ << std::endl;
                    break;
                }
            }
            //int starting_point_minutes = calculate_starting_minutes(first_stop->stop_id_);


            int route_number = -10;
            for(stop_data_ *stop : shortest_route){
                //std::cout <<stop->route_nro << std::endl;
                //std::cout <<route_number << std::endl;
                if (route_number != stop->route_nro){
                    //starting_point_minutes = calculate_starting_minutes(stop->route_nro);
                    for(route_data_ *route : routes){
                        if (route->route_id_ == stop->route_nro){
                            std::cout<< route->route_name_<< std::endl;
                            break;
                        }
                    }
                }
                route_number = stop->route_nro;
                std::cout <<"  ";
                std::cout <<hours<< ":"<<minutes+stop->weight;
                std::cout <<"  ";
                std::cout <<stop->stop_id_;
                std::cout << ",  ";
                std::cout << stop->stop_name_<< std::endl;
            }
        }
        gray_nodes.erase(gray_nodes.begin());
    }
    if(found_route == false){
        std::cout <<"No route!"<< std::endl;
    }
}

/*int Datastructure::calculate_starting_minutes(int stop){
    for(route_data_ *route : routes){
        if (stop == route->route_id_){
            for(connection *c : route->connections){
                if(c->stop_id == stop){
                    //std::cout << c->minutes << std::endl;
                    return c->minutes;
                }
            }
        }
    }
}*/
