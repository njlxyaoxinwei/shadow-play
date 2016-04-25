#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>

/* Helper functions for project */

template<typename T>
void inline LogError(const T& str) {
  std::cerr << "ERROR:: " << str << std::endl;
}

template<typename T>
void inline Die(const T& str) {
  LogError(str); exit(EXIT_FAILURE);
}

#endif
