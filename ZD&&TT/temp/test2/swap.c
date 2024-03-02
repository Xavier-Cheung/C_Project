void swap(int *xptr, int *yptr) {
    int temp;
    temp = *xptr;
    *xptr = *yptr;
    *yptr = temp;
}