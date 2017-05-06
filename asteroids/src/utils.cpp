/* utility functions */
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "model.h"

/* some numerical helper functions */
float norm(float value, float min, float max) 
{
    return (value-min)/(max-min); 
}
float lerp(float min, float max, float value) 
{
    return max*value+(1.0f-value)*min; 
}
float map(float value, float lower, float upper, float min, float max) 
{
    return lerp(min,max, norm(value,lower,upper)); 
}
/*------*/

/* random number between values, not including last
    randrange(0,360) produces numbers 0..359
*/
int randrange(int from, int to)
{
    int range = to-from;
    return from + rand()%range;
}

/* Convert degrees to radians */
const float pi = 3.1415926f;
float radians(float degrees) { return pi*(degrees/180); }

