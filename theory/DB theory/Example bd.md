

[example](photo/20241121155155.png)


Получить все доступные города:
``` sql
SELECT DISTINCT airports_data.city
FROM flights
LEFT JOIN airports_data ON airports_data.airport_code = flights.arrival_airport;
```

Вывод всех людей, летавших бизнесом больше 100 раз:
``` sql
SELECT tickets.passenger_name
FROM tickets
INNER JOIN ticket_flights ON tickets.ticket_no = ticket_flights.ticket_no
WHERE ticket_flights.fare_conditions = 'Business'
GROUP BY tickets.passenger_id, tickets.passenger_name
HAVING COUNT(tickets.passenger_id) > 3
ORDER BY tickets.passenger_name;

```


Найти все завтрашние рейсы из Москвы в Петербург, где больше трех свободных мест
``` sql
EXPLAIN SELECT flights.flight_id, flights.flight_no, flights.departure_airport, flights.arrival_airport, flights.scheduled_departure, flights.scheduled_arrival

FROM flights 
JOIN airports AS dep_airports ON (dep_airports.airport_code = flights.departure_airport)
JOIN airports AS arr_airports ON (arr_airports.airport_code = flights.arrival_airport)
JOIN seats ON (seats.aircraft_code = flights.aircraft_code)

JOIN (SELECT aircraft_code, COUNT(*) AS max_seats FROM seats GROUP BY aircraft_code) AS max_seats ON (max_seats.aircraft_code = flights.aircraft_code)

JOIN (SELECT flight_id, COUNT(*) AS occ_seats FROM ticket_flights GROUP BY flight_id) AS occ_seats ON (occ_seats.flight_id = flights.flight_id)

WHERE (dep_airports.city = 'Москва' AND arr_airports.city = 'Санкт-Петербург' AND max_seats - occ_seats >= 3 AND flights.scheduled_departure = (bookings.now()::date + 1));

```


Давайте выведем все рейсы, на котором загрузка больше 90%
``` sql
SELECT DISTINCT flights.departure_airport, flights.arrival_airport

FROM flights 
JOIN airports AS dep_airports ON (dep_airports.airport_code = flights.departure_airport)
JOIN airports AS arr_airports ON (arr_airports.airport_code = flights.arrival_airport)
JOIN seats ON (seats.aircraft_code = flights.aircraft_code)

JOIN (SELECT aircraft_code, COUNT(*) AS max_seats FROM seats GROUP BY aircraft_code) AS max_seats ON (max_seats.aircraft_code = flights.aircraft_code)

JOIN (SELECT flight_id, COUNT(*) AS occ_seats FROM ticket_flights GROUP BY flight_id) AS occ_seats ON (occ_seats.flight_id = flights.flight_id)

WHERE occ_seats / max_seats > 0.9;
```