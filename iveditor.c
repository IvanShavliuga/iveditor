#include "iveditor.h"
//Модуль iveditor.c
void stricpy(char source[], char priem[],int index, int len)
{           //    источник       приемник    нач. поз   длина
   register int i;  //индексная переменная
   for(i=0; i<len; i++)   //посимвольное копирование
       priem[i]=source[index+i];
   priem[len]=0;  //конец строки
}
void SpaceToTab(void)
{
   register int p, x, y; //страница колонка строка
   register unsigned int long part;
   int e=(CountPages<MAXPAGECOUNT)?(CountPages):(MAXPAGECOUNT);
   char i;               //индексная переменная
   char tmp[80];
   HintView(PLEASEWAIT);
   for(part=0; part<=CountPart; part++)
   {
     if(CountPart>0)
     {
       sprintf(tmp,"c:\\iveditor\\part_%d.txt",part);
       LoadFile(tmp);
     }
     for(p=0; p<=e;p++)
     {
      for(y=0; y<22; y++)
      {
         for(x=0; x<80; x++)
         {
            if(!Text[p][y][x]) break;
            i=0; //считаем сколько пробелов
            while(Text[p][y][x+i]==' ')
            {
              i++;
              if(i==TabSize)
              {
                //удаляем
                chrndel(Text[p][y],x,TabSize);
                //всталяем символ табуляции
                chrins(Text[p][y],x,'\t');
                break;
              }//if
            }//while
          }//for x
       } //for y
      }//for p
     if(CountPart>0)
     {
       sprintf(tmp,"c:\\iveditor\\part_%d.txt",part);
       SaveFile(tmp);
     }//if
   }//for part
   if(CountPart>0)
   {
     sprintf(tmp,"c:\\iveditor\\part_%d.txt",Part);
     LoadFile(tmp);
   } 
   gotoxy(1,25);
   clreol();
}
void TabToSpace(void)
{
   register int p, x, y; //страница колонка строка
   register unsigned int part;
   int e=(CountPages<MAXPAGECOUNT)?(CountPages):(MAXPAGECOUNT);
   char i;               //индексная переменная
   char tmp[80];
   HintView(PLEASEWAIT);
   for(part=0; part<=CountPart; part++)
   {
     if(CountPart>0)
     {
       sprintf(tmp,"c:\\iveditor\\part_%d.txt",part);
       LoadFile(tmp);
     }
     for(p=0; p<=e;p++)
     {
     for(y=0; y<22; y++)
     {
       for(x=0; x<80; x++)
       {
           if(Text[p][y][x]=='\t')
           {
           	   //удаляем символ табуляции	 
               chrdel(Text[p][y],x); 
               //вставляем пробелы
               for(i=0; i<TabSize; i++)
                  chrins(Text[p][y],x,' ');
           }
       }
     }
     }
     if(CountPart>0)
     {
       sprintf(tmp,"c:\\iveditor\\part_%d.txt",part);
       SaveFile(tmp);
     }
     
   }
   if(CountPart>0)
   {
     sprintf(tmp,"c:\\iveditor\\part_%d.txt",Part);
     LoadFile(tmp);
   }
   gotoxy(1,25);
   clreol();
}
void chrdel(char str[], int index)
{           //   строка     позиция  
  register unsigned int i; //индексная переменная
  if(index>strlen(str)) return;
  for(i=index+1; i<strlen(str); i++)
    str[i-1]=str[i]; //смецаем все символы влево
  str[strlen(str)-1]=0; //конец строки
}
void chrndel(char str[], int a,int n)
{            //   строка   поз. кол-во  
  register int i;
  for(i=0; i<n; i++)
    chrdel(str,a);
}
void chrins(char str[], int a,int c)
{           // строка   поз.  символ   
  register int i;
  int n=strlen(str);
  for(i=n; i>a; i--)
    str[i]=str[i-1];
  str[a]=c;
  str[n+1]=0;
}
void strins(char source[],int a,char word[])
{				//куда    индекс что  
  register unsigned int i;
  for(i=0; i<strlen(word);i++)
    chrins(source,a+i,word[i]);

}
void DosToWin(void)
{
   register int p, x, y; //страница колонка строка
   unsigned long int part;
   int e=(CountPages<MAXPAGECOUNT)?(CountPages):(MAXPAGECOUNT);
   char i;               //индексная переменная
   char tmp[80];
   HintView(PLEASEWAIT);
   for(part=0; part<=CountPart; part++)
   {
     if(CountPart>0)
     {
       sprintf(tmp,"c:\\iveditor\\part_%d.txt",part);
       LoadFile(tmp);
     }
     for(p=0; p<=e;p++)
     {
	  for(y=0; y<22; y++)
	  {
		for(x=0; x<80; x++)
		{
          switch(Text[p][y][x])
		  {//символы псевдографики
		    case 0xb0:
		    case 0xb1:
		    case 0xb2:
		    case 0xc5:
		    case 0xce:
		    case 0xd7:
		    case 0xd8:
		    case 0xb7:
		    case 0xb8:
		    case 0xbb:
		    case 0xbc:
		    case 0xbd:
		    case 0xbe:
		    case 0xbf:
		    case 0xc0:
		    case 0xc8:
		    case 0xc9:
		    case 0xd3:
		    case 0xd4:
		    case 0xd5:
		    case 0xd6:
            case 0xdb:
            case 0xdc:
            case 0xdd:
            case 0xde:
            case 0xdf:
		      Text[p][y][x]='*';
		      break;
		    case 0xb3:
            case 0xb4:
            case 0xb5:
            case 0xb6:
            case 0xb9:
            case 0xba:
            case 0xc3:
            case 0xc6:
            case 0xc7:
            case 0xcc:
              Text[p][y][y]='|';
              break;
           case 0xc1:
           case 0xc2:
           case 0xca:
           case 0xcb:
           case 0xcd:
           case 0xcf:
           case 0xd0:
           case 0xd1:
           case 0xd2:
              Text[p][y][x]='-';
              break;
		  }
          if(Text[p][y][x]>=0xe0&&Text[p][y][x]<=0xef)
		    Text[p][y][x]+=0x10;
          if(Text[p][y][x]>=0x80&&Text[p][y][x]<=0xaf)
		  	Text[p][y][x]+=0x40;

		}	  
	  }
     }
     if(CountPart>0)
     {
       sprintf(tmp,"c:\\iveditor\\part_%d.txt",part);
       SaveFile(tmp);
     }
     
   }
   if(CountPart>0)
   {
     sprintf(tmp,"c:\\iveditor\\part_%d.txt",Part);
     LoadFile(tmp);
   }
   gotoxy(1,25);
   clreol();
}
void WinToDos(void)
{
  register int p, x, y; //страница колонка строка
   unsigned long int part;
   int e=(CountPages<MAXPAGECOUNT)?(CountPages):(MAXPAGECOUNT);
   char i;               //индексная переменная
   char tmp[80];
   HintView(PLEASEWAIT);
   for(part=0; part<=CountPart; part++)
   {
     if(CountPart>0)
     {
       sprintf(tmp,"c:\\iveditor\\part_%d.txt",part);
       LoadFile(tmp);
     }
     for(p=0; p<=e;p++)
     {
    for(y=0; y<22; y++)
    {
      for(x=0; x<80; x++)
      {
        if(Text[p][y][x]>=127)
        {
          if(Text[p][y][x]>=0xc0&&Text[p][y][x]<=0xef)
            Text[p][y][x]-=0x40;
          if(Text[p][y][x]>=0xf0&&Text[p][y][x]<=0xff)
            Text[p][y][x]-=0x10;
        } 
      }
    }
    }
    if(CountPart>0)
     {
       sprintf(tmp,"c:\\iveditor\\part_%d.txt",part);
       SaveFile(tmp);
     }
     
   }
   if(CountPart>0)
   {
     sprintf(tmp,"c:\\iveditor\\part_%d.txt",Part);
     LoadFile(tmp);
   }
   gotoxy(1,25);
   clreol();
}
void HintView(char *string)
{
  gotoxy(1,25);
  textbackground(0);
  clreol();
  gotoxy(1,25);
  textcolor(15);
  cprintf("%s",string);
}
//Функция вывода строки-подсказки
void FileChange()
{
  char key;
  if(modify)
  {
     HintView(FILECHANGE);
     while(1){
       key=getch();
       if(key=='y'||key=='Y')
       {
         if(!CountPart)
           SaveFile(filename);
         else
           GetFullFile(filename);
         break;
       }
       if(key=='n'||key=='N') break;
     }
     modify=0;
     gotoxy(1,25);
     textbackground(0);
     clreol();
  }
}
 /*Функция сохранения документа*/
