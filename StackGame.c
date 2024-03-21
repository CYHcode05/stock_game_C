#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>
#include "article.h"

#define STOCK_COUNT 8
#define START_MONEY 10000
#define TAX(money) (30000+(money)/4)
/***************************************구조체************************************************/
struct STOCK
{
    char* companyname; //주식이름
    int stockprice; // 주식가격
    int prevprice;// 1시간전 주식가격
    int prevprve; // 2시간전 주식가격
    int amount; // 주식수량
    int goodnews; //좋은뉴스
    int good_event//이벤트
};
typedef struct STOCK s_STOCK_type;


 s_STOCK_type stock[STOCK_COUNT] = { 
    {"samsung"}, {"LG"}, {"Amazon"}, {"Google"}, {"bitcoin"}, {"Aferica"}, {"twitch"}, {"Nexon"}
 };
s_STOCK_type *p_stock = stock;

/*************************************전역변수************************************************/
long long int money = 0, loan = 0,aimoney =30000;
int mystock = 0;
int want_buy = 0;
int month = 0, day = 0, hour = 0;
int aistock[STOCK_COUNT] = { 0, };
int aibuypoint[STOCK_COUNT] = { 0, };
int* paistock = aistock;
int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
int airand = 0;
int setspeed = 50;
/***********************************기본적으로쓰일것들*****************************************/
void gotoxy(int x, int y)//커서이동
{
 COORD pos = { x, y };
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void textcolor(int color_number)//글자색변경/////초록 2 빨강 4----검정 7----- 연초록 10 연빨강 14
{
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}
typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

void setcursortype(CURSOR_TYPE c)//커서타입변경. NOSURSUR만쓸거임
{
 CONSOLE_CURSOR_INFO CurInfo;
 switch (c)
 {
 case NOCURSOR:
  CurInfo.dwSize = 1;
  CurInfo.bVisible = FALSE;
  break;
 case SOLIDCURSOR:
  CurInfo.dwSize = 100;
  CurInfo.bVisible = TRUE;
  break;
 case NORMALCURSOR:
  CurInfo.dwSize = 20;
  CurInfo.bVisible = TRUE;
  break;
 }
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

void clrscr(void)//화면지우기
{
 system("cls");
}

int getkey(char* c)//키입력
{
 if (_kbhit())
 {
  *c = _getch();
  return 0;
 }
 return 1;
}

void clearbuffer()
{
 while (_kbhit())
 {
  _getch();
 }
 return 0;
}

void title(char* title)
{
 clrscr();
 int i;
 printf("\n %s \n", title);
 for (i = 0; i < 40; i++)
 {
  printf("-");

 }
 printf("\n");

}

/********************************************************************************************************/


/******************************************함수정의****************************************************/

void f_save();//저장
void f_load();//로딩
void f_startlogo();//시작화면
void f_loan(long long int loan_money);//빚
void f_loanmenu();//빚 빌리는데
void f_mainmenu();//메인메뉴
void f_stock_price_change();//주식가격변동
void f_game_reset();//초기화세팅
void f_interest();//이자
void f_setting();//설정
void f_setgamespeed();//게임속도
void f_buy_stock(int want_buy, int amount);//주식구매
void f_sell_stock(int amount);//주식판매
void f_bring_stock();//보유 주식
void f_startmain(); //주식회사 및 가격변동(증감 표시X)
void f_print_stock_price(int choice);//주식가격출력
void f_draw_newspaper(int choice);//주식 뉴스출력
void f_payback();//돈갚기
void f_show_stock_price();//주식가격 메인화면 출력
void f_buy_menu(int choice);//구매메뉴
void f_sell_menu(int choice);//판매메뉴
void f_showstock();//보유주식들
void f_showstat();//스탯
void f_newsmenu(int choice);//뉴스
void f_aibuystock(int aichoice, int price, int amount);//AI주식구매
void f_aisellstock(int aichoice, int price, int amount);//AI주식판매
void f_showaistat();//AI상태 보기


/******************************************메인함수*****************************************************/
int main(void)
{
 srand(time(NULL));
 int i = 0, menu = 0, pausemenu;
 char menu = 0;
 char select ='\0';
 int cnt = 0;
 cnt = month = day = hour = 0;

do{
    clrscr();
    f_startlogo();//시작화면
    scanf_s("%d", &menu,sizeof(menu));

    f_game_reset();//게임초기화
    clrscr();
    f_loan(20000);//대출
    switch(menu)
    {
        case 1:
        f_stock_price_change();//주식가격변동
        f_save();//저장

        for(i=1; i<STOCK_COUNT; i++)
        {
            if(rand()%3 == 0)
            {
                (p_stock+i)->goodnews = true;
            }
            else
            {
                (p_stock+i)->goodnews = false;
            }
        }
        break;

        case 2:
        f_load();//로딩
        break;

        case 3:
        exit(0);
        break;   

        default:
        {
            continue;
        }
    }
    break;
}while (1);
clrscr();

f_draw_newspaper(want_buy);

while(1)
{
    f_mainmenu();//메인메뉴
    f_newsmenu(want_buy);//뉴스

    if(money)
    {
        clrscr();
        printf("GG");
        system("pause");
        exit(1);
    }

    gotoxy(52,9 + want_buy);
    printf(" ");

    gotoxy(52,10 + want_buy);
    printf("<");

    gotoxy(52,11 + want_buy);
    printf(" ");
    select = '\0';

    switch (select)
    {
        case 'b':
        case 'B':
        {
        f_buy_menu(want_buy);
        break;
        }

        case 27://esc
        {
        clrscr();
        title("일시정지");
        printf("1. 통계\n\n 2. 대출\n\n 3. 갚기\n\n 4. 설정\n\n 5. 끝내기\n\n Esc. 계속하기\n\n");

        pausemenu = _getch();

        switch(pausemenu)
        {
            case 1://통계
            {
                f_showstat();
                break;
            }

            case 2://대출
            {
                f_loanmenu();
                break;
            }

            case 3:// 갚기
            {
                f_payback();
                clrscr(); 
                break;
            }

            case 4:// 설정
            {
                f_setting();
                clrscr();
                break;
            }

            case 5:// 끝내기
            {
                exit(0);
                break;
            }

            case 27:// 계속하기
            {
                clrscr();
                break;
            }
            default:
            {
                break;
            }
            clrscr();
        } 
        break;
        }
        case 's':
        case 'S':// 판매 
        {
            f_sell_menu(want_buy);//판매메뉴
            break;
        }

        case 'e':
        case 'E'://저장
        {
            f_save();
            break;
        }  

        case '2':
        {
            if(want_buy < STOCK_COUNT - 1)
            {
                want_buy++;
            }
            f_draw_newspaper(want_buy);
            break;
        }
        
        case '8':
        {
            if(want_buy > 0)
            {
                want_buy--;
            }
            f_draw_newspaper(want_buy);
            break;
        }  
    } 
/**********************************************************************************************************/
    Sleep(1000/setspeed);
    cnt++;
    if(cnt%50 == 0)
    {
        for(i = 0; i<STOCK_COUNT; i++)
        {
            (p_stock+i)->prevprve = (p_stock+i)->prevprice;
            (p_stock+i)->prevprice = (p_stock+i)->stockprice;
        }
        hour++;
        f_stock_price_change();
    }   

    if(cnt % 50 == 0)// 1초 ai 주식 매입 메도(난이도 조절)
    {
        for(i = 0; i<STOCK_COUNT; i++)
        {
            airand = (rand() % 3 + 1);
            if(((p_stock + i)-> stockprice - (p_stock + i)->prevprice) >300)
            {
                f_aibuystock(i , (p_stock + i)->prevprice, airand);
            }
            else if(((p_stock + i)-> stockprice < (p_stock + i)->prevprice))
            {
                f_aisellstock(i, (p_stock + i)->prevprice, *(aistock + i +1));
            }       
        }
    }

    gotoxy(0,10);
    f_show_stock_price();//주식가격 메인화면 출력
    f_showaistat();//AI상태 보기

    if(hour == 0)
    {
        for(i=0; i<STOCK_COUNT; i++)
        {
            if(rand()%3 == 0)
            {
                if((p_stock+i)->good_event)
                {
                    (p_stock+i)->goodnews = true;
                }
            }
            else
            {
                (p_stock+i)->goodnews = false;
            }
        }
    }
    if(hour > 23)
    {
        f_save();
        hour = 0;
        f_interest();
        day++;
        srand((unsigned int) time(NULL));
    } 
    if(day > *(days + month)-1)
    {
        month++;
        day = 0;
        money -= TAX(money);
    }
    if(month > 11)
    {
        if(aimoney > money - loan)
        {
            title("당신은 실패했습니다.");
            printf("목표금액을 달성하지 못했습니다.\n");
        }
        else
        {
            title("축하합니다.");
            printf("당신은 목표금액을 달성했습니다.\n");
        }
    }
    month = 0;
    }
}
/**********************************************************************************************************/
void f_save()
{
    int i = 0;
    int a = 0;
    FILE* save = fopen("stock_save.txt", "w+");

    if(save == NULL)
    {
        printf("저장에 실패했습니다.\n");
        exit(1);
    }

    for(i=0; i<STOCK_COUNT; i++) //주식가격저장
    {
        fprintf(save, "%s:   %d\n",(p_stock+i)->companyname, (p_stock+i)->stockprice);
    }

   for(i=0; i<STOCK_COUNT; i++) //플레이오가 갖고 있는 주식
    {
        fprintf(save, "%s:   %d\n",(p_stock+i)->companyname, (p_stock+i)->amount);
    }

    for(i=0; i<STOCK_COUNT; i++) 
    {
        fprintf(save, "%s:   %d\n",(p_stock+i)->companyname, (p_stock+i)->prevprice);
    }
    for(i =0 ; i<STOCK_COUNT; i++)
        {
            fprintf(save, "%s:   %d\n",(p_stock+i)->companyname, (p_stock+i)->good_event);
        }

    for(i =0 ; i<STOCK_COUNT; i++)
        {
            fprintf(save, "%s:   %d\n",(p_stock+i)->companyname, (p_stock+i)->goodnews);
        }

    fprintf(save, "돈%lld\n", money);
    fprintf(save, "빚%lld\n", loan);
    fprintf(save, "보유주식개수: %d\n", mystock);
    fprintf(save, "월%d\n", month);
    fprintf(save, "일%d\n", day);
    fprintf(save, "시%d\n", hour);

    fclose(save);
}

void f_load()//불러오기
{
    int i = 0,j =0,k=0;
    long long int m = 0;
    FILE* save = fopen("stock_save.txt", "r+");

    char b[10] = "";
    char c[100] = "";
    long long int a = 0;

    for (i = 0; i<STOCK_COUNT; i++)
    {
        fscanf(save, "%s",c);
        fscanf(save, "%d", &j);
        fget(b , 10 ,save);
        (p_stock+i)->amount = j;
    }

    for(i=0; i<STOCK_COUNT; i++)
    {
        fscanf(save, "%s",c);
        fscanf(save, "%d", &j);
        fget(b , 10 ,save);
        (p_stock+i)->stockprice = j;
    }

    for(i=0; i<STOCK_COUNT; i++)
    {
        fscanf(save, "%s",c);
        fscanf(save, "%d", &j);
        fget(b , 10 ,save);
        (p_stock+i)->prevprice = j;
    }

    for(i=0; i<STOCK_COUNT; i++)
    {
        fscanf(save, "%s",c);
        fscanf(save, "%d", &j);
        fget(b , 10 ,save);
        (p_stock+i)->good_event = j;
    }

    for(i=0; i<STOCK_COUNT; i++)
    {
        fscanf(save, "%s",c);
        fscanf(save, "%d", &j);
        fget(b , 10 ,save);
        (p_stock+i)->goodnews = j;
    }

    fscanf(save, "%s",c);
    fscanf(save, "%lld", &m);
    fget(b , 10 ,save);

    money = m;

    fscanf(save, "%s",c);
    fscanf(save, "%lld", &m);
    fget(b , 10 ,save);
    loan = m;

    fscanf(save, "%s",c);
    fscanf(save, "%d", &j);
    fget(b , 10 ,save);
    mystock = j;

    fscanf(save, "%s",c);
    fscanf(save, "%d", &j);
    fget(b , 10 ,save);
    month = j;

    fscanf(save, "%s",c);
    fscanf(save, "%d", &j);
    fget(b , 10 ,save);
    day = j;

    fscanf(save, "%s",c);
    fscanf(save, "%d", &j);
    fget(b , 10 ,save);
    hour = j;

    fclose(save);
}

void f_startlogo()// 시작 로고
{
    printf("\t\t\t\t\t 1960012 김태호 1960052 추영호\n");
    printf("\t\t\t\t\t 사람 vs 컴퓨터 주식게임 \n");
    printf("1. 새로하기\n\n 2. 불러오기\n\n 3. 끝내기\n\n");
    printf("원하는 번호를 입력하세요: ");
}

void f_loan(long long int loan_money)//빚
{
    loan += loan_money;//대출금액
    money += loan_money;//돈
}

void f_payback()
{
    if(money >= loan)
    {
        money -= loan;
        loan = 0;
    }

    else
    {
        loan -= money; 
        money = 0;
    }
}

void f_loanmenu()//대출 화면
{
    long long int loan_money = 0;
    int check = 1;
    
    do
    {
        clrscr();
        title("대출");
        printf("대출금액을 입력하세요: ");
        scanf_s("%lld", &loan_money);

        if(loan_money == 0)
        {
            printf("대출금액을 입력하세요.최대한도 130만원\n");
            Sleep(500);

            loan_money = getchar();
            continue;
        }
        else
        {
            if(loan <= 1300000)
            {
                if(loan + loan_money <= 1300000)
                {
                    f_loan(loan_money);
                    check = 0;
                }
                else
                {
                    printf("대출한도 초과입니다.\n");
                    Sleep(500);
                }
            }
            else
            {
                printf("대출한도 초과입니다.\n");
                Sleep(500);
            }
        }

    }while(check);         
}

void f_mainmenu()//플레이어 상태창
{
    gotoxy(0,1);
    printf("\n B 사기, S 팔기, E 저장, 8 / 2 회사 선택, Esc 메뉴");
    gotoxy(0,3);
    printf("\n 현재 내 돈: %lld원,  갚아야 할 돈 : %lld원, 보유 주식 주:%d\n\n\n\n", money,loan, mystock);
    gotoxy(0,5);
    printf("현재 시간: %d월 %d일 %d시\n\n", month+1, day+1, hour);
    printf("\n\n 이번 달 납부할 세금은 %lld원 입니다. %d일 남았습니다\n", TAX(money),days[month]-day);
}

void f_startmain() //주식회사
{
    int i = 0;
    for(i = 0; i<STOCK_COUNT; i++)
    {
        printf("회사 : %+10s     가격|       %8d\n",(p_stock+i)->companyname, (p_stock+i)->stockprice);
    }
}

void f_newsmenu(int want_buy)
{
    gotoxy(76 ,2);
    printf("회사 : %8s\n", (p_stock + want_buy)->companyname);
    gotoxy(76, 4);
    printf("현재주가 : %10d\n", (p_stock + want_buy)->stockprice);
    gotoxy(76, 5);
    if((p_stock + want_buy)->goodnews)
    {
        printf("좋은 뉴스가 있습니다.\n");
    }
    else
    {
        printf("좋은 뉴스가 없습니다.\n");
    }
    printf("\n\n");
}

void f_stock_price_change()
{
    int i = 0;
    for(i = 0; i<STOCK_COUNT; i++)
    {
        if((p_stock +i)->goodnews && !(p_stock)->good_event)
        {
            if(rand()%2 == 0)
            {
                (p_stock + i)->stockprice += rand()%1300;
            }
            else
            {
                (p_stock + i)->stockprice -= rand()%100;
            }
        }
        else if((p_stock + i)->goodnews && (p_stock)->good_event)
        {
          (p_stock + i)->stockprice += rand()%2000;
        }

        else if(!(p_stock + i)->goodnews && !(p_stock)->good_event)
        {
            (p_stock + i)->stockprice += rand()%300;
        }
        else
        {
            (p_stock + i)->stockprice -= rand()%2000;
        }
        if((p_stock + i)->stockprice < 4000)
        {
            (p_stock + i)->goodnews = true;
        }
    }
}

void f_game_reset()
{
    int i = 0;
    money = START_MONEY;
    for(i = 0; i<STOCK_COUNT; i++)
    {
        (p_stock + i)->stockprice = 10000;
        (p_stock + i)->amount = 0;
        (p_stock + i)->goodnews = false;
        (p_stock + i)->good_event = false;
    }
    mystock = 0;
    loan = 0;
    hour++;
    f_stock_price_change();
    setcursortype(NOCURSOR);
}

void f_interest()
{
    if(loan)
    {
        loan += loan*0.1;
    }
}

void f_buy_stock(int want_buy, int amount)
{
    clrscr();

    int i = 0;
    for (i = 0; i <amount; i++)
    {
        if((p_stock + want_buy)->stockprice <= money)
        {
            mystock++;
            money -= (p_stock + want_buy)->stockprice;
            (p_stock + want_buy)->amount++;
        }
       
    }
}

void f_sell_stock(int amount)
{
   int i = 0;

   for (i = 0; i<STOCK_COUNT; i++)
   {
      if((p_stock + want_buy)->amount)
      {
            mystock--;
            money += (p_stock + want_buy)->stockprice;
            (p_stock + want_buy)->amount--;
      }
   }
}

void f_print_stock_price(int i)
{
    int max, min = 0;
    max = (p_stock +i) -> stockprice- (p_stock +i) -> prevprice;   
    min = (p_stock +i) -> prevprice- (p_stock +i) -> stockprice;

    printf(" 회사 : ");
    if(((p_stock +i)->prevprice<(p_stock+i)->stockprice))
    {
        textcolor(10);
        printf("%s", (p_stock +i)->companyname);
        textcolor(7);
    }
    else
    {
        textcolor(12);
        printf("%s", (p_stock +i)->companyname);
        textcolor(7);
    }

    printf("\t\t가격 : %8d원", (p_stock +i)->stockprice);

    if((p_stock +i)->prevprice<(p_stock+i)->stockprice)
    {
        textcolor(2);
        printf("\t▲%7d", max);
        textcolor(7);
    }
    else
    {
        textcolor(4);
        printf("\t▼%7d", min);
        textcolor(7);
    }

    max = min = 0;
    printf("\n");
}

void f_draw_newspaper(int choice)
{
    int i = 0, j =0;
    for(i= 0; i <20 ;i++)
    {
        gotoxy(70, 10+i);
        for(j=0;j<50;j++)
        {
            putchar(' ');
        }
    }

    gotoxy(80, 7);
    printf("신 문  %d월 %d일 ", month+1, day+1);
    gotoxy(70, 8);
    printf("======================================================================");

    gotoxy(70, 10);

    if((p_stock +choice)->goodnews == true)
    {
        printf(("%s%s"),(p_stock +choice)->companyname, Goodnews_Headline[rand()%MAX_headline]);
    }
    else{
        printf(("%s%s"),(p_stock +choice)->companyname, Badnews_Headline[rand()%MAX_headline]);
    }

    gotoxy(70, 12);

    if((p_stock+ choice)->goodnews == true)
    {
        int i =0, j = 0;
        int Artice_rand = rand() % MAX_Article;
        printf(("%s", p_stock + choice)->companyname);
        while(GoodArticle[Artice_rand][i] != '\0')
        {
           if(GoodArticle[Artice_rand][i] == '\n')
           {
               j++;
               gotoxy(70, 12+j);
           }
           else
           {
               putchar(GoodArticle[Artice_rand][i]);
           }
           i++;
        }
    }
    else
    {
        int i = 0,  j = 0;
        int Artice_rand = rand() % MAX_Article;
        printf("%s", (p_stock + choice)->companyname);
        while(BadArticle[Artice_rand][i] != '\0')
        {
            if(BadArticle[Artice_rand][i] == '\n')
            {
                j++;
                gotoxy(70, 12+j);
            }
            else
            {
                putchar(BadArticle[Artice_rand][i]);
            }
            i++;
        }
    }
}

void f_show_stock_price()
{
    int i = 0;
    for(i = 0; i<STOCK_COUNT; i++)
    {
        f_print_stock_price(i);
    }
}

void f_setting()
{
    char c = 0;
    title("설정");
    printf("1. 게임속도\n\n ");

    fflush(stdin);
    while(getkey(&c))
    {
       switch(c)
       {
           case '1':
           {
               f_setgamespeed();
               break;
           }
           default:
           {
               break;
           }
       }
    }
}

void f_setgamespeed()
{
    char c = 0;
    system("cls");
    title("게임속도");
    printf("1. 빠름\n\n 2. 보통\n\n 3. 느림\n\n");

    fflush(stdin);
    while(getkey(&c))
    {
        switch(c)
        {
            case '1':
            {
                setspeed = 100;
                break;
            }
            case '2':
            {
                setspeed = 50;
                break;
            }
            case '3':
            {
                setspeed = 25;
                break;
            }
        }
    }
}

void f_buy_menu(int choice)
{
    int amount = 0;
    char c = 0;
    title("구매");
    printf("현재 플레이어가 보유 금액은 %lld원 입니다.\n", money);
    printf("현재 %s 주식 가격 : %d\n\n",(p_stock + want_buy)->companyname ,(p_stock + choice)->stockprice);
    printf("구매할 주식의 수량을 입력하세요: ");
    scanf_s("%d", &amount);

    if(amount > 0)
    {
        printf("구매할 주식의 수량을 입력하세요.\n");
        
    }
    clrscr();
}

void f_sell_stock(int choice)
{
    int amount = 0;
    clrscr();
    title("판매");
    printf("현재 플레이어가 보유한 %s 주식은 %d개 입니다.\n",(p_stock + want_buy)->companyname ,(p_stock + choice)->amount);
    printf("판매할 주식의 수량을 입력하세요: ");
    scanf_s("%d", &amount);

    if(amount > 0)
    {
        printf("판매할 주식의 수량을 입력하세요.\n");
    }
    clrscr();
}

void f_showstat()
{
    int i = 0;
    clrscr();
    title("통계");
    printf("\n 현재 가진돈 :%lld, 주식개수:%d\n", money, mystock);
    for(i = 0; i<STOCK_COUNT; i++)
    {
        if((p_stock + i)->amount > 0)
        {
            printf("%s: %d개n", (p_stock + i)->companyname, (p_stock + i)->amount);
        }
    }
    getchar();
    clrscr();
}

void f_aibuystock(int aichoice, int price, int amount)
{
   int i =0;
   for(i = 0; i<amount; i++)
   {
       if(aimoney >=price)
       {
        (*(paistock + aichoice))++;
        aimoney -= price;
       }
   }
   *(aibuypoint+aichoice) = price;
}

void f_aisellstock(int aichoice, int price, int amount)
{
    int i = 0;
    for(i = 0; i<amount; i++)
    {
        if(*(paistock + aichoice)>0 && *(aibuypoint + aichoice) < price)
        {
            (*(paistock + aichoice))--;
            aimoney += price;
        }
    }
}

void f_showaistat()
{
    printf("\n\n\n");
    printf("AI가 가진 돈 : %lld\n", aimoney);
    for(int i = 0; i<STOCK_COUNT; i++)
    {
        if(*(paistock + i) != 0)
        {
            printf("AI 보유주식 %s: %d개\n", (p_stock + i)->companyname, *(paistock + i));
        }
    }
}
