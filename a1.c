#include "test.h"

/*
 * Generate k-selections of a[0..n-1] in lexicographic order and call process_selection to process them.
 *
 * The array b[] will have enough space to hold k elements.
 * For a selection i1, ..., ik, you should set b[0] = a[i1], ..., b[k-1] = a[ik].
 * Selections should be generated in lexicographic order.
 * a[0..k-1] is the smallest selection and a[n-k..n-1] is the largest.
 */
void generate_selections(int a[], int n, int k, int b[], void *data, void (*process_selection)(int *b, int k, void *data))
{     
    int temp[k];
    for (int i = 0; i < k; i++) {
        temp[i] = i;
        b[i] = a[i];
    }
    while (1) {
        process_selection(b, k, data);
        int i = k - 1;
        while (i >= 0 && temp[i] == n - k + i) {
            i--;
        }
        if (i < 0) {
            break;
        }
        temp[i]++;
        b[i] = a[temp[i]];
        for (int j = i + 1; j < k; j++) {
            temp[j] = temp[j - 1] + 1;
            b[j] = a[temp[j]];
        }
    }


}

/*
 * See Exercise 2 (a), page 94 in Jeff Erickson's textbook.
 * The exercise only asks you to count the possible splits.
 * In this assignment, you have to generate all possible splits into buf[]
 * and call process_split() to process them.
 * The dictionary parameter is an array of words, sorted in dictionary order.
 * nwords is the number of words in this dictionary.
 */
int isWord(char word[],int start,int end, const char *dictionary[], int nwords) {
    int flag = 0;
    for (int i = 0; i < nwords; i++) {
        if (end-start+1 == strlen(dictionary[i])) {
            flag = 0;
            for (int j = 0; j < strlen(dictionary[i]); j++) {
                if (word[j+start] != dictionary[i][j]) {
                    flag = 1;
                }
            }
            if (flag == 0) {
                return 1;
            }
        }
    }
    return 0;
}
void split(char word[], const char *dictionary[], int nwords, char buf[], int start,int end,int num_space,void *data, void (*process_split)(char buf[], void *data)) {
    if (strlen(buf)==strlen(word)+num_space){
        buf[strlen(buf)-1]='\0';
        process_split(buf,data);
    }
    for (int i=start;i<end+1;i++){
        if (isWord(word,start,i,dictionary,nwords)){
            int i1=strlen(buf);
            for (int j=start;j<i+1;j++){
                buf[j-start+i1]=word[j];
            }
            buf[i+1-start+i1]=' ';
            buf[i+1-start+i1+1]='\0';
            split(word,dictionary,nwords,buf,i+1,end,num_space+1,data,process_split);
            for (int j=start;j<i+2;j++){
                buf[j-start+i1]='\0';
            }
        }
    }
}

void printstr(char buf[], void *data) {
    printf("%s\n", buf);
}

/*
 * Transform a[] so that it becomes the previous permutation of the elements in it.
 * If a[] is the first permutation, leave it unchanged.
 */
void previous_permutation(int a[], int n)
{
     int i = n - 2;
    while (i >= 0 && a[i] <= a[i + 1]) {
        i--;
    }

    if (i >= 0) {
        int j = n - 1;
        while (a[j] >= a[i]) {
            j--;
        }
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
        int left = i + 1;
        int right = n - 1;
        while (left < right) {
            int temp = a[left];
            a[left] = a[right];
            a[right] = temp;
            left++;
            right--;
        }
    }
}

/* Write your tests here. Use the previous assignment for reference. */

int main()
{
    return 0;
}
