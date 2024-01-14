#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//1. 데이터를 정렬해야했는데 구조체는 변수선언이 가능하므로 단순대입이 가능. 따라서 버블정렬을 이용해 정렬함
//2. 구조체 배열을 선언하고 그것을 함수를 통해 데이터를 다룰때 화살표연산, 배열처리 등을 공부할 수 있었음
//3. 연결리스트를 만들때 마지막 노드의 next변수는 NULL포인터를 가리키고 있는지 확인해보기
//4. 함수들의 매개변수의 자료형이 Student인 이유는 Student라는 자료형을 typedef로 새로 정의했기 때문이다.
//따라서 struct*가 아닌 Student*가 되는 것이다. 

typedef struct Grade
{
    int Korean;
    int English;
    int math;
}Grade;

typedef struct Score
{
    int sum;//총점
    double avg;//평균값
    char grade;//학점
    int rank;//순위
}Score;

typedef struct Student
{
    int schoolnumber;//학번
    char name[20];//이름
    Grade score3;//3과목
    Score num;
    struct Student* next;
}Student;

void InitData(Student*);
void TestGrade(Student*);
void LineupStudent_sum(Student*);
void PrintStudent(Student*);

int main()
{
    Student s[5];

    InitData(s);
    printf("\n");
    printf("# 정렬 전 데이터\n");
    PrintStudent(s);
    printf("\n");
    LineupStudent_sum(s);
    printf("# 정렬 후 데이터\n");
    PrintStudent(s);

    return 0;
}

void TestGrade(Student* ps)
{
    ps->num.sum = ps->score3.Korean + ps->score3.English + ps->score3.math;
    ps->num.avg = ps->num.sum / 3.0;

    if (ps->num.avg >= 90.0)
        ps->num.grade = 'A';
    else if (ps->num.avg >= 80.0)
        ps->num.grade = 'B';
    else if (ps->num.avg >= 70.0)
        ps->num.grade = 'C';
    else   
        ps->num.grade = 'F';
}

void LineupStudent_sum(Student* ps)
{
     Student temp;
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            if ((ps + i)->num.sum < (ps + j)->num.sum)
            {
                temp = *(ps + i);
                *(ps + i) = *(ps + j);
                *(ps + j) = temp;
            }
        }
    }
}

void InitData(Student* ps)
{
    for (int i = 0; i < 5; i++) {
        printf("학번: ");
        scanf("%d", &(ps+i)->schoolnumber);
        printf("이름: ");
        scanf("%s", (ps+i)->name);//&연산자가 없는 이유는 (ps+i)가 가리키는 name이 배열이기 때문이다.
        printf("국어 영어 수학 점수: ");
        scanf("%d%d%d", &(ps+i)->score3.Korean,&(ps+i)->score3.English, &(ps+i)->score3.math);
        
        //NULL이 나와도 돌아가는 이유와, InitData가 아니라 PrintStudent함수를 건드려야 함
        (ps+i)->next = ps+i;
        (ps+4)->next=NULL;
        TestGrade(ps+i);
    }
}

void PrintStudent(Student* ps)
{
    //학번 이름 국영수 총점 평균 학점
    int i=0;
    while((ps+i)->next != NULL){
    printf("%d %s %d %d %d %d %.1lf %c %p\n",
    (ps+i)->schoolnumber, (ps+i)->name, 
    (ps+i)->score3.Korean, (ps+i)->score3.English, (ps+i)->score3.math, 
    (ps+i)->num.sum, (ps+i)->num.avg, (ps+i)->num.grade, (void*)(ps+i)->next);//연결리스트를 위한 next값 출력해보기
    i++;
    }
}

/*void PrintStudent(Student* ps)
{
    //학번 이름 국영수 총점 평균 학점
    for(int i=0;i<5;i++){
    printf("%d %s %d %d %d %d %.1lf %c %p\n",
    (ps+i)->schoolnumber, (ps+i)->name, 
    (ps+i)->score3.Korean, (ps+i)->score3.English, (ps+i)->score3.math, 
    (ps+i)->num.sum, (ps+i)->num.avg, (ps+i)->num.grade, (void*)(ps+i)->next);//연결리스트를 위한 next값 출력해보기
    }
}*/
//(ps+i)->는 ps[i]. 과 같은 의미이다. 왜나하면 배열은 사실상 포인터이기 때문이다.
//.(도트)연산자는 클래스의 멤버에 직접적으로 접근한다. ->(화살표)는 포인터를 통해 멤버를 간접적으로 접근한다.
//즉 a->b는 (*a).b와 동일하다.
//ip[i].name == (*(lp+i)).name == (lp+i)->name
//보통은 도트연산자 ( . )를 사용해서 맴버에 접근하지만, 구조체 포인터의 맴버에 접근할 때는 화살표( -> )로 접근해야 한다.
