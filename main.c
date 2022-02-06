//---------------------------------------------------------------------------
#include "iveditor.h"
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
        int p;
        char err;
        char comm[80],comm2[80],x, y,key;
        struct time Zeit; //�����
        Page=0;           //��������
        Col=0;            //�������
        Row=0;            //������
        modify=0;         //�� �������
        insert=1;         //����� �������
        graphmode=0;      //����. �����
        select=0;         //��������� ����
        SelColStart=0;    //���. �������
        SelColEnd=0;      //���. �������
        SelRowStart=0;    //���. ������
        SelRowEnd=0;      //���. ������
        SelPageStart=0;   //���. ��������
        SelPageEnd=0;     //���. ��������
        Part=0;           //������� �����
        CountPart=0;      //���-�� ������
        OptionsLoad();    //�������� �����
        //���������
        for(x=0; x<80; x++)
        {
          filename[x]=0;  //��� �����
          oldfile[x]=0;   //��� ����������� �����
          comm2[x]=0;     //�������
          findstr[x]=0;   //������ ��� ������
          replacestr[x]=0;//������ ��� ������
          comm[x]=' ';    //�������
        }
        //����� ����������� ������� �����/������
        fflush(stdin);
        fflush(stdout);
        fflush(stderr);
        getcwd(comm2,80);
        //��������, ���� ������� C:\IvEditor
        if(chdir("C:\\IvEditor"))
                mkdir("C:\\IvEditor");
        else
                chdir(comm2);
        for(x=0; x<80; x++) comm2[x]=0;
        textmode(2); //���������� ��������� ����� 80x25 16
        if(argc>1)        //���� ���-������ � ��������� ������
        {
          GetPartFile(argv[1]);
          if(!CountPart)
          {
            if(LoadFile(argv[1]))
             strcpy(filename,argv[1]);
            else
            {
              New();
              strcpy(filename,"noname.txt");
            }
          }
          else
          {
            LoadFile("c:\\iveditor\\part_0.txt");
            strcpy(filename,argv[1]);
          }
        }
        else {
          New();
          strcpy(filename,"noname.txt");
        }
        do{
          //������ ������
          _setcursortype(_NOCURSOR);
          //����� �� �����
          Print();
          //�������������� ������
          textbackground(4);
          gotoxy(1,1);
          clreol();
          textcolor(15);
          //����� ��������� �������
          cprintf("%6d/%-6d\x0b3X:%02d Y:%02d\x0b3",Page+1+Part*300,CountPages+1,Col+1,Row+1);
          //����� ������� �����
          cprintf("%s\x0b3%s\x0b3",(insert)?(INSERT):(OWERTYPE),(graphmode)?(GRAPHICS):(NORMALTEXT));
          //����� ���������
          cprintf("%s\x0b3",(doscode)?("Dos"):("Win"));
          //����� ����� ����������� '*'
          cprintf(" %c",(modify)?('*'):(' '));
          //����� ����� �����
          cprintf("%-38s",GetNameFile(filename));
          //������ ����� �������
          gotoxy(1,24);
          textbackground(2);
          clreol();
          //��������� �������
          gotoxy(Col+1,Row+2);
          //���������� �������
          gettime(&Zeit);
          p=Zeit.ti_min;
          err=p;
          //����� �������
          gotoxy(73,1);
          textcolor(15);
          textbackground(4);
          cprintf("\x0b3%02d:%02d",Zeit.ti_hour,Zeit.ti_min);
          //���������� ������
          _setcursortype(_NORMALCURSOR);
          while(!kbhit())
          {
            //������ �����
            gettime(&Zeit);
            //������ ������
            if(Zeit.ti_min-err==1)
            {
              err=Zeit.ti_min;
              //������ ������
              _setcursortype(_NOCURSOR);
              //������ �����
              gotoxy(73,1);
              textcolor(15);
              textbackground(4);
              cprintf("\x0b3%02d:%02d",Zeit.ti_hour,Zeit.ti_min);
              //���������� ������
              _setcursortype(_NORMALCURSOR);

            }
            //��������������
            if(Zeit.ti_min-p==autosave)
            {
              HintView(AUTOSAVE);
              //�������� ������������, ��� ���������
              sleep(1);
              //������� ������ ���������
              textbackground(0);
              gotoxy(1,25);
              clreol();
              p=Zeit.ti_min;
              if(!CountPart)  SaveFile("autosave.txt");
              else            GetFullFile("autosave.txt");
              
            }
            gotoxy(Col+1,Row+2);
          }
          //��������� ��� �������
          key=getch();
          //�������� ������ ���������
          textbackground(0);
          gotoxy(1,25);
          clreol();
          switch(key)
          {
            case key_ctrlA: //�������� ���
              select=1;
              SelPageStart=0;
              SelPartStart=0;
              if(!CountPart)
              {
                SelPageEnd=CountPages;
                SelPartEnd=0;
              }
              else
              {
                SelPartEnd=CountPart;
                SelPageEnd=CountPages-CountPart*MAXPAGECOUNT;
              }
              SelRowStart=0;
              SelRowEnd=21;
              SelColStart=0;
              SelColEnd=79;
              break;
            case key_ctrlD: //����������
              if(select)
              {
                CopySelection();
                select=0;
              }  
              break;
            case key_ctrlX: //��������
              if(select)
              {
                CutSelection();
                select=0;
                modify=1;
              }

              break;
            case key_ctrlV: //��������
              Paste();
              modify=1;
              break;
            case key_ctrlN: //����� ���������
              select=0;
              break;
            case key_Tab:   //���������
              if(insert)
              {
                for(x=0; x<TabSize; x++)
                  chrins(Text[Page][Row],Col+x,' ');
              }
              if(Col+TabSize>79) {Col=0; Row++; break;}
              for(err=0; err<TabSize; err++)
                if(!Text[Page][Row][Col+err]||
                    Text[Page][Row][Col+err]=='\r'||
                    Text[Page][Row][Col+err]=='\n')
                    Text[Page][Row][Col+err]=' ';
              Col+=TabSize;
              modify=1;
              break;
            case key_BSpace: //�������� ����������� �������
              if(Col>0)Col--;  //���������� �� ������� �����
              chrdel(Text[Page][Row],Col);
              if(!strlen(Text[Page][Row])) DelString();
              if(!strlen(Text[Page][Row]))
              {
                 Row--;
                 if(Row==0)
                 {
                   if(Page>0)
                   {
                      Row=21;
                      Page--;
                   }
                 }
                 Col=strlen(Text[Page][Row]);
              }
              if(!Text[0][0][0])
              {
                 Row=0;
                 Col=0;
                 Page=0;
                 Text[0][0][0]=' ';
              }
              break;
            case key_ctrlL: //���������
              if(!select)
              {
                select=1;
                SelColEnd=79;
                SelColStart=0;
                SelPageStart=Page;
                SelPageEnd=Page;
                SelRowStart=Row;
                SelRowEnd=Row;
                SelPartStart=Part;
                SelPartEnd=Part;
                break;
              }
              else
              {
                SelRowEnd=Row;
                SelPageEnd=Page;
                SelPartStart=Part;
                SelPartEnd=Part;
                if(SelRowEnd<SelRowStart)
                {
                  y=SelRowEnd;
                  SelRowEnd=SelRowStart;
                  SelRowStart=y;
                }
                if(SelPageEnd<SelPageStart)
                {
                  p=SelPageEnd;
                  SelPageEnd=SelPageStart;
                  SelPageStart=p;
                }
                if(SelPartEnd<SelPartStart)
                {
                  p=SelPartEnd;
                  SelPartEnd=SelPartStart;
                  SelPartStart=p;
                }
              }
              break;
            case key_ctrlB:  //���������
              if(!select)
              {
                select=1;
                SelColEnd=Col;
                SelColStart=Col;
                SelPageStart=Page;
                SelPageEnd=Page;
                SelRowStart=Row;
                SelRowEnd=Row;
                SelPartStart=Part;
                SelPartEnd=Part;
                break;
              }
              else
              {
                SelColEnd=Col;
                SelRowEnd=Row;
                SelPageEnd=Page;
                SelPartStart=Part;
                SelPartEnd=Part;
                if(SelColEnd<SelColStart)
                {
                  x=SelColEnd;
                  SelColEnd=SelColStart;
                  SelColStart=x;
                }
                if(SelRowEnd<SelRowStart)
                {
                  y=SelRowEnd;
                  SelRowEnd=SelRowStart;
                  SelRowStart=y;
                }
                if(SelPageEnd<SelPageStart)
                {
                  p=SelPageEnd;
                  SelPageEnd=SelPageStart;
                  SelPageStart=p;
                }
                if(SelPartEnd<SelPartStart)
                {
                  p=SelPartEnd;
                  SelPartEnd=SelPartStart;
                  SelPartStart=p;
                }
              }
              break;

            case 13:    //������� �� ����� ������
              if(insert)
              {
                Row++;
                InsertString();
              }
              else
              {
                Col=0;
                Row++;
              }
              if(Row>=22)
              {
                Page++;
                Row=0;
                if(Page>CountPages)
                {
                  CountPages++;
                  if(CountPages>MAXPAGECOUNT)
                    CountPages=MAXPAGECOUNT;
                }
              }
              break;
            case 0:         //��������������� �������
              switch(getch())
              {
                case key_altF4: //�����
                  ExitProgram();
                  break;
                case key_F1: //����� �������
                  SaveFile(filename);
                  if(LoadFile(HelpFile))
                  {
                     strcpy(oldfile,filename);
                     strcpy(filename,HelpFile);
                  }
                  select=0;
                  break;
                case key_altF3: //�������� ������ ���������
                  New();
                  strcpy(oldfile,filename);
                  strcpy(filename,"noname.txt");
                  break;
                case key_F2://���������� �������� ���������
                  if(strcmp(filename,"noname.txt")!=0)
                  {
                    if(!CountPart) SaveFile(filename);
                    else           GetFullFile(filename);
                    modify=0;
                    break;
                  }
                case key_altF2:  //��������� � ��������� ����
                  HintView(SAVEHINT);
                  textbackground(2);
                  textcolor(15);
                  gotoxy(1,24);
                  cprintf("save ");
                  cgets(comm);
                  textbackground(0);
                  gotoxy(1,25);
                  clreol();
                  if(comm[2]==0) break;
                  //������� ������
                  for(err=0; err<strlen(comm);err++)
                    comm[err]=comm[err+2];
                  strcpy(filename,comm);
                  if(!CountPart) SaveFile(filename);
                  else           GetFullFile(filename);
                  modify=0;
                  select=0;
                  break;
                case key_F3:    //��������
                  HintView(LOADHINT);
                  textbackground(2);
                  textcolor(15);
                  gotoxy(1,24);
                  cprintf("load ");
                  cgets(comm);
                  textbackground(0);
                  gotoxy(1,25);
                  clreol();
                  if(comm[2]==0) break;
                  //������� ������
                  for(err=0; err<strlen(comm);err++)
                    comm[err]=comm[err+2];
                  select=0;
                  GetPartFile(comm);
                  if(CountPart>0)
                  {
                    Part=CountPages;
                    strcpy(oldfile,filename);
                    strcpy(filename,comm);
                    strcpy(comm,"c:\\iveditor\\part_0.txt");
                    LoadFile(comm);
                    CountPages=Part;
                    Part=0;
                  }
                  else
                  {
                    if(LoadFile(comm))
                    {
                      strcpy(oldfile,filename);
                      strcpy(filename,comm);
                    }
                  }
                  TabToSpace();
                  break;
                case key_F4: //������� �� ��������
                  HintView(GOTOHINT);
                  textbackground(2);
                  textcolor(15);
                  gotoxy(1,24);
                  cprintf("goto ");
                  cgets(comm);
                  textbackground(0);
                  gotoxy(1,25);
                  clreol();
                 if(comm[2]==0) break;
                  //������� ������
                  for(err=0; err<strlen(comm);err++)
                    comm[err]=comm[err+2];
                  GoTo(atoi(comm));
                  break;
                case key_F5: //��\���� �������������
                  graphmode=!graphmode;
                  break;
                case key_F6: //����� ���������
                  if(doscode) { DosToWin(); doscode=0;}
                  else        { WinToDos(); doscode=1;}
                  modify=1;
                  select=0;
                  break;
                case key_F7:  //��������� �����
                  if(strlen(findstr)>0)
                  {
                    Find(findstr);
                    break;
                  }
                case key_altF7: //�����
                  select=0;
                  HintView(FINDHINT);
                  textbackground(2);
                  textcolor(15);
                  gotoxy(1,24);
                  cprintf("find ");
                  cgets(comm);
                  textbackground(0);
                  gotoxy(1,25);
                  clreol();
                  if(comm[2]==0) break;
                  //������� ������
                  for(err=0; err<strlen(comm);err++)
                    comm[err]=comm[err+2];
                  strcpy(findstr,comm);
                  Find(findstr);
                  break;
                case key_F8: //��������� ������
                  if(strlen(findstr)>0&&strlen(replacestr)>0)
                  {
                    Replace(findstr,replacestr);
                    break;
                  }
                case key_altF8: //������
                  select=0;
                  HintView(REPLACEHINT);
                  textbackground(2);
                  textcolor(15);
                  gotoxy(1,24);
                  cprintf("replace ");
                  cgets(comm);
                  textbackground(0);
                  gotoxy(1,25);
                  clreol();
                  if(comm[2]==0) break;
                  //������� ������
                  for(err=0; err<strlen(comm);err++)
                    comm[err]=comm[err+3];
                  comm[strlen(comm)-1]=0;
                  err=0;
                  while(comm[err]!='\"')
                  {
                    comm2[err]=comm[err];
                    err++;
                  }
                  err=0;
                  while(err<strlen(comm))
                  {
                    comm[err]=comm[err+strlen(comm2)+3];
                    err++;
                  }
                  strcpy(findstr,comm2);
                  strcpy(replacestr,comm);
                  Replace(findstr,replacestr);
                  break;
               case key_F9:      //��������� ��������
                  OptionsChange();
                  break;
               case key_F10://������ � ���������� ����
                  select=0;
                  if(!CountPart) SaveFile(filename);
                  else           GetFullFile(filename);
                  GetPartFile(oldfile);
                  if(!CountPart)
                  {
                    if(!LoadFile(oldfile))
                    {
                      HintView(FILENOTFOUND);
                      break;
                    }
                  }
                  else
                  {
                    LoadFile("c:\\iveditor\\part_0.txt");
                    Part=0;
                  }
                  strcpy(comm,filename);
                  strcpy(filename,oldfile);
                  strcpy(oldfile,comm);
                  break;
                case key_Ins:  //�������\������
                  insert=!insert;
                  break;
                case key_Left: //������ �����
                  if(Col>0) Col--;
                  break;
                case key_Right://������ ������
                  if(Col<79&&Text[Page][Row][Col]!=0) Col++;
                  if(Text[Page][Row][Col]==0&&
                     Text[Page][Row][Col-1]!='\n')
                     Text[Page][Row][Col]='\n';
                  if(Text[Page][Row][Col]=='\n')
                  {
                     if(Text[Page][Row+1][0]!=0x1a&&
                        Text[Page][Row+1][0]!=0) Row++;
                     if(Row>22)
                     {
                       p=(CountPages<MAXPAGECOUNT)?(CountPages):(MAXPAGECOUNT);
                       if(Page<p)
                         Page++;
                       if(Page==p&&Part<CountPart)
                       {
                         sprintf(comm2,"c:\\iveditor\\part_%d.txt",Part);
                         SaveFile(comm2);
                         Part++;
                         sprintf(comm2,"c:\\iveditor\\part_%d.txt",Part);
                         LoadFile(comm2);
                       }
                       Row=0;
                     }
                     if(!Text[Page][Row+1][0]) Col=0;
                  }
                  break;
                case key_Up:   //������ �����
                  Row--;
                  if(Row<0)
                  {
                    Row=21;
                    if(Page==0) Row=0;
                    if(Page>0) Page--;
                    if(Page==0&&Part>0)
                    {
                      sprintf(comm2,"c:\\iveditor\\part_%d.txt",Part);
                      SaveFile(comm2);
                      Part--;
                      sprintf(comm2,"c:\\iveditor\\part_%d.txt",Part);
                      LoadFile(comm2);
                      Page=MAXPAGECOUNT-1;
                      Row=21;
                    }

                  }
                  if(Text[Page][Row][Col]==0)
                    Col=strlen(Text[Page][Row])-1;
                  break;
                case key_Down:   //������ ����
                  if(Text[Page][Row+1][0]!=0&&Text[Page][Row+1][0]!=0x1a)
                    Row++;
                  if(Row>21)
                  {
                    Row=0;
                    p=(CountPages<MAXPAGECOUNT)?(CountPages):(MAXPAGECOUNT);
                    if(Page<p)
                      Page++;
                    if(Page==p&&Part<CountPart)
                    {
                      sprintf(comm2,"c:\\iveditor\\part_%d.txt",Part);
                      SaveFile(comm2);
                      Part++;
                      sprintf(comm2,"c:\\iveditor\\part_%d.txt",Part);
                      LoadFile(comm2);
                    }

                  }
                  if(Text[Page][Row][Col]==0)
                    Col=strlen(Text[Page][Row])-1;
                  break;
                case key_PgUp: //�������� �����
                  if(Page>0) Page--;
                  if(Page==0&&Part>0)
                  {
                    sprintf(comm2,"c:\\iveditor\\part_%d.txt",Part);
                    SaveFile(comm2);
                    Part--;
                    sprintf(comm2,"c:\\iveditor\\part_%d.txt",Part);
                    LoadFile(comm2);
                    Page=MAXPAGECOUNT-1;
                  }
                  if(Text[Page][Row][Col]==0)
                    Col=strlen(Text[Page][Row])-1;
                  break;
                case key_PgDn: //�������� ����
                  p=(CountPages<MAXPAGECOUNT)?(CountPages):(MAXPAGECOUNT);
                  if(Page<p)
                    Page++;
                  if(Page==p&&Part<CountPart)
                  {
                    sprintf(comm2,"c:\\iveditor\\part_%d.txt",Part);
                    SaveFile(comm2);
                    Part++;
                    sprintf(comm2,"c:\\iveditor\\part_%d.txt",Part);
                    LoadFile(comm2);
                  }
                  if(Text[Page][Row][Col]==0)
                    Col=strlen(Text[Page][Row])-1;
                  break;
                case key_Home: //������ ������
                  Col=0;
                  break;
                case key_End:  //� ����� ������
                  Col=strlen(Text[Page][Row])-1;
                  break;
                case key_ctrlHome:   //� ������ ���������
                  if(CountPages<MAXPAGECOUNT)
                    Page=0;
                  else
                  {
                    sprintf(comm2,"c:\\iveditor\\part_%d.txt",Part);
                    SaveFile(comm2);
                    Part=0;
                    sprintf(comm2,"c:\\iveditor\\part_%d.txt",Part);
                    LoadFile(comm2);
                    Page=0;
                  }
                  Col=0;
                  Row=0;
                  break;
                case key_ctrlEnd:   //� ����� ���������
                  if(CountPages<MAXPAGECOUNT)
                    Page=CountPages;
                  else
                  {
                    sprintf(comm2,"c:\\iveditor\\part_%d.txt",Part);
                    SaveFile(comm2);
                    Part=CountPart;
                    sprintf(comm2,"c:\\iveditor\\part_%d.txt",Part);
                    LoadFile(comm2);
                    Page=CountPages-MAXPAGECOUNT*Part;
                  }
                  Col=0;
                  Row=0;
                  while(Text[Page][Row][Col]!=0) Row++;
                  break;
                case key_Delete:    //��������
                  if(!insert) FillSpace();
                  else        DelSelection();
                  modify=1;
                  if(Text[Page][Row][0]=='\n')
                    DelString();
                  else
                    chrdel(Text[Page][Row],Col);
                  break;
                case key_shiftF1:  //�������� C �����
                  New();
                  strcpy(oldfile,filename);
                  strcpy(filename,"noname.c");
                  strcpy(Text[0][0],"//IvEditor C file\n");
                  strcpy(Text[0][1],"#include <stdio.h>\n");
                  strcpy(Text[0][2],"int main(int argc, char *argv[])\n");
                  strcpy(Text[0][3],"{\n");
                  strcpy(Text[0][4],"     \n");
                  strcpy(Text[0][5],"     return 0;\n");
                  strcpy(Text[0][6],"}\n");
                  Col=5;
                  Page=0;
                  Row=4;
                  break;
                case key_shiftF2:   //�������� ��������
                  for(x=0; x<6; x++)
                    InsertString();
                  strcpy(Text[Page][Row+1],"     if(  ){\n");
                  strcpy(Text[Page][Row+2],"       \n");
                  strcpy(Text[Page][Row+3],"     }else{\n");
                  strcpy(Text[Page][Row+4],"       \n");
                  strcpy(Text[Page][Row+5],"     }\n");
                  Row++;
                  Col=9;
                  break;
                case key_shiftF3:   //������������ ����
                  for(x=0; x<3; x++)
                    InsertString();
                  strcpy(Text[Page][Row+1],"     while(  ){\n");
                  strcpy(Text[Page][Row+2],"       \n");
                  strcpy(Text[Page][Row+3],"     }\n");
                  Row++;
                  Col=12;
                  break;
                case key_shiftF4:   //���� � ������������
                  for(x=0; x<4; x++)
                    InsertString();
                  strcpy(Text[Page][Row+1],"     do{\n");
                  strcpy(Text[Page][Row+2],"       \n");
                  strcpy(Text[Page][Row+3],"     }while(  );\n");
                  Row+=2;
                  Col=8;
                  break;
                case key_shiftF5:   //��������� ����
                  for(x=0; x<3; x++)
                    InsertString();
                  strcpy(Text[Page][Row+1],"     for( ; ; ){\n");
                  strcpy(Text[Page][Row+2],"       \n");
                  strcpy(Text[Page][Row+3],"     }\n");
                  Row++;
                  Col=10;
                  break;
                case key_shiftF6:   //�������� ��������
                  for(x=0; x<6; x++)
                    InsertString();
                  strcpy(Text[Page][Row+1],"     switch(  ){\n");
                  strcpy(Text[Page][Row+2],"       case  :\n");
                  strcpy(Text[Page][Row+3],"         break;\n");
                  strcpy(Text[Page][Row+4],"       default:\n");
                  strcpy(Text[Page][Row+5],"         break;\n");
                  strcpy(Text[Page][Row+6],"     }\n");
                  Row++;
                  Col=12;
                  break;
                case key_shiftF7:   //���������� ���������
                  for(x=0; x<3; x++)
                    InsertString();
                  strcpy(Text[Page][Row+1],"     struct {\n");
                  strcpy(Text[Page][Row+2],"       \n");
                  strcpy(Text[Page][Row+3],"     };\n");
                  Row+=2;
                  Col=8;
                  break;
               case key_shiftF8:  //�������������� � ��������
                  textupr();      //��������
                  modify=1;
                  break;
               case key_shiftF9:  //�������������� � �������
                  textlwr();      //��������
                  modify=1;
                  break;
               case key_shiftF10: //�������������� "����� �
                  textword();     //� ������� �����"
                  modify=1;
                  break;
               
              }
              break;

            case key_Esc:    //�����
              ExitProgram();
              break;
            default:
              modify=1;
              if(select)
              {
                DelSelection();
                Col=SelColStart;
                Row=SelRowStart;
                Page=SelPageStart;
              }
              select=0;
              if(graphmode) key=Graph(key);
              if(insert)
              {
                 err=strlen(Text[Page][Row]);
                 while(err>=Col)
                 {
                   Text[Page][Row][err+1]=Text[Page][Row][err];
                   err--;
                 }
              }
              Text[Page][Row][Col]=key;
              Col++;
              if(Col>=80)
              {
                Row++;
                Col=0;
                if(Row>=22)
                {
                  Row=0;
                  p=(CountPages<MAXPAGECOUNT)?(CountPages):(MAXPAGECOUNT);
                  if(Page<p)
                    Page++;
                  if(Page==p&&Part<CountPart)
                  {
                    sprintf(comm2,"c:\\iveditor\\part_%d.txt",Part);
                    SaveFile(comm2);
                    Part++;
                    sprintf(comm2,"c:\\iveditor\\part_%d.txt",Part);
                    LoadFile(comm2);
                  }
                  
                }


              }
              break;
          }
        }while(1);
        return 0;
}
//---------------------------------------------------------------------------




