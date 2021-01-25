//									Выражения свертки
// 2.Функция, которая добавляет произвольное количество параметров в контейнер std::set
// и возвращает булево значение, показывающее,успешно ли прошла операция. Контейнер,
// для которого решается задача, должен быть параметризован собственным классом, например, KRat.

#include <iostream>
#include <set>
#include <map>
#include <vector>

using namespace std;

class student
{
public:
	student(int _age,string _name):age(_age),surname(_name){}
	bool operator <(const student& st2)const
	{
		return this->surname < st2.surname;
	}
	friend ostream& operator <<(ostream& out, student& st)
	{
		out << st.surname << " " << st.age;
		return out;
	}
private:
	int age;
	string surname;
};

//возвращает true, только если удалось добавить все аргументы
template <typename T,typename ...Args>
bool set_insert(set<T>& s,Args ... args)
{
	return (s.insert(args).second && ...);
}

template <typename T>
void container_print(T & c)
{
	for (auto i : c)
		cout << i << "\t";
}

namespace std
{
	template<typename T,typename U>
	ostream& operator <<(ostream& out, pair<T, U>& p)
	{
		return out << p.first << " " << p.second;
	}
}

int main()
{
	set<student> s;
	bool b = set_insert(s,student(17,"Cherepennikov"),student(18,"Ivanov"),student(20,"Petrov"));
	cout << boolalpha << b << endl;
	container_print(s);

}