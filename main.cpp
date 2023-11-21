#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <ostream>
#include <iomanip>
#include <cmath>
#include <cctype>
#include <cstring>

using namespace std;

/**************************************************************
Programmer:	Chin Pei Wern
Name: 		FileName

task:			get filename from user and make sure the filename is valid
data in:	    -
data returned:	infile
Referred to:	-
**************************************************************/
ifstream FileName()
{
    string name;
    cout << endl << "-------------------WELCOME TO BASIC DATA ANALYSIS APPLICATION-----------------" << endl << endl;
    cout << "Please enter filename: " << endl;
    cin >> name;
    ifstream infile;
    infile.open(name);
    while (!infile)
    {
        cerr << "Error! File not found. Please re-enter filename." << endl;
        cerr << "Make sure the file is located inside the same folder as the cpp file" << endl;
        cin >> name;
        infile.open(name);
    }
    return infile;
}

/**************************************************************
Programmer:	Chin Pei Wern
Name: 		readHeader

task:			read the title of each columns inside data file and store them inside a vector called headers.
data in:	    infile, total number of rows and columns of the data file, an empty vector to store title of each column
data returned:	-
Referred to:	http://www.cplusplus.com/reference/sstream/stringstream/stringstream/
**************************************************************/
void readHeader(ifstream &infile, int &totalColumns, int &totalRows, vector<string> &header)
{
    string headers, title;
    infile >> totalColumns;
    infile >> headers;

    stringstream split(headers);

    while (getline(split,title,','))
    {
        header.push_back(title);
    }
    infile >> totalRows;
}

/**************************************************************
Programmer:	Chin Pei Wern
Name: 		readData

task:			read every rows and columns of data into a 2d vector
data in:	    infile, 2d vector called data
data returned:	-
Referred to:	http://www.cplusplus.com/reference/sstream/stringstream/stringstream/
**************************************************************/
void readData(ifstream &file, vector< vector<int> > &array)
{
    string line, info;

    int j=0;
    file.ignore();
    while(getline(file, line))
    {
        stringstream sep(line);
        vector <int> i;
        while (getline(sep, info, ','))
        {
            stringstream convertor(info);
            int x = 0;
            convertor >> x;
            i.push_back(x);
        }
        array.push_back(i);
        j++;
    }
    file.close();
}

/**************************************************************
Programmer:	Chin Pei Wern
Name: 		detectFormatError

task:			detect if the user file format does not comply with the description
data in:	    vector of data, total number of columns and rows.
data returned:	-
Referred to:	-
**************************************************************/
void detectFormatError(const vector<vector<int>> vect, const int numOfCols, const int numOfRows)
{
    if (vect.size() != numOfRows)
    {
        cout << "Format error detected. Number of rows is incorrect." << endl;
        exit(-1);
    }
    for (int row=0; row < numOfRows; row++)
    {
        if (vect[row].size() != numOfCols)
        {
            cout << "Format error detected. Number of columns in row " << row+1 << " is incorrect" << endl;
            exit(-1);
        }
    }
}

/**************************************************************
Programmer:	Chin Pei Wern
Name: 		saveUserInput

task:			get user input on whether they would like to save data into a file
data in:	    -
data returned:	boolean data type, true if user wants to save and otherwise, false
Referred to:	-
**************************************************************/
bool saveDataInput()
{
    char userInput;
    cout << "Do you want to save data into a file?" << endl;
    cout << "(Y/N)" << endl;
    cin >> userInput;

    while ((toupper(userInput) != 'Y') && (toupper(userInput) != 'N'))
    {
        cout << "Input Error! Please input either Y or N :" << endl;
        cin >> userInput;
    }
    if (toupper(userInput) == 'Y')
        return true;

    else if (toupper(userInput) == 'N')
    {
        system("CLS");
        return false;
    }

}
/**************************************************************
Programmer:	Chin Pei Wern
Name: 		htmlortxt

task:			get user input for their file type
data in:	    -
data returned:	type of file user wants in char data type
Referred to:	-
**************************************************************/
int htmlortxt()
{
    char filetype;
    cout << endl << "Choose file format: " << endl;
    cout << "1. HTML" << endl << "2. txt" << endl;
    cin >> filetype;
    while ((filetype != 49) && (filetype != 50))
    {
        cout << "\tInput Error! Please input either 1 or 2 :" << endl;
        cin >> filetype;
    }
    return filetype;
}

/**************************************************************
Programmer:	Chin Pei Wern
Name: 		userInputFileName

task:			get user input for the name of new file and create a file of that name
data in:	    file type
data returned:	new file
Referred to:	-
**************************************************************/
ofstream userInputFileName(int type)
{
    string filename;
    ofstream outfile;
    cout << "Enter file name: " << endl;
    getline(cin, filename);
    if (type == 50)
    outfile.open(filename + ".txt", ios::out | ios::app);
    else if (type == 49)
    outfile.open(filename + ".html", ios::out | ios::app);
    return outfile;

}
/**************************************************************
Programmer:	Chin Pei Wern
Name: 		UserInput

task:			get user input for which column to generate data for
data in:	    title of each columns and total number of columns
data returned:	column number of the data user wants
Referred to:	-
**************************************************************/
int UserInput(const vector <string> header, const int COLS)
{
    int column;
    cout << "\tPlease input the column to generate data for: " << endl;
    for (int i=1 ; i < header.size(); i++)      //loop for subscript smaller than the vector size
    {
        cout << "\t- Column " << i+1 << " : " << header[i] << endl;   //print out header name
    }
    cin >> column;

    while (column < 2 || column > COLS)       //if user input is not in range
    {
        cout << "\tError! Invalid Input." << endl;
        cout << "\tPlease re-enter the column to generate data for: " << endl;
        cin >> column;
    }
    //system("CLS");
    return column;

}

/**************************************************************
Programmer:	Chin Pei Wern
Name: 	    distNum

task:			find all the distinct numbers in a certain column and put then into a vector.
data in:	    data in 2d vector, total number of rows, and the column to find all the distinct numbers for.
data returned:	distinct numbers of the column in vector.
Referred to:	-
**************************************************************/
vector<int> distNum(const vector <vector <int>> data, const int totalRows, const int COL)
{
    vector<int> distinctNum;

    bool flag[totalRows];
    for (int j=0; j < totalRows; j++)
        flag[j] = false;

    for (int row=0; row < totalRows; row++)
    {
        int j = row+ 1;             // j is the variable for element to compare first variable with
        if (flag[row] == false)     //if the element == true, it will skip the loop as the element has been compared before
        {
            for (int j= row+1;j < totalRows; j++)
            {
                if (data[row][COL] == data[j][COL])
                   flag[j] = true;      //if there is a number same with the number being compared to, the flag will be
            }                           //changed to true.
            distinctNum.push_back(data[row][COL]);    //if same numbers, array of distinctNum will push back the number.
        }
    }
    return distinctNum;
}

/**************************************************************
Programmer:	Chin Pei Wern
Name: 		freqOfDistNum

task:			find the frequency of every distinct number
data in:	    data in 2d vector, total number of rows, and the column to find the frequency of data for.
data returned:	frequencies of distinct numbers of the column in vector.
Referred to:	-
**************************************************************/
vector<int> freqOfDistNum(const vector<vector <int>> data, const int totalRows, const int COL)
{
    vector<int> frequency;

    bool flag[totalRows];
    for (int j=0; j < totalRows; j++)
        flag[j] = false;

    for (int row=0; row < totalRows; row++)
    {   int counter = 1;
        //int j = row+ 1;
        if (flag[row] == false)
        {
            for (int j= row+1;j < totalRows; j++)
            {
                if (data[row][COL] == data[j][COL])
                {
                    flag[j] = true;
                    counter += 1;
                }
            }
            frequency.push_back(counter);
        }
    }
    return frequency;
}
/**************************************************************
Programmer  : Nurul Syaqeera
Name        : saveDistNumfreq

task        : This function will save data output in text file
data in     : List of vector arrays in selected column that have been computed
              as Distinct Number and its frequency
data returned: data will be returned as output in text file
Referred to : -
**************************************************************/
void saveDistNumfreq(ofstream &outfile, const vector<int> distinctNum,const vector<int> frequency, const vector<string>header, const int col)
{
    outfile << "\t ------ DISTINCT NUMBER AND ITS FREQUENCY ------" << endl;            //
    outfile << endl;
    outfile << "\t\tTITLE : " << header[col] << endl << endl;
    outfile << "\t -----------------------------------------------" << endl;
    outfile << "\t|" << setw(25) << "DISTINCT NUMBER" << " | " << setw(15) << "FREQUENCY" << "\t|" << endl;
    outfile << "\t|-----------------------------------------------|" << endl;
    for (int size=0; size < distinctNum.size(); size++)
        outfile << "\t|" << setw(25) << distinctNum[size] << " | " << setw(15) << frequency[size] << "\t|" << endl;

    outfile << "\t ----------------------------------------------- " << endl << endl;
}

