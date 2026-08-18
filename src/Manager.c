#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
char *free_head_module=NULL;
int state=0,depth_value=1;
long long int split(char *query){
long long int i=0,count=1;
while(query[i]!='\0'){
if(query[i]==' '){
count+=1;
while(query[i]==' '){
printf("%c",query[i]);
i++;
if(query[i]=='\0')return count-1;
}
}else{
i++;
}
}
return count;
}
char *wrap(long long int value){
if(value<0){
perror("Long Long Integer Overflow error please try to break your queries into parts or provide a smaller input\nExiting..");
exit(1);
}
if(0==state){
free_head_module=(char *)malloc(sizeof(char )*55);
if(free_head_module==NULL){
perror("Failed to Allocate Memory By Malloc.\nExiting\n");
exit(1);
}
state=1;
}
free_head_module[0]='\0';
sprintf(free_head_module,"%lld",value);
return free_head_module;
}
int main(){
char query[1024],query2[(1024*3)];
state=0;
depth_value=20;
while(1){
printf("\nenter>");
scanf("%1023[^\n]",query);
if(!strcmp(query,"exit")){
printf("Exiting..\n");
free(free_head_module);
break;
}else if(!strcmp(query,"Depth")){
scanf("%d",&depth_value);
if(depth_value<1){
depth_value=1;
perror("Error occured please enter a depth value of above or equal to one.");
return 1;
}
}else if(!strcmp(query,"help")){
printf("1.use exit to exit.\n"
"2. use Depth to enter search depth.\n\t"
"Depth Means how Accurately and deeply does the code search\n\tfor the given code.\n"
"3.just use ctrl+c to exit forcefully."
);
}else{
strcpy(query2,"./new ");
strcat(query2,wrap(depth_value));
strcat(query2," ");
strcat(query2,query);
printf("%s",query2);
system(query2);
}
}
return 0;
}
