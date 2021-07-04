int switch_case(int x, int y)
{
    int ans = 0;
    switch (x)
    {
    case 1:
        ans = y * x;
        break;
    case 2:
        ans = y* y * x;
        break;
    default:
        ans = 0;
        break;
    }
    return ans;
}