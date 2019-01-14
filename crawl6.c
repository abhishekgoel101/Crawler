//gcc crawl2.c -o crawl
//./crawl https://www.chitkara.edu.in ~/crawler 2

//for dev cpp https://www.chitkara.edu.in C:\Users\Abhi\Desktop\crawler\crawldata 2

//check for .html and .htm pages only in url extractor

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<time.h>
#include<ctype.h>

#define HASH_SIZE 100
#define MAX_DEPTH 3
#define URL_LENGTH 1000

#define SEED_URL "https://www.chitkara.edu.in"

#define MAX_URL_PER_PAGE 200

#define INTERVAL_TIME 10      //time in ms

#define CHECK_MALLOC(s) if ((s) == NULL) { \
printf("memory allocation failed in %s: line%d", _FILE, __LINE_); \
perror(":"); \
exit(0); \
}

#define SET_MEM(start,size) memset(start,0,size)

struct url{
	char* link;
	int depth;
	int key;
}url;

struct node{

struct url url;
int isVisited;
struct node* next;
	
};

struct hash{

struct node* head;
struct node* tail;
struct node* visited;
int count;	

};



int file_no=1;

void delay(int s)
{
	int ms=s;
	clock_t stime=clock();
	while(clock()<stime+ms)
	{if(kbhit())
	break;
	}

}


/*
char* tag = "href";

char to_lower(char c) {
    return c > 92 ? c : c + 32;
}

char is_whitespace(char c) {
    return c == '\t' || c == '\n' || c == ' ';
}

int url_extract(char *str, int n, char **p) 
{
    char *t = *p, *c = tag;
    char quote;
    int i=0;
    while(*t != '\0') {
        while(*t && *c && to_lower(*t) == *c) {
            t++;
            c++;
        }

        if(*c == '\0') {
            i = 0;
            while(*t != '\0' && is_whitespace(*t))
                t++;
            if(*t++ == '=') {
                while(*t != '\0' && is_whitespace(*t))
                    t++;
                if(*t == '\'' || *t == '\"') {
                    quote = *t++;

                    while(*t != '\0' && is_whitespace(*t))
                        t++;

                    while(*t != '\0' && *t != quote )
                    {
                        //to handle for whitespace in the url
                        if(is_whitespace(*t))
                        {   t++;
                            continue;
                        }
                        if(i>=n-1)
                        {   i=n;
                            break;
                        }

                        str[i++] = *t++;

                    }
                    if(i==n)
                    {   str[n-1] = '\0';
                    }
                    else
                    {
                        str[i] = '\0';
                    }


                }
            }
            if(i != 0) break;
        }
        c = tag;
        t++;
    }

    *p = t;
    return i;
}

*/
/*
int hrefFile(char* file,char* href[],int count)
{
	printf("\nExtracting URL Links from page....\n");
	
    int i=count;
    char url[URL_LENGTH];
    char *t = file;
    int a;
    while(i<MAX_URL_PER_PAGE)
    {

        a=url_extract(url,URL_LENGTH, &t);
        if(a==0)
        {
            break;
        }
        
        if(checkSubUrl(url,a))
        {

//checks for duplicates
            int f=0;
            int j;
            for( j=0; j<i; j++)
            {
                if(strcmp(url,href[j])==0)
                {   f=1;
                    break;
                }

            }
            if(f==0)
            {
                char *link=(char*)malloc(a+1);
                if(link!=NULL)
				{
				strcpy(link,url);
                href[i++]=link;
				}
				else{
					printf("Malloc for char array for URL failed\n");
					exit(0);
				}
            }

        }


    }

    return i;
}
*/




