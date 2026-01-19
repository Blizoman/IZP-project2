//This program was made to find geometric shapes in text file given by user.
//xblizna00 - IZP - second project
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//////////////////////////////////////////////////////////////////////////////////////////////////
////////// DEFINES ///////////////////////////////////////////////////////////////////////////////

#define DIMENSION 2 //Correct number of parametres for resolution ('file_format' and 'tester')
#define MINIMAL_SIZE 1 //Correct type of parametres for resolution ('file_format' and 'tester') 
#define SINGLE_ELEMENT 1 //Correct number of 'loads' for one pixel ('file_format' and 'tester')
#define BLACK 1 //Representing 'Black' pixel value
#define SEARCHER 1 //Representing type of operation that user choosen ('arguments_format')
#define FYLE 2 //Representing given file by the user 
#define HELP 2  //Number of arguments entered by user
#define GEOMETRY 3 //Number of arguments entered by user
#define R1 0 //Coordinates of geometric shape that was searched by program
#define C1 1
#define R2 2
#define C2 3 
#define DEFAULT -1 //Default maximal distance ('square')
//////////////////////////////////////////////////////////////////////////////////////////////////
////////// RETURNS ///////////////////////////////////////////////////////////////////////////////

enum return_values{PASS, NOT_FILE, IAOARG, WRONG_INPUT, FILE_CHECK, TEST_CHECK, BLANK}; 
//(IAOARG) -> 'INCORRECT_AMOUNT_OF_ARGUMENTS'
//////////////////////////////////////////////////////////////////////////////////////////////////
////////// FUNCTIONS /////////////////////////////////////////////////////////////////////////////
////////// PRIORITY FUNCTIONS ////////////////////////////////////////////////////////////////////

int arguments_format(int argc, char* argv[], FILE* picture);
int file_format(FILE* picture, bool vline_checker, bool square_checker); 
int tester(FILE* picture);
////////// HELP FUNCTIONS ////////////////////////////////////////////////////////////////////////

int loader(FILE* picture, int** storage, int rows, int cols, int cookie);
int** array_health(int rows, int cols);  
bool is_file(FILE* picture); 
void coordinates(int* pole);
void swapper(int* numero, int* numerum);
////////// GEOMETRY FUNCTIONS ////////////////////////////////////////////////////////////////////

int line_maker(int** storage, int rows, int cols, bool vline_checker);
int** transpose(int** storage, int rows, int cols, bool vline_checker);
int square(int** storage, int rows, int cols);
////////// MESSAGE FUNCTIONS /////////////////////////////////////////////////////////////////////

void alloc_fail();
void help();
void helper();
//////////////////////////////////////////////////////////////////////////////////////////////////
////////// CODE //////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]){                           //Loading file...
    FILE* picture = fopen(argv[FYLE], "r");                 //Variable that obtain value of
    int end_value = arguments_format(argc, argv, picture);  //function 'arguments_format' for  
    return end_value;                                       //is used as return value of our  
}                                                           //program
                                                           
/**
 * @brief Second main, checks for given arguments at the beggining of program.
 * 
 * This function is used as a checker of given arguments to be searched and properly used by 
 * program.
 * Firstly it looks trough the number of entered arguments which should be from '2' to '3', than
 * it
 * compares the given arguments with our static options (arguments that are allowed to be used).
 * @param argc Number of entered arguments at the start of program.
 * @param argv Pointer to given arguments ar the start of program.
 * @param picture Loaded file for reading.
 * 
 * @return 
 * '0' - If everything went right, the file is 'Valid' and can be used for our program.
 * 
 * '1' - If given file as argument can not be used.
 * 
 * '2' - If user input wrong amount of arguments at the start of program.
 * 
 * '3' - If given argument was not recognized by program.
 * 
 * '4' - If something failed while program tryied to load data from file.
 */
