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


typedef struct JSString_ {
    const char* str;
    unsigned long length;
} JSString;

// returns a not-on-stack
extern JSString* JSSCreate(const char* string);

// frees the structure + string data
extern void JSSDestroy(JSString* string);

// frees an array of strings
extern void JSSDestroyList(JSString** list, int count);

// returns a not-on-stack ordinary c-string.
extern const char* JSSCopy(JSString* string, bool destroyInput);

// returns pointer to the CString (not a copy, just a reference)
extern const char* JSSCString(JSString* string);

// returns numbers of characters
extern unsigned long JSSGetLength(JSString* string);

// concatinates two strings into one new
extern JSString* JSSConcat(JSString* beginning, JSString* trailing, bool destroyInput);

// returns a fraction of string
extern JSString* JSSSubstr(JSString* string, unsigned int startIndex, int length, bool destroyInput);

// an array of pointers to JSString
extern JSString** JSSSplit(JSString* string, char delimiter, bool destroyInput, int* outCount);

// returns character index where the first occurance of the match parameter is. if not found return -1
extern int JSSSearch(JSString* string, JSString* match, int startIndex);
// returns character index where the first occurance of the match parameter is. if not found return -1
extern int JSSSearchCString(JSString* string, const char* match, int startIndex);

#endif
