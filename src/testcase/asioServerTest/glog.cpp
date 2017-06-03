#include <sys/types.h>
#include <sys/stat.h>
#include "glog.hpp"

void mklogdir(char *dirname){
    mkdir(dirname, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}