int arguments_format(int argc, char* argv[], FILE* picture){
    int end_value = 0;                                      //Return value from other functions
    bool vline_checker = false;                             //Boolean values depending on user 
    bool square_checker = false;                            //depending on user input
    if (argc == HELP && strcmp(argv[SEARCHER],"--help") == 0){
        help();
        return PASS;
    }   
    else if(argc == GEOMETRY){                              //Checking number of given arguments
        if(is_file(picture)){                               
            if(strcmp(argv[SEARCHER],"test") == 0){
                end_value = tester(picture);
            }
            else if(strcmp(argv[SEARCHER],"hline") == 0){
                end_value = file_format(picture, vline_checker, square_checker);
            }
            else if(strcmp(argv[SEARCHER],"vline") == 0){
                vline_checker = true;
                end_value = file_format(picture, vline_checker, square_checker);
            }
            else if(strcmp(argv[SEARCHER],"square") == 0){
                square_checker = true;
                end_value = file_format(picture, vline_checker, square_checker);
            }
            else{
                helper();
                fclose(picture);
                return WRONG_INPUT;
            }
            fclose(picture);
            return end_value;
        }
        else{
            helper();
            return NOT_FILE;
        }
    }
    else{
        helper();
        return IAOARG;
    } 
}

/**
 * @brief Create whole matrix, at the end it decide, where the user input will root.
 * 
 * This function is called, after the allocation of an array to fill it with caracters
 * from given bitmap (picture). It use function to scan for elements inside a file, 
 * check if they can be used by our program, accepting only '0' as white and '1' as black.
 * @param picture Loaded file for reading.
 * @param vline_checker Boolean, set at the beggining of program, holding 'true' or 'false' 
 * expression.
 * @param square_checker Boolean, set at the beggining of program, holding 'true' or 'false' 
 * expression.
 * @return 
 * '4' - If dimension of matrix can not be used, if they failed to be loaded or if they contain
 * unallowed numbers. Also it is returned, when allocation of matrix failed, or 
 * if 'loader' found unallowed caracters inside bitmap.
 * 
 * '0' - If everything went alright.
 */
int file_format(FILE* picture, bool vline_checker, bool square_checker){
    int rows = 0;                                           //Resolution of picture (rows)
    int cols = 0;                                           //Resolution of picture (columns)
    int cookie = 0;                                         //Variable for every pixel
    if(fscanf(picture, "%i %i", &rows, &cols) != DIMENSION){
        helper();                                           //1) Getting resolution values
        return FILE_CHECK;                                                                 
    } 
    if(rows < MINIMAL_SIZE || cols < MINIMAL_SIZE){         //2) Controling if resolution is valid
        helper();
        return FILE_CHECK; 
    }

    int** storage = array_health(rows, cols);               //3) Allocation of 2D array
    if (storage == NULL){                                   
        alloc_fail();     
        return FILE_CHECK;                                  
    }

    int pixel = loader(picture, storage, rows, cols, cookie);           
                                                            //4) Loading every pixel to and array
    
    if(pixel == FILE_CHECK){                                //5) Controlling if every pixel  
        return FILE_CHECK;                                  // is valid
    }
    else if(vline_checker){                                 //5a) Checking if user searched for 
        transpose(storage, rows, cols, vline_checker);      // vertical line                      
    }
    else if(square_checker){                                //5b) Checking if user searched for 
        square(storage, rows, cols);                        // square
    }
    else{
        line_maker(storage, rows, cols, vline_checker);     //5c) Checking if user searched for 
    }                                                       // horizontal line

    for (int i = 0; i < rows; i++){                         //6) Releasing a 2D array allocated 
        free(storage[i]);                                   // before
    }
    free(storage);                  
    return PASS;
}

/**
 * @brief Tests, if given file can be runned correctly by program.
 * 
 * Firstly, it checks if the resolution/dimension of the matrix(picture), was loaded correctly,
 * focusing if the numbers are greater than 0. After correct resolution, it starts to load
 * the black and white pixels, one by one checking them if they contain only allowed numbers,
 * '0' or '1'. At the end, the function is checking if there in no more numbers in the file. 
 * If there is, it will be counted as the invalid picture.
 * @param picture Loaded file for reading.
 * @return 
 * '0' - If everything went right, the file is 'Valid' and can be used for our program.
 * 
 * '5' - If something from above failed, status of file will be 'Invalid'.
 */
