#ifndef __numberoflines_H
#define __numberoflines_H
#include<iostream>
#include<fstream>

int get_numberoflines()
{
  int number_of_lines = 0;
  std::string line;
  std::ifstream myfile("urllist.txt");
  while(std::getline(myfile, line))
    ++number_of_lines;
  std::cout<<"number of lines in text file is :" <<number_of_lines;
  return number_of_lines;
}


#endif

