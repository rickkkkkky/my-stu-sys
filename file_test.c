#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
typedef struct userdata//
{
    int num;
    char name[20];
    char password[20];
    char sex[20];
    int age;
    int score;
    struct userdata  *next;
} userdata_t;
typedef enum list
{
    teacher_list=2,
    student_list=6
} list_m;
typedef enum sex
{
    man,
    woman,
    secret
} sex_m;
char login_interface();
char console_interface(userdata_t * head);
userdata_t * list_init(int list_type,char *file_name);
userdata_t* list_changed(userdata_t * head);
void  list_del(userdata_t * head);
void  Register_users(userdata_t * head);
char * sign_up(userdata_t * head);
void student_inquire(userdata_t * head);
userdata_t *student_sort(userdata_t * head);
userdata_t *add_stu(userdata_t * head);
userdata_t *delete_stu(userdata_t *head);
userdata_t * import_information(userdata_t * head);
void stu_statistic(userdata_t *head);
void save_stu(userdata_t *head,char *file_name);
void buffer_print(userdata_t *head);
void pause();

char * filename=NULL;
int main()
{
    userdata_t *head;
    system("chcp 65001");
    system("cls");
    login:
    filename=NULL; 
    char cons;
    head=list_init(teacher_list,"user_data.txt"); 
    switch (login_interface())
    {
    case 49:
        filename =sign_up(head);
        if(filename==NULL)
        {
            goto login;
        }
        break;
    case 50:        
        Register_users(head);
        list_del(head);
        goto login;
        break;
    case 51:
        return 2;
    default:
       
        break;
    }
    list_del(head);
    filename=strcat(filename,".txt");
    head=list_init(student_list,filename); 
    while (1)
    {   
        cons=console_interface(head);

        switch (cons)
        {
        case 49: //1 添加学生
            head=add_stu(head);
            break;
        case 50:        
            head=delete_stu(head);
            // buffer_print(head);        
            break;
        case 51://3 �?改成�?
            head=list_changed(head);
            break;
        case 52: //4 查�?��?�生信息
            student_inquire(head);
            break;
        case 53:    //5 统计
            stu_statistic(head);
            break;
        case 54: //6  学生成绩排序
            head=student_sort( head);
            break;
        case 55: // 7保存信息 
            save_stu(head,filename);
            head=list_init(student_list,filename); 
            break;            
        case 56: //8 导入信息
            head=import_information(head);
            break;
        case 57 ://9 退出用�?
            goto login; 
            break;
        case 48 : // 0退出软�?
            list_del(head);
            return 0;
            break;
        default:
            break;
        }
    }
    return 1;

}
char login_interface()
{
    char a[5];
    system("cls");
    printf("\n欢迎使用学生信息管理系统\n");
    printf("1.登录  2.注册 3.退出系统\n");
    while(1)
    {
        scanf("%2[0-9]",a); 
        while ( getchar() != '\n' );
        if(atoi(a) > 3||atoi(a)<1) 
            printf("非法输入,请重新输入\n");
        else
        {   
                return a[0];   
        }
        
    }
}

