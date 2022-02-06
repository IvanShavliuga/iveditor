#ifndef iveditorH
#define iveditorH

#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>
#include <dir.h>

//Имена файлов IvEditor
#define HelpFile     "c:\\IvEditor\\help.txt"
#define OptionsFile  "c:\\IvEditor\\options.dat"
// Строки подсказки
// для интерфейса с пользователем
#define FILENOTFOUND  "Файл не найден"
#define FILECHANGE    "Файл изменен, сохранять (Y/N)?"
#define PLEASEWAIT    "Пожалуйста подождите..."
#define NOTMEMORY     "Не хватает памяти"
#define EXITYESNO     "Вы действительно хотите выйти? (Y/N)"
#define NOTFILLBUF    "Буфер пуст"
#define AUTOSAVE      "Автосохранение"
#define STRNOFOUND    "Строка не найдена"
#define GOTOHINT      "goto <номер страницы>"
#define SAVEHINT      "save <имя файла>"
#define LOADHINT      "load <имя файла>"
#define FINDHINT      "find <строка символов>"
#define REPLACEHINT   "replace <\"старая строка\"> <\"новая строка\">"
#define NORMALTEXT    "текст"
#define GRAPHICS      "Граф"
#define INSERT        "Вст"
#define OWERTYPE      "Зам" 		
//Коды клавиш
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
//Глобальные переменные
unsigned char Text[MAXPAGECOUNT][22][80];//память под текст
unsigned char *buffer;
unsigned char bufx;
char filename[80];              //имя файла
char oldfile[80];               //предыдущий файл
char findstr[80];               //строка для поиска
char replacestr[80];            //строка для замены
unsigned long int CountPages;   //Количество страниц в
unsigned long int CountPart;    //
unsigned long int Part;
unsigned long int SelPartStart;
unsigned long int SelPartEnd;
char Col,Row;                   //Колонка, строка
int Page;                       //страница
char SelColStart, SelRowStart;  //выделение нач. колонка нач. строка
int SelPageStart;				//выделение нач. странницы
char TabSize;                   //Размер табуляции
char SelColEnd,SelRowEnd;       //выделение кон. колонка кон. строка
int SelPageEnd;					//выделение кон. страницы
char select;					//флаг: есть выделение?
char modify;                    //Флаг изменения документа
char insert;                    //Режим вставки
char autosave;					//Время автосохранения
int  Digit;						//Цвет цифр
int  Background;				//Цвет фона основного текста
int  Selground;					//Цвет фона выделяемого текста
int  Lat;						//Цвет латинских символов
int  Other;						//Цвет остальных символов
char graphmode;                 //Режим псевдографики
char doscode;                   //Dos - 1, Win - 0
char RedString;                 //Длина "Красной строки"
void New();                     //Функция создания документа
void FileChange();              //Функция проверки: изменен файл?
void __fastcall Print(void);    //Функция вывода текста на экран
void SaveFile(char *);          //Функция сохранения документа
int  LoadFile(char *);          //Загрузка файла
void ExitProgram(void);         //Цивилизованный выход из программы
void Find(char *);              //Поиск строки в тексте
void GoTo(int);                 //Переход на страницу
void InsertString(void);        //Вставка строки в текст
void DosToWin(void);            //Перевод кодировки из Dos в Windows
void WinToDos(void);            //Перевод кодировки из Windows в Dos
void chrdel(char [], int);      //Удаление символа из строки
void chrndel(char [], int, int);//Удаление n символов из строки
void chrins(char [],int,int);   //Вставить символ
void strins(char [],int,char []);//Вставить строку
void Replace(char *,char *);    //замена
void TabToSpace(void);          //Табы в пробелы
void SpaceToTab(void);          //Пробелы в табы
void stricpy(char [],char [],int,int);//Копирование строки с с поз. i
void FillSpace(void);			//Заполнить выделенную область ' '
void DelSelection();			//Удалить выделение
void CopySelection(void);		//Скопировать выделение
void CutSelection(void);		//Вырезать выделение
void Paste(void);				//Вставить
void OptionsChange();			//Запуск окна изменения настроек
void OptionsLoad();				//Загрузка настроек
void OptionsSave();				//Сохранение настроек
void DelString();				//Удаление строки
char * GetNameFile(char *);     //Получает имя файла
char Graph(char	);				//Преобразователь для псевдографики
void textupr(void);				//Преобразовать в вверхний регистер
void textlwr(void);             //Преобразователь в нижний регистер
void textword(void);            //Слова с большой буквы
void GetPartFile(char *);
void GetFullFile(char *);
void HintView(char *);
//-------------------------------------------------------------------

#endif
