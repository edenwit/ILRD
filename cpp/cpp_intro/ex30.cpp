
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

void Fifi() 
{ 
    throw BadDog("bad pup"); cerr << "Fifi() after throw" << endl; 
} 
void Foo() 

{ 
    //  X x1;     

    // Printer p;
    Fifi();     
    cerr << "Foo() after Fifi()" << endl; 
} 

void Bar() 
{ 
    Foo(); 
    cerr << "Bar() after Foo()" << endl; 
} 
int main() {     
    try     
    {         
        Bar();     
    }     
    catch(bad_alloc&)     
    {         
        cerr << "Out of memory! exiting."; exit(2);     
    }     
    catch(BadDog& b)     
    {         
        cerr << "Bad dog exception: " << b.what(); exit(3);     
    }     
    catch( exception& r )
    {
        cerr << "unknown exception: " << r.what();
        exit(4);     
    }
    catch (...)
    {
        cerr << "catch them all!!" ;
       
    }
    return 0; 
}