#include <iostream>
#include <memory>

#include <termios.h>
#include <unistd.h>

using namespace std;

// Finite state machine definition
class Context;

/**
 *  @brief Abstraction of a state in the finite state machine.
 *
 *  <p>This class is directly responsible for defining a suitable
 *  interface for the finite state machine. The event handled here
 *  is the simple evaluate() function call that behaves accordingly
 *  to the internal Context's internal state.</p>
 *  
 *  <p>Derived classes are responsible for defining next state in the 
 *  finite state machine, therefore the next method is public in order 
 *  to be overridden and protected because the State parent class interacts
 *  with the Context object.</p>
 */
class State {
public:
  State(){}
  virtual ~State(){}
  virtual void evaluate() const = 0;
  virtual void next(Context& context) = 0;
protected:
  /**
   *  Changes the internal state of Context object.
   */
  void next(Context& context, unique_ptr<State> nextState); 
};

class FirstState : public State
{
public:
  FirstState(){}
  ~FirstState(){ cout << "First state destructed" << endl; }
  void evaluate() const { cout << "First evaluate" << endl; }
  void next(Context& context);
};

class SecondState : public State
{
public:
  SecondState(){}
  ~SecondState(){ cout << "Second state destructed" << endl; }
  void evaluate() const { cout << "Second evaluate" << endl; }
  void next(Context& context);
};

// End of finite state machine definition

// Context class definition 
class Context 
{
public:
  Context() : state{unique_ptr<State>{new FirstState}} {} // Start as FirstState
  ~Context(){}
  void evaluate(){ state->evaluate(); } // Delegates to internal state the evaluation function
  void next(){ state->next(*this); } // Delegates to state machine the choice of next state
private:
  friend class State; // Allow State class to change internal Context's state 
  unique_ptr<State> state; // Internal state
};

void State::next(Context& context, unique_ptr<State> nextState) { context.state = std::move(nextState); }
void SecondState::next(Context& context) { State::next(context, unique_ptr<State>{new FirstState}); }
void FirstState::next(Context& context) { State::next(context, unique_ptr<State>{new SecondState}); }

int main()
{
  termios oldt; // Old terminal
  tcgetattr(STDIN_FILENO, &oldt); // Get terminal attributes 
  termios newt = oldt; // New terminal
  newt.c_lflag &= ~ ECHO; // Remove echo
  tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Set newt as new terminal

  char input;
  Context context;
  
  cout << "Press 'e' to evaluate current state or 'n' to move to next state" << endl;
   
  while( cin >> input )
  {
    switch(input)
    {
      case 'e':
        context.evaluate();
        break;
      case 'n':
        context.next();
        break;
      default:
        break;
    }
  }
  
  return 0;
}
