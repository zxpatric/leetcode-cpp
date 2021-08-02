//
// Created by zxpat on 1/11/2020.
//

#ifndef CPPSANDBOX_SHAREDPOINTER_H
#define CPPSANDBOX_SHAREDPOINTER_H

#include <cstdint>

struct Foo {
    Foo() { std::cout << "Foo...\n"; }
    ~Foo() { std::cout << "~Foo...\n"; }
};

struct D {
    void operator()(Foo* p) const {
        std::cout << "Call delete from function object...\n";
        delete p;
    }
};

template <typename T>
class SharedPointer
{
private:
    T* the_ptr_;
    uint32_t* ref_count_ptr_;
    uint32_t ref_count_;

//    void operator()(T* p) const deleter_;
public:
    SharedPointer(): ref_count_(1), ref_count_ptr_(&ref_count_), the_ptr_(new T())
    {

    }

    SharedPointer(T* ptr) : ref_count_(1), ref_count_ptr_(&ref_count_), the_ptr_(ptr)
    {

    }

//    template<typename Y, typename Deleter>
//    SharedPointer(Y* ptr, Deleter d ) : SharedPointer<Y>(ptr), deleter_(d)
//    {
//        ;
//    }

    virtual ~SharedPointer()
    {
        --*ref_count_ptr_;
        if(*ref_count_ptr_ == 0)
        {
            delete the_ptr_;
        }
    }

    SharedPointer(const SharedPointer& sptr)noexcept
    {
        this->the_ptr_ = sptr.the_ptr_;
        this->ref_count_ptr_ = sptr.ref_count_ptr_;
        ++*this->ref_count_ptr_;
    }

    SharedPointer& operator=(const SharedPointer& sptr)
    {
        this->~SharedPointer();

        this->the_ptr_ = sptr.the_ptr_;
        this->ref_count_ptr_ = sptr.ref_count_ptr_;
        ++*this->ref_count_ptr_;
        return *this;
    }

    SharedPointer(const SharedPointer&& sptr)
    {
        this->the_ptr_ = sptr.the_ptr_;
        this->ref_count_ptr_ = sptr.ref_count_ptr_;
        ++*this->ref_count_ptr_;
    }

    SharedPointer& operator=(const SharedPointer&& sptr)
    {
        this->~SharedPointer();

        this->the_ptr_ = sptr.the_ptr_;
        this->ref_count_ptr_ = sptr.ref_count_ptr_;
        ++*this->ref_count_ptr_;
        return *this;
    }

    void reset(T* ptr)
    {
        this->~SharedPointer();

        the_ptr_ = ptr;
        ref_count_ = 1;
        ref_count_ptr_ = &ref_count_;
    }

    inline T* get() const
    {
        return the_ptr_;
    }

    uint32_t use_count() const noexcept{
        return *ref_count_ptr_;
    }

    bool unique() const
    {
        return *ref_count_ptr_ == 1;
    }

    T& operator*(){
        return *the_ptr_;
    }

    T* operator->() const noexcept
    {
        return the_ptr_;
    }
};

//template<typename T>
//SharedPointer<T> make_shared(Args args)
//{
//
//}

#include <memory>

void test_sharedPointer()
{
    {
        std::cout << "constructor with no managed object\n";
        SharedPointer<Foo> sh1;
    }

    {
        std::cout << "constructor with object\n";
        SharedPointer<Foo> sh2(new Foo);
        SharedPointer<Foo> sh3(sh2);
        std::cout << sh2.use_count() << '\n';
        std::cout << sh3.use_count() << '\n';
    }

    // test the class with deleter
    {
        std::cout << "constructor with object and deleter\n";
        std::shared_ptr<Foo> sh4(new Foo, D());
        std::shared_ptr<Foo> sh5(new Foo, [](auto p) {
            std::cout << "Call delete from lambda...\n";
            delete p;
        });
    }
}

#endif //CPPSANDBOX_SHAREDPOINTER_H
