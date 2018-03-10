/******************************
Write By XPF:
Time :2018.01.13
key:  1,2,3,...m
child:0,1,2,3..m
//
���棺���²��֣���λ��꣬��������ʾ
ҳ����ת�� �����תҳ�涯��
*******************************/
#include "Btree.h"
#include <time.h>
#include <conio.h>
#include <windows.h>
using namespace std;
typedef long long ll;
int p=0;//ע������
int book_num=0;  //����ִ�ͼ�������
const int book_max=1e6+5; //�����������
typedef struct Time     //�洢ϵͳʱ��
{
    int year;
    int mon;
    int day;
    void show()
    {
        cout<<year<<"��"<<mon<<"��"<<day<<"��";
    }
    Time()
    {
        year=mon=day=0;
    }
    Time(int q,int w,int e):year(q),mon(w),day(e){}
};
typedef struct nnode        //�û�������ͼ��
{
    int id ;
    nnode *next;
}*user_read;
typedef struct user    //Write By XPF
{

    char user_id[20];
    char user_name[20];
    char user_password[20];
//    int max_book;//���Խ��ĵ�����鼮
    int now_book;//�����ѽ��ĵ�ͼ������  //���8��
    user_read read;//�Ѷ���ͼ��
    user()
    {
        strcpy(user_id," ");
        strcpy(user_name," ");
        strcpy(user_password," ");
        now_book=0;
        read=NULL;
    }
    user (char q[],char w[],char e[]){
        strcpy(user_id,q);
        strcpy(user_name,w);
        strcpy(user_password,e);
        now_book=0;
        read=NULL;
    }
    void show()    ////////////////////////////////////////**************************************
    {
        cout<<"Your name is : "<<user_name<<endl;
        cout<<"Your Id is : "<<user_id<<endl;
        cout<<"YOur password is : "<<user_password<<endl;
    }
} User,user;
user  client[1000];// ע���û�
user admin;
//user a;//////********************************************************************��ʱ����
struct node // user ,������Ϣ��ԤԼ��Ϣ        //***ȱ��ʱ�䴦���� *************************** ��д����������
{

   Time brorrow_time ;
   Time return_time;
   bool be_pre;
   Time pre_brorrow_time;
   Time  get_time;
   user userdata;
   user userdata_two;
    node *next;
    node ()
    {
      next=NULL;
      be_pre=0;
    }
};
typedef struct book     //WRite By XPF
{

    int   book_id;//���           Ĭ��Ϊ 0
    char book_name[20];//����      Ĭ��Ϊ " "
    char book_author[20];//����    Ĭ��Ϊ " "
    char book_pulish[20];//������  Ĭ��Ϊ " "
    char book_time[21];//����ʱ��  Ĭ��Ϊ " "
    double book_values;//��Ķ���  Ĭ��Ϊ 0
    int  book_num_now;//�ִ���     Ĭ��Ϊ 0
    int book_num_all;//�ܴ���      Ĭ��Ϊ 0
    int book_num_pre;//ԤԼ��ͼ��  Ĭ��Ϊ0
    bool book_judge;//�Ƿ�Ϊ���ͼ��  Ĭ��Ϊfalse
    node *head;
    book()
    {
        book_id=0;
        strcpy(book_author," ");
        strcpy(book_name," ");
        strcpy(book_pulish," ");
        strcpy(book_time," ");
        book_values=0;
        book_num_all=book_num_now=book_num_pre=0;
        book_judge=false;
        head=NULL;
    }

    book(int q,char w[],char e[],char r[],char t[],int a,double b)
    {
        book_id=q;
        strcpy(book_name,w);
        strcpy(book_author,e);
        strcpy(book_pulish,r);
        strcpy(book_time,t);
        book_num_all=book_num_now=a;
        book_values=b;
        book_judge=1;
        book_num_pre=0;
        head=NULL;
    }
    void show ()// ��
    {
        cout<<"\t\t\t     "<<setiosflags(ios_base::right)<<setw(6)<<book_id
            <<resetiosflags(ios_base::right)<<setw(10)<<book_name
            <<setw(10)<<book_author<<setw(10)<<book_pulish<<setw(12)
            <<book_time<<setw(8)<<book_values<<setw(10)<<book_num_now
            <<setw(10)<<book_num_all<<endl;
    }

} Book,book;
book lib_book[book_max]; //�����Ϣ
///////////////SYSTEM//////////////////
void SetColor(unsigned short TextColor );
void Welcome_Menu();
void Welcome(int color);
inline void Goto_Other_window();//ǰ������ҳ��
void Login_Admin(Btree &tree);      //����Ա��¼����
void Login_User(Btree &tree,user &admin);     //�����ߵ�¼ҳ��
void Reg_Menu(Btree &tree,user &admin);        //ע��ҳ��
void Entry_Menu(Btree &tree,user &admin);      //ѡ��ҳ��
void User_Menu(Btree &tree ,user &admin);       //������ҳ��
void First_Menu();      //�������
void Out_Menu(Btree &tree);         //�˳�����
void Admin_Menu(Btree &tree );        //����Ա����
void Head();              //����
void gotoxy(short x,short y);//��λ����
bool cmp_time(Time &a,Time &b);// �Ƚ�����ʱ��Ĵ�С ��a>=b ,����1 �����򷵻�0
void HideCursor();//���ع��
int isLeap(int year);// �ж�����
Time Count_time(Time a);//��ȡ�黹����
inline void GetDate(tm &tim) ;//��ȡϵͳʱ��
inline void Give_time(Time &a);//����ʱ����ṹ�� time
inline bool user_cmp(user &a,user &b);// �ж������û���Ϣ�Ƿ�һ��*************************************************
bool Linklist_Search(node *head);       //��������Ĳ�ѯ *****************************************************
inline void Init_lib(); //���������             ********���ڿ��Ըĳɶ��ļ�
inline void Print_book(book &b);//��ӡͼ����Ϣ        //��ʽ̫�� ����
inline void Info_book_styple();//��ӡͼ��Ļ�����Ϣ��
void Print_book_All_information(book &b);//��ӡͼ���������Ϣ
void Btree_INorder(Btree &tree); //    �������
void Print_Linklist(node *head);//��ӡ����ڵ���Ϣ
void Add_Book(Btree &tree);//ͼ��ɼ���ҳ��
void add_book(Btree &tree);//���ͼ������ҳ
void Delete_book(Btree &tree);//ɾ��ͼ����ҳ��
void delte_book(Btree  &tree);//ͼ��ɾ������ҳ
int author_book_id[book_max];//ĳλ��������ͼ��ID
int author_book_num;//ĳλ����ͼ�������
void Author_Zone(Btree &tree);//����ר��
/******************************
����� �������а�ǿ���ÿ���
******************************/
void Reader_Push();//�����Ƽ�ͼ��  /************************************************************
void Btree_Inorder_Search(Btree &tree,char name[]);//�����������
void Info_book(Btree &tree);//��ѯͼ����Ϣ������
void info_book(Btree &tree);//ͼ����Ϣ����ҳ
void Btree_Inorder_Info(Btree &tree);//��ѯͼ���������Ϣ
void Info_book_find(Btree &tree);//��ѯͼ����Ϣ��������
void Brorrow_book(Btree &tree,user &admin);//ͼ����Ľ���
void brorrow_book(Btree &tree,user &admin);//ͼ���������ҳ
void Return_book(Btree &tree,user &admin);//ͼ��黹��ҳ��
void return_book(Btree &tree,user &admin);//ͼ��黹����ҳ
void Pre_Brorrow_book(Btree &tree,int id,user &admin);//ͼ��ԤԼ������
void pre_brorrow_book(Btree &tree,int id,user &admin);//ͼ��ԤԼ����ҳ
//��Ҫ�ж�����黹�ľ���ʱ��
void test();//�������Գ���
void ShowCursor();//��ʾ���
int main ()
{
    system("title:ͼ�����");
    First_Menu();
    return 0;
}
void Welcome_Menu()
{
    int i;
    for (i=0;i<=10;i++)
    {
        Welcome(i%16);
        Sleep(200);
    }
}