/*******************************************************************************
Programmer: Ng Yoong Kee
Name: printDistNumNFreqHtml

task: output the distinct numbers and its frequency into html file.

data in: outfile, header, 2D vector of data, total number of rows and columns
data returned: -
Referred to: -
********************************************************************************/
void printDistNumNFreqHtml(ofstream &outfile, const vector<string>header, const vector<vector <int>> arr, const int numOfRows, const int col)
{
    outfile << "<h2 style=\"text-align:center;\">DISTINCT NUMBER AND ITS FREQUENCY</h2>" << endl
            << "<style>table, th, td {border: 1px solid black;}</style> "<<endl;

        vector <int> distinctNum = distNum(arr, numOfRows, col);
        vector <int> frequency = freqOfDistNum(arr, numOfRows, col);
        outfile << "<h3>TITLE : " << header[col] << "</h3>" << endl
                << "<table style=\"width:70%;background-color:#3A638C\">" << endl
                << "<tr>"<< endl << "<th>DISTINCT NUMBER</th>" << endl <<"<th>FREQUENCY</th>" <<endl<< "</tr>" <<endl;
        for (int size=0; size < distinctNum.size(); size++)
        {
            outfile << "<tr>"<< endl << "<td>" << distinctNum[size] <<"</td>"<< endl <<"<td>" << frequency[size] << "</td>"<<endl<< "</tr>" <<endl;
        }
        outfile << "</table>" <<endl;

}
/**************************************************************
Programmer:	Chin Pei Wern
Name: 		distNumAndFreq

task:			gather all the functions to find distinct numbers and its frequencies, and print them out
data in:	    data in 2d vector,the title of every columns, total number of rows and columns of the data file.
data returned:	-
Referred to:	-
**************************************************************/
void distNumAndFreq(const vector<vector <int>> arr,const vector<string> header, const int numOfRows, const int numOfCols)
{
    int col, count;
    cout << endl << "\t-----------------------DISTINCT NUMBER AND ITS FREQUENCY---------------------" << endl;
    cout << endl;
    col = UserInput(header, numOfCols);    //call the function to ask for user input, pass header as argument
    system("CLS");
    col -= 1;   //is a subscript, so need to substracts 1

    vector <int> distinctNum = distNum(arr, numOfRows, col);    //call distNum function and pass 2d vector named arr, numOfRows
                                                        //column input by user, array named distinctNum and flag as arguments.
    vector <int> frequency = freqOfDistNum(arr, numOfRows, col);

    cout << "\t-----------------------DISTINCT NUMBER AND ITS FREQUENCY---------------------" << endl;
    cout << endl;
    cout << "\t\tTITLE : " << header[col] << endl << endl;
    cout << "\t -----------------------------------------------" << endl;
    cout << "\t|" << setw(25) << "DISTINCT NUMBER" << " | " << setw(15) << "FREQUENCY" << "\t|" << endl;
    cout << "\t|-----------------------------------------------|" << endl;
    for (int size=0; size < distinctNum.size(); size++)
        cout << "\t|" << setw(25) << distinctNum[size] << " | " << setw(15) << frequency[size] << "\t|" << endl;

    cout << "\t ----------------------------------------------- " << endl;
    if(saveDataInput())
    {
        int type = htmlortxt();
        cin.ignore();
        ofstream outfile = userInputFileName(type);
        if (type == 50)
            saveDistNumfreq(outfile, distinctNum, frequency, header, col);
        else if (type == 49)
            printDistNumNFreqHtml(outfile, header, arr, numOfRows, col);
        outfile.close();
        cout << "DATA SAVED!" << endl;
        cout << "Press Enter to continue" << endl;
        cin.get();
        system("CLS");
    }
}

/*****************************************************************************
Programmer: Amani Balqis Binti Johal
Name: calcMean
task: calculate mean

data in: arr,COL and rows

data returned:  mean

Referred to: lecturer's code in class

******************************************************************************/
float calcMean(vector <vector<int>>arr,const int COL,const int rows)
{
    float mean;
    int sum = 0;
    for (int row=0; row<rows; row++)
    {
        sum += arr[row][COL];
    }
    mean = sum / float(rows);
    return mean;
}

/*****************************************************************************
Programmer: Amani Balqis Binti Johal
Name: aboveMean
task: get the data that above the mean

data in: arr,header, COL, rows and mean

data returned: data above mean

Referred to: lecturer's code in class
******************************************************************************/
vector<int> aboveMean(vector <vector<int>>arr,vector<string> header, const int COL, int rows,const float mean)
{
    vector<int> above_mean;
    for (int row=0;row< rows;row++)
    {
        if (arr[row][COL]> mean)
            above_mean.push_back(arr[row][COL]);
    }
    return above_mean;
}

/*****************************************************************************
Programmer: Amani Balqis Binti Johal
Name: belowMean
task: get the data that below the mean

data in: arr,header, COL, rows and mean

data returned: data below mean

Referred to: lecturer's code in class
******************************************************************************/
vector<int> belowMean(vector <vector<int>>arr,vector<string> header, const int COL,const int rows,const float mean)
{
    vector<int> below_mean;
    for (int row=0;row<rows;row++)
    {
        if (arr[row][COL] < mean)
            below_mean.push_back(arr[row][COL]);
    }
    return below_mean;
}

/*****************************************************************************
Programmer: Ng Yoong Kee
Name: htmlAboveMean

task: stored the data item above mean in html file.

data in: 2D vector of data, header, number of column that user input, vector of above_mean
data returned: -

Referred to: https://www.w3schools.com/html/html_tables.asp
             https://www.w3schools.com/html/html_styles.asp
             https://www.w3schools.com/w3css/w3css_tables.asp

******************************************************************************/
void htmlAboveMean(ofstream &ofile, vector<vector<int>> arr, vector<string> header, int col, vector<int> above_mean)
{
    ofile << "<html>\n<body>\n" << "<link rel=\"stylesheet\" href=\"https://www.w3schools.com/w3css/4/w3.css\">\n"
          << "<div class=\"w3-container\">\n" << "<table class=\"w3-table-all w3-card-4\"> \n";
    ofile << "<h2 style=\"text-align:center;\">Data Item Above Mean</h2>\n"
          << "<tr>\n<th>" << header[0] << "</th>\n<th>" << header[col] << "</th>\n</tr>\n";
    for (int i=0; i < above_mean.size(); i++)
        ofile << "<tr>\n<td>" << arr[i][0] << "</td>\n<td>" << above_mean[i] << "</td>\n</tr>\n";
    ofile << "</table>\n</div>\n</body>\n</html>\n";
}

/*****************************************************************************
Programmer: Ng Yoong Kee
Name: htmlBelowMean

task: stored the data item below mean in html file.

data in: 2D vector of data, header, number of column that user input, vector of below_mean
data returned: -

Referred to: https://www.w3schools.com/html/html_tables.asp
             https://www.w3schools.com/html/html_styles.asp
             https://www.w3schools.com/w3css/w3css_tables.asp

******************************************************************************/
void htmlBelowMean(ofstream &ofile, vector<vector<int>> arr, vector<string> header, int col, vector<int> below_mean)
{
    ofile << "<html>\n<body>\n" << "<link rel=\"stylesheet\" href=\"https://www.w3schools.com/w3css/4/w3.css\">\n"
          << "<div class=\"w3-container\">\n" << "<table class=\"w3-table-all w3-card-4\"> \n";
    ofile << "<h2 style=\"text-align:center;\">Data Item Below Mean</h2>\n"
          << "<tr>\n<th>" << header[0] << "</th>\n<th>" << header[col] << "</th>\n</tr>\n";
    for (int i=0; i < below_mean.size(); i++)
        ofile << "<tr>\n<td>" << arr[i][0] << "</td>\n<td>" << below_mean[i] << "</td>\n</tr>\n";
    ofile << "</table>\n</div>\n</body>\n</html>\n";
}

/**************************************************************
Programmer:	Chin Pei Wern
Name: 		saveAboveMean

task:			save data item above mean into a file
data in:	    stream a file, data in 2d vector,the title of every columns, vector called above_mean, selected column
data returned:	-
Referred to:	-
**************************************************************/
void saveAboveMean(ofstream &outfile,vector<vector<int>> arr,vector<string> header,vector<int> above_mean, const int col)
{
        outfile << "\t---------------DATA ITEM ABOVE MEAN--------------" << endl << endl;
        outfile << "\t-------------------------------------------------" << endl;
        outfile << "\t|" << setw(20) << header[0] << "|\t" << setw(20) << header[col] << "\t|"  << endl;
        outfile << "\t-------------------------------------------------" << endl;
        for (int i=0; i < above_mean.size(); i++)
            outfile << "\t|" << setw(20) << arr[i][0] << "|\t" << setw(20) << above_mean[i] << "\t|" << endl;
        outfile << "\t-------------------------------------------------" << endl << endl;
}

/**************************************************************
Programmer:	Chin Pei Wern
Name: 		saveBelowMean

task:			save data item below mean into a file
data in:	    stream a file, data in 2d vector,the title of every columns, vector called below_mean, selected column
data returned:	-
Referred to:	-
**************************************************************/
void saveBelowMean(ofstream &outfile,vector<vector<int>> arr,vector<string> header,vector<int> below_mean,const int col)
{
        outfile << "\t---------------DATA ITEM BELOW MEAN--------------" << endl << endl;
        outfile << "\t------------------------------------------------" << endl;
        outfile << "\t|" << setw(20) << header[0] << "\t|" << setw(20) << header[col] << "\t|" << endl;
        outfile << "\t------------------------------------------------" << endl;
        for (int i=0; i < below_mean.size(); i++)
            outfile << "\t|" << setw(20) << arr[i][0] <<"\t|" << setw(20) << below_mean[i] << "\t|" << endl;
        outfile << "\t------------------------------------------------" << endl << endl;
}

/**************************************************************
Programmer:	Chin Pei Wern
Name: 		printAboveMean

task:			print out data items above mean, and save them if the user wants
data in:	    data in 2d vector,the title of every columns, selected column, mean of selected column, and total number of rows
data returned:	-
Referred to:	-
**************************************************************/
void printAboveMean(vector<vector<int>> arr, vector<string> header, const int col, const float mean, const int ROWS)
{
    vector<int> above_mean = aboveMean(arr, header, col,ROWS, mean);

        cout << "\t---------------DATA ITEM ABOVE MEAN--------------" << endl << endl;
        cout << "\t-------------------------------------------------" << endl;
        cout << "\t|" << setw(20) << header[0] << "|\t" << setw(20) << header[col] << "\t|"  << endl;
        cout << "\t-------------------------------------------------" << endl;
        for (int i=0; i < above_mean.size(); i++)
            cout << "\t|" << setw(20) << arr[i][0] << "|\t" << setw(20) << above_mean[i] << "\t|" << endl;
        cout << "\t-------------------------------------------------" << endl;

        if(saveDataInput())
        {
            int type = htmlortxt();
            cin.ignore();
            ofstream outfile = userInputFileName(type);
            if (type == 50)
                saveAboveMean(outfile, arr, header, above_mean, col);
            else if (type == 49)
                htmlAboveMean(outfile, arr, header, col, above_mean);
            outfile.close();
            cout << "DATA SAVED!" << endl;
            cout << "Press Enter to continue" << endl;
            cin.get();
            system("CLS");
        }
}
/**************************************************************
Programmer:	Chin Pei Wern
Name: 		aboveAndBelowMean

task:			gather all the functions to find data above and below mean and print them out
data in:	    data in 2d vector,the title of every columns, total number of rows and columns of the data file.
data returned:	-
Referred to:	-
**************************************************************/
void aboveAndBelowMean(vector<vector<int>> arr, vector<string> header, const int ROWS, const int COLS)
{
    int meanChoice;
    cout << endl << "\t--------DATA ITEM ABOVE AND BELOW MEAN------" << endl;
    cout << "\t------------------------------------------------" << endl << endl;
    cout << "\tPlease select an option: " << endl;
    cout << "\t1. Data Item Above Mean" << endl;
    cout << "\t2. Data Item Below Mean" << endl;
    cin >> meanChoice;
    while ((meanChoice != 1) && (meanChoice != 2))       //if user input is not in range
    {
        cout << "Error! Invalid Input." << endl;
        cout << "Please select option 1 or option 2" << endl;
        cin >> meanChoice;
    }

    int col = UserInput(header, COLS);
    system("CLS");
    col -= 1;
    float mean = calcMean(arr, col, ROWS);
    if (meanChoice == 1)
    {
        printAboveMean(arr, header, col, mean, ROWS);
    }
    else if (meanChoice == 2)
    {
        vector<int> below_mean = belowMean(arr, header, col,ROWS, mean);

        cout << "\t---------------DATA ITEM BELOW MEAN--------------" << endl << endl;
        cout << "\t------------------------------------------------" << endl;
        cout << "\t|" << setw(20) << header[0] << "\t|" << setw(20) << header[col] << "\t|" << endl;
        cout << "\t------------------------------------------------" << endl;
        for (int i=0; i < below_mean.size(); i++)
            cout << "\t|" << setw(20) << arr[i][0] <<"\t|" << setw(20) << below_mean[i] << "\t|" << endl;
        cout << "\t------------------------------------------------" << endl;
        if(saveDataInput())
        {
            int type = htmlortxt();
            cin.ignore();
            ofstream outfile = userInputFileName(type);
            if (type == 50)
                saveBelowMean(outfile, arr, header, below_mean, col);
            else if (type == 49)
                htmlBelowMean(outfile, arr, header, col, below_mean);
            outfile.close();
            cout << "DATA SAVED!" << endl;
            cout << "Press Enter to continue" << endl;
            cin.get();
            system("CLS");
        }
    }

}

