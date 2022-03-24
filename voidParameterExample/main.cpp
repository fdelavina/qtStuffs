#include <QCoreApplication>
#include <QDebug>



class TestVoid
{
public:
    TestVoid(int, double );

    int getInt();
    double getDouble();
private:
    int m_int;
    double m_double;
};

void func(void* ptr)
{
  int* p = (int*)ptr;  // cast it to an int

  // now we can use it as an int*
  *p = 5;
}

void funcForTestVoid(void* ptr)
{
  TestVoid* p = (TestVoid*)ptr;  // cast it to an int

  // now we can use it as an int*
  qInfo()<< p->getDouble();
  qInfo()<< p->getInt();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TestVoid m_test_instance = TestVoid(4,1.2);

    funcForTestVoid(&m_test_instance);

    return a.exec();
}

TestVoid::TestVoid(int _int, double _double)
{
    this->m_int = _int;
    this->m_double = _double;
}

int TestVoid::getInt()
{
    return this->m_int;
}

double TestVoid::getDouble()
{
    return this->m_double;
}
