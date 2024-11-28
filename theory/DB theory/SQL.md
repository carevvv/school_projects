
СУБД - тот кто управляет базами данных.

Виды СУБД:
- Sqlite 3
- MySQL
- Postgres

## Подключение к postgres

```
cd C:\Program Files\PostgreSQL\16\bin

psql -h localhost -U postgres -d demo

\encoding UTF8
```



## Функции самого postgres

 1. Просмотр списка баз данных
```
\l
```
 2. Просмотр списка таблиц:
```sql
\d
```
3. Подключиться к другой базе данных:
```
\c <имя_базы>
```
5. Выйти из psql
```
\q
```
7. Информация о конкретной таблице:
```sql
\d имя_таблицы
```
8. Узнать тип данных всего в бд:
```
\d+
```
## Агрегатные функции

1.   COUNT()
   Описание: Подсчитывает количество строк или ненулевых значений в указанном столбце.
   
   Пример:
```sql
	SELECT COUNT(*) AS total_employees
	FROM employees;
```
   
   Подсчитывает общее количество сотрудников.

2.  SUM()
   Описание: Вычисляет сумму значений в указанном столбце.
   
   Пример:
```sql
	SELECT SUM(salary) AS total_salary
	FROM employees;
```
   
   Считает общую сумму зарплат всех сотрудников.

3.  AVG()
  Описание: Вычисляет среднее значение указанного столбца.
```sql
	SELECT SUM(salary) AS total_salary
	FROM employees;
```

4. ### MIN() / MAX()
   Описание: Находит минимальное/максимальное значение в указанном столбце.
   
   Пример:
```sql
	SELECT MAX(salary) AS highest_salary
	FROM employees;
```
   
   
   Определяет самую высокую зарплату среди сотрудников.

---

## Строковые функции

6.  CONCAT()
   Описание: Объединяет две или более строковых выражений в одну строку.
   
   Пример:
```sql
	SELECT CONCAT(first_name, ' ', last_name) AS full_name
	FROM employees;
```
  
   
   Создает полное имя сотрудника, объединяя имя и фамилию.

7.  UPPER() / LOWER()
   Описание: Преобразует все символы строки в нижний регистр.
   
   Пример:
```sql
	SELECT LOWER(email) AS email_lower
	FROM employees;
```

   
   Преобразует электронные адреса сотрудников в нижний регистр.

9.  SUBSTRING() / SUBSTR()
   Описание: Извлекает подстроку из строки, начиная с указанной позиции.
   
   Пример:
```sql
	SELECT SUBSTRING(first_name, 1, 3) AS first_three_letters
	FROM employees;
```
   Извлекает первые три буквы из имени сотрудника.

10.  LENGTH() / LEN()
    Описание: Возвращает длину строки (количество символов).
```sql
   Пример:
    
    SELECT LENGTH(first_name) AS name_length
    FROM employees;
    
    Определяет длину имен сотрудников.
```
 
11. TRIM()
    Описание: Удаляет пробелы или другие указанные символы с начала и конца строки.
    
    Пример:
```sql
    SELECT TRIM('  John Doe  ') AS trimmed_name;
    
    Удаляет лишние пробелы вокруг строки "John Doe".

```

12.  REPLACE()
    Описание: Заменяет все вхождения одной подстроки на другую.
    
    Пример:
```sql
    SELECT REPLACE(email, '@oldmail.com', '@newmail.com') AS updated_email
    FROM employees;
    
    Замещает домен электронной почты с "@oldmail.com" на "@newmail.com".
```


13. LEFT() / RIGHT()
    Описание: Возвращает указанное количество символов из начала или конца строки.
    
    Пример:
```sql
    SELECT LEFT(phone_number, 3) AS area_code
    FROM employees;
    
    Извлекает первые три цифры номера телефона (код региона).
```
---

## Функции преобразования типов


