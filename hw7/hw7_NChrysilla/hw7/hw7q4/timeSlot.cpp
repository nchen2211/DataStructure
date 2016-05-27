#include <sstream>
#include <cstdlib>
#include <algorithm>
#include "timeSlot.h"

using namespace std;

TimeSlot::TimeSlot() {}

TimeSlot::~TimeSlot() {

    for(int i=0; i <totalExam ; i++)
      delete [] scheduleTable [i];

    delete [] scheduleTable; 
    scheduleTable = NULL;
}

void TimeSlot::readFile(istream &file)
{
    stringstream ss;
    string line;

    // get the first line
    getline(file,line);
    ss << line;
    ss >> totalExam;
    ss >> totalStudent;
    ss >> totalSlot;

    // initializing scheduleTable
    scheduleTable = new int*[totalExam];
    for(int i=0; i<totalExam; i++)
        scheduleTable[i] = new int [totalStudent];

    for(int i=0; i<totalExam; i++)
        for(int j=0; j<totalSlot; j++)
            scheduleTable[i][j] = 0;

    int r = 0;
    int c = 0;
    int courseNumber;

    while (!file.eof())
    {
        string name;
        stringstream s;
        
        getline(file,line);
        if (line != "")
        {
            s << line; 
            s >> name;

            while (s >> courseNumber)
            {
                std::vector<int>::iterator it;
                it = find(course.begin(), course.end(), courseNumber); // for storing unique course

                //if !find
                if(it == course.end())
                {
                    course.push_back(courseNumber);
                    r = course.size() - 1;
                }
                else
                    r = it - course.begin();

                scheduleTable[r][c] = 1;
            }
        }
        ++c;   
    }


    // backtracking
    if (scheduling(0,1))
    {
        AVLTree<int,int>::iterator it = avltree.begin();
        for(; it != avltree.end(); ++it)
            std::cout << it->first << " " << it->second << std::endl;
    }
    else
        std::cout << "No valid solution" << std::endl;
}

bool TimeSlot::isValid(int c, int slot)
{
    for (int i=0; i<totalStudent; ++i)
    {
        if (scheduleTable[c][i] == 1)
        {
            for (unsigned int j=0; j < course.size(); j++)
            {
                if (scheduleTable[j][i] == 1 && j != unsigned(c))
                {
                    AVLTree<int,int>::iterator it = avltree.find(course[j]);
                    if(it != avltree.end() && it->second == slot)
                        return false;
                }
            }
        }
    }
    return true;
}

bool TimeSlot::scheduling(int c, int slot)
{
    if (c >= totalExam)
        return true;

    for (int i=1; i<= totalSlot; i++)
    {
        avltree.insert(std::make_pair(course[c],i));

        if (isValid(c,i) && scheduling(c+1, i))
            return true;

        avltree.remove(course[c]);
    }
    return false;
    scheduling(c+1,1);
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cerr<< "Please provide an input file." << std::endl;
        return 1;
    }

    std::ifstream inputFile (argv[1]);
    if (!inputFile)
        std::cout << "File is not open" << std::endl;

    TimeSlot timeslot;  
    timeslot.readFile(inputFile);
}