void Welcome(int color) //��ӭ�����������
{
    int x=36,y=6;
    SetColor(color);
    gotoxy(x,y);
    printf("  ::����**�����**�	");
    gotoxy(x,y+1);
    printf("  ����������    ����ߡ�ߡ� ");
    gotoxy(x,y+2);
    printf("  ���切�切��*����ߣ�");
    gotoxy(x,y+3);
    printf("  ���切�切��*����ߣ�");
    gotoxy(x,y+4);
    printf("  ���切�切    ����ߡ���ߡ࣮");
    gotoxy(x,y+5);
    printf("  ���切�切����ߡ���..**��");
    gotoxy(x,y+6);
	printf("  ���切�切  �����ߡ���*�");
	gotoxy(x,y+7);
	printf("  ������������");
	gotoxy(x,y+8);
	printf("����������������~~~~~*^_^*");
}

void 	SetColor(unsigned short TextColor )// ��������ͱ�����ɫ
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon,TextColor);
}
inline void Goto_Other_window()     //ת�ؽ��涯��
{
    int i;
    for (i = 0; i<11; i++)
    {
        Sleep(100);
        printf("�� ");
    }
}
void test() //���Խ׶�
{
    //    int i,j,k;
//    Init_lib();
//    cout<<endl;
////    Print_book_All_information(lib_book[1]);
////    Time a;
////    Give_time(a);
////    Time aa(2019,01,01);
////    cout<<cmp_time(aa,a)<<endl;
//
////    Give_time(a);
////    a.show();
////    Time b;
////    b=Count_time(a);
////    b.show();
//////    if (lib_book[1].head==NULL)
//////    {
//////        node *p;
//////        int x;
//////        lib_book[1].head=new node ;
//////        lib_book[1].head->next=NULL;
//////        for(i=0;i<10;i++)
//////        {
//////            p=new node ;
//////            cin>>p->data;
//////            p->next=lib_book[1].head->next;
//////            lib_book[1].head->next=p;
//////            cout<<"****"<<endl;
//////        }
//////        Print_Linklist(lib_book[1].head);
//////    }
//    Btree tree=NULL;
//    for (i=1; i<=10; i++)
//        Btree_Insert(tree,i);
////        Info_book(tree);
////        Author_Zone(tree);
//     user admin("123","456_","123456");
////     Delete_book(tree);
//    Brorrow_book(tree,admin);
////    Print_book_All_information(lib_book[1]);
////    Return_book(tree,admin);
////     Info_book(tree);
}
void Head() //����
{
    int		x = 25,y = 2;
    tm		date;
    HideCursor();
    GetDate(date);
    gotoxy(x,y);
    printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[");
    gotoxy(x,y+1);
    printf("�U                                                        �U");
    gotoxy(x,y+2);
    printf("�U                                                        �U");
    gotoxy(x,y+3);
    printf("�U                     ͼ�����ϵͳ                       �U");
    gotoxy(x,y+4);
    printf("�U                                                        �U");
    gotoxy(x,y+5);
    printf("�U                                                        �U");
    gotoxy(x,y+6);
    printf("�U                                                        �U");
    gotoxy(x,y+7);
    printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a");
    while(!_kbhit())												// ��δ��⵽����
    {
        gotoxy(x+17,y+6);
        HideCursor();
        GetDate(date);												// ��ȡʱ��
        printf("%d��%2d��%2d�� %02d:%02d:%02d ",date.tm_year,date.tm_mon,date.tm_mday,date.tm_hour,date.tm_min,date.tm_sec);
        Sleep(1000);													// ��ʾʱ��
    }
}
void First_Menu()         //�������            /////��Ҫ�޸�
{

    //Ԥ����
    Btree tree=NULL;
    user admin;
    HideCursor();
    Welcome_Menu();
    gotoxy(36,16);
//    SetColor(16);
    printf("��������ͼ�����ϵͳ��");
    gotoxy(36,18);
    Goto_Other_window();
    system("cls");
    SetColor(14);
    Init_lib();
    for (int i=1;i<=10;i++)
        Btree_Insert(tree,i);
    Entry_Menu(tree,admin);
//    Entry_Menu(tree,admin);
}
void Login_Admin(Btree &tree)      //����Ա��½ҳ��            //x 36  x+6 x+18    x+6 x+12 x+14     �Ѹ� ��******************** δд��
{
    int x=36;
    char key[20],ch;
//    HideCursor();
    gotoxy(x,12);
    printf(" +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ ");
    gotoxy(x,13);
    printf("|                                   |");
    gotoxy(x,14);
    printf("|                                   |");
    gotoxy(x,15);

    printf("|                                   |");
    gotoxy(x,16);
    printf(" +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ ");
    gotoxy(x+6,14);
    printf("����Ա���룺");
    Head();
    gotoxy(x+18,14);
    ShowCursor();
    scanf("%s",key);
    if(strcmp(key,"000000")==0)
    {
        gotoxy(x+6,20);
        printf("������ȷ������ǰ������Ա���棡   ");
        gotoxy(x+6,22);
        Goto_Other_window();
        system("cls");
        Admin_Menu(tree);
    }
    else
    {
        gotoxy(x+6,20);
        printf("��������Ƿ��������룡      ");
        gotoxy(x+12,22);
        printf("Y or N  ");
        gotoxy(x+14,24);
        while (ch=getch())
        {
            if (ch=='Y'||ch=='y'||ch=='N'||ch=='n')
                break;
        }
        if(ch=='Y'||ch=='y')
            {
                system("cls");
                Login_Admin(tree);
            }
        else
        {
            gotoxy(x+6,20);
            printf("�����������������棡        ");
            gotoxy(x+4,22);
            Goto_Other_window();
            system("cls");
            Entry_Menu(tree,admin);
        }
    }
}
void Login_User(Btree &tree,user &admin)       //�û���¼                   //************************************δд��
{
    char id[20],key[20],ch;
    int i;
    HideCursor();
    gotoxy(36,12);
    printf(" +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ ");
    gotoxy(36,13);
    printf("|                                   |");
    gotoxy(36,14);
    printf("|                                   |");
    gotoxy(36,15);
    printf("|                                   |");
    gotoxy(36,16);
    printf("|                                   |");
    gotoxy(36,17);
    printf("|                                   |");
    gotoxy(36,18);
    printf(" +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ ");
    int x=36;
    gotoxy(x+6,14);
    printf("�û�ID : ");

    gotoxy(x+6,16);
    printf("  ���� : ");
     Head();
    gotoxy(x+16,14);
    ShowCursor();
    scanf("%s",id);
    gotoxy(x+16,16);
    scanf("%s",key);


    for(i=0; i<p; i++)
    {
        if(strcmp(id,client[i].user_id)==0)
        {
            if(strcmp(key,client[i].user_password)==0)
            {
                gotoxy(x+8,20);
                printf("���������û������棡      ");
                gotoxy(x+4,22);
                Goto_Other_window();
                system("cls");
                User_Menu(tree,admin);     //��ת�û�
                break;
            }
            gotoxy(x+6,20);
            printf("��������Ƿ��������룡");
            gotoxy(x+18,22);

            while (ch=getch())
            {
                if (ch=='Y'||ch=='N'||ch=='y'||ch=='n')
                    break;
            }
            if(ch=='Y'||ch=='y')
                {
                       system("cls");
                    Login_User(tree,admin);
                }
            else
            {
                    gotoxy(x+8,20);
                    printf("�����������������棡      ");
                    gotoxy(x+4,22);
                    Goto_Other_window();
                    system("cls");
                    Entry_Menu(tree,admin);
            }
            break;
        }
    }
    if(i==p)
    {
        gotoxy(x+4,20);
        printf("û�и��û����������Ƿ�Ҫע�᣿                  ");
        gotoxy(x+14,22);
        printf("Y or N");
        gotoxy(x+16,24);
        while (ch=getch())
        {
            if (ch=='Y'||ch=='N'||ch=='y'||ch=='n')
                break;
        }
        if(ch=='Y'||ch=='y')
        {
                gotoxy(x+8,20);
                printf("���������û�ע����棡           ");
                gotoxy(x+4,22);
                Goto_Other_window();
                system("cls");
            Reg_Menu(tree,admin);
        }
        else
        {
             gotoxy(x+8,20);
             printf("�����������������棡          ");
             gotoxy(x+4,22);
             Goto_Other_window();
                system("cls");
                Entry_Menu(tree,admin);
        }
    }
}
void Reg_Menu(Btree &tree,user &admin)         //�û�ע��                   //�Ѹ� ���������ж�����gotoxy������   ���� showcuror����
{
    char k;
   int x =36;
    gotoxy(x,12);
    printf(" +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ ");
    gotoxy(x,13);
    printf("|                                   |");
    gotoxy(x,14);
    printf("|                                   |");
    gotoxy(x,15);
    printf("|                                   |");
    gotoxy(x,16);
    printf("|                                   |");
    gotoxy(x,17);
    printf("|                                   |");
    gotoxy(x,18);
    printf("|                                   |");
    gotoxy(x,19);
    printf("|                                   |");
    gotoxy(x,20);
    printf(" +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ ");
    gotoxy(x+6,14);
    printf("�û�ID : ");
    gotoxy(x+6,16);
    printf("  ���� : ");
    gotoxy(x+6,18);
    printf("  ���� : ");
    Head();
    gotoxy(x+18,14);
    ShowCursor();
    scanf("%s",client[p].user_id);
    gotoxy(x+18,16);
    ShowCursor();
    scanf("%s",client[p].user_name);
    gotoxy(x+18,18);
    ShowCursor();
    scanf("%s",client[p++].user_password);
    gotoxy(x+13,22);
    admin=client[p-1];
    printf("ȷ��ע��?\n");
    gotoxy(x+13,24);
    printf(" Y or N");
    user caption =client[p-1];
    gotoxy(x+16,26);
    ShowCursor();
    while (k=getchar())
    {
        if (k=='Y'||k=='N'||k=='y'||k=='n')
            break;
    }
    //    k=getchar();      /////////////////////////////////////////

    if(k=='Y'||k=='y')
    {
        gotoxy(x+10,26);
        HideCursor();
        printf("����ע��ɹ���");
        gotoxy(x+6,28);
        printf("����ǰ���û���¼ҳ�棡");
        gotoxy(x+4,30);
        Goto_Other_window();
        system("cls");
        Login_User(tree,admin);
    }
    else
    {
        gotoxy(x+6,26);
        printf("�������������棡");
        gotoxy(x+4,28);
        Goto_Other_window();
        system("cls");
        Entry_Menu(tree,admin);
    }
}
void Entry_Menu(Btree &tree,user &admin)      //��¼ҳ���ѡ��                           //�޸����
{
    char  n;
//    HideCursor();
    //printf("\n\n\n\n\n\n\n");
    int x=36;
    gotoxy(x,12);
    printf(" +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ ");
    gotoxy(x,13);
    printf("|                                   |");
    gotoxy(x,14);
    printf("|                                   |");
    gotoxy(x,15);
    printf("|                                   |");
    gotoxy(x,16);
    printf("|                                   |");
    gotoxy(x,17);
    printf("|                                   |");
    gotoxy(x,18);
    printf("|                                   |");
     gotoxy(x,19);
    printf("|                                   |");
     gotoxy(x,20);
    printf("|                                   |");
     gotoxy(x,21);
    printf("|                                   |");
    gotoxy(x,22);
    printf(" +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ ");
    x+=10;
    gotoxy(x,14);
    printf("1. ����Ա��¼\n");
    gotoxy(x,16);
    printf("2. �����ߵ�¼\n");
    gotoxy(x,18);
    printf("3. ���û�ע��\n");
    gotoxy(x,20);
    printf("0. �˳�ϵͳ\n");
    gotoxy(x,24);
    printf("�����룺");
    Head();
    gotoxy(x+10,24);
    x-=6;
    ShowCursor();
    while(1)
    {
        n=getchar();
        if(n=='1')
        {
            gotoxy(x,24);
            printf("����ǰ������Ա��¼���棡          ");
            gotoxy(x,26);
            Goto_Other_window();
            system("CLS");
            Login_Admin(tree);
        }
        else if(n=='2')
        {
            gotoxy(x,24);
            printf("����ǰ���û���¼���棡            ");
            gotoxy(x,26);
            Goto_Other_window();
            system("CLS");
            Login_User(tree,admin);
        }
        else if(n=='3')
        {
            gotoxy(x,24);
            printf("����ǰ���û�ע����棡           ");
            gotoxy(x,26);
            Goto_Other_window();
            system("CLS");
            Reg_Menu(tree,admin);
        }
        else if(n=='0')
        {
            gotoxy(x,24);
            printf("�����˳���ϵͳ��                    ");
            gotoxy(x,26);
            Goto_Other_window();
            system("CLS");
//            Out_Menu(tree);
            Out_Menu(tree);
        }
        else
            continue ;
    }
}
void User_Menu(Btree &tree ,user &admin)      //������ҳ��                   //�޸����
{

    char n;             //������int??
    HideCursor();
    int x =36;
    gotoxy(x,12);
    printf(" +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ ");
    gotoxy(x,13);
    printf("|                                   |");
    gotoxy(x,14);
    printf("|                                   |");
    gotoxy(x,15);
    printf("|                                   |");
    gotoxy(x,16);
    printf("|                                   |");
    gotoxy(x,17);
    printf("|                                   |");
    gotoxy(x,18);
    printf("|                                   |");
    gotoxy(x,19);
    printf("|                                   |");
    gotoxy(x,20);
    printf("|                                   |");
    gotoxy(x,21);
    printf("|                                   |");
    gotoxy(x,22);
    printf("|                                   |");
    gotoxy(x,23);
    printf("|                                   |");
    gotoxy(x,24);
    printf("|                                   |");
    gotoxy(x,25);
    printf(" +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ ");
    gotoxy(x+12,14);
    printf("1. ����ͼ��\n");
    gotoxy(x+12,16);
    printf("2. �黹ͼ��\n");
    gotoxy(x+12,18);
    printf("3. ����ר��\n");
    gotoxy(x+12,20);
    printf("4. ͼ����Ϣ\n");
    gotoxy(x+12,22);
    printf("5. ����������\n");
    gotoxy(x+12,24);
    printf("0. �˳�ϵͳ\n");
    gotoxy(x+10,27);
    printf("�����룺");
    Head();
    gotoxy(x+18,27);
    ShowCursor();
    x--;
    while(1)
    {
        gotoxy(x+18,27);
        n=getchar();
        if(n=='1')
        {
            gotoxy(x+10,28);
            printf("����ǰ��ͼ����Ľ��棡");
            gotoxy(x+6,30);
            Goto_Other_window();

            system("CLS");
            //ͼ�����
            Brorrow_book(tree,admin);
        }
        else if(n=='2')
        {
            gotoxy(x+10,28);
            printf("����ǰ��ͼ��黹���棡");
            gotoxy(x+6,30);
            Goto_Other_window();

            system("CLS");
            Return_book(tree,admin);
            //ͼ��黹
        }
        else if(n=='3')
        {
            gotoxy(x+10,28);
            printf("����ǰ������ר�����棡");
            gotoxy(x+6,30);
            Goto_Other_window();

            system("CLS");
            //����ר��
            Author_Zone(tree);
        }
        else if(n=='4')
        {
            gotoxy(x+10,28);
            printf("����ǰ��ͼ����Ϣ���棡");
            gotoxy(x+6,30);
            Goto_Other_window();

            system("CLS");
            //ͼ����Ϣ
            Info_book(tree);
        }
        if(n=='5')
        {
            gotoxy(x+10,28);
            printf("�������ؽ��棡   ");
            gotoxy(x+6,30);
            Goto_Other_window();

            system("CLS");
            Entry_Menu(tree,admin);//����ϵͳ
        }
        if(n=='0')
        {
            gotoxy(x+10,28);
            printf("�����˳�����    ");
            gotoxy(x+6,30);
            Goto_Other_window();

            system("CLS");
            Out_Menu(tree);//�˳�ϵͳ
        }
    }
}
void Admin_Menu(Btree &tree)      //����Աҳ��           //�޸����
{
    char  n;
    HideCursor();
    int x=36;
     gotoxy(x,12);
    printf(" +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ ");
    gotoxy(x,13);
    printf("|                                   |");
    gotoxy(x,14);
    printf("|                                   |");
    gotoxy(x,15);
    printf("|                                   |");
    gotoxy(x,16);
    printf("|                                   |");
    gotoxy(x,17);
    printf("|                                   |");
    gotoxy(x,18);
    printf("|                                   |");
    gotoxy(x,19);
    printf("|                                   |");
    gotoxy(x,20);
    printf("|                                   |");
    gotoxy(x,21);
    printf("|                                   |");
    gotoxy(x,22);
    printf("|                                   |");
    gotoxy(x,23);
    printf("|                                   |");
    gotoxy(x,24);
    printf("|                                   |");
    gotoxy(x,25);
    printf("|                                   |");
    gotoxy(x,26);
    printf(" +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ ");
    gotoxy(x+12,14);
    printf("1. ͼ�����\n");
    gotoxy(x+12,16);
    printf("2. ������\n");
    gotoxy(x+12,18);
    printf("3. ����ר��\n");
    gotoxy(x+12,20);
    printf("4. ͼ����Ϣ\n");
    gotoxy(x+12,22);
    printf("5. ���ص�¼\n");
    gotoxy(x+12,24);
    printf("0. �˳�ϵͳ\n");
    gotoxy(x+10,28);
    printf("�����룺");

    Head();
    gotoxy(x+18,28);
    ShowCursor();
    while(1)
    {
        n=getchar();
        if(n=='1')
        {
            gotoxy(x+6,28);
            printf("����ǰ��ͼ�������棡");
            gotoxy(x+6,30);
            Goto_Other_window();
            system("CLS");
            //ͼ�����
            Add_Book(tree);
        }
        else if(n=='2')
        {

            gotoxy(x+6,28);
            printf("����ǰ����������棡");
            gotoxy(x+6,30);
            Goto_Other_window();
            system("CLS");
            Delete_book(tree);

            //������
        }
        else if(n=='3')
        {

            gotoxy(x+6,28);
            printf("����ǰ������ר�����棡");
            gotoxy(x+6,30);
            Goto_Other_window();
            system("CLS");
            Author_Zone(tree);
            //����ר��
        }
        else if(n=='4')
        {

            gotoxy(x+6,28);
            printf("����ǰ��ͼ����Ϣ���棡");
            gotoxy(x+6,30);
            Goto_Other_window();
            system("CLS");
            Info_book(tree);
            //ͼ����Ϣ
        }
        if(n=='5')
        {

            gotoxy(x+6,28);
            printf("��������ϵͳ�����棡");
            gotoxy(x+6,30);
            Goto_Other_window();
            system("CLS");
            Entry_Menu(tree,admin);//����ϵͳ
        }
        if(n=='0')
        {

            gotoxy(x+6,28);
            printf("�����˳���ϵͳ��");
            gotoxy(x+6,30);
            Goto_Other_window();
            system("CLS");
            Out_Menu(tree);//�˳�ϵͳ
        }
    }
}
void Out_Menu(Btree &tree)        //�˳�ϵͳ
{
    HideCursor();
    int x=25,y=5;
    gotoxy(x,y);
    printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[");
    gotoxy(x,y+1);
    printf("�U                                                        �U");
    gotoxy(x,y+2);
    printf("�U                                                        �U");
    gotoxy(x,y+3);
    printf("�U                                                        �U");
    gotoxy(x,y+4);
    printf("�U                    лл����ʹ�ã�                      �U");
    gotoxy(x,y+5);
    printf("�U                                                        �U");
    gotoxy(x,y+6);
    printf("�U                                                        �U");
    gotoxy(x,y+7);
    printf("�U                      GOODBYE!!!                        �U");
    gotoxy(x,y+8);
    printf("�U                                                        �U");
    gotoxy(x,y+9);
    printf("�U                                                        �U");
    gotoxy(x,y+10);
    printf("�U                      ͼ�����                          �U");
    gotoxy(x,y+11);
    printf("�U                                                        �U");
    gotoxy(x,y+12);
    printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a");
     delete tree;
     gotoxy(x,y+20);
    exit(0);
//    return ;
}
void gotoxy(short x,short y)        //���㺯��
// �ƶ���굽��x��y�����꣬25>x>=0,80>y>=0
{
    COORD point = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}
void HideCursor()//���ع��
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
    CursorInfo.bVisible = 0; //���ؿ���̨���
    SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
}
void ShowCursor()//��ʾ���
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
    CursorInfo.bVisible = 1; //���ؿ���̨���
    SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
}
void Print_book_All_information(book &b) //��ӡͼ���������Ϣ / //ͼ����Ϣר��
{
    cout<<"\t\t\t     ******************************����Ļ�����Ϣ**********************************         "<<endl;
    cout<<endl;
    cout<<"\t\t\t     "<<setiosflags(ios_base::right)<<setw(6)<<"���"<<resetiosflags(ios_base::right)<<setw(10)<<"����"<<setw(10)<<"����"
    <<setw(10)<<"������"<<setw(12)<<"����ʱ��"<<setw(8)<<"����"
    <<setw(10)<<"�ִ���"<<setw(10)<<"�ܴ���"<<endl;
    cout<<endl;
    b.show();
    node *p=b.head;
    if(p==NULL)
    {
        cout<<endl;
        cout<<"\t\t\t     Sorry, ������δ�����ģ�"<<endl;
        cout<<endl;
        return ;
    }
    else
    {
        cout<<endl;
        cout<<"\t\t\t     ******************************����Ľ�����Ϣ**********************************         "<<endl;
        cout<<endl;
        cout<<"\t\t\t     "<<setiosflags(ios_base::right)<<setw(15)<<"User_id"<<resetiosflags(ios_base::right)<<setw(15)<<"User_name"<<setw(15)<<"����ʱ��"
        <<setw(15)<<"Ӧ��ʱ��"<<endl;
        node *q=p->next;
        while (q)
        {
            cout<<endl;
            cout<<setiosflags(ios_base::right)<<setw(15)<<q->userdata.user_id<<resetiosflags(ios_base::right)<<setw(15)<<q->userdata.user_name;

            cout<<"\t";
            q->brorrow_time.show();
            cout<<"\t";
            q->return_time.show();
            q=q->next;
        }
        cout<<endl;
         if (b.book_num_pre==0)
         {
             cout<<endl;
            cout<<"\t\t\t     ***************************������δ��ԤԼ��***********************************         "<<endl;
            return ;
         }
         else
           {
               cout<<endl;
               cout<<"\t\t\t     ******************************�����ԤԼ��Ϣ**********************************         "<<endl;
               cout<<endl;
               cout<<"\t\t\t     "<<setiosflags(ios_base::right)<<setw(15)<<"User_id"<<resetiosflags(ios_base::right)<<setw(15)<<"User_name"<<setw(15)<<"ԤԼʱ��"
        <<setw(15)<<"ȡ��ʱ��"<<endl;
                   q=p->next;
                 while (q)
                 {
                     if (q->be_pre==1)
                        {
                            cout<<endl;
                            cout<<setiosflags(ios_base::right)<<setw(15)<<q->userdata_two.user_id<<resetiosflags(ios_base::right)<<setw(15)<<q->userdata_two.user_name;
                            cout<<"\t";
                            q->pre_brorrow_time.show();
                            cout<<"\t";
                            q->get_time.show();
                        }
                        q=q->next;
                 }
           }
    }

}
inline bool user_cmp(user &a,user &b)    //a==b return 1; else return 0
{
    if (strcmp(a.user_id,b.user_id)==0&&strcmp(a.user_name,b.user_name)==0)
        return 1;
    else
        return 0;
}
void Return_book(Btree &tree,user &admin) //ͼ��黹������*******************************************************************************************************
{

    cout<<"\n\n\n\t\t\t     ��ӭ����ͼ��黹�����棡"<<endl;
    cout<<endl;
    while (1)
    {
        return_book(tree,admin);
        cout<<"\t\t\t     �������Ƿ�Ҫ�������飿��"<<endl<<endl;
        cout<<"\t\t\t         1.��     2.��"<<endl<<endl;
        cout<<"\t\t\t     �����룺";
        char key;
        while (cin>>key)
        {
            if (key=='1'||key=='2')
                break;
            else
                continue ;
        };
        if (key=='2')
            break;
    }
    getchar();//*********************************************************************************
    cout<<"\t\t\t     GoodBye,���������û������棡"<<endl;
    cout<<endl;
    cout<<"\t\t\t     ";
    Goto_Other_window();
    system("cls");
    User_Menu(tree,admin);
}
void return_book(Btree &tree,user &admin) //ͼ��黹����ҳ
{
    cout<<"\t\t\t     ��������Ҫ�黹����ţ�";
    int id;
    cin>>id;
    if (lib_book[id].book_num_all==lib_book[id].book_num_now)
    {
        cout<<endl;
        cout<<"\t\t\t     �Բ���������Ⲣδ����������͵��飡"<<endl<<endl;
        return ;
    }
    cout<<"\t\t\t     ��Ҫ�黹��ͼ��Ļ�����Ϣ�ǣ�"<<endl;
    cout<<endl;

    Print_book(lib_book[id]);
    cout<<endl;
    cout<<"\t\t\t     �����Ƿ�ȷ�ϣ�"<<endl;
    cout<<"\t\t\t      1.��  2.��"<<endl;
    char key ;
    cout<<"\t\t\t     �����룺";
    while (cin>>key&&key==' '||key=='\n');
    if (key=='2')
        return ;
    lib_book[id].book_num_now++;
    node *p=lib_book[id].head;
    int yes=0;
    node *q;
    q=p->next;
    while (q)
    {
        if (user_cmp(admin,q->userdata))     // ����ҵ�admin
        {
            yes=1;
            p->next=q->next;
            free(q);
            q=p->next;
            break;
        }
        else
        {
            p=q;
            q=q->next;
        }
    }
    if (yes)
    {
        cout<< "\t\t\t          �黹�ɹ������� "<<endl;
        cout<<endl;
    }
    else
    {
        cout<<"\t\t\t     Sorry,"<<admin.user_name<<"��û��������������Ȿ�顣"<<endl;
        cout<<endl;
        return ;
    }

}
bool cmp_time(Time &a,Time &b) // �Ƚ�����ʱ��Ĵ�С ��a>b ,����1 �����򷵻�0
{
    if (a.year>b.year)
        return 1;
    else if (a.year==b.year)
    {
        if (a.mon>b.mon)
            return 1;
        else if (a.mon==b.mon)
        {
            if (a.day>b.day)
                return 1;
            else return 0;
        }
        return  0;
    }
    else
        return 0;
}
int isLeap(int year)  //�ж�����
{
    // �������ж���ƽ������ ���ж���������
    if((year%100==0 && year%400!=0) || year%3200==0)
    {
        // �ܱ�100�������Ҳ��ܱ�400�����Ĳ�������
        // �ܱ�3200�����Ĳ�������
        return 0;
    }
    else if(year%4==0 && year%100!=0)
    {
        // �ܱ�4�������Ҳ��ܱ�100������������
        return 1;
    }
    else if(year%400==0)
    {
        // �ܱ�400������������
        return 1;
    }
    else
        return 0;
}
Time Count_time(Time a) //��ȡ�黹ʱ�䣬����ȡ��ʱ��
{
     int flag=0;
    flag=isLeap(a.year);
    if(flag==1)
    {
        int end_day;
        end_day=a.day+30;
        switch(a.mon)
        {
        case 1:
            if(end_day>31)
            {
                a.mon=a.mon+1;
                a.day=end_day-31;
            }
            else
                a.day=end_day;
            break;
        case 2:
            if(end_day>29)
            {
                a.mon=a.mon+1;
                a.day=end_day-29;
            }
            else
                a.day=end_day;
            break;
        case 3:
            if(end_day>31)
            {
                a.mon=a.mon+1;
                a.day=end_day-31;
            }
            else
                a.day=end_day;
            break;
        case 4:
            if(end_day>30)
            {
                a.mon=a.mon+1;
                a.day=end_day-30;
            }
            else
                a.day=end_day;
            break;
        case 5:
            if(end_day>31)
            {
                a.mon=a.mon+1;
                a.day=end_day-31;
            }
            else
                a.day=end_day;
            break;
        case 6:
            if(end_day>30)
            {
                a.mon=a.mon+1;
                a.day=end_day-30;
            }
            else
                a.day=end_day;
            break;
        case 7:
            if(end_day>31)
            {
                a.mon=a.mon+1;
                a.day=end_day-31;
            }
            else
                a.day=end_day;
            break;
        case 8:
            if(end_day>31)
            {
                a.mon=a.mon+1;
                a.day=end_day-30;
            }
            else
                a.day=end_day;
            break;
        case 9:
            if(end_day>30)
            {
                a.mon=a.mon+1;
                a.day=end_day-30;
            }
            else
                a.day=end_day;
            break;
        case 10:
            if(end_day>31)
            {
                a.mon=a.mon+1;
                a.day=end_day-31;
            }
            else
                a.day=end_day;
            break;
        case 11:
            if(end_day>30)
            {
                a.mon=a.mon+1;
                a.day=end_day-30;
            }
            else
                a.day=end_day;
            break;
        case 12:
            if(end_day>31)
            {
                a.mon=a.mon-11;
                a.day=end_day-31;
                a.year=a.year+1;
            }
            else
                a.day=end_day;
            break;
        }
    }
    else
    {
        int end_day;
        end_day=a.day+30;
        switch(a.mon)
        {
        case 1:
            if(end_day>31)
            {
                a.mon=a.mon+1;
                a.day=end_day-31;
            }
            else
                a.day=end_day;
            break;
        case 2:
            if(end_day>28)
            {
                a.mon=a.mon+1;
                a.day=end_day-28;
            }
            else
                a.day=end_day;
            break;
        case 3:
            if(end_day>31)
            {
                a.mon=a.mon+1;
                a.day=end_day-31;
            }
            else
                a.day=end_day;
            break;
        case 4:
            if(end_day>30)
            {
                a.mon=a.mon+1;
                a.day=end_day-30;
            }
            else
                a.day=end_day;
            break;
        case 5:
            if(end_day>31)
            {
                a.mon=a.mon+1;
                a.day=end_day-31;
            }
            else
                a.day=end_day;
            break;
        case 6:
            if(end_day>30)
            {
                a.mon=a.mon+1;
                a.day=end_day-30;
            }
            else
                a.day=end_day;
            break;
        case 7:
            if(end_day>31)
            {
                a.mon=a.mon+1;
                a.day=end_day-31;
            }
            else
                a.day=end_day;
            break;
        case 8:
            if(end_day>31)
            {
                a.mon=a.mon+1;
                a.day=end_day-30;
            }
            break;
        case 9:
            if(end_day>30)
            {
                a.mon=a.mon+1;
                a.day=end_day-30;
            }
            else
                a.day=end_day;
            break;
        case 10:
            if(end_day>31)
            {
                a.mon=a.mon+1;
                a.day=end_day-31;
            }
            else
                a.day=end_day;
            break;
        case 11:
            if(end_day>30)
            {
                a.mon=a.mon+1;
                a.day=end_day-30;
            }
            else
                a.day=end_day;
            break;
        case 12:
            if(end_day>31)
            {
                a.mon=a.mon-11;
                a.day=end_day-31;
                a.year=a.year+1;
            }
            else
                a.day=end_day;
            break;
        }
    }

     Time b=a;
     return b;
}
inline void Give_time(Time &a) //����ʱ��
{

    tm date;
    GetDate(date);
    a.year=date.tm_year;
    a.mon=date.tm_mon;
    a.day=date.tm_mday;
}
inline void	GetDate(tm &tim)// ��ȡϵͳʱ�䣬����tm�ṹ�����tim
{
	time_t curtime=time(0);
	tim = *localtime(&curtime);
	tim.tm_year += 1900;		// tm �����1900��
	tim.tm_mon ++;				// tm month ��0-11���ʼ�1
}
bool Linklist_Search(node *head);           //*******************************************************************************************************
void Pre_Brorrow_book(Btree &tree,int id,user &admin)   //ͼ��ԤԼ������   *************************************************************************************��
{


    cout<<"\n\n\n\t\t\t     ��ӭ����ͼ��ԤԼϵͳ��"<<endl;
    cout<<endl;
    cout<<"\t\t\t     ����ҪԤԼ��ͼ����Ϣ���£�"<<endl;
    cout<<endl;
    /////       **********************************************************************
    Print_book(lib_book[id]);//��ӡͼ��Ļ�����Ϣ
    cout<<endl;
    cout<<"\t\t\t     �������Ƿ�ȷ�ϣ�"<<endl<<endl;
    cout<<"\t\t\t       1.��   2.��"<<endl<<endl;
    cout<<"\t\t\t     �����룺";
    char key;
        while (cin>>key)
    {
        if (key=='1'||key=='2')
            break;
        else
            continue ;
    };
    if (key=='1')
    {
        cout<<"\t\t\t     ****************************"<<endl;

        pre_brorrow_book(tree,id,admin);//ԤԼͼ������ҳ*****************************************
        ///////////////////ԤԼͼ��//////////////////////////****************
//        cout<<"ԤԼͼ��ɹ�"<<endl<<endl;
    }
//    getch();
    cout<<"��������ͼ����Ľ���"<<endl;
    cout<<endl;
    cout<<"\t";//***************************************************************************************
    Goto_Other_window();
    system("cls");
    //////����ͼ����Ľ���
    return ;

}
void pre_brorrow_book(Btree &tree,int id ,user &admin)  //ͼ��ԤԼ����ҳ
{
    cout<<"\t\t\t     ****************************"<<endl;
    if (lib_book[id].book_num_pre==lib_book[id].book_num_all)
    {
        cout<<"\t\t\t     ʮ�ֱ�Ǹ�����е�ͼ���ѱ�ԤԼ�꣬��ȴ���һ�ֵĽ��ĺ�ԤԼ��"<<endl;
        return ;
    }
    bool yes =0;
    Time cmp;
    node *p =lib_book[id].head->next;
    while (p)
    {
        if(p->be_pre==0)
        {
            yes=1;
            cmp=p->return_time;
            break;
        }
        p=p->next;
    }

     if (!yes)
        return ;
    node *q=p->next;
    int pos =0;
    int cnt =0;
    while (q)
    {
        cnt++;
        if (q->be_pre==0)
        {
            pos=cnt;
            if (cmp_time(cmp,q->return_time))  //cmp_time(a,b) a>b return 1,else  return 0
            cmp=q->return_time;
         }
         q=q->next;
    }
    if (!pos)
        q=p;
    else
    {
        q=p->next;
        cnt=0;
        while (q)
        {
            cnt++;
            if (cnt==pos)
                break;
         q=q->next;
        }
    }
    Give_time(q->pre_brorrow_time);
    q->get_time=cmp;
    q->be_pre=1;
    q->userdata_two=admin;
    lib_book[id].book_num_pre++;
    cout<<"\t\t\t          ԤԼ�ɹ�������"<<endl<<endl;
    cout<<"\t\t\t     ����ԤԼʱ���ǣ�";
    q->pre_brorrow_time.show();
    cout<<endl;
    cout<<"\t\t\t     ����ȡ��ʱ���ǣ�";
    q->get_time.show();
    cout<<endl;
    //***********************************************************************************
//     if()
}
void Brorrow_book(Btree &tree,user &admin)//ͼ����Ľ���      //*************************************************************************************
{
//    system("cls");
    cout<<endl;
    cout<<"\n\n\n\t\t\t     ��ӭ����ͼ�����ר��!(���ĵ�Ĭ������Ϊ30��)"<<endl;
    cout<<endl;
    while (1)
    {
        brorrow_book(tree,admin);
        cout<<"\t\t\t     �������Ƿ�Ҫ�������ģ�"<<endl;
        cout<<endl;
        cout<<"\t\t\t        1.��   2.��"<<endl;
        cout<<endl;
        cout<<"\t\t\t     �����룺";
        char key;
        while (cin>>key)
        {
            if (key=='1'||key=='2')
                break;
            else
                continue ;
        };
        if (key=='2')
            break;
        cout<<endl;
    }
    getch();
    cout<<"\t\t\t     �ڴ������´ν��ģ�"<<endl;
    cout<<endl;
    cout<<"\t\t\t     ���������û������棡"<<endl;
    cout<<endl;
    cout<<"\t\t\t     ";//****************
    Goto_Other_window();
    system("cls");
    User_Menu(tree,admin);//******************************************************************************************
}
void brorrow_book(Btree &tree,user &admin)//ͼ���������ҳ  //��Ž���
{
    cout<<"\t\t\t     ����������Ҫ���ĵ���ţ�";
    int id ;
    cin>>id;
    cout<<endl;
    Find_res ret=Btree_Search(tree,id);
    if (ret.yes==0)
    {
        cout<<"\t\t\t     Sorry, ���ǲ�û����¼�Ȿ�飡"<<endl;
        cout<<endl;
        return ;
    }
    else
    {
        cout<<"\t\t\t     ��Ҫ���ĵ���Ļ�����Ϣ�ǣ�"<<endl;
        cout<<endl;
        Print_book(lib_book[id]);
        cout<<endl;
        cout<<"\t\t\t     �����Ƿ�ȷ�ϣ�"<<endl<<endl;
        cout<<"\t\t\t      1.��   2.��"<<endl<<endl;
        cout<<"\t\t\t     �����룺";
        char kkey;
        while (cin>>kkey&&kkey==' '||kkey=='\n');
        if (kkey=='1')
        {
            if (lib_book[id].book_num_now) //ͼ�����
            {
                if (lib_book[id].head==NULL)
                {
                    lib_book[id].head=new node ;
                    lib_book[id].head->next=NULL;
                }
                //ȱ���ظ�����һ��������  //�����ж� �����߸ı�user �� IDֵ����
                //ȱ���жϽ����߽���ͼ����������
                //********************************************************************************************
                if (admin.now_book==3)      //�����Ѵ�����
                {
                    cout<<"\t\t\t     �Բ������Ľ����Ѵ����ޣ����ȿ������Ľ����鼮��"<<endl;
                    cout<<endl;
                    return ;
                }
                node *p;
                p=new node ;
                //�Ǽǽ�������Ϣ
                p->userdata=admin;//��������**********************************************************************
                Give_time(p->brorrow_time);
                p->return_time=Count_time(p->brorrow_time);
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////
                cout<<endl;
                cout<<"\t\t\t     ���ĸ�����Ϣ���£�"<<endl;
                cout<<endl;
                cout<<"\t\t\t     ����֤�ţ�";
                cout<<p->userdata.user_id<<endl<<"\t\t\t     ����������"<<p->userdata.user_name<<endl;
                cout<<"\t\t\t     ���Ľ���ʱ���ǣ�";
                p->brorrow_time.show();
                cout<<endl;
                cout<<"\t\t\t     ���Ĺ黹ʱ���ǣ�";
                p->return_time.show();
                cout<<endl;
                p->next=lib_book[id].head->next;
                lib_book[id].head->next=p;
                lib_book[id].book_num_now--; //�����ȴ��ͼ��
                ////////////////////////////////////////////////////////////////////////////////////
                cout<<"\t\t\t     ����ͼ����Ϣ��ӡ"<<endl;
//                Print_book_All_information(lib_book[id]);
                admin.now_book++;
                cout<<endl;
                cout<<"\t\t\t         ���ĳɹ��� "<<endl;
            }
            else
            {
                cout<<endl;
                cout<<"\t\t\t     But�����ڱ���̫�����ţ��������"<<endl;
                cout<<endl;
                cout<<"\t\t\t     �������Ƿ�ҪԤԼ�Ȿ�飿��"<<endl;
                cout<<endl;
                cout<<"\t\t\t           1.��    2.��"<<endl;
                cout<<"\t\t\t     ";
                char key ;
                while(cin>>key&&key=='\n'||key==' ');
                if (key=='1')
                    Pre_Brorrow_book(tree,id,admin);
                else
                    return ;
            }
        }
    }
    cout<<endl;
}
void Print_Linklist(node *head) //��ӡ����ڵ���Ϣ
{
    node *p=head->next;
    while (p->next)
    {
        p->userdata.show();
//            cout<<p->data<<",";
        p=p->next;
    }
    p->userdata.show();
//        cout<<p->data<<endl;
}
void Info_book(Btree &tree) //ͼ����Ϣ��ҳ��
{
    cout<<"\n\n\n\t\t\t     Welcome,������ͼ����Ϣ����"<<endl;
    cout<<endl;
    cout<<"\t\t\t     ���������Բ�ѯ����һ��ͼ��Ļ�����Ϣ��Ҳ���Բ鿴���е�ͼ����Ϣ!"<<endl;
    while (1)
    {
        info_book(tree);
        cout<<"\t\t\t     �������Ƿ�Ҫ������ѯͼ��������Ϣ��"<<endl;
        cout<<endl;
        cout<<"\t\t\t              1.��       2.��"<<endl;
        cout<<endl;
        cout<<"\t\t\t     �����룺";
        char key ;
        while (cin>>key)
        {
            if (key=='1'||key=='2')
                break;
        }
        if (key=='1');
        else
            break;
    }
    getchar();
    cout<<"\t\t\t     See You Later,�������ز������棡"<<endl;
    cout<<endl;
    cout<<"\t\t\t     ";
    Goto_Other_window();
    system("cls");
    Entry_Menu(tree,admin);
}
void info_book(Btree &tree)//ͼ����Ϣ����ҳ       //��Ҫ��ӹ���         //****************************************************************
{
//    system("cls");
cout<<endl;
    cout<<"\t\t\t     1.����ͼ����Ϣ"<<endl;
    cout<<endl;
    cout<<"\t\t\t     2.�鿴����ͼ��"<<endl;
    cout<<endl;
    cout<<"\t\t\t     ";
    char key;
    while (cin>>key)
    {
        if (key=='1'||key=='2')
            break;
        else
            continue ;
    };
    if (key=='1')
    {
        while(1)
        {
            Info_book_find(tree);//����ͼ��Ļ�����Ϣ
            cout<<"\t\t\t     �������Ƿ�Ҫ������ѯ��"<<endl;
            cout<<endl;
            cout<<"\t\t\t        1.��     2.��"<<endl;
            cout<<endl;
            cout<<"\t\t\t     ";
            char Key;
         while (cin>>Key)
         {
             if(Key=='1'||Key=='2')
                break;
         }
        if (Key=='1')//���� �� 1 ������2 �˳�
            continue ;
        else
            break;
        }
        cout<<endl;
    }
    else
    {

        Info_book_styple(); //��ӡͷ�� ���Ǵ�ӡ��ţ�������
        Btree_Inorder_Info(tree);// �����������ӡ������Ϣ
        cout<<endl<<"\t\t\t     ******************************************************************************         "<<endl;
//        getchar();
    }
                   //*******************************************************************************

}