24. CAST()`
    **Описание:** Преобразует выражение одного типа данных в другой.
    
    **Пример:**
```sql
    SELECT CAST(salary AS VARCHAR(10)) AS salary_str
    FROM employees;
    ```
    *Преобразует числовую зарплату в строковый формат.*

25. CONVERT()`
    **Описание:** Преобразует выражение одного типа данных в другой с дополнительными параметрами форматирования.
    
    **Пример:**
    ```sql
    SELECT CONVERT(VARCHAR, hire_date, 103) AS hire_date_formatted
    FROM employees;
    ```
    *Преобразует дату найма в строку с форматом "дд/мм/гггг".*

--------

## Условные и другие функции

26. CASE`
    **Описание:** Возвращает значения на основе условий, аналог конструкции `if-else`.
    
    **Пример:**
    ```sql
    SELECT first_name,
           CASE
               WHEN salary > 100000 THEN 'High'
               WHEN salary BETWEEN 50000 AND 100000 THEN 'Medium'
               ELSE 'Low'
           END AS salary_level
    FROM employees;
    ```
    *Классифицирует сотрудников по уровню зарплаты.*

27. COALESCE()`
    **Описание:** Возвращает первое ненулевое значение из списка.
    
    **Пример:**
    ```sql
    SELECT first_name, COALESCE(middle_name, 'N/A') AS middle_name
    FROM employees;
    ```
    *Выводит отчество сотрудника или "N/A", если отчества нет.*

28. NULLIF()`
    **Описание:** Возвращает `NULL`, если два выражения равны; иначе — первое выражение.
    
    **Пример:**
    ```sql
    SELECT first_name, NULLIF(department, 'Sales') AS department_nullable
    FROM employees;
    ```
    *Возвращает `NULL` для сотрудников из отдела "Sales", иначе — название отдела.*

29. DISTINCT`
    **Описание:** Убирает дубликаты строк в результате запроса.
    
    **Пример:**
    ```sql
    SELECT DISTINCT department
    FROM employees;
    ```
    *Получает список уникальных отделов.*

30. ROW_NUMBER()`
    **Описание:** Присваивает уникальный номер каждой строке в результате, основываясь на порядке.
    
    **Пример:**
```sql
    SELECT first_name, salary,
	ROW_NUMBER() OVER (ORDER BY salary DESC) AS rank
    FROM employees;
```
    *Присваивает рейтинг сотрудникам на основе зарплаты.*

---
## Взаимодействие с временем

14. GETDATE() / CURRENT_DATE
    Описание: Возвращает текущую дату и время.
    Пример:
``` sql
	SELECT GETDATE() AS current_datetime;
```

15. ### `DATEDIFF()
**Описание:** Вычисляет разницу между двумя датами в указанных единицах.
    
    **Пример:**
    ```sql
    SELECT DATEDIFF(day, hire_date, GETDATE()) AS days_employed
    FROM employees;
    ```
    *Определяет количество дней, прошедших с даты найма.*

17. ### `YEAR()`
    **Описание:** Извлекает год из даты.
    
    **Пример:**
    ```sql
    SELECT YEAR(birth_date) AS birth_year
    FROM employees;
    ```
    *Получает год рождения сотрудников.*

18. ### `MONTH()`
    **Описание:** Извлекает месяц из даты.
    
    **Пример:**
    ```sql
    SELECT MONTH(hire_date) AS hire_month
    FROM employees;
    ```
    *Определяет месяц найма сотрудников.*

19. ### `DAY()`
    **Описание:** Извлекает день из даты.
    
    **Пример:**
    ```sql
    SELECT DAY(birth_date) AS birth_day
    FROM employees;
    ```
    *Получает день рождения сотрудников.*

---

## Объединение таблиц и поиск


