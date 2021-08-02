//
// Created by ZhouP on 3/3/2019.
//

#ifndef CPP_SINGELTON_H
#define CPP_SINGELTON_H

class Singelton1
{
public:
    static Singelton1 instance;

    static Singelton1 getInstance () { return instance; }

    Singelton1 (const    Singelton1& s)
    {
        printf("%s\n", "copy constructor of Singelton1 gets called");
    }

private:
    Singelton1 ()
    {}


};



class Singelton2
{
public:
    static Singelton2 instance;

    static Singelton2 &getInstance () { return instance; }

    Singelton2 (const    Singelton2& s)
    {
        printf("%s\n", "copy constructor gets called");
    }

private:
    Singelton2 ()
    {}


};

//

Singelton1 Singelton1::instance;
Singelton2 Singelton2::instance;


int testSingelton() {


    std::cout << "Hello, World!" << std::endl;

    Singelton1 a = Singelton1::getInstance();
    Singelton1 b = Singelton1::getInstance();

    printf("Singelton1: %d, %d \n", a, b);


    Singelton2 &c = Singelton2::getInstance();
    Singelton2 &d = Singelton2::getInstance();

    printf("Singelton2: %d, %d\n", &c, &d);
}


#endif //CPP_SINGELTON_H
