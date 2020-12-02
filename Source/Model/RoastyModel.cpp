#include "RoastyModel.hpp"

/* Bean */
Bean::Bean(std::string name): name(name) {}

Bean::Bean( Bean const& b){ name = b.getName(); }

Bean& Bean::operator=(Bean const& b){
    this->name = b.getName();
    return *this;
}

std::string Bean::getName() const { return name; }

Bean::~Bean(){}


/* Ingredient */
Ingredient::Ingredient(Bean& bean, int amount): bean(bean),amount(amount){}

int Ingredient::getAmount() const { return amount; }

Bean const& Ingredient::getBean() const { return bean; }

Ingredient::~Ingredient(){}


/* EventValue */
long EventValue::getValue() const { return value; }

EventValue::EventValue(EventValue& ev){ value = ev.getValue(); }

EventValue& EventValue::operator=(long const& v) {
    this->value = v;
    return *this;
}

EventValue::~EventValue(){}


/* Event */
Event::Event(std::string type, long timestamp, EventValue* eventValue): type(type), eventTimestamp(timestamp), eventValue(eventValue) {}

Event::Event(std::string type, long timestamp): type(type), eventTimestamp(timestamp) {}

Event::Event(Event const& e){
    type = e.getType();
    eventTimestamp = e.getTimestamp();
    eventValue = e.getValue();
}

std::string Event::getType() const { return type; }

long Event::getTimestamp() const { return eventTimestamp; }

bool Event::hasValue() const {
    if (eventValue != nullptr){
        return true;
    } else {
        return false;
    }
}
        
EventValue* Event::getValue() const {
    if (hasValue()) {
        return eventValue;
    } else {
        //ask for a nonexistent value
        std::cerr << "This event does not contain any value" << std::endl;
        exit(0);
    }
}

Event::~Event(){}


/* Roast */
Roast::Roast(long id, long timestamp): id(id), timestamp(timestamp){}

Roast::Roast(Roast const& r){
    id = r.getId();
    timestamp = r.getTimestamp();
    ingredientsCount = r.getIngredientsCount();
    eventCount = r.getEventCount();
    
    ingredients = r.getIngredientsList();
    events = r.getEventList();
}

long Roast::getId() const { return id;}

long Roast::getTimestamp() const { return timestamp; }

int Roast::getIngredientsCount() const { return ingredientsCount; }

int Roast::getEventCount() const { return eventCount; }

IngredientsList* Roast::getIngredientsList() const{ return ingredients; }

EventsList* Roast::getEventList() const { return events; }

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
    std::cerr<<"The "<<index<<"th ingredient does not exist"<<std::endl;
    //exit(0);
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
    std::cerr<<"The "<<index<<"th event does not exist" << std::endl;
    //exit(0);
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
    ingredientsCount++; //update count regardless
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
                delete old; //deleter this ingredient
                return;
            }
            iterator = &((*iterator)->next); //check next ingredient
        }
        if (getIngredientsCount()>0){
            ingredientsCount--; //update count only if removed
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
    eventCount++; //update count regardless
}

void Roast::removeEventByTimestamp(long timestamp){
    if (events != nullptr){//don't remove from empty list
        EventsList** iterator = &events;
        //loop until find the target event to be deleted
        while((*iterator)->next != nullptr){
            if ((*iterator)->event.getTimestamp() == timestamp){
                //assign a new pointer to that event
                auto old = (*iterator);
                //point to the next event
                (*iterator) = (*iterator)->next;
                delete old; //deleter this event
                return;
            }
            iterator = &((*iterator)->next); //check next event
        }
        if (getEventCount()>0){
            eventCount--; //update count only if removed
        }
    }
}

//won't compile (ಥ﹏ಥ)
Roast::~Roast() {
    //if (ingredients != nullptr) {
        //while (ingredients->next != nullptr){
          //  auto x = &ingredients->ingredient;
            //auto beanName = x->getBean().getName();
            //removeIngredientByBeanName(beanName);
            //delete x;
        //}
        //delete ingredients;
    //}
    
    //if (events != nullptr) {
        //while (events->next != nullptr){
            //auto x = &events->event;
            //auto timestamp = x->getTimestamp();
            //removeEventByTimestamp(timestamp);
           // delete x;
            
        //}
        //delete events;
    //}
}
