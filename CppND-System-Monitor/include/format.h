#ifndef FORMAT_H
#define FORMAT_H

#include <string>

namespace Format {
std::string ElapsedTime(long seconds);  //Convert long int measuring seconds into HH:MM:SS format
std::string TimeToString(long time);//If hours or minutes or seconds in HH:MM:SS are in single digit, append a zero before them
};                                    

#endif