int testDir(char *dir)
{
 	printf("\nChecking Valid Directory Path....\n");
    struct stat statbuf;
    if ( stat(dir, &statbuf) == -1 )
    {
        fprintf(stderr, "-----------------\n");
        fprintf(stderr, "Invalid directory\n");
        fprintf(stderr, "-----------------\n");
        exit(1);
    }

    //Both check if there's a directory and if it's writable
    if ( !S_ISDIR(statbuf.st_mode) )
    {
        fprintf(stderr, "-----------------------------------------------------\n");
        fprintf(stderr, "Invalid directory entry. Your input isn't a directory\n");
        fprintf(stderr, "-----------------------------------------------------\n");
        exit(0);
    }

    if ( (statbuf.st_mode & S_IWUSR) != S_IWUSR )
    {
        fprintf(stderr, "------------------------------------------\n");
        fprintf(stderr, "Invalid directory entry. It isn't writable\n");
        fprintf(stderr, "------------------------------------------\n");
        exit(0);
    }
    return 1;
}

int checkSubUrl(char *url,int l)
{
    char s1[URL_LENGTH]="";
    
    int i;

//for url less than max length
    if(l>=URL_LENGTH)
    {
        return 0;
    }
	    strcpy(s1,SEED_URL);
//to check start from seed url
    for(i=0; s1[i]!='\0'; i++)
    {
        if(url[i]==s1[i])
        {
            continue;
        }
        else
        {
            break;
        }

    }

    if(s1[i]!='\0')
    {   return 0;
    }
    return 1;

}

int validUrl(char *url)
{
	printf("\nChecking Main URL...\n");
	
    char s1[1000]="";
    strcat(s1,SEED_URL);
    int l1,l2,i;
    l1=strlen(s1);
    l2=strlen(url);

    if(l2>=URL_LENGTH)
    {
        printf("Length of URL should be less than %d\n",URL_LENGTH);
        exit(0);

    }

    if(l1>l2)
    {
        printf("URL should start with %s\n",SEED_URL);
        exit(0);
    }

    int f=0;
    for(i=0; i<l1; i++)
    {
        if(url[i]==s1[i])
        {
            continue;
        }
        else
        {   f=1;
            break;
        }

    }
    if(f==1)
    {
        printf("URL should start with %s\n",SEED_URL);
        exit(0);

    }

    char s2[2000]="wget --no-check-certificate --spider ";
    strcat(s2,url);

    if(!system(s2))
    {   printf("Valid URL on internet\n");
        return 1;
    }
    else
    {
        printf("Invalid URL on internet\n");
        exit(0);
        return 0;
    }

}

int validDepth(int d)
{
	printf("\nChecking valid main depth...\n");
    if(d<=0)
    {   printf("Enter non zero positive depth\n");
        exit(0);
    }
    if(d>MAX_DEPTH)
    {   printf("Enter depth less than equl to %d\n",MAX_DEPTH);
        exit(0);
    }
    return 1;
}

int getPage(char *url,char *dir)
{
	printf("\nGetting page data in temporary storage....\n");
    char tpath[200]="";
    strcat(tpath,dir);
    strcat(tpath,"/temp.txt");
    FILE *fp=fopen(tpath,"w");
    if(fp!=NULL)
    {
        fclose(fp);

        char urlbuffer[URL_LENGTH+300]= {0};
        strcat(urlbuffer, "wget --no-check-certificate -O ");

        strcat(urlbuffer,dir);

        strcat(urlbuffer,"/temp.txt ");

        strcat(urlbuffer, url);

        system(urlbuffer);
        printf("Temp PATH has been created\n");
        return 1;
    }
    printf("Page could not be copied to temporary storage\n");
    exit(0);
    return 0;
}