/*****************************************************************************
Programmer: Amani Balqis Binti Johal
Name: calcStdDev
task: calculate the standard devitation

data in: arr,header, COL, rows and mean

data returned: standard devitation

Referred to: https://www.techcrashcourse.com/2017/01/cpp-program-to-calculate-standard-deviation.html
******************************************************************************/
float calcStdDev(vector <vector<int>>arr,const int COL,const int rows,const float mean)
{
    float sum = 0;
    float stdDev;
    for (int row=0; row<rows; row++)
    {
        sum += pow(arr[row][COL] - mean, 2);
    }
    stdDev = sqrt(sum/rows);
    return stdDev;
}

/*****************************************************************************
Programmer: Amani Balqis Binti Johal
Name: calcVar
task: calculate the variance

data in: stdDev

data returned: variance

Referred to: https://www.techcrashcourse.com/2017/01/cpp-program-to-calculate-standard-deviation.html
******************************************************************************/
float calcVar(float stdDev)
{
    float variance;
    variance = pow(stdDev,2);
    return variance;
}

/*****************************************************************************************************************
Programmer: Ng Yoong Kee
Name: findHighestCol

task: compare values of a column and find the highest.

data in: 2D vector of data, number of column that user input, total number of rows

data returned: highestCol

Referred to: https://www.tutorialspoint.com/find-maximum-element-of-each-column-in-a-matrix-in-cplusplus
             https://www.faceprep.in/c/find-the-minimum-and-maximum-element-in-each-column-of-a-matrix/
             https://stackoverflow.com/questions/34210401/finding-the-maximum-value-of-every-row-in-2d-array-c
******************************************************************************************************************/
int findHighestCol(vector <vector<int>>arr,const int col, const int ROWS)
{
    int highestCol = arr[0][col];

    for(int row = 1; row < ROWS; row++)
    {
        if(arr[row][col] > highestCol)
        {
            highestCol = arr[row][col];
        }
    }

    return highestCol;
}


/****************************************************************************************************************
Programmer: Ng Yoong Kee
Name: findLowestCol

task: compare values of a column and find the lowest.

data in: 2D vector of data, number of column that user input, total number of rows

data returned: lowestCol

Referred to: https://www.tutorialspoint.com/find-maximum-element-of-each-column-in-a-matrix-in-cplusplus
             https://www.faceprep.in/c/find-the-minimum-and-maximum-element-in-each-column-of-a-matrix/
             https://stackoverflow.com/questions/34210401/finding-the-maximum-value-of-every-row-in-2d-array-c

*****************************************************************************************************************/
int findLowestCol(vector <vector<int>>arr,const int col, const int ROWS)
{
    int lowestCol = arr[0][col];

    for(int row = 1; row < ROWS; row++)
    {
        if(arr[row][col] < lowestCol)
        {
            lowestCol = arr[row][col];
        }
    }

    return lowestCol;
}
/*****************************************************************************
Programmer: Amani Balqis Binti Johal
Name: RegMnCHtml
task: generate calculation of line regression to html

data in: outfile,header,arr,ROWS,x and y

data returned: -
******************************************************************************/
void RegMnCHtml(ofstream &outfile,vector<string> header,vector <vector<int>>arr, const int ROWS, int x, int y)
{
    float sumX, sumXX, sumY, sumXY;
    sumX = 0;
    sumXX = 0;
    sumY = 0;
    sumXY = 0;
    outfile << "<h2 style=\"text-align:center;\">LINEAR REGRESSION LINE FORMULA</h2>" << endl
            << "<style>table, th, td {border: 1px solid black;}</style> "<<endl
            << "<table style=\"width:70%;background-color:#3A638C\">"<<endl
            << "<tr>"<< endl << "<th>" << header[x] << "(X)" << "</th>" <<endl <<  "<th>" << header[y] << " (Y)"<< "</th>"<<endl
            << "<th>XX</th>" <<endl<< "<th>XY</th>" << endl << "</tr>" <<endl;
    for(int i=0; i<ROWS; i++)
    {
        sumX = sumX + arr[i][x];
        sumXX = sumXX + arr[i][x] * arr[i][x];
        sumY = sumY + arr[i][y];
        sumXY = sumXY + arr[i][x] * arr[i][y];
        outfile << "<tr>"<< endl << "<td>" << arr[i][x] <<"</td>"<< endl <<"<td>" << arr[i][y] << "</td>" <<endl
                << "<td>"<< pow(arr[i][x],2) <<"</td>"<< endl <<"<td>" << arr[i][x] * arr[i][y] << "</td>"<<endl<< "</tr>" <<endl;

    }
    outfile << "</table>" << endl;
    float m = (ROWS*sumXY - sumX*sumY) / (ROWS*sumXX - sumX*sumX);
    float c = (sumY - m*sumX) / ROWS;
    outfile<< "<h3>SUM OF X = " << sumX << "</h3>" << endl << "<h3>SUM OF Y = " << sumY << "</h3>" << endl
           << "<h3>SUM OF XX = " << sumXX << "</h3>" << endl << "<h3>SUM OF XY = " << sumXY <<"</h3>"<< endl
           << "<h3>m = "<< m <<"</h3>"<< endl << "<h3>c = "<< c <<"</h3>" << endl
           << "<h3>LINEAR REGRESSION EQUATION: y = " << m << "x + " <<  c << "</h3>"<< endl;
}


/*****************************************************************************
Programmer: Amani Balqis Binti Johal
Name: pearsonCorHtml
task: generate calculation of PEARSON'S CORRELATION to html

data in: outfile,header,arr,ROWS,x and y

data returned: -
******************************************************************************/
void pearsonCorHtml(ofstream &outfile,vector<string> header,vector<vector<int>> arr, const int ROWS,int x, int y)
{
    int sumX, sumXX, sumY, sumXY, sumYY;
    sumX = 0;
    sumXX = 0;
    sumY = 0;
    sumXY = 0;
    sumYY = 0;
    outfile << "<h2 style=\"text-align:center;\">PEARSON'S CORRELATION</h2>"<< endl
            << "<style>table, th, td {border: 1px solid black;}</style> " << endl
            << "<table style=\"width:70%;;background-color:#3A638C\">"<< endl
            << "<tr>"<< endl << "<th>" << header[x] << " (X)" << "</th>" << endl << "<th>" << header[y] << " (Y)" << "</th>" << endl
            << "<th>XY</th>" << endl << "<th>XX</th>" << endl << "<th>YY</th>" << "</tr>" <<endl;
    for(int i=0; i<ROWS; i++)
    {
        sumX = sumX + arr[i][x];
        sumXX = sumXX + arr[i][x] * arr[i][x];
        sumY = sumY + arr[i][y];
        sumXY = sumXY + arr[i][x] * arr[i][y];
        sumYY = sumYY + arr[i][y] * arr[i][y];
        outfile
                << "<tr>"<< endl << "<td>" << arr[i][x] <<"</td>"<< endl <<"<td>" << arr[i][y] << "</td>"<<endl
                << "<td>" << arr[i][x] * arr[i][y] <<"</td>"<< endl <<"<td>" << pow(arr[i][x],2) <<"</td>"<< endl
                <<"<td>" << pow(arr[i][y],2) << "</td>"<<endl<< "</tr>" <<endl;

    }
    outfile << "</table>" << endl;
    outfile << "<h3>SUM OF X = " <<  sumX << "</h3>"<< endl <<"<h3>SUM OF Y = " << sumY << "</h3>" << endl << "<h3>SUM OF XY = " << sumXY <<"</h3>"<< endl
            << "<h3>SUM OF XX = " << sumXX <<"</h3>" << endl << "<h3>SUM OF YY = " << sumYY << "</h3>" << endl;
    float r = float((ROWS * sumXY) - (sumX * sumY)) / sqrt((ROWS * sumXX - pow(sumX,2)) * (ROWS * sumYY - pow(sumY,2)));
    outfile << "<h3>PEARSON'S CORRELATION COEFFICIENT, r = " << r << "</h3>" << endl;
}


/**************************************************************
Programmer  : Nurul Syaqeera
Name        : saveLineReg

task        : This function will save data output in text file
data in     : List of vector arrays in selected column that have been computed
              as Linear Regression
data returned: data will be returned as output in text file
Referred to : -
**************************************************************/
void saveLineReg(ofstream &outfile, vector <vector<int>>arr,vector<string> header, const int ROWS, const int x,const int y)
{
    outfile << endl << "\t------------- LINEAR REGRESSION LINE FORMULA -----------------" << endl << endl;
    outfile         << "\t--------------------------------------------------------------" << endl;
    outfile << "\t|"<< setw(10) << header[x] << " (X)|" << setw(10) << header[y] << " (Y)|"
            << setw(16) << "XX|" << setw(16) << "XY|" << endl;
    outfile << "\t -------------------------------------------------------------" << endl;

    float sumX=0, sumXX=0, sumY=0, sumXY=0;
    for(int i=0; i<ROWS; i++)
    {
        sumX = sumX + arr[i][x];
        sumXX = sumXX + arr[i][x] * arr[i][x];
        sumY = sumY + arr[i][y];
        sumXY = sumXY + arr[i][x] * arr[i][y];
        outfile << "\t|"<< setw(14) << arr[i][x] <<"|" << setw(14) << arr[i][y] <<"|" << setw(15) << pow(arr[i][x],2) <<"|" << setw(15) << arr[i][x] * arr[i][y] <<"|" << endl;
    }
    outfile << "\t -------------------------------------------------------------" << endl;
    float m = (ROWS*sumXY - sumX*sumY) / (ROWS*sumXX - sumX*sumX);
    float c = (sumY - m*sumX) / ROWS;
    outfile << endl << "\tSUM OF X = " << sumX << endl << "\tSUM OF Y = " << sumY << endl << "\tSUM OF XX = " << sumXX << endl << "\tSUM OF XY = " << sumXY << endl << endl;
    outfile << "\tm = " << m << endl << "\tc = " << c << endl << endl;
    outfile << "\tLINEAR REGRESSION EQUATION: y = " << m << "x + " << c << endl << endl;
}

