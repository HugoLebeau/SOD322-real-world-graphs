#ifndef MISC_H
#define MISC_H

#include "graph.h"

unsigned long max(unsigned long a, unsigned long b);
void quicksort(unsigned long* array, unsigned long first, unsigned long last);
void intersection(unsigned long* sorted_a, unsigned long size_a, unsigned long* sorted_b, unsigned long size_b, unsigned long* inter, unsigned long* size_inter);

#endif
