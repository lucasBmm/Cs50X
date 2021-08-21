-- Keep a log of any SQL queries you execute as you solve the mystery.

-- SELECT description FROM crime_scene_reports
-- WHERE month = 7 AND day = 28;

-- SELECT * FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour = 10;

-- SELECT * FROM interviews WHERE month >= 7 AND day >= 28;

-- SELECT * FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "Fifer Street";

-- SELECT * FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 61;

-- SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour = 10)
-- AND phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 61);

-- SELECT * FROM bank_accounts;

-- SELECT * FROM bank_accounts WHERE account_number IN (
-- SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "Fifer Street");


-- SELECT * FROM people WHERE id IN (
-- SELECT person_id FROM bank_accounts WHERE account_number IN (
-- SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "Fifer Street";

-- SELECT * FROM flights WHERE DAY = 29 ORDER BY hour;

-- SELECT NAME FROM people WHERE passport_number IN (
-- SELECT passport_number FROM passengers WHERE flight_id = 36);


-- Suspects :
-- Ernest
-- Madison

-- People who used ATM machines in the day of the crime
SELECT name FROM people WHERE id IN (SELECT person_id
FROM bank_accounts
WHERE account_number IN (SELECT account_number
FROM atm_transactions
WHERE month = 7 AND day = 28
AND atm_location = "Fifer Street"));

-- People who made phone calls in the day of the crime
SELECT name FROM people WHERE phone_number IN (SELECT caller
FROM phone_calls
WHERE month = 7 AND day = 28
AND duration < 61);

-- People where used courthouse parking lot in the day of the crime
SELECT name FROM people WHERE license_plate IN (
SELECT license_plate FROM courthouse_security_logs
WHERE month = 7 AND day = 28 AND hour = 10
AND minute > 15 AND minute < 26);

-- People who got on the first flight in the day after the crime
SELECT name FROM people WHERE passport_number IN (
SELECT passport_number FROM passengers
WHERE flight_id IN(
SELECT id FROM flights WHERE day = 29
AND month = 7 ORDER BY hour
LIMIT 1));

-- Result
SELECT name FROM people WHERE id IN (SELECT person_id
FROM bank_accounts
WHERE account_number IN (SELECT account_number
FROM atm_transactions
WHERE month = 7 AND day = 28
AND atm_location = "Fifer Street"))
INTERSECT
SELECT name FROM people WHERE phone_number IN (SELECT caller
FROM phone_calls
WHERE month = 7 AND day = 28
AND duration < 61)
INTERSECT
SELECT name FROM people WHERE license_plate IN (
SELECT license_plate FROM courthouse_security_logs
WHERE month = 7 AND day = 28 AND hour = 10
AND minute > 15 AND minute < 26)
INTERSECT
SELECT name FROM people WHERE passport_number IN (
SELECT passport_number FROM passengers
WHERE flight_id IN(
SELECT id FROM flights WHERE day = 29
AND month = 7 ORDER BY hour
LIMIT 1));

-- Accomplice
SELECT name FROM people WHERE phone_number IN (
SELECT receiver FROM phone_calls
WHERE caller = (SELECT phone_number FROM people
WHERE name = "Ernest") AND day = 28
AND duration < 60);

-- Escape
SELECT city FROM airports 
WHERE id = (SELECT destination_airport_id 
FROM flights WHERE id = (
SELECT flight_id FROM passengers WHERE
passport_number = (SELECT passport_number 
FROM people WHERE name = "Ernest")));