void SaveFile(char *name)
{
   int p,e=(CountPages<MAXPAGECOUNT)?(CountPages):(MAXPAGECOUNT-1);
   char y,x;
   FILE *file;
   if(strlen(name)==0) return;
   file=fopen(name,"wb");
   for(p=0; p<=e; p++)
   {
     for(y=0;y<22; y++)
     {
       for(x=0; x<80; x++)
       {
         if(Text[p][y][x]==0&&Text[p][y][x]!='\n'&&x>0)
                Text[p][y][x]='\n';
         fputc(Text[p][y][x],file);
         if(Text[p][y][x]=='\n'||Text[p][y][x]==0) break;
         if(Text[p][y][0]==0)
         {
            fclose(file);
            return;
         }
       }
     }
   }
   fclose(file);
   modify=0;
}

/*Функция загрузки файла в память
  Возращает:
  1  - файл загружен в память
  0  - ошибка: файл не найден
  -1 - ошибка: нет памяти
*/
int LoadFile(char *name)
{
    int p;
    char x,y;
    FILE *file;
    if(strlen(name)==0) return;
    file=fopen(name,"rb");
    if(file==NULL) {
      fclose(file);
      HintView(FILENOTFOUND);
      return 0;
    }
    FileChange();
    //Узнали размер файла
    for(p=0; p<MAXPAGECOUNT; p++)
      for(y=0; y<22; y++)
        for(x=0; x<80; x++)
          Text[p][y][x]=0;
    for(p=0; p<MAXPAGECOUNT; p++)
      for(y=0; y<22; y++)
      {
        fgets(Text[p][y],80,file);
        if(feof(file)) goto end;
      }
end:
    if(!CountPart) CountPages=p;
    fclose(file);
    modify=0;
    Row=0;
    Col=0;
    Page=0;
    return 1;
}
/*Функция вывода текста на экран*/
void __fastcall Print(void)
{
    register int x,y;
    textbackground(Background);
    for(y=0; y<22; y++)
    {
      gotoxy(1,y+2);
      clreol();
    }
    for(y=0; y<22; y++)
    {
       for(x=0; x<80; x++)
       {
          if(select&&Part>=SelPartStart&&Part<=SelPartEnd)
          {
            if(Page>SelPageStart&&Page<SelPageEnd&&
               x>=SelColStart&&x<=SelColEnd)
               textbackground(Selground);
            else if(Page==SelPageStart&&y>=SelRowStart&&
                 x>=SelColStart&&x<=SelColEnd&&
                 SelPageEnd>SelPageStart)
               textbackground(Selground);
            else if(Page==SelPageEnd&&y<=SelRowEnd&&
                 x>=SelColStart&&x<SelColEnd&&
                 SelPageEnd>SelPageStart)
               textbackground(Selground);
            else if(SelPageStart==SelPageEnd&&
                 Page==SelPageStart&&
                 x>=SelColStart&&x<=SelColEnd&&
                 y>=SelRowStart&&y<=SelRowEnd)
               textbackground(Selground);
            else
               textbackground(Background);
          }
          if(Text[Page][y][x]==0) break;
          if(Text[Page][y][0]==0) return;

          if((Text[Page][y][x]>='A'&&Text[Page][y][x]<='Z')||
             (Text[Page][y][x]>='a'&&Text[Page][y][x]<='z'))
             textcolor(Lat);
          else if(Text[Page][y][x]>='0'&&Text[Page][y][x]<='9')
             textcolor(Digit);
          else textcolor(Other);
          gotoxy(x+1,y+2);
          cprintf("%c",Text[Page][y][x]);
          
       }

    }
    gotoxy(1,1);


}
//Функция создания документа
void New()
{
  int p,y,x;
  char tmp[80];
  FileChange();
  for(p=0; p<MAXPAGECOUNT; p++)
      for(y=0; y<22; y++)
        for(x=0; x<80; x++)
          Text[p][y][x]=0;
  for(x=0; x<RedString; x++) Text[0][0][x]=' ';
  for(Part=0; Part<=CountPart; Part++)
  {
    sprintf(tmp,"c:\\iveditor\\part_%d.txt",Part);
    remove(tmp);
  }
  CountPart=0;
  Part=0;
  CountPages=0;
  Page=0;
  Row=0;
  Col=RedString;
  
}
void ExitProgram(void)
{
  char key,tmp[80];
  HintView(EXITYESNO);
  while(1)
  {
     key=getch();
     if(key=='Y'||key=='y')
     {
       FileChange();
       for(Part=0; Part<=CountPart; Part++)
       {
         sprintf(tmp,"c:\\iveditor\\part_%d.txt",Part);
         remove(tmp);
       }
       clrscr();
       exit(0);
     }
     if(key=='n'||key=='N')
     {
       gotoxy(1,25);
       textbackground(0);
       clreol();
       return;
     }
  }
}
void Find(char *string)
{
  char *str1=calloc(80,sizeof(char));
  char *str2=calloc(80,sizeof(char));
  register int p,  y; //страница колонка строка
   register int part;
   int e=(CountPages<MAXPAGECOUNT)?(CountPages):(MAXPAGECOUNT);
   char tmp[80];
   if(str1==NULL||str2==NULL)
  {
     HintView(NOTMEMORY);
     return;
  }
  HintView(PLEASEWAIT);
   for(part=0; part<=CountPart; part++)
   {
     if(CountPart>0)
     {
       sprintf(tmp,"c:\\iveditor\\part_%d.txt",part);
       LoadFile(tmp);
     }
     for(p=0; p<=e;p++)
     {
    for(y=0; y<22; y++)
    {
      if(p==Page&&y<Row) break;
      if(Text[p][y][0]!=0)
      {
        strcpy(str1,Text[p][y]);
        str2=strstr(str1,string);
        if(str2!=NULL)
        {
          Col=str2-str1;
          Row=y;
          Page=p;
          Part=part;
          free(str1);
          free(str2);
          select=1;
          SelPartStart=Part;
          SelPartEnd=Part;
          SelPageStart=SelPageEnd=Page;
          SelRowStart=SelRowEnd=Row;
          SelColStart=Col;
          SelColEnd=Col+strlen(string)-1;
          Col+=strlen(string);
          gotoxy(1,25);
          clreol();
          return;
        }
      }

    }
  }
    if(CountPart>0)
     {
       sprintf(tmp,"c:\\iveditor\\part_%d.txt",part);
       SaveFile(tmp);
     }

   }
   if(CountPart>0)
   {
     sprintf(tmp,"c:\\iveditor\\part_%d.txt",Part);
     LoadFile(tmp);
   }

  free(str1);
  free(str2);
  HintView(STRNOFOUND);
  return;
}
void GoTo(int pg)
{
  char buf[80];
  if(pg>0&&pg<=CountPages)
  {
    if(Page-pg>MAXPAGECOUNT||pg-Page>MAXPAGECOUNT)
    {
      sprintf(buf,"c:\\iveditor\\part_%d.txt",Part);
      SaveFile(buf);
      Page=pg%MAXPAGECOUNT;
      Part=(pg-Page)/MAXPAGECOUNT;
      pg=Page-1;
      sprintf(buf,"c:\\iveditor\\part_%d.txt",Part);
      LoadFile(buf);
      Page=pg;
    }
    else
      Page=pg-1;
  }
}
void InsertString(void)
{
  char string[80],buf[80];
  int y,p,pg=Page,rw=Row;
  FILE *out;
  unsigned long int part;
  strcpy(string,Text[Page][21]);
  for(y=21; y>Row; y--)
    strcpy(Text[Page][y],Text[Page][y-1]);
  if(!CountPart)
  {
    for(p=Page+1; p<CountPages;p++)
    {
      strcpy(buf,Text[p][21]);
      for(y=21; y>0; y--)
        strcpy(Text[p][y],Text[p][y-1]);
      strcpy(Text[p][0],string);
      strcpy(string,buf);
    }
    if(strlen(string)!=0)
    {
      if(CountPages<MAXPAGECOUNT-1)
      {
        CountPages++;
        Page++;
        strcpy(Text[CountPages][0],string);
      }
      else
      {
        SaveFile("c:\\iveditor\\part_0.txt");
        out=fopen("c:\\iveditor\\part_1.txt","wb+");
        fputs(string,out);
        fclose(out);
        CountPart++;
      }
    }
  }
  else
  {
    for(part=Part; part<CountPart; part++)
    {
      for(p=Page+1; p<MAXPAGECOUNT;p++)
      {
        strcpy(buf,Text[p][21]);
        for(y=21; y>0; y--)
          strcpy(Text[p][y],Text[p][y-1]);
        strcpy(Text[p][0],string);
        strcpy(string,buf);
      }
      sprintf(buf,"c:\\iveditor\\part_%d.txt",part);
      SaveFile(buf);
      sprintf(buf,"c:\\iveditor\\part_%d.txt",part+1);
      LoadFile(buf);
    }
    sprintf(buf,"c:\\iveditor\\part_%d.txt",CountPart);
    LoadFile(buf);
    for(p=0; p<=CountPages-MAXPAGECOUNT*CountPart;p++)
    {
      strcpy(buf,Text[p][21]);
      for(y=21; y>0; y--)
        strcpy(Text[p][y],Text[p][y-1]);
      strcpy(Text[p][0],string);
      strcpy(string,buf);
    }
    if(strlen(string)>0)
    {
      CountPages++;
      if(CountPages<MAXPAGECOUNT*(CountPart+1))
        strcpy(Text[CountPages][0],string);
      else
      {
        CountPart++;
        sprintf(buf,"c:\\iveditor\\part_%d.txt",CountPart);
        out=fopen(buf,"wb+");
        fputs(string,out);
        fclose(out);
      }
    }
    SaveFile(buf);
    sprintf(buf,"c:\\iveditor\\part_%d.txt",Part);
    LoadFile(buf);
  }
  Page=pg;
  Row=rw;
  strnset(Text[Page][Row],0,80);
  for(Col=0; Col<RedString; Col++) Text[Page][Row][Col]=' ';
  Text[Page][Row][Col+1]='\n';
  modify=1;
}
void Replace(char *string,char *newstr)
{
 char *str1=calloc(80,sizeof(char));
  char *str2=calloc(80,sizeof(char));
  register int p,  y; //страница колонка строка
   register int part;
   int e=(CountPages<MAXPAGECOUNT)?(CountPages):(MAXPAGECOUNT);
   char tmp[80];
   if(str1==NULL||str2==NULL)
  {
     HintView(NOTMEMORY);
     return;
  }
  HintView(PLEASEWAIT);
  for(part=0; part<=CountPart; part++)
   {
     if(CountPart>0)
     {
       sprintf(tmp,"c:\\iveditor\\part_%d.txt",part);
       LoadFile(tmp);
     }
     for(p=0; p<=e;p++)
     {
    for(y=0; y<22; y++)
    {
      if(p==Page&&y<Row) continue;
      if(Text[p][y][0]!=0)
      {
        strcpy(str1,Text[p][y]);
        str2=strstr(str1,string);
        if(str2!=NULL)
        {
          Col=str2-str1;
          Row=y;
          Page=p;
          Part=part;
          chrndel(Text[p][y],Col,strlen(string)+1);
          strins(Text[p][y],Col-1,newstr);
          free(str1);
          free(str2);
          select=1;
          SelPartStart=SelPartEnd=Part;
          SelPageStart=SelPageEnd=Page;
          SelRowStart=SelRowEnd=Row;
          SelColStart=Col-1;
          SelColEnd=Col+strlen(newstr)-2;
          Col+=strlen(string);
          gotoxy(1,25);
          clreol();
          return;
        }//if
      }//if

    }//for y
    }//for p
  if(CountPart>0)
     {
       sprintf(tmp,"c:\\iveditor\\part_%d.txt",part);
       SaveFile(tmp);
     }

   }
   if(CountPart>0)
   {
     sprintf(tmp,"c:\\iveditor\\part_%d.txt",Part);
     LoadFile(tmp);
   }

  free(str1);
  free(str2);
  HintView(STRNOFOUND);
  return;
}
void FillSpace(void)
{
  register unsigned int p;
  unsigned long int part;
  register unsigned char x, y;
  char buf[80];
  if(select)
  {
   if(!CountPart)
   {
    if(SelPageStart==SelPageEnd)
    {
       for(y=SelRowStart;y<=SelRowEnd;y++)
       {
         for(x=SelColStart;x<=SelColEnd;x++)
           Text[SelPageStart][y][x]=' ';
       }//for
    }//if
    if(SelPageStart<SelPageEnd)
    {
      for(y=SelRowStart; y<22; y++)
      {
        for(x=SelColStart;x<=SelColEnd;x++)
           Text[SelPageStart][y][x]=' ';
      }
      for(y=0; y<=SelRowEnd; y++)
      {
        for(x=SelColStart;x<=SelColEnd;x++)
           Text[SelPageEnd][y][x]=' ';
      }
      for(p=SelPageStart+1;p<SelPageEnd;p++)
      {
        for(y=0;y<22;y++)
          for(x=SelColStart;x<=SelColEnd;x++)
            Text[p][y][x]=' ';
      }//for
    }//if
   }//if CountPart
   else
   {
     for(y=SelRowStart; y<22; y++)
     {
       for(x=SelColStart; x<=SelColEnd; x++)
         Text[SelPageStart][y][x]=' ';
     }//for y
     for(p=SelPageStart+1; p<MAXPAGECOUNT; p++)
       for(y=0; y<22; y++)
         for(x=SelColStart; x<=SelColEnd; x++)
           Text[p][y][x]=' ';
     sprintf(buf,"c:\\iveditor\\part_%d.txt",SelPartStart);
     SaveFile(buf);
     for(part=SelPartStart+1; part<SelPartEnd; part++)
     {
       sprintf(buf,"c:\\iveditor\\part_%d.txt",part);
       LoadFile(buf);
       for(p=0; p<MAXPAGECOUNT; p++)
         for(y=0;y<22;y++)
           for(x=SelColStart;x<SelColEnd;x++)
             Text[p][y][x]=' ';
       sprintf(buf,"c:\\iveditor\\part_%d.txt",part);
       SaveFile(buf);
     }//for part
     for(p=0; p<SelPageEnd; p++)
       for(y=0; y<22; y++)
         for(x=SelColStart;x<=SelColEnd;x++)
           Text[SelPageEnd][y][x]=' ';
     for(y=0; y<=SelRowEnd; y++)
       for(x=SelColStart; x<=SelColEnd;x++)
         Text[SelPageEnd][y][x]=' ';
     sprintf(buf,"c:\\iveditor\\part_%d.txt",SelPartEnd);
     SaveFile(buf);
   }
    sprintf(buf,"c:\\iveditor\\part_%d.txt",Part);
     LoadFile(buf);
select=0;
  }//if
}
void DelSelection(void)
{
  register int p;
  register char x,y;
  unsigned long int part;
  char buf[80];
  if(SelPageStart==0&&SelPageEnd==CountPages&&CountPart==0&&
       SelColStart==0&&SelColEnd==79)
    {
      New();
      return;
    }
    if(SelPartStart==0&&SelPartEnd==CountPart&&
       SelColStart==0&&SelColEnd==79&&
       SelPageStart==0&&SelPageEnd==CountPages-CountPart*MAXPAGECOUNT)
    {
      New();
      return;
    }
  if(select)
  {
   if(!CountPart)
   {
    
    if(SelPageStart==SelPageEnd)
    {
      for(y=SelRowStart; y<=SelRowEnd;y++)
      {
  chrndel(Text[SelPageStart][y],SelColStart,SelColEnd-SelColStart+1);
  if(Text[SelPageStart][y][0]==0||Text[SelPageStart][y][0]=='\n')
          DelString();
      }
    }//if
    if(SelPageEnd>SelPageStart)
    {
      for(y=SelRowStart; y<22; y++)
      {
        chrndel(Text[SelPageStart][y],SelColStart,SelColEnd-SelColStart+1);
        if(Text[SelPageStart][y][0]==0||Text[SelPageStart][y][0]=='\n')
          DelString();
      }
      for(y=0; y<=SelRowEnd; y++)
      {
        chrndel(Text[SelPageEnd][y],SelColStart,SelColEnd-SelColStart+1);
        if(Text[SelPageEnd][y][0]==0||Text[SelPageEnd][y][0]=='\n')
          DelString();
      }//for y
      for(p=SelPageStart+1;p<SelPageEnd;p++)
        for(y=0;y<22;y++)
        {
          chrndel(Text[p][y],SelColStart,SelColEnd-SelColStart+1);
          if(Text[p][y][0]==0||Text[p][y][0]=='\n')
            DelString();
        }//for y
    }
   }//if CountPart
   else
   {
     //+фрышь яхЁтую чрёть
     for(y=SelRowStart; y<22; y++)
     {
       chrndel(Text[SelPageStart][y],SelColStart,SelColEnd-SelColStart+1);
       if(Text[SelPageStart][y][0]==0||Text[SelPageStart][y][0]=='\n')
         DelString();
     }
     for(p=SelPageStart+1;p<MAXPAGECOUNT;p++)
       for(y=0;y<22;y++)
       {
         chrndel(Text[p][y],SelColStart,SelColEnd-SelColStart+1);
         if(Text[p][y][0]==0||Text[p][y][0]=='\n')
           DelString();
       }//for y
     sprintf(buf,"c:\\iveditor\\part_%d.txt",SelPartStart);
     SaveFile(buf);
     for(part=SelPartStart;part<SelPartEnd; part++)
     {
       sprintf(buf,"c:\\iveditor\\part_%d.txt",part);
       LoadFile(buf);
       for(p=0;p<MAXPAGECOUNT;p++)
         for(y=0;y<22;y++)
         {
          chrndel(Text[p][y],SelColStart,SelColEnd-SelColStart+1);
          if(Text[p][y][0]==0||Text[p][y][0]=='\n')
            DelString();
         }//for y
       SaveFile(buf);
     }
     sprintf(buf,"c:\\iveditor\\part_%d.txt",SelPartEnd);
     LoadFile(buf);
     for(p=0;p<SelPageEnd;p++)
      for(y=0;y<22;y++)
      {
        chrndel(Text[p][y],SelColStart,SelColEnd-SelColStart+1);
        if(Text[p][y][0]==0||Text[p][y][0]=='\n')
            DelString();
      }//for y
     for(y=0; y<=SelRowEnd; y++)
     {
       chrndel(Text[SelPageEnd][y],SelColStart,SelColEnd-SelColStart+1);
       if(Text[SelPageEnd][y][0]==0||Text[SelPageEnd][y][0]=='\n')
         DelString();
     }//for y

   }//else
    sprintf(buf,"c:\\iveditor\\part_%d.txt",Part);
     LoadFile(buf);
        select=0;
  }//if select
}

