#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <list>

class StringUtils
{
public:
    static void split(std::list<std::string>& a_vector,
                      const std::string& a_line,
                      const std::string& a_delimiter)
    {
        a_vector.clear();
        
        const char *delimiter = a_delimiter.c_str();
        char *cstr = const_cast<char*>(a_line.c_str());
        char *current_char = strtok(cstr, delimiter);
        
        while (current_char != NULL)
        {
            a_vector.push_back(std::string(current_char));
            current_char = strtok(NULL, delimiter);
        }
    }
    static bool replace(std::string &a_string,
                        const std::string &a_stringFrom,
                        const std::string &a_stringTo)
    {
        size_t current_pos = a_string.find(a_stringFrom);
        if (current_pos == std::string::npos)
        {
            return false;
        }
        std::string aux = a_string;
        size_t aux_pos = current_pos;
        while (current_pos != std::string::npos)
        {
            aux.replace(aux_pos, a_stringFrom.length(), a_stringTo);
            current_pos = a_string.find(a_stringFrom, current_pos + 1);
            aux_pos = aux.find(a_stringFrom, aux_pos + 1);
        }
        a_string = aux;
        return true;
    }
};

#endif // STRING_UTILS_H