char console_interface(userdata_t * head)
{
    char a[5]={0};
    char name[10]={0};
    system("cls");
    printf("%s的学生信息如下 \n",strncpy(name,filename,strlen(filename)-4));
    printf("————————————————————————————————————————————————\n");
    printf("序号 姓名       学号       性别       年龄 成绩\n");
    buffer_print(head);
    printf("————————————————————————————————————————————————\n");
    printf("修改学生后请注意保存,保存后自动刷新序号\n");
    printf("\t\t\t功能菜单\n");
    printf("1.添加学生信息 2.删除学生信息     3.修改学生信息 4.查询学生信息 5.班级信息统计\n");
    printf("6.学生排序     7.保存当前学生信息 8.导入学生信息 9.退出当前用户 0.退出系统\n");
    while(1)
    {
        scanf("%2[0-9]",a);
        while ( getchar() != '\n' );
        if(strlen(a)>=2) 
            printf("非法输入,请重新输入\n");
        else
        {   
            if(a[0]>='0' && a[0]<='9')
                return a[0];   
        }
        
    
    }
}
void  Register_users(userdata_t * head)//
{
    FILE * fp;
    char name[25]={0};
    char password[25]={0};
    userdata_t * p = head;
    fp = fopen("user_data.txt","a+");
    if(fp == NULL){
        printf("文件打开失败!\n");
        exit(0); 
    }
    printf("请输入您的用户名\n");
    scanf("%10s",name);
    while ( getchar() != '\n' );
    while(p!=NULL)
    {
        if(strcmp(name,p->name) ==0)
        {
            printf("用户名已存在!\n");
            pause();
            return;
        }
        p=p->next;
    }


    fprintf(fp,"%s ",name);

    printf("请输入您的密码\n");
    scanf("%10[a-zA-Z0-9]",password);
    while ( getchar() != '\n' );

    fprintf(fp,"%s\n",password);
    fclose(fp);
    printf("注册成功\n");
    pause();
}
char * sign_up(userdata_t * head) 
{
    userdata_t *p;
    static char name[25]={0};
    char password[25];
    p=head;
    system("cls");
    printf("请输入您的用户名\n"); 
    scanf("%15s",name);
    while ( getchar() != '\n' );

    if(head==NULL)    
    {
        printf("用户名不存在 请先注册\n");
        pause();
        return NULL;
    }
    while(strcmp(p->name,name)!=0) 
    {
        if(p->next==NULL)
        {
            printf("用户名不存在!请先注册\n");
            pause();
            return NULL;
          
        }

        p=p->next;
    }
    printf("请输入您的密码\n");
    scanf("%10[a-zA-Z0-9]",password);while ( getchar() != '\n' );
    if(0==strcmp(p->password,password))
    {
        printf("登录成功!\n");
    }
    else
    {
        printf("密码错误!\n");
        pause();
        return NULL;
    }
    pause();   
    return name;


}

userdata_t * list_init(int list_type,char *file_name)
{
    FILE * fp;
    userdata_t *head,*p1,*p2;
    fp = fopen(file_name,"a+");    
    if(fp == NULL){
        printf("文件打开失败!\n");
        pause();
        exit(0); 
    }
    head=NULL;
    p1=p2=(userdata_t *)calloc(1,sizeof(userdata_t));
    switch (list_type)
    {
        case 2:
            while (fscanf(fp,"%s%s",p2->name,p2->password)!=EOF)
            {
                if(head==NULL)
                {
                    head=p1;
                }
                else
                {
                    p1->next=p2;            
                }
                p1=p2;
                p2=(userdata_t *)calloc(1,sizeof(userdata_t));  
            }
           
            break;
        case 6:
            while ( fscanf(fp,"%d%s%s%s%d%d",&p2->num,p2->name,p2->password,p2->sex,&p2->age,&p2->score)!=EOF)
            {
                if(head==NULL){
                    head=p1;
                }
                else{
                    p1->next=p2;            
                }
                p1=p2;
                p2=(userdata_t *)calloc(1,sizeof(userdata_t));              
            }
            break;
        default:
            break;
    }
    fclose(fp);
    p1->next=NULL;
    return head;
}

