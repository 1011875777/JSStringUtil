//
//  main.c
//  JSStringUtil
//
//  Created by Johan Sundhage on 2013-08-08.
//  Copyright (c) 2013 Johan Sundhage. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 


#include "JSStringUtil.h"
void doIt() {
    const char* origin = "Hello";
    
    jsstring_t* s = jss_create(origin);
    unsigned long len = jss_get_length(s);
    
    const char* copy = jss_copy(s, false);
    printf("res: %s copy: %s %p %p %p len: %li\n", jss_c_string(s), copy, origin, jss_c_string(s), copy,len);
    free((void*)copy);
    copy = NULL;
    
    jsstring_t* s2 = jss_create(" world!");
    jsstring_t* concat = jss_concat(s, s2, false);
    
    printf("Concat res: %s\n", jss_c_string(concat));
    
    jsstring_t* subs = jss_substr(concat, 2, 3, false);
    if (subs) {
        printf("Substring: %s\n", jss_c_string(subs));
        jss_destroy(subs);
    }
    int count, i;
    jsstring_t** list = jss_split(concat, ' ', false, &count);
    
    for (i = 0; i<count; i++) {
        printf("Split item: %s\n", jss_c_string(list[i]));
    }
    
    
    int si = jss_search_c_string(concat, "w", 0);
    printf("Match index: %i\n", si);

    jss_destroy_list(list, count);
    jss_destroy(s);
    jss_destroy(s2);
    jss_destroy(concat);
    
}
int main(int argc, const char * argv[])
{
    
    doIt();
    
    return 0;
}

