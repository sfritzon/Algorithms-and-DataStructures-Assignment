#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include "raylib.h"


enum class BarState 
{
    Default,    // Gray
    Comparing,  // Yellow
    Swapping,   // Red
    Sorted      // Green
};


class BarArray 
{
    public:
    
    static constexpr Color COL_DEFAULT = { 120, 120, 130, 255 };
    static constexpr Color COL_COMPARING = { 255, 210, 50, 255 };
    static constexpr Color COL_SWAPPING = { 220, 60, 60, 255 };
    static constexpr Color COL_SORTED = { 60, 200, 100, 255 };
    static constexpr Color COL_BG = { 18, 18, 24, 255 };

    BarArray() {}
    explicit BarArray(int count) { Init(count); }


    void Init(int count) 
    {
        values.resize(count);
        states.resize(count, BarState::Default);

        for (int i = 0; i < count; ++i) 
        {
            values[i] = i + 1;
        }

        Shuffle();
    }

    
    void Shuffle() 
    {
        static std::mt19937 random{ std::random_device{}() };
        std::shuffle(values.begin(), values.end(), random);
        std::fill(states.begin(), states.end(), BarState::Default);
    }


    int  Size() const { return (int)values.size(); }
    int  Get(int i) const { return values[i]; }


    void Swap(int i, int j) 
    {
        std::swap(values[i], values[j]);
        std::swap(states[i], states[j]);
    }


    void SetState(int i, BarState s)  
    { 
        states[i] = s; 
    }


    BarState GetState(int i)   const  
    { 
        return states[i]; 
    }


    void ResetStates() 
    {
        std::fill(states.begin(), states.end(), BarState::Default);
    }


    void Draw(int x, int y, int w, int h) const 
    {
        int n = Size();
        if (n == 0) return;

        float barW = (float)w / n;
        float maxVal = (float)n;

        for (int i = 0; i < n; ++i) 
        {
            float barH = ((float)values[i] / maxVal) * h;
            float bx = x + i * barW;
            float by = y + h - barH;

            Color col;
            switch (states[i]) 
            {
                case BarState::Comparing: 
                    col = COL_COMPARING; 
                    break;

                case BarState::Swapping:
                    col = COL_SWAPPING;
                    break;

                case BarState::Sorted:
                    col = COL_SORTED;
                    break;

                default: 
                    col = COL_DEFAULT;   
                    break;
            }

            DrawRectangleRec({ bx + 1, by, barW - 1, barH }, col);
        }
    }

    private:
    std::vector<int> values;
    std::vector<BarState> states;
};
