#include <iostream>

using namespace std;

class Vector {
public:
  Vector() : sz{0}, elem{nullptr}{}
  Vector(int s) : sz{s}, elem{new double[s]}{ cout << "Constructor" << endl; }
  Vector(const Vector& v) : sz{v.sz}, elem{new double[v.sz]} 
  { 
    cout << "Copy constructor" << endl;
    for(int i = 0; i < v.sz; i++)
      elem[i] = v[i];
  }

  Vector(Vector&& v) : sz{v.sz}, elem{v.elem}
  {
    cout << "Move constructor" << endl;
    v.sz = 0;
    v.elem = nullptr;
  }

  ~Vector(){ delete[] elem; sz = 0; }

  Vector& operator= (Vector&& v)
  {
    cout << "Move assignment operator" << endl;
    delete[] elem; // Release resources that *this owns
    sz = v.sz; // Get other's state
    elem = v.elem;

    v.sz = 0; // Reset other to default
    v.elem = nullptr;

    return *this;
  }

  Vector& operator= (const Vector& v)
  {
    cout << "Assignment operator" << endl;

    sz = v.sz;
    delete[] elem;
    elem = new double[v.sz];

    for(int i = 0; i < v.sz; i++)
      elem[i] = v[i];

    return *this;
  }
  
  double& operator[](int i) { return elem[i]; }
  const double& operator[](int i) const { return elem[i]; }
  
  Vector operator+(const Vector& v)
  {
    cout << "Operator +" << endl;
    Vector res(v.size());
    for(auto i = 0; i < v.size(); i++)
      res[i] = elem[i] + v[i];
    return res;
  }

  int size() const { return sz; }
  
  friend ostream& operator<< (ostream& os, const Vector& v)
  {
    os << "Size = " << v.sz << endl;
    os << "["; 
    for(int i = 0; i < v.sz; i++)
    {
      os << v[i];
      if( i < v.sz - 1 )
        os << ", ";
    }
    os << "]";
  }

private:
  int sz;
  double *elem;
};

int main()
{
  Vector v1(10); 

  for(int i = 0; i < v1.size(); i++)
    v1[i] = i + 1;
  
  Vector v2 = v1;
  cout << "v2 = v1" << endl;

  {
    Vector v3 = v1 + v2;
    cout << "V3 = v1 + v2" << endl;

    v3[0] = 0;
    v1[0] = 22;
  }

  // print vector
  cout << "Vector v1 " << v1 << endl;
  cout << "Vector v2 " << v2 << endl;
  //cout << "Vector v3 " << v3 << endl;

  return 0;
}