int tester(FILE* picture){                             
    int rows = 0;                                           //Resolution of picture (rows)
    int cols = 0;                                           //Resolution of picture (columns)
    if(fscanf(picture, "%i %i", &rows, &cols) != DIMENSION){         
        helper();                                           //1) Getting resolution values
        return TEST_CHECK;                                               
    }
    if(rows < MINIMAL_SIZE || cols < MINIMAL_SIZE){         //2) Controling if resolution is valid
        helper();
        return TEST_CHECK; 
    }
    int tester_cookie = 0;                                  //Variable for every pixel
    int tester_counter = 0;                                 //Variable for counting pixels

    while(tester_counter != rows*cols){                     //3) Go trough all pixels
        if(fscanf(picture, "%i", &tester_cookie) != SINGLE_ELEMENT){
            helper();                                       //4) Check if load of pixel was
            return TEST_CHECK;                              // successful
        }
        if(tester_cookie != 0 && tester_cookie != BLACK){   //5) Check if the pixel is 'black' or
            helper();                                       // 'white'
            return TEST_CHECK;                                           
        }
        tester_counter++;
    }
    printf("Valid\n");                 
    return PASS;
}

/**
 * @brief Load pixels from given file to array.
 * 
 * This function is called, after the allocation of an array to fill it with caracters
 * from given bitmap (picture). It use function to scan for elements inside a file, 
 * check if they can be used by our program, accepting only '0' as white and '1' as black.
 * @param picture Loaded file for reading.
 * @param storage Pointer to pointer to an array where the bitmap pixels are stored.
 * @param rows Represents number of rows.
 * @param cols Represents number of columns.
 * @param cookie Integer, everytime represents one pixel from bitmap.
 * 
 * @return 
 * '4' - If pixel (cookie) does not store '0' or '1' (allowed caracters).
 * 
 * '**storage' - Giving back a pointer to a pointer to an array (matrix) containing pixels 
 * of bitmap.
 */
int loader(FILE* picture, int** storage, int rows, int cols, int cookie){
    for(int i = 0; i < rows; i++){                          
        for(int j = 0; j < cols; j++){
            if(fscanf(picture, "%i", &cookie) != SINGLE_ELEMENT){
                helper();
                return FILE_CHECK;                  
            }                                               //Loading every pixel inside file to 
            if(cookie != 0 && cookie != BLACK){             //storage (matrix) after the load
                helper();                                   //was from file was successful and
                return FILE_CHECK;                          //pixel was only 'black' or 'white'
            }
            storage[i][j] = cookie;
        }
    }
    return **storage;
}

/**
 * @brief Allocating an 2D array for data from given file.
 * 
 * This function is called for create (allocate) an array (storage) for data (pixels) given
 * by file. It uses a dimension of rows and columns to create a matrix of needed size.
 * (Inspired by Dr. Jakub H.)
 * @param rows Represents number of rows.
 * @param cols Represents number of columns.
 * 
 * @return 
 * 'NULL' - If allocation of new array failed.
 * 
 * 'storage' - Returning an allocated 2D array (matrix).
 */
int** array_health(int rows, int cols){
    int** storage = malloc(sizeof(int*) * rows);            //Allocating firstly 'rows'
    if (storage != NULL){                                   //Checking if allocation succeeded
        for(int i = 0; i < rows; i++){                      //Going trough every 'row'...
            storage[i] = malloc(sizeof(int) * cols);        //Allocating 'columns' of matrix
            if (storage[i] == NULL){                        //If allocation failed, every
                for (int j = i-SINGLE_ELEMENT; j >= 0; j--){//allocation before need to be freed
                    free(storage[j]); 
                }
                free(storage); 
                return NULL;          
            }
        }
    }
    else{
        return NULL; 
    }
    return storage;
}