int makeFile(char *url,char *dir,int depth,char** mainFile)
{
 	printf("\nCopying Page in storage folder and Loading page in Main Memory....\n");
    char path[1000]="";
    char fno[10]="";
    char tpath[1000]="";
    char file[]="/file"; //name of file.
    char ext[]=".txt";
    sprintf(fno,"%d",file_no);
    file_no++;
    strcat(path,dir); //creating path using strcat in p.
    strcat(path,file);
    strcat(path,fno);
    strcat(path,ext);

    strcat(tpath,dir);
    strcat(tpath,"/temp.txt");

    FILE *fp=fopen(path,"w");

    if(fp!=NULL)
    {
        printf("File Path created for %s\n",path);

        fprintf(fp,"%s\n%d\n",url,depth);


        FILE *fp1=fopen(tpath,"r");

        if(fp1!=NULL)
        {
 			struct stat st;
		    stat(tpath,&st);
		    int file_size=st.st_size;
		    char *file=(char*)malloc(file_size+1);
		
		//CHECK_MALLOC(file);
		    if(file==NULL)
		    {   printf("Memory allocation failed in moving temp file to memory\n");
		        exit(0);
		    }
		    int i=0;

            char ch;
            ch=fgetc(fp1);
            while(ch!=EOF)
            {
       	        file[i++]=ch;
                fputc(ch,fp);
                ch=fgetc(fp1);
            }
			
			file[i]='\0';
			*mainFile=file;
			  
            fclose(fp1);
            fclose(fp);

            printf("Data copied Successfully\n");

            return 1;
        }
        fclose(fp);
    }


    printf("Unsuccessful copying of data\n");
    exit(0);
    return 0;
}


int url_extractor(char *str,int i,char* anchor,int n,int *s)
{
	int flag=0,j=0,m=0;
	strcpy(anchor,"");
	*s=0;
	
	static char adef1[]="<a";
	static char adef2[]="href=\"";

	char temp;
	
	while(str[i]!='\0')
	{
	if(isspace(str[i]))
	{}
	else
	 {
	 	temp=tolower(str[i]);
		
		if(flag==0 && temp==adef1[j])
         {
         	j++;

         	if(adef1[j]=='\0')
         	flag=1;
         }
         else
         j=0;
         
         if(flag==1 && temp=='>')
         {
         	flag=0;
         	j=0;
		 }
		 
         if(flag==1 && adef2[m]==temp)
        {
		  m++;
         	if(adef2[m]=='\0')
         	{
         		int k=0;
         		i++;
         		while(str[i]!='\0' && isspace(str[i]))
         		i++;
         		if(str[i]=='\0')
         		return -1;
         		while(str[i]!='\0' && str[i]!='\"' && !isspace(str[i]))
         		{
				if(k>=n-1)
				{
				k=n;	
				}
				else
				{
				anchor[k++]=str[i];	
				}
				
         		i++;
				}
				
         		if(str[i]=='\0')
         		return -1;
         		
         		if(k==n)
         		{
         		anchor[k-1]='\0';	
				 }
				 else
				 {
				 	anchor[k]='\0';
				 	if(k>0 && anchor[k-1]=='/')
				 	{
				 		k--;
				 	anchor[k]='\0';	
					 }
				 }
				*s=k;
				m=0;
				j=0;
				flag=0;
				
				return i+1;		
				
				
			}
		 }
		 else
		 m=0;
	 }
	 i++;
	}
	return -1;	
}


int hrefFile(char* file,char* href[],int count)
{
	printf("\nExtracting URL Links from page....\n");
	
    int i=count;
    char url[URL_LENGTH];

    int a,pos=0;
    while(i<MAX_URL_PER_PAGE)
    {
		pos=url_extractor(file,pos,url,URL_LENGTH,&a);
        
        if(pos==-1)
        {
            break;
        }
        
        if(checkSubUrl(url,a))
        {

//checks for duplicates
            int f=0;
            int j;
            for( j=0; j<i; j++)
            {
                if(strcmp(url,href[j])==0)
                {   f=1;
                    break;
                }

            }
            if(f==0)
            {
                char *link=(char*)malloc(a+1);
                if(link!=NULL)
				{
				strcpy(link,url);
                href[i++]=link;
				}
				else{
					printf("Malloc for char array for URL failed\n");
					exit(0);
				}
            }

        }


    }

    return i;
}


