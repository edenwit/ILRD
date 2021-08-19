void Foo()
{
    int *ip = new int;
    Bar(ip);
    Fishi();
    Fifi(ip);
    Dodo();
    delete ip;
}

int main ()
{
    Foo();

    return (0);
}