/**
 * @brief Checks, if given file can be opened.
 * 
 * @param picture Loaded file for reading.
 * @return 
 * 'true' - If given file can be opened.
 * 
 * 'false' - If given file can not be opened.
 */
bool is_file(FILE* picture){
    if (picture == NULL){
        return false; 
    }
    return true;
}

/**
 * @brief Prints a coordinates of searched geometric shape.
 * 
 * This function is used to print a coordinates of largest geometric shape that was serached.
 * It could be horizontal line, vertical line or square. First two numbers represents starting
 * point, his row and column position and the other two numbers represents a destination point of
 * geometric shape, also his row and column position 
 * @param array Pointer to an array containing coordinates of geomtric shape.
 */
void coordinates(int* array){  
    printf("%i %i %i %i\n", array[R1], array[C1], array[R2], array[C2]);
}

/**
 * @brief Swaps the values between two integer values
 *
 * When called, it will switch entered values of entered variables(integers).
 * Using temporary variable to store value of first integer, than it change value
 * of first integer to second and after a value of second integer obtain value 
 * from temporary variable.
 *
 * @param numero Pointer of first integer, after the swap, it will obtain value of second integer.
 * @param numerum Pointer of second integer, after the swap, it will obtain value of first 
 * integer.
 */
void swapper(int* numero, int* numerum){        
    int temporary = *numero;                                //Temporary variable to store value
    *numero = *numerum;
    *numerum = temporary;
}

/**
 * @brief Searching for a line inside given bitmap.
 * 
 * This function is called inside 'file_format' function, to find longest horizontal line or,
 * it could be called inside 'transpose' function after the rotation of matrix to search for 
 * longest vertical line. It saves an integer representing 'distance' of lines. When new distance
 * is greater than 'max_distance', the coordinates of longest line are rewritten. Also 
 * 'max_distance' obtain current value from 'distance'. By this process, we will always safe
 * values of longest line inside given bitmap.  
 * @param storage Pointer to pointer to an array where the bitmap pixels are stored.
 * @param rows Represents number of rows.
 * @param cols Represents number of columns.
 * @param vline_checker Boolean, set at the beggining of program, holding 'true' or 'false' 
 * expression.
 * 
 * @return 
 * '6' - If all pixels (numbers) are white ('0'), so there is not a line.
 * 
 * '0' - If everything went alright.
 */
int line_maker(int** storage, int rows, int cols, bool vline_checker){
    int dim_store[] = {0, 0, 0, 0};                         //Array for coordinates of actual line
    int arr[] = {0, 0, 0, 0};                               //Array for coordinates of longest line
    int max_distance = 0;                                   //Distance of longest line
    int dim_store_len = sizeof(dim_store) / sizeof(dim_store[R1]);
    for(int i = 0; i < rows; i++){                         
        int distance = 0;                                   //Distance of actual line
        for (int j = 0; j < cols; j++){      
            if(storage[i][j] == BLACK){                     //If pixel is 'black', temporary array
                dim_store[R1] = i;                          //obtain coordinates of actual line
                dim_store[C1] = j-distance;
                dim_store[R2] = dim_store[R1];
                dim_store[C2] = dim_store[C1]+distance;     
                distance++;
            }
            else{
                if (max_distance < distance){               //After it compares distances, if our
                    max_distance = distance;                //actual line has greater 'distance'
                    for (int k = 0; k < dim_store_len; k++){//than is a 'max_distance', longest       
                        arr[k] = dim_store[k];              //line (coordinates) will be changed
                    }                                       //and distance will be reseted.
                }
                distance = 0;
            }
        }
        if (max_distance < distance){                       //At the end of row we could ended
            max_distance = distance;                        //with '1', so distance was not
            for (int k = 0; k < dim_store_len; k++){        //reseted, we need to check one
                arr[k] = dim_store[k];                      //last time for actual distance
            }                                               //before we move to another row.
        }
    }
    if (max_distance == 0){                                 //If no 'black' pixel was found.
        printf("Not found\n");
        return BLANK;
    }

    if (vline_checker){                                     //By transposing our matrix in
        swapper(&arr[R1], &arr[C1]);                        //function 'transpose', we need to 
        swapper(&arr[R2], &arr[C2]);                        //swap the coordinates of line.
    }
    coordinates(arr);                                       //Printing coordinates of 'line'.
    return PASS;
}

