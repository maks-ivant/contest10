#include<stdio.h>
#include<string.h>
#include<math.h>
#include<assert.h>

typedef struct {
    char name[256];
    int size;
    char message[256];
    int imessage;
    int messageCount;
}satellite;

static int jMessage = 0;
static satellite *currSat = NULL;

//Different states of FSM
typedef enum
{
 Idle_Read_Name,
 Read_Message,
 After_Quote,
 End_State,
}eSystemState;

int main (){
    FILE *fpIn,*fpOut;
    char fNameIn[] = "SPACE.DAT";
    char fNameOut[] = "MESS.DAT";
    char Message[256];
    char quotes[] = "ABBA";
    const int qlen = (int)strlen(quotes);
    satellite sp1,sp2;

    fpIn = fopen(fNameIn,"r");
    fpOut = fopen(fNameOut,"w");
    assert(fpIn);
    assert(fpOut);

    sp1 = (satellite){.imessage = 0, .messageCount = 0};
    fgets(sp1.name,256,fpIn);
    sp1.name[strcspn(sp1.name, "\r\n")] = 0;//remove /n or /r at the end of line
    sp1.size = (int)strlen(sp1.name);

    sp2 = (satellite){.imessage = 0, .messageCount = 0};
    fgets(sp2.name,256,fpIn);
    sp2.name[strcspn(sp2.name, "\r\n")] = 0;//remove /n or /r at the end of line
    sp2.size = (int)strlen(sp2.name);


    fgets(Message,256,fpIn);
    Message[strcspn(Message, "\n\r")] = 0;//remove /n or /r at the end of line

    eSystemState eNextState = Idle_Read_Name;


    while(1){
     switch(eNextState)
     {
     case Idle_Read_Name:
     {
         char buf[256];
         for(int i=0;i < (int)(fmin(sp1.size,sp2.size));i++){
             buf[i] = Message[i+jMessage];
         }
         jMessage = (int)(fmin(sp1.size,sp2.size)) + jMessage;
         if(0==strcmp(buf,sp1.name)){
             eNextState = Read_Message;
             currSat = &sp1;
         }
         if(0==strcmp(buf,sp2.name)){
             eNextState = Read_Message;
             currSat = &sp2;
         }
     }
     break;
     case Read_Message:
     {
         char *sat1InMessage, *sat2InMessage, *quoteInMessage;
         sat1InMessage = strstr(&Message[jMessage], &sp1.name);
         sat2InMessage = strstr(&Message[jMessage], &sp2.name);
         quoteInMessage = strstr(&Message[jMessage], &quotes);
         //printf("%p %p %p %d %d",sat1InMessage, sat2InMessage, quoteInMessage,sat2InMessage -quoteInMessage,sat1InMessage -quoteInMessage);
         if (((quoteInMessage < sat1InMessage)||(NULL==sat1InMessage))&&((quoteInMessage < sat2InMessage)||(NULL==sat2InMessage))&&(quoteInMessage!=NULL)){
             eNextState = After_Quote;
             strncpy(&currSat->message[currSat->imessage],&Message[jMessage],quoteInMessage - &Message[jMessage]);
             currSat->imessage+=(int)(quoteInMessage - &Message[jMessage]);
             jMessage +=(quoteInMessage - &Message[jMessage]+qlen);
             break;
         }
         if (((sat1InMessage< sat2InMessage)||(NULL==sat2InMessage))&&(sat1InMessage != NULL)){
             eNextState = Idle_Read_Name;
             strncpy(&currSat->message[currSat->imessage],&Message[jMessage],sat1InMessage - &Message[jMessage]);
             currSat->imessage+=(int)(sat1InMessage - &Message[jMessage]+1);
             currSat->message[currSat->imessage-1] ='\n';//messages delimiter \n
             jMessage += (int)(sat1InMessage - &Message[jMessage]);
             currSat->messageCount++;
             break;
         }
         if (((sat2InMessage< sat1InMessage)||(NULL==sat1InMessage))&&(sat2InMessage != NULL)){
             eNextState = Idle_Read_Name;
             strncpy(&currSat->message[currSat->imessage],&Message[jMessage],sat2InMessage - &Message[jMessage]);
             currSat->imessage+=(int)(sat2InMessage - &Message[jMessage]+1);
             currSat->message[currSat->imessage-1] ='\n';//messages delimiter \n
             jMessage += (int)(sat2InMessage - &Message[jMessage]);
             currSat->messageCount++;
             break;
         }
         if ((NULL==sat1InMessage)&&(NULL==sat2InMessage)&&(NULL==quoteInMessage)){
            eNextState = End_State;
            while(0!=Message[jMessage]){
                currSat->message[currSat->imessage] = Message[jMessage];
                currSat->imessage++;
                jMessage++;
            }
            currSat->message[currSat->imessage+1] = 0;
            currSat->messageCount++;
         }
         // all null and error
     }
     break;
     case After_Quote:
     {
         char *sat1InMessage, *sat2InMessage, *quoteInMessage;
         sat1InMessage = strstr(&Message[jMessage], &sp1.name);
         sat2InMessage = strstr(&Message[jMessage], &sp2.name);
         quoteInMessage = strstr(&Message[jMessage], &quotes);
         if (quoteInMessage==&Message[jMessage]){
             eNextState = Read_Message;
             strncpy(&currSat->message[currSat->imessage],&Message[jMessage], qlen);
             jMessage +=qlen;
             break;
         }
         if (sat1InMessage == &Message[jMessage]){
             eNextState = Read_Message;
             strncpy(&currSat->message[currSat->imessage],&Message[jMessage],sp1.size);
             currSat->imessage+= sp1.size;
             jMessage += sp1.size;
             break;
         }
         if (sat2InMessage == &Message[jMessage]){
             eNextState = Read_Message;
             strncpy(&currSat->message[currSat->imessage],&Message[jMessage],sp2.size);
             currSat->imessage+=sp2.size;
             jMessage += sp2.size;
             break;
         }
         if ((NULL==sat1InMessage)&&(NULL==sat2InMessage)&&(NULL==quoteInMessage)){
             if(Message[jMessage]==0){//allow quote terminating strings
                 eNextState = End_State;
                 strncpy(&currSat->message[currSat->imessage],&Message[jMessage-qlen],qlen);
                 currSat->imessage+=qlen;
                 currSat->message[currSat->imessage] ='\n';//messages delimiter \n
                 currSat->messageCount++;
             }else{
                 assert(0);//error unexpected string end
             }
         }

     }
     break;
     case End_State:{
         fprintf(fpOut,"%d\n",sp1.messageCount+sp2.messageCount);
         fprintf(fpOut,"SPUTNIK1\n%s",sp1.message);
         fprintf(fpOut,"SPUTNIK2\n%s",sp2.message);

         fclose(fpIn);
         fclose(fpOut);
         return 0;
    }
    }//end switch
    }//end of while(1)
}
