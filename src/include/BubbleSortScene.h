#pragma once
#include "SortScene.h"


class BubbleSortScene : public SortScene
{
    public:
    BubbleSortScene(int barCount) : SortScene("Bubble Sort", barCount) {}


    void Reset() override
    {
        SortScene::Reset();
        lastSwapped = bars.Size() - 1;
    }


    void Update() override
    {
        if (sorted)
        {
            return;
        }

        int n = bars.Size();
        bars.ResetStates();

        for (int k = lastSwapped + 1; k < n; k++)
        {
            bars.SetState(k, BarState::Sorted);
        }

        if (i >= n -1)
        {
            for (int k = 0; k < n; k++)
            {
                bars.SetState(k, BarState::Sorted);
            }

            sorted = true;
            return;
        }

        bars.SetState(j, BarState::Comparing);
        bars.SetState(j + 1, BarState::Comparing);
        comparisons++;

        if (bars.Get(j) > bars.Get(j + 1))
        {
            bars.SetState(j, BarState::Swapping);
            bars.SetState(j + 1, BarState::Swapping);
            bars.Swap(j, j + 1);
            swaps++;
            lastSwapped = j;
        }

        j++;
        if (j >= lastSwapped)
        {
            j = 0;
            i++;
        }
    }


    void Draw(int x, int y, int w, int h) override
    {
        bars.Draw(x, y, w, h);
    }

    
    private:
    int lastSwapped = 0;
};