void Info_book_find(Btree &tree)//��ѯͼ����Ϣ��������
{

        cout<<"\t\t\t     ����������Ҫ��ѯ��ͼ�����"<<endl<<endl;
        cout<<"\t\t\t     ID��";
        int id;
        cin>>id;
        char key;
        Find_res ret=Btree_Search(tree,id);
        if (!ret.yes)
        {
            cout<<endl<<"\t\t\t     �Բ���������Ⲣû���Ȿ�飡"<<endl;
        }
        else
        {
            cout<<"\t\t\t     ����Ҫ��ѯ��ͼ����Ϣ���£�"<<endl;
            cout<<endl;
            Print_book_All_information(lib_book[id]);
//            Info_book_styple();
//            lib_book[id].show();        //////////*********************************************************
            cout<<endl;
        }
        cout<<endl;


}
void Btree_Inorder_Info(Btree &tree)//��ѯͼ����Ϣ����
{
    if (tree==NULL)
        return ;
    int n=tree->keynum;
    int i;
    for (i=1; i<=n; i++)
    {
        Btree_Inorder_Info(tree->child[i-1]);
        int x=tree->key[i];
        lib_book[x].show();        //**************************************��ʾͼ���������Ϣ
        //ȱ�ٽ�����Ϣ��ԤԼ��Ϣ
    }
    Btree_Inorder_Info(tree->child[i-1]);
}
void Btree_INorder(Btree &tree) //B���������
{
    if (tree==NULL)
        return ;
    int n=tree->keynum;
    int i;
    for( i=1; i<=n; i++)
    {
        Btree_INorder(tree->child[i-1]);
        cout<<tree->key[i]<<",";

    }
    Btree_INorder(tree->child[i-1]);
}
void Reader_Push()//��������ͼ��//************************************************************************************
{
    //cout<<"**********"<<endl;
}
void Author_Zone(Btree &tree)//����ר��     ***************************************************************************
/********************************
char key ;
    while (cin>>key &&key=='\n'||key==' '); //��ȡ׼ȷ�ַ�
********************************/
{
//     system("cls");
    cout<<"\n\n\n\t\t\t     ��ӭ��������ר��������һ�������������һ���Ӵ����ߵĵط���"<<endl;
    cout<<endl;
//    getchar();
    while (1)
    {
        author_book_num=0;
        char name[20];
        cout<<"\t\t\t     ����������Ҫ��ѯ����������(20���ַ�����)"<<endl;
        cout<<endl;
        cout<<"\t\t\t     ����������";
        getchar();
        gets(name);
        cout<<endl<<endl;
        cout<<"\t\t\t     ��Ҫ��ѯ�����������ǣ�"<<name<<endl<<endl;
        Btree_Inorder_Search(tree,name);
        if (author_book_num==0)
        {
            cout<<endl;
            cout<<"\t\t\t     ʮ�ֱ�Ǹ�����ǲ�û���κι�����λ���ߵ��鼮�����ǻᾡ�������ص��鼮�ģ�"<<endl;
            cout<<endl;
            cout<<"\t\t\t     ���Ƿ�Ҫ�Ǽ������Ϣ���Ա������´βɹ�ʱ����!"<<endl<<endl;
            cout<<"\t\t\t     1.��   2.��"<<endl;
            cout<<endl;
            cout<<"\t\t\t     �����룺";
            char key ;
            while (cin>>key &&key=='\n'||key==' ');
//            printf("%d %c\n",key,key);
            cout<<endl;
//            getchar();
            if (key=='1')
            {
                Reader_Push();//��������ͼ��          ****************************************************************δд
                    break;
            }
            else
            {
                cout<<"\t\t\t     �������Ƿ�Ҫ�˳�����ר����"<<endl<<endl;
                cout<<"\t\t\t     1.��   2.��"<<endl<<endl;
                char Key;
                cout<<"\t\t\t     �����룺";

                while (cin>>Key &&Key=='\n'||Key==' ');

//            printf("%d %c\n",Key,Key);
                if (Key=='1')
                    break;
                cout<<endl<<endl;
//                getchar();
            }
        }
        else
        {

            //cout<<author_book_num<<endl;
            Info_book_styple();
            for (int i=0; i<author_book_num; i++)
            {
                lib_book[author_book_id[i]].show();

            }
            cout<<endl<<"\t\t\t     ******************************************************************************         "<<endl;
            cout<<endl;

            cout<<"\t\t\t     �������Ƿ�Ҫ�˳�����ר����"<<endl<<endl;
                cout<<"\t\t\t     1.��   2.��"<<endl<<endl;
                char Key;
                cout<<"\t\t\t     �����룺";

            while (cin>>Key &&Key=='\n'||Key==' ');

//            printf("%d %c\n",Key,Key);
            if (Key=='1')
                break;
            cout<<endl<<endl;
//            getchar();
        }

    }
   //getchar();
    cout<<endl<<"\t\t\t     GoodBye(<-^_^->),����������Ҫ����ҳ�棡"<<endl;
    cout<<endl;
    cout<<"\t\t\t     ";
    Goto_Other_window();    //ת��ҳ�涯��
    system("cls");
    Entry_Menu(tree,admin);      ///��ҳ�� ***************************************************************************************
    //�˳��ӿ�
    //**********************************************************************************************************************
}

