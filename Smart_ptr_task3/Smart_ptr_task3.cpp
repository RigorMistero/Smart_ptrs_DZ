#include <iostream>
#include <utility>

template<typename T>
class SimpleUniquePtr 
{
private:
    T* ptr;

    // copying forbidden
    SimpleUniquePtr(const SimpleUniquePtr&) = delete;
    SimpleUniquePtr& operator=(const SimpleUniquePtr&) = delete;

public:
    // constructor taking raw pntr
    explicit SimpleUniquePtr(T* p = nullptr) : ptr(p) {}

    // moving constructor
    SimpleUniquePtr(SimpleUniquePtr&& other) noexcept : ptr(other.ptr) 
    {
        other.ptr = nullptr;
    }

    // move assign operator
    SimpleUniquePtr& operator=(SimpleUniquePtr&& other) noexcept 
    {
        if (this != &other) 
        {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // Desctrucotr
    ~SimpleUniquePtr() 
    {
        delete ptr;
    }

    // Overloaded operator * 
    T& operator*() const 
    {
        if (!ptr) 
        {
            throw std::runtime_error("Dereferencing null pointer in SimpleUniquePtr");
        }
        return *ptr;
    }

    // Overloaded operator -> for adressing elements
    T* operator->() const {
        return ptr;
    }

    // releasing 
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    // getting raw pntr
    T* get() const {
        return ptr;
    }

    // deleting ptr
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }

    explicit operator bool() const {
    return ptr != nullptr;
    }

    // ptr swapping
    void swap(SimpleUniquePtr& other) noexcept {
        std::swap(ptr, other.ptr);
    }
};


class TestClass 
{
public:
    int value;
    TestClass(int v) : value(v) 
    {
        std::cout << "TestClass constructed with value: " << value << std::endl;
    }

    ~TestClass() 
    {
        std::cout << "TestClass destroyed with value: " << value << std::endl;
    }

    void print() const 
    {
        std::cout << "Value: " << value << std::endl;
    }
};

int main(int argc, char** argv) 
{

    std::cout << "=== Testing SimpleUniquePtr ===" << std::endl;

    SimpleUniquePtr<TestClass> ptr1(new TestClass(10));

    // using operator*
    (*ptr1).print();

    // using operator->
    ptr1->print();

    // using release()
    {
        std::cout << "\nTesting release():" << std::endl;
        SimpleUniquePtr<TestClass> ptr2(new TestClass(20));
        TestClass* raw_ptr = ptr2.release();

        if (!ptr2) {
            std::cout << "ptr2 is now empty after release" << std::endl;
        }

        raw_ptr->print();
        delete raw_ptr; 
    }

    // moving test
    std::cout << "\nTesting move semantics:" << std::endl;
    {
        SimpleUniquePtr<TestClass> ptr3(new TestClass(30));
        SimpleUniquePtr<TestClass> ptr4 = std::move(ptr3);

        if (!ptr3) {
            std::cout << "ptr3 is empty after move" << std::endl;
        }

        if (ptr4) {
            std::cout << "ptr4 contains: ";
            ptr4->print();
        }
    }

    std::cout << "\nTesting reset():" << std::endl;
    {
        SimpleUniquePtr<TestClass> ptr5(new TestClass(40));
        ptr5->print();
        ptr5.reset(new TestClass(50));
        ptr5->print();
    }

    std::cout << "\n=== End of test ===" << std::endl;

    return EXIT_SUCCESS;
}