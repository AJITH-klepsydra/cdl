#include<stdio.h>

#include<stdbool.h>
#include "common.h"
bool X();
bool T();
bool E();
bool Y();
bool F();
char string[10];
int c_ptr;
bool X(){
	if(string[c_ptr]=='+'){
		c_ptr+=1;
		if(T())
			if(X())
				return true;
			return false;
	}
    else return true;
}


bool F(){
    if(string[c_ptr]=='('){
        c_ptr++;
        if(E()){
            if(string[c_ptr]==')'){
                c_ptr++;
                return true;
            }
        }
        return false;
    }
    else if(string[c_ptr]=='i'){
        c_ptr++;
        return true;
    } else return false;
}
bool Y(){
    if(string[c_ptr]=='*'){
        if(F()){
            if(Y()){
                return true;
            }

        }
        return false;
    }
    else return true;
}
bool T(){
    if(F())
        if(Y())
            return true;
    return false;


}
bool E(){
    if(T())
        if(X())
            return true;
    return false;
}
int main(){
    printf("# input string: ");
    scanf("%s",string);
	c_ptr=0;
	get_data3();
	printf("Result: %d\n",E());
    return 0;
		
}
