#pragma once

// it returns the number of variadic arguments
#define VA_ARGS_SIZE(...) VA_ARGS_SIZE_AUX(__VA_ARGS__, INDEX_REV_SEQ())

#define INDEX_REV_SEQ() 7, 6, 5, 4, 3, 2, 1, 0
#define VA_ARGS_SIZE_IMPL(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, N, ...) N
#define VA_ARGS_SIZE_AUX(...) VA_ARGS_SIZE_IMPL(__VA_ARGS__)

#define CONCAT_AUX(x, y) x##y
#define CONCAT(x, y) CONCAT_AUX(x, y)
#define FOLD_VA_ARGS_AUX_1(FUNC, ARG1, ...) FUNC(ARG1)
#define FOLD_VA_ARGS_AUX_2(FUNC, ARG1, ...) CONCAT(FUNC(ARG1), FOLD_VA_ARGS_AUX_1(FUNC, __VA_ARGS__))
#define FOLD_VA_ARGS_AUX_3(FUNC, ARG1, ...) CONCAT(FUNC(ARG1), FOLD_VA_ARGS_AUX_2(FUNC, __VA_ARGS__))
#define FOLD_VA_ARGS_AUX_4(FUNC, ARG1, ...) CONCAT(FUNC(ARG1), FOLD_VA_ARGS_AUX_3(FUNC, __VA_ARGS__))
#define FOLD_VA_ARGS_AUX_5(FUNC, ARG1, ...) CONCAT(FUNC(ARG1), FOLD_VA_ARGS_AUX_4(FUNC, __VA_ARGS__))
#define FOLD_VA_ARGS_AUX_6(FUNC, ARG1, ...) CONCAT(FUNC(ARG1), FOLD_VA_ARGS_AUX_5(FUNC, __VA_ARGS__))
#define FOLD_VA_ARGS_AUX_7(FUNC, ARG1, ...) CONCAT(FUNC(ARG1), FOLD_VA_ARGS_AUX_6(FUNC, __VA_ARGS__))
#define FOLD_VA_ARGS(FUNC, ...) CONCAT(FOLD_VA_ARGS_AUX_, VA_ARGS_SIZE(__VA_ARGS__))(FUNC, __VA_ARGS__)

#define CONCAT_ID(x) x##_

#define CONCAT_ID_WITH_UNDERBAR(...) FOLD_VA_ARGS(CONCAT_ID, __VA_ARGS__)

#define INSTRUCTION_TYPE_ALIAS(...) CONCAT(Inst_, CONCAT_ID_WITH_UNDERBAR(__VA_ARGS__))