void Btree_Inorder_Search(Btree &tree,char name[]) //�������ÿһ���ڵ���Ϣ
{
    if (tree==NULL)
        return ;
    int i;
    int n=tree->keynum;
    for (i=1; i<=n; i++)
    {
        Btree_Inorder_Search(tree->child[i-1],name);
        int  x=tree->key[i];
        if (strcmp(lib_book[x].book_author,name)==0)
        {
            author_book_id[author_book_num]=x;
            author_book_num++;
//                 cout<<x<<endl;
        }
    }
    Btree_Inorder_Search(tree->child[i-1],name);

}
inline void Init_lib() //���������
{
    book a(1,"123  15","1 2","1","1",2,20);
    lib_book[1]=a;
//    Info_book_styple();
//    a.show();
    book b(2,"abcd","1 2","1","1",2,20);
    lib_book[2]=b;
//    b.show();
    book c(3,"stop!!","1 2","1","1",2,20);
    lib_book[3]=c;
//    c.show();
    book d(4,"***456","1 2","1","1",2,20);
    lib_book[4]=d;
//    d.show();
    book e(5,"***456","1 2 3","1","1",2,20);
    lib_book[5]=e;
//    e.show();
    book f(6,"�ط�","4 5","1","1",2,20);
    lib_book[6]=f;
//    f.show();
    book g(7,"1","4 5","1","1",2,20);
    lib_book[7]=g;
//    g.show();
    book h(8,"wangzhe","df","1","1",2,20);
    lib_book[8]=h;
//    h.show();
    book i(9,"666��˹","xxx","1","1",2,20);
    lib_book[9]=i;
//    i.show();
    book j(10,"��Ŷ123!","1234","1","1",2,20);
    lib_book[10]=j;
//    j.show();


}
inline void Info_book_styple()// ��ӡͼ��Ļ�����Ϣ��
{
    cout<<"\t\t\t     ******************************����Ļ�����Ϣ**********************************         "<<endl;
    cout<<"\t\t\t     "<<setiosflags(ios_base::right)<<setw(6)<<"���"<<resetiosflags(ios_base::right)<<setw(10)<<"����"<<setw(10)<<"����"
        <<setw(10)<<"������"<<setw(12)<<"����ʱ��"<<setw(8)<<"����"
        <<setw(10)<<"�ִ���"<<setw(10)<<"�ܴ���"<<endl<<endl;
}
/*****
// test����data

*****/
inline void  Print_book(book &b) //�����ӡͼ����Ϣ
{
    //��λ����
    Info_book_styple();//��Ļ��� ��Ϣ
    b.show();
    cout<<endl<<"\t\t\t     ******************************************************************************         "<<endl;
    cout<<endl;
}
void delete_book(Btree &tree) //ɾ��ͼ������ҳ
{
    cout<<"\t\t\t     ��������Ҫɾ������ţ�";
    int tmp;
    cin>>tmp;
    cout<<endl;
    Find_res ret = Btree_Search(tree,tmp);
    if(!ret.yes)
    {
        cout<<"\t\t\t     Sorry, ���ǵ���Ⲣû���Ȿ�飡"<<endl;
        cout<<endl;
    }
    else
    {
        cout<<"\t\t\t     ��Ҫɾ����ͼ����ϢΪ��"<<endl;
        Print_book(lib_book[tmp]);
        char key;
        cout<<"\t\t\t     ȷ��Ҫɾ��������"<<endl<<endl;
        cout<<"\t\t\t     1.��   2.��"<<endl<<endl;
        cout<<"\t\t\t     �����룺";
        cin>>key;
        if (key=='2')
        {
            return ;
        }
        bool yes=Btree_Delete(tree,tmp);
        lib_book[tmp].book_judge=0;
        cout<<endl;
        cout<<"\t\t\t     ����ɹ���-_-"<<endl<<endl;;
        cout<<"\t\t\t     ɾ�����B�����£�"<<endl;
        Btree_show(tree);
        cout<<endl<<endl;
    }
}
void Delete_book( Btree &tree ) //���ͼ��ҳ��
/****************************************
    ȱ��esc��ؽ���
    ��ӡλ�õ�ȷ��
    ���������
    Write By XPF
****************************************/
{

    char out_key;
    cout<<"\n\n\n\t\t\t     ��ӭ����ͼ�����֮������ϵͳ ^_^!"<<endl<<endl;
    while(1)
    {
        delete_book(tree);
        cout<<"\t\t\t     ���ʣ����Ƿ������ɾ��ͼ��?"<<endl<<endl;
        cout<<"\t\t\t     ��2���ع���Ա���棬������������ִ�в���!"<<endl<<endl;
        cout<<"\t\t\t     ";
        cin>>out_key;
        if (out_key=='2')
            break;
        cout<<endl;
    }

    getchar();
    cout<<"\t\t\t     ͼ��ɾ����ϣ��������ع���Ա���棡"<<endl;
    cout<<endl;
    cout<<"\t\t\t     ";
    Goto_Other_window();
    system("cls");
    Admin_Menu(tree);
//�������˵�                                                                         *******************
//    Sleep(1000);
//    system("cls");
//     main_window();
}
void add_book(Btree &tree) //���ͼ������ҳ
{
    cout<<endl;
    cout<<"\t\t\t     ��������ţ� ";
    book tmp;
    cin>>tmp.book_id;
    int x =tmp.book_id;
    Find_res ret=Btree_Search(tree,x);
    if (ret.yes)
    {
        Print_book(lib_book[x]);
        cout<<"\t\t\t     ����������⣡"<<endl<<endl;
        cout<<"\t\t\t     ����������ͼ��������";
        //cout<<endl;
        int add;
        cin>>add;
        lib_book[x].book_num_all+=add;
        lib_book[x].book_num_now+=add;
        Print_book(lib_book[x]);

        return ;
    }
//    Insert(tree,tmp.book_id);
//    lib_book[book_num].book_id=tmp_id;
    while (getchar()!='\n');// ȥ���޹�����
    cout<<"\t\t\t     ������������ ";
    gets(tmp.book_name);
//    gets(lib_book[book_num].book_name);
//    getchar();
    cout<<"\t\t\t     ���������ߣ� ";
    gets(tmp.book_author);
//    gets(lib_book[book_num].book_author);
//    getchar();
    cout<<"\t\t\t     ����������磺 ";
    gets(tmp.book_pulish);
//    gets(lib_book[book_num].book_pulish);
//    getchar();
    cout<<"\t\t\t     ���������ʱ�䣺";
    gets(tmp.book_time);
//    gets(lib_book[book_num].book_time);
//    getchar();
    cout<<"\t\t\t     ��������Ķ��ۣ� ";
    cin>>tmp.book_values;
    while (getchar()!='\n');// ȥ���޹�����
//    cin>>lib_book[book_num].book_values;
//    getchar();
    cout<<"\t\t\t     ��������������� ";
    cin>>tmp.book_num_all;
    while (getchar()!='\n');// ȥ���޹�����
//    cin>>lib_book[book_num].book_num_all;
//    getchar();
    lib_book[book_num].book_num_now=lib_book[book_num].book_num_all;
    cout<<endl;
    cout<<"\t\t\t     Ҫ��ӵ�ͼ����Ϣ���£�"<<endl;
    Info_book_styple();
    tmp.book_num_now=tmp.book_num_all;
    tmp.show();
    cout<<endl<<"\t\t\t     ******************************************************************************         "<<endl;
    cout<<endl;
    cout<<"\t\t\t     ��ȷ��Ҫ����Ȿ����"<<endl<<endl;
    cout<<"\t\t\t     1.��   2.��"<<endl<<endl;
    char book_insuree;
    cout<<"\t\t\t     �����룺";
    cin>>book_insuree;   //ȷ���Ƿ����ͼ��
    if (book_insuree=='1')
    {
        tmp.book_judge=1;
//        lib_book[book_num++].show();
        lib_book[tmp.book_id]=tmp;
        book_num++;
        cout<<endl;
        Btree_Insert(tree,x);
        cout<<"\t\t\t     ������B�����£�"<<endl;
//        Show_BTree(tree);
        Btree_show(tree);
        cout<<endl<<endl;
    }
    getchar();
}
void Add_Book( Btree &tree ) //���ͼ��ҳ��   **************************************************************************
/****************************************
    ȱ��esc��ؽ���
    ��ӡλ�õ�ȷ��
    ���������
    Write By XPF
****************************************/
{

    char key;
    cout<<"\n\n\n\t\t\t     ��ӭ����ͼ�����֮�ɱ����ϵͳ ^_^!"<<endl<<endl;
    cout<<"\t\t\t     ��ӭ��Ϊ���ǵ�ͼ�����ש����^_^"<<endl;
    cout<<endl;
    cout<<"\t\t\t     ����������ҳ��"<<endl;
    while(1)
    {
        add_book(tree);
        cout<<"\t\t\t     ���ʣ����Ƿ���������ͼ��??"<<endl<<endl;
        cout<<"\t\t\t     1.��   2.��"<<endl<<endl;
        cout<<"\t\t\t     �����룺";
        while (cin>>key)
        {
            if (key=='1'||key=='2')
                break;
            else
                continue ;
        };
        if (key=='2')
            break;
        cout<<endl;
    }

    cout<<endl;
    getchar();
    cout<<"\t\t\t     ͼ��¼����ϣ��������ع���Ա��ҳ�棡"<<endl<<endl;
    cout<<"\t\t\t     ";
        Goto_Other_window();// ----ת��ҳ�涯��   *********************************************************************
        system("cls");
        Admin_Menu(tree);
//�������˵�
//    Sleep(1000);
//    system("cls");
//     main_window();
}

