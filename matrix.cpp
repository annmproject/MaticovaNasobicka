#include <iostream> // <- io
#include <utility>  // std::swap
#include <cstdint>  // std::int32t
#include <vector>   // std::vector
#include <chrono>   // <- stopwatch
#include <thread>   // <- threads

/**
 * 
 * @brief The function reads number from standard input.
 * 
 * Scanf or cin is too slow to read 4 million numbers.
 * This is extremely performances function.
 * 
 * @return The function returns readed number from standard 
 * input as 64 bit signed integer.
 * 
 */

std::int32_t getNum() {

    std::int32_t num = 0;
    bool         neg = false;
    char         chr = getchar();

    if(chr == '-') {
        neg = true;
        chr = getchar();
    }

    while(chr >= '0' && chr <= '9') {
        num = (num << 3) + (num << 1) + chr - '0';
        chr = getchar();
    }

    if(neg) {
        num *=-1;
    }

    return num;

}

/**
 * 
 * @brief The function calculates one row of AB matrix.
 * 
 * @param A Reference to matrix A.
 * @param B Reference to matrix B.
 * @param AB Reference to matrix AB.
 * @param A_cols Number of columns of A matrix.
 * @param B_cols Number of columns of B matrix.
 * @param AB_cols Number of columns of AB matrix.
 * @param r Actual row of AB matrix to calculate.
 * 
 */

void calculate_row(std::vector<std::int32_t> &A, std::vector<std::int32_t> &B, std::vector<std::int32_t> &AB, std::int32_t A_cols, std::int32_t B_cols, std::int32_t AB_cols, std::size_t r) {
    for(std::int32_t c = 0; c < AB_cols; c++) {
        std::int32_t sum = 0;
        for(std::int32_t i = 0; i < A_cols; i++) {
            sum += A[r * A_cols + i] * B[c * B_cols + i];
        }
        AB[r * AB_cols + c] = sum;
    }
}


/**
 * 
 * @brief The program multiplies two matrices.
 * 
 * @param argc Number of arguments.
 * @param argv Arguments.
 * 
 * @note The app uses olny basic standard IO.
 * For bigger matrices are better files,
 * like this: "./main < matrices.txt > output.txt".
 * 
 * @note The app uses threads defaultly. To run it
 * only in single thread use switch -singleThread
 * like this: "./main -singleThread < matrices.txt > output.txt".
 * 
 * @return The program return 0 if eversthing is ok, 
 * otherwise returns: 1 - invalid arguments,
 *                    2 - invalid dimensions of matrix A,
 *                    3 - invalid dimensions of matrix B,
 *                    4 - invalid dimensions fof multiplying.
 * 
 */

int main(int argc, char *argv[]) {

    // variables
    std::size_t  i;
    std::int32_t r, c;
    std::int32_t A_rows, A_cols;
    std::int32_t B_rows, B_cols;
    std::int32_t AB_rows, AB_cols;
    std::chrono::high_resolution_clock::time_point start, stop;

    // --help argument
    if(argc == 2 && strcmp(argv[1], "--help") == 0) {
        puts("This is how to use this program...");
        return 0;
    }

    // invalid arguments
    if(argc > 1 && !(argc == 2 && strcmp(argv[1], "-singleThread") == 0)) {
        return 1;
    }

    // matrix A
    if((A_rows = getNum()) < 1 || (A_cols = getNum()) < 1) {
        return 2;
    }

    std::vector<std::int32_t> A(A_rows * A_cols);

    for(i = 0; i < A.size(); i++) {
        A[i] = getNum();
    }

    // Matrix B (will be transposed)
    if((B_rows = getNum()) < 1 || (B_cols = getNum()) < 1) {
        return 3;
    }

    std::vector<std::int32_t> B(B_rows * B_cols);

    for(r = 0; r < B_rows; r++) {
        for(c = 0; c < B_cols; c++) {
            B[c * B_rows + r] = getNum();
        }
    }
    
    std::swap(B_rows, B_cols);

    // stopwatch
    start = std::chrono::high_resolution_clock::now();
    
    // Matrix AB
    AB_rows = A_rows;
    AB_cols = B_rows;

    if(A_cols != B_cols) {
        return 4;
    }

    std::vector<std::int32_t> AB(AB_rows * AB_cols);

    if((AB_rows < 100 && AB_cols < 100) || argc == 2) {
        for(r = 0; r < AB_rows; r++) {
            calculate_row(A, B, AB, A_cols, B_cols, AB_cols, r);
        }   
    }
    else {
        std::vector<std::thread> threads;
        for(r = 0; r < AB_rows; r++) {
            threads.push_back(std::thread(calculate_row, std::ref(A), std::ref(B), std::ref(AB), A_cols, B_cols, AB_cols, r));
        }
        for(i = 0; i < threads.size(); i++) {
            threads[i].join();
        }
    }
    
    // stopwatch
    stop = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken " << std::chrono::duration_cast< std::chrono::duration<double> >(stop - start).count() << " seconds.\n";

    // print
    std::cout << AB_rows << " " << AB_cols << std::endl;
    for(r = 0; r < AB_rows; r++) {
        for(c = 0; c < AB_cols; c++) {
            printf("%s ", std::to_string(AB[r * AB_cols + c]).c_str());
        }
        putchar('\n');
    }

    // return
    return 0;

}
