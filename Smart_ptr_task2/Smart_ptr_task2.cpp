#include <iostream>
#include <memory>

class node 
{
public:
    int m_value;
    std::weak_ptr<node> parent; // Changed to weak_ptr

    node(int value) : m_value{ value } {}

    ~node() 
    {
        std::cout << "destructor called\n";
    }
};

int main(int argc, char** argv) 
{
    {
        auto node1 = std::make_shared<node>(1);
        auto node2 = std::make_shared<node>(2);

        node1->parent = node2;  // weak_ptr can be assigned shared_ptr
        node2->parent = node1;  // weak_ptr can be assigned shared_ptr
    }

    return EXIT_SUCCESS;
}