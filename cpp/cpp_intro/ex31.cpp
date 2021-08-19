
#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>

using namespace std; 

class Printer
{
public:
    Printer(){cout << "hello world!!" << endl;}
    ~Printer(){cout << "goodbye world!!" << endl;}
};

struct BadDog: public runtime_error 
{   
    BadDog(const string& s_ = "This is a bad dog"): runtime_error(s_) {;}
}; 

void Fifi() throw (int)
{ 
    throw BadDog("dad pup"); cerr << "Fifi() after throw" << endl; 
} 
void Foo() 

{ 
    //  X x1;     

    // Printer p;
    Fifi();     
    cerr << "Foo() after Fifi()" << endl; 
} 

void unexcpacted()
{
    cout << "unexcpaced!!" << endl;  
    cout << "unexcpaced!!" << endl;    

}

void terminated()
{
    cout << "terminated!!" << endl;   
    cout << "terminated!!" << endl;    

}

void Bar() 
{ 
    Foo(); 
    cerr << "Bar() after Foo()" << endl; 
} 
int main() {     

    set_unexpected(unexcpacted);
    set_terminate(terminated);

    try     
    {         
        Bar();     
    }     
    catch(bad_alloc&)     
    {         
        cerr << "Out of memory! exiting."; exit(2);     
    }     
    // catch(BadDog& b)     
    // {         
    //     cerr << "Bad dog exception: " << b.what(); exit(3);     
    // }     
    // catch( exception& r )
    // {
    //     cerr << "unknown exception: " << r.what();
    //     exit(4);     
    // }

    return 0; 
}