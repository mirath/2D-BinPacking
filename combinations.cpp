int * combinations(int k, int n, int* arr){
  int i = k-1;

  if (arr[i] < n-1)
    arr[i] += 1;
  else{
    while(arr[i] >= n-1){
      arr[i-1] += 1;
      i -= 1;
    }

    while(i < k-1){
      arr[i+1] = arr[i]+1;
      i += 1;
    }
  }

  return arr;
}
