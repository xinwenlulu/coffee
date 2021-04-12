#pragma once
#include <string>

/* Ingredient Section */
class Bean {
    std::string name;
public:
    //constructors
    Bean(std::string name);
    
    //get the state of bean
    std::string getName() const;
};

class Ingredient {
    Bean& bean;
    int amount;
public:
    Ingredient(Bean& bean, int amount);
    
    //get the state of the Ingredient//
    int getAmount() const;
    Bean const& getBean() const;
    
    ~Ingredient();
};

struct IngredientsList {     // a linked list for all ingredients added//
    Ingredient const& ingredient;
    IngredientsList* next = nullptr;
    //constructor declared and initialised here
    IngredientsList(Ingredient const& ingredient):ingredient(ingredient){};
};

/* Event Section */
class EventValue {
    long value;
public:
    //constructor
    EventValue (long value): value(value){};
    
    //get the state of EventValue
    long getValue() const;
    
};

class Event {
    std::string type;
    long eventTimestamp;
    EventValue* eventValue = nullptr;
public:
    //constructors: EventValue* eventValue is optional //
    Event(std::string type, long timestamp, EventValue* eventValue);
    Event(std::string type, long timestamp);
    Event(Event const& e);
    //copy assignment
    Event& operator=(Event const& e);
    
    //get the state of the event
    std::string getType() const;
    long getTimestamp() const;
    bool hasValue() const;
    EventValue* getValue() const;
    
    ~Event();
};
     
struct EventsList { // a linked list for all events added//
    Event const& event;
    EventsList* next = nullptr;
    //constructor declared and initialised here
    EventsList(Event const& event): event(event){};
};

/* Roast Section */
class Roast {
    long id;
    long timestamp;
    IngredientsList* ingredients = nullptr;
    EventsList* events = nullptr;
    
public:
    //constructors
    Roast(long id, long timestamp);
    Roast(Roast const& r);
    //copy assignment
    Roast& operator=(Roast const& r);
    
    //getting the state of the roast
    long getId() const;
    long getTimestamp() const;
    
    int getIngredientsCount() const;
    int getEventCount() const;
    
    //get ingredient and event from its index in list
    Ingredient const& getIngredient(int index) const;
    Event const& getEvent(int index) const;
    
    void addIngredient(Ingredient const& ingredient);
    /* roast assumes ownership of ingredient */
    
    void removeIngredientByBeanName(std::string const& beanName);
    /* deletes the removed Ingredient, should the bean with it */
    
    void addEvent(Event const& event);
    /* roast assumes ownership of event*/
    
    void removeEventByTimestamp(long timestamp);
    /* deletes the removed Event*/
    
    ~Roast(); //deconstructor
};
