#include <iostream>
#include <memory>

using namespace std;

class Singleton
{
public:
  /**
   *  Destructor
   */
  ~Singleton(){ cout << "Singleton::~Singleton called" << endl; }
  /**
   *  Returns Singleton instance
   */
  static shared_ptr<Singleton> getInstance()
  {
    if( !instance ) 
      instance = shared_ptr<Singleton>{new Singleton};
    return instance;
  }
  /**
   *  Singleton interface function
   */
  void debug() const { cout << "Debug function called" << endl; }
private:
  /**
   *  Constructor is private
   */
  Singleton(){ cout << "Singleton created" << endl; }
  static shared_ptr<Singleton> instance; /** Internal pointer to Singleton unique instance */
};

shared_ptr<Singleton> Singleton::instance = nullptr;

int main()
{
  auto c1 = Singleton::getInstance(); // Get instance of Singleton
  cout << "c1->Singleton = " << c1 << endl;
   
  {
    auto c2 = Singleton::getInstance();
    cout << "c2->Singleton = " << c2 << endl; // New pointer to same Singleton
    c2->debug();
  }

  c1->debug();

  return 0;
}
