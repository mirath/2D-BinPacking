#include "utils.h"

bool compareHeight(Item a, Item b) {
  // We add the outer minus sign to get nonincreasing 
  // ordering.
  return (a.height < b.height);
}
