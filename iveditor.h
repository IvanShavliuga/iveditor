#ifndef iveditorH
#define iveditorH

#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>
#include <dir.h>

//����� 䠩��� IvEditor
#define HelpFile     "c:\\IvEditor\\help.txt"
#define OptionsFile  "c:\\IvEditor\\options.dat"
// ��ப� ���᪠���
// ��� ����䥩� � ���짮��⥫��
#define FILENOTFOUND  "���� �� ������"
#define FILECHANGE    "���� �������, ��࠭��� (Y/N)?"
#define PLEASEWAIT    "�������� ��������..."
#define NOTMEMORY     "�� 墠⠥� �����"
#define EXITYESNO     "�� ����⢨⥫쭮 ��� ���? (Y/N)"
#define NOTFILLBUF    "���� ����"
#define AUTOSAVE      "�����࠭����"
#define STRNOFOUND    "��ப� �� �������"
#define GOTOHINT      "goto <����� ��࠭���>"
#define SAVEHINT      "save <��� 䠩��>"
#define LOADHINT      "load <��� 䠩��>"
#define FINDHINT      "find <��ப� ᨬ�����>"
#define REPLACEHINT   "replace <\"���� ��ப�\"> <\"����� ��ப�\">"
#define NORMALTEXT    "⥪��"
#define GRAPHICS      "���"
#define INSERT        "���"
#define OWERTYPE      "���" 		
//���� ������
#define key_F1        59
#define key_F2        60
#define key_F3        61
#define key_F4        62
#define key_F5        63
#define key_F6        64
#define key_F7        65
#define key_F8        66
#define key_F9        67
#define key_F10       68
#define key_Home      71
#define key_End       79
#define key_Left      75
#define key_Right     77
#define key_Up        72
#define key_Down      80
#define key_PgUp      73
#define key_PgDn      81
#define key_Esc       27
#define key_BSpace    8
#define key_Tab       9
#define key_ShiftTab  15
#define key_Delete    83
#define key_Ins       82
#define key_ctrlHome  119
#define key_ctrlEnd   117
#define key_ctrlLeft  115
#define key_ctrlRight 116
#define key_ctrlUp    141
#define key_ctrlDown  145
#define key_ctrlPgUp  132
#define key_ctrlPgDn  118
#define key_ctrlA     1
#define key_ctrlB     2
#define key_ctrlC     3
#define key_ctrlD     4
#define key_ctrlL     12
#define key_ctrlN     14
#define key_ctrlV     22
#define key_ctrlX     24
#define key_altF1     104
#define key_altF2     105
#define key_altF3     106
#define key_altF4     107
#define key_altF5     108
#define key_altF6     109
#define key_altF7     110
#define key_altF8     111
#define key_altF9     112
#define key_altF10    113
#define key_altUp     152
#define key_altDown   160
#define key_altLeft   155
#define key_altRight  157
#define key_shiftF1   84
#define key_shiftF2   85
#define key_shiftF3   86
#define key_shiftF4   87
#define key_shiftF5   88
#define key_shiftF6   89
#define key_shiftF7   90
#define key_shiftF8   91
#define key_shiftF9   92
#define key_shiftF10  93

#define MAXPAGECOUNT 300
//�������� ��६����
unsigned char Text[MAXPAGECOUNT][22][80];//������ ��� ⥪��
unsigned char *buffer;
unsigned char bufx;
char filename[80];              //��� 䠩��
char oldfile[80];               //�।��騩 䠩�
char findstr[80];               //��ப� ��� ���᪠
char replacestr[80];            //��ப� ��� ������
unsigned long int CountPages;   //������⢮ ��࠭�� �
unsigned long int CountPart;    //
unsigned long int Part;
unsigned long int SelPartStart;
unsigned long int SelPartEnd;
char Col,Row;                   //�������, ��ப�
int Page;                       //��࠭��
char SelColStart, SelRowStart;  //�뤥����� ���. ������� ���. ��ப�
int SelPageStart;				//�뤥����� ���. ��࠭����
char TabSize;                   //������ ⠡��樨
char SelColEnd,SelRowEnd;       //�뤥����� ���. ������� ���. ��ப�
int SelPageEnd;					//�뤥����� ���. ��࠭���
char select;					//䫠�: ���� �뤥�����?
char modify;                    //���� ��������� ���㬥��
char insert;                    //����� ��⠢��
char autosave;					//�६� �����࠭����
int  Digit;						//���� ���
int  Background;				//���� 䮭� �᭮����� ⥪��
int  Selground;					//���� 䮭� �뤥�塞��� ⥪��
int  Lat;						//���� ��⨭᪨� ᨬ�����
int  Other;						//���� ��⠫��� ᨬ�����
char graphmode;                 //����� �ᥢ����䨪�
char doscode;                   //Dos - 1, Win - 0
char RedString;                 //����� "��᭮� ��ப�"
void New();                     //�㭪�� ᮧ����� ���㬥��
void FileChange();              //�㭪�� �஢�ન: ������� 䠩�?
void __fastcall Print(void);    //�㭪�� �뢮�� ⥪�� �� �࠭
void SaveFile(char *);          //�㭪�� ��࠭���� ���㬥��
int  LoadFile(char *);          //����㧪� 䠩��
void ExitProgram(void);         //������������� ��室 �� �ணࠬ��
void Find(char *);              //���� ��ப� � ⥪��
void GoTo(int);                 //���室 �� ��࠭���
void InsertString(void);        //��⠢�� ��ப� � ⥪��
void DosToWin(void);            //��ॢ�� ����஢�� �� Dos � Windows
void WinToDos(void);            //��ॢ�� ����஢�� �� Windows � Dos
void chrdel(char [], int);      //�������� ᨬ���� �� ��ப�
void chrndel(char [], int, int);//�������� n ᨬ����� �� ��ப�
void chrins(char [],int,int);   //��⠢��� ᨬ���
void strins(char [],int,char []);//��⠢��� ��ப�
void Replace(char *,char *);    //������
void TabToSpace(void);          //���� � �஡���
void SpaceToTab(void);          //�஡��� � ⠡�
void stricpy(char [],char [],int,int);//����஢���� ��ப� � � ���. i
void FillSpace(void);			//��������� �뤥������ ������� ' '
void DelSelection();			//������� �뤥�����
void CopySelection(void);		//�����஢��� �뤥�����
void CutSelection(void);		//��१��� �뤥�����
void Paste(void);				//��⠢���
void OptionsChange();			//����� ���� ��������� ����஥�
void OptionsLoad();				//����㧪� ����஥�
void OptionsSave();				//���࠭���� ����஥�
void DelString();				//�������� ��ப�
char * GetNameFile(char *);     //����砥� ��� 䠩��
char Graph(char	);				//�८�ࠧ���⥫� ��� �ᥢ����䨪�
void textupr(void);				//�८�ࠧ����� � ����孨� ॣ����
void textlwr(void);             //�८�ࠧ���⥫� � ������ ॣ����
void textword(void);            //����� � ����让 �㪢�
void GetPartFile(char *);
void GetFullFile(char *);
void HintView(char *);
//-------------------------------------------------------------------

#endif