/**
 * @brief Transposing a matrix.
 * 
 * This function is called, when user searched for vertical line. Firstly, it use
 * 'swapper' function to swap values of 'rows' and 'cols', after it calls function
 * 'array_health' to allocate a new array with swapped dimensions of rows and columns.
 * After that a function 'line_maker' is called and a created array (new_storage) is freed.
 * @param storage Pointer to pointer to an array where the bitmap pixels are stored.
 * @param rows Represents number of rows.
 * @param cols Represents number of columns.
 * @param vline_checker Boolean, set at the beggining of program, holding 'true' or 'false' 
 * expression.
 * 
 * @return 
 * 'NULL' - If allocation of new array failed.
 * 
 * '0' - If everything went alright.
 */
int** transpose(int** storage, int rows, int cols, bool vline_checker){ 
    swapper(&rows, &cols);                                  //Function called to switch 'rows'and
    int** new_storage = array_health(rows,cols);            //'columns' values, than allocate a
    if (new_storage == NULL){                               //new 'storage' where the data from
        alloc_fail();                                       //'storage' will be stored.
        return NULL;                                        //'alloc_fail' is controlling an
    }                                                       //allocation of 'new_storage'.
    for (int i = 0; i < rows; i++){                         
        for (int j = 0; j < cols; j++){                     //Going trough every row and every
            new_storage[i][j] = storage[j][i];              //column of 'new_storage', program
        }                                                   //is copying values from default matrix
    }                                                       //to the new one.
    
    line_maker(new_storage, rows, cols, vline_checker);     //After this process, 'line_maker' is 
    for (int i = 0; i < rows; i++){                         //called but with first parameter
        free(new_storage[i]);                               //representing 'new_storage', to find
    }                                                       //longest vertical line inside matrix.
    free(new_storage);                                      //After that process, 'new_storage' is
                                                            //freed.
    return PASS;
}

/**
 * @brief Searching for a square inside given bitmap.
 * 
 * This function is called inside 'file_format' function, to find biggest square
 * inside given bitmap (matrix). This function uses a loop for distance index, inside which 
 * are two more loops which controls a distances of two vertical and two horizontal lines.
 * If those lines contains only black ('1') pixels (numbers), boolean 'is_square' remain
 * as 'true' and than a an actual 'distance' is being compared with 'max_distance' (representing 
 * a distance of biggest square). If 'distance' is greater, than the coordinates of square are
 * rewritten and a loop for distance is searching for a squares with greater distance at the 
 * current pixel. Otherwise, a loop for distance is being breaked and a program continue to 
 * look trough other pixels.
 *  a distance is being enlarged
 * @param storage Pointer to pointer to an array where the bitmap pixels are stored.
 * @param rows Represents number of rows.
 * @param cols Represents number of columns.
 * 
 * @return 
 * '6' - If all pixels (numbers) are white ('0'), so there is not a square.
 * 
 * '0' - If everything went alright.
 */
