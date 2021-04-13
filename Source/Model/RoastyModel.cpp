#include "RoastyModel.hpp"
#include <iostream>

using namespace std;

/* Bean */
Bean::Bean(std::string name){ this->name = name; }

std::string Bean::getName() const { return name; }

/* Ingredient */
Ingredient::Ingredient(Bean& bean, int amount): bean(bean) {
    this->amount = amount;
}

int Ingredient::getAmount() const { return amount; }

Bean const& Ingredient::getBean() const { return bean; }

Ingredient::~Ingredient(){ delete &bean; }

/* EventValue */
long EventValue::getValue() const { return value; }

/* Event */
Event::Event(std::string type, long timestamp, EventValue* eventValue): type(type), eventTimestamp(timestamp), eventValue(eventValue) {}

Event::Event(std::string type, long timestamp): type(type), eventTimestamp(timestamp) {}

// copy constructor
Event::Event(Event const& e){
    delete this->eventValue;
    this->type = e.getType();
    this->eventTimestamp = e.getTimestamp();
    if (e.hasValue()) {
        this->eventValue = new EventValue(e.getValue()->getValue());
    }
}

//copy assignment
Event& Event::operator=(Event const& e){
    delete this->eventValue;
    this->type = e.getType();
    this->eventTimestamp = e.getTimestamp();
    if (e.hasValue()) {
        this->eventValue = new EventValue(e.getValue()->getValue());
    }
    return *this;
}


std::string Event::getType() const { return type; }

long Event::getTimestamp() const { return eventTimestamp; }

bool Event::hasValue() const { return (eventValue != nullptr); }
        
EventValue* Event::getValue() const { return eventValue; }

Event::~Event(){
    if (this->hasValue()) {
        delete eventValue;
    }
}


/* Roast */
Roast::Roast(long id, long timestamp): id(id), timestamp(timestamp){}

// copy constructor
Roast::Roast(Roast const& r){
    
    //deallocate original memory
    auto tmp = this->ingredients;

    while (tmp != nullptr) {
        auto x = &(tmp->ingredient);
        delete x;
        auto next = tmp->next;
        delete tmp;
        tmp = next;
    }

    auto tmp2 = this->events;

    while (tmp2 != nullptr) {
        auto x = &(tmp2->event);
        delete x;
        auto next = tmp2->next;
        delete tmp2;
        tmp2 = next;
    }
    
    // copy attributes
    this->id = r.getId();
    this->timestamp = r.getTimestamp();
    
    // make deep copies
    if (r.ingredients == NULL) {
        this->ingredients = nullptr;
    }else{
        auto x = r.ingredients;
        this->ingredients = new IngredientsList(*(new Ingredient(*(new Bean(x->ingredient.getBean().getName())), x->ingredient.getAmount())));
        
        auto tmp = this->ingredients;
        x = x->next;
        while (x != nullptr) {
            tmp->next = new IngredientsList(*(new Ingredient(*(new Bean(x->ingredient.getBean().getName())), x->ingredient.getAmount())));
            x = x->next;
            tmp = tmp->next;
        }
    }
    
    if (r.events == NULL) {
        this->events = nullptr;
    }else{
        auto x = r.events;
        if (x->event.hasValue()) {
            this->events = new EventsList(*(new Event(x->event.getType(), x->event.getTimestamp(), new EventValue(x->event.getValue()->getValue()))));
        } else {
            this->events = new EventsList(*(new Event(x->event.getType(), x->event.getTimestamp())));
        }
        
        auto tmp = this->events;
        x = x->next;
        while (x != nullptr) {
            if (x->event.hasValue()) {
                tmp->next = new EventsList(*(new Event(x->event.getType(), x->event.getTimestamp(), new EventValue(x->event.getValue()->getValue()))));
            } else {
                tmp->next = new EventsList(*(new Event(x->event.getType(), x->event.getTimestamp())));
            }
            x = x->next;
            tmp = tmp->next;
        }
    }
}

// copy assignment
Roast& Roast::operator=(Roast const& r){
    //deallocate original memory
    auto tmp = this->ingredients;
        
    while (tmp != nullptr) {
        auto x = &(tmp->ingredient);
        delete x;
        auto next = tmp->next;
        delete tmp;
        tmp = next;
    }
    
    auto tmp2 = this->events;
        
    while (tmp2 != nullptr) {
        auto x = &(tmp2->event);
        delete x;
        auto next = tmp2->next;
        delete tmp2;
        tmp2 = next;
    }
    
    // copy attributes
    this->id = r.getId();
    this->timestamp = r.getTimestamp();
    
    // make deep copies
    if (r.ingredients == NULL) {
        this->ingredients = nullptr;
    }else{
        auto x = r.ingredients;
        this->ingredients = new IngredientsList(*(new Ingredient(*(new Bean(x->ingredient.getBean().getName())), x->ingredient.getAmount())));
        auto tmp = this->ingredients;
        x = x->next;
        while (x != nullptr) {
            tmp->next = new IngredientsList(*(new Ingredient(*(new Bean(x->ingredient.getBean().getName())), x->ingredient.getAmount())));
            x = x->next;
            tmp = tmp->next;
        }
    }
    
    if (r.events == NULL) {
        this->events = nullptr;
    }else{
        auto x = r.events;
        if (x->event.hasValue()) {
            this->events = new EventsList(*(new Event(x->event.getType(), x->event.getTimestamp(), new EventValue(x->event.getValue()->getValue()))));
        } else {
            this->events = new EventsList(*(new Event(x->event.getType(), x->event.getTimestamp())));
        }
        
        auto tmp = this->events;
        x = x->next;
        while (x != nullptr) {
            if (x->event.hasValue()) {
                tmp->next = new EventsList(*(new Event(x->event.getType(), x->event.getTimestamp(), new EventValue(x->event.getValue()->getValue()))));
            } else {
                tmp->next = new EventsList(*(new Event(x->event.getType(), x->event.getTimestamp())));
            }
            x = x->next;
            tmp = tmp->next;
        }
    }
    
    return *this;
}

