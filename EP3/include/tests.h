#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include <string>
#include <vector>

#include "shell.h"
#include "colors.h"
#include "string_split.h"
#include "read.h"

using namespace std;

void print_check (string str);

void print_failed (string str);

void test_read ();

void test_best ();

void tests(int id);

#endif