void CopySelection()
{
  long int sz=(SelPageEnd-SelPageStart+1)*22*(SelColEnd-SelColStart)+(SelPartEnd-SelPartStart)*MAXPAGECOUNT;
  register unsigned int p;
  register char x, y;
  int part;
  char buf[80];
  char *ptr=NULL;
  buffer=calloc(sz,sizeof(char));
  if(buffer==NULL){
    HintView(NOTMEMORY);
    return;
  }
  memset(buffer,0,sz);
  ptr=buffer;
  bufx=SelColEnd-SelColStart;
  if(!CountPart)
  {
  if(SelPageStart==SelPageEnd)
  {
    for(y=SelRowStart; y<=SelRowEnd; y++)
    {
      for(x=SelColStart; x<=SelColEnd; x++)
      {
        *buffer=Text[SelPageStart][y][x];
        buffer++;
      }
    }
  }
  else
  {
     for(y=SelRowStart; y<22; y++)
     {
       for(x=SelColStart; x<=SelColEnd; x++)
       {
         *buffer=Text[SelPageStart][y][x];
         buffer++;
       }
     }
     for(p=SelPageStart+1; p<SelPageEnd; p++)
     {
       for(y=0; y<22; y++)
       {
         for(x=SelColStart; x<=SelColEnd; x++)
         {
           *buffer=Text[p][y][x];
           buffer++;
         }
       }
     }
     for(y=0; y<=SelRowEnd; y++)
     {
       for(x=SelColStart; x<=SelColEnd; x++)
       {
         *buffer=Text[SelPageEnd][y][x];
         buffer++;
       }
     }
  }
  }
  else
  {
     for(y=SelRowStart; y<22; y++)
     {
       for(x=SelColStart; x<=SelColEnd; x++)
       {
         *buffer=Text[SelPageStart][y][x];
         buffer++;
       }
     }
     for(part=SelPartStart; part<SelPartEnd; part++)
     {
      sprintf(buf,"c:\\iveditor\\part_%d.txt",part);
      LoadFile(buf);
      for(p=SelPageStart+1; p<MAXPAGECOUNT; p++)
      {
       for(y=0; y<22; y++)
       {
         for(x=SelColStart; x<=SelColEnd; x++)
         {
           *buffer=Text[p][y][x];
           buffer++;
         }
       }
      }
      sprintf(buf,"c:\\iveditor\\part_%d.txt",part);
      SaveFile(buf);
     }
     sprintf(buf,"c:\\iveditor\\part_%d.txt",SelPartEnd);
     LoadFile(buf);
     for(p=0; p<SelPageEnd; p++)
       for(y=0;y<22; y++)
         for(x=SelColStart; x<=SelColEnd;x++)
         {
           *buffer=Text[p][y][x];
           buffer++;
         }
     for(y=0; y<=SelRowEnd; y++)
     {
       for(x=SelColStart; x<=SelColEnd; x++)
       {
         *buffer=Text[SelPageEnd][y][x];
         buffer++;
       }
     }
     sprintf(buf,"c:\\iveditor\\part_%d.txt",Part);
     LoadFile(buf);
  }
  buffer=ptr;
}
void CutSelection(void)
{
  free(buffer);
  buffer=NULL;
  CopySelection();
  if(insert) DelSelection();
  else       FillSpace();
}
void Paste(void)
{
  unsigned long int sz;
  register int i;
  char buf[80],*ptr=NULL;
  if(buffer==NULL)
  {
    HintView(NOTFILLBUF);
    return;
  }
  ptr=buffer;
  sz=strlen(buffer)/bufx;
  strnset(buf,' ',80);
  if(insert)
  {
    for(i=0; i<sz;i++)
    {
      strncpy(buf,buffer,bufx+1);
      buf[bufx+1]=0;
      if(!Text[Page][Row+i][0])
        strnset(Text[Page][Row+i],' ',Col);
      strins(Text[Page][Row+i],Col,buf);
      buffer+=bufx+1;
    }
  }
  else
  {
    for(i=0; i<sz;i++)
    {
      if(!Text[Page][Row+i][0])
        strnset(Text[Page][Row+i],' ',Col);
      stricpy(Text[Page][Row+i],buffer,Col,bufx+1);
      buffer+=bufx;
    }
  }
  buffer=ptr;
}
void OptionsChange(void)
{
  register char y;
  char colors[][20]={"черный",
  				 "Синий\0",
  				 "Голубой\0",
  				 "Зеленый\0",
  				 "Красный\0",
  				 "Сиреневый\0",
  				 "Коричневый\0",
  				 "Светло серый\0",
  				 "Темно серый\0",
  				 "Светло синий\0",
  				 "Светло зеленый\0",
  				 "Светло голубой\0",
  				 "Светло красный\0",
  				 "Светло сиреневый\0",
  				 "Желтый\0",
  				 "Белый\0"};
  textcolor(15);
  textbackground(4);
  gotoxy(25,5);
  y=0;
  cprintf("      Настройки редактора               ");
  gotoxy(25,15);
  cprintf("OK                              Отмена  ");
  while(1)
  {
    gotoxy(25,6);
    textcolor(0);
    textbackground((y==0)?(2):(7));
    cprintf("Отступ \"Красной строки\": ");
    gotoxy(49,6);
    cprintf("%-16d",RedString);
    gotoxy(25,7);
    textbackground((y==1)?(2):(7));
    cprintf("Размер табуляции:        ");
    gotoxy(49,7);
    cprintf("%-16d",TabSize);
    gotoxy(25,8);
    textbackground((y==2)?(2):(7));
    cprintf("Автосохранение (мин):    ");
    gotoxy(49,8);
    cprintf("%-16d",autosave);
    gotoxy(25,9);
    textbackground((y==3)?(2):(7));
    cprintf("Кодировка по умолчанию:   ");
    gotoxy(49,9);
    cprintf("%-16s",(doscode)?("DOS"):("WIN"));
    gotoxy(25,10);
    textbackground((y==4)?(2):(7));
    cprintf("Фон области ввода текст: ");
    gotoxy(49,10);
    cprintf("%-16s",colors[Background]);
    gotoxy(25,11);
    textbackground((y==5)?(2):(7));
    cprintf("Фон выделяемого текста:   ");
    gotoxy(49,11);
    cprintf("%-16s",colors[Selground]);
    gotoxy(25,12);
    textbackground((y==6)?(2):(7));
    cprintf("Цвет латинских символов: ");
    gotoxy(49,12);
    cprintf("%-16s",colors[Lat]);
    gotoxy(25,13);
    textbackground((y==7)?(2):(7));
    cprintf("Цвет цифр:               ");
    gotoxy(49,13);
    cprintf("%-16s",colors[Digit]);
    gotoxy(25,14);
    textbackground((y==8)?(2):(7));
    cprintf("Цвет остальных сиволов:  ");
    gotoxy(49,14);
    cprintf("%-16s",colors[Other]);

    switch(getch())
    {
       case key_Up:
         if(y>0) y--;
         break;
       case key_Down:
         if(y<8) y++;
         break;
       case 13:
         OptionsSave();
         SpaceToTab();
         TabToSpace();
         return;
       case 27:
         OptionsLoad();
         return;
       case key_Left:
         switch(y)
         {
            case 0:
              if(RedString>0)
                RedString--;
              break;
            case 1:
              if(TabSize>3)
                TabSize--;
              break;
            case 2:
              if(autosave>1)
                autosave--;
              break;
            case 3:
              doscode=!doscode;
              break;
            case 4:
              if(Background>0) Background--;
              break;
            case 5:
              if(Selground>0) Selground--;
              break;
            case 6:
              if(Lat>0) Lat--;
              break;
            case 7:
              if(Digit>0) Digit--;
              break;
            case 8:
              if(Other>0) Other--;
              break;
         }
         break;
       case key_Right:
         switch(y)
         {
            case 0:
              if(RedString<10)
                RedString++;
              break;
            case 1:
              if(TabSize<15)
                TabSize++;
              break;
            case 2:
              if(autosave<30)
                autosave++;
              break;
            case 3:
              doscode=!doscode;
              break;
            case 4:
              if(Background<7) Background++;
              break;
            case 5:
              if(Selground<7) Selground++;
              break;
            case 6:
              if(Lat<15) Lat++;
              break;
            case 7:
              if(Digit<15) Digit++;
              break;
            case 8:
              if(Other<15) Other++;
              break;
         }
         break;
    }
  }

}
void OptionsSave(void)
{
   FILE *file=fopen(OptionsFile,"wb");
   fputc(RedString,file);
   fputc(TabSize,file);
   fputc(doscode,file);
   fputc(autosave,file);
   fputc(Background,file);
   fputc(Selground,file);
   fputc(Lat,file);
   fputc(Digit,file);
   fputc(Other,file);
   fclose(file);
}
void OptionsLoad(void)
{
   FILE *file=fopen(OptionsFile,"rb");
   if(!file)
   {
      RedString=5;
      TabSize=8;
      autosave=5;
      doscode=1;
      Background=1;
      Selground=4;
      Lat=14;
      Digit=13;
      Other=15;
      return;
   }
   RedString =fgetc(file);
   TabSize   =fgetc(file);
   doscode   =fgetc(file);
   autosave  =fgetc(file);
   Background=fgetc(file);
   Selground =fgetc(file);
   Lat       =fgetc(file);
   Digit     =fgetc(file);
   Other     =fgetc(file);
   fclose(file);
}
void DelString(void)
{
   register char y;  //=юьхЁ ётЁюъш
   register int p;   //=юьхЁ ётЁрэшцы
   unsigned long int part;
   char buf[80],str[80];
   HintView(PLEASEWAIT);
   //-+^ +++++++ ++++=++X
   //+юяшЁютрэшх ёыхфующхщ ётЁюъш т тхъущую
   for(y=Row; y<22;y++)
     strncpy(Text[Page][y],Text[Page][y+1],80);
   //-+^ +++-+l+++ ++++=++X (++++ +=+ +++m)
   //+юяшЁютрэшх яхЁтющ ётЁюъш шч ёыхфующхщ ётЁюрэшцы т
   //яЁхфыфущую ётЁрэшцу
   if(CountPages>1)
     strncpy(Text[Page][21],Text[Page+1][0],80);
   //+ючэю тръ цх фыя юётрыьэых ётЁрэшц
   if(!CountPart)
   {
     for(p=Page+1; p<=CountPages; p++)
     {
       for(y=0; y<21;y++)
         strncpy(Text[p][y],Text[p][y+1],80);
       strncpy(Text[p][21],Text[p+1][0],80);
     }
   }
   else
   {
     for(p=Page+1; p<MAXPAGECOUNT; p++)
     {
       for(y=0; y<21;y++)
         strncpy(Text[p][y],Text[p][y+1],80);
       strncpy(Text[p][21],Text[p+1][0],80);
     }
     sprintf(buf,"c:\\iveditor\\part_%d.txt",Part);
     SaveFile(buf);
     for(part=Part+1; part<CountPart;part++)
     {
       sprintf(buf,"c:\\iveditor\\part_%d.txt",part);
       LoadFile(buf);
       for(p=0; p<MAXPAGECOUNT-1; p++)
       {
         for(y=0; y<21;y++)
           strncpy(Text[p][y],Text[p][y+1],80);
         strncpy(Text[p][21],Text[p+1][0],80);
       }
       sprintf(buf,"c:\\iveditor\\part_%d.txt",part);
       SaveFile(buf);

     }
     sprintf(buf,"c:\\iveditor\\part_%d.txt",CountPart);
     LoadFile(buf);
     for(p=0; p<CountPages-MAXPAGECOUNT*CountPart; p++)
     {
       if(!Text[p][0][0])
       {
         CountPages--;
         break;
       }
       for(y=0; y<21;y++)
         strncpy(Text[p][y],Text[p][y+1],80);
       strncpy(Text[p][21],Text[p+1][0],80);
       
     }
     sprintf(buf,"c:\\iveditor\\part_%d.txt",CountPart);
     SaveFile(buf);
     sprintf(buf,"c:\\iveditor\\part_%d.txt",Part);
     LoadFile(buf);
   }
   gotoxy(1,25);
   clreol();
}
//Псевдографика
char Graph(char key)
{
  switch(key)
  {
    //Нижний регистр
    //Вверхний ряд
    case 'q': key=0xda; break;
    case 'w': key=0xc2; break;
    case 'e': key=0xbf; break;
    case 'r': key=0xd6; break;
    case 't': key=0xd2; break;
    case 'y': key=0xb7; break;
    case 'u': key=0xc4; break;
    case 'i': key=0xdc; break;
    case 'o': key=0xcd; break;
    case 'p': key=0x03; break;
    case '[': key=0x11; break;
    case ']': key=0x10; break;
    //средний ряд
    case 'a': key=0xc3; break;
    case 's': key=0xc5; break;
    case 'd': key=0xb4; break;
    case 'f': key=0xc7; break;
    case 'g': key=0xd7; break;
    case 'h': key=0xb6; break;
    case 'j': key=0xde; break;
    case 'k': key=0xdb; break;
    case 'l': key=0xdd; break;
    case ';': key=0x04; break;
    case '\'': key=0x05; break;
    //нижний ряд
    case 'z': key=0xc0; break;
    case 'x': key=0xc1; break;
    case 'c': key=0xd9; break;
    case 'v': key=0xd3; break;
    case 'b': key=0xd0; break;
    case 'n': key=0xbd; break;
    case 'm': key=0xb3; break;
    case ',': key=0xdf; break;
    case '.': key=0xba; break;
    case '/': key=0x06; break;
    //Вверхний регистр
    //Вверхний ряд
    case 'Q': key=0xc9; break;
    case 'W': key=0xcb; break;
    case 'E': key=0xbb; break;
    case 'R': key=0xd5; break;
    case 'T': key=0xd1; break;
    case 'Y': key=0xb8; break;
    case 'U': key=0xB0; break;
    case 'I': key=0xdc; break;
    case 'O': key=0xB1; break;
    case 'P': key=0x0b; break;
    case '{': key=0x1e; break;
    case '}': key=0x1f; break;
    //средний ряд
    case 'A': key=0xcc; break;
    case 'S': key=0xce; break;
    case 'D': key=0xb9; break;
    case 'F': key=0xc6; break;
    case 'G': key=0xd8; break;
    case 'H': key=0xb5; break;
    case 'J': key=0xde; break;
    case 'K': key=0xdb; break;
    case 'L': key=0xdd; break;
    case ':': key=0x0c; break;
    case '\"': key=0xfb; break;
    //нижний ряд
    case 'Z': key=0xc8; break;
    case 'X': key=0xca; break;
    case 'C': key=0xbc; break;
    case 'V': key=0xd4; break;
    case 'B': key=0xcf; break;
    case 'N': key=0xbe; break;
    case 'M': key=0xB2; break;
    case '<': key=0xdf; break;
    case '>': key=0xFE; break;
    case '?': key=0x15; break;
  }
  return key;
}
char * GetNameFile(char *string)
{
   char *name=strrchr(string,'\\');
   return (!name)?(string):(name+1);
}
void textupr(void)
{
	register int p;
	register char x,y;
	if(select)
	{
	  if(SelPageStart==SelPageEnd)
	  {
	    p=SelPageStart;
	    for(y=SelRowStart; y<=SelRowEnd; y++)
	    {
	      for(x=SelColStart;x<=SelColEnd;x++)
	      {
	        if(Text[p][y][x]>='a'&&Text[p][y][x]<='z')
	          Text[p][y][x]-=32;
	        if(doscode==0&&Text[p][y][x]>=0xe0&&Text[p][y][x]<=0xff)
	          Text[p][y][x]-=32;
	        if(doscode==1&&Text[p][y][x]>=0xa0&&Text[p][y][x]<=0xaf)
	          Text[p][y][x]-=32;
	        if(doscode==1&&Text[p][y][x]>=0xe0&&Text[p][y][x]<=0xef)
	          Text[p][y][x]-=0x50;
	      }
	    }
	  }
	  else
	  {
	 	p=SelPageStart;
	    for(y=SelRowStart; y<=22; y++)
	    {
	      for(x=SelColStart;x<=SelColEnd;x++)
	      {
	        if(Text[p][y][x]>='a'&&Text[p][y][x]<='z')
	          Text[p][y][x]-=32;
	        if(doscode==0&&Text[p][y][x]>=0xe0&&Text[p][y][x]<=0xff)
	          Text[p][y][x]-=32;
	        if(doscode==1&&Text[p][y][x]>=0xa0&&Text[p][y][x]<=0xaf)
	          Text[p][y][x]-=32;
	        if(doscode==1&&Text[p][y][x]>=0xe0&&Text[p][y][x]<=0xef)
	          Text[p][y][x]-=0x50;
	      }
	    }
	    p=SelPageEnd;
	    for(y=0; y<=SelRowEnd; y++)
	    {
	      for(x=SelColStart;x<=SelColEnd;x++)
	      {
	        if(Text[p][y][x]>='a'&&Text[p][y][x]<='z')
	          Text[p][y][x]-=32;
	        if(doscode==0&&Text[p][y][x]>=0xe0&&Text[p][y][x]<=0xff)
	          Text[p][y][x]-=32;
	        if(doscode==1&&Text[p][y][x]>=0xa0&&Text[p][y][x]<=0xaf)
	          Text[p][y][x]-=32;
	        if(doscode==1&&Text[p][y][x]>=0xe0&&Text[p][y][x]<=0xef)
	          Text[p][y][x]-=0x50;
	      }
	    }
	    for(p=SelPageStart+1; p<SelPageEnd; p++)
	    {
	      for(y=0; y<=SelRowEnd; y++)
	      {
	        for(x=SelColStart;x<=SelColEnd;x++)
	        {
	        if(Text[p][y][x]>='a'&&Text[p][y][x]<='z')
	          Text[p][y][x]-=32;
                if(doscode==0&&Text[p][y][x]>=0xe0&&Text[p][y][x]<=0xff)
	          Text[p][y][x]-=32;
	        if(doscode==1&&Text[p][y][x]>=0xa0&&Text[p][y][x]<=0xaf)
	          Text[p][y][x]-=32;
	        if(doscode==1&&Text[p][y][x]>=0xe0&&Text[p][y][x]<=0xef)
	          Text[p][y][x]-=0x50;
	        }
	      } 
	    }
	  }//else
	}//if	
}
void textlwr(void)
{
	register int p;
	register char x,y;
	if(select)
	{
	  if(SelPageStart==SelPageEnd)
	  {
	    p=SelPageStart;
	    for(y=SelRowStart; y<=SelRowEnd; y++)
	    {
	      for(x=SelColStart;x<=SelColEnd;x++)
	      {

                  if(Text[p][y][x]>='A'&&Text[p][y][x]<='Z')
	            Text[p][y][x]+=32;
	          if(doscode==0&&Text[p][y][x]>=0xc0&&Text[p][y][x]<=0xdf)
	            Text[p][y][x]+=32;
	          if(doscode==1&&Text[p][y][x]>=0x80&&Text[p][y][x]<=0x8f)
	            Text[p][y][x]+=32;
	          if(doscode==1&&Text[p][y][x]>=0x90&&Text[p][y][x]<=0x9f)
	            Text[p][y][x]+=0x50;

	      }
	    }
	  }
	  else
	  {
            p=SelPageStart;
	    for(y=SelRowStart; y<=22; y++)
	    {
	      for(x=SelColStart;x<=SelColEnd;x++)
	      {
	        if(Text[p][y][x]>='A'&&Text[p][y][x]<='Z')
	          Text[p][y][x]+=32;
	        if(doscode==0&&Text[p][y][x]>=0xc0&&Text[p][y][x]<=0xdf)
	          Text[p][y][x]+=32;
	        if(doscode==1&&Text[p][y][x]>=0x80&&Text[p][y][x]<=0x8f)
	          Text[p][y][x]+=32;
	        if(doscode==1&&Text[p][y][x]>=0x90&&Text[p][y][x]<=0x9f)
	          Text[p][y][x]+=0x50;;
	      }
	    }
	    p=SelPageEnd;
	    for(y=0; y<=SelRowEnd; y++)
	    {
	      for(x=SelColStart;x<=SelColEnd;x++)
	      {
	        if(Text[p][y][x]>='A'&&Text[p][y][x]<='Z')
	          Text[p][y][x]+=32;
	        if(doscode==0&&Text[p][y][x]>=0xc0&&Text[p][y][x]<=0xdf)
	          Text[p][y][x]+=32;
	        if(doscode==1&&Text[p][y][x]>=0x80&&Text[p][y][x]<=0x8f)
	          Text[p][y][x]+=32;
	        if(doscode==1&&Text[p][y][x]>=0x90&&Text[p][y][x]<=0x9f)
	          Text[p][y][x]+=0x50;
	      }
	    }
	    for(p=SelPageStart+1; p<SelPageEnd; p++)
	    {
	      for(y=0; y<=SelRowEnd; y++)
	      {
	        for(x=SelColStart;x<=SelColEnd;x++)
	        {
	        if(Text[p][y][x]>='A'&&Text[p][y][x]<='Z')
	          Text[p][y][x]+=32;
	        if(doscode==0&&Text[p][y][x]>=0xc0&&Text[p][y][x]<=0xdf)
	          Text[p][y][x]+=32;
	        if(doscode==1&&Text[p][y][x]>=0x80&&Text[p][y][x]<=0x8f)
	          Text[p][y][x]+=32;
	        if(doscode==1&&Text[p][y][x]>=0x90&&Text[p][y][x]<=0x9f)
	          Text[p][y][x]+=0x50;
	        }
	      }
	    }
	  }//else
	}//if
}
void textword(void)
{
        register int p;
	register char x,y;
        HintView(PLEASEWAIT);
	if(select)
	{
	  if(SelPageStart==SelPageEnd)
	  {
	    p=SelPageStart;
	    for(y=SelRowStart; y<=SelRowEnd; y++)
	    {
	      for(x=SelColStart;x<=SelColEnd;x++)
	      {
	        if(Text[p][y][x-1]!=' '&&Text[p][y][x-1]!='\n'&&Text[p][y][x-1])
                {
                  if(Text[p][y][x]>='A'&&Text[p][y][x]<='Z')
	            Text[p][y][x]+=32;
	          if(doscode==0&&Text[p][y][x]>=0xc0&&Text[p][y][x]<=0xdf)
	            Text[p][y][x]+=32;
	          if(doscode==1&&Text[p][y][x]>=0x80&&Text[p][y][x]<=0x8f)
	            Text[p][y][x]+=32;
	          if(doscode==1&&Text[p][y][x]>=0x90&&Text[p][y][x]<=0x9f)
	            Text[p][y][x]+=0x50;
                }
                else
                {
                  if(Text[p][y][x]>='a'&&Text[p][y][x]<='z')
	            Text[p][y][x]-=32;
	          if(doscode==0&&Text[p][y][x]>=0xe0&&Text[p][y][x]<=0xff)
	            Text[p][y][x]-=32;
	          if(doscode==1&&Text[p][y][x]>=0xa0&&Text[p][y][x]<=0xaf)
	            Text[p][y][x]-=32;
	          if(doscode==1&&Text[p][y][x]>=0xe0&&Text[p][y][x]<=0xef)
	            Text[p][y][x]-=0x50;
                }
	      }
	    }
	  }
	  else
	  {
            p=SelPageStart;
	    for(y=SelRowStart; y<=22; y++)
	    {
	      for(x=SelColStart;x<=SelColEnd;x++)
	      {
	        if(Text[p][y][x-1]!=' '&&Text[p][y][x-1]!='\n'&&Text[p][y][x-1])
                {
                  if(Text[p][y][x]>='A'&&Text[p][y][x]<='Z')
	            Text[p][y][x]+=32;
	          if(doscode==0&&Text[p][y][x]>=0xc0&&Text[p][y][x]<=0xdf)
	            Text[p][y][x]+=32;
	          if(doscode==1&&Text[p][y][x]>=0x80&&Text[p][y][x]<=0x8f)
	            Text[p][y][x]+=32;
	          if(doscode==1&&Text[p][y][x]>=0x90&&Text[p][y][x]<=0x9f)
	            Text[p][y][x]+=0x50;
                }
                else
                {
                  if(Text[p][y][x]>='a'&&Text[p][y][x]<='z')
	            Text[p][y][x]-=32;
	          if(doscode==0&&Text[p][y][x]>=0xe0&&Text[p][y][x]<=0xff)
	            Text[p][y][x]-=32;
	          if(doscode==1&&Text[p][y][x]>=0xa0&&Text[p][y][x]<=0xaf)
	            Text[p][y][x]-=32;
	          if(doscode==1&&Text[p][y][x]>=0xe0&&Text[p][y][x]<=0xef)
	            Text[p][y][x]-=0x50;
                }
	      }
	    }
	    p=SelPageEnd;
	    for(y=0; y<=SelRowEnd; y++)
	    {
	      for(x=SelColStart;x<=SelColEnd;x++)
	      {
	        if(Text[p][y][x-1]!=' '&&Text[p][y][x-1]!='\n'&&Text[p][y][x-1])
                {
                  if(Text[p][y][x]>='A'&&Text[p][y][x]<='Z')
	            Text[p][y][x]+=32;
	          if(doscode==0&&Text[p][y][x]>=0xc0&&Text[p][y][x]<=0xdf)
	            Text[p][y][x]+=32;
	          if(doscode==1&&Text[p][y][x]>=0x80&&Text[p][y][x]<=0x8f)
	            Text[p][y][x]+=32;
	          if(doscode==1&&Text[p][y][x]>=0x90&&Text[p][y][x]<=0x9f)
	            Text[p][y][x]+=0x50;
                }
                else
                {
                  if(Text[p][y][x]>='a'&&Text[p][y][x]<='z')
	            Text[p][y][x]-=32;
	          if(doscode==0&&Text[p][y][x]>=0xe0&&Text[p][y][x]<=0xff)
	            Text[p][y][x]-=32;
	          if(doscode==1&&Text[p][y][x]>=0xa0&&Text[p][y][x]<=0xaf)
	            Text[p][y][x]-=32;
	          if(doscode==1&&Text[p][y][x]>=0xe0&&Text[p][y][x]<=0xef)
	            Text[p][y][x]-=0x50;
                }
	      }
	    }
	    for(p=SelPageStart+1; p<SelPageEnd; p++)
	    {
	      for(y=0; y<=SelRowEnd; y++)
	      {
	        for(x=SelColStart;x<=SelColEnd;x++)
	        {
	        if(Text[p][y][x-1]!=' '&&Text[p][y][x-1]!='\n'&&Text[p][y][x-1])
                {
                  if(Text[p][y][x]>='A'&&Text[p][y][x]<='Z')
	            Text[p][y][x]+=32;
	          if(doscode==0&&Text[p][y][x]>=0xc0&&Text[p][y][x]<=0xdf)
	            Text[p][y][x]+=32;
	          if(doscode==1&&Text[p][y][x]>=0x80&&Text[p][y][x]<=0x8f)
	            Text[p][y][x]+=32;
	          if(doscode==1&&Text[p][y][x]>=0x90&&Text[p][y][x]<=0x9f)
	            Text[p][y][x]+=0x50;
                }
                else
                {
                  if(Text[p][y][x]>='a'&&Text[p][y][x]<='z')
	            Text[p][y][x]-=32;
	          if(doscode==0&&Text[p][y][x]>=0xe0&&Text[p][y][x]<=0xff)
	            Text[p][y][x]-=32;
	          if(doscode==1&&Text[p][y][x]>=0xa0&&Text[p][y][x]<=0xaf)
	            Text[p][y][x]-=32;
	          if(doscode==1&&Text[p][y][x]>=0xe0&&Text[p][y][x]<=0xef)
	            Text[p][y][x]-=0x50;
                }
	        }
	      }
	    }
	  }//else
	}//if
        gotoxy(1,25);
        textbackground(0);
        clreol();
}
void GetPartFile(char name[80])
{
        FILE *in=fopen(name,"rb+");
        FILE *out=fopen("c:\\iveditor\\part_0.txt","wb+");
        unsigned char y;
        unsigned int  p;
        char buffer[80];
        HintView(PLEASEWAIT);
        if(!in)
        {
          HintView(FILENOTFOUND);
          fclose(in);
          CountPart=0;
          return;
        }
        CountPart=0;
        CountPages=0;
        y=0;
        p=0;
        while(!feof(in))
        {
          fgets(buffer,80,in);
          if(feof(in)) break;
          if(!buffer) break;
          fputs(buffer,out);
          y++;
          if(y>=22)
          {
            y=0;
            p++;
            CountPages++;
            if(p>=MAXPAGECOUNT)
            {
              p=0;
              CountPart++;
              sprintf(buffer,"c:\\iveditor\\part_%d.txt",CountPart);
              fclose(out);
              out=fopen(buffer,"wb+");
            }
          }
        }
        fclose(in);
        fclose(out);
        if(!CountPart)
          remove("c:\\iveditor\\part_0.txt");
        gotoxy(1,25);
        textbackground(0);
        clreol();
}
void GetFullFile(char *name)
{
        FILE *out=fopen(name,"wb+");
        FILE *in;
        unsigned char y;
        unsigned int  p;
        unsigned long int part;
        char buffer[80],tmpfile[80];
        HintView(PLEASEWAIT);
        for(part=0; part<=CountPart; part++)
        {
           sprintf(tmpfile,"c:\\iveditor\\part_%d.txt",part);
           in=fopen(tmpfile,"rb+");
           if(!in)
           {
             fprintf(out,"IvEditor Error\n"
                         "File %s not found\n\n",tmpfile);
             fclose(in);
             continue;
           }

           for(p=0; p<MAXPAGECOUNT; p++)
           {
              for(y=0; y<=22; y++)
              {
                 fgets(buffer,80,in);
                 if(feof(in))
                 {
                   if(part<CountPart) goto next;
                   else               goto end;

                 }
                 fputs(buffer,out);
              }
           }
          next:
           fclose(in);

        }
      end:
        fclose(in);
        fclose(out);
        gotoxy(1,25);
        textbackground(0);
        clreol();
}