long Roast::getId() const { return id;}

long Roast::getTimestamp() const { return timestamp; }

int Roast::getIngredientsCount() const {
    IngredientsList* iterator = ingredients;
    int count = 0;
    while (iterator != nullptr) {
        iterator = iterator->next;
        count++;
    }
    return count;
}

int Roast::getEventCount() const {
    EventsList* iterator = events;
    int count = 0;
    while (iterator != nullptr) {
        iterator = iterator->next;
        count++;
    }
    return count;
}

Ingredient const& Roast::getIngredient(int index) const {
    IngredientsList* iterator = ingredients;
    int count = 0; //counter of ith ingredient
    while (iterator != nullptr){
        if (count == index) {//found the ith ingredient
            //return a reference to that ingredient
            return (iterator->ingredient);
        }
        //check next ingredient
        count++;
        iterator = iterator->next;
    }
    //index exceeds the number of ingredients in IngredientsList
    cerr<<"The "<<index<<"th ingredient does not exist"<<std::endl;
    exit(0);
}

Event const& Roast::getEvent(int index) const {
    EventsList* iterator = events;
    int count = 0; //counter of ith event
    while (iterator != nullptr){
        if (count == index) { //found the ith event
            //return a reference to that event
            return (iterator->event);
        }
        //check next event
        count++;
        iterator = iterator->next;
    }
    //index exceeds the number of events in EventsList
    cerr<<"The "<<index<<"th event does not exist" << std::endl;
    exit(0);
}

void Roast::addIngredient(Ingredient const& ingredient){
    if (ingredients == nullptr){//IngredientsList empty
        //add list in the beginning
        ingredients = new IngredientsList(ingredient);
    } else { //IngredientsList not empty
        IngredientsList* iterator = ingredients;
        while(iterator->next != nullptr){
            iterator = iterator->next;
        } //add ingredient at the first nullptr
        iterator->next = new IngredientsList(ingredient);
    }
}

void Roast::removeIngredientByBeanName(std::string const& beanName){
    if (ingredients != nullptr){ //don't remove from empty list
        IngredientsList** iterator = &ingredients;
        //loop until find the target event to be deleted
        while((*iterator) != nullptr) {
            if ((*iterator)->ingredient.getBean().getName() == beanName){
                //assign a new pointer to that ingredient
                auto old = (*iterator);
                //point to the next ingredient
                (*iterator) = (*iterator)->next;
                
                //free the ingredient
                delete &(old->ingredient);
                //free the ingredientsList
                delete old;
                return;
            }
            iterator = &((*iterator)->next); //check next ingredient
        }
    }
}

void Roast::addEvent(Event const& event){
    if (events == nullptr){//eventsList empty
        // add event in the begining
        events = new EventsList(event);
    }else{ // eventsList not empty
        EventsList* iterator = events;
        while(iterator->next != nullptr){
            iterator = iterator->next;
        }
        // add event at the first nullptr
        iterator->next = new EventsList(event);
    }
}

void Roast::removeEventByTimestamp(long timestamp){
    if (events != nullptr){//don't remove from empty list
        EventsList** iterator = &events;
        //loop until find the target event to be deleted
        while((*iterator) != nullptr){
            if ((*iterator)->event.getTimestamp() == timestamp){
                //assign a new pointer to that event
                auto old = (*iterator);
                //point to the next event
                (*iterator) = (*iterator)->next;
                //free the event
                delete &(old->event);
                //free the eventsList
                delete old;
                return;
            }
            iterator = &((*iterator)->next); //check next event
        }
    }
}

//won't compile (ಥ﹏ಥ)
Roast::~Roast() {
    
    //deallocate
    while (ingredients != nullptr) {
        auto tmp = ingredients->next;
        delete &(ingredients->ingredient);
        delete ingredients;
        ingredients = tmp;
    }
    
    while (events != nullptr) {
        auto tmp = events->next;
        delete &(events->event);
        delete events;
        events = tmp;
    }
}
