#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

//动态内存管理
//栈区：局部变量，函数的形式参数
//堆区：动态内存分配
//静态区：全局变量 静态变量


//当前我们知道的使用内存的方式：
//1:创建一个变量
//int a = 10; //局部变量-栈区
//int ga = 20; //全局变量-静态区
//2:创建一个数组
//int arr[10]; //局部数组 放在栈区 全局范围数组放在静态区


//malloc(size_t size); //向内存申请制定字节的空间 返回地址的指针(void*)
// free(void* mem); //回收空间 配合malloc使用


//calloc(size_t number,size_t size) //开辟制定个数的空间，并初始化为0

//realloc(void* memory,size_t newsize);
//realloc()使用注意事项：
//1:若p指向的空间后 有足够的空间可以追加，则直接追加后面，返回p
//2:若p指向的空间后 没有足够的空间，则realloc会重新寻找一个新的内存区域
//开辟一块满足需求的空间，并且把原来的内存数据copy过来，释放旧的空间 最后返回新的内存地址
//3:必须使用一个新的变量存储realloc的返回值

//free() 只能释放 动态内存开辟的空间(堆区)
struct student {
    char name[20];
    int age;
};

int main1() {

//    struct student arr[50]; //50个struct student类型的数组
    //30 - 浪费             //数组的元素个数必须是一个常量

    //向内存申请10个整形空间,返回地址的指针void*
//    int *p = (int *) malloc(10 * sizeof(int));
    int *p = (int *) malloc(10 * INT_MAX);
//    printf("%p\n",p); //0000021190ba1420

    if (p == NULL) {
        //打印错误原因
        printf("%s", strerror(errno));
    } else {
        int i = 0;
        for (i = 0; i < 10; i++) {
            *(p + i) = i;
        }
        for (i = 0; i < 10; i++) {
            printf("%d ", *(p + i));
        }
    }
    //主动回收内存
    free(p);
    //主动赋值空指针
    p = NULL;
    return 0;
}

int main2() {
    //开辟10个 int类型的空间
    int *p = (int *) calloc(10, sizeof(int));
    if (p == NULL) {
        printf("%s", strerror(errno));
    }

    int i = 0;
    for (i = 0; i < 10; i++) {
        printf("%d\n", *(p + i)); //已经初始化为0
    }

    //释放空间
    free(p); //free()函数用来释放 动态开辟的空间
    p = NULL;
    return 0;
}

int main3() {


    //realloc(); 调整动态开辟空间的大小
    int *p = (int *) malloc(20);
    if (NULL == p) {
        printf("%s", strerror(errno));
    } else {
        int i = 0;
        for (i = 0; i < 5; i++) {
            *(p + i) = i; //使用开辟的mallloc空间 20个字节的空间
        }
    }
    //假设：20个字节不能满足空间
    //可以使用realloc()来调整动态开辟的空间
    int *np = (int *) realloc(p, 40); //将p调整为40个字节

    if (NULL == np) {
        printf("%s", strerror(errno));

    }
    int i = 0;
    for (i = 4; i < 10; i++) {
        *(p + i) = i; //使用开辟的mallloc空间 20个字节的空间
    }
    for (i = 0; i < 10; i++) {
        printf("%d ", *(np + i));

    }
    free(p);
    p = NULL;

    int a = 10;
    int *pa = &a;

//    free(pa); error a在栈区

    int *rp = realloc(NULL, 40);// 相当于 malloc(40);

    return 0;
}


//动态内存常见错误操作
/*int main4()
{
    //1：对NULL指针 解引用
    int *p = malloc(40);
    *p = 10; //若malloc开辟失败-error

    //2:对动态开辟内存的越界访问
    int *p2 = (int*)malloc(40);
    if(p2 == NULL)
    {
        printf("%s",strerror(errno));
    }
    int i = 0;
    for(i = 0;i <10; i++ )
    {
        *(p+i)= i; //error 内存越界
    }

    //3:对于非动态开辟的内存使用free函数
    int a = 10;
    int *pa = &a;
    free(pa); //error
    pa = NULL;

    //4:使用free释放动态内存开辟内存的一部分
    int* p3 = (int*)malloc(40);
    if(p3 == NULL)
    {
        return 0;
    }

    for(i = 0; i<10 ; i++)
    {
        *p3++ = i; //error  p指向最后了
    }
    //回收空间
    free(p3); //p变化了，不在指向开辟的起始位置
    p3 = NULL;

    //5: 对同一块动态开辟空间的多次释放
    int* p4 = (int*)malloc(40);
    if(p4 == NULL)
    {
        printf("%s",strerror(errno));
    }
    free(p4);
    p4 = NULL; //很有必要
    //.....
    free(p4); //error

    //6: 动态开辟内存忘记释放 (内存泄漏)
    while(1)
    {
        malloc(20); //error
//        Sleep(1000);
    }

}*/

