//
//  JSStringUtil.c
//  JSStringUtil
//
//  Created by Johan Sundhage on 2013-08-08.
//  Copyright (c) 2013 Johan Sundhage. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JSStringUtil.h"

JSString* JSSCreate(const char* cstring) {
    JSString* obj = (JSString*)malloc(sizeof(JSString));
    if (cstring) {
        obj->length = strlen(cstring)+1;
        obj->str = malloc(obj->length);
        memcpy((void*)obj->str, cstring, obj->length);
    } else {
        obj->length = 0;
        obj->str = malloc(1);
        *(char*)(obj->str) = '\0';
    }
    return obj;
}

// frees the structure + string data
void JSSDestroy(JSString* string) {
    if (string->str)
        free((void*)string->str);
    free((void*)string);
}

// frees an array of strings
void JSSDestroyList(JSString** list, int count) {
    int i;
    for (i=0; i<count; i++) {
        JSSDestroy(list[i]);
    }
    free((void**)list);
}

// returns a not-on-stack ordinary c-string.
const char* JSSCopy(JSString* string, bool destroyInput) {
    const char* ns = malloc(string->length);
    memcpy((void*)ns, string->str, string->length);
    if (destroyInput) JSSDestroy(string);
    return ns;
}

// returns pointer to the CString (not a copy, just a reference)
const char* JSSCString(JSString* string) {
    return string->str;
}

unsigned long JSSGetLength(JSString* string) {
    return string->length-1;
}

// concatinates two strings into one new
JSString* JSSConcat(JSString* beginning, JSString* trailing, bool destroyInput) {
    unsigned long totLen = beginning->length+trailing->length-1;
    
    const char* result = (const char*)malloc(totLen);
    memcpy((void*)result, beginning->str, beginning->length-1);
    void* middle = (void*)(result+beginning->length-1);
    memcpy((void*)middle, trailing->str, trailing->length);
    JSString* obj = (JSString*)malloc(sizeof(JSString));
    obj->length = totLen;
    obj->str = result;
    if (destroyInput) {
        JSSDestroy(beginning);
        JSSDestroy(trailing);
    }
    return obj;
}

// returns a fraction of string
JSString* JSSSubstr(JSString* string, unsigned int startIndex, int length, bool destroyInput) {
    // sanitize -> out comes endPos
    unsigned long slen = string->length-1;
    if (startIndex >= slen) return NULL;
    int endPos = startIndex+length;
    if (endPos > slen || length < 1) endPos = (int)slen;
    
    
    int totLen = endPos-startIndex+1;
    
    char* result = (char*)malloc(totLen);
    memcpy(result, (void*)string->str+startIndex, totLen-1);
    
    //null terminate
    *(result+totLen-1) = '\0';

    
    // returning object
    JSString* obj = (JSString*)malloc(sizeof(JSString));
    obj->length = totLen;
    obj->str = result;
    
    if (destroyInput) JSSDestroy(string);
    
    return obj;
}

// an array of pointers to JSString
JSString** JSSSplit(JSString* string, char delimiter, bool destroyInput, int* outCount) {
    
    int len = (int)JSSGetLength(string);
    int i, count = 1, listIndex = 0, startPos = 0;
    const char* os = JSSCString(string);
    
    // check occurance count
    for (i=0; i<len; i++) {
        if (os[i] == delimiter) count++;
    }
    printf("%i\n", count);
    
    // create list
    JSString** list = (JSString**)malloc(sizeof(JSString*)*count);
    
    for (i=0; i<len; i++) {
        if (os[i] == delimiter) {
            int slen = i-startPos;
            if (slen <= 0) {
                list[listIndex] = JSSCreate(NULL);
            } else {
                list[listIndex] = JSSSubstr(string, startPos, slen, false);
            }
            
            startPos = i+1;
            listIndex++;
        }
    }
    
    // last item
    if (startPos < len) {
        list[listIndex] = JSSSubstr(string, startPos, len-startPos, false);
    } else if (startPos == len){
        list[listIndex] = JSSCreate(NULL);
    }
    *outCount = count;
    
    return list;
}

// returns character index where the first occurance of the string is
int JSSSearch(JSString* string, JSString* match, int startIndex) {
    if (startIndex>string->length-1) return -1;
    char* res = strstr(string->str+startIndex, match->str);
    if (res)
        return (int)(res-string->str);
    return -1;
}

int JSSSearchCString(JSString* string, const char* match, int startIndex) {
    if (startIndex>string->length-1) return -1;
    char* res = strstr(string->str+startIndex, match);
    if (res)
        return (int)(res-string->str);
    return -1;
    
}

