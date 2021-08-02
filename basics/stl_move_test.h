//
// Created by patrick.zhou on 1/24/20.
//

#ifndef CPPSANDBOX_STL_MOVE_TEST_H
#define CPPSANDBOX_STL_MOVE_TEST_H

#include <iostream>

#pragma pack(push, 1)
class C
{
public:
    C (std::string msg, int size) : msg_(msg), member1_(size, 'c'){}
//    void print(){std::cout << msg_ << " at: " << (void *)(msg_.c_str()) <<std::endl;}
    void print(){
//        std::cout << msg_ << " at: " << (void*)msg_.data() <<std::endl;
        std::cout << (void*)this << std::endl;
        std::cout << msg_ << " at: " << &msg_ <<std::endl;
        std::cout << member1_.size() << " , " << (void*)member1_.data()<< std::endl;
    }

    C(C&& sb) = default;
//    {
////        this->msg_ = std::move(sb.msg_);
////        this->member1_ = std::move(sb.member1_);
//        this->member1_ = sb.member1_;
//        this->msg_ = sb.msg_;
//        std::cout << "Move Constructor" << std::endl;
//    }

    C& operator= (C&& sb) //= default;
    {
        this->msg_ = std::move(sb.msg_);
        this->member1_ = std::move(sb.member1_);
//        this->member1_ = sb.member1_;
//        this->msg_ = sb.msg_;
        std::cout << "Move Assignment" << std::endl;
    }

private:
    unsigned int member2_;
    std::string msg_;
    std::vector<char> member1_;
};


int test0()
{
    C obj_1("obj 1", 3);
    obj_1.print();
    C obj_2("obj 2", 5);
    obj_2.print();
    obj_2 = std::move(obj_1);
    obj_2.print();
    return 0;
}

class SB
{
private:
    bool member1_;
    int  member2_;
public:
    std::vector<int> member3_;
//    char* member4_;

    SB ()
    {
//        std::cout << "Constructor" << std::endl;
    }

    ~SB ()
    {
//        std::cout << "Destructor" << std::endl;
    }

    SB(const SB& sb)     {
        this->member3_ = sb.member3_;
        std::cout << "Copy Constructor" << std::endl;
    }

    SB& operator= (const SB& sb)
    {
        this->member3_ = sb.member3_;
        std::cout << "Assignment" << std::endl;
        return *this;
    }

    SB(SB&& sb)
    {
        this->member3_ = std::move(sb.member3_);
//        this->member3_ = sb.member3_;
        std::cout << "Move Constructor" << std::endl;
    }

    SB& operator= (SB&& sb)
    {
        this->member3_ = std::move(sb.member3_);
//        this->member3_ = sb.member3_;
        std::cout << "Move Assignment" << std::endl;
        return *this;
    }
};


typedef std::vector<SB> SBS;

SB returnSB ()
{
    return SB();
}

void test1() {
    SB sb;
    SB sb1;
    sb.member3_.resize(4);
    std::cout << &sb.member3_ << std::endl;
    SB sbm = std::move(sb);

    std::cout << sbm.member3_.size() << ',' << sb.member3_.size() << std::endl;
    std::cout << &sbm.member3_ << ',' << &sb.member3_ << std::endl;
    SB sbm1 = std::move(sb1);
}

void test2()
{
//    std::vector<int> a{1,2,3};
//    std::cout << a.data() << std::endl;
//    const auto b = std::move(a);
//    std::cout << a.size() << "," << a.data() << std::endl;
//    std::cout << b.data() << std::endl;

//    int a[100000000][100000000];

    std::string a_str{"abcdefghijklmnopqrstuvwxyz"};
    std::cout << (void*)a_str.data() << std::endl;
    a_str.resize(100);
    std::cout << (void*)a_str.data() << std::endl;
    a_str.resize(1);
//    a_str.clear();
    a_str.shrink_to_fit();
    std::cout << (void*)a_str.data() << "," << a_str << std::endl;
    a_str.resize(50);
    std::cout << (void*)a_str.data() << "," << a_str << std::endl;
    const auto b_str = std::move(a_str);
    std::cout << (void*)a_str.data() << "," << a_str.size() << std::endl;
    std::cout << (void*)b_str.data() << "," << b_str.size() << std::endl;
}

class D
{
public:
    int member01_[2];
public:
    D(int v0, int v1)
    {
        member01_[0] = v0;
        member01_[1] = v1;
    }

};

void test3()
{
    std::vector<int> v1(5, 'a');
    std::vector<int> v2(10, 'b');

    std::cout << (void*)&v1 << "," << (void*)v1.data() << std::endl;
    std::cout << (void*)&v2 << "," << (void*)v2.data() << std::endl;
    v1 = std::move(v2);
    std::cout << (void*)&v1 << "," << (void*)v1.data() << std::endl;
    std::cout << (void*)&v2 << "," << (void*)v2.data() << std::endl;


    D d0(0, 1);
    D d1(2, 3);
    std::cout << (void*)&d0 << "," << d0.member01_[0] << "," << d0.member01_[1] << std::endl;
    std::cout << (void*)&d1 << "," << d1.member01_[0] << "," << d1.member01_[1] << std::endl;
    d0 = std::move(d1);
    std::cout << (void*)&d0 << "," << d0.member01_[0] << "," << d0.member01_[1] << std::endl;
    std::cout << (void*)&d1 << "," << d1.member01_[0] << "," << d1.member01_[1] << std::endl;
}


#endif //CPPSANDBOX_STL_MOVE_TEST_H
