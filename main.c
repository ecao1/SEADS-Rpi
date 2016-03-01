#include "requestExecutor.h";
#include <time.h>

int main(int argc,char *argv[])
{
    int myArray[10] = {1,2,3,4,5,6,7,8,9,10,11};
    const uint64_t timestamp = (unsigned)time(NULL);
    sendRequest(myArray,10,timestamp);
    return 0;
}