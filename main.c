#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

//��̬�ڴ����
//ջ�����ֲ���������������ʽ����
//��������̬�ڴ����
//��̬����ȫ�ֱ��� ��̬����


//��ǰ����֪����ʹ���ڴ�ķ�ʽ��
//1:����һ������
//int a = 10; //�ֲ�����-ջ��
//int ga = 20; //ȫ�ֱ���-��̬��
//2:����һ������
//int arr[10]; //�ֲ����� ����ջ�� ȫ�ַ�Χ������ھ�̬��


//malloc(size_t size); //���ڴ������ƶ��ֽڵĿռ� ���ص�ַ��ָ��(void*)
// free(void* mem); //���տռ� ���mallocʹ��


//calloc(size_t number,size_t size) //�����ƶ������Ŀռ䣬����ʼ��Ϊ0

//realloc(void* memory,size_t newsize);
//realloc()ʹ��ע�����
//1:��pָ��Ŀռ�� ���㹻�Ŀռ����׷�ӣ���ֱ��׷�Ӻ��棬����p
//2:��pָ��Ŀռ�� û���㹻�Ŀռ䣬��realloc������Ѱ��һ���µ��ڴ�����
//����һ����������Ŀռ䣬���Ұ�ԭ�����ڴ�����copy�������ͷžɵĿռ� ��󷵻��µ��ڴ��ַ
//3:����ʹ��һ���µı����洢realloc�ķ���ֵ

//free() ֻ���ͷ� ��̬�ڴ濪�ٵĿռ�(����)
struct student {
    char name[20];
    int age;
};

