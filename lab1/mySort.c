void mySort(int d[], unsigned int n)
{
    double tempNum;
    // runs through the entire array of numbers 
    for(int i = 0; i < n - 1; i++){
        // Looking for the position of the samllest number 
        for(int j = i+1; j < n; j++){
            //checking if the next number is smaller than the current number
            if(d[j] < d [i]){
                //swapping the numbers around
                tempNum = d[i];
                d[i] = d[j];
                d[j] = tempNum;
            }
        }
    }
}
