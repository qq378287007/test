extern "C"
{
    int add(int a, int b)
    {
        return a + b;
    }
}

// g++ -shared -fPIC add.cpp -o add.cpp.so