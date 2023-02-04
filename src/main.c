#include <Clearning/config.h>
#include <Clearning/factorial.h>
#include <Clearning/hello_world.h>
#include <string.h>
#include <stdio.h>


int main(int argc, char* argv[])
{
    
    if (argc == 2 && strcmp(argv[1],"--version"))
    {
        printf("Project Name version %s\n",VERSION);
        printf("Copyright information here\n");
        printf("More copyright details.\n\n");
    }
    else
    {
        printf("%s, %s\n", hello(), world());
        printf("%d\n",generateRandomNumber());
        printf("%d\n", factorial(5));
    }
    return 0;
}