/*  //面试题：
void getMem(char *p) //形参是一份临时copy
{
    p  = (char*) malloc(100); //方法结束 p销毁了 且内存没有释放
}
void test(void){
    char* str = NULL;
    getMem(str); //传值
    strcpy(str,"Hello,world"); //str是一个NULL 程序崩溃 访问内存失败
    printf(str);
}
int main()
{

    test(); //程序崩溃
}
*/

/*
char *getMem(void) {
    char p[] = " Hello world !";
    return p;  //此时p是形参 存放的地址是栈 方法结束 变量销毁了 出现非法访问的问题 返回任何地址是无效的
}

void test(void) {
    char *str = NULL;
    str = getMem(); //返回栈空间地址问题
    printf(str);
}

int main() {
    test(); //error
    return 0;
}
*/
/*
int *test() {
    int *p = malloc(20); //因为存放的是 堆空间，出了方法 是不会销毁的
    return p;
}

int main() {
    int *p = test();
    return 0;
}
*/
/*
void getMem(char **p, int num) {
    *p = (char *)malloc(num); //内存泄漏 没有free
}
void test(void)
{
    char* str = NULL;
    getMem(&str,100);
    strcpy(str,"Hello");

    printf(str);

}
int main()
{
    test();
    return 0;
}*/
/*
void test()
{
    char* str = (char*) malloc(100);
    strcpy(str,"Hello");

    free(str); //释free并不会把str置为null

    if(str!= NULL)
    {
        strcpy(str,"world");  //非法访问内存 释放后的空间被使用
        printf(str);
    }
}
int main()
{
    test();
    return 0;
}
*/

//柔性数组 c99中出现
/*
struct s {
    int n;
//    int arr[]; //未知大小 柔型数组成员
    int arr[0]; //另一种写法
};

int main() {
    struct s s;
    printf("%d\n", sizeof(s)); //4  没有包含数组大小

    //希望数组有多大 就+多少
    struct s *ps = (struct s *) malloc(sizeof(s) + 10 * sizeof(int));
    ps->n = 100;
    int i = 0;
    for (i = 0; i < 5; i++) {
        ps->arr[i] = i;
    }

    //调整
    struct s * ss = realloc(ps,10 * sizeof(int));
    if(ss!= NULL)
    {
        ss = ps;
    }
    for(i = 5; i <10; i++)
    {
        ss->arr[i] = i;
    }

    for(i = 0; i<10;i++)
    {
        printf("%d ",ss->arr[i]);
    }

    free(ss);
    ss= NULL;
}
*/
struct s
{
    int n;
    int* arr; //不使用数组 使用指针 指向一个空间
};

int main()
{
    struct s* sp =(struct s*) malloc(sizeof(struct s));
    //让arr指向一个可变的指针 完成数组的设置
    sp->arr = malloc(5*sizeof(int));

    int i = 0;
    for(i = 0; i < 5; i++)
    {
        sp->arr[i] = i;
    }
    for(i= 0; i < 5 ; i++)
    {
        printf("%d ",sp->arr[i]);
    }
    printf("\n\n");

    //调整大小
    int * ptr = realloc(sp->arr,sizeof(int)*10);
    if(ptr != NULL)
    {
        sp->arr = ptr;
    }
    for(i = 5; i < 10; i++)
    {
        sp->arr[i] = i;
    }

    for(i =0 ;i < 10; i++)
    {
        printf("%d ",sp->arr[i]);
    }

    //因为sp-arr 是独立的
    free(sp->arr);
    free(sp);
}
//柔型数组的好处：
// 1:减少malloc的次数，方便内存释放
// 2：有利于访问速度(连续内存)

