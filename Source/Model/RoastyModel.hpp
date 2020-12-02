#pragma once
#include <iostream>
#include <string>

class Bean {
    std::string name;
public:
    Bean(std::string name);
    std::string getName() const;
    Bean& operator=(std::string const& name);
    Bean(Bean const& b);
    Bean& operator=(Bean const& b);
};

class Ingredient {
    Bean& bean;
    int amount;
public:
    Ingredient(Bean& bean, int amount);
    Ingredient(Ingredient const& i): bean(*new Bean(i.bean)) {};
    int getAmount() const;
    Bean const& getBean() const;
};

class EventValue {
    long value;
public:
    EventValue (long value): value(value){};
    long getValue() const;
    EventValue& operator=(long const& v);
    EventValue(EventValue& ev);
};

class Event {
    std::string type;
    long eventTimestamp;
    EventValue* eventValue = nullptr;
public:
    Event(std::string type, long timestamp, EventValue* eventValue);
    Event(std::string type, long timestamp);
    std::string getType() const;
    long getTimestamp() const;
    bool hasValue() const;
    EventValue* getValue() const;
    Event(Event const& e);
};

struct IngredientsList {
    Ingredient const& ingredient;
    IngredientsList* next = nullptr;
    IngredientsList(Ingredient const& ingredient):ingredient(ingredient){};
    IngredientsList(IngredientsList const& il): ingredient(*new Ingredient const(il.ingredient)) {};
};

struct EventsList {
    Event const& event;
    EventsList* next = nullptr;
    EventsList(Event const& event): event(event){};
    EventsList(EventsList const& el): event(*new Event const(el.event)) {};
};

class Roast {
    long id;
    long timestamp;
    int ingredientsCount = 0;
    int eventCount = 0;
    IngredientsList* ingredients = nullptr;
    EventsList* events = nullptr;
    
public:
    Roast(long id, long timestamp);
    long getId() const;
    long getTimestamp() const;
    Ingredient const& getIngredient(int index) const;
    Event const& getEvent(int index) const;
    void addIngredient(Ingredient const& ingredient);
    /* roast assumes ownership of ingredient */
    void removeIngredientByBeanName(std::string const& beanName);
    int getIngredientsCount() const;
    void addEvent(Event const& event);
    /* roast assumes ownership of event*/
    void removeEventByTimestamp(long timestamp);
    int getEventCount() const;
    ~Roast();
    Roast(Roast const& r);
    IngredientsList* getIngredientsList() const;
    EventsList* getEventList() const;
};
