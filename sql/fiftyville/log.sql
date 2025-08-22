-- Keep a log of any SQL queries you execute as you solve the mystery.
--
-- .table
-- table: airports, crime_scene_reports, people, atm_transactions, flights, phone_calls, bakery_security_logs, interviews, bank_accounts, passengers, 
--
-- .schema crime_scene_reports
SELECT
    *
FROM
    crime_scene_reports;

-- Too many things
-- > All you know is that the theft took place on July 28, 2024 and that it took place on Humphrey Street.
SELECT
    *
FROM
    crime_scene_reports
WHERE
    year = 2024
    AND month = 7
    AND day = 28
    AND street = 'Humphrey Street';

-- Theft took place at 10:15am with 3 witnesses
SELECT
    *
FROM
    interviews
WHERE
    year = 2024
    AND month = 7
    AND day = 28;

-- Ruth say thief left in 10 minutes by car
-- Eugene say thief withdraw money from ATM on Leggett Street earlier
-- Raymond say thief calls and plans to take tomorrow's earliest flight and buy ticket today
SELECT
    *
FROM
    crime_scene_reports
WHERE
    year = 2024
    AND month = 7
    AND day = 28
    AND street = 'Leggett Street';

-- no output
-- .schema bakery_security_logs
SELECT
    *
FROM
    bakery_security_logs
WHERE
    year = 2024
    AND month = 7
    AND day = 28;

-- 5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55
-- These car exit between 10:16am and 10:23am
SELECT
    *
FROM
    bakery_security_logs
WHERE
    license_plate IN (
        SELECT
            license_plate
        FROM
            bakery_security_logs
        WHERE
            year = 2024
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute >= 15
            AND minute <= 25
    );

-- I want to find possible bank account
--.schema atm_transactions
SELECT
    *
FROM
    atm_transactions
WHERE
    atm_location = 'Leggett Street'
    AND year = 2024
    AND month = 7
    AND day = 28
    AND transaction_type = 'withdraw';

-- and find possible people
-- .schema bank_accounts 
-- .schema people
--
-- I find that table people has 'name', 'phone number', 'passport number' and 'license plate'
-- Maybe I have found two of them.
--
-- Let me find out possible phone number
-- .schema phone_calls
SELECT
    *
FROM
    phone_calls
WHERE
    year = 2024
    AND month = 7
    AND day = 28
LIMIT
    5;

-- I want to find possible flights
-- .schema flights
SELECT
    *
FROM
    flights
WHERE
    year = 2024
    AND month = 7
    AND day = 29
ORDER BY
    hour,
    minute;

-- But I can't sure if they actually choose the earliest flight
-- A good news: every flights' origins that day is Fiftyville Regional Airport
--
-- .schema airports
-- .schema passengers
-- List passengers'name of one flight
SELECT
    name
FROM
    people
WHERE
    passport_number IN (
        SELECT
            passport_number
        FROM
            passengers
        WHERE
            flight_id IN (
                SELECT
                    id
                FROM
                    flights
                WHERE
                    year = 2024
                    AND month = 7
                    AND day = 29
            )
    );

-- Let's combine all of them
SELECT
    name
FROM
    people
WHERE
    license_plate IN (
        SELECT
            license_plate
        FROM
            bakery_security_logs
        WHERE
            year = 2024
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute >= 15
            AND minute <= 25
    )
    AND passport_number IN (
        SELECT
            passport_number
        FROM
            passengers
        WHERE
            flight_id IN (
                SELECT
                    id
                FROM
                    flights
                WHERE
                    year = 2024
                    AND month = 7
                    AND day = 29
                ORDER BY
                    hour,
                    minute
                LIMIT
                    4
                    -- We don't know if they take the earliest flight, but we don't find any other person until the 5th early flight.
            )
    )
    AND phone_number IN (
        SELECT
            caller
        FROM
            phone_calls
        WHERE
            year = 2024
            AND month = 7
            AND day = 28
    )
    AND id IN (
        SELECT
            person_id
        FROM
            bank_accounts
        WHERE
            account_number IN (
                SELECT
                    account_number
                FROM
                    atm_transactions
                WHERE
                    atm_location = 'Leggett Street'
                    AND year = 2024
                    AND month = 7
                    AND day = 28
                    AND transaction_type = 'withdraw'
            )
    );

-- We found Bruce is the thief.
SELECT
    *
FROM
    airports
WHERE
    id = (
        SELECT
            destination_airport_id
        FROM
            flights
        WHERE
            id = (
                SELECT
                    flight_id
                FROM
                    passengers
                WHERE
                    passport_number = (
                        SELECT
                            passport_number
                        FROM
                            people
                        WHERE
                            name = 'Bruce'
                    )
            )
    );

-- He wanted to LaGuardia Airport in New York City
SELECT
    name
FROM
    people
WHERE
    phone_number = (
        SELECT
            receiver
        FROM
            phone_calls
        WHERE
            caller = (
                SELECT
                    phone_number
                FROM
                    people
                WHERE
                    name = 'Bruce'
            )
    );

-- And his accomplice is Pamela