1. JOIN — Объединение таблиц:
	JOIN используется для объединения строк из двух или более таблиц на основе связанного между ними столбца.
	
	Типы JOIN:
	- INNER JOIN: Возвращает только те строки, которые имеют совпадающие значения в обеих таблицах.
	- LEFT (OUTER) JOIN: Возвращает все строки из левой таблицы и совпадающие строки из правой. Если нет совпадений, значения из правой будут NULL.
	- RIGHT (OUTER) JOIN: Аналогично LEFT JOIN, но возвращает все строки из правой таблицы.
	- FULL (OUTER) JOIN: Возвращает строки, когда есть совпадение в одной из таблиц.
	- NATURAL JOIN: Автоматически соединяет таблицы по совпадающим названиям столбцов
	-  CROSS JOIN: Декартово произведение
	  
	  **Пример INNER JOIN:**
```sql
	SELECT passengers.name, tickets.class
	FROM passengers
	INNER JOIN tickets ON passengers.id = tickets.passenger_id;
```

2.  GROUP BY — Группировка строк

	GROUP BY используется для группировки строк, имеющих одинаковые значения в определённых столбцах, часто вместе с агрегатными функциями.
	
	Пример:
```sql
	SELECT class, COUNT(*) as count
	FROM tickets
	GROUP BY class;
```

3.  HAVING — Фильтрация групп

	HAVING используется для фильтрации групп, созданных с помощью GROUP BY. В отличие от WHERE, который фильтрует отдельные строки, HAVING фильтрует уже сгруппированные данные.
	
	Пример:
``` sql
	SELECT class, COUNT(*) as count
	FROM tickets
	GROUP BY class
	HAVING COUNT(*) > 10;
	GROUP_BY - указывается множество столбцов;
```

---

## Линейная Алгебра

1. **Объединение (`UNION`)**: объединяет результаты двух запросов, удаляя дубликаты.
2. **Пересечение (`INTERSECT`)**: возвращает общие строки из двух запросов.
3. **Вычитание (`MINUS`/`EXCEPT`)**: возвращает строки из первого запроса, отсутствующие во втором.
4. **Проекция**: выбор определённых столбцов с помощью `SELECT`.
5. **Декартово произведение (`CROSS JOIN`)**: объединяет каждую строку одной таблицы с каждой строкой другой.
6. **Деление**(`DIVIDE`): находит записи, связанные со всеми записями в другой таблице, реализуется через подзапросы или агрегатные функции.

``` sql
	SELECT employee_id, name, department_id
	FROM bookings.employees_2023
	UNION
	SELECT employee_id, name, department_id
	FROM bookings.employees_2024;
```

## SELECT

- `WITH`
	позволяет задать один или несколько подзапросов, к которым затем можно обратиться по имени в основном запросе.  Каждый подзапрос может представлять собой оператор `SELECT`, `TABLE`, `VALUES`, `INSERT`, `UPDATE` или `DELETE`(для создания временной таблицы)
``` sql
	Пример без WITH:
	SELECT e.name, e.salary
	FROM employees e
	WHERE e.salary > (
	    SELECT AVG(salary)
	    FROM employees
	    WHERE department_id = e.department_id
	);
	
	
	
	Тот же пример с WITH:
	WITH AvgSalaryPerDept AS (
	    SELECT department_id, AVG(salary) AS avg_salary
	    FROM employees
	    GROUP BY department_id
	)
	SELECT e.name, e.salary
	FROM employees e
	JOIN AvgSalaryPerDept a ON e.department_id = a.department_id
	WHERE e.salary > a.avg_salary;
```

 - Предложение `GROUP BY`, `Having`
	`GROUP BY` собирает в одну строку все выбранные строки, выдающие одинаковые значения для выражений группировки
	
	`HAVING` исключает из результата строки групп, не удовлетворяющих условию. `HAVING` отличается от `WHERE`: `WHERE` фильтрует отдельные строки до применения `GROUP BY`, а `HAVING` фильтрует строки групп, созданных предложением `GROUP BY`.В присутствие `HAVING` запрос превращается в группируемый, даже если `GROUP BY` отсутствует.
