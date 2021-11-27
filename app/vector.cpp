#include <algorithm>
#include <atomic>
#include <fstream>
#include <gtest/gtest.h>
#include <exception>
#include <initializer_list>
#include <iostream>
#include <istream>
#include <memory>
#include <ostream>
#include <string>
#include <vector>
#include <cstdlib>


template<typename T>
class Container
{
public:

    virtual T& operator[](int) = 0;
    virtual const T& operator[](int) const = 0;
    virtual int size() const = 0;
    virtual ~Container() {};

    Container(){};
    Container& operator=(Container& vec) = delete;
    Container& operator=(Container&& vec) = delete;
    Container(Container&) = delete;
    Container(Container&&) = delete;

};

template<typename T, int N>
struct Buffer
{
    using value_type = T;
    constexpr int size() const { return N; }
    T* data = new T[N];
};

template<typename T>
class Vector : public Container<T>
{
private:
    int _size;
    int _capacity;
    T* _data;
public:
    using value_type = T;
    explicit Vector(int i);
    Vector();
    Vector(std::initializer_list<T> list_);
    ~Vector();
    Vector(Vector&& vec_);
    Vector& operator=(Vector&& vec_);
    Vector(const Vector& vec_);
    Vector& operator=(const Vector& vec_);
    int size() const override;
    int capacity() const;
    void reserve(int num_);
    virtual T& operator[](int i) override;
    virtual const T& operator[](int i) const override;
    void push_back(T elem_);
    T* begin() const;
    T* end() const;
};


template<typename T>
Vector<T>::Vector(int sz)
:   _size(sz)
,   _capacity(2*sz)
,   _data(new T[sz])
{
    if (sz < 0)
        throw std::length_error{"Invalid length for vector."};
    for (int i(0); i<_size; i++)
        _data[i] = 0;
}

template<typename T>
Vector<T>::Vector()
:   _size(0)
,   _capacity(8)
,   _data(new T[0])
{}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> list_)
:   _size(list_.size())
,   _capacity(2*list_.size())
,   _data(new T[list_.size()])
{
    std::copy(list_.begin(), list_.end(), _data);
}

template<typename T>
Vector<T>::~Vector()
{
    delete[] _data;
}

template<typename T>
Vector<T>::Vector(const Vector<T>& vec_)
:   Container<T>()   
,   _size(vec_.size())
,   _capacity(vec_.capacity())
,   _data(new T[_size])
{
    for (int i(0); i < _size; i++)
        _data[i] = vec_[i]; 
}

template<typename T>
Vector<T>::Vector(Vector<T>&& vec_)
:   _size(vec_._size)
,   _capacity(vec_._capacity)
,   _data(vec_._data)
{
    vec_._size = 0;
    vec_._data = nullptr;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& vec_)
{
    return vec_;
}

template<typename T>
void Vector<T>::reserve(int size_)
{
    if (_capacity > size_)
        return;
    T* newData = new T[size_];
    for (int i(0); i < size_; i++)
        newData[i] = _data[i];
    delete[] _data;
    _data = newData;
    _capacity = size_;
}

template<typename T>
void Vector<T>::push_back(T elem_)
{
    if (capacity() < size() + 1)
        reserve(size() == 0 ? 8 : 2 * size());
    _data[++_size] = elem_;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& vec_)
{
    T* p = new T[vec_.size()];
    for (int i(0); i < vec_.size(); i++)
        p[i] = vec_[i];
    delete[] _data;
    _data = p;
    _size = vec_.size();
    return *this;
}

template<typename T>
int Vector<T>::size() const
{
    return _size;
}

template<typename T>
int Vector<T>::capacity() const
{
    return _capacity;
}

TEST(vector, capacity)
{
    Vector<int> vec = {1,2,3,4};
    vec.reserve(5);
    std::cout << "capcacity=" << vec.capacity() << " size=" << vec.size() << '\n';
    vec.push_back(1);
    vec.push_back(1);
    std::cout << "capcacity=" << vec.capacity() << " size=" << vec.size() << '\n';
    vec.reserve(8);
    std::cout << "capcacity=" << vec.capacity() << " size=" << vec.size() << '\n';
}

template<typename T>
T& Vector<T>::operator[](int i)
{
    return _data[i];
}

template<typename T>
const T& Vector<T>::operator[](int i) const
{
    return _data[i];
}

template<typename T>
T* Vector<T>::begin() const
{
    return size() ? &_data[0] : nullptr;
}

template<typename T>
T* Vector<T>::end() const
{
    return size() ? &_data[_size] : nullptr;
}

template<typename T>
void print(T t)
{
    std::cout << t << ' ';
}