/**********************************************************************************************************
Programmer: Ng Yoong Kee
Name: RegMnC

task: calculate linear regression value of m and c

data in: 2D vector of data, total number of rows, two columns that user input
data returned: -

Referred to: https://www.codesansar.com/numerical-methods/linear-regression-method-using-cpp-output.htm
             https://www.easycalculation.com/statistics/learn-regression.php
             http://www.cplusplus.com/forum/beginner/124364/

**********************************************************************************************************/
void RegMnC(vector <vector<int>>arr, const int ROWS, const int x,const int y)
{
    float sumX, sumXX, sumY, sumXY;
    sumX = 0;
    sumXX = 0;
    sumY = 0;
    sumXY = 0;
    for(int i=0; i<ROWS; i++)
    {
        sumX = sumX + arr[i][x];
        sumXX = sumXX + arr[i][x] * arr[i][x];
        sumY = sumY + arr[i][y];
        sumXY = sumXY + arr[i][x] * arr[i][y];
        cout << "\t|"<< setw(14) << arr[i][x] <<"|" << setw(14) << arr[i][y] <<"|" << setw(15) << pow(arr[i][x],2) <<"|" << setw(15) << arr[i][x] * arr[i][y] <<"|" << endl;
    }
    cout << "\t -------------------------------------------------------------" << endl;
    float m = (ROWS*sumXY - sumX*sumY) / (ROWS*sumXX - sumX*sumX);
    float c = (sumY - m*sumX) / ROWS;
    cout << endl << "\tSUM OF X = " << sumX << endl << "\tSUM OF Y = " << sumY << endl << "\tSUM OF XX = " << sumXX << endl << "\tSUM OF XY = " << sumXY << endl << endl;
    cout << "\tm = " << m << endl << "\tc = " << c << endl << endl;
    cout << "\tLINEAR REGRESSION EQUATION: y = " << m << "x + " << c << endl << endl;
}

/*******************************************************************************
Programmer: Ng Yoong Kee
Name: lineReg

task: calculate linear regression and get the equation y = mx + c

data in: 2D vector of data, header, total number of rows and columns
data returned: -

Referred to: https://www.codesansar.com/numerical-methods/linear-regression-method-using-cpp-output.htm
             https://www.easycalculation.com/statistics/learn-regression.php
             http://www.cplusplus.com/forum/beginner/124364/

********************************************************************************/
void lineReg(vector <vector<int>>arr, vector<string> header, const int COLS, const int ROWS)
{
    cout << endl;
    cout << "--------------------------LINEAR REGRESSION LINE FORMULA--------------------------" << endl << endl;
    int x, y;
    cout << "COLUMN X -> " << endl;
    //cin >> x;
    x =  UserInput(header, COLS);

    cout << "COLUMN Y -> " << endl;
    y = UserInput(header, COLS);
    system("CLS");

    x = x - 1;
    y = y - 1;
    cout << endl << "\t--------------------------LINEAR REGRESSION LINE FORMULA--------------------------" << endl << endl;
    cout << "\t -------------------------------------------------------------" << endl;
    cout << "\t|"<< setw(10) << header[x] << " (X)|" << setw(10) << header[y] << " (Y)|"
         << setw(16) << "XX|" << setw(16) << "XY|" << endl;
    cout << "\t -------------------------------------------------------------" << endl;
    RegMnC(arr, ROWS, x, y);
    if (saveDataInput())
    {
        int type = htmlortxt();
        cin.ignore();
        ofstream outfile = userInputFileName(type);
        if (type == 50)
            saveLineReg(outfile, arr, header, ROWS, x, y);
        else if(type == 49)
            RegMnCHtml(outfile, header, arr, ROWS, x, y);
        outfile.close();
        cout << "DATA SAVED!" << endl;
        cout << "Press Enter to continue" << endl;
        cin.get();
        system("CLS");
    }
}
/**************************************************************
Programmer  : Nurul Syaqeera
Name        : savePearson

task        : This function will save data output in text file
data in     : List of vector arrays in selected column that have been computed
              as Pearson Correlation
data returned: -
Referred to : -
**************************************************************/
void savePearson(ofstream &outfile, vector<vector<int>> arr, vector<string> header, const int ROWS,const int x,const int y)
{
    int sumX=0, sumXX=0, sumY=0, sumXY=0, sumYY=0;
    outfile << endl << "\t----------------------------- PEARSON'S CORRELATION --------------------------" << endl << endl;
    outfile << "\t -----------------------------------------------------------------------------" << endl;
    outfile << "\t|"<< setw(10) << header[x] << " (X)|" << setw(10) << header[y] << " (Y)|"
            << setw(16) << "XY|" << setw(16) << "XX|" << setw(16) << "YY|" << endl;
    outfile << "\t -----------------------------------------------------------------------------" << endl;
    for(int i=0; i<ROWS; i++)
    {
        sumX = sumX + arr[i][x];
        sumXX = sumXX + arr[i][x] * arr[i][x];
        sumY = sumY + arr[i][y];
        sumXY = sumXY + arr[i][x] * arr[i][y];
        sumYY = sumYY + arr[i][y] * arr[i][y];
        outfile << "\t|"<< setw(14) << arr[i][x] <<"|" << setw(14) << arr[i][y] <<"|"
            << setw(15) << arr[i][x] * arr[i][y] <<"|" << setw(15) << pow(arr[i][x],2) <<"|" << setw(15) << pow(arr[i][y],2) << "|" << endl;
    }
    outfile << "\t -------------------------------------------------------------------------------" << endl;
    outfile << endl << "\tSUM OF X = " << sumX << endl << "\tSUM OF Y = " << sumY << endl << "\tSUM OF XY = " << sumXY << endl
         << "\tSUM OF XX = " << sumXX << endl << "\tSUM OF YY = " << sumYY << endl << endl;
    float r = float((ROWS * sumXY) - (sumX * sumY)) / sqrt((ROWS * sumXX - pow(sumX,2)) * (ROWS * sumYY - pow(sumY,2)));
    outfile << "\tPEARSON'S CORRELATION COEFFICIENT, r = " << r << endl << endl;
}

/**************************************************************
Programmer:	Chin Pei Wern
Name: 		pearson

task:			calculate the pearson's correlation and print them out
data in:	    2d vector of data, title of every columns 2d vector called data, total number of rows of data, and user input
                column, x and y.
data returned:	-
Referred to:	https://www.statisticshowto.com/probability-and-statistics/correlation-coefficient-formula/
**************************************************************/
void calcPearson(vector<vector<int>> arr, vector<string> header, const int ROWS,const int x, const int y)
{
    int sumX, sumXX, sumY, sumXY, sumYY;
    sumX = 0;
    sumXX = 0;
    sumY = 0;
    sumXY = 0;
    sumYY = 0;
    for(int i=0; i<ROWS; i++)
    {
        sumX = sumX + arr[i][x];
        sumXX = sumXX + arr[i][x] * arr[i][x];
        sumY = sumY + arr[i][y];
        sumXY = sumXY + arr[i][x] * arr[i][y];
        sumYY = sumYY + arr[i][y] * arr[i][y];
        cout << "\t|"<< setw(14) << arr[i][x] <<"|" << setw(14) << arr[i][y] <<"|"
            << setw(15) << arr[i][x] * arr[i][y] <<"|" << setw(15) << pow(arr[i][x],2) <<"|" << setw(15) << pow(arr[i][y],2) << "|" << endl;
    }
    cout << "\t -------------------------------------------------------------------------------" << endl;
    cout << endl << "\tSUM OF X = " << sumX << endl << "\tSUM OF Y = " << sumY << endl << "\tSUM OF XY = " << sumXY << endl
         << "\tSUM OF XX = " << sumXX << endl << "\tSUM OF YY = " << sumYY << endl << endl;
    float r = float((ROWS * sumXY) - (sumX * sumY)) / sqrt((ROWS * sumXX - pow(sumX,2)) * (ROWS * sumYY - pow(sumY,2)));
    cout << "\tPEARSON'S CORRELATION COEFFICIENT, r = " << r << endl << endl;

}

/**************************************************************
Programmer:	Chin Pei Wern
Name: 		pearson

task:			compute the pearson's correlation and print them out
data in:	    2d vector of data, title of every columns 2d vector called data, total number of columns and rows of data.
data returned:	-
Referred to:	https://www.statisticshowto.com/probability-and-statistics/correlation-coefficient-formula/
**************************************************************/
void pearson(vector<vector<int>> arr, vector<string> header, const int COLS, const int ROWS)
{
    cout << endl;
    cout << "---------------------------PEARSON'S CORRELATION----------------------------" << endl << endl;
    int x, y;
    cout << "COLUMN X -> " << endl;
    //cin >> x;
    x =  UserInput(header, COLS);

    cout << "COLUMN Y -> " << endl;
    y = UserInput(header, COLS);
    system("CLS");

    x = x - 1;
    y = y - 1;
    cout << endl << "\t----------------------------PEARSON'S CORRELATION---------------------------" << endl << endl;
    cout << "\t -----------------------------------------------------------------------------" << endl;
    cout << "\t|"<< setw(10) << header[x] << " (X)|" << setw(10) << header[y] << " (Y)|"
         << setw(16) << "XY|" << setw(16) << "XX|" << setw(16) << "YY|" << endl;
    cout << "\t -----------------------------------------------------------------------------" << endl;

    calcPearson(arr, header, ROWS, x, y);
    if(saveDataInput())
    {
        int type = htmlortxt();
        cin.ignore();
        ofstream outfile = userInputFileName(type);
        if (type == 50)
            savePearson(outfile, arr, header, ROWS, x, y);
        else if(type == 49)
            pearsonCorHtml(outfile, header, arr, ROWS, x, y);
        outfile.close();
        cout << "DATA SAVED!" << endl;
        cout << "Press Enter to continue" << endl;
        cin.get();
        system("CLS");
    }
}
/*****************************************************************************
Programmer: Amani Balqis Binti Johal
Name: printHistogramHtml
task: generate histogram to html

data in: outfile,header,arr,COLS and ROWS

data returned: -
******************************************************************************/
void printHistogramHtml(ofstream &outfile,vector<string>headers,vector<vector<int>> arr, const int col, const int ROWS)
{
    outfile << "<h2 style=\"text-align:center;\">HISTOGRAM</h2>" << endl
            << "<style>table, th, td {border: 1px solid black;}</style> "<<endl;

    outfile << "<h3 style=\"text-align:center;\">TITLE: " << headers[col] <<"</h3>" << endl
            << "<table style=\"width:70%;background-color:#3A638C\">"<<endl
            <<"<tr>"<< endl << "<th>Interval</th>"<< endl << "<th>Frequency</th>"<<endl<< "</tr>"<< endl;
    int max = findHighestCol(arr, col, ROWS);
    int min = findLowestCol(arr, col, ROWS);
    int difference = max - min;
    int interval = difference / 5;
    int lPoint = min;
    while (lPoint <= max)
    {
        int hPoint = lPoint + interval;
        int frequency = 0;
        for (int i=0; i < ROWS; i++)
        {
            if ((arr[i][col] >=lPoint) && arr[i][col] <= hPoint)
                frequency += 1;
        }

        outfile
                <<"<tr>"<< endl << "<th>"<< lPoint << " - " << hPoint <<"</th>"<< endl
                << "<td>";
        for (int j= 1; j <= frequency; j++)
            outfile << "*" ;
        outfile << "</td>" << endl
                << "</tr>"<< endl;
        lPoint = hPoint + 1;
    }
    outfile << "</table>"<< endl;


}

