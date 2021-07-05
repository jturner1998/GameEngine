#pragma once
#include <map>
#include <string>
#include <vector>

class Message;
class Observer;

typedef std::map<std::string, std::vector<Observer*> > MessageListenerMap;
typedef std::map<std::string, std::vector<Observer*> >::iterator MessageListenerMapIterator;
typedef std::vector<Observer*>::iterator ObserverListIterator;

/// Abstract parent class for the Observer pattern
/// This class should be inherited by objects that want to be observed and pass messages to their Observers
class ObserverSubject
{


};