void  list_del(userdata_t * head)
{
    userdata_t * p;
    if(head!=NULL)
    {
        while (NULL != head->next)
        {        
            p=head->next;
            free(head);
            head=p;
        }
    
    free(head);
    }
}
userdata_t* list_changed(userdata_t * head) 
{
    userdata_t *p;
    p=head;
    char name[20]={0};
    char a[5];
    if(head==NULL)
    {
        printf("没有学生信息,请先先添加\n");
        pause();
        return head;
    }
    printf("请输入需要修改的学生学号\n");
    scanf("%15s",name);while ( getchar() != '\n' );
    if(strcmp(p->password,name)==0)
    {

    }
    else
    {
        while(p->next!=NULL&&strcmp(p->password,name))
        {

            p=p->next;
        }
        if(strcmp(p->password,name)!=0)
        {
            printf("该学号不存在\n");
            pause();
            return head;
        }

    }

    change_goto:
    printf("当前学生信息如下: 请选择需要修改的内容\n");
    printf("序号 姓名       学号       性别      年龄 成绩\n");
    printf("%-4d %-10s %-10s %-10s %-4d %-4d\n",p->num,p->name,p->password,p->sex,p->age,p->score);
    printf("1.改姓名 2.改性别 3.改年龄 4.改成绩 5.改学号 6.退出修改\n");
    while(1)
    {
        scanf("%2[0-9]",a);
        while ( getchar() != '\n' );
        if(strlen(a)>=2||a[0]<'1'||a[0]>'6') 
            printf("非法输入,请重新输入\n");
        else
        {   
            if(a[0]>='1' && a[0]<='6')
                break;
        }
    }
    switch (a[0])
    {
    case 49:
        printf("请输入学生姓名\n");
        scanf("%15s",name);while ( getchar() != '\n' );
        strcpy(p->name,name);
        break;
    case 50:
        printf("请输入学生性别\n");
        scanf("%10[a-zA-Z0-9]",name);while ( getchar() != '\n' );
        strcpy(p->sex,name);
        break;
    case 51:
        printf("请输入学生年龄\n");
        scanf("%5[0-9]",name);while ( getchar() != '\n' );
        p->age=atoi(name);
        break;
    case 52:
        printf("请输入学生成绩\n");
        scanf("%4[0-9]",name);while ( getchar() != '\n' );
        p->score=atoi(name);
        break;
    case 53:
        printf("请输入学生学号\n");
        scanf("%10[a-zA-Z0-9]",name);while ( getchar() != '\n' );
        strcpy(p->password,name);
        break;
    case 54:
        
        return head;
        break;
    default:
        
        break;
    }
    
    goto change_goto;
    return head;

}
void student_inquire(userdata_t * head)
{
    userdata_t *p;
    char a[5];
    p=head;
    char name[20]={0};
    if(head==NULL)
    {
        printf("没有学生信息，请先添加\n");
        return ;
    }
    // inquire_goto:

        printf("请选择查询学生的方式\n1.姓名查询 2.学号查询 3.退出查询\n");
        while(1){
            scanf("%2[0-9]",a);
            while ( getchar() != '\n' );
            if(strlen(a)>=2||a[0]<'1'||a[0]>'3') 
                printf("非法输入,请重新输入\n");
            else
            {   
                if(a[0]>='1' && a[0]<='3')
                    break;   
            }
        }   
        switch (a[0])
        {
        case 49:
            
            printf("请输入学生姓名\n");
            scanf("%15s",name);while ( getchar() != '\n' );
            if(strcmp(p->name,name)==0);
            else
            {
                while(p->next!=NULL&&strcmp(p->name,name))
                    p=p->next;
                if(strcmp(p->name,name)!=0)
                {
                    printf("该学生不存在\n"); 
                    pause();
                    return ;
                }
            }

            break;
        case 50:
            printf("请输入学生学号\n");
            scanf("%10[a-zA-Z0-9]",name);while ( getchar() != '\n' );
            if(strcmp(p->password,name)==0);
            else
            {
                while(p->next!=NULL&&strcmp(p->password,name))
                    p=p->next;
                if(strcmp(p->password,name)!=0)
                {
                    printf("该学生不存在\n");pause(); //按任意键退�?
                    return ;
                }
            }
            break;
        case 51:
            return ;
            break;
        default:  

            break;
        }

    printf("序号 姓名       学号       性别      年龄 成绩\n");
    printf("%-4d %-10s %-10s %-10s %-4d %-4d\n",p->num,p->name,p->password,p->sex,p->age,p->score);
    pause();
    



} 

