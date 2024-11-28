Операторы программы, при выполнении которых необходимо обеспечить обработку исключений, выделяются в try-catch-блок.

```
#include <iostream>
#include <stdexcept>

void divide(int a, int b) {
    if (b == 0)
        throw std::runtime_error("Деление на ноль!");
    std::cout << "Результат: " << a / b << std::endl;
}

int main() {
    try {
        divide(10, 0);
    } catch (const std::runtime_error& e) {
        std::cerr << "Поймано исключение: " << e.what() << std::endl;
    }
    return 0;
}

```

Если ошибка произошла внутри try-блока (в частности, в вызываемых из try-блока функциях), то соответствующее исключение должно генерироваться с помощью операции throw (ее приоритет ниже, чем у «=», но выше, чем у «,»), а перехватываться и обрабатываться в теле одного из обработчиков catch, которые располагаются непосредственно за try-блоком

``throw прописывается там же в try

```
class A {
	public:
		A () {cout << "Constructor of A\n";}
		~A () {cout << "Destructor of A\n";}
	};
	class Error {};
	class Error_of_A : public Error {};
	
void f () {
	A a;
	throw 1;
	cout << "This message is never printed" << endl;
}

int main () {
	try {
		f ();
		throw Error_of_A();
	}
	catch (int) { cerr << "Catch of int\n"; }
	catch (Error_of_A) { cerr << "Catch of Error_of_A\n"; }
	catch (Error) { cerr << "Catch of Error\n"; }
	return 0;
}

Constructor of A
Destructor of A
Catch of int
```

### Механизм RTTI (Run-Time Type Identification)

Механизм RTTI состоит из трех частей: 

1. операция dynamic_cast в основном предназначена для получения указателя на объект производного класса при наличии указателя на объект полиморфного базового класса 

2. операция typeid служит для идентификации точного типа объекта при наличии указателя на полиморфный базовый класс

3. структура type_info позволяет получить дополнительную информацию, ассоциированную с типом Для использования RTTI в программу следует включить заголовок


[иерархия классов](photo/20241112120314.png)
[пример использования](photo/20241112120323.png)
