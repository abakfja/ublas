//
// Created by fragrant on 4/14/21.
//

#include <boost/numeric/ublas/matrix/vector.hpp>
#include <iostream>

using namespace boost::numeric::ublas::experimental;

int main() {
    using fvector3 = fvector<int, 3>;

    dvector<int> a{1,2,3};

    fvector3 b{1,2,3};

    a = a + b * 2 + b * 3; // linear combination

    std::cout << (a == b * 6) << std::endl;
}