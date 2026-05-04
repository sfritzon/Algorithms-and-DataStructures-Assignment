#pragma once
#include "SortScene.h"


class InsertionSortScene : public SortScene
{
    public:
    InsertionSortScene(int barCount) : SortScene("Insertion Sort", barCount) {}


    void Reset() override 
    {
        SortScene::Reset();
        phase = PICK;
        i = 1;
        j = 1;
        bars.SetState(0, BarState::Sorted);
    }


    void Update() override
    {
        if (sorted) return;

        int n = bars.Size();

        if (phase == PICK)
        {
            bars.ResetStates();
            for (int k = 0; k < i; k++)
		bars.SetState(k, BarState::Sorted);

            if (i >= n)
            {
                for (int k = 0; k < n; k++)
                {
                    bars.SetState(k, BarState::Sorted);
                }

                sorted = true;
                return;
            }

            j = i;
            bars.SetState(j, BarState::Comparing);
            phase = SHIFT;

            return;
        }

        bars.ResetStates();
        for (int k = 0; k < i; k++)
        {
            bars.SetState(k, BarState::Sorted);
        }

        if (j > 0)
        {
            bars.SetState(j, BarState::Comparing);
            bars.SetState(j - 1, BarState::Comparing);
            comparisons++;

            if (bars.Get(j) < bars.Get(j - 1)) 
            {
                bars.SetState(j, BarState::Swapping);
                bars.SetState(j - 1, BarState::Swapping);
                bars.Swap(j, j - 1);
                swaps++;
                j--;

                return;
            }
        }

        bars.SetState(j, BarState::Sorted);
        i++;
        phase = PICK;
    }


    void Draw(int x, int y, int w, int h) override
    {
        bars.Draw(x, y, w, h);
    }
    

    private:
    enum Phase { PICK, SHIFT } phase = PICK;
};
