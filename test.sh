#!/bin/bash

echo "Test: Normal Run"
./philo 5 800 200 200

echo "Test: Death Expected"
./philo 5 100 200 200

echo "Test: Single Philosopher"
./philo 1 800 200 200

echo "Test: All Philosophers Eat 3 Times"
./philo 5 800 200 200 3
