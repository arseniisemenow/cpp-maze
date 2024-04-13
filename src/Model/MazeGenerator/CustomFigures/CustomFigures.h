#ifndef A1_MAZE_CPP_1_MODEL_MAZE_GENERATOR_CUSTOM_FIGURES_CUSTOM_FIGURES_H_
#define A1_MAZE_CPP_1_MODEL_MAZE_GENERATOR_CUSTOM_FIGURES_CUSTOM_FIGURES_H_

#include "common/MazeData.h"

inline const s21::MazeData kHuman(
    {
        {
            false,
            false,
            false,
            false,
            false,
        },
        {
            false,
            false,
            false,
            true,
            false,
        },
        {
            true,
            false,
            false,
            false,
            true,
        },
        {
            true,
            true,
            true,
            true,
            true,
        },
        {
            false,
            true,
            true,
            true,
            false,
        },
    },
    {
        {
            false,
            false,
            true,
            true,
            false,
        },
        {
            false,
            false,
            true,
            true,
            true,
        },
        {
            false,
            false,
            false,
            false,
            false,
        },
        {
            false,
            true,
            false,
            false,
            true,
        },
        {
            false,
            false,
            true,
            true,
            false,
        },
    });
inline const std::vector<s21::MazeData> kCustomFigures = {kHuman};

#endif  // A1_MAZE_CPP_1_MODEL_MAZE_GENERATOR_CUSTOM_FIGURES_CUSTOM_FIGURES_H_