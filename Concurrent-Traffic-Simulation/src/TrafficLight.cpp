#include <iostream>
#include <random>
#include "TrafficLight.h"
#include <chrono>

/* Implementation of class "MessageQueue" */

template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function. 
  
    // perform queue modification under the lock
     std::unique_lock<std::mutex> uLock(_mutex);
     _condition.wait(uLock, [this] { return !_messages.empty(); }); // pass unique lock to condition variable
    // remove last vector element from queue
     T msg = std::move(_messages.back());
     _messages.pop_back();

     return msg; // will not be copied due to return value optimization (RVO) in C++
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // add vector to queue
    std::lock_guard<std::mutex> uLock(_mutex);
    _messages.clear();
    _messages.push_front(std::move(msg));
    _condition.notify_one(); // notify client after pushing new Vehicle into vector
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
}


/* Implementation of class "TrafficLight" */


TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{
    while ( true ){
    //std::this_thread::sleep_for( std::chrono::milliseconds(1) );
    auto current_phase = _trafficLightPhases.receive();
    while (current_phase == TrafficLightPhase::green ) return;
  }
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class. 
  threads.emplace_back( std::thread( &TrafficLight::cycleThroughPhases, this) );
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    // FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles 
    // and toggles the current phase of the traffic light between red and green and sends an update method 
    // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds. 
    // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles. 
  
  const auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator( seed );
  std::uniform_int_distribution<int> distribution(4,6);
  const auto duration = distribution( generator );

  auto start_of_cycle = std::chrono::steady_clock::now();
  while ( true ) {

    const auto current_time = std::chrono::steady_clock::now();
    const auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds> (current_time - start_of_cycle).count();

    if ( elapsed_time >= duration ) {
      start_of_cycle = std::chrono::steady_clock::now();
      _currentPhase = ( _currentPhase == TrafficLightPhase::green ) ?
                      TrafficLightPhase::red : TrafficLightPhase::green;
      
      _trafficLightPhases.send( std::move( TrafficLightPhase( _currentPhase ) ));
    }
    std::this_thread::sleep_for( std::chrono::milliseconds(1) );
  }
}

