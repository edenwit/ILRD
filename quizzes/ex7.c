#include <stdio.h>

int MaxProfit(int *arr, int n, int *b, int *s);
  
int main()
{
	int buy = 0;
	int sell = 0;
	int i = 0;
    int prices[] = {23, 21, 19, 25, 12, 12, 11, 4};
    int n = sizeof(prices) / sizeof(prices[0]);
	int best_profit = 0;

	for (i = 0; i < n; ++i)
	{
		printf ("%d ",prices[i]);
	}
	best_profit = MaxProfit(prices, n, &buy, &sell);
    printf("\nBuy on %d, Sell on %d, Max profit is: %d.\n", buy + 1, sell + 1, best_profit);
 
    return 0;
}

int MaxProfit(int *arr, int n, int *b, int *s)
{
	int min_price_loc = 0;
    int min_price = arr[0];
    int profit = 0;
    int i = 0;
    
    assert (NULL != arr);
    
    if (n < 2) 
    {
    	printf("\nAtleast 2 price periods necessary!");
        return 0;
    }
    
    for(i = 0; i < n; i++)
    {
    	if(min_price > arr[i])
    	{
    		min_price = arr[i];
    		min_price_loc = i;
    	}
    	else if(profit < (arr[i] - min_price))
    	{
    		profit = arr[i] - min_price;
    		*b = min_price_loc;
    		*s = i;
    	}
    }
    return profit;
}
