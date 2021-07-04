int switch_case(int x, int y)
{
    int ans = 0;
    if (x == 1)
        ans = y * x;
    else if (x == 2)
    {
        ans = y* y * x;
    }
    else
        ans = 0;
    return ans;
}