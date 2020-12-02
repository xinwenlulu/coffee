#include "RoastyModel.hpp"

Roast::Roast(long id, long timestamp): id(id), timestamp(timestamp){}

long Roast::getId() const { return id;}

long Roast::getTimestamp() const { return timestamp; }

Ingredient const& Roast::getIngredient(int index) const {
    IngredientsList* iterator = ingredients;
    int count = 0;
    while (iterator != nullptr){
        if (count == index) {
            return (iterator->ingredient);
        }
        count++;
        iterator = iterator->next;
    }
    std::cerr<<"The "<<index<<"th ingredient not found: check your index"<<std::endl;
    return iterator->ingredient;
}

Event const& Roast::getEvent(int index) const {
    EventsList* iterator = events;
    int count = 0;
    while (iterator != nullptr){
        if (count == index) {
            return (iterator->event);
        }
        count++;
        iterator = iterator->next;
    }
    std::cerr<<"The "<<index<<"th event not found: check your index" << std::endl;
    return iterator->event;
}

void Roast::addIngredient(Ingredient const& ingredient){
    if (ingredients == nullptr){
        ingredients = new IngredientsList(ingredient);
    } else {
        IngredientsList* iterator = ingredients;
        while(iterator->next != nullptr){
            iterator = iterator->next;
        }
        iterator->next = new IngredientsList(ingredient);
    }
    ingredientsCount++;
}

void Roast::removeIngredientByBeanName(std::string const& beanName){
    if (ingredients != nullptr){
        IngredientsList** iterator = &ingredients;
        while((*iterator) != nullptr) {
            if ((*iterator)->ingredient.getBean().getName() == beanName){
                auto old = (*iterator);
                (*iterator) = (*iterator)->next;
                delete old;
                return;
            }
            iterator = &((*iterator)->next);
        }
    }
    ingredientsCount--;
}

int Roast::getIngredientsCount() const { return ingredientsCount; }

void Roast::addEvent(Event const& event){
    if (events == nullptr){
        events = new EventsList(event);
    }else{
        EventsList* iterator = events;
        while(iterator->next != nullptr){
            iterator = iterator->next;
        }
        iterator->next = new EventsList(event);
    }
    eventCount++;
}

void Roast::removeEventByTimestamp(long timestamp){
    if (events == nullptr){
        return;
    } else {
        EventsList** iterator = &events;
        while((*iterator)->next != nullptr){
            if ((*iterator)->event.getTimestamp() == timestamp){
                auto old = (*iterator);
                (*iterator) = (*iterator)->next;
                delete old;
                return;
            }
            iterator = &((*iterator)->next);
        }
    }
    eventCount--;
}

int Roast::getEventCount() const { return eventCount; }

Roast::~Roast() {
    //if (ingredients != nullptr) {
      //  IngredientsList* iterator = ingredients;
        //while (iterator->next != nullptr){
          //  auto x = iterator->ingredient;
            //auto beanName = x.getBean().getName();
            //removeIngredientByBeanName(beanName);
            //delete x;
            //iterator = iterator->next;
        //}
        //delete ingredients;
    //}
    
    //if (events != nullptr) {
        //EventsList* iterator = events;
        //while (iterator->next != nullptr){
            //auto x = iterator->event;
            //auto timestamp = x.getTimestamp();
            //removeEventByTimestamp(timestamp);
            //delete x;
            //iterator = iterator->next;
        //}
        //delete events;
    //}
}

Roast::Roast(Roast const& r){
    id = r.getId();
    timestamp = r.getTimestamp();
    ingredientsCount = r.getIngredientsCount();
    eventCount = r.getEventCount();
    
    ingredients = r.getIngredientsList();
    events = r.getEventList();
}

IngredientsList* Roast::getIngredientsList() const{ return ingredients; }

EventsList* Roast::getEventList() const { return events; }

Ingredient::Ingredient(Bean& bean, int amount): bean(bean),amount(amount){}

int Ingredient::getAmount() const { return amount; }

Bean const& Ingredient::getBean() const { return bean; }

Bean::Bean(std::string name): name(name) {}

std::string Bean::getName() const { return name; }

Bean& Bean::operator=(std::string const& name) {
    this->name = name;
    return *this;
}

Bean::Bean(Bean const& b){
    name = b.getName();
}

Bean& Bean::operator=(Bean const& b){
    this->name = b.getName();
    return *this;
}

long EventValue::getValue() const { return value; }

EventValue& EventValue::operator=(long const& v) {
    this->value = v;
    return *this;
}

Event::Event(std::string type, long timestamp, EventValue* eventValue): type(type), eventTimestamp(timestamp), eventValue(eventValue) {}

Event::Event(std::string type, long timestamp): type(type), eventTimestamp(timestamp) {}

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
        return nullptr;
    }
}

EventValue::EventValue(EventValue& ev){
    value = ev.getValue();
}

Event::Event(Event const& e){
    type = e.getType();
    eventTimestamp = e.getTimestamp();
    eventValue = e.getValue();
}

