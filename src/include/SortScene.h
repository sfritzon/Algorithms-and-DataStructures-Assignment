#pragma once
#include <string>
#include "BarArray.h"
#include "raylib.h"


class SortScene
{
    public:
    SortScene(const std::string& name, int barCount) : name(name), bars(barCount) {}

    virtual ~SortScene() = default; 

    virtual void Update() = 0;

    virtual void Draw(int x, int y, int w, int h) = 0;

    virtual void Reset()
    {
        bars.Shuffle();
        i = 0; j = 0;
        sorted = false;
        comparisons = 0;
        swaps = 0;
    }


    const std::string& GetName() const 
    {
        return name;
    }

    bool IsSorted() const 
    {
        return sorted;
    }

    int GetComparisons() const
    {
        return comparisons;
    }

    int GetSwaps() const
    {
        return swaps;
    }


    void DrawStats(int x, int y) const
    {
        if (!sorted)
            return;

        DrawRectangle(x, y, 300, 90, { 10, 10, 18, 200 });
        DrawRectangleLines(x, y, 200, 90, { 80, 80, 100, 200 });

        DrawText(("Algorithm : " + name).c_str(), x + 12, y + 10, 16, { 180, 180, 200, 255 });
        DrawText(("Comparisons : " + std::to_string(comparisons)).c_str(), x + 12, y + 34, 16, BarArray::COL_COMPARING);
        DrawText(("Swaps : " + std::to_string(swaps)).c_str(), x + 12, y + 58, 16, BarArray::COL_SWAPPING);
    }

    protected:
    std::string name;
    BarArray bars;
    int i = 0, j = 0;
    bool sorted = false;
    int comparisons = 0;
    int swaps = 0;
};