void printHrefFile(char* href[],int count)
{
    int i;
    printf("All a tags of this file......\n");
    for(i=0; i<count; i++)
    {   printf("%d %s\n",i,href[i]);
    }
    printf("\n");
}


int indexH(char* a)
{
	int i,s=0;
	for(i=0;a[i]!='\0';i++)
	{
		s+=a[i];
	}
	s=s%HASH_SIZE;
	return s;
}

struct node* insertHL(char* link,int d,struct hash h[],struct node* Mhead,struct node** Mtail,int max_d)
{
	//creating node of linked list and initializing it.
	
	struct node* temp=(struct node*)malloc(sizeof(struct node));
	if(temp==NULL)
	{printf("Malloc for node of linked list failed\n");
	exit(0);
	}
	temp->url.link=link;
	temp->url.depth=d;
	temp->url.key=indexH(link);
	if(d<=max_d)
	{
	temp->isVisited=0;	
	}
	else
	{temp->isVisited=1;	
	}
	temp->next=NULL;
	int p=temp->url.key;
	

	if(h[p].head==NULL)
	{
		//insert at begining of hash index and end of linked list
	h[p].head=temp;
	h[p].tail=temp;
	h[p].count=1;
	temp->next=NULL;
	
	if(Mhead==NULL)
	{
		Mhead=temp;
		*Mtail=temp;
	}
	else
	{
		(*Mtail)->next=temp;
		*Mtail=temp;
		}	
		
	}
	else
	{
	//insert at end of hash index and in middle of linked list(at the end of a cluster)	
	struct node* ptr=h[p].tail->next;	
	
	h[p].tail->next=temp;
	h[p].tail=temp;
	temp->next=ptr;
	h[p].count++;
	
	if(temp->next==NULL)
	{	
	(*Mtail)->next=temp;
	*Mtail=temp;
	}
		
	}
	return Mhead;
}

struct node* loadHL(char* link,int d,struct hash h[],struct node* Mhead,struct node** Mtail,int key,int isVisited)
{
	//creating node of linked list and initializing it.
	
	struct node* temp=(struct node*)malloc(sizeof(struct node));
	if(temp==NULL)
	{printf("Malloc for node of linked list failed in loading Crawler\n");
	exit(0);
	}
	temp->url.link=link;
	temp->url.depth=d;
	temp->url.key=key;
	temp->isVisited=isVisited;	
	
	temp->next=NULL;
	int p=temp->url.key;
	

	if(h[p].head==NULL)
	{
		//insert at begining of hash index and end of linked list
	h[p].head=temp;
	h[p].tail=temp;
	h[p].count=1;
	temp->next=NULL;
	
	if(Mhead==NULL)
	{
		Mhead=temp;
		*Mtail=temp;
	}
	else
	{
		(*Mtail)->next=temp;
		*Mtail=temp;
		}	
		
	}
	else
	{
	//insert at end of hash index and in middle of linked list(at the end of a cluster)	
	struct node* ptr=h[p].tail->next;	
	
	h[p].tail->next=temp;
	h[p].tail=temp;
	temp->next=ptr;
	h[p].count++;
	
	if(temp->next==NULL)
	{	
	(*Mtail)->next=temp;
	*Mtail=temp;
	}
		
	}
	return Mhead;
}


void printH(struct hash h[])
{
	int i;
	printf("Hash for all URL's is:\n");
	for(i=0;i<HASH_SIZE;i++)
	{
		printf("Index:%d Count:%d Hash is\n",i,h[i].count);
	if(h[i].head==NULL)
	{
		printf("Hash is empty\n");
	}	
	else
	{
	struct node* ptr1=h[i].head;
	struct node* ptr2=h[i].tail->next;
	int j=1;
	while(ptr1!=ptr2)
	{
		printf("No.%d  URL-%s   key-%d   depth-%d isVisited=%d     ",j,ptr1->url.link,ptr1->url.key,ptr1->url.depth,ptr1->isVisited);
		ptr1=ptr1->next;
		j++;
	}
	printf("\n");	
	}	
	
	}
	printf("---------------------------------------------------\n");	
}