``` sql
	SELECT tickets.passenger_name
	FROM tickets
	INNER JOIN ticket_flights ON tickets.ticket_no = ticket_flights.ticket_no
	WHERE ticket_flights.fare_conditions = 'Business'
	GROUP BY tickets.passenger_id, tickets.passenger_name
	HAVING COUNT(tickets.passenger_id) > 3
	ORDER BY tickets.passenger_name;
```

- `Window`
	инструмент для выполнения вычислений над наборами строк, связанных с текущей строкой в результирующем наборе.
	Пример: 
	Вычисляет средний размер заказа для каждого клиента, сохраняя информацию о каждом заказе.
``` sql
	SELECT
	    order_id,
	    customer_id,
	    order_total,
	    AVG(order_total) OVER (PARTITION BY customer_id) AS average_order_total
	FROM
	    orders;
```

-  `LIMIT` - ограничение количества строк, возвращаемых запросом.
``` sql
SELECT *
FROM employees
LIMIT 5;
```
## DELETE

- Команда `DELETE` удаляет из указанной таблицы строки, удовлетворяющие условию `WHERE`. Если предложение `WHERE` отсутствует, она удаляет из таблицы все строки, в результате будет получена рабочая, но пустая таблица.

- Чтобы удалять данные из таблицы, необходимо иметь право DELETE для неё, а также право SELECT для всех таблиц, перечисленных в предложении USING, и таблиц, данные которых считываются в условии.

 - Если перед именем таблицы добавлено `ONLY`, соответствующие строки удаляются только из указанной таблицы.

- Выводимая информация
	В случае успешного завершения, DELETE возвращает метку команды в виде

`DELETE число`

1. Удаление всех записей из таблицы

	Если необходимо удалить все записи из таблицы, можно использовать команду DELETE без условия WHERE. Однако следует быть осторожным, так как это удалит всю информацию из таблицы.
``` sql
	DELETE FROM employees;
```

2. Удаление записей с использованием условия WHERE

	Чаще всего DELETE используется вместе с условием WHERE для удаления конкретных записей, соответствующих определенным критериям.
``` sql
	DELETE FROM employees
	WHERE department = 'Sales' AND hire_date < '2020-01-01';
```

3.  Использование оператора RETURNING (специфично для PostgreSQL)
	В PostgreSQL можно использовать оператор RETURNING для получения информации о удаленных записях сразу после выполнения команды DELETE.

``` sql
	DELETE FROM employees
	WHERE department = 'Sales' AND hire_date < '2020-01-01'
	RETURNING id, name, department;
```

4. Использование USING и ссылки на другую таблицу

``` sql
	DELETE FROM films USING producers
	  WHERE producer_id = producers.id AND producers.name = 'foo';
```

5. Вложенный запрос

``` sql
	DELETE FROM films
	  WHERE producer_id IN (SELECT id FROM producers WHERE name = 'foo');
```


## UPDATE

- `SET` - определяет какие столбцы в таблице будут меняться
- `FROM` - изменяет попутно и другие таблицы
- `ONLY` -  строки изменяются только в указанной таблице.
- `UPDATE table_name SET table_name.col = 1` - ошибка
- `DEFAULT` - присвоить столбцу значение по умолчанию (это может быть NULL, если для столбца не определено некоторое выражение по умолчанию).
- `вложенный_SELECT` выдает столько выходных столбцов, сколько перечислено в предшествующем ему списке столбцов в скобках. 

#### Выводимая информация
	
	В случае успешного завершения, `UPDATE` возвращает метку команды в виде
	
	UPDATE _`число`_
1. Обновление всех записей в столбце

	Если необходимо обновить все записи в таблице, можно использовать команду UPDATE без условия WHERE. Это изменит значения указанных столбцов для всех строк таблицы.
	
	Пример:
``` sql
	UPDATE employees
	SET department = 'General';
```

2. Обновление записей с использованием условия WHERE

	Чаще всего UPDATE используется вместе с условием WHERE для изменения конкретных записей, соответствующих определенным критериям.
	
