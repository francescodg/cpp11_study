#include <iostream>

using namespace std;

class B
{
public:
  B(int num) : b(num){}
  int bField() const { return b; }
protected:
  int b;
};

class A : public B
{
public:
  A(const B& b) : B(b) {}  
  A(int num) : B(0), a(num){}
  A(int num, const B &b) : a(num), B(b) {}
  int aField() const { return a; }
  A& operator= (const B& b){ this->b = b.bField(); }
private:
  int a;
};

int main()
{
  A a(5);
  cout << "A.a = " << a.aField() << ", " << "A.b = " << a.bField() << endl; 
  a = B(3);
  cout << "A.a = " << a.aField() << ", " << "A.b = " << a.bField() << endl; 
  A a1(5, B(3));
  cout << "A.a = " << a1.aField() << ", " << "A.b = " << a1.bField() << endl; 
  a1 = B(3);
  cout << "A.a = " << a1.aField() << ", " << "A.b = " << a1.bField() << endl; 
  return 0;
}
