// Definition of Datastructure class, hw3 of TIE-20100/TIE-20106
#include "iostream"
#include "datastructure.hh"


Datastructure::Datastructure()
{
}

Datastructure::~Datastructure()
{
    empty();
}
// stops will act as nodes in the graph
void Datastructure::add_stop(int stop_id, std::string stop_name)
{
    std::shared_ptr<stop_data_> stop(new stop_data_);
    stop->stop_id_ = stop_id;
    stop->stop_name_ = stop_name;

    stops.push_back(stop);
}

void Datastructure::add_route(int route_id, std::string route_name)
{
    std::shared_ptr<route_data_> route(new route_data_);

    route->route_id_ = route_id;
    route->route_name_ = route_name;
    route->connections = {};
    route->buses = {};

    routes.push_back(route);

}

void Datastructure::add_stop_to_route(int route_id, int stop_id, unsigned int minutes)

{
    std::shared_ptr<connection> last_connection (new connection);





    for(std::shared_ptr<route_data_> iter : routes){
        if (iter->route_id_ == route_id){
            std::shared_ptr<connection> conn (new connection);
            //std::cout << minutes << std::endl;
            conn->minutes = minutes;
            conn->stop_id = stop_id;
            iter->connections.insert(iter->connections.begin(), conn);
            break;
        }
    }

    // This for loop creates the edges for nodes
    for (std::shared_ptr<route_data_> route : routes){
        std::shared_ptr<stop_data_> next_stop(new stop_data_);
        for(std::shared_ptr<connection> conn: route->connections){
            for(std::shared_ptr<stop_data_> stop : stops){
                if(conn->stop_id == stop->stop_id_){
                    new_edge = true;

                    if(next_stop != nullptr){
                        for(std::shared_ptr<edge> edg : stop->edges){
                            if (edg->route_number == next_stop->stop_id_){
                                new_edge = false;
                                break;
                            }
                        }
                    }

                    if(next_stop != nullptr && new_edge == true){
                        std::shared_ptr<edge> e (new edge);
                        e->route_number = next_stop->stop_id_;
                        e->ptr = next_stop;
                        e->minutes = conn->minutes;
                        e->weight = (last_connection->minutes) - (conn->minutes);
                        e->route_nro = route_id;
                        stop->edges.push_back(e);
                    }

                    next_stop = stop;

                }
            }
        last_connection = conn;
        }

    }
}

void Datastructure::add_bus(int bus_id, int route_id, unsigned int start_hours, unsigned int start_minutes)
{
    for(std::shared_ptr<route_data_> iter : routes){
        if (iter->route_id_ == route_id){
            std::shared_ptr<bus> b (new bus);
            b->bus_id = bus_id;
            b->start_hours = start_hours;
            b->start_minutes = start_minutes;
            iter->buses.push_back(b);
            break;
        }
    }
}

void Datastructure::empty()

{
    stops.clear();
    routes.clear();
    dijkstra.clear();
    gray_nodes.clear();
    shortest_route.clear();
}

void Datastructure::print_stop(int stop_id)
{

    bool found_stop = false;
    for (std::shared_ptr<stop_data_> stop : stops){
        if(stop->stop_id_ == stop_id){
            std::cout<< stop->stop_name_ << std::endl;
            found_stop = true;
            break;
        }
    }
    if (found_stop == false){
        std::cout<< "Error: No such stop!"<< std::endl;
    }
}

void Datastructure::print_buses(int stop_id)
{
    bool found_bus = false;
    for (std::shared_ptr<route_data_> route : routes){
        for(std::shared_ptr<connection> conn: route->connections){
            if(conn->stop_id == stop_id){
                std::cout<< route->route_name_ << std::endl;
                found_bus = true;
                break;
            }
        }
    }
    if (found_bus == false){
        std::cout<< "Error: No such stop!"<< std::endl;
    }
}

void Datastructure::print_statistics()
{
    int number_of_stops = 0;
    int number__of_routes = 0;
    int number_of_buses = 0;

    for(std::shared_ptr<route_data_> route: routes){
        number_of_stops += route->connections.size();
        number_of_buses += route->buses.size();
    }
    number__of_routes = routes.size();
    std::cout << number_of_stops <<" stops, "<< number__of_routes << " routes, "<< number_of_buses <<" buses."<<  std::endl;
}


