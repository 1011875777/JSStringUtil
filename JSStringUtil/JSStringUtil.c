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

jsstring_t* jss_alloc() {
    jsstring_t* obj = (jsstring_t*)malloc(sizeof(jsstring_t));
    return obj;
    
}

jsstring_t* jss_init(jsstring_t* instance) {
    instance->length = 0;
    instance->str = malloc(1);
    *(char*)(instance->str) = '\0';
    return instance;
}

jsstring_t* jss_init_with_c_string(jsstring_t* instance, const char* cstring) {
    if (cstring == NULL) return jss_init(instance);
    
    instance->length = strlen(cstring)+1;
    instance->str = malloc(instance->length);
    memcpy((void*)instance->str, cstring, instance->length);
    return instance;
    
}

jsstring_t* jss_create(const char* cstring) {
    return jss_init_with_c_string(jss_alloc(), cstring);
}



// frees the structure + string data
void jss_destroy(jsstring_t* string) {
    if (string->str)
        free((void*)string->str);
    free((void*)string);
}

// frees an array of strings
void jss_destroy_list(jsstring_t** list, int count) {
    int i;
    for (i=0; i<count; i++) {
        jss_destroy(list[i]);
    }
    free((void**)list);
}

// returns a not-on-stack ordinary c-string.
const char* jss_copy(jsstring_t* string, bool destroy_input) {
    const char* ns = malloc(string->length);
    memcpy((void*)ns, string->str, string->length);
    if (destroy_input) jss_destroy(string);
    return ns;
}

// returns pointer to the CString (not a copy, just a reference)
const char* jss_c_string(jsstring_t* string) {
    return string->str;
}

unsigned long jss_get_length(jsstring_t* string) {
    return string->length-1;
}

// concatinates two strings into one new
jsstring_t* jss_concat(jsstring_t* beginning, jsstring_t* trailing, bool destroy_input) {
    unsigned long totLen = beginning->length+trailing->length-1;
    
    const char* result = (const char*)malloc(totLen);
    memcpy((void*)result, beginning->str, beginning->length-1);
    void* middle = (void*)(result+beginning->length-1);
    memcpy((void*)middle, trailing->str, trailing->length);
    jsstring_t* obj = (jsstring_t*)malloc(sizeof(jsstring_t));
    obj->length = totLen;
    obj->str = result;
    if (destroy_input) {
        jss_destroy(beginning);
        jss_destroy(trailing);
    }
    return obj;
}

// returns a fraction of string
jsstring_t* jss_substr(jsstring_t* string, unsigned int start_index, int length, bool destroy_input) {
    // sanitize -> out comes endPos
    unsigned long slen = string->length-1;
    if (start_index >= slen) return NULL;
    int endPos = start_index+length;
    if (endPos > slen || length < 1) endPos = (int)slen;
    
    
    int totLen = endPos-start_index+1;
    
    char* result = (char*)malloc(totLen);
    memcpy(result, (void*)string->str+start_index, totLen-1);
    
    //null terminate
    *(result+totLen-1) = '\0';

    
    // returning object
    jsstring_t* obj = (jsstring_t*)malloc(sizeof(jsstring_t));
    obj->length = totLen;
    obj->str = result;
    
    if (destroy_input) jss_destroy(string);
    
    return obj;
}

// an array of pointers to jsstring_t
jsstring_t** jss_split(jsstring_t* string, char delimiter, bool destroy_input, int* out_count) {
    
    int len = (int)jss_get_length(string);
    int i, count = 1, listIndex = 0, startPos = 0;
    const char* os = jss_c_string(string);
    
    // check occurance count
    for (i=0; i<len; i++) {
        if (os[i] == delimiter) count++;
    }
    
    // create list
    jsstring_t** list = (jsstring_t**)malloc(sizeof(jsstring_t*)*count);
    
    for (i=0; i<len; i++) {
        if (os[i] == delimiter) {
            int slen = i-startPos;
            if (slen <= 0) {
                list[listIndex] = jss_create(NULL);
            } else {
                list[listIndex] = jss_substr(string, startPos, slen, false);
            }
            
            startPos = i+1;
            listIndex++;
        }
    }
    
    // last item
    if (startPos < len) {
        list[listIndex] = jss_substr(string, startPos, len-startPos, false);
    } else if (startPos == len){
        list[listIndex] = jss_create(NULL);
    }
    *out_count = count;
    
    return list;
}

// returns character index where the first occurance of the string is
int jss_search(jsstring_t* string, jsstring_t* match, int start_index) {
    if (start_index>string->length-1) return -1;
    char* res = strstr(string->str+start_index, match->str);
    if (res)
        return (int)(res-string->str);
    return -1;
}

int jss_search_c_string(jsstring_t* string, const char* match, int start_index) {
    if (start_index>string->length-1) return -1;
    char* res = strstr(string->str+start_index, match);
    if (res)
        return (int)(res-string->str);
    return -1;
    
}