userdata_t *student_sort(userdata_t * head)
{

    int flag;
    char a[5];
    userdata_t  *p, *prev, *tail,*new_head, *old_head;

    new_head=(userdata_t*)calloc(1, sizeof(userdata_t));
    new_head->next=head;
    tail = NULL;     
    printf("请选择排序的方式\n1.学号排序 2.成绩排序 \n");
        while(1){
            scanf("%2[0-9]",a);
            while ( getchar()!= '\n' );
            if(a[0]<'1'||a[0]>'2'||strlen(a)>=2) 
                printf("非法输入,请重新输入\n");
            else
            {   
                if(a[0]>='1' && a[0]<='2')
                    break;   
            }
        }
       
    
    while(1)
    {
        flag = 1;   //flag用来标志�?否已经排好序                                  
 
        
        for(prev = new_head, p = new_head->next; p && p->next != tail; prev = prev->next)
        {
            if(a[0]==49)
            {
                if(atoi(p->password )< atoi(p->next->password))
                {
                    flag = 0;      //�?改flag=0，标志本�?�?�?交换�?
                    prev->next = p->next;    //弹出p节点
                    p->next = p->next->next; //插入p节点
                    prev->next->next = p;    //原来的p->next已经�?改，需要用prev->next代替

                }
                else
                    p = p->next;

            }
            else
            {
                if(p->score < p->next->score)
                {
                    flag = 0;      //�?改flag=0，标志本�?�?�?交换�?
                    prev->next = p->next;    //弹出p节点
                    p->next = p->next->next; //插入p节点
                    prev->next->next = p;    
                }
                else
                    p = p->next;
            }              
            
        } 
        if(flag)   //如果内层�?�?�?都没有交换过，则所有节点都已经�?排好序的
            break;
        tail = p;  //tail向前移一�?，tail以及tail后面的是排好序的元素   
    }
    old_head = new_head->next;
    free(new_head);
    
    return old_head; //


}