/**************************************************************
Programmer:	Chin Pei Wern
Name: 		calchistogram

task:			compute histogram and print them out
data in:	    data in 2d vector,total number of rows and selected column of the data file.
data returned:	-
Referred to:	-
**************************************************************/
void calcHistogram(vector<vector<int>> arr, const int col, const int ROWS)
{
    int max = findHighestCol(arr, col, ROWS);
    int min = findLowestCol(arr, col, ROWS);
    int difference = max - min;
    int interval = difference / 5;
    int lPoint = min;
    while (lPoint <= max)
    {
        int hPoint = lPoint + interval;
        int frequency = 0;
        for (int i=0; i < ROWS; i++)
        {
            if ((arr[i][col] >=lPoint) && arr[i][col] <= hPoint)
                frequency += 1;
        }
        cout << "\t" << setw(14) << lPoint << " - " << setw(3) << hPoint << "| ";
        for (int i= 1; i <= frequency; i++)
            cout << "*";
        cout << endl;
        lPoint = hPoint + 1;
    }
}

/**************************************************************
Programmer:	Chin Pei Wern & Nurul Syaqeera
Name: 		saveHistogram

task:			compute histogram and save them
data in:	    new file, data in 2d vector,the title of every columns, total number of rows and selected column of the data file.
data returned:	-
Referred to:	-
**************************************************************/
void saveHistogram(ofstream &outfile, vector <vector<int>> arr,vector<string>headers, const int col, const int ROWS)
{
    outfile << "\t--------------- HISTOGRAM --------------" << endl << endl;
    outfile << "\t\t TITLE: " << headers[col] << endl << endl;
    outfile << "\t----------------------------------------" << endl;
    outfile << "\t" << setw(20) << " Intervals" << "|"  << setw(15) << " Frequency " << endl;
    outfile << "\t----------------------------------------" << endl;
    int max = findHighestCol(arr, col, ROWS);
    int min = findLowestCol(arr, col, ROWS);
    int difference = max - min;
    int interval = difference / 5;
    int lPoint = min;
    while (lPoint <= max)
    {
        int hPoint = lPoint + interval;
        int frequency = 0;
        for (int i=0; i < ROWS; i++)
        {
            if ((arr[i][col] >=lPoint) && arr[i][col] <= hPoint)
                frequency += 1;
        }
        outfile << "\t" << setw(14) << lPoint << " - " << setw(3) << hPoint << "| ";
        for (int i= 1; i <= frequency; i++)
            outfile << "*";
        outfile << endl;
        lPoint = hPoint + 1;
    }
    outfile << "\t----------------------------------------" << endl << endl << endl;
}
/**************************************************************
Programmer:	Chin Pei Wern
Name: 		histogram

task:			compute histogram and print them out
data in:	    data in 2d vector,the title of every columns, total number of rows and columns of the data file.
data returned:	-
Referred to:	-
**************************************************************/
void histogram(vector <vector<int>> arr,vector<string>headers,const int ROWS, const int COLS)
{
    cout << endl << "\t------------------------------HISTOGRAM-------------------------" << endl << endl;
    int col = UserInput(headers, COLS);
    system("CLS");
    col -= 1;
    cout << endl << "\t------------------------------ HISTOGRAM -------------------------" << endl << endl;
    cout << "\t\t TITLE: " << headers[col] << endl << endl;
    cout << "\t----------------------------------------" << endl;
    cout << "\t" << setw(20) << " Intervals" << "|"  << setw(15) << " Frequency " << endl;
    cout << "\t----------------------------------------" << endl;
    calcHistogram(arr, col, ROWS);
    cout << "\t----------------------------------------" << endl;
    if (saveDataInput())
    {
        int type = htmlortxt();
        cin.ignore();
        ofstream outfile = userInputFileName(type);
        if (type == 50)
            saveHistogram(outfile, arr, headers, col, ROWS);
        else if (type == 49)
            printHistogramHtml(outfile, headers, arr, col, ROWS);
        outfile.close();
        cout << "DATA SAVED!" << endl;
        cout << "Press Enter to continue" << endl;
        cin.get();
        system("CLS");
    }
}
/**************************************************************
Programmer  : Nurul Syaqeera
Name        : saveAscOrder

task        : This function will save data output in text file
data in     : List of vector arrays in selected column that have been sorted
data returned: -
Referred to : -
**************************************************************/
void saveAscOrder(ofstream &outfile, vector<vector<int>> data, vector<string> header, const int COL)
{

    outfile << "\t------------- ASCENDING ORDER -----------" << endl << endl;
    outfile << "\t\tTITLE: " << header[COL] << endl << endl;
    outfile << "\t-----------------------------------------" << endl;
    outfile << "\t|" << setw(20) << header[0] << "|" << setw(15) << header[COL] << "\t|\t" << endl;
    outfile << "\t-----------------------------------------" << endl;
    for (int size=0; size < data.size(); size++)
        outfile << "\t|" << setw(20) << data[size][0] << "|" << setw(15) << data[size][COL] <<"\t|\t" << endl;

    outfile << "\t-----------------------------------------" << endl << endl;
}

/**************************************************************
Programmer  : Nurul Syaqeera
Name        : printAsc

task        : This will be the output of data in ascending order.
data in     : List of vector arrays in selected column
data returned: data will be returned as output in ascending order
Referred to : -
**************************************************************/
void printAsc(vector<vector<int>> data, vector<string> header, const int COL)
{
    cout << "-----------------------ASCENDING ORDER----------------------" << endl << endl;
    cout << "\t\tTITLE: " << header[COL] << endl << endl;
    cout << "\t-----------------------------------------" << endl;
    cout << "\t|" << setw(20) << header[0] << "|" << setw(15) << header[COL] << "\t|\t" << endl;
    cout << "\t-----------------------------------------" << endl;
    for (int size=0; size < data.size(); size++)
        cout << "\t|" << setw(20) << data[size][0] << "|" << setw(15) << data[size][COL] <<"\t|\t" << endl;

    cout << "\t-----------------------------------------" << endl;
}

/**************************************************************
Programmer  : Nurul Syaqeera
Name        : AscOrder

task        : This function will sort data in ascending order
data in     : List of vector arrays in selected column and read each row of data
data returned: position of array will be displayed in printAsc() function
Referred to : Gaddis, C++ From Control Structures Through Objects, 9th Ed. Pages 22-8.
**************************************************************/
void AscOrder(vector<vector <int>> &data, const int totalRows, const int COL)
{
    int minIndex, minValue;
    for (int row=0; row < totalRows; row++)
    {
        minIndex = row;
        minValue = data[row][COL];
        for (int j = row + 1; j < totalRows ; j++)
        {
            if (data[j][COL] < minValue)
            {
                minValue = data[j][COL];
                minIndex = j;
            }
        }
        swap(data[minIndex][COL], data[row][COL]);
    }
}
/*****************************************************************************
Programmer: Amani Balqis Binti Johal
Name: printAscHtml
task: generate Ascending order of data to html

data in: outfile,data,header and COL

data returned: -
******************************************************************************/
void printAscHtml(ofstream &outfile,vector<vector<int>> data, vector<string> header, const int totalRows, const int COL)
{
    outfile << "<h2 style=\"text-align:center;\">ASCENDING ORDER</h2>" << endl
            << "<h3 style=\"text-align:center;\">TITLE:"<< header[COL] <<"</h3>"<< endl
            << "<style>table, th, td {border: 1px solid black;}</style> "<<endl
            << "<table style=\"width:70%;;background-color:#3A638C\">"<<endl
            << "<tr>"<< endl << "<th>" << header[0] << "</th>"<<"<th>"<<header[COL] <<"</th>" << endl<<"<tr>"<<endl;
    AscOrder(data, totalRows, COL);
    for (int size=0; size < data.size(); size++)
    {
        outfile << "<tr>"<< endl << "<td>" << data[size][0] << "</td>" << endl << "<td>" << data[size][COL]<<"</td>" << endl<<"<tr>"<<endl;
    }
    outfile << "</table>" << endl;
}

/**************************************************************
Programmer  : Nurul Syaqeera
Name        : ascendingOrder

task        : Main function to process sorting function in ascending order
data in     : List of data , header, number of rows and number of column to be chosen
data returned: position of array will be processed in ascending order
Referred to : -
**************************************************************/
void ascendingOrder(vector<vector <int>> arr,vector<string> header, const int numOfRows, const int numOfCols)
{
    string filename;
    cout << "-----------------------ASCENDING ORDER----------------------" << endl << endl;
    int col;
    col = UserInput(header, numOfCols);
    col -= 1;
    system("CLS");
    vector<vector<int>> data = arr;
    AscOrder(data, numOfRows, col);
    printAsc(data, header, col);
    if (saveDataInput())
    {
        int type = htmlortxt();
        cin.ignore();
        ofstream outfile = userInputFileName(type);
        if (type == 50)
            saveAscOrder(outfile, data, header, col);
        else if (type == 49)
            printAscHtml(outfile, data, header,numOfRows, col);
        outfile.close();
        cout << "DATA SAVED!" << endl;
        cout << "Press Enter to continue" << endl;
        cin.get();
        system("CLS");
    }
}