int square(int** storage, int rows, int cols){
    int dim_store[] = {0, 0, 0, 0};                         //Array for coordinates of square
    int max_distance = DEFAULT;                             //Maximal distance before the
    for (int i = 0; i < rows; i++){                         //program searched for squares
        for (int j = 0; j < cols; j++){                     //Going trough every pixel
            if(storage[i][j] == BLACK){                     //Looking for 'black' pixels
                for (int distance = 0; (i+distance) < rows && (j+distance) < cols; distance++){  
                    bool is_square = true;                  //Loop for distance controlling if
                                                            //index of pixel with distance will
                                                            //not look outside of matrix.
                                                            //Setting 'is_square' defaultly as                  
                    for (int a = j; a <= j+distance; a++){  //true. 
                        if(storage[i][a] != BLACK || storage[i+distance][a] != BLACK){//TOP+BOTTOM
                            is_square = false;              //After we check both horizontal lines
                            break;                          //one defaultly starts at pixel 
                        }                                   //position, second one is on the same 
                    }                                       //column but on different row by 
                    for (int b = i; b <= i+distance; b++){  //by distance
                        if(storage[b][j] != BLACK || storage[b][j+distance] != BLACK){//LEFT+RIGHT
                            is_square = false;              //Same with vertical lines, they are
                            break;                          //on same row but different column.
                        }                                   //If the pixels passed by those lines
                    }                                       //are not 'black', loop for lines will
                                                            //break and program will continue with
                                                            //another 'distance'. If loops for 
                    if(is_square){                          //lines not break, 'is_square' remain
                        if(max_distance < distance){        //as 'true', program will check if
                            max_distance = distance;        //'max_distance' can be updated by
                            dim_store[R1] = i;              //actual distance. This will result,
                            dim_store[C1] = j;              //that 'dim_store' will store biggest
                            dim_store[R2] = i+distance;     //square coordinates that he has found
                            dim_store[C2] = j+distance;     //yet.
                        }
                    }
                }
            }
        }
    }
    if(max_distance < 0){
        printf("Not found\n");                              //If no 'black' pixel was found.
        return BLANK;
    }
    coordinates(dim_store);                                 //Printing coordinates of 'square'.
    return PASS;
}

/**
 * @brief Prints an error message to the standard error.
 * 
 * This function is used to print 'Invalid' to the standard error (stderr).
 * Used, when conditions of the program were unfulfilled.
 */
void helper(){
    fprintf(stderr,"Invalid\n");
}

/**
 * @brief Prints an error message to the standard error.
 * 
 * This function is used to print that allocation has failed to the standard error (stderr).
 * Used, when allocation of an array failed and can not be used.
 */
void alloc_fail(){
    fprintf(stderr,"ERROR: Allocation failed !\n");
}

/**
 * @brief Prints a helpful message (instructions).
 * 
 * This function is used to print instructions, if user need some advices how to use the program correctly.
 */
void help(){
    printf("This program was made to find longest vertical or horizontal lines ");
    printf("and squares\nin monochromatic picture given by user as the arguments ");
    printf("at the start of the program. The results will be shown as numbers, \n"); 
    printf("representing coordinates where the geometric shape begind and ends.\n");
    printf("Here are some tips to how to use ");
    printf("the program and how to properly start it...\n");
    printf("1.\n");
    printf("Type './figsearch test file.txt' to see ");
    printf("if the program will be started safely. It should return 'Valid' if file\n");
    printf("is able to be used by program or 'Invalid' if file is not able to be used\n");
    printf("by program.\n");
    printf("2.\n");
    printf("Type './figsearch hline file.txt' to find longest horizontal line.\n");
    printf("For example: 'file.txt' is represented\n");
    printf("as matrix:");
    printf("4 5\n");
    printf("0 0 1 1 1\n");
    printf("0 0 1 0 1\n");
    printf("1 0 1 1 1\n");
    printf("1 1 1 1 1\n");
    printf("'hline' should return coordinates: 3 0 3 4, that represents last line containing\n");
    printf("only '1s'(black pixels). Number '4' represents number of rows and number '5'\n");
    printf("represents number of columns in matrix(picture).\n");
    printf("3.\n");
    printf("Type './figsearch vline file.txt' to find longest vertical line.\n");
    printf("As example we will use 'file.txt' above...\n");
    printf("'vline' should return coordinates: 0 2 3 2, that represents third column containing\n");
    printf("only '1s'(black pixels).\n");
    printf("4.\n");
    printf("Type './figsearch square file.txt' to find the biggest square.\n");
    printf("As example we will use 'file.txt' above...\n");
    printf("'square' should return coordinates: 0 2 2 4, that represents beggining coordinates at \n");
    printf("first line and third column and end coordinates at third line and fifth column of square.\n");
}