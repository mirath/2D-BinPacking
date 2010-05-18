#include "utils.h"

int compareHeight(const void *a, const void *b) {
  // We add the outer minus sign to get nonincreasing 
  // ordering.
  return ( -((*(Item *)a).height - (*(Item*)b).height) );
}
