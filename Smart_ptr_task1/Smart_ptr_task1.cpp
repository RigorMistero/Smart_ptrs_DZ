#include <iostream>
#include <vector>
#include <memory>

class tridiagonal_matrix 
{
public:
    std::vector<double> m_down;
    std::vector<double> m_upper;
    std::vector<double> m_middle;

    tridiagonal_matrix(
        const std::vector<double>& down,
        const std::vector<double>& upper,
        const std::vector<double>& middle) :
        m_down{ down }, m_upper{ upper }, m_middle{ middle }
    {};

    ~tridiagonal_matrix() 
    {
        std::cout << "destructor called\n";
    }

    // clone() - deep copying object
    std::unique_ptr<tridiagonal_matrix> clone() const 
    {
        // unique_ptr with all copies
        return std::make_unique<tridiagonal_matrix>(m_down, m_upper, m_middle);
    }
};

int main(int argc, char** argv) 
{
    auto down = std::vector<double>{ -4.0, 5.0 };
    auto upper = std::vector<double>{ 14.0, 8.0 };
    auto middle = std::vector<double>{ 3.0, 1.0, 7.0 };

    auto matrix = std::make_unique<tridiagonal_matrix>(
        down,
        upper,
        middle
    );

    auto matrix_clone = matrix->clone();

    // checking for difference
    std::cout << "Original middle[0]: " << matrix->m_middle[0] << std::endl;
    std::cout << "Clone middle[0]: " << matrix_clone->m_middle[0] << std::endl;

    // changing clone no changing original 
    matrix_clone->m_middle[0] = 100.0;
    std::cout << "After modification:" << std::endl;
    std::cout << "Original middle[0]: " << matrix->m_middle[0] << std::endl;
    std::cout << "Clone middle[0]: " << matrix_clone->m_middle[0] << std::endl;

    return EXIT_SUCCESS;
}