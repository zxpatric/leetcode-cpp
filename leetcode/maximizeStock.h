//
// Created by ZhouP on 3/23/2019.
//

#ifndef CPPSANDBOX_MAXIMIZESTOCK_H
#define CPPSANDBOX_MAXIMIZESTOCK_H

#include "../include/datastructure.h"
#include <limits>

void setFlags(const Ints& prices, Ints& flags)
{
    int count = flags.size();

    for (int i = 1; i < count-1; ++i) {
        int left_value = prices[i-1];
        int value = prices[i];
        int right_value = prices[i+1];
        if(left_value>value)
        {
            if (right_value>value)
            {
                flags[i] = -1;
            }
            else
            {
                flags[i] = 0;
            }
        }
        else
        {
            if (right_value<value)
            {
                flags[i]=1;
            }
            else
            {
                flags[i] = 0;
            }
        }
    }

//    if(prices[1]>prices[0])
//        flags[0] = -1;
//    else if(prices[1]<prices[0])
//        flags[0] = 1;
//    else
//        flags[0] = flags[1];
//
//    if(prices[count-2]>prices[count-1])
//        flags[count-1] = -1;
//    else if(prices[count-2]<prices[count-1])
//        flags[count-1] = 1;
//    else
//        flags[count-1] = flags[count-2];
    int i;
    for (i = 1; i < count-1; ++i) {
        if (flags[i]!=0)
        {
            break;
        }
    }

    if (i<count-1)
    {
        if (flags[i]==1)
        {
            if (prices[0]<prices[i])
                flags[0]=-1;
            else
                flags[0]=0;
        }
        else
        {
            if (prices[0]>prices[i])
                flags[0]=1;
            else
                flags[0]=0;
        }

        for (i = count-2; i > 0; --i) {
            if (flags[i]!=0)
            {
                break;
            }
        }

        if (i>0)
        {
            if (flags[i]==1)
            {
                if (prices[count-1]<prices[i])
                    flags[count-1]=-1;
                else
                    flags[count-1]=0;
            }
            else
            {
                if (prices[count-2]>prices[i])
                    flags[count-1]=1;
                else
                    flags[count-1]=0;
            }
        }
        else
        {
            if (prices[0]<prices[count-1])
            {
                flags[0]=-1;
                flags[count-1]=1;
            }
            else
            {
                flags[0]=0;
                flags[count-1]=0;
            }
        }
    }
    else
    {
        if (prices[0]<prices[count-1])
        {
            flags[0]=-1;
            flags[count-1]=1;
        }
        else
        {
            flags[0]=0;
            flags[count-1]=0;
        }
    }
}

int maxprofile1 (const Ints& prices)
{
    // find all the valleys and all the peaks
    // if the start point is less than its neighbor, it is a valley
    // if the end point is less than its neighbor, it is a valley

    int count = prices.size();
    if (count<2)
        return -1;

    Ints flags(count);
    setFlags(prices, flags);

    // find the smallest valleys to the left of biggest peak.

    // find peak breakpoints.
    int peak = -1;
    int index = -1;
    Ints PeakBreaks;
    PeakBreaks.reserve(count);
    for (int j = 0; j < count; ++j) {
        if (flags[j]==1)
        {
            if (prices[j]< peak) {
                PeakBreaks.push_back(index);
            }
            peak = prices[j];
            index = j;
        }
    }
//    std::rotate(PeakBreaks.begin(), PeakBreaks.begin()+1, PeakBreaks.end());
//    if(PeakBreaks.front() != -1)
    PeakBreaks.push_back(index);
    PeakBreaks.insert(PeakBreaks.begin(), -1);

    int final_valley_index = -1;
    int final_peak_index = -1;

    int profit = 0;
    int count_peak = PeakBreaks.size();
    for(int i=1; i<count_peak;++i)
    {
        int peak0 = PeakBreaks[i-1];
        int peak1 = PeakBreaks[i];

        if (peak0>=peak1)
            break;

        int valley_index = -1;
        int valley_value = std::numeric_limits<int>::max();
        for (int j = peak0+1; j < peak1; ++j) {
            if (flags[j]==-1)
            {
                if (prices[j]< valley_value) {
                    valley_value = prices[j];
                    valley_index = j;
                }
            }
        }

        if (valley_index>=0)
        {
            int local_profit = prices[peak1] - valley_value;
            if (local_profit>profit) {
                profit = local_profit;
                final_peak_index = peak1;
                final_valley_index = valley_index;
            }
        }
    }

    printf ("final_valley_index is %d, final_peak_index is %d\n", final_valley_index, final_peak_index);

    return profit;
}


Ints maxprofile2 (const Ints& prices)
{
    // find all the valleys and all the peaks
    // if the start point is less than its neighbor, it is a valley
    // if the end point is less than its neighbor, it is a valley

    Ints profits;
    int count = prices.size();
    if (count<2)
        return profits;

    Ints flags(count);
    setFlags(prices, flags);

    // find the smallest valleys to the left of biggest peak.

    // find peak breakpoints.
    int peak = -1;
    int index = -1;
    Ints PeakBreaks;
    PeakBreaks.reserve(count);
    PeakBreaks.push_back(-1);
    for (int j = 0; j < count; ++j) {
        if (flags[j]==1)
        {
            PeakBreaks.push_back(j);
        }
    }

//    int profit = 0;
    int count_peak = PeakBreaks.size();
    for(int i=1; i<count_peak;++i)
    {
        int peak0 = PeakBreaks[i-1];
        int peak1 = PeakBreaks[i];

        if (peak0>=peak1)
            break;

        int valley_index = -1;
        int valley_value = std::numeric_limits<int>::max();
        for (int j = peak0+1; j < peak1; ++j) {
            if (flags[j]==-1)
            {
                if (prices[j]< valley_value) {
                    valley_value = prices[j];
                    valley_index = j;
                }
            }
        }

        if (valley_index>=0)
        {
            int local_profit = prices[peak1] - valley_value;
//            profit += local_profit;
            profits.push_back(local_profit);
        }
    }

    return profits;
}