// a private function to calculate the waiting time at a stop //
int Datastructure::calculate_waiting_time(int stop, int route_id, int hours, int minutes){

    int waiting_time_in_minutes = 0;
    for(std::shared_ptr<route_data_> route :routes){
        if (route->route_id_ == route_id){
            for(std::shared_ptr<connection> conn : route->connections){
                if(conn->stop_id == stop){
                    for(std::shared_ptr<bus> b : route->buses){
                        if( ((b->start_hours*60)+b->start_minutes + conn->minutes) > ((hours*60) +minutes)){
                            waiting_time_in_minutes = ((b->start_hours-hours)*60 +b->start_minutes + conn->minutes) - ( + minutes);
                            return waiting_time_in_minutes;
                        }
                        else{
                            waiting_time_in_minutes = ((b->start_hours*60)+b->start_minutes + conn->minutes) - hours*60 + minutes;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

void Datastructure::print_fastest_journey(int start_stop, int end_stop, unsigned int hours, unsigned int minutes)
{
    // the following 15 lines is the dijkstra algorithm.
    waiting_time = 0;
    waiting_time_hours = 0;
    int time=0;

    for (std::shared_ptr<stop_data_> stop: stops){
        stop->colour = "white";
        stop->last_stop = nullptr;
        stop->weight = INT8_MAX;
    }
    for (std::shared_ptr<stop_data_> stop: stops){
        if(stop->stop_id_ == start_stop){
            stop->weight = 0;
            begin_point = stop;
            stop->colour = "gray";
            gray_nodes.push_back(stop);
            break;
        }
    }

    bool found_route = false;
    bool line_changed = false;

    while (gray_nodes.size() != 0) {
        std::shared_ptr<stop_data_> iter = gray_nodes[0];
        for(std::shared_ptr<edge> e : iter->edges){
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
        if (iter->stop_id_ == end_stop){ // the last stop was found
            found_route = true;
        while(last != nullptr){//go through the shortest route and collect the stops to a list
            shortest_route.insert(shortest_route.begin(), last);
            last = last->last_stop;

        }
        //int counter = 0;
        for(std::shared_ptr<stop_data_> stop : shortest_route){
            //counter += 1;
            if (stop->last_stop != nullptr){
                stop->last_stop->route_nro = stop->route_nro;
                first_stop = stop->last_stop;
                break;
            }
        }


        int route_number = -1;
        for(std::shared_ptr<stop_data_> stop : shortest_route){
            if (route_number != stop->route_nro){

                for(std::shared_ptr<route_data_> route : routes){
                    if (route->route_id_ == stop->route_nro){
                        if(stop->last_stop == nullptr){
                            waiting_time = waiting_time + calculate_waiting_time(stop->stop_id_, route->route_id_, hours+ waiting_time_hours, minutes+time);
                        }
                        else{
                            line_changed =true;
                            waiting_time = waiting_time + calculate_waiting_time(stop->last_stop->stop_id_, route->route_id_, hours+ waiting_time_hours, minutes+time);
                        }
                        std::cout<< route->route_name_<< std::endl;
                        if(line_changed == true){
                            std::cout <<"  ";
                            std::cout <<((hours*60) + waiting_time_hours + minutes+stop->last_stop->weight+waiting_time)/60;
                            if((hours*60 + waiting_time_hours + minutes+stop->last_stop->weight+waiting_time)%60 > 10){
                                std::cout <<":"<<(hours*60 + waiting_time_hours + minutes+stop->last_stop->weight+waiting_time)%60;
                                time =(stop->last_stop->weight+waiting_time)%60;
                            }
                            else{
                                std::cout <<":0"<<(hours*60 + waiting_time_hours + minutes+stop->last_stop->weight+waiting_time)%60;
                                time =(stop->last_stop->weight+waiting_time)%60;
                            }
                            std::cout <<"  ";
                            std::cout <<stop->last_stop->stop_id_;
                            std::cout << ",  ";
                            std::cout << stop->last_stop->stop_name_<< std::endl;
                            line_changed = false;
                        }
                        break;
                    }
                }
            }
            route_number = stop->route_nro;
            if(stop->stop_id_ == end_stop){
                std::cout<<"->";
            }
            else{
                std::cout <<"  ";
            }

            std::cout <<((hours*60) + waiting_time_hours + minutes+stop->weight+waiting_time)/60;
            if((hours*60 + waiting_time_hours + minutes+stop->weight+waiting_time)%60 > 10){
                std::cout <<":"<<(hours*60 + waiting_time_hours + minutes+stop->weight+waiting_time)%60;
                time =(stop->weight+waiting_time)%60;
            }
            else{
                std::cout <<":0"<<(hours*60 + waiting_time_hours + minutes+stop->weight+waiting_time)%60;
                time =(stop->weight+waiting_time)%60;
            }
            std::cout <<"  ";
            std::cout <<stop->stop_id_;
            std::cout << ",  ";
            std::cout << stop->stop_name_<< std::endl;
        }
        shortest_route.clear();

        }
        gray_nodes.erase(gray_nodes.begin());
    }
    if(found_route == false){
        std::cout <<"Error: No route!"<< std::endl;
        return;
    }
}