``` sql
	UPDATE employees
	SET salary = salary * 1.10
	WHERE department = 'Sales' AND hire_date < '2020-01-01';
```

5. Использование оператора RETURNING (специфично для PostgreSQL)

	В PostgreSQL можно использовать оператор RETURNING для получения информации об обновленных записях сразу после выполнения команды UPDATE.
	
	Пример:
``` sql
	UPDATE employees
	SET salary = salary * 1.05
	WHERE department = 'Engineering'
	RETURNING id, name, salary;
```


## INSERT


Вставка одной записи(дефолтное значение - ноль):
``` sql
INSERT INTO employees (name, department, hire_date, salary)
VALUES ('Иван Иванов', 'Маркетинг', '2023-05-15', 50000.00);
```


Вставка нескольких записей за один запрос
``` sql
INSERT INTO employees (name, department, hire_date, salary)
VALUES 
    ('Анна Петрова', 'Продажи', '2023-06-01', 45000.00),
    ('Сергей Смирнов', 'ИТ', '2023-07-20', 60000.00),
    ('Елена Кузнецова', 'Финансы', '2023-08-10', 55000.00);
```

Вставка с использованием подзапроса (INSERT INTO ... SELECT ...)

Предположим, есть две таблицы: new_employees и employees. Необходимо перенести всех новых сотрудников из new_employees в employees.
``` sql
INSERT INTO employees (name, department, hire_date, salary)
SELECT name, department, hire_date, salary
FROM new_employees
WHERE hire_date >= '2023-01-01';
```

Вложенный позапрос
``` sql
UPDATE employees 
SET sales_count = sales_count + 1 
WHERE id = (SELECT sales_person FROM accounts WHERE name = 'Acme Corporation');
```
## CREATE / SHOW

 1. CREATE DATABASE

	Создаёт новую базу данных.
	
	Пример:
``` sql
	CREATE DATABASE my_database;
```

 2. CREATE TABLE

	Создаёт новую таблицу в базе данных с указанной структурой столбцов и их типами данных.
	
	Пример:
``` sql
	CREATE TABLE employees (
	    id SERIAL PRIMARY KEY,
	    name VARCHAR(100) NOT NULL,
	    department VARCHAR(50),
	    hire_date DATE DEFAULT CURRENT_DATE,
	    salary NUMERIC(10, 2)
	);
```

1. SHOW DATABASES

	Отображает список всех баз данных на сервере.
	
	Пример:
	``` sql
	SHOW DATABASES;
	```


Этот запрос возвращает перечень всех доступных баз данных.

2. SHOW TABLES

	Отображает список всех таблиц в текущей базе данных.
	
	Пример:
	``` sql
	SHOW TABLES;
```
	
	Этот запрос выводит все таблицы, существующие в активной базе данных.

### 3. SHOW COLUMNS / SHOW FIELDS

Отображает информацию о столбцах заданной таблицы, включая их типы данных, ключевые параметры и другие атрибуты.

Пример:
``` sql
SHOW COLUMNS FROM employees;
```
или
``` sql
SHOW FIELDS FROM employees;
```


Этот запрос показывает структуру таблицы `employees`, включая названия столбцов, их типы и другие характеристики.

### 4. SHOW INDEX

Отображает информацию об индексах, созданных для указанной таблицы.

Пример:
``` sql
SHOW INDEX FROM employees;
```

Этот запрос выводит информацию о всех индексах таблицы `employees`, включая названия индексов, используемые столбцы и тип индекса.

### 5. SHOW CREATE TABLE

Отображает полный SQL-запрос, используемый для создания указанной таблицы. Полезно для получения структуры таблицы в формате SQL.

Пример:

SHOW CREATE TABLE employees;
## Типы данных

CHAR - строка с указанным количеством символов
VARCHAR - строка с ограничением на длину
TEXT - безразмерная строка