/**************************************************************
Programmer  : Nurul Syaqeera
Name        : Median

task        : This function will find the middle number of the selected column
data in     : List of data, selected column and the number of rows
data returned: data will be returned as number of the middle of the arrays
Referred to:  https://www.tutorialspoint.com/mean-and-median-of-a-matrix-in-cplusplus
**************************************************************/
int Median(vector<vector <int>> data,const int col, const int totalRows)
{
    AscOrder(data, totalRows, col);
    if (totalRows % 2 != 0)                     //odd
        return data[totalRows/2][col];
    else if (totalRows % 2 == 0){               //even
        return (data[totalRows/2 - 1][col] + data[totalRows/2][col])/2;
    }
}

/**************************************************************
Programmer  : Nurul Syaqeera
Name        : saveDescOrder

task        : This function will save data output in text file
data in     : List of vector arrays in selected column that have been
              sorted in descending order
data returned: -
Referred to : -
**************************************************************/
void saveDescOrder(ofstream &outfile, vector<vector <int>> data,vector<string> header, const int col)
{
    outfile << "\t------------ DESCENDING ORDER -----------" << endl << endl;
    outfile << "\t\tTITLE: " << header[col] << endl << endl;
    outfile << "\t-----------------------------------------" << endl;
    outfile << "\t|" << setw(20) << header[0] << "|" << setw(15) << header[col] << "\t|\t" << endl;
    outfile << "\t-----------------------------------------" << endl;
    for (int size=0; size < data.size(); size++)
        outfile << "\t|" << setw(20) << data[size][0] << "|" << setw(15) << data[size][col] <<"\t|\t" << endl;
    outfile << "\t-----------------------------------------" << endl << endl;
}

/**************************************************************
Programmer  : Nurul Syaqeera
Name        : printDes

task        : This will be the output of data in descending order.
data in     : List of vector arrays in selected column
data returned: -
Referred to : -
**************************************************************/
void printDes(vector<vector<int>> data, vector<string> header, const int col)
{
    cout << "-----------------------DESCENDING ORDER----------------------" << endl << endl;
    cout << "\t\tTITLE: " << header[col] << endl << endl;
    cout << "\t-----------------------------------------" << endl;
    cout << "\t|" << setw(20) << header[0] << "|" << setw(15) << header[col] << "\t|\t" << endl;
    cout << "\t-----------------------------------------" << endl;
    for (int size=0; size < data.size(); size++)
        cout << "\t|" << setw(20) << data[size][0] << "|" << setw(15) << data[size][col] <<"\t|\t" << endl;
    cout << "\t-----------------------------------------" << endl;
}


/**************************************************************
Programmer  : Nurul Syaqeera
Name        : DescOrder

task        : This function will sort data in descending order
data in     : List of vector arrays in selected column and read each row of data
data returned: position of array will be displayed
Referred to : https://stackoverflow.com/questions/53138907/how-to-reverse-selectionsort-to-display-in-descending-order
**************************************************************/
void DescOrder(vector<vector <int>> &data,vector<string> header, const int totalRows, const int col)
{
    int maxIndex, maxValue;
    for (int row=0; row < totalRows; row++)
    {
        maxIndex = row;
        maxValue = data[row][col];
        for (int j = row + 1; j < totalRows ; j++)
        {
            if (data[j][col] > maxValue)
            {
                maxValue = data[j][col];
                maxIndex = j;
            }
        }
        swap(data[maxIndex][col], data[row][col]);
    }
}

/*****************************************************************************
Programmer: Amani Balqis Binti Johal
Name: DescOrderHtml
task: generate descending order of data to html

data in: outfile,data,header,totalRows and col

data returned: -
******************************************************************************/
void DescOrderHtml(ofstream &outfile,vector<vector <int>> data,vector<string> header, const int totalRows, const int col)
{
    outfile << "<h2 style=\"text-align:center;\">DESCENDING ORDER</h2>"<< endl
            << "<h3 style=\"text-align:center;\">TITLE:" << header[col]<<"</h3>" <<endl
            << "<style>table, th, td {border: 1px solid black;}</style> "<<endl
            << "<table style=\"width:70%;;background-color:#3A638C\">"<<endl
            << "<tr>"<< endl << "<th>" << header[0] <<"</th>"<< endl <<"<th>" << header[col]<< "</th>"<<endl<< "</tr>" <<endl;
    DescOrder(data, header, totalRows, col);
    for (int size=0; size < data.size(); size++)
    {
        outfile <<"<tr>"<< endl << "<td>"<< data[size][0] <<"</td>"<< endl << "<td>"<< data[size][col]<<"</td>"<< endl<< "</tr>" <<endl;
    }
    outfile << "</table>" << endl;

}
/**************************************************************
Programmer  : Nurul Syaqeera
Name        : descendingOrder

task        : Main function to process sorting function in descending order
data in     : List of data , header, number of rows and number of column to be chosen
data returned: position of array will be processed in descending order
Referred to : -
**************************************************************/
void descendingOrder(vector<vector <int>> arr,vector<string> header, const int numOfRows, const int numOfCols)
{
    cout << "-----------------------DESCENDING ORDER----------------------" << endl << endl;
    int col;
    col = UserInput(header, numOfCols);
    col -= 1;
    system("CLS");
    vector<vector<int>> data = arr;
    DescOrder(data, header, numOfRows, col);
    printDes(data, header, col);
    if (saveDataInput())
    {
        int type = htmlortxt();
        cin.ignore();
        ofstream outfile = userInputFileName(type);
        if (type == 50)
            saveDescOrder(outfile, data, header, col);
        else if (type == 49)
            DescOrderHtml(outfile, data, header, numOfRows, col);
        outfile.close();
        cout << "DATA SAVED!" << endl;
        cout << "Press Enter to continue" << endl;
        cin.get();
        system("CLS");
    }

}

/**************************************************************
Programmer:	Chin Pei Wern
Name: 		printStatsMenu

task:			get user input of column for tabulation of mean, median, max, min and etc.
data in:	    the title of every columns, total number of columns of the data file.
data returned:	column to generate data for
Referred to:	-
**************************************************************/
int printStatsMenu(const vector<string> header, const int COL)
{
    int column;
    cout << "\tPlease input the column number to generate data for: " << endl;
    for (int i=1 ; i < COL; i++)      //loop for subscript smaller than the vector size
    {
        cout << "\t- Column " << i+1 << " : " << header[i] << endl;   //print out header name
    }
    cout << "\tEnter " << COL + 1 << " to compute data for all the columns." << endl;
    cin >> column;

    while (column < 2 && column > (COL + 1))       //if user input is not in range
    {
        cout << "Error! Invalid Input." << endl;
        cout << "Please re-enter the column to generate data for: " << endl;
        cin >> column;
    }
    system("CLS");
    return column;

}

/*******************************************************************************
Programmer: Ng Yoong Kee & Amani Balqis
Name: printStatsAllColsHtml

task: output result of statsAllCols function into html file.

data in: header, vector of standard deviation, variance, mean, max, min and median, total number of columns.
data returned: -

Referred to: https://www.w3schools.com/html/html_tables.asp
             https://www.w3schools.com/html/html_styles.asp
             https://www.w3schools.com/w3css/w3css_tables.asp

********************************************************************************/
void printStatsAllColsHtml(ofstream &outfile,vector<vector<int>> arr, vector<string>header, const int COLS, const int ROWS)
{
    outfile << "<h2 style=\"text-align:center;\">Descriptive Statistics</h2>" << endl
            << "<style>table, th, td {border: 1px solid black;}</style> "<<endl;
    outfile << setprecision(2) << fixed;
    for (int i=1; i < COLS; i++)
    {
        outfile << "<h3 style=\"text-align:center;\">TITLE: " << header[i] <<"</h3>" << endl
                << "<table style=\"width:70%;background-color:#3A638C\">"<<endl
                << "<tr>"<< endl<< "<th>Maximum</th>"<< endl << "<td>" << findHighestCol(arr,i,ROWS) << "</td>"<<endl<< "</tr>"<< endl
                << "<tr>"<< endl<< "<th>Minimum</th> "<< endl <<"<td>" << findLowestCol(arr, i, ROWS) << "</td>"<<endl<< "</tr>"<< endl
                << "<tr>"<< endl<< "<th>Mean</th> "<< endl <<"<td>" << calcMean(arr, i, ROWS) << "</td>" <<endl<< "</tr>"<< endl
                << "<tr>"<< endl<< "<th>Median</th> " << endl <<"<td>" << Median(arr,i,ROWS) << "</td>"<< endl<< "</tr>"<< endl
                << "<tr>"<< endl<< "<th>Standard Deviation</th> "<<endl << "<td>" << calcStdDev(arr, i, ROWS, calcMean(arr,i,ROWS))  << "</td>"<< endl<< "</tr>"<< endl
                << "<tr>"<< endl<< "<th>Variance</th> "<<endl << "<td>" << calcVar(calcStdDev(arr, i, ROWS, calcMean(arr,i,ROWS)) ) << "</td>"<< endl<< "</tr>"<< "</table>" << endl;
    }
}

/**************************************************************
Programmer  : Nurul Syaqeera
Name        : saveAllStats

task        : This save the output of the computed descriptive statistic.
data in     : List of vector arrays selected column, header,stdDev,var,
              mean,max,min, median
data returned: -
Referred to : -
**************************************************************/
void saveAllStats(ofstream &outfile, vector<string>header, vector<float> stdDev, vector<float> var, vector<float> mean, vector<int> max, vector<int>min,vector<float>median, const int COLS)
{
    outfile << setprecision(2) << fixed;
    outfile << "\t--------------------------- DESCRIPTIVE STATISTICS ---------------------------" << endl;
    outfile << "\t------------------------------------------------------------------------------" << endl;
    outfile << "\t|" << setw(11) << "Title|" << setw(10) << "Min" <<"|" << setw(10) << "Max" <<"|" << setw(10) << "Mean"
            <<"|" << setw(10) << "Median" <<"|" << setw(10) << "Std Dev." <<"|" << setw(10) << "Variance" <<"|"<< endl;
    outfile << "\t------------------------------------------------------------------------------" << endl << endl;
    for (int i=0; i < COLS-1; i++)
    {
        outfile << "\t|" << setw(10) << header[1+i] <<"|" << setw(10) << min[i] <<"|" << setw(10) << max[i]
            <<"|" << setw(10) << mean[i] <<"|" << setw(10) << median[i]
            << "|"  << setw(10) << stdDev[i] <<"|" << setw(10) << var[i] <<"|"<< endl;
        outfile << "\t-----------------------------------------------------------------------------" << endl << endl;
    }
}