void printL(struct node* Mhead)
{
	struct node* ptr1=Mhead;
	printf("Linked List is-------\n");
	if(Mhead==NULL)
	{
		printf("Linked list is empty\n");
	}
	else
	{int j=1;
		while(ptr1!=NULL)
		{
		printf("No.%d  URL-%s   key-%d   depth-%d isVisited=%d\n",j,ptr1->url.link,ptr1->url.key,ptr1->url.depth,ptr1->isVisited);
		ptr1=ptr1->next;
		j++;
		}		
	}
	
	printf("----------------------------------------------------\n");
}


int startCrawler()
{
	FILE *fp;
	int i=1,n;
	fp=fopen("crawlA.txt","r");
	printf("Web Crawler\n");
	printf("%d. New Crawler\n",i);
	i++;
	if(fp!=NULL)
	{printf("%d. Load Crawler\n",i);
	i++;
	}
	printf("%d. Exit Crawler\n",i);
	printf("Enter your choice ");
	scanf("%d",&n);
	if(fp==NULL && n>1)
	{n++;}
	
	while(n!=1 && n!=2 && n!=3)
	{
		printf("Enter valid choice ");
		scanf("%d",&n);
		if(fp==NULL && n>1)
		{n++;}
	
	}
	fclose(fp);
	system("cls");
	return n;
}

void saveCrawler(char* mainURL,char* dir,int depth,struct node* Mhead)
{
	//system("cls");
	char choice;
	
	printf("\nDo you wish to save the crawling (y/n)\n");
	
	scanf(" %c",&choice);
	while((getchar())!='\n');
	
	if(choice=='y')
	{
	printf("\nSaving Crawling Data....\n");
		
	FILE *fp;	
	fp=fopen("crawlA.txt","w");	
	if(fp!=NULL)	
	{
	fprintf(fp,"%s %s %d %d\n",mainURL,dir,depth,file_no);	
	
	struct node* ptr=Mhead;
	while(ptr!=NULL)
	{
	fprintf(fp,"%s %d %d %d\n",ptr->url.link,ptr->url.depth,ptr->url.key,ptr->isVisited);
	ptr=ptr->next;	
	}
	
	fclose(fp);
	printf("Crawl data saved\n");		
	}	
				
	}
	printf("Crawler Exited\n");
		exit(0);
	
	
}

int loadCrawler(struct node** Mhead,struct node** Mtail,struct hash h[],char* url,char* dir,int* depth)
{
	FILE *fp;
	fp=fopen("crawlA.txt","r");
	
	if(fp!=NULL)
	{
	printf("\nLoading Crawler....\n");
		
	fscanf(fp,"%s %s %d %d\n",url,dir,depth,&file_no);

    if( validUrl(url) && testDir(dir) && validDepth(*depth))
    {    
	int i;
	*Mhead=NULL;
	*Mtail=NULL;
	
	for(i=0;i<HASH_SIZE;i++)
	{
		h[i].head=NULL;
		h[i].tail=NULL;
		h[i].visited=NULL;
		h[i].count=0;
	}

	char* link,tempLink[URL_LENGTH];
	int cur_depth,key,isVisited,size;
	
	while(!feof(fp))
	{
	fscanf(fp,"%s %d %d %d\n",tempLink,&cur_depth,&key,&isVisited);
	size=strlen(tempLink);
	
	link=(char* )malloc(size+1);
	
	if(link==NULL)
	{
		printf("Malloc for char array for URL Link failed while loading\n");
		exit(0);
				
	}
	
	strcpy(link,tempLink);

	*Mhead=loadHL(link,cur_depth,h,*Mhead,Mtail,key,isVisited);
	
	}
	
	
	printf("Crawler Loaded Sucessfully\n");
	return 1;

	}
		
	}

	printf("Crawler could not be loaded successfully\n");	
	exit(0);
	return 0;	
	

}