void variadic_func()
{
    std::cout << '\n';
}

template<typename T, typename... S>
void variadic_func(T t, S... s)
{
    print(t);
    variadic_func(s...);
}

TEST(Variadic_template, example)
{
    variadic_func("Hello", "world", "Hi", "there", "You", "can", "pass", "as", "many","arguments", "as", 1, "may", "like");    
}

TEST(Vector, test_size)
{
    Vector<double>* vec_p = new Vector<double>(10);
    EXPECT_EQ(vec_p->size(), 10);
}

TEST(Vector, add_elements)
{

}

TEST(misc, declare_in_if_statement)
{
    Container<double>* c = new Vector<double>();
    if (Vector<double>* pv = dynamic_cast<Vector<double>*>(c))
    {
        pv->push_back(2.2);
    }
}

TEST(Vector, range_based_loop)
{
    Vector<std::string> vec = {"Hello", "World"};
    for(const std::string& st : vec)
        std::cout << st << '\n';
}

TEST(misc, array)
{
    double* arr = new double[10];
    for (int i(0); i < 10; i++)
    {
        if (arr[i])
            std::cout << arr[i] << '\n';
        else
            arr[i] = 0;
    }
    for (int i(0); i < 10; i++)
    {
        if (arr[i])
            std::cout << arr[i] << '\n';
    }
}

class Entry
{
private:
    std::string _name;
    int _number;
public:
    Entry(std::string name_, int number_)
    :   _name(name_)
    ,   _number(number_)
    {}
    Entry()
    :   _name("")
    ,   _number()
    {}
    ~Entry()
    {
    }

    int number() const { return _number; }
    std::string name() const { return _name; }
    void setnumber(int number_) { _number = number_; }
    void setname(const std::string& name_) { _name = name_; }

    Entry(const Entry&& entry_)
    :   _name(entry_.name())
    ,   _number(entry_.number())
    {
        std::cout << "Move!\n";
    }

    
    Entry(const Entry& entry_)
    :   _name(entry_.name())
    ,   _number(entry_.number())
    {
        std::cout << "Move!\n";
    }

    Entry& operator=(Entry&& entry_)
    {
        std::cout << "Move operator!\n";
        return entry_;
    }
};


TEST(Entry, move)
{
    auto names_file = std::fstream("names.txt");
    std::string name_buffer;
    std::vector<std::unique_ptr<Entry>> phone_book;  
    while(std::getline(names_file, name_buffer))
    { 
        int num = rand() % 100;
        phone_book.emplace_back(new Entry(name_buffer, num));
    }
    std::vector<std::unique_ptr<Entry>> new_book;
    auto it = phone_book.begin();
    for (std::unique_ptr<Entry>& entry : phone_book)
    {
        new_book.push_back(std::move(entry));
        new_book.erase(it);
    }
    int count(0);
    for (auto& old : phone_book)
    {
        if (old)
            ++count;
    }
    std::cout << "not null in old=" << count << '\n';
    std::cout << "new_book.size()=" << new_book.size() << '\n';
    std::cout << "phone_book.size()=" << phone_book.size() << '\n';
    std::cout << "test fin\n";
}

TEST(iterators, back_inserter)
{
  std::vector<int> foo,bar;
  for (int i=1; i<=5; i++)
  { foo.push_back(i); bar.push_back(i*10); }

  std::move(bar.begin(),bar.end(),back_inserter(foo));

  std::cout << "foo contains:";
  for ( std::vector<int>::iterator it = foo.begin(); it!= foo.end(); ++it )
	  std::cout << ' ' << *it;
  std::cout << '\n';
  std::cout << "bar containers:";
  for (auto i : bar)
      std::cout << ' ' << i;
  std::cout << '\n';
}

std::ostream& operator<<(std::ostream& os_, const Entry& entry_)
{
    return os_ << "{\"" << entry_.name() << "\": " << entry_.number() << "}\n";
}

std::istream& operator>>(std::istream& is_, Entry& entry_)
{
    char c1, c2;
    std::string name;
    if (is_ >> c1 and c1 == '{' and is_ >> c2 and c2 == '"')
    {
        while (is_.get(c1) && c1 != '"')
            name += c1;
    }
    int number;
    if (is_ >> number >> c1 && c2 == '}')
    {
        entry_.setname(name);
        entry_.setnumber(number);
        return is_;
    }
    is_.setstate(std::istream::failbit);
    return is_;
}


TEST(fstreams, test)
{
    auto ofs = std::ofstream("out.txt", std::ofstream::app);
    if (ofs)
        std::cout << "open file\n";
    ofs << "Hello world";
}

 


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

