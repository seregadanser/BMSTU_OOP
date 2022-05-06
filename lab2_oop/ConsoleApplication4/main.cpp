#include <iostream>

#include "Vector.h"
#include "errors.h"

int main()
{
    try
    {
        std::cout << "Test constructs\n\n";

        Vector<double> v1;
        std::cout << "Def constract\n";
        std::cout << v1 << "\n";

        std::cout << "Param Construct\n";
        Vector<double> v2(2, 3., 4.);
        Vector<double> v3(3, 3.0, 4.0, 0.0);
        std::cout << v2 << "\n" << v3 << "\n";

        double arr[5] = { 5, 1, 7, 4, 0 };
        Vector<double> v4(5, arr);
        std::cout << v4 << "\n";

        std::cout << "Copy construct\n";
        Vector<double> v5(v3);
        std::cout << v5 << "\n";

        std::cout << "Iter construct\n";
        int size = 5;
        const char* str = "abcdef";
        Vector<char> vector_1(size, str);
        Vector<char> vector_2(vector_1.cbegin() + 1, vector_1.cend() - 1);
        std::cout << vector_2 << "\n";


        std::cout << "--------------------------------\n";
        std::cout << "Methods\n\n";

        std::cout << "Len 3 element (3, 4, 0): " << v3.Len() << "\n";
        std::cout << "Size 3 element (3, 4, 0): " << v3.size() << "\n";
        std::cout << "Empty Vector default?  " << v1 << "\n\n";
        std::cout << "output second element {5, 1, 7, 4, 0}: " << v4.GetElement(1) << "\n";

        std::cout << "Mult Vector elements to 10: " << (v4 *= 10) << "\n";
        std::cout << "Division to 10: " << (v4 /= 10) << "\n";
        std::cout << "Subbmision from {5, 1, 7, 4, 0} a {3, 4, 0}: " << (v4 -= v3) << "\n";


        std::cout << "Unary minus {3, 4, 0}: " << (-v3) << "\n";
        std::cout << "Unary minus {3, 4, 0}: " << (v3.neg()) << "\n\n";

        Vector<double> v12{1., 2., 3., 4., 5. };
        std::cout << "Init Vector {1., 2., 3., 4., 5.}: " << v12 << "\n";
        v12[2] = 10.;
        std::cout << "Change third element to 10 with []: " << v12 << "\n";
        v12.SetElement(3, 11.);
        std::cout << "Change thourth element to 11 with method set_elem_Vector: " << v12 << "\n";
        v12 = v12.GetSingle();
        std::cout << "Unary Vector: " << v12 << "\n\n";

        Vector<double> v6(3, 3.0, 4.0, 0.0);
        std::cout << "Vector mul {3,4,0} and {3,4,0}: " << (v3 ^ v6) << "\n";
        Vector<int> v7(2, 10, 0);
        Vector<int> v8(2, 0, 10);
        std::cout << "Angle beetwen vectors {10, 0} and {0, 10}: " << v7.Angle(v8) << "\n";
        Vector<double> v9(2, 5., 5.);
        Vector<double> v10(2, 10., 0.0);
        std::cout << "Angle beetwen vectors {5, 5} and {10, 0}: " << v9.Angle(v10) << "\n";
        Vector<double> v20(2, 20., 20.0);
        std::cout << "Vectors {5, 5} and {20, 20} is colinearity? : " << v9.IsCollinearity(v20) << "\n";
        std::cout << " vectors {10, 0} and {0, 10} is ortoganality? : " << v7.IsOrthogonality(v8) << "\n";
        std::cout << "scalar mul {5, 5} and {10, 0}: " << v9 * v10 << "\n\n";

        Vector<int> v11(4, 1, 0, 0, 0);
        std::cout << "Vectors {4, 1, 0, 0, 0} is unary? " << v11.IsSingle() << "\n";
        std::cout << "Vectors {3, 4, 0} and {3, 4, 0} is eq? " << (v3 == v6) << "\n";
        std::cout << "Vectors {3, 4, 0} and {3, 4, 0} is not eq? " << (v3 != v6) << "\n";
        std::cout << "Vectors {3, 4, 0} and {3, 4, 0} is eq? " << (v3.IsEqual(v6)) << "\n";
        std::cout << "Vectors {3, 4, 0} and {3, 4, 0} is not eq? " << (v3.IsNotEqual(v6)) << "\n";
        v3 / 0;
    }
    catch (BaseErrors& err)
    {
        std::cout << err.what() << std::endl;
    }
}