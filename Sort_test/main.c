#include <stdio.h>
#include <stdlib.h>

typedef enum{
    INSERT_SORT = 1,
    BUBBLE_SORT,
    QUICK_SORT
} enum_sort;

void Swap(int *a, int *b);

void print_O(void){
    printf("    ");
}

void print_arr(int list[], int len){
    printf("[ ");
    int i=0;
    while(i<len){
        printf("%d ", list[i]);
        i++;
    }
    printf("]\n");
}

/* 快速排序法 */
void quick_sort(int arr[], int first_index, int last_index, int len) {
  // 宣告索引變數
  int pivotIndex, temp, index_a, index_b;

  if (first_index < last_index) {
    // 以第一個元素作為基準
    pivotIndex = first_index;
    index_a = first_index;
    index_b = last_index;

    // 以遞增方式排序
    while (index_a < index_b) {
      while (arr[index_a] <= arr[pivotIndex] && index_a < last_index) {
        index_a++;
      }
      while (arr[index_b] > arr[pivotIndex]) {
        index_b--;
      }

      if (index_a < index_b) {
        // 交換元素
        Swap(&arr[index_a], &arr[index_b]);
      }
    }

    // 交換基準元素與 index_b 元素
    Swap(&arr[pivotIndex], &arr[index_b]);

    printf("    --> ");
    print_arr(arr, len);

    // 遞迴呼叫快速排序法函數
    quick_sort(arr, first_index, index_b - 1, len);
    quick_sort(arr, index_b + 1, last_index, len);
  }
}

void Swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* flag means whether need to directly change input list */
int Sorting(enum_sort mode, int list[], int len, int flag)
{
    int dummy_list[len];
    int idx=0;
    while(idx<len){
        dummy_list[idx] = list[idx];
        idx++;
    }

    if ( mode == INSERT_SORT ){
        printf("[Use Insert sorting method]\n");
        printf("    Init array: ");
        print_arr(dummy_list, len);
        for ( int tar_p = 1; tar_p < len; tar_p++ ){
            int cur_p = 0;
            while (cur_p<tar_p){
                if (dummy_list[tar_p] < dummy_list[cur_p]){
                    int tmp = dummy_list[tar_p];
                    int s=tar_p;
                    while(s>cur_p){
                        dummy_list[s] = dummy_list[s-1];
                        s--;
                    }
                    dummy_list[cur_p] = tmp;
                    break;
                }
                cur_p++;
            }
            printf("    --> ");
            print_arr(dummy_list, len);
        }
    }

    else if ( mode == BUBBLE_SORT ){
        printf("[Use Bubble sorting method]\n");
        printf("    Init array: ");
        print_arr(dummy_list, len);
        int check_time = 0;
        while(check_time < len-1){
            for (int i=0; i<len-1-check_time; i++){
                if (dummy_list[i] > dummy_list[i+1]){
                    Swap(&dummy_list[i], &dummy_list[i+1]);
                }
            }
            printf("    --> ");
            print_arr(dummy_list, len);
            check_time++;
        }

    }

    else if ( mode == QUICK_SORT ){
        printf("[Use Quick sorting method]\n");
        printf("    Init array: ");
        print_arr(dummy_list, len);
        quick_sort(dummy_list, 0, len-1, len);
    }

    printf("    Sort array: ");
    print_arr(dummy_list, len);

    idx = 0;
    if (flag){
        while(idx<len){
            list[idx] = dummy_list[idx];
            idx++;
        }
    }
}

int main()
{
    int data_lst[] = {5,3,9,1,2,8};
    int len = sizeof(data_lst)/sizeof(int);
    Sorting(INSERT_SORT, data_lst, len, 0);
    Sorting(BUBBLE_SORT, data_lst, len, 0);
    Sorting(QUICK_SORT, data_lst, len, 0);
    return 0;
}
