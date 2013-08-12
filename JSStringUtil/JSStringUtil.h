//
//  JSStringUtil.h
//  JSStringUtil
//
//  Created by Johan Sundhage on 2013-08-08.
//  Copyright (c) 2013 Johan Sundhage. All rights reserved.
//

#ifndef JSStringUtil_JSStringUtil_h
#define JSStringUtil_JSStringUtil_h

#include <stdbool.h>


typedef struct jsstring_t {
    const char* str;
    unsigned long length;
} jsstring_t;

extern jsstring_t* jss_alloc();

extern jsstring_t* jss_init(jsstring_t* instance);

extern jsstring_t* jss_init_with_c_string(jsstring_t* instance, const char* cstring);


// returns a not-on-stack
extern jsstring_t* jss_create(const char* string);

// frees the structure + string data
extern void jss_destroy(jsstring_t* string);

// frees an array of strings
extern void jss_destroy_list(jsstring_t** list, int count);

// returns a not-on-stack ordinary c-string.
extern const char* jss_copy(jsstring_t* string, bool destroy_input);

// returns pointer to the CString (not a copy, just a reference)
extern const char* jss_c_string(jsstring_t* string);

// returns numbers of characters
extern unsigned long jss_get_length(jsstring_t* string);

// concatinates two strings into one new
extern jsstring_t* jss_concat(jsstring_t* beginning, jsstring_t* trailing, bool destroy_input);

// returns a fraction of string
extern jsstring_t* jss_substr(jsstring_t* string, unsigned int start_index, int length, bool destroy_input);

// an array of pointers to jsstring_t
extern jsstring_t** jss_split(jsstring_t* string, char delimiter, bool destroy_input, int* out_count);

// returns character index where the first occurance of the match parameter is. if not found return -1
extern int jss_search(jsstring_t* string, jsstring_t* match, int start_index);
// returns character index where the first occurance of the match parameter is. if not found return -1
extern int jss_search_c_string(jsstring_t* string, const char* match, int start_index);

#endif
