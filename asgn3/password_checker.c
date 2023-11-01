#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "password_checker.h"

bool check_length(const char *password) {
    int length = strlen(password);
    bool meets_len_req = (length >= 10);
    return meets_len_req;
}

bool check_range(char letter, char lower, char upper) {
    bool is_in_range = (letter >= lower && letter <= upper);
    return is_in_range;
}

bool check_upper(const char *password) {
    while (*password != '\0') {
        bool is_in_range = check_range(*password, 'A', 'Z');
        if (is_in_range) {
            return true;
        }
        ++password;
    }
    return false;
}

bool check_lower(const char *password) {
    while (*password != '\0') {
        bool is_in_range = check_range(*password, 'a', 'z');
        if (is_in_range) {
            return true;
        }
        ++password;
    }
    return false;
}

bool check_number(const char *password) {
    while (*password != '\0') {
        if (isdigit(*password)) {
            return true;
        }
        ++password;
    }
    return false;
}

bool check_name(const char *first_name, const char *last_name, const char *password) {
    const char *first = strstr(password, first_name);
    const char *last = strstr(password, last_name);
    return (!first && !last);
}

bool check_password(const char *first_name, const char *last_name, const char *password) {
    bool length, upper, lower, number, name;
    lower = check_lower(password);
    length = check_length(password);
    //assert(lower);
    name = check_name(first_name, last_name, password);
    number = check_number(password);
    upper = check_upper(password);
    return (lower && length && name && upper && number);
}
