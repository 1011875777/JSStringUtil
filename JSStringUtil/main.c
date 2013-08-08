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
    
    JSString* s = JSSCreate(origin);
    unsigned long len = JSSGetLength(s);
    
    const char* copy = JSSCopy(s, false);
    printf("res: %s copy: %s %p %p %p len: %li\n", JSSCString(s), copy, origin, JSSCString(s), copy,len);
    free((void*)copy);
    copy = NULL;
    
    JSString* s2 = JSSCreate(" world!");
    JSString* concat = JSSConcat(s, s2, false);
    
    printf("Concat res: %s\n", JSSCString(concat));
    
    JSString* subs = JSSSubstr(concat, 2, 3, false);
    if (subs) {
        printf("Substring: %s\n", JSSCString(subs));
        JSSDestroy(subs);
    }
    int count, i;
    JSString** list = JSSSplit(concat, 'p', false, &count);
    
    for (i = 0; i<count; i++) {
        printf("Split item: %s\n", JSSCString(list[i]));
    }
    
    
    int si = JSSSearchCString(concat, "an", 16);
    printf("Match index: %i\n", si);

    JSSDestroyList(list, count);
    JSSDestroy(s);
    JSSDestroy(s2);
    JSSDestroy(concat);
    
}
int main(int argc, const char * argv[])
{
    
    doIt();
    
    return 0;
}

