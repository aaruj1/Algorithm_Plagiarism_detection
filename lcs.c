#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#define BUFFER_SIZE 1024

int max(int a, int b);

int lcs_Check(char *source_content, char *test_content, FILE *resultFP) {

    //step 1: Calculate their sizes and use them to allocate 2 dimensional matrix
    int src_len = strlen(source_content);
    int test_len = strlen(test_content);
//    printf("Length of source_content : %d \n", src_len);
//    printf("Length of test_content : %d \n", test_len);

    //step 2: If size of any of the strings is zero report LCS = 0
    if (src_len == 0 || test_len == 0) {
        printf("Size of LCS:: 0\n");
        return 0;
    }

    //step 3: Initialize the two i and j rows/column of the 2D matrix
    int matrix[src_len + 1][test_len + 1];

    for (int i = 0; i <= src_len; i++) {
        for (int j = 0; j <= test_len; j++) {
            matrix[i][j] = 0;
        }
    }

    //step 4: using the lenLCS algorithm calculate the each element of the matrix
    // Calculate the matrix values

    for (int i = 1; i <= src_len; i++) {
        for (int j = 1; j <= test_len; j++) {
            if (source_content[i - 1] == test_content[j - 1]) {
                matrix[i][j] = matrix[i - 1][j - 1] + 1;
            } else {
                matrix[i][j] = max(matrix[i][j - 1], matrix[i - 1][j]);
            }

        }
    }


//  step 5: traverse backward from last element of the matrix and print out the LCS

    char *longest_common_string = (char *) malloc(sizeof(char) * (matrix[src_len][test_len] + 1));
    int strpos = 0;
    int temp = 0;
    int n1 = src_len, n2 = test_len;

    while (n1 > 0 && n2 > 0) {
        temp = matrix[n1][n2];
        if (temp == matrix[n1 - 1][n2]) {
            n1--;
        } else if (temp == matrix[n1][n2 - 1]) {
            n2--;
        } else {
            longest_common_string[matrix[src_len][test_len] - 1 - strpos] = source_content[n1 - 1];
            n1--;
            n2--;
            strpos++;
        }
    }

    char LCS_splitStrings[matrix[src_len][test_len]][matrix[src_len][test_len]];
    int j = 0, cnt = 0;
    for (int i = 0; i <= (strlen(longest_common_string)); i++) {
        if (longest_common_string[i] == ' ' || longest_common_string[i] == '\0') {
            LCS_splitStrings[cnt][j] = '\0';
            cnt++;
            j = 0;
        } else {
            LCS_splitStrings[cnt][j] = longest_common_string[i];
            j++;
        }
    }
    int numword_lcs = cnt;

    char test_splitStrings[test_len][test_len];
    j = 0, cnt = 0;
    for (int i = 0; i <= (strlen(test_content)); i++) {
        if (test_content[i] == ' ' || test_content[i] == '\0') {
            test_splitStrings[cnt][j] = '\0';
            cnt++;
            j = 0;
        } else {
            test_splitStrings[cnt][j] = test_content[i];
            j++;
        }
    }
    int numword_test_content = cnt;
    j = 0;
    cnt = 0;

    char final_common_words[matrix[src_len][test_len]];
    for (int i = 0; i < numword_lcs; i++) {
        for (int k = 0; k < numword_test_content; k++) {
            if (strcmp(test_splitStrings[k], LCS_splitStrings[i]) == 0) {
                strcat(final_common_words, " ");
                strcat(final_common_words, test_splitStrings[k]);
                break;
            }
        }
    }

    fprintf(resultFP, "\n=====================================================================================\n");
    fprintf(resultFP, "Source File Content : \n%s\n", source_content);
    fprintf(resultFP, "\nTest File Content : \n%s\n", test_content);

    double percentage = (matrix[src_len][test_len] * 100 / test_len);
    fprintf(resultFP, "\n\nLength of LCS Pattern : %d", matrix[src_len][test_len]);
    fprintf(resultFP, "\nLCS Found : %s\n", longest_common_string);
    fprintf(resultFP, "Percentage of LCS pattern match : %3.1f %% \n", percentage);
//    printf("\n");


    percentage = ((strlen(final_common_words) - 1) * 100 / test_len);
    fprintf(resultFP, "\n\nFinal common words length: %ld", strlen(final_common_words));
    fprintf(resultFP, "\nFinal common words :: %s\n", final_common_words);
    fprintf(resultFP, "Percentage of Plagiarism : %3.1f %% \n", percentage);
//    printf("\n");

    return 0;

}


int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Enter command in form of ./LCS_Plagiarism_Detect sourceFile testFile\n");
        exit(0);
    }
    FILE *srcFP, *testFP, *resultFP;
    char source_content[BUFFER_SIZE];
    char test_content[BUFFER_SIZE];
    clock_t start, end;
    double cpu_time_used;

    if ((srcFP = fopen(argv[1], "r")) == NULL) {
        perror("Error while opening source file");
        exit(1);
    }

    if ((testFP = fopen(argv[2], "r")) == NULL) {
        perror("Error while opening test file");
        exit(1);
    }

    if ((resultFP = fopen("Result.txt", "w")) == NULL) {
        perror("Error while opening Result file");
        exit(1);
    }

    fgets(test_content, BUFFER_SIZE, testFP);

    //fgets(source_content, BUFFER_SIZE, srcFP);

    int size = 0;
    while (fgets(source_content, BUFFER_SIZE, srcFP)) {
//        printf("%s", source_content);
        start = clock();

        lcs_Check(source_content, test_content, resultFP);

        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        fprintf(resultFP, "Execution time: %f seconds\n", cpu_time_used);
        fprintf(resultFP,
                "\n\n=====================================================================================\n");
    }
    return 0;
}


int max(int a, int b) {
    if (a >= b) return a;
    else return b;
}
