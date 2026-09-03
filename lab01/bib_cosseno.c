#include <math.h>
#include "bib_cosseno.h"


float to_rad(float angulo){
  return PI * angulo / 180.0;
}

float cosseno(float angulo){
  return cos(to_rad(angulo));
}