int main1() {

//    struct student arr[50]; //50��struct student���͵�����
    //30 - �˷�             //�����Ԫ�ظ���������һ������

    //���ڴ�����10�����οռ�,���ص�ַ��ָ��void*
//    int *p = (int *) malloc(10 * sizeof(int));
    int *p = (int *) malloc(10 * INT_MAX);
//    printf("%p\n",p); //0000021190ba1420

    if (p == NULL) {
        //��ӡ����ԭ��
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
    //���������ڴ�
    free(p);
    //������ֵ��ָ��
    p = NULL;
    return 0;
}

int main2() {
    //����10�� int���͵Ŀռ�
    int *p = (int *) calloc(10, sizeof(int));
    if (p == NULL) {
        printf("%s", strerror(errno));
    }

    int i = 0;
    for (i = 0; i < 10; i++) {
        printf("%d\n", *(p + i)); //�Ѿ���ʼ��Ϊ0
    }

    //�ͷſռ�
    free(p); //free()���������ͷ� ��̬���ٵĿռ�
    p = NULL;
    return 0;
}

int main3() {


    //realloc(); ������̬���ٿռ�Ĵ�С
    int *p = (int *) malloc(20);
    if (NULL == p) {
        printf("%s", strerror(errno));
    } else {
        int i = 0;
        for (i = 0; i < 5; i++) {
            *(p + i) = i; //ʹ�ÿ��ٵ�mallloc�ռ� 20���ֽڵĿռ�
        }
    }
    //���裺20���ֽڲ�������ռ�
    //����ʹ��realloc()��������̬���ٵĿռ�
    int *np = (int *) realloc(p, 40); //��p����Ϊ40���ֽ�

    if (NULL == np) {
        printf("%s", strerror(errno));

    }
    int i = 0;
    for (i = 4; i < 10; i++) {
        *(p + i) = i; //ʹ�ÿ��ٵ�mallloc�ռ� 20���ֽڵĿռ�
    }
    for (i = 0; i < 10; i++) {
        printf("%d ", *(np + i));

    }
    free(p);
    p = NULL;

    int a = 10;
    int *pa = &a;

//    free(pa); error a��ջ��

    int *rp = realloc(NULL, 40);// �൱�� malloc(40);

    return 0;
}


//��̬�ڴ泣���������
/*int main4()
{
    //1����NULLָ�� ������
    int *p = malloc(40);
    *p = 10; //��malloc����ʧ��-error

    //2:�Զ�̬�����ڴ��Խ�����
    int *p2 = (int*)malloc(40);
    if(p2 == NULL)
    {
        printf("%s",strerror(errno));
    }
    int i = 0;
    for(i = 0;i <10; i++ )
    {
        *(p+i)= i; //error �ڴ�Խ��
    }

    //3:���ڷǶ�̬���ٵ��ڴ�ʹ��free����
    int a = 10;
    int *pa = &a;
    free(pa); //error
    pa = NULL;

    //4:ʹ��free�ͷŶ�̬�ڴ濪���ڴ��һ����
    int* p3 = (int*)malloc(40);
    if(p3 == NULL)
    {
        return 0;
    }

    for(i = 0; i<10 ; i++)
    {
        *p3++ = i; //error  pָ�������
    }
    //���տռ�
    free(p3); //p�仯�ˣ�����ָ�򿪱ٵ���ʼλ��
    p3 = NULL;

    //5: ��ͬһ�鶯̬���ٿռ�Ķ���ͷ�
    int* p4 = (int*)malloc(40);
    if(p4 == NULL)
    {
        printf("%s",strerror(errno));
    }
    free(p4);
    p4 = NULL; //���б�Ҫ
    //.....
    free(p4); //error

    //6: ��̬�����ڴ������ͷ� (�ڴ�й©)
    while(1)
    {
        malloc(20); //error
//        Sleep(1000);
    }

}*/

/*  //�����⣺
void getMem(char *p) //�β���һ����ʱcopy
{
    p  = (char*) malloc(100); //�������� p������ ���ڴ�û���ͷ�
}
void test(void){
    char* str = NULL;
    getMem(str); //��ֵ
    strcpy(str,"Hello,world"); //str��һ��NULL ������� �����ڴ�ʧ��
    printf(str);
}
int main()
{

    test(); //�������
}
*/

/*
char *getMem(void) {
    char p[] = " Hello world !";
    return p;  //��ʱp���β� ��ŵĵ�ַ��ջ �������� ���������� ���ַǷ����ʵ����� �����κε�ַ����Ч��
}

void test(void) {
    char *str = NULL;
    str = getMem(); //����ջ�ռ��ַ����
    printf(str);
}

int main() {
    test(); //error
    return 0;
}
*/
/*
int *test() {
    int *p = malloc(20); //��Ϊ��ŵ��� �ѿռ䣬���˷��� �ǲ������ٵ�
    return p;
}

int main() {
    int *p = test();
    return 0;
}
*/
/*
void getMem(char **p, int num) {
    *p = (char *)malloc(num); //�ڴ�й© û��free
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

    free(str); //��free�������str��Ϊnull

    if(str!= NULL)
    {
        strcpy(str,"world");  //�Ƿ������ڴ� �ͷź�Ŀռ䱻ʹ��
        printf(str);
    }
}
int main()
{
    test();
    return 0;
}
*/

//�������� c99�г���
/*
struct s {
    int n;
//    int arr[]; //δ֪��С ���������Ա
    int arr[0]; //��һ��д��
};

int main() {
    struct s s;
    printf("%d\n", sizeof(s)); //4  û�а��������С

    //ϣ�������ж�� ��+����
    struct s *ps = (struct s *) malloc(sizeof(s) + 10 * sizeof(int));
    ps->n = 100;
    int i = 0;
    for (i = 0; i < 5; i++) {
        ps->arr[i] = i;
    }

    //����
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
    int* arr; //��ʹ������ ʹ��ָ�� ָ��һ���ռ�
};

int main()
{
    struct s* sp =(struct s*) malloc(sizeof(struct s));
    //��arrָ��һ���ɱ��ָ�� ������������
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

    //������С
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

    //��Ϊsp-arr �Ƕ�����
    free(sp->arr);
    free(sp);
}
//��������ĺô���
// 1:����malloc�Ĵ����������ڴ��ͷ�
// 2�������ڷ����ٶ�(�����ڴ�)