int maxProfit3(Ints &prices, int K) {
    // f[k, ii] represents the max profit up until prices[ii] (Note: NOT ending with prices[ii]???) using at most k transactions.
    // Great idea of divide and conquer!!!
    //*f[k, ii] = max(f[k, ii-1], prices[ii] - prices[jj] + f[k-1, jj]) { jj in range of [0, ii-1] }
    //          = max(f[k, ii-1], prices[ii] + max(f[k-1, jj] - prices[jj]))
    // f[0, ii] = 0; 0 times transation makes 0 profit
    // f[k, 0] = 0; if there is only one price data point you can't make any money no matter how many times you can trade
    if (prices.size() < 2) return 0;
    else {
        int maxProf = 0;
        std::vector<Ints> f(K+1, Ints(prices.size(), 0));
        for (int kk = 1; kk <= K; kk++) {
            // Due to the index, you have to deal with f[0][X] and f[X][0] differently.
            int tmpMax = f[kk-1][0] - prices[0];
            for (int ii = 1; ii < prices.size(); ii++) {
                f[kk][ii] = std::max(f[kk][ii-1], prices[ii] + tmpMax);
                maxProf = std::max(f[kk][ii], maxProf);

                tmpMax = std::max(tmpMax, f[kk-1][ii] - prices[ii]);
            }
        }
        return maxProf;
    }
}


int maxProfit4(Ints &prices, int KTimes) {
    if (prices.size() < 2 || KTimes < 1)
        return 0;

    int maxProf = 0;
    int count = prices.size();
    ++KTimes;
    std::vector<Ints> profits(KTimes, Ints(count, 0));

    // profits[k,i] is the max profit we can make by k transactions with stock price 0 ~ i
    // max(prices[i] - prices[j] + profits[k-1, j]) is the max profit of using the price[i] toward any price between 0 and i-1 to create one transaction
    //                                                                         and any prices before the selected price to make k-1 transactions

    // profits[k,i] = max(profits[k, i-1], max(prices[i] - prices[j] + profits[k-1, j]) j=0...i-1)
    int maxProfit = 0;
    for (int k = 1; k < KTimes; ++k) {
        for (int i = 1; i < count; ++i) {
            int max_k_1(0);
            for (int j = 0; j < i; ++j) // This check is more straightforward but didn't leverage the information you may collect in the second loop, - prices[j] + profits[k-1][j] stays same through i changes
            {
                max_k_1 = std::max(max_k_1, prices[i] - prices[j] + profits[k-1][j]);  //j is 0~i-1, you would want max(- price[j] + profits[k-1][j])
            }
            profits[k][i] = std::max(profits[k][i-1], max_k_1);
            maxProfit = std::max(maxProfit, profits[k][i]);
        }
    }

    return maxProfit;
}

void test_buysellstock()
{
//    Ints prices = {7,1,5,3,6,4};

    Ints prices = {3, 7, 1, 5, 3, 6, 14};
//    Ints prices = {3,3,5,0,0,3,1,4};
    printVector<decltype(prices)::value_type> (prices);

    printf ("Only one buy and one sell is allowed. Max profit is %d\n", maxprofile1(prices));

//    Ints profits = maxprofile2(prices);
//    int max_profit = std::accumulate(profits.begin(), profits.end(), 0);
//    printf ("Free buy and sell is allowed. Max profit is %d\n", max_profit);

    int MAX_TRANSACTION = 2;
    printf ("Optimized: Allow only %d transactions then the Max profit is %d\n", MAX_TRANSACTION, maxProfit3 (prices, MAX_TRANSACTION));
    int maxProfit = maxProfit4 (prices, MAX_TRANSACTION);
    printf ("Three loops: Allow only %d transactions then the Max profit is %d\n", MAX_TRANSACTION, maxProfit);

}



void test_buySellStockWithCoolDown ()
{
    Ints values = {1,2,3,0,2};

//    sell[i]=max(buy[i-1]+prices[i], sell[i-1]-prices[i-1]+prices[i]);
//    buy[i]=max(sell[i-2]-prices[i], buy[i-1]+prices[i-1]-prices[i]);

//    int maxProfit(vector<int>& p)
//    {
//        if (p.size() < 2)
//            return 0;
//        int i, sz = p.size();
//        int ret = 0;
//        vector<int> buy(sz, 0);
//        vector<int> sell(sz, 0);
//        buy[0] = -p[0];
//        for (i = 1; i < sz; ++i)
//        {
//            sell[i] = max(buy[i - 1] + p[i], sell[i - 1] - p[i - 1] + p[i]);
//            if (ret < sell[i]) //record the max sell[i]
//                ret = sell[i];
//            if (1 == i)
//                buy[i] = buy[0] + p[0] - p[1];
//            else
//                buy[i] = max(sell[i - 2] - p[i], buy[i - 1] + p[i - 1] - p[i]);
//        }
//        return ret;
//    }
}
#endif //CPPSANDBOX_MAXIMIZESTOCK_H
