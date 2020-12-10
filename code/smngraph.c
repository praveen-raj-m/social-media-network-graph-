#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
int f=0,i;
int x=0,n,h=0;
struct friends//friends of the members in the network
{
    char fname[20];
    struct friends *side;//pointing next friend
}*tem,*nwf,*top1,*tem2;
struct members//members of the network
{
    char mname[20];
    int fr,q;//fr=no of friends for that member and q is for mutual check
    struct members *down;// pointing next member
    struct friends *right;// pointing friends of the member
}*top,*bottom,*nw,*temp,*temp2;
struct mutual//for friend suggestions
{
    char mfname[20];
    int c;// no of people suggesting a friend
    struct mutual *nxt;
}*topm=NULL,*bottomm=NULL,*tempm=NULL,*nwm;
void addmember()//for adding a new member
{
    temp=top;
    int p=1;//to check whether the member already exists
    char newname[20];
    printf(" Enter the name of the new member %d: ",f+1);
    scanf("%s",&newname);
    while(temp!=NULL)
    {
        if(strcmp(temp->mname,newname)==0)
        {
            p=0;
            break;
        }
        temp=temp->down;
    }
    if(p==1)
    {
    struct members*nw=(struct members*)malloc(sizeof(struct members));
    strcpy(nw->mname,newname);
    nw->down=NULL;
    nw->right=NULL;
    nw->fr=0;
    nw->q=0;//check variable for mutual friends
    if(top!=NULL)
    {
        bottom->down=nw;
        bottom=nw;
    }
    else
    {
        top=nw;
        bottom=nw;
    }
    f++;//total number of members in the network
    h=f;
    }
    else
        {
            printf("\nALREADY EXISTING MEMBER\n");
        h=h-1;
        i=i-1;//to repeat the iteration at initial stage;
        }
}
void addfriend()//for adding new friend
{
    int g=0,e=0;//g is used to check existence of member,e is used to check whether the already existing as a friend
    char nwname[20];
    printf("enter the name of the friend %d: ",x+1);
    scanf("%s",&nwname);
    temp2=top;
    while(temp2!=NULL)//checking whether member is existing
    {
        if(strcmp(temp2->mname,nwname)==0)
        {
            g=1;
            break;
        }
         temp2=temp2->down;
    }
    tem=temp->right;
    while(tem!=NULL)//checking whether already existing a friend
    {
        if(strcmp(tem->fname,nwname)==0)
        {e=1;
        x=x-1;//used while adding friend to a member newly created after the creation of network
         break;
    }
    tem=tem->side;
    }
    if(e==0)
    {
   if(g==1)
   {
    if(strcmp(nwname,temp->mname)!=0)
   {
       temp->fr=temp->fr+1;//incrementing friends of the member
    struct friends*nwf=(struct friends*)malloc(sizeof(struct friends));
    strcpy(nwf->fname,nwname);
    nwf->side=NULL;
    if(temp->right==NULL)
    {
        temp->right=nwf;
        top1=temp->right;
    }
    else
    {
        top1->side=nwf;
        top1=nwf;
    }

   }
   else
    {printf("\nOOPS you have entered the member itself\n");
      x=x-1;
    }
   }
   else
    {printf("\n****MEMBER NOT FOUND IN THE NETWORK****\n");
    x=x-1;
    }
    }
    else
        {
        printf("\nALREADY EXISTING AS A FRIEND\n");
        }

}
void addfriendnew()//for adding friends while creating new member
{
    int v,i;
    do{
     printf("\nEnter the number of friends of %s :",bottom->mname);
    scanf("%d",&v);
    if(v<f)//to make sure that friends do not exceed number of friends
    {temp=bottom;//so that friends are added to the previously created member
    for(x=0;x<v;x++)
    {
        addfriend();
    }break;}
    else
    {
        printf("\nNumber of friends are exceeding number of members left");
    }}while(v>=f);
}
void printnetwork()//to print the network
{
    int g;
   temp=top;
   printf("\n TOTAL NUMBER OF MEMBERS IN THIS NETWORK ARE %d",f);
   while(temp!=NULL)
   {
       printf("\n -> '%s' has %d friends",temp->mname,temp->fr);
       tem=temp->right;
       g=1;
       printf("\nFriends of '%s' are",temp->mname);
       while(tem!=NULL)
       {
           printf("\n\t%d. %s",g++,tem->fname);
           tem=tem->side;
       }
       temp=temp->down;
   }
}
void addmutual()//to add mutual friends
{
    int h=1;
   tempm=topm;
   while(tempm!=NULL)
   {
       if(strcmp(tempm->mfname,tem2->fname)==0)
       {
           h=0;//to make sure that suggestions are added only once if not number of them following are incremented
           break;
       }
       tempm=tempm->nxt;
   }

   if(h==1)
   {
   struct mutual*nwm=(struct mutual*)malloc(sizeof(struct mutual));
   strcpy(nwm->mfname,tem2->fname);
   nwm->c=1;
   nwm->nxt=NULL;
   if(topm==NULL)
   {
       topm=bottomm=nwm;
   }
   else
    {
        bottomm->nxt=nwm;
        bottomm=nwm;
    }
   }
   else
    {
     tempm->c=tempm->c+1;
    }
}
void printmutual()//printing mutual suggestions
{
    int b=0;
    char sname[20];
 temp=top;
 printf("\nEnter the person who's mutual to be found:");
 scanf("%s",&sname);
 tem=NULL;
 while(temp!=NULL)//to locate the member
 {
     if(strcmp(temp->mname,sname)==0)
     {
         tem=temp->right;
         b=1;
         break;
     }
     temp=temp->down;
 }
 if(b==1)//to check whether the member exists
 {
        while(tem!=NULL)//friends of the member
         {
             temp2=top;
             while(temp2!=NULL)
             {
                 if(strcmp(temp2->mname,tem->fname)==0)
                 {
                     tem2=temp2->right;
                     while(tem2!=NULL)//locating the suggestions
                     {
                         addmutual();//adding another node
                         tem2=tem2->side;
                 }
                 }
                 temp2=temp2->down;
             }
             tem=tem->side;
         }
tem=temp->right;
while(tem!=NULL)//to make sure that suggestions should not show the already existing friends
{
    tempm=topm;
while(tempm!=NULL)
{
if(strcmp(tempm->mfname,tem->fname)==0)
{
 tempm->c=-1;//check variables
 break;
}
tempm=tempm->nxt;
}

tem=tem->side;
}

 tempm=topm;
 temp->q=temp->q+1;//to make sure that there is no doubling of members following that suggestion
 printf("\nmutual friends of %s are:\n",sname);
 while(tempm!=NULL)
 {
     if(strcmp(sname,tempm->mfname)!=0 && tempm->c>0)//avoiding suggestions of their own name as well as
                                                    //already existing friends
    {
         if(temp->q>=2)//to ensure there is no doubling of members following the suggestion
     {printf("%s -followed by %d\n",tempm->mfname,tempm->c/2);}
     else
        {
        printf("%s -followed by %d\n",tempm->mfname,tempm->c);
        }}
     tempm=tempm->nxt;

 }
 }
 else
    printf("\nMEMBER DOES NOT EXIST");
}
void addfriendalone()//for adding friend alone
{
    int g=1;
    char nam[20];
    printf("\nEnter the name of the member for whom new friend should be added:");
    scanf("%s",&nam);
    temp=top;
     x=1;
    while(temp!=NULL)
    {
        if(strcmp(nam,temp->mname)==0)
        {
                 top1=temp->right;
                 g=0;//to make sure that the member is present
                 break;}
                  temp=temp->down;
                  }
     while(top1->side!=NULL)
     {
         top1=top1->side;
         x=x+1;//to find number of friends for that member
     }
     if(x+1<f-1)//to check whether the number of friends are not more than the number of members in the network
     {
     if(g==0)
        addfriend();}
        else
          printf("\n MEMBER HAS MAXIMUM NUMBER OF FRIENDS");
    if(g==1)
    {
        printf("\n***MEMBER NOT FOUND***\n");
    }
}
void deletefriend()//to delete a friend
{
    int g=0,h=0;//g is used to check whether the member exist
    char dname[20],dnam[20];
    printf("\nEnter the name from which you should delete:");
    scanf("%s",dname);
    temp=top;
    while(temp!=NULL)
    {
        if(strcmp(temp->mname,dname)==0)
        {tem=temp->right;
        if(temp->right==NULL)
        {
            printf("\n there are no friends for %s",temp->mname);
            h=1;// no friends exist
        }
        tem2=tem;
         g=1;// member found
          break;
        }
        temp=temp->down;
    }
    if(g==0)
        {printf("\n\t***MEMBER not found***");
        h=2;//member not found
        }
   if(g==1 && h==0)
   {
    printf("\nEnter the friend to be removed:");
    scanf("%s",&dnam);
    while(tem!=NULL)
  {

      if(tem->side!=NULL)
      {
       if(strcmp(tem->side->fname,dnam)==0)
       {
           tem2=tem2->side;
           tem->side=tem2->side;
           free(tem2);
           h=3;// friend deleted
           break;
       }
       else if(strcmp(tem->fname,dnam)==0 )
            {temp->right=tem->side;
            h=3;// friend deleted
            break;}
       tem=tem->side;
       tem2=tem2->side;
      }
      else
      {
           if(strcmp(tem->fname,dnam)==0)
          {temp->right=NULL;
          tem=NULL;
          h=3;
          break;}
          else
          {
            tem=tem->side;
            h=4;}//friend not found for that member
      }
   }
   }
   if(h==4)
    printf("\n %s is not a friend of %s",dnam,dname);
   if(g==1 && h==3)
    {printf("\nDELETED SUCCESSFULLY");
     temp->fr=temp->fr-1;}

}
void delay(int nosec)//to delay the time
{
       clock_t start_time = clock();//linking it with the clock of the system
    while (clock() < start_time + nosec);
}
int main()//main function
{
    int l=0,choice;
    top=NULL;
    top1=NULL;
    bottom=NULL;
    temp=NULL;
    temp2=NULL;
    printf("\n\t\t\t\t\t\t\t***LETS CREATE A NETWORK TO BEGIN*** \n\nEnter the number of members at the beginning of the network:");
    scanf("%d",&n);//number of friends
    for(i=0;i<n;i++)
    {
        addmember();
    }
    temp=top;
   while(temp!=NULL)
    {
        do
        {
    printf("\nEnter the number of friends of '%s'  (should be less than number of members in the network):",temp->mname);
    scanf("%d",&l);
    }while(l>=f);
    for(x=0;x<l;x++)
    {
        addfriend();
    }
    printf("\nFRIENDS ADDED FOR '%s' SUCCESSFULLY",temp->mname);
    temp=temp->down;
    }
    printf("\n\n*****NOW THE NETWORK HAS BEEN SUCCESSFULLY CREATED*****");
    do
    {
           delay(4000);//to delay 4 seconds
           system("cls");// to clear the output screen
            printf("\nNow select the action to be performed in this network :");
                printf("\n1. Add a member to the network\n2. Show friend suggestion for a member\n");
                printf("3. Add a friend to existing member\n4. Delete a friend of existing member\n5. Display the network\n6. Exit\nEnter your choice:");
      scanf("%d",&choice);
      switch (choice)
      {
      case 1:
        do
        {
        addmember();
        }while(h<f);//to make sure that the member is added
        printf("\nMEMBER ADDED SUCCESSFULLY IN THIS NETWORK");
        addfriendnew();
        printf("\n FRIENDS ADDED SUCCESSFULLY FOR THE NEW MEMBER");
        break;
      case 2:
        printmutual();
        break;
      case 3:
        addfriendalone();
        break;
      case 4:
          deletefriend();
        break;
      case 5:
          printnetwork();
        break;
      default:
        break;
       }}while(choice<=5);
       return 0;//end of the program
}