/**************************************************************
Programmer:	Chin Pei Wern
Name: 		statsAllCols

task:			compute and print the statistics of all columns
data in:	    data in 2d vector,the title of every columns, total number of rows and columns of the data file.
data returned:	-
Referred to:	-
**************************************************************/
void statsAllCols(vector<vector<int>> arr,vector<string>header, const int ROWS, const int COLS)
{
    cout << fixed << setprecision(2);
    float mean, stdDev, var, median;
    int max, min;
    vector<float> meanArr, stdDevArr, varArr, medianArr;
    vector<int> maxArr, minArr;
    for (int i=1; i < COLS; i++)
    {
        mean = calcMean(arr, i, ROWS);
        stdDev = calcStdDev(arr, i, ROWS, mean);
        var = calcVar(stdDev);
        max = findHighestCol(arr, i, ROWS);
        min = findLowestCol(arr, i, ROWS);
        median = Median(arr, i, ROWS);
        medianArr.push_back(median);
        stdDevArr.push_back(stdDev);
        varArr.push_back(var);
        meanArr.push_back(mean);
        maxArr.push_back(max);
        minArr.push_back(min);
    }
    cout << "\t------------------------------------------------------------------------------" << endl;
    cout << "\t|" << setw(11) << "Title|" << setw(10) << "Min" <<"|" << setw(10) << "Max" <<"|" << setw(10) << "Mean"
         <<"|" << setw(10) << "Median" <<"|" << setw(10) << "Std Dev." <<"|" << setw(10) << "Variance" <<"|"<< endl;
    cout << "\t------------------------------------------------------------------------------" << endl;
    for (int i=0; i < COLS-1; i++)
    {
        cout << "\t|" << setw(10) << header[1+i] <<"|" << setw(10) << minArr[i] <<"|" << setw(10) << maxArr[i]
             <<"|" << setw(10) << meanArr[i] <<"|" << setw(10) << medianArr[i]
             << "|"  << setw(10) << stdDevArr[i] <<"|" << setw(10) << varArr[i] <<"|"<< endl;
        cout << "\t-----------------------------------------------------------------------------" << endl;
    }
    if(saveDataInput())
    {
        int type = htmlortxt();
        cin.ignore();
        ofstream outfile = userInputFileName(type);
        if (type == 50)
            saveAllStats(outfile, header, stdDevArr, varArr, meanArr, maxArr, minArr, medianArr, COLS);
        else if (type == 49)
            printStatsAllColsHtml(outfile, arr, header, COLS, ROWS);
        outfile.close();
        cout << "DATA SAVED!" << endl;
        cout << "Press Enter to continue" << endl;
        cin.get();
        system("CLS");
    }
}
/**************************************************************
Programmer:	Chin Pei Wern
Name: 		saveStats

task:			save statistics in a file
data in:	    data in 2d vector,the title of every columns, total number of rows and columns of the data file,
                standard deviation, variance, mean, maximum, minimum, and median of the selected column
data returned:	-
Referred to:	-
**************************************************************/
void saveStats(ofstream &outfile,vector<string> header,const float stdDev,const float var,const float mean,const int max,const int min,const int median, const int column)
{
    outfile << setprecision(2) << fixed;
    outfile << "\t TITLE : " << header[column] << endl << endl;
    outfile << "\t---------------------------------" << endl;
    outfile << "\t|" << setw(20) << "MINIMUM" << "|" <<setw(10) << min << "|"<< endl
            << "\t---------------------------------" << endl
            << "\t|" << setw(20) << "MAXIMUM" << "|" << setw(10) << max << "|"<< endl
            << "\t---------------------------------" << endl
            << "\t|" << setw(20)<< "MEAN" << "|" << setw(10) << mean << "|"<< endl
            << "\t---------------------------------" << endl
            << "\t|" << setw(20) << "MEDIAN" << "|" << setw(10) << median << "|"<< endl
            << "\t---------------------------------" << endl
            << "\t|" << setw(20) << "STANDARD DEVIATION" << "|" << setw(10) << stdDev << "|"<< endl
            << "\t---------------------------------" << endl
            << "\t|" << setw(20) << "VARIANCE" << "|" << setw(10) << var << "|"<< endl;
    outfile << "\t--------------------------------" << endl;
}

/*******************************************************************************
Programmer: Ng Yoong Kee
Name: htmlStats

task: output result of stats function into html file.

data in: header, number of column that user input, value of min, max, mean, median, standard deviation and variance
data returned: -

Referred to: https://www.w3schools.com/html/html_tables.asp
             https://www.w3schools.com/html/html_styles.asp
             https://www.w3schools.com/w3css/w3css_tables.asp

********************************************************************************/
void htmlStats(ofstream &ofile,vector<string> header, int column, int min, int max, float mean, int median, float stdDev, float var)
{
    ofile << setprecision(2) << fixed;
    ofile << "<html>\n<body>\n" << "<link rel=\"stylesheet\" href=\"https://www.w3schools.com/w3css/4/w3.css\">\n"
          << "<div class=\"w3-container\">\n" << "<table class=\"w3-table-all w3-card-4\"> \n";
    ofile << "<h2 style=\"text-align:center;\"> TITLE : " << header[column] << "</h2>\n\n";
    ofile << "<tr>\n" << "<th>MINIMUM</th>\n" << "<td>" << min << "</td>\n"<< "</tr>\n"
          << "<tr>\n" << "<th>MAXIMUM</th>\n" << "<td>" << max << "</td>\n"<< endl
          << "<tr>\n" << "<th>MEAN</th>\n" << "<td>"  << mean << "</td>\n"<< endl
          << "<tr>\n" << "<th>MEDIAN</th>\n" << "<td>"  << median << "</td>\n"<< endl
          << "<tr>\n" << "<th>STANDARD DEVIATION</th>\n" << "<td>"  << stdDev << "</td>\n"<< endl
          << "<tr>\n" << "<th>VARIANCE</th>\n" << "<td>"  << var << "</td>\n"<< endl;
    ofile << "</table>\n</div>\n</body>\n</html>\n";
}
/**************************************************************
Programmer:	Chin Pei Wern
Name: 		stats

task:			gather, compute and print the statistics of desired columns
data in:	    data in 2d vector,the title of every columns, total number of rows and columns of the data file.
data returned:	-
Referred to:	-
**************************************************************/
void stats(vector<vector <int>> arr,vector<string> header, const int ROWS,const int COLS)
{
    cout << setprecision(2) << fixed;
    int column = printStatsMenu(header, COLS);
    float mean, stdDev, var;
    int max, min, median;
    column -= 1;
    cout << "\t----------------------DESCRIPTIVE STATISTICS-----------------------" << endl << endl;
    if (column >= 1 && column < COLS)
    {
        mean = calcMean(arr, column, ROWS);
        stdDev = calcStdDev(arr, column, ROWS, mean);
        var = calcVar(stdDev);
        max = findHighestCol(arr, column, ROWS);
        min = findLowestCol(arr, column, ROWS);
        median = Median(arr, column, ROWS);
        cout << "\t TITLE : " << header[column] << endl << endl;
        cout << "\t---------------------------------" << endl;
        cout << "\t|" << setw(20) << "MINIMUM" << "|" <<setw(10) << min << "|"<< endl
             << "\t---------------------------------" << endl
             << "\t|" << setw(20) << "MAXIMUM" << "|" << setw(10) << max << "|"<< endl
             << "\t---------------------------------" << endl
             << "\t|" << setw(20)<< "MEAN" << "|" << setw(10) << mean << "|"<< endl
             << "\t---------------------------------" << endl
             << "\t|" << setw(20) << "MEDIAN" << "|" << setw(10) << median << "|"<< endl
             << "\t---------------------------------" << endl
             << "\t|" << setw(20) << "STANDARD DEVIATION" << "|" << setw(10) << stdDev << "|"<< endl
             << "\t---------------------------------" << endl
             << "\t|" << setw(20) << "VARIANCE" << "|" << setw(10) << var << "|"<< endl;
         cout << "\t--------------------------------" << endl;
         if(saveDataInput())
        {
            int type = htmlortxt();
            cin.ignore();
            ofstream outfile = userInputFileName(type);
            if (type == 50)
                saveStats(outfile, header, stdDev, var, mean, max, min, median, column);
            else if (type == 49)
                htmlStats(outfile, header,column,min, max, mean, median,stdDev, var);
            outfile.close();
            cout << "DATA SAVED!" << endl;
            cout << "Press Enter to continue" << endl;
            cin.get();
            system("CLS");
        }
    }
    else if (column == COLS)
        statsAllCols(arr, header, ROWS, COLS);
}

/**************************************************************
Programmer:	Chin Pei Wern
Name: 		printTabularFormMenu

task:			print out the menu for descriptive statistics, and call the functions desired according to user input
data in:	    data in 2d vector,the title of every columns, total number of rows and columns of the data file.
data returned:	-
Referred to:	-
**************************************************************/
void printTabularFormMenu( vector <vector<int>> arr,const  vector<string>header, const int ROWS, const int COLS)
{
    for(int i=0; i < COLS; i++)
        AscOrder(arr, ROWS, i);
    int tblChoice;
    cout << "\t------------------------DESCRIPTIVE STATISTICS-------------------------" << endl;
    cout << endl;
    cout << "\t Please select an option: " << endl;
    cout << "\t 1. Tabulation of Distinct Number and Its Frequency" << endl;
    cout << "\t 2. Tabulation of :" << endl;
    cout << "\t   > Minimum" << endl << "\t   > Maximum" << endl << "\t   > Mean" << endl;
    cout << "\t   > Median" << endl << "\t   > Standard Deviation" << endl << "\t   > Variance" << endl;
    cout << "\t 3. Table of Data Items Below and Above the Mean" << endl;
    cout << "\t 4. Back to Main Menu" << endl;
    cin >> tblChoice;

    while (tblChoice < 1 || tblChoice > 4)
    {
        cout << "Input Error! Please select an option from 1 to 4" << endl;
        cin >> tblChoice;
    }
    system("CLS");
    if (tblChoice == 1)
        distNumAndFreq(arr, header, ROWS, COLS);
    else if (tblChoice == 2)
        stats(arr, header, ROWS, COLS);
    else if (tblChoice == 3)
        aboveAndBelowMean(arr, header, ROWS, COLS);
    else if (tblChoice == 4)
        system("CLS");
}

