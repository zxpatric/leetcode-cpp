//
// Created by ZhouP on 3/3/2019.
//

#ifndef CPP_PROPERTY_H
#define CPP_PROPERTY_H

#include <numeric>

template<typename T, typename C>
class Property{
public:
    using SetterType = void (C::*)(T);
    using GetterType = T (C::*)() const;

    Property(C* theObject, SetterType theSetter, GetterType theGetter)
            :itsObject(theObject),
             itsSetter(theSetter),
             itsGetter(theGetter)
    { }

    Property(C* theObject, GetterType theGetter)
            :itsObject(theObject),
             itsGetter(theGetter),
             itsSetter(NULL)
    { }

    operator T() const
    { return (itsObject->*itsGetter)(); }

    C& operator = (T theValue) {
        if (itsSetter==NULL)
            throw std::logic_error("Assign to readonly property");
        (itsObject->*itsSetter)(theValue);
        return *itsObject;
    }

private:
    C* const itsObject;
    SetterType const itsSetter;
    GetterType const itsGetter;
};



class Test{
public:
    Property<int, Test> Number{this,&Test::setNumber,&Test::getNumber};
    Property<char, Test> Alphabet{this,&Test::getAlphabet};
private:
    int itsNumber;
    char m_theA;

public:
    char getAlphabet () const
    {
        return m_theA;
    }

    void setNumber(int theNumber)
    { itsNumber = theNumber; m_theA=std::to_string(theNumber)[0];}

    int getNumber() const
    { return itsNumber; }
};


int testProperty() {
    Test test1;
    test1.Number = 10;

//    test1.Alphabet = 'c';
    std::cout << "test1.Alphabet: " << test1.Alphabet << std::endl;

    Property<int, Test> test2 (&test1, &Test::setNumber,&Test::getNumber);
    test2 = 5;

    printf ("test1.Number: %d\n", test1.Number);    // different from the following. C printf is not fully compatiable with the property implementation
    int v = test1.Number;
    printf ("test1.Number: %d\n", v);

    std::cout << test1.Number << std::endl;
    return 0;
}

#endif //CPP_PROPERTY_H
