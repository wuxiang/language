#include <valarray>

class Student
{
    private:
        typedef std::valarray<int>  ArrayInt;
        ArrayInt   m_score;
};

int main()
{
    Student student;
    return true;
}
