#include "matrix_cal.h"

using namespace std;

int main(int argc, char const *argv[])
{
    vector<UINT> a1(10, 5);
    cout << "size = " << a1.size() << endl;
    vector<vector<UINT>> src{{1, 2, 3, 4, 5}, {2, 3, 4, 5, 6}, {3, 4, 5, 6, 7}, {4, 5, 6, 7, 8}, {5, 6, 7, 8, 9}, {6, 7, 8, 9, 0}};
    vector<UINT> src2 = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};
    vector<vector<UINT>> dst = NSMatrix::transposition(src);
    vector<vector<UINT>> dst2 = NSMatrix::transposition(src2);
    cout << "original matrix :" << endl;
    NSMatrix::PrintMatrix(src);
    cout << "\n\ndest matrix :" << endl;
    NSMatrix::PrintMatrix(dst);
    cout << "\n\noriginal matrix2 :" << endl;
    NSMatrix::PrintMatrix(src2);
    cout << "\n\ndest matrix2 :" << endl;
    NSMatrix::PrintMatrix(dst2);

    vector<vector<UINT>> l = {{22, 22, 33, 33}, {11, 22, 3, 3}};
    vector<vector<UINT>> r = {{1}, {2}, {2}, {3}};
    vector<vector<UINT>> res = NSMatrix::multiply(l, r);
    cout << "======================================================" << endl;
    NSMatrix::PrintMatrix(l);
    cout << "======================================================" << endl;
    NSMatrix::PrintMatrix(r);
    cout << "======================================================" << endl;
    NSMatrix::PrintMatrix(res);
    cout << "======================================================" << endl;
    return 0;
}
