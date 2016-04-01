#include "datastructure.hh"
#include <iostream>

// Empty implementations for public interface, modify and add your own code here

Datastructure::Datastructure()
{
    for (int i = 0; i < varasto_size; i++){
        varasto_[i] = new candy;
        varasto_[i]->next = nullptr;
    }
    counter = 0;
}

Datastructure::~Datastructure()
{

}


// gives the hash key for the ID
size_t anna_key(const std::string& ID){
    std::hash<std::string> hash_funktio;
    return (hash_funktio(ID) % 1000);
}

// adds candies to the hash table
void Datastructure::add(const string &ID, const string &location,
                        unsigned int amount, const string &name)
{
    size_t key = anna_key(ID);
    if (varasto_[key]->name == ""){
        varasto_[key]->ID = ID;
        varasto_[key]->loc = location;
        varasto_[key]->amnt = amount;
        varasto_[key]->name = name;
        counter += 1;
    }
    else{
        candy* ptr = varasto_[key];
        candy* n = new candy;
        n->ID = ID;
        n->loc = location;
        n->amnt = amount;
        n->name = name;
        n->next = nullptr;
        if(ptr->ID == ID){
            ptr->amnt = ptr->amnt + amount;
            return;
        }
        while(ptr->next != nullptr){
            ptr = ptr->next;
            if(ptr->ID == ID){
                ptr->amnt = ptr->amnt + amount;
                return;
            }
        }
        ptr->next = n;
        counter += 1;
        return;
    }
}


void Datastructure::substract(const string &ID, unsigned int amount)
{
    candy* del;
    candy* ptr_eka;
    candy* ptr_edellinen;

    size_t key = anna_key(ID);
    candy* ptr = varasto_[key];
    if(ptr->ID == ID and ptr->amnt < amount){
        std::cout<< "Not enough candy available." << std::endl;
        std::cout<< "Amount: " << ptr->amnt << " Shelf: " <<
                    ptr->loc << std::endl;
        return;
    }
    else if(ptr->ID == ID and ptr->amnt > amount){
        ptr->amnt = ptr->amnt - amount;
        std::cout<< "Amount: " << ptr->amnt << " Shelf: " <<
                    ptr->loc << std::endl;
        return;
    }
    else if(ptr->ID == ID and ptr->amnt == amount and ptr->next == nullptr){
        del = varasto_[key];
        std::cout<< "Amount: 0 Shelf: " << ptr->loc << std::endl;
        delete del;
        varasto_[key] = new candy;
        varasto_[key]->next = nullptr;
        counter -= 1;
        return;
    }
    else if(ptr->amnt == amount and ptr->next !=  nullptr){
        del = varasto_[key];
        varasto_[key] = varasto_[key]->next;
        std::cout<< "Amount: 0 Shelf: " << ptr->loc << std::endl;
        delete del;
        counter -= 1;
        return;
    }
    else{
        ptr_eka = varasto_[key]->next;
        ptr_edellinen = varasto_[key];

        while(ptr_eka != nullptr){
            if (ptr_eka->ID == ID){
                break;
            }
            ptr_edellinen = ptr_eka;
            ptr_eka = ptr_eka->next;
        }
        if (ptr_eka == nullptr){
            std::cout << "Product not in warehouse." << std::endl;
            return;
        }
        else if ( ptr_eka->ID == ID and ptr_eka->amnt < amount){
            std::cout<< "Not enough candy available." << std::endl;
            std::cout<< "Amount: " << ptr_eka->amnt << " Shelf: " <<
                        ptr_eka->loc << std::endl;
            return;
        }

        else if(ptr_eka->ID == ID and ptr_eka->amnt > amount){
            ptr_eka->amnt = ptr_eka->amnt - amount;
            std::cout<< "Amount: " << ptr_eka->amnt << " Shelf: " <<
                        ptr_eka->loc << std::endl;
            return;
        }

        else if(ptr_eka->ID == ID and ptr_eka->amnt == amount){
            del = ptr_eka->next;
            std::cout<< "Amount: 0 Shelf: " << ptr_eka->loc << std::endl;
            ptr_edellinen->next = del;
            delete ptr_eka;
            counter -= 1;
            return;
        }
    }
}

void Datastructure::find(const string &ID) const
{
    size_t key = anna_key(ID);
    candy* ptr = varasto_[key];
    if(ptr->ID == ID){
        std::cout<< varasto_[key]->name << " " << varasto_[key]->amnt << " "<<
                    varasto_[key]->loc << std::endl;
        return;
    }
    while (ptr->next != nullptr) {
        ptr = ptr->next;
        if(ptr->ID == ID){
            std::cout<< ptr->name << " " << ptr->amnt << " "<<
                        ptr->loc << std::endl;
            return;
        }
    }
    std::cout<<"Product not in warehouse." << std::endl;
    delete ptr;

}

size_t Datastructure::count() const
{
    return counter;
}

void Datastructure::empty()
{
    candy* ptr_del;
    candy* ptr_seuraava;
    counter = 0;
    // loops the whole array and deletes the pointers and the content of the array
    for (int i = 0; i < varasto_size; i++){
        if (varasto_[i]->ID != "" and varasto_[i]->next == nullptr){
            varasto_[i] = new candy;
            varasto_[i]->next = nullptr;
        }
        else if (varasto_[i]->ID != "" and varasto_[i]->next != nullptr){
            ptr_seuraava = varasto_[i]->next;
            varasto_[i] = new candy;
            varasto_[i]->next = nullptr;
            while(ptr_seuraava != nullptr){
                ptr_del = ptr_seuraava;
                ptr_seuraava = ptr_seuraava->next;
                delete ptr_del;
            }
            delete ptr_seuraava;
        }

    }
}
