#include <time.h>

time_t time(time_t *__timer){
if(__timer){
*__timer =(time_t)2147472000;
}
return 2147472000;
}