/*****************************************************************************
Programmer: Chin Pei Wern, Ng Yoong Kee and Amani Balqis Binti Johal
Name: htmlData
task: call all html function of data

data in: outfile,arr,header, COLS and ROWS

data returned: -
******************************************************************************/
void htmlData( vector<vector<int>> arr, const vector<string> header, const int ROWS, const int COLS)
{
    ofstream  outfile;
    outfile.open("StatisticalReport.html");
    outfile << "<html><head><title>HTML REPORT</title></head>"<< endl
            << "<body style=\"background-color:rgba(63, 127, 191, 0.2);\">" << endl
            << "<h2 style=\"text-align:center;\">Statistical Report</h2>" << endl
            << "<style>table, th, td {border: 1px solid black; border-collapse: collapse;}</style> "<<endl
            << "<center><table style=\"width:70%;background-color:#3A638C\">"<<endl
            << setprecision(2) << showpoint << fixed;;
    printStatsAllColsHtml(outfile,arr,header, COLS,ROWS);
    for (int col=1; col < COLS; col++)
    {
        AscOrder(arr, ROWS,col);
        float mean = calcMean(arr, col, ROWS);
        printDistNumNFreqHtml(outfile, header, arr ,ROWS, col);
        vector<int> above_mean = aboveMean(arr, header, col, ROWS, mean);
        htmlAboveMean(outfile, arr, header, col, above_mean);

        vector<int> below_mean = belowMean(arr, header,col, ROWS, mean);
        htmlBelowMean(outfile, arr, header, col, below_mean);
        printAscHtml(outfile, arr, header, ROWS,col);
        DescOrderHtml(outfile, arr, header, ROWS, col);
        printHistogramHtml(outfile,header,arr, col, ROWS);
    }
    pearsonCorHtml(outfile,header, arr, ROWS, 2, 3);
    RegMnCHtml(outfile,header,arr, ROWS, 2, 3);

    outfile << "</table><center>" <<endl
            << "</body>" << endl
            << "</html>" << endl;
    outfile.close();
}
/**************************************************************
Programmer:	Nurul Syaqeera & Chin Pei Wern
Name: 		statReport

task:			gather all functions needed to create a statistical report in text file
data in:	    data in 2d vector,the title of every columns, total number of rows and columns of the data file.
data returned:	-
Referred to:	-
**************************************************************/
void statReport( vector<vector<int>> arr,const vector<string> header, const int ROWS, const int COLS)
{
    ofstream  outfile;
    int col,x,y;
    outfile.open("StatisticalReport.txt", ios::out | ios::app);
    if(!outfile)
    {
        cout << "Error in creating file" << endl;
    }
    outfile << "\t------------------------------------------------------------------------" << endl;
    outfile << "\t|                         STATISTICAL REPORT                           |" << endl;
    outfile << "\t------------------------------------------------------------------------" << endl << endl;
    for (int i=1; i < COLS; i++)
    {
        AscOrder(arr, ROWS, i);
        vector<int> distinctNum = distNum(arr, ROWS, i);
        vector<int> freq = freqOfDistNum(arr, ROWS, i);
        saveDistNumfreq(outfile, distinctNum, freq, header,i);
        float mean, stdDev, var, max, min, median;

        outfile << "\t-------------------------- DESCRIPTIVE STATISTICS ----------------------------" << endl;
        outfile << "\t------------------------------------------------------------------------------" << endl
                << "\t|" << setw(11) << "Title|" << setw(10) << "Min" <<"|" << setw(10) << "Max" <<"|" << setw(10) << "Mean"
                <<"|" << setw(10) << "Median" <<"|" << setw(10) << "Std Dev." <<"|" << setw(10) << "Variance" <<"|"<< endl;
        outfile << "\t------------------------------------------------------------------------------" << endl;
        mean = calcMean(arr, i, ROWS);
        stdDev = calcStdDev(arr, i, ROWS, mean);
        var = calcVar(stdDev);
        max = findHighestCol(arr, i, ROWS);
        min = findLowestCol(arr, i, ROWS);
        median = Median(arr, i, ROWS);
        outfile << "\t|" << setw(10) << header[i] <<"|" << setw(10) << min <<"|" << setw(10) << max
                <<"|" << setw(10) << mean <<"|" << setw(10) << median
                << "|"  << setw(10) << stdDev <<"|" << setw(10) << var <<"|"<< endl;
        outfile << "\t-----------------------------------------------------------------------------" << endl << endl;
        vector<int> above_mean = aboveMean(arr, header, i, ROWS, mean);
        saveAboveMean(outfile, arr, header, above_mean, i);

        vector<int> below_mean = belowMean(arr, header,i, ROWS, mean);
        saveBelowMean(outfile, arr, header, below_mean, i);
        saveAscOrder(outfile, arr, header, i);

        vector<vector<int>> descData = arr;
        DescOrder(descData, header, ROWS, i);
        saveDescOrder(outfile, descData, header, i);

        saveHistogram(outfile, arr, header, i, ROWS);
    }
    saveLineReg(outfile, arr, header, ROWS, 2,3);
    savePearson(outfile, arr,header, ROWS, 2,3);
    outfile.close();
}

/**************************************************************
Programmer:	Chin Pei Wern
Name: 		printDataSortingMenu

task:			print menu for data sorting, and get user input for their data choice
data in:	    data in 2d vector,the title of every columns, total number of rows and columns of the data file.
data returned:	-
Referred to:	-
**************************************************************/
void printDataSortingMenu(const vector<vector<int>> arr,const vector<string> header, const int ROWS, const int COLS)
{
    int sortChoice;
    cout << "------------------------------- DATA SORTING ------------------------------" << endl;
    cout << endl;
    cout << "Please select an option: " << endl;
    cout << endl;
    cout << "1. Data in Ascending Order" << endl;
    cout << "2. Data in Descending Order" << endl;
    cout << "3. Back to Main Menu" << endl;
    cin >> sortChoice;

    while (sortChoice < 1 && sortChoice >3)
    {
        cout << "Input error! Please select an option from 1 to 3" << endl;
        cin >> sortChoice;
    }
    system("CLS");
    if (sortChoice == 1)
        ascendingOrder(arr, header, ROWS, COLS);
    else if (sortChoice == 2)
        descendingOrder(arr, header, ROWS, COLS);
    else if (sortChoice == 3)
        system("CLS");
}


/**************************************************************
Programmer:	Chin Pei Wern
Name: 		printMainMenu

task:			print main menu and get user input of their desired data choice
data in:	    data in 2d vector,the title of every columns, total number of rows and columns of the data file.
data returned:	user option
Referred to:	-
**************************************************************/
int printMainMenu()
{
    int option;
    cout << endl << "------------------------BASIC DATA ANALYSIS APPLICATION-----------------------" << endl;
    cout << endl;
    cout << "Please select an option: " << endl;
    cout << "1. Descriptive Statistics" << endl; //data in tabular form
    cout << "2. Data Sorting" << endl;
    cout << "3. Tabulation of Data Graph" << endl;
    cout << "4. Statistical Report" << endl;
    cout << "5. Exit the program" << endl;
    cin >> option;
    while (option < 1 || option > 5)
    {
        cout << "Error! Please choose an option from 1 to 5." << endl;
        cin >> option;
    }
    system("CLS");
    return option;
}

/**************************************************************
Programmer:	Chin Pei Wern
Name: 		printDataGraphMenu

task:			print data graph menu and get user input of their desired data choice
data in:	    data in 2d vector,the title of every columns, total number of rows and columns of the data file.
data returned:	-
Referred to:	-
**************************************************************/
void printDataGraphMenu(const vector <vector<int>> arr,const vector<string> headers, const int ROWS, const int COLS)
{
    int graphChoice;
    cout << "\t--------------------TABULATION OF DATA GRAPH---------------------" << endl;
    cout << endl;
    cout << "\tPlease select an option: " << endl;
    cout << "\t1. Histogram of Data in Textual Form" << endl;
    cout << "\t2. Linear Regression Line Formula" << endl;
    cout << "\t3. Pearson's Correlation" << endl;
    cout << "\t4. Back to Main Menu" << endl;
    cin >> graphChoice;

    while (graphChoice < 1 && graphChoice >4)
    {
        cout << "Input Error! Please select an option between 1 and 4" << endl;
        cin >> graphChoice;
    }
    system("CLS");

    if (graphChoice == 1)
        histogram(arr,headers,ROWS, COLS);
    else if (graphChoice == 2)
        lineReg(arr, headers, COLS, ROWS);
    else if (graphChoice == 3)
        pearson(arr, headers, COLS, ROWS);
    else if (graphChoice == 4)
        system("CLS");
}

/**************************************************************
Programmer:	Chin Pei Wern
Name: 		statisticalReport

task:			print statistical report menu and get user input of their desired file type choice
data in:	    data in 2d vector,the title of every columns, total number of rows and columns of the data file.
data returned:	-
Referred to:	-
**************************************************************/
void statisticalReport(vector<vector<int>> data, vector<string> header, const int ROWS, const int COLS)
{
    int statChoice;
    cout << "\t--------------------STATISTICAL REPORT---------------------" << endl;
    cout << endl;
    cout << "\tPlease select an option: " << endl;
    cout << "\t1. txt file " << endl;
    cout << "\t2. HTML file" << endl;
    cout << "\t3. Back to Main Menu" << endl;
    cin >> statChoice;
    while (statChoice < 1 && statChoice >3)
    {
        cout << "Input Error! Please select an option between 1 and 2" << endl;
        cin >> statChoice;
    }
    cin.ignore();
    if (statChoice == 1)
    {
        statReport(data, header, ROWS, COLS);
        cout << "FILE SAVED INTO StatisticalReport.txt!" << endl;
        cout << "Press Enter to continue." << endl;
        cin.get();
        system("CLS");
    }
    else if (statChoice == 2)
    {
        htmlData(data, header, ROWS, COLS);
        cout << "FILE SAVED INTO StatisticalReport.html!" << endl;
        cout << "Press Enter to continue." << endl;
        cin.get();
        system("CLS");
    }
    else if (statChoice == 3)
        system("CLS");
}


int main()
{
    ifstream infile = FileName();
    int columns, rows;              //variable for total number of columns and total number of rows
    vector<string> header;          //create a vector to contain all header names
    readHeader(infile, columns, rows, header);
    vector <vector <int>> data;    //create a 2d vector to contain all data items inside
    readData(infile, data);
    detectFormatError(data, columns, rows);

    do
    {
        int option = printMainMenu();     //print out main menu

        if (option == 1)
            printTabularFormMenu(data, header, rows, columns);
        else if (option == 2)
            printDataSortingMenu(data, header, rows, columns);
        else if (option == 3)
            printDataGraphMenu(data, header, rows, columns);
        else if (option == 4)
            statisticalReport(data, header, rows, columns);
        else if (option == 5)
            exit(-1);
    }while(true);

    return 0;
}
