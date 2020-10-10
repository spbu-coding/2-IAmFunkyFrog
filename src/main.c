#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

#define INPUT_ARRAY_MAX_SIZE 100
#define stderr_printf(...) fprintf(stderr, __VA_ARGS__)

//Параметры from и from_set_flag (to и to_set_flag) обновляются парами
//Если параметр неактивен, его флаг необходимо установить в 0
struct interval_t {
    long long from;
    long long to;
    int from_set_flag;
    int to_set_flag;
};

int parse_argv(int argc, char* argv[], struct interval_t* out_interval) {
    if(argc < 2)
        return -1;
    if(argc > 3)
        return -2;
    if(argc == 3 && strcmp(strtok(argv[1], "="), strtok(argv[2], "=")) == 0)
        return -3;

    for(int i = 1; i < argc; i++) {
        long long number_in_string;
        if(strncmp(argv[i], "--from", 6) == 0 && out_interval->from_set_flag == 0) {
            number_in_string = strtoll(argv[i] + 7, NULL, 10);
            out_interval->from = number_in_string;
            out_interval->from_set_flag = 1;
        }
        else if(strncmp(argv[i], "--to", 4) == 0 && out_interval->to_set_flag == 0) {
            number_in_string = strtoll(argv[i] + 5, NULL, 10);
            out_interval->to = number_in_string;
            out_interval->to_set_flag = 1;
        }
    }

    if(out_interval->from_set_flag == 0 && out_interval->to_set_flag == 0)
        return -4;

    return 0;
}

int read_array(long long out_array[], int array_max_size, struct interval_t interval) {
    int size = 0;
    char delim;
    long long num;

    do {
        if(scanf("%lli%c", &num, &delim) != 2)
            exit(EXIT_FAILURE);
        if(num <= interval.from && interval.from_set_flag == 1)
            printf("%lli ", num);
        if(num >= interval.to && interval.to_set_flag == 1)
            stderr_printf("%lli ", num);
        if((num > interval.from || interval.from_set_flag == 0) && (num < interval.to || interval.to_set_flag == 0)) {
            out_array[size] = num;
            size++;
        }
    } while (delim != '\n' && size < array_max_size);

    return size;
}

void copy_array(const long long array_from[], long long array_to[], int size) {
    for(int i = 0; i < size; i++)
        array_to[i] = array_from[i];
}

int compare_arrays(const long long array1[], const long long array2[], int size) {
    int difference_count = 0;
    for(int i = 0; i < size; i++) {
        if(array1[i] != array2[i])
            difference_count++;
    }
    return difference_count;
}

int main(int argc, char* argv[]) {

    struct interval_t interval = {0, 0, 0, 0};

    int parse_return_code = parse_argv(argc, argv, &interval);
    if(parse_return_code != 0)
        return parse_return_code;

    int size;
    long long array[INPUT_ARRAY_MAX_SIZE];
    size = read_array(array, INPUT_ARRAY_MAX_SIZE, interval);

    long long *array_copy = (long long*)malloc(size * sizeof(long long));
    if(array_copy == NULL)
        exit(EXIT_FAILURE);
    copy_array(array, array_copy, size);
    sort(array_copy, array_copy + size);
    int swapped_count = compare_arrays(array, array_copy, size);

    return swapped_count;
}
// return code -1 - < 2 params, -2 - > 2 params, -3 - repeat of params, -4 - not valid params