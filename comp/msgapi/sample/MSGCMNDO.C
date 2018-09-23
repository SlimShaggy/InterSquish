#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "prog.h"
#include "msgapi.h"

#define VERSION "1.00"
#define MAX_NAMES 64

char name[MAX_NAMES][PATHLEN];

int main(int argc, char *argv[])
{
  MSG *mh;
  MSGH *msgh;
  FILE *fp;
  word n_names=0;
  word n_nuke=0;
  dword mn;
  
  printf("\nMSGCMNDO  Message Commando, Version " VERSION ".\n");
  printf("Copyright 1991 by Scott J. Dudley.  All rights reserved.\n\n");
  
  if (argc < 3)
  {
    printf("Usage:\n\n");
    
    printf("MSGCMNDO <config file> <area path>\n");
    return 1;
  }
  
  if ((fp=fopen(argv[1], "r"))==NULL)
  {
    printf("Error opening `%s'!\n", argv[1]);
    return 1;
  }
  
  while (fgets(name[n_names], PATHLEN, fp))
  {
    Strip_Trailing(name[n_names], '\n');

    if (*name[n_names])
      n_names++;
  }
  
  fclose(fp);

  strupr(argv[2]);
  
  if ((mh=MsgOpenArea(argv[2]+(*argv[2]=='$'), MSGAREA_NORMAL,
                      *argv[2]=='$' ? MSGTYPE_SQUISH : MSGTYPE_SDM))==NULL)
  {
    printf("Can't open message area `%s'!\n", argv[2]);
    return 1;
  }

  printf("Scanning %s:\n", argv[2]+(*argv[2]=='$'));
  
  MsgLock(mh);
  
  for (mn=1; mn <= MsgGetHighMsg(mh); mn++)
  {
    char *txt;
    XMSG msg;
    UMSGID uid;
    word i;
    word reloop;
    
    reloop=FALSE;

    printf("%ld\r", mn);
    
    if ((msgh=MsgOpenMsg(mh, MOPEN_READ, mn))==NULL)
      continue;
    
    if ((txt=malloc(MsgGetTextLen(msgh))) != NULL)
    {
      MsgReadMsg(msgh, &msg, 0L, MsgGetTextLen(msgh), txt, 0L, NULL);
      
      for (i=0; i < n_names; i++)
      {
        if (stristr(txt, name[i]) ||
            stristr(msg.from, name[i]) ||
            stristr(msg.to, name[i]) ||
            stristr(msg.subj, name[i]))
        {
          uid=MsgMsgnToUid(mh, mn);
          
          MsgCloseMsg(msgh);
          MsgKillMsg(mh, mn);
          
          printf("Found `%s':  nuked %s#%ld\n", name[i], argv[2], mn);
          n_nuke++;

          mn=MsgUidToMsgn(mh, uid, UID_PREV);
          reloop=TRUE;
          
          break;
        }
      }

      free(txt);
      
      if (reloop)
        continue;
    }
    
    MsgCloseMsg(msgh);
  }
  
  MsgCloseArea(mh);

  printf("\rDone!  %d messages nuked.\n", n_nuke);
  
  return 0;
}
