#pragma once
#include "SortScene.h"
#include <iostream>


class HeapSortScene : public SortScene
{
    public:
    HeapSortScene(int barCount) : SortScene("Heap Sort", barCount) {}


    void Reset() override
    {
        SortScene::Reset();
        phase = BUILD_HEAP;
        int n = bars.Size();
        siftRoot = (n - 1) / 2;
        heapSize = n;
        siftCurrent = siftRoot;
        siftSize = n;
        extracting = false;
    }


    void Update() override 
    {
        if (sorted) return;

        int n = bars.Size();
        //bars.ResetStates();

        for (int k = heapSize; k < n; k++) 
        {
            bars.SetState(k, BarState::Sorted);
        }

        if (phase == BUILD_HEAP) 
        {
            if (!siftStep()) 
            {
                siftRoot--;
                if (siftRoot < 0) 
                {
                    phase = EXTRACT;
                    extracting = true;
                    siftCurrent = 0;
                    siftSize = heapSize;
                } 
                else 
                {
                    siftCurrent = siftRoot;
                    siftSize = heapSize;
                }
            }
        } 
        else 
        {
            if (heapSize <= 1) 
            {
                if (heapSize == 1) bars.SetState(0, BarState::Sorted);
                sorted = true;

                return;
            }

            if (extracting) 
            {
                //bars.ResetStates();
                bars.SetState(0, BarState::Swapping);
                bars.SetState(heapSize - 1, BarState::Swapping);
                bars.Swap(0, heapSize - 1);
                swaps++;
                heapSize--;
                //bars.SetState(heapSize - 1, BarState::Sorted);
                siftCurrent = 0;
                siftSize = heapSize;
                extracting = false;

                return;
            }

            if (!siftStep()) 
            {
                extracting = true;
                siftCurrent = 0;
            }
        }
    }


    void Draw(int x, int y, int w, int h) override 
    {
        bars.Draw(x, y, w, h);
    }


    private:
    enum Phase { BUILD_HEAP, EXTRACT } phase = BUILD_HEAP;

    int siftRoot = 0;
    int heapSize = 0;
    int siftCurrent = 0;
    int siftSize = 0;
    bool extracting = false;

    bool siftStep()
    {
        int largest = siftCurrent;
        int level = 2 * siftCurrent + 1;
        int retur = 2 * siftCurrent + 2;

        bars.ResetStates();
        bars.SetState(siftCurrent, BarState::Comparing);

        if (level < siftSize)
        {
            bars.SetState(level, BarState::Comparing);
            comparisons++;

            if (bars.Get(level) > bars.Get(largest))
                largest = level;
        }

        if (retur < siftSize)
        {
            bars.SetState(retur, BarState::Comparing);
            comparisons++;

            if (bars.Get(retur) > bars.Get(largest))
                largest = retur;
        }

        if (largest != siftCurrent)
        {
            bars.SetState(siftCurrent, BarState::Swapping);
            bars.SetState(largest, BarState::Swapping);
            bars.Swap(siftCurrent, largest);
            swaps++;
            bars.SetState(siftCurrent, BarState::Default);
            bars.SetState(largest, BarState::Default);
            siftCurrent = largest;

            return true;
        }

        return false;
    }
};
