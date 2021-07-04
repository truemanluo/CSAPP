int x = 10;

int sum(int *a, int n)
{
    int i, s = 0;
    while (i < n)
    {
        s += a[i++];
    }
    return s;
}