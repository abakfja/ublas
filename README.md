Boost Linear and Multilinear Algebra Library 
=====
# Google summer of Code project: uBlas

- Fork [uBlas](https://github.com/boostorg/ublas) and use the `develop` branch for your implementation

  - :white_check_mark:

- Create a `matrix` folder in

  - `include/boost/numeric/ublas` for your implementation
  - `test` for the unit-tests
  - `examples` for the QR decomposition example
    - :white_check_mark:

- Provide a new `matrix` and `vector` C++17 implementation:

- :white_check_mark: A `matrix<Engine>` implementation and a `vector<Engine, Layout>`. The `Engine` is the data owning object whose size can be declared both at compile time and run-time. 

- Provide following functionality:

  - `A = zeros(3,2);`

    - :white_check_mark: A similar function `dmatrix::zeros(r, c)` is provided

  - `C = A+B`, `C = 2*A`, etc. for element-wise matrix operations

    - :white_check_mark: Element wise  negation, addition between matrices and vectors have been provided. Also multiplication and division with scalars has also been implemented

  - `C = A*B` for matrix multiplication 

    - :white_check_mark: ​Same expression can be used for matrix multiplication. However matrix multiplication has not been implemented using expression templates due to the fact that expressions like :

      `x = A * x`

      Don't work using expression templates as value of cell depends on other cells of the matrix as well, However with modern c++'s copy elision the performance hit might not be too hard.

  - `C = A'` for matrix transposition

    - :white_check_mark: A helper function `transpose()` has bee provided 

  - `A==B` for element-wise comparison

    - :white_check_mark: ​Comparison operators for both matrix and vector have been provided

  - `c = A[3]` for accessing elements with a single zero-based index

    - :white_check_mark: Index operator has been provided currently only row-major layout is supported. 

  - `c = A(3,2)` or `A(3,5) = c` for accessing elements with a two zero-based indices

    - :white_check_mark: The following operators have been provided by overloading the `()` operator​

  - `C = A(1:2,1:3)` to generate a `matrix` instance that contains data of `A` referenced by the ranges `1:2` and `1:3`

    - :white_check_mark: Such an operation leads to creation read/write non owning view.​

- Use the C++ standard library for your matrix implementation wherever possible (e.g. use `std::tuple` and `std::tie`)

  - :white_check_mark: Extensive use of modern c++ STL functions and types has been done while implementing the classes​

- Implement auxiliary types such as `range`/`span` and helper functions such as `zeros`, `size`, `norm` to offer maximum readability

  - :white_check_mark: `span` has been implemented
  - :white_check_mark: `zeros` has been implemented
  - :white_check_mark: `size` has been implemented as a member function
  - :white_check_mark: `norm​` has been implemented

- Modify the `README.md` for Github Actions usage

  - :white_check_mark: ​Both the Github Actions and the `README.md` have been updated to include the new `matrix` folders and types that have been created.

- Implement a C++ `qr` function QR-decomposing a matrix with a **minimal number of code lines** based on the following Matlab code

```matlab
function [Q,R] = qr(A)
  [m, n] = size(A);
  Q = zeros(m,n);
  R = zeros(n,n);
  for k = 1:n
    R(1:k-1,k) = Q(:,1:k-1)' * A(:,k);
    v = A(:,k) - Q(:,1:k-1) * R(1:k-1,k);
    R(k,k) = norm(v);
    Q(:,k) = v / R(k,k);
  end
end
```

  - :white_check_mark: ​Here is the function using the above constructs(One could go for further reduction in lines using std::copy but that would take away from the readability of code): 

```c++
template<typename T>
auto qr(dmatrix<T> A) {
    auto[m, n] = A.size();
    auto Q = zeros<T>(m, n);
    auto R = zeros<T>(n, n);
    for (std::size_t k = 0; k < n; k++) {
        dmatrix<T> v = A({0, m}, k);
        if (k > 0) {
            R({0, k}, k) = transpose(Q({0, m}, {0, k})) * A({0, m}, k);
            v = A({0, m}, k) - Q({0, m}, {0, k}) * R({0, k}, k);
        }
        R(k, k) = norm<float>(v);
        Q({0, m}, k) = v / R(k, k);
    }
    return std::make_pair(Q, R);
}

```

* Implement a C++ `main` function showing with`A == Q*R` that your `qr` decomposition works correctly
  * :white_check_mark: ​The file `example/matrix/qr_decomposition.cpp` contains the aforementioned function


[![Language](https://img.shields.io/badge/C%2B%2B-11-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization)
[![License](https://img.shields.io/badge/license-BSL-blue.svg)](https://opensource.org/licenses/BSL-1.0)
[![Documentation](https://img.shields.io/badge/ublas-documentation-blue.svg)](https://www.boost.org/doc/libs/1_69_0/libs/numeric/ublas/doc/index.html)
[![Wiki](https://img.shields.io/badge/ublas-wiki-blue.svg)](https://github.com/boostorg/ublas/wiki)
[![Mailing List](https://img.shields.io/badge/ublas-mailing%20list-4eb899.svg)](https://lists.boost.org/mailman/listinfo.cgi/ublas)
[![Gitter](https://img.shields.io/badge/ublas-chat%20on%20gitter-4eb899.svg)](https://gitter.im/boostorg/ublas)

**Boost.uBLAS** is part of the [Boost C++ Libraries](http://github.com/boostorg). It is directed towards scientific computing on the level of basic linear and multilinear algebra operations with tensors, matrices and vectors. 


## Documentation 
uBLAS is documented at [boost.org](https://www.boost.org/doc/libs/1_69_0/libs/numeric/ublas/doc/index.html).
The tensor extension has also a [wiki page](https://github.com/BoostGSoC18/tensor/wiki).

## License
Distributed under the [Boost Software License, Version 1.0](http://www.boost.org/LICENSE_1_0.txt).

## Properties
* Header-only
* Tensor extension requires C++17 compatible compiler
* Unit-tests require Boost.Test

## Build Status


#### Tensor and Matrix Build & Test

|      Operating System       |      Compiler       |  [`master`](https://github.com/boostorg/ublas/tree/master)   | [`develop`](https://github.com/boostorg/ublas/tree/develop)  |
| :-------------------------: | :-----------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
| Linux (Ubuntu 20.04 x86_64) |  gcc-{7, 8, 9, 10}  | [![Linux GCC Debug](https://github.com/boostorg/ublas/workflows/Linux%20GCC%20Debug/badge.svg?branch=master)](https://github.com/boostorg/ublas/actions?query=workflow%3A%22Linux+GCC%22+branch%3Amaster) | [![Linux GCC Debug](https://github.com/boostorg/ublas/workflows/Linux%20GCC%20Debug/badge.svg?branch=develop)](https://github.com/boostorg/ublas/actions?query=workflow%3A%22Linux+GCC%22+branch%3Adevelop) |
| Linux (Ubuntu 20.04 x86_64) | clang-{6, 8, 9, 10} | [![Linux Clang Release](https://github.com/boostorg/ublas/workflows/Linux%20Clang%20Release/badge.svg?branch=master)](https://github.com/boostorg/ublas/actions?query=workflow%3A%22Linux+Clang%22+branch%3Amaster) | [![Linux Clang Release](https://github.com/boostorg/ublas/workflows/Linux%20Clang%20Release/badge.svg?branch=develop)](https://github.com/boostorg/ublas/actions?query=workflow%3A%22Linux+Clang%22+branch%3Adevelop) |
|     Windows 10 (x86_64)     | msvc-{14.16, 14.26} | [![Windows MSVC](https://github.com/boostorg/ublas/workflows/Windows%20MSVC/badge.svg?branch=master)](https://github.com/boostorg/ublas/actions?query=workflow%3A%22Windows+MSVC%22+branch%3Amaster) | [![Windows MSVC](https://github.com/boostorg/ublas/workflows/Windows%20MSVC/badge.svg?branch=develop)](https://github.com/boostorg/ublas/actions?query=workflow%3A%22Windows+MSVC%22+branch%3Adevelop) |
|   MacOS Catalina (x86_64)   |      clang-11       | [![Apple Clang](https://github.com/boostorg/ublas/workflows/Apple%20Clang/badge.svg?branch=master)](https://github.com/boostorg/ublas/actions?query=workflow%3A%22Apple+Clang%22+branch%3Amaster) | [![Apple Clang](https://github.com/boostorg/ublas/workflows/Apple%20Clang/badge.svg?branch=develop)](https://github.com/boostorg/ublas/actions?query=workflow%3A%22Apple+Clang%22+branch%3Adevelop) |

#### Tensor and Matrix Additional Checks

|    Checks     |  [`master`](https://github.com/boostorg/ublas/tree/master)   | [`develop`](https://github.com/boostorg/ublas/tree/develop)  |
| :-----------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
| UB Sanitizer  | [![Undefined Behaviour Sanitizer](https://github.com/boostorg/ublas/workflows/Undefined%20Behaviour%20Sanitizer/badge.svg?branch=master)](https://github.com/boostorg/ublas/actions?query=workflow%3A%22Undefined+Behaviour+Sanitizer%22+branch%3Amaster) | [![Undefined Behaviour Sanitizer](https://github.com/boostorg/ublas/workflows/Undefined%20Behaviour%20Sanitizer/badge.svg?branch=develop)](https://github.com/boostorg/ublas/actions?query=workflow%3A%22Undefined+Behaviour+Sanitizer%22+branch%3Adevelop) |
| TH Sanitizer  | [![Thread Sanitizer](https://github.com/boostorg/ublas/workflows/Thread%20Sanitizer/badge.svg?branch=master)](https://github.com/boostorg/ublas/actions?query=workflow%3A%22Thread+Sanitizer%22+branch%3Amaster) | [![Thread Sanitizer](https://github.com/boostorg/ublas/workflows/Thread%20Sanitizer/badge.svg?branch=develop)](https://github.com/boostorg/ublas/actions?query=workflow%3A%22Thread+Sanitizer%22+branch%3Adevelop) |
| ADD Sanitizer | [![Address Sanitizer](https://github.com/boostorg/ublas/workflows/Address%20Sanitizer/badge.svg?branch=master)](https://github.com/boostorg/ublas/actions?query=workflow%3A%22Address+Sanitizer%22+branch%3Amaster) | [![Address Sanitizer](https://github.com/boostorg/ublas/workflows/Address%20Sanitizer/badge.svg?branch=develop)](https://github.com/boostorg/ublas/actions?query=workflow%3A%22Address+Sanitizer%22+branch%3Adevelop) |
|    Codecov    | [![codecov](https://codecov.io/gh/boostorg/ublas/branch/master/graph/badge.svg)](https://codecov.io/gh/boostorg/ublas/branch/master) | [![codecov](https://codecov.io/gh/boostorg/ublas/branch/develop/graph/badge.svg)](https://codecov.io/gh/boostorg/ublas/branch/develop) |
| Clang-Format  | [![Code Format](https://github.com/boostorg/ublas/workflows/Code%20Format/badge.svg?branch=master)](https://github.com/boostorg/ublas/actions?query=workflow%3A%22Code+Format%22+branch%3Amaster) | [![Code Format](https://github.com/boostorg/ublas/workflows/Code%20Format/badge.svg?branch=develop)](https://github.com/boostorg/ublas/actions?query=workflow%3A%22Code+Format%22+branch%3Adevelop) |
|  Clang-Tidy   | [![Clang tidy checks](https://github.com/boostorg/ublas/workflows/Clang%20tidy%20checks/badge.svg?branch=master)](https://github.com/boostorg/ublas/actions?query=workflow%3A%22Clang+tidy+checks%22+branch%3Amaster) | [![Clang tidy checks](https://github.com/boostorg/ublas/workflows/Clang%20tidy%20checks/badge.svg?branch=develop)](https://github.com/boostorg/ublas/actions?query=workflow%3A%22Clang+tidy+checks%22+branch%3Adevelop) |

#### Tensor and Matrix Build Information

|         OS         |    Toolchain    |                  Compiler Flags                   |
| :----------------: | :-------------: | :-----------------------------------------------: |
| Linux Ubuntu 20.04 |       GCC       |                       `-O0`                       |
| Linux Ubuntu 20.04 |      Clang      |                       `-O3`                       |
|     Windows 10     |      MSVC       |                 No Special Flags                  |
|   MacOS Catalina   |      Clang      |                 No Special Flags                  |
|    UB Sanitizer    |  GCC and Clang  |            `"-g -fsanitize=undefined"`            |
|    TH Sanitizer    |  GCC and Clang  |           `"-g -fsanitize=thread -O2"`            |
|   ADD Sanitizer    |  GCC and Clang  | `"-g -fsanitize=address -fno-omit-frame-pointer"` |
|     Clang Tidy     |  Clang-Tidy-10  |         [Configuration File](.clang-tidy)         |
|    Clang Format    | Clang-Format-10 |        [Configuration File](.clang-format)        |

#### uBLAS CI

Branch  | Travis | Appveyor  | Regression  | Docs  
:-----: | ------ | --------- | ----------- | ----- 
  [`master`](https://github.com/boostorg/ublas/tree/master)   | [![Build Status](https://travis-ci.org/boostorg/ublas.svg?branch=master)](https://travis-ci.org/boostorg/ublas) | [![Build status](https://ci.appveyor.com/api/projects/status/ctu3wnfowa627ful/branch/master?svg=true)](https://ci.appveyor.com/project/stefanseefeld/ublas/branch/master) | [![ublas](https://img.shields.io/badge/ublas-master-blue.svg)](https://www.boost.org/development/tests/master/developer/numeric-ublas.html) | [![Documentation](https://img.shields.io/badge/docs-develop-brightgreen.svg)](http://www.boost.org/doc/libs/release/libs/numeric) 
 [`develop`](https://github.com/boostorg/ublas/tree/develop)  | [![Build Status](https://travis-ci.org/boostorg/ublas.svg?branch=develop)](https://travis-ci.org/boostorg/ublas) | [![Build status](https://ci.appveyor.com/api/projects/status/ctu3wnfowa627ful/branch/develop?svg=true)](https://ci.appveyor.com/project/stefanseefeld/ublas/branch/develop) | [![ublas](https://img.shields.io/badge/ublas-develop-blue.svg)](https://www.boost.org/development/tests/develop/developer/numeric-ublas.html) | [![Documentation](https://img.shields.io/badge/docs-develop-brightgreen.svg)](http://www.boost.org/doc/libs/release/libs/numeric) 

## Directories

| Name         | Purpose                 |
| ------------ | ----------------------- |
| `doc`        | documentation           |
| `examples`   | example files           |
| `include`    | headers                 |
| `test`       | unit tests              |
| `benchmarks` | timing and benchmarking |

## More information

* If you would like to test the library, contribute new feature or a bug fix, see [contribution](https://github.com/boostorg/ublas/wiki/Guidelines-for-Contribution) where the whole development infrastructure and the contributing workflow is explained in details.
* Ask questions in [stackoverflow](http://stackoverflow.com/questions/ask?tags=c%2B%2B,boost,boost-ublas) with `boost-ublas` or `ublas` tags.
* Report [bugs](https://github.com/boostorg/ublas/issues) and be sure to mention Boost version, platform and compiler you're using. A small compilable code sample to reproduce the problem is always good as well.
* Submit your patches as pull requests against **develop** branch. Note that by submitting patches you agree to license your modifications under the [Boost Software License, Version 1.0](http://www.boost.org/LICENSE_1_0.txt).
* Developer discussions about the library are held on the [Boost developers mailing list](https://lists.boost.org/mailman/listinfo.cgi/ublas). Be sure to read the [discussion policy](http://www.boost.org/community/policy.html) before posting and add the `[ublas]` tag at the beginning of the subject line
* For any other questions, you can contact David, Stefan or Cem: david.bellot-AT-gmail-DOT-com, cem.bassoy-AT-gmail-DOT-com stefan-AT-seefeld-DOT-name
