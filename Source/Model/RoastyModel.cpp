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
      //  while (ingredients->next != nullptr){
        //    auto x = &ingredients->ingredient;
          //  auto beanName = x->getBean().getName();
            //removeIngredientByBeanName(beanName);
            //delete x;
        //}
        //delete ingredients;
    //}
    
    //if (events != nullptr) {
      //  while (events->next != nullptr){
        //    auto x = &events->event;
          //  auto timestamp = x->getTimestamp();
            //removeEventByTimestamp(timestamp);
            //delete x;
        //}
        //delete events;
    //}
}

Ingredient::Ingredient(Bean& bean, int amount): bean(bean),amount(amount){}

int Ingredient::getAmount() const { return amount; }

Bean const& Ingredient::getBean() const { return bean; }

Bean::Bean(std::string name): name(name) {}

std::string Bean::getName() const { return name; }

long EventValue::getValue() const { return value; }

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
