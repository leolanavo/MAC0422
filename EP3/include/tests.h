#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include <string>
#include <vector>

#include "colors.h"
#include "string_split.h"
#include "read.h"
#include "shell.h"

using namespace std;

void print_check (string str);

void print_failed (string str);

void test_read ();

void test_best ();

void tests();

#endif
