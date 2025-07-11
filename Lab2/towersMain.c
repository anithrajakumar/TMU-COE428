#include <stdlib.h>
#include "towers.h"

int main(int argc, char **argv)
{
    int n, from, dest;
    //if more the 2 arguments are given then we assume from and dest are given
    if(argc > 2){
        n = atoi(argv[1]);
        from = atoi(argv[2]);
        dest = atoi(argv[3]);

    } 
    // if two arguments are given then we know the number of disks only
    else if(argc == 2){
        n = atoi(argv[1]);
        from = 1;
        dest = 2;
    } 
    // otherwise we assume 3 disk are being moved from 1 to 2
    else{
        n = 3;
        from = 1;
        dest = 2;
    }
    
    towers(n, from, dest);
    exit(0);
}

