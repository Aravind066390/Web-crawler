#include<curl/curl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int mark(char *,char **,int );
char data[1024*1024*2];
char data2[1024][1024*4];
char point_link[100][100];
int ss=1,nk=0,jnj=0,too=0;
int cost=0,xval=0,meta_data;
CURL *curl;
size_t write_data(void *ptr,size_t a,size_t b,void *beta){
strncat((char *)beta,(char *)ptr,a*b);
return a*b;
}
char** init(char **argv,int argn){
int k=0;
char **s=(char **)malloc(argn);
for(int i=0;i<argn;i++){
s[i]=(char *)malloc(100);
}
for(int i=2;i<argn;i++){
if((strcmp(argv[i],"he"))&&(strcmp(argv[i],"she"))&&(strcmp(argv[i],"the"))&&(strcmp(argv[i],"a"))&&(strcmp(argv[i],"me"))&&(strcmp(argv[i],"my"))&&(strcmp(argv[i],"us"))&&(strcmp(argv[i],"kept"))&&(strcmp(argv[i],"and"))&&(strcmp(argv[i],"her"))){
strcpy(s[k],argv[i]);
k=k+1;
}
}
cost=k;
return s;
}
void clear_init(char **s,int n){
for(int i=0;i<n;i++){
free(s[i]);
}
free(s);
return;
}
int search_engine(char **argv,int argn,char *str){
int g=0,j=0,enda=0;
char *tst=data;
int validity=0;
for(int i=0;i<argn;i++){
tst=data;
while(*tst!='\0'){
if(strlen(argv[i])>strlen(tst)){
break ;
}
/**printf("%s-----%.4s\n\n",argv[i],tst);
sleep(1);*/
if(!strncmp("<h",tst,2)||!strncmp("<a",tst,2)||!strncmp("<p",tst,2)){
validity=1;
}
if(!strncmp("</h",tst,3)||!strncmp("</a",tst,3)||!strncmp("</p",tst,3)){
validity=0;
}
if(!strncmp(argv[i],tst,strlen(argv[i]))&&validity){
g++;
}
tst++;
}
}
if(xval==100){
xval=0;
too+=2;
meta_data=100;
}
if((g)>=(too+2)){
strcpy(point_link[xval++],str);
return 0;
}else{
return 1;
}
}
int main(int argno,char **argv){
curl_global_init(CURL_GLOBAL_DEFAULT);
char **s;
char urg_name[100];
if(fork()){
if(fork()){
strcpy(urg_name,"https://vtu.ac.in");
}else{
strcpy(urg_name,"https://www.youtube.com");
}
}else{
if(fork()){
strcpy(urg_name,"https://www.wikipedia.org");
}
else{
strcpy(urg_name,"https://data.gov");
}
}
mark(urg_name,s=init(argv,argno),cost);
clear_init(s,cost);
curl_easy_cleanup(curl);
curl_global_cleanup();
for(int i=0;i<100;i++){
if(strlen(point_link[i]))
printf("%s\n",point_link[i]);
}
return 0;
}
int find_val(char *s,char **ch,int no){
int i=0;
while(i<no){
char *t=s;
while(strlen(t)<strlen(ch[i])){
if(!strncmp(ch[i],t,strlen(ch[i]))){
return 0;
}
t+=1;
}
i++;
}
return 1;
}
void restructure_link(int sz,char **argv,int argno){
int k=0,top=ss-1,nf=0;
while(sz<ss){
k=find_val(data2[sz],argv,argno);
if(k){
char temp[1000];
strcpy(temp,data2[sz]);
strcpy(data2[sz],data2[top]);
strcpy(data2[top],temp);
if(top<(ss/2)){
return ;
}
top--;
nf=1;
}
sz++;
}
if(nf)
ss=ss-1;
return ;
}
int mark(char *s,char **ch,int sizes){
if(nk>=ss||nk>=20){
return 0;
}
curl=curl_easy_init();
curl_easy_setopt(curl,CURLOPT_USERAGENT,"mozzila1.0");
curl_easy_setopt(curl,CURLOPT_ACCEPT_ENCODING,"");
curl_easy_setopt(curl,CURLOPT_FOLLOWLOCATION,1L);
curl_easy_setopt(curl,CURLOPT_URL,s);
curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_data);
curl_easy_setopt(curl,CURLOPT_WRITEDATA,data);
curl_easy_perform(curl);
int kpush=strlen(data);
//printf("%s--%s  \n",data,s);
//printf("%s--%s  \n",data,s);
for(int i=0;i<kpush-4;i++){
if(data[i]=='h'){
if(data[i+1]=='t'){
if(data[i+2]=='t'){
if(data[i+3]=='p'){
data2[ss][0]='h';
data2[ss][1]='t';
data2[ss][2]='t';
data2[ss][3]='p';
if(data[i+4]!=':'  && i<kpush-5&&data[i+5]!='s'){
continue;
}
int k=4;
for(int j=i+4;data[j]!='\"'&&data[j]!='\''&&data[j]!=' ';j++){
if(data2[ss][k-1]==','){
k=k-1;
break;
}
if(k<=2048)
if(data[j]=='\\'||data[j]=='\''||data[j]=='<'||data[j]=='>'||data[j]==';'||data[j]=='}'){
continue;
}
else{
data2[ss][k++]=data[j];
}
}
data2[ss][k]='\0';
if(ss<1000){
ss=ss+1;
}else{
printf("\n\n\nended");
return 12;
}
}
}
}
}
jump:
}
nk++;
if(jnj<ss){
search_engine(ch,sizes,data2[jnj]);
restructure_link(jnj,ch,sizes);
strcpy(data,"null");
mark(data2[jnj++],ch,cost);
}
return 0;
}

/**
  * ================================================================
  *                       WEB CRAWLER(keyword-based search engine)
  *                       newexp.cpp
  * ================================================================
  *
  * Description:
  *     Experimental implementation of a web crawler and search
  *     engine written in C/C++.
  *
  *     The program is designed to fetch webpages, process their
  *     contents, extract links, search for user-provided keywords,
  *     and recursively discover relevant webpages.
  *
  * Main Features:
  *     - Webpage retrieval using libcurl
  *     - HTML content processing
  *     - URL / hyperlink extraction
  *     - Keyword-based page searching
  *     - Recursive crawling
  *     - Multiple crawling processes
  *     - Dynamic memory management
  *     - Experimental search-engine functionality
  *
  * File:
  *     newexp.cpp
  *
  * Project:
  *     Web-crawler
  *
  * Author:
  *     Aravind
  *
  * Repository:
  *     https://github.com/Aravind066390/Web-crawler
  *
  * Purpose:
  *     This file is intended for experimentation and development
  *     of new crawling, searching, URL-processing, and memory-
  *     management techniques.
  *
  * Note:
  *     This is an experimental project. The implementation may
  *     change as new algorithms and optimizations are tested.
  *
  * ================================================================
  */