userdata_t *add_stu(userdata_t * head)
{
    userdata_t *new_stu,*p;
    int i=1;
    new_stu=(userdata_t *)calloc(1,sizeof(userdata_t));
    num_repeat:
    p=head;
    printf("请输入学号:");
    scanf("%10[a-zA-Z0-9]",new_stu->password); while ( getchar() != '\n' );
    if(head!=NULL)
    {
        // do
        while(p!=NULL)
        {
            if(strcmp(p->password,new_stu->password)==0)
            {
                printf("学号重复,请重新输入\n");
                goto num_repeat;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
            }
            if(p->next==NULL)
            {
                break;
            }
            i++;
            p->num=i;
            p=p->next;        
        }
        // while(p->next!=NULL||strcmp(p->password,new_stu->password)==0); 

        p->num=i+1;
    }
    new_stu->num=1;
    printf("请输入姓名:");
    scanf("%15s",new_stu->name);while ( getchar() != '\n' );
    printf("请输入性别(woman/man) \n");//zhongwen
    scanf("%10[a-zA-Z0-9]",new_stu->sex);while ( getchar() != '\n' );
    printf("请输入年龄:");
    scanf("%d",&new_stu->age);while ( getchar() != '\n' );
    printf("请输入分数:");
    scanf("%d",&new_stu->score);  while ( getchar() != '\n' );
    new_stu->next=head;
    head=new_stu;
    printf("添加成功\n");
    pause();
    return head;

}
userdata_t *delete_stu(userdata_t *head)//
{    
    userdata_t *node1,*node2;
    char name[20]={0};
    char a[5];
    node1=head;
    if(node1==NULL)
    {
        printf("该班级还没有学生，请先添加学生信息\n");
        pause();
        return head;
    }
    else
    {
        del_goto:
        printf("请选择删除方式\n1.输入名字删除  2.输入学号删除 3.全部删除 4.退出\n"); 
        while(1){
            scanf("%1[0-9]",a);
            while ( getchar()!= '\n' );
            if(strlen(a)>=2||a[0]<'1'||a[0]>'3') 
                printf("非法输入,请重新输入\n");
            else
            {   
                if(a[0]>='1' && a[0]<='4')
                    break;   
            }
        }

        switch (a[0])
        {

        case 49:
            printf("请输入姓名\n");
            scanf("%15s",name); while ( getchar() != '\n' );
            while(node1!=NULL&&strcmp(node1->name,name))
            {            
                node2=node1;
                node1=node1->next;                            
            }            
            break;
        case 50:
            printf("请输入学号\n");
            scanf("%10[a-zA-Z0-9]",name); while ( getchar() != '\n' );
            while(node1!=NULL&&strcmp(node1->password,name))
            {            
                node2=node1;
                node1=node1->next;                            
            }
            break;
        case 51:
            
            return NULL;    
            break;
        case 52:
            return head;
            break;
        default:
            goto del_goto;
            break;
        } 
        if(node1==head)
            head=node1->next;
        else if (node1==NULL)
        {
            printf("未找到\n");
            pause();
            return head;
        }
        else   
        { 
            node2->next=node1->next;
            
        }
    }
    printf("删除成功\n");
    pause();
    return head;
   
}
userdata_t * import_information(userdata_t * head )
{
    userdata_t *new_head,*p;
    char information[20]={0};
    printf("注意:本程序不对录入信息有效性做检查,请录入后及时修改重复学生信息\n1.参考%s添加学生信息\n2.将待录入文件移动至本程序目录下\n",filename);
    printf("请输入文件名(如123.txt)\n");
    scanf("%15s",information); while ( getchar() != '\n' );
    new_head=list_init(student_list,information);
    if(head==NULL)
        head=new_head;
    p=head;
    while(p->next!=NULL)        
        p=p->next;
    p->next=new_head;
    return head;
}

void stu_statistic(userdata_t *head)
{

    userdata_t *p;
    float i=0,j=0; //人数 平均�? 及格�? 
    float sum=0;
    p=head;
    if(head==NULL) 
    {
        printf("该班级还没有学生，请先添加学生信息\n");
        pause();
        return ;
    }
    while(p->next!=NULL)
    {
        i++;
        if(p->score>60)
            j++;
        sum+=p->score;
        p=p->next;
        
    }
    i++;
    if(p->score>60)
        j++;
    sum+=p->score;
    printf("总人数:%d 平均分:%6.2f 及格率:%4.2f%%\n",(int)i,sum/i,(j/i)*100);
    pause();
    
}
void save_stu(userdata_t *head,char *file_name)
{
    FILE * fp;
    userdata_t *p;
    int i=0;
    fp = fopen(file_name,"w+");
    if(fp == NULL){
        printf("文件打开失败!\n");
        pause();
        exit(0); 
    }
    p=head;
    while(p!=NULL)
    {
        i++;
        fprintf(fp,"%d %s %s %s %d %d\n",i,p->name,p->password,p->sex,p->age,p->score);
        p=p->next;
    }
    fclose(fp);

}
void buffer_print(userdata_t *head)
{
    userdata_t *p;
    p=head;
    while(p!=NULL)
    {
        printf("%-4d %-10s %-10s %-10s %-4d %-4d\n",p->num,p->name,p->password,p->sex,p->age,p->score);
        p=p->next;
    }
}
void pause()
{
    
    printf("输入任意键返回...\n");
    getchar();
    while ((getchar()) != '\n');
    
}

// void simple_encrypt(char *str, int key) {
//     int i;
//     for (i = 0; str[i] != '\0'; i++) {
//         str[i] = (char)(str[i] ^ key);
//     }
// }
 
// void simple_decrypt(char *str, int key) {
//     simple_encrypt(str, key);
// }