int newStart(struct node** Mhead,struct node** Mtail,struct hash h[],char* url,char* dir,int* depth,int argc,char* argv[])
{
	int i,start_depth=1;
	*Mhead=NULL;
	*Mtail=NULL;

    if(argc!=4) {
        printf("Provide valid arguments\n");
        exit(0);
    }

	printf("\nStarting New Crawler....\n");
		
	for(i=0;i<HASH_SIZE;i++)
	{
		h[i].head=NULL;
		h[i].tail=NULL;
		h[i].visited=NULL;
		h[i].count=0;
	}
    
	strcpy(url,argv[1]);
    strcpy(dir,argv[2]);
    sscanf(argv[3],"%d",depth);
	

    if( validUrl(url) && testDir(dir) && validDepth(*depth))
    {   
    
	*Mhead=insertHL(url,start_depth,h,*Mhead,Mtail,*depth);
	printf("\nNew Crawler Started Sucessfully\n");
	return 1;
	}
	else
	{return 0;
	}
		
}

int main(int argc,char* argv[])
{
	struct hash	h[HASH_SIZE];
	struct node* Mhead=NULL,*Mtail=NULL;
	int i,c,success;
	char url[URL_LENGTH]="";
    char dir[100]="";
    int depth=0;
	
	
	c=startCrawler();
	if(c==1)
	{
	success=newStart(&Mhead,&Mtail,h,url,dir,&depth,argc,argv);
	
	}
	else if(c==2)
	{
	success=loadCrawler(&Mhead,&Mtail,h,url,dir,&depth);
	}
	else
	{
	printf("\nCrawler Exited\n");	
	exit(0);
	}
	
		
	char* href[MAX_URL_PER_PAGE]= {0};
    int href_count=0;
	
    if( success)
    {   
		printf("\nContinuing Crawling Process....\n\n");				
	//int flag=0;
	
	while(1)
	{	
		href_count=0;
		struct node *ptr=Mhead;	
		while(ptr!=NULL)	
		{
		if(ptr->isVisited==0)
		{break;
		}
		ptr=ptr->next;	
		}	
		if(ptr==NULL)
		{	break;	}	
		
		getPage(ptr->url.link,dir);
		
		char *file=NULL;
        makeFile(ptr->url.link,dir,ptr->url.depth,&file);
		
        href_count=hrefFile(file,href,href_count);
		free(file);
		/*
		if(flag==0)
		{
		flag=1;
		printHrefFile(href,href_count);	
		}
		*/
		for(i=0;i<href_count;i++)
		{
		int p=indexH(href[i]);
		int f=0;	
		if(h[p].head!=NULL)
		{
		struct node* ptr1=h[p].head;
		struct node* ptr2=h[p].tail->next;	
		while(ptr1!=ptr2)
		{
		if(strcmp(href[i],ptr1->url.link)==0)
		{f=1;
		break;
		}
		ptr1=ptr1->next;	
		}
		
		}
		if(f==0)
		{
		Mhead=insertHL(href[i],ptr->url.depth+1,h,Mhead,&Mtail,depth);	
		}
		else
		{
		free(href[i]);
		href[i]=NULL;	
		}
		
		}
		
		ptr->isVisited=1;
		
		printf("\n\n\n\n");
		
        //printHrefFile(href,href_count);
	
		delay(INTERVAL_TIME);
		
		if(kbhit())
		{
		  	char c=	getch();
		  	if(c==27)
		  	{	
		  	
			printH(h);
			printL(Mhead);
		  	saveCrawler(url,dir,depth,Mhead);
			break;
			}
		}
		
	}
	printH(h);
	printL(Mhead);
	
	saveCrawler(url,dir,depth,Mhead);	
	
  }
    return 0;

}
//set isvisted after visting each node 1.
//visted in each hash index in staring is NULL
