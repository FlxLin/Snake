#include<stdio.h>
#include<conio.h>
#include<windows.h>	
#include<stdlib.h>//����������Ŀ� 
#include<time.h> 

const int SNAKE_LENGTH = 3;//����һ����������ʼ������ 

//����ȫ�ֱ���
char Mode = 'A';//Ĭ��Ϊ����ģʽ 
int WaitTime;//�ȴ�ʱ�� 
int Speed;//��ǰ�ٶ� 
double DefaultTime = 1000 * 60;//һ���� 
double GameTime = 1;//��Ϸʱ�� 
//����ģʽʹ�� 
char Dire=77;//Ĭ�Ϸ��� 
bool Stoop = false;
bool ThreadKey = false;
int Sx1,Sx2,Sy1,Sy2;//���˫��ģʽ�ĳ�ͻ���� 


//˫��ģʽ��ʹ�� 
char Dire1=77;
char Dire2='s';

struct info{
	char name[20];
	char password[20]; 
	int score;
	int DoubleScore;
};//���а�ṹ��  

info NowGamer;//��¼��ǰ��Ϸ�����Ϣ 

// ���ع�� �̶�����	
void Hide_Cursor(HANDLE hConsole)			                    	
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };  //CONSOLE_CURSOR_INFO: ����̨������Ϣ
	SetConsoleCursorInfo(hConsole, &cursor_info);//���ù����Ϣ���������bool 
}


//��궨λ���� 
void Goto(int x, int y)
{
	short a=(short)x*2;									//*2��֤xy��1:1��ת������x�������������Ϊ�õĴ�ӡ�ķ��鶼��ռһ���ַ�
	COORD pos = {a, (short)y };		        	      	// ����һ���ַ��ڿ���̨��Ļ�ϵ�����POS, COORD:��ʾһ���ַ��ڿ���̨��Ļ�ϵ�����
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // ��ȡ��׼����ľ��
	SetConsoleCursorPosition(hConsole, pos);	    	// ��λ���λ�õĺ���
	Hide_Cursor(hConsole);
}
/*
HANDLE����PVOID��Ҳ����������ָ��
˵��ȷ��һ�㣬���ʵ������һ��ָ��ĳ����Դ��ָ�룬����ָ����������ͬ��ָ���Ӧ��һ���������ڴ��еĵ�ַ��
�õ���ָ��Ϳ������ɵ��޸ĸ����ݡ�Windows����ϣ��һ������޸����ڲ����ݽṹ����Ϊ����̫����ȫ��
����Windows��ÿ��ʹ��GlobalAlloc�Ⱥ����������ڴ�����ָ��һ�����(����������һ��ָ�룬����Ҫֱ�Ӳ�����),
ƽʱ��ֻ���ڵ���API����ʱ������������˵��Ҫ�����Ķ��ڴ档 
*/


//������ɫ
void SetColor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);//���ÿ���̨����������ɫ�ͱ���ɫ�ļ�������� 
} 
 
 
void PBox(int x,int y)//��x��y����ӡ����
{
	Goto(x,y);
	printf("��");
}

void PBox1(int x,int y)//��x��y����ӡ����
{
	Goto(x,y);
	printf("��");
}

void Psqrt(int l, int w, int x, int y){
	for(int i = 0; i < l; i++){
		PBox1(x+i,y);
		PBox1(x+i,y+w);
	}
	for(int i = 0; i < w; i++){
		PBox1(x,y+i);
		PBox1(x+l-1,y+i);
	}
}


int Readrank(int x){    
	info tmp[20];	
	info temp;	
	int j = 0,i = 0,k = 0;	
	FILE *fp;	
	fp = fopen("rank.txt","r");	
	if(fp==NULL){          
		printf("cannot open the files\n");          
		system("pause");          
		return -1;      
		}	
	while(fscanf(fp,"%s %s %d %d",tmp[i].name,tmp[i].password,&tmp[i].score,&tmp[i].DoubleScore)!=EOF && i < 20){	
		i++;	
	}	
	if(x == 1){
		if(Mode == 'A' || Mode == 'a'){
			for(j = 0;j < i;j++)		
				for(k = 0;k <= i;k++){			
					if(tmp[k].score<tmp[j].score){				
						temp = tmp[k];				
						tmp[k] = tmp[j];				
						tmp[j] = temp;			
						}		
					}//�������а����� 
			for(j = 0; j < i && j < 10; j++){
				Goto(41,j+6);
				printf("��%d����%6s �÷֣�%d",j+1,tmp[j].name,tmp[j].score );
			}
		}else if(Mode == 'B' || Mode == 'b'){
			for(j = 0;j < i;j++)		
				for(k = 0;k <= i;k++){			
					if(tmp[k].DoubleScore<tmp[j].DoubleScore){				
						temp = tmp[k];				
						tmp[k] = tmp[j];				
						tmp[j] = temp;			
						}		
					}//˫�����а�����
			for(j = 0; j < i && j < 10; j++){
				Goto(41,j+6);
				printf("��%d����%6s �÷֣�%d",j+1,tmp[j].name,tmp[j].DoubleScore );
			}
		}		
	}else if(x == 2){
		for(j = 0;j < i;j++)		
			for(k = 0;k <= i;k++){			
				if(tmp[k].score<tmp[j].score){				
					temp = tmp[k];				
					tmp[k] = tmp[j];				
					tmp[j] = temp;			
					}		
				}//�������а����� 
		for(j = 0; j < i && j < 10; j++){
				Goto(13,j+28);
				printf("��%d����%6s �÷֣�%d",j+1,tmp[j].name,tmp[j].score );
			}
		
		for(j = 0;j < i;j++)		
			for(k = 0;k <= i;k++){			
				if(tmp[k].DoubleScore<tmp[j].DoubleScore){				
					temp = tmp[k];				
					tmp[k] = tmp[j];				
					tmp[j] = temp;			
					}		
				}//˫�����а�����
		for(j = 0; j < i && j < 10; j++){
				Goto(31,j+28);
				printf("��%d����%6s �÷֣�%d",j+1,tmp[j].name,tmp[j].DoubleScore);
			} 
	}	
	fclose(fp);	
	return 0;
}


//ʵ�����а�	
int Rank(int SnakeLength){
	SetColor(12); 
	Goto(26,3);
	printf("̰����");
	SetColor(15);//������ɫ ��ɫ 
	for(int i = 0; i < 55; i++){
		PBox(i,0);
		PBox(i,39);
	} 
	for(int i = 0; i < 40; i++){
		PBox(0,i);
		PBox(54,i);
	}  
	for(int i = 23; i < 32; i++){
		PBox1(i,5);
		PBox1(i,9);
		if(i >= 25 && i <= 30){
			PBox1(i,13);
			PBox1(i,15);
			PBox1(i,17);		
		} 
	}
	PBox1(25,14);PBox1(30,14);PBox1(25,16);PBox1(30,16);
	for(int i = 5; i < 10; i++){
		PBox1(23,i);
		PBox1(28,i);
		PBox1(32,i);
	}//�߿��Լ��÷���Ϣ��	
	Psqrt(6,2,25,19);
	
	Goto(25,7);
	SetColor(12); 
	printf("�÷�");
	Goto(30,7);
	if(Mode == 'A' || Mode == 'a')
		printf("%d",(SnakeLength-SNAKE_LENGTH)*10 + int((SnakeLength-SNAKE_LENGTH) / 5) * 10);
	else if(Mode == 'B' || Mode == 'b')
		printf("%d",(SnakeLength-SNAKE_LENGTH * 2)*10 + int((SnakeLength-SNAKE_LENGTH*2) / 5) * 10);
	SetColor(15);
	Goto(26,16);
	printf("�����Ѷ�");//ʵ�ֽ��� 
			
	if(Mode == 'A' || Mode == 'a'){
		if(NowGamer.score <= (SnakeLength-SNAKE_LENGTH)*10 + int((SnakeLength-SNAKE_LENGTH) / 5) * 10){
			NowGamer.score = (SnakeLength-SNAKE_LENGTH)*10 + int((SnakeLength-SNAKE_LENGTH) / 5) * 10;
			Psqrt(19,3,18,12);
			Goto(26,13);
			printf("�ٽ�����");
			Goto(19,14);
			printf("��ϲ%s�������㴴�����Լ����¼�¼!",NowGamer.name);
			//�����¼�¼ 
			FILE *fin,*ftp;
		    info temp;
		    fin=fopen("rank.txt","r");//����ԭ�ļ�
		    ftp=fopen("tmp.txt","w");//д����ʱ�ļ�
		    while(fscanf(fin,"%s %s %d %d",temp.name,temp.password,&temp.score,&temp.DoubleScore)!=EOF)//��ԭ�ļ���ȡһ��
		        if( strcmp(temp.name,NowGamer.name) != 0 )//�����˺��Ƿ���ͬ 
		           fprintf(ftp,"%s %s %d %d\n",temp.name,temp.password,temp.score,temp.DoubleScore);//��������һ��д����ʱ�ļ�tmp.txt
		    fprintf(ftp,"%s %s %d %d\n",NowGamer.name,NowGamer.password,NowGamer.score,NowGamer.DoubleScore);
			fclose(fin);
		    fclose(ftp); 
		    remove("rank.txt");// ɾ���ļ� 
		    rename("tmp.txt","rank.txt");//����ʱ�ļ�����Ϊԭ�ļ��� 
		}else{
			Psqrt(19,3,18,12);
			Goto(26,13);
			printf("��Ҫ����");
			Goto(19,14);
			printf("���ź�%s��������Ͳ���ôһ���!",NowGamer.name);
		} 
	}
	else if(Mode == 'B' || Mode == 'b'){		
		if(NowGamer.DoubleScore <= (SnakeLength-SNAKE_LENGTH * 2)*10 + int((SnakeLength-SNAKE_LENGTH*2) / 5) * 10){
			NowGamer.DoubleScore = (SnakeLength-SNAKE_LENGTH * 2)*10 + int((SnakeLength-SNAKE_LENGTH*2) / 5) * 10;
			Psqrt(19,3,18,12);
			Goto(26,13);
			printf("�ٽ�����");
			Goto(19,14);
			printf("��ϲ%s�������㴴�����Լ����¼�¼!",NowGamer.name);
			//�����¼�¼ 
			FILE *fin,*ftp;
		    info temp;
		    fin=fopen("rank.txt","r");//����ԭ�ļ�
		    ftp=fopen("tmp.txt","w");//д����ʱ�ļ�
		    while(fscanf(fin,"%s %s %d %d",temp.name,temp.password,&temp.score,&temp.DoubleScore)!=EOF)//��ԭ�ļ���ȡһ��
		        if( strcmp(temp.name,NowGamer.name) != 0 )//�����˺��Ƿ���ͬ 
		           fprintf(ftp,"%s %s %d %d\n",temp.name,temp.password,temp.score,temp.DoubleScore);//��������һ��д����ʱ�ļ�tmp.txt
		    fprintf(ftp,"%s %s %d %d\n",NowGamer.name,NowGamer.password,NowGamer.score,NowGamer.DoubleScore);
			fclose(fin);
		    fclose(ftp); 
		    remove("rank.txt");// ɾ���ļ� 
		    rename("tmp.txt","rank.txt");//����ʱ�ļ�����Ϊԭ�ļ��� 
		}else{
			Psqrt(19,3,18,12);
			Goto(26,13);
			printf("��Ҫ����");
			Goto(19,14);
			printf("���ź�%s��������Ͳ���ôһ���!",NowGamer.name);
		} 
	}
	
	SetColor(10); 
	Goto(16,26);
	printf("�������а�");
	Goto(34,26);
	printf("˫�����а�");
	Readrank(2);
		
	Goto(26,20);
	scanf("%d",&Speed);
	WaitTime = Speed;
	Goto(31,20);
	printf("��");
	Sleep(3000);//��ͣ����
	return 0;
}


void PInterface()//��ӡ����
{
	system("cls");//�����Ļ
	int i=0;
	SetColor(15);//������ɫ ��ɫ  
	for(;i<55;i++)
	{
		if(i<=39)
			{	
				PBox(0,i);//��ӡ����
				PBox(39,i);
				PBox(54,i);
				PBox(i,0);//��ӡ����
				PBox(i,39);
			}
		else 
			{	
				PBox(i,0);//��ӡ����
				PBox(i,39);
			}	
	}
	if(Mode == 'A' || Mode == 'B' || Mode == 'a' || Mode =='b'){
		Goto(45,3);//��ӡ��Ϣ
		printf("̰������Ϸ");
		Goto(45,5);
		if(Mode == 'A' || Mode == 'a')
			printf("�������а�");
		else if(Mode == 'B' || Mode == 'b')
			printf("˫�����а�");
		SetColor(15);
		Readrank(1); 
	}	
}

bool login(info temp){
	info tmp;
	FILE *fp;	
	fp = fopen("rank.txt","r");	
	if(fp==NULL){          
		printf("cannot open the files\n");          
		system("pause");          
		return -1;      
		}
	while(fscanf(fp,"%s %s %d %d",tmp.name,tmp.password,&tmp.score,&tmp.DoubleScore)!=EOF){	
		if(strcmp(tmp.name,temp.name) == 0){
			if(strcmp(tmp.password,temp.password) == 0){
				NowGamer = tmp;//���浱ǰ��Ϸ���֮ǰ��Ϣ 
				fclose(fp);
				return true;
			}
			else{
				fclose(fp);
				return false;
			}
		}			
	}
	NowGamer = temp;//���浱ǰ��Ϸ���֮ǰ��Ϣ 				
	fprintf(fp,"%s %s %d %d\n",temp.name,temp.password,temp.score,temp.DoubleScore);
	fclose(fp);
	return true;
}

void Relogin(){
	SetColor(12);
	PBox(24,14); PBox(27,14);
	for(int i = 17; i < 35; i++){
		PBox(i,15);
		PBox(i,17);
		if(i >= 24 && i <= 27)
			PBox(i,13);
	}
	PBox(17,16); PBox(34,16);// ��ӡ�߿� 
	
	SetColor(14);
	Goto(18,16);
	printf("�˺Ż���������������µ�½��Ϸ");	
	Goto(25,14);
	printf("��ʾ");		
}

//��ʼ������
void Init()
{
	//���ñ���
	system("̰����");
	
	//��������̨�Ŀ��
	system("mode con: cols=110 lines=40"); 
		
	SetColor(12); 
	Goto(26,3);
	printf("̰����");
	SetColor(15);//������ɫ ��ɫ 
	for(int i = 0; i < 55; i++){
		PBox(i,0);
		PBox(i,39);
	} 
	for(int i = 0; i < 40; i++){
		PBox(0,i);
		PBox(54,i);
	} //��߿� 
	for(int i = 23; i < 32; i++){
		PBox1(i,8);
		PBox1(i,10);
		PBox1(i,12);
		PBox1(i,14);
		if(i >= 25 && i <= 30){
			PBox1(i,6);
			PBox1(i,16);
			PBox1(i,18);
			PBox1(i,20);
		} 
	}
	PBox1(25,7);PBox1(30,7);PBox1(25,17);PBox1(30,17);PBox1(25,19);PBox1(30,19);
	for(int i = 8; i <= 14; i++){
		if(i <= 10 || i >= 12){
			PBox1(23,i);
			PBox1(32,i);
		}else{
			PBox1(26,i);
			PBox1(29,i);
		}
	} //��ӡ���� 
	Psqrt(8,2,24,22);
	Psqrt(8,2,14,22);
	Psqrt(8,2,34,22);
	PBox1(26,21);PBox1(29,21);
	
	
	SetColor(5);
	Goto(26,7);
	printf("��������");
	Goto(27,11);
	printf("����");
	Goto(16,15);
	printf("�����Ѷȵȼ�,10-1000�ڵ�һ����ֵ��10����죬1000������");
	Goto(26,19);
	printf("ģʽѡ��");
	Goto(15,23);
	printf("A������ģʽ");
	Goto(25,23);
	printf("B��˫��ģʽ");
	Goto(35,23);
	printf("C����սģʽ");
	
	SetColor(10); 
	Goto(16,26);
	printf("�������а�");
	Goto(34,26);
	printf("˫�����а�");
	Readrank(2);//ʵ�ֽ��� 
	
	info temp;
	char str1[20],str2[20];
	Relogin: Goto(24,9);
	str1[0] = getchar();
	if(str1[0] == '\n') 
		goto Relogin;
	scanf("%s",str2);
	strcat(str1,str2);	
	strcpy(temp.name,str1);
	Goto(33,9);
	printf("��");
	
	
	char str3[20],str4[20];
	Relogin1: Goto(24,13);
	str3[0] = getchar();
	if(str3[0] == '\n') 
		goto Relogin1;
	scanf("%s",str4);
	strcat(str3,str4);	
	strcpy(temp.password,str3);
	
	char ch;
	Goto(33,13);
	printf("��");
	ReSpeed: Goto(26,17);
	//ch = getchar();
	//if(ch == '\n')
	//	goto ReSpeed;
	scanf("%d",&Speed);
	if(Speed > 1000 || Speed < 10){
		Goto(31,17);
		printf("��");
		for(int i = 0; i < 4; i++){
			Goto(26+i,17);
			printf("  ");
		}
		fflush(stdin);
		goto ReSpeed; 
	}
		
	getchar();//�����س� 
	Goto(31,17);
	printf("��");
	ReMode: Goto(27,21);
	scanf("%c",&Mode);
	if( (Mode != 'A' && Mode != 'a' && Mode != 'B' && Mode != 'b' && Mode != 'C' && Mode != 'c') || getchar() != '\n' ){
		Goto(30,21);
		printf("��");
		for(int i = 0; i < 2; i++){
			Goto(27+i,21);
			printf("  ");
		}
		fflush(stdin);//������뻺����
		goto ReMode; 
	} 
	Goto(30,21);
	printf("��");
	if(Mode == 'C' || Mode == 'c'){
		fflush(stdin);//������뻺����
		Psqrt(8,3,34,17);
		SetColor(15);
		Goto(37,18);
		printf("PKʱ��");
		Goto(39,19);
		printf(":����");
		ReGameTime: Goto(38,19);
		scanf("%lf",&GameTime);
		if(GameTime > 15 ){
			Goto(42,19);
			printf("��");
			Goto(38,19);
			printf("  ");
			fflush(stdin);
			goto ReGameTime; 
		}
	} 
	
	
	
	temp.score = 0;
	temp.DoubleScore = 0;
	if( login(temp) ){
		//�������ñ߿��� 
		PInterface();
	} else{
		Relogin();
		//���µ�½ 
		Sleep(3000);//��ͣ����
		Init();
	}
} 


void InitSnake(int (*Snake)[2],int SnakeLength)//��ʼ������
{
	int i;
	srand((unsigned)time(NULL));//����������ӣ�ʹ�ò�������������̶� 
	loop: int Addressx = rand() % 30;//����һ����ʼλ�õ�x�������ֵ 
	int Addressy = rand() % 35;//����һ����ʼλ�õ�y�������ֵ 
	if(Addressx <= 2 || Addressy == 0) goto loop;//��ֹ�߳�ʼλ����ǽ�� 
	 
	//������ɫ,������ɫ 
	SetColor(10);
	for(i=SnakeLength-1;i>0;i--)//��������
		{
			*(Snake[i]+0) = Addressx - i;//���ó�ʼֵ
			*(Snake[i]+1) = Addressy;
			PBox(*(Snake[i]+0),*(Snake[i]+1));//��ӡ����
		}
	Goto(*(Snake[2]+0),*(Snake[2]+1));
	printf("��");	
	*(Snake[0]+0) = Addressx - i;//���ó�ʼֵ
	*(Snake[0]+1) = Addressy;	
	Goto(*(Snake[0]+0),*(Snake[0]+1));
	printf("@@");
}


void Clear(int x,int y)//���x��y�����ַ�
{
	Goto(x,y);
	putchar('\0');
	putchar('\0');
}


void NextStape(int *Sx,int *Sy)//���ݷ���ȷ����һ����x��y
{
	
	switch (Dire)
	  {
		  case 72: (*Sy)--;break; //��
		  case 80: (*Sy)++;break; //��
		  case 75: (*Sx)--;break; //��
		  case 77: (*Sx)++;break; //��
		  case 'w': (*Sy)--;break; //��
		  case 's': (*Sy)++;break; //��
		  case 'a': (*Sx)--;break; //��
		  case 'd': (*Sx)++;break; //��
		  case 'W': (*Sy)--;break; //��
		  case 'S': (*Sy)++;break; //��
		  case 'A': (*Sx)--;break; //��
		  case 'D': (*Sx)++;break; //��
	  }
}


//ʵ�������ƶ� 
void MoveSnake(int Sx,int Sy,int (*Snake)[2],int SnakeLength)  //�ƶ��ߵ�ָ���ĵ�
{
	int j;
	Clear(*(Snake[SnakeLength-1]+0),*(Snake[SnakeLength-1]+1));//�����β
	for(j=SnakeLength;j>=2;j--)//��������
		{
			*(Snake[j-1]+0) = *(Snake[j-2]+0); //�������������δӺ���ǰ����
			*(Snake[j-1]+1) = *(Snake[j-2]+1);
		}
	*(Snake[0]+0)=Sx;//����ͷ��ֵ
	*(Snake[0]+1)=Sy;
	
	SetColor(10);
	Goto(*(Snake[0]+0),*(Snake[0]+1));
	printf("@@");//��ӡ��ͷ
	Goto(*(Snake[SnakeLength-1]+0),*(Snake[SnakeLength-1]+1));
	printf("��");//��ӡ��β 
	for(int i=SnakeLength-2;i>0;i--)//��������
		{
			PBox(*(Snake[i]+0),*(Snake[i]+1));//��ӡ����
		}
}


//�̼߳�����������
DWORD WINAPI ListenKey( LPVOID lpParam )				//�����̵��û�
{
    while(!ThreadKey)
      {
	  char flag = getch();//��ȡ������Ϣ
	  switch(flag)
			{
				case 72: if(Dire!=80)//�ж������ֵ���Ƿ��뵱ǰֵ�����෴
							{Dire=flag;WaitTime=0;break;}//������෴���ı䷽�����õȴ�ʱ�䣬����switch
	                     else  
							{break;}
				case 80: if(Dire!=72) 
							{Dire=flag;WaitTime=0;break;}
	                     else 
							{break;}
				case 75: if(Dire!=77) 
							{Dire=flag;WaitTime=0;break;}
	                     else  
							{break;}
				case 77: if(Dire!=75) 
							{Dire=flag;WaitTime=0;break;}
	                     else  
							 {break;}
				case 'w': if(Dire!= 's')//�ж������ֵ���Ƿ��뵱ǰֵ�����෴
							{Dire=flag;WaitTime=0;break;}//������෴���ı䷽�����õȴ�ʱ�䣬����switch
	                     else  
							{break;}
				case 'a': if(Dire!= 'd') 
							{Dire=flag;WaitTime=0;break;}
	                     else 
							{break;}
				case 'd': if(Dire!= 'a') 
							{Dire=flag;WaitTime=0;break;}
	                     else  
							{break;}
				case 's': if(Dire!= 'w') 
							{Dire=flag;WaitTime=0;break;}
	                     else  
							 {break;}
				case 'W': if(Dire!= 'S')//�ж������ֵ���Ƿ��뵱ǰֵ�����෴
							{Dire=flag;WaitTime=0;break;}//������෴���ı䷽�����õȴ�ʱ�䣬����switch
	                     else  
							{break;}
				case 'A': if(Dire!= 'D') 
							{Dire=flag;WaitTime=0;break;}
	                     else 
							{break;}
				case 'D': if(Dire!= 'A') 
							{Dire=flag;WaitTime=0;break;}
	                     else  
							{break;}
				case 'S': if(Dire!= 'W') 
							{Dire=flag;WaitTime=0;break;}
	                     else  
							 {break;}
				case 'p': Stoop = true;ThreadKey = true; break;
			}
		}
	   return 0;
}


void PCircle(int x,int y,int fg)//��x��y����ӡ��ʵ 
{	
	if(fg % 5 != 4){	
		Goto(x,y);
		printf("��");
	}else{
		Goto(x,y);
		printf("��");
	}
}


//����ʳ��
void CreateFood(int *Food,int Snake[400][2],int SnakeLength)
{
	int Cfood[2];
	srand((unsigned)time(NULL));						//�������������
	while(true)
		{
			int flag=1;
			int i;
			Cfood[0] = rand()%38+1;//����λ��
			Cfood[1] = rand()%38+1;
			for(i=0;i<SnakeLength;i++)//�жϻ�ȡ��λ���Ƿ�����������
				{
					if(Cfood[0]==Snake[i][0]&&Cfood[1]==Snake[i][1])//�����������
						{flag=0;break;}//����ѭ�����¼���
				}
			if(flag==1)//���ɵ�ʳ������ȷ��
				{
					SetColor(12);
					PCircle(Cfood[0],Cfood[1],SnakeLength - SNAKE_LENGTH);//��ӡʳ��
					*Food = Cfood[0];//Ϊʳ�︳ֵ
					*(Food+1) = Cfood[1];
					break;
				}
		}	
}


void AddSpeed(int SnakeLength)//���������������ٶ�
{
	if(WaitTime == 0)//��WaitTime���ı�ʱ�����л�ԭ
		{
			int NewTime;
			NewTime = Speed - (SnakeLength-SNAKE_LENGTH)*10;//��ȡ�µĵȴ�ʱ��
			if(NewTime >= 10)//����µĵȴ�ʱ��>=10
				WaitTime = NewTime;//���µĵȴ�ʱ�丳ֵ��WaitTime
			else//�µĵȴ�ʱ��<=10
				WaitTime = 10;			
		}
}


void PScore(int SnakeLength)//��ӡ����
{
	int score = (SnakeLength-SNAKE_LENGTH)*10 + int((SnakeLength-SNAKE_LENGTH) / 5) * 10;//��ǰ�����ȼ�ȥ��ʼֵ��*10
	SetColor(15);
	for(int i = 42; i < 52; i++){
		PBox(i,25);
		PBox(i,29);
	}
	for(int i = 25; i < 29; i++){
		PBox(42,i);
		PBox(47,i);
		PBox(51,i);
	}	
	SetColor(10);
	Goto(44,27);
	printf("�÷�");
	Goto(49,27);
	printf("%d",score);
}

void GameOver(int (*Snake)[2],int *SnakeLength,int *Food)
{
	SetColor(15);
	PBox(18,15); PBox(21,15);
	for(int i = 11; i < 29; i++){
		PBox(i,16);
		PBox(i,18);
		if(i >= 18 && i <= 21)
			PBox(i,14);
	}
	PBox(11,17); PBox(28,17);// ��ӡ�߿� 
	
	SetColor(10);
	Goto(12,17);
	printf("��Ϸ������������Զ���ʼ������Ϸ");	
	Goto(19,15);
	printf("��ʾ");	
	Sleep(3000);//��ͣ����
	system("cls");//�����Ļ
	Rank(*SnakeLength);//������� 
	*SnakeLength = SNAKE_LENGTH;	//����������
	PInterface(); //��ʼ������
	InitSnake(Snake,*SnakeLength);//��ʼ������	
	CreateFood(Food,Snake,*SnakeLength);//������ʵ
	Dire = 77;//���÷���
	PScore(*SnakeLength);//��ӡ����
}


int Judge(int Sx,int Sy,int (*Snake)[2],int *SnakeLength,int *Food)
{
	int i;	
	if(Sx<=0||Sx>=39||Sy>=39||Sy<=0)//�ж��Ƿ�ײǽ
		{
			GameOver(Snake,SnakeLength,Food);//������Ϸ
			return 0;
		}	
	for(i=3;i<*SnakeLength;i++)//��������
		{
			if(Sx==Snake[i][0]&&Sy==Snake[i][1])//�ж��Ƿ�ײ���Լ�
				{
					GameOver(Snake,SnakeLength,Food);//������Ϸ
					return 0;//��ʾ��Ϸ����
				}
		}	
	if(Sx==*Food&&Sy==*(Food+1))//�ж��Ƿ���ʳ��
		{	
			(*SnakeLength)++;//���ӳ���
			CreateFood(Food,Snake,*SnakeLength);//����ʳ��
			PScore(*SnakeLength);//���·���
		}
}	
		
	
//˫��ģʽ�¸Ķ�����
void Double_InitSnake(int (*Snake)[2],int SnakeLength,int color)//��ʼ������
{
	int i;
	srand((unsigned)time(NULL));//����������ӣ�ʹ�ò�������������̶� 
	loop: int Addressx = rand() % 30;//����һ����ʼλ�õ�x�������ֵ 
	int Addressy = rand() % 35;//����һ����ʼλ�õ�y�������ֵ 
	if(Addressx <= 2 || Addressy == 0) goto loop;//��ֹ�߳�ʼλ����ǽ�� 
	 
	//������ɫ,������ɫ 
	if(color == 1)	SetColor(10);
	else	SetColor(8);
	for(i=SnakeLength-1;i>0;i--)//��������
		{
			*(Snake[i]+0) = Addressx - i;//���ó�ʼֵ
			*(Snake[i]+1) = Addressy;
			PBox(*(Snake[i]+0),*(Snake[i]+1));//��ӡ����
		}
	Goto(*(Snake[2]+0),*(Snake[2]+1));
	printf("��");	
	*(Snake[0]+0) = Addressx - i;//���ó�ʼֵ
	*(Snake[0]+1) = Addressy;	
	Goto(*(Snake[0]+0),*(Snake[0]+1));
	printf("@@");
}	
	
void Double_NextStape(int *Sx1,int *Sy1,int *Sx2,int *Sy2)//���ݷ���ȷ����һ����x��y
{	
	switch (Dire1)
	  {
		  case 72: if(*Sy1>0) (*Sy1)--;break; //��
		  case 80: if(*Sy1<39) (*Sy1)++;break; //��
		  case 75: if(*Sx1>0) (*Sx1)--;break; //��
		  case 77: if(*Sx1<54) (*Sx1)++;break; //��
	  }
	switch (Dire2)
	{
		  case 'w': if(*Sy1>1) (*Sy2)--;break; //��
		  case 's': if(*Sy1<39) (*Sy2)++;break; //��
		  case 'a': if(*Sx1>0) (*Sx2)--;break; //��
		  case 'd': if(*Sx1<54) (*Sx2)++;break; //��
		  case 'W': if(*Sy1>1) (*Sy2)--;break; //��
		  case 'S': if(*Sy1<39) (*Sy2)++;break; //��
		  case 'A': if(*Sx1>0) (*Sx2)--;break; //��
		  case 'D': if(*Sx1<54) (*Sx2)++;break; //��
	}
}	

//�̼߳�����������
DWORD WINAPI Double_ListenKey( LPVOID lpParam )				//�����̵��û�
{
    while(!ThreadKey)
      {
      		char flag = getch();//��ȡ������Ϣ
	  		switch(flag)
			{
				case 72: if(Dire1 !=80  )//�ж������ֵ���Ƿ��뵱ǰֵ�����෴
							{Dire1 = flag;WaitTime=0;break;}//������෴���ı䷽�����õȴ�ʱ�䣬����switch
	                     else  
							{break;}
				case 80: if(Dire1 !=72 ) 
							{Dire1 = flag;WaitTime=0;break;}
	                     else 
							{break;}
				case 75: if(Dire1 != 77 ) 
							{Dire1 = flag;WaitTime=0;break;}
	                     else  
							{break;}
				case 77: if(Dire1 != 75 ) 
							{Dire1 = flag;WaitTime=0;break;}
	                     else  
							 {break;}
				case 'w': if(Dire2!= 's' )//�ж������ֵ���Ƿ��뵱ǰֵ�����෴
							{Dire2=flag;WaitTime=0;break;}//������෴���ı䷽�����õȴ�ʱ�䣬����switch
	                     else  
							{break;}
				case 'a': if(Dire2!= 'd') 
							{Dire2=flag;WaitTime=0;break;}
	                     else 
							{break;}
				case 'd': if(Dire2!= 'a') 
							{Dire2=flag;WaitTime=0;break;}
	                     else  
							{break;}
				case 's': if(Dire2!= 'w' ) 
							{Dire2=flag;WaitTime=0;break;}
	                     else  
							 {break;}
				case 'W': if(Dire2!= 'S')//�ж������ֵ���Ƿ��뵱ǰֵ�����෴
							{Dire2=flag;WaitTime=0;break;}//������෴���ı䷽�����õȴ�ʱ�䣬����switch
	                     else  
							{break;}
				case 'A': if(Dire2!= 'D') 
							{Dire2=flag;WaitTime=0;break;}
	                     else 
							{break;}
				case 'D': if(Dire2!= 'A') 
							{Dire2=flag;WaitTime=0;break;}
	                     else  
							{break;}
				case 'S': if(Dire2!= 'W') 
							{Dire2=flag;WaitTime=0;break;}
	                     else  
							 {break;}
				case 'p': Stoop = true;ThreadKey = true; break;
				}	  
		}
	   return 0;
}	

//�̼߳�����������
DWORD WINAPI PK_ListenKey( LPVOID lpParam )				//�����̵��û�
{
    while(!ThreadKey)
      {
	  char flag = getch();//��ȡ������Ϣ
	  switch(flag)
			{
				case 72: if(Dire1 !=80 && Sy1 > 1 )//�ж������ֵ���Ƿ��뵱ǰֵ�����෴
							{Dire1 = flag;WaitTime=0;break;}//������෴���ı䷽�����õȴ�ʱ�䣬����switch
	                     else  
							{break;}
				case 80: if(Dire1 !=72 && Sy1 < 38) 
							{Dire1 = flag;WaitTime=0;break;}
	                     else 
							{break;}
				case 75: if(Dire1 != 77 && Sx1 > 1) 
							{Dire1 = flag;WaitTime=0;break;}
	                     else  
							{break;}
				case 77: if(Dire1 != 75 && Sx1 < 38) 
							{Dire1 = flag;WaitTime=0;break;}
	                     else  
							 {break;}
				case 'w': if(Dire2!= 's' && Sy2 > 1)//�ж������ֵ���Ƿ��뵱ǰֵ�����෴
							{Dire2=flag;WaitTime=0;break;}//������෴���ı䷽�����õȴ�ʱ�䣬����switch
	                     else  
							{break;}
				case 'a': if(Dire2!= 'd' && Sx2 > 1) 
							{Dire2=flag;WaitTime=0;break;}
	                     else 
							{break;}
				case 'd': if(Dire2!= 'a'&& Sx2 < 38) 
							{Dire2=flag;WaitTime=0;break;}
	                     else  
							{break;}
				case 's': if(Dire2!= 'w' && Sy2 < 38) 
							{Dire2=flag;WaitTime=0;break;}
	                     else  
							 {break;}
				case 'W': if(Dire2!= 'S' && Sy2 > 1)//�ж������ֵ���Ƿ��뵱ǰֵ�����෴
							{Dire2=flag;WaitTime=0;break;}//������෴���ı䷽�����õȴ�ʱ�䣬����switch
	                     else  
							{break;}
				case 'A': if(Dire2!= 'D' && Sx2 > 1) 
							{Dire2=flag;WaitTime=0;break;}
	                     else 
							{break;}
				case 'D': if(Dire2!= 'A' && Sx2 < 38) 
							{Dire2=flag;WaitTime=0;break;}
	                     else  
							{break;}
				case 'S': if(Dire2!= 'W'&& Sy2 < 38) 
							{Dire2=flag;WaitTime=0;break;}
	                     else  
							 {break;}
				case 'p': Stoop = true;ThreadKey = true; break;	
			//	case 'P': Stoop = true;break;                
			}
		}
	   return 0;
}	

//����ʳ��
void Double_CreateFood(int *Food,int Snake1[400][2],int Snake2[400][2],int SnakeLength1,int SnakeLength2) 
{
	int Cfood[2];
	srand((unsigned)time(NULL));						//�������������
	while(true)
		{
			int flag=1;
			int i;
			Cfood[0] = rand()%38+1;//����λ��
			Cfood[1] = rand()%38+1;
			for(i=0;i<SnakeLength1;i++)//�жϻ�ȡ��λ���Ƿ�����������
				{
					if(Cfood[0]==Snake1[i][0]&&Cfood[1]==Snake1[i][1])//�����������
						{flag=0;break;}//����ѭ�����¼���
				}
			for(i=0;i<SnakeLength2;i++)//�жϻ�ȡ��λ���Ƿ�����������
				{
					if(Cfood[0]==Snake2[i][0]&&Cfood[1]==Snake2[i][1])//�����������
						{flag=0;break;}//����ѭ�����¼���
				}
			if(flag==1)//���ɵ�ʳ������ȷ��
				{
					SetColor(12);
					PCircle(Cfood[0],Cfood[1],SnakeLength1 + SnakeLength2  - SNAKE_LENGTH*2);//��ӡʳ��
					*Food = Cfood[0];//Ϊʳ�︳ֵ
					*(Food+1) = Cfood[1];
					break;
				}
		}	
}

//ʵ�������ƶ� 
void Double_MoveSnake(int Sx,int Sy,int (*Snake)[2],int SnakeLength,int color)  //�ƶ��ߵ�ָ���ĵ�
{
	int j;
	Clear(*(Snake[SnakeLength-1]+0),*(Snake[SnakeLength-1]+1));//�����β
	for(j=SnakeLength;j>=2;j--)//��������
		{
			*(Snake[j-1]+0) = *(Snake[j-2]+0); //�������������δӺ���ǰ����
			*(Snake[j-1]+1) = *(Snake[j-2]+1);
		}
	*(Snake[0]+0)=Sx;//����ͷ��ֵ
	*(Snake[0]+1)=Sy;
	
	if(color == 1) SetColor(10);
	else SetColor(8);
	for(int i=SnakeLength-2;i>0;i--)//��������
		{
			PBox(*(Snake[i]+0),*(Snake[i]+1));//��ӡ����
		}
	Goto(*(Snake[0]+0),*(Snake[0]+1));
	printf("@@");//��ӡ��ͷ
	Goto(*(Snake[SnakeLength-1]+0),*(Snake[SnakeLength-1]+1));
	printf("��");//��ӡ��β 
}


void Double_AddSpeed(int SnakeLength)//���������������ٶ�
{
	if(WaitTime == 0)//��WaitTime���ı�ʱ�����л�ԭ
		{
			int NewTime;
			NewTime = Speed - (SnakeLength-SNAKE_LENGTH*2)*10;//��ȡ�µĵȴ�ʱ��
			if(NewTime >= 10)//����µĵȴ�ʱ��>=10
				WaitTime = NewTime;//���µĵȴ�ʱ�丳ֵ��WaitTime
			else//�µĵȴ�ʱ��<=10
				WaitTime = 10;			
		}
}


void Double_PScore(int SnakeLength)//��ӡ����
{
	int score = (SnakeLength-SNAKE_LENGTH * 2)*10 + int((SnakeLength-SNAKE_LENGTH*2) / 5) * 10;//��ǰ�����ȼ�ȥ��ʼֵ��*10

	SetColor(15);
	for(int i = 42; i < 52; i++){
		PBox(i,25);
		PBox(i,29);
	}
	for(int i = 25; i < 29; i++){
		PBox(42,i);
		PBox(47,i);
		PBox(51,i);
	}	
	
	
	SetColor(10);
	Goto(44,27);
	printf("�÷�");
	Goto(49,27);
	printf("%d",score);
}

int PK_Rank(int SnakeLength1, int SnakeLength2){
	SetColor(12); 
	Goto(26,3);
	printf("̰����");
	SetColor(15);//������ɫ ��ɫ 
	for(int i = 0; i < 55; i++){
		PBox(i,0);
		PBox(i,39);
	} 
	for(int i = 0; i < 40; i++){
		PBox(0,i);
		PBox(54,i);
	}  
	for(int i = 23; i < 32; i++){
		PBox1(i,5);
		PBox1(i,9);
		if(i >= 25 && i <= 30){
			PBox1(i,13);
			PBox1(i,15);
			PBox1(i,17);		
		} 
	}
	PBox1(25,14);PBox1(30,14);PBox1(25,16);PBox1(30,16);
	for(int i = 5; i < 10; i++){
		PBox1(23,i);
		PBox1(28,i);
		PBox1(32,i);
	}//�߿��Լ��÷���Ϣ��	
	Psqrt(6,2,25,19);
	
	int score1 = (SnakeLength1-SNAKE_LENGTH)*10 + int((SnakeLength1-SNAKE_LENGTH) / 5) * 10;
	int score2 = (SnakeLength2-SNAKE_LENGTH)*10 + int((SnakeLength2-SNAKE_LENGTH) / 5) * 10;
	Goto(25,7);
	SetColor(12); 
	printf("�÷�");
	Goto(30,7);	
	printf("%d",score1 > score2 ? score1 : score2);
	SetColor(15);
	Goto(26,16);
	printf("�����Ѷ�");//ʵ�ֽ��� 			
	
	Psqrt(19,3,18,12);
	Goto(26,13);
	printf("��ϲ���");
	Goto(20,14);
	printf("��ϲ��������%d�ĸ߷������ܶ��֣�",score1 > score1 ? score1 : score2);
	SetColor(10); 
	Goto(16,26);
	printf("�������а�");
	Goto(34,26);
	printf("˫�����а�");
	Readrank(2);
	
	
	Goto(26,20);
	scanf("%d",&Speed);
	WaitTime = Speed;
	Goto(31,20);
	printf("��");
	Sleep(3000);//��ͣ����
	return 0;
	
}

void PK_PScore(int SnakeLength1,int SnakeLength2)//��ӡ����
{	
	int score1 = (SnakeLength1-SNAKE_LENGTH)*10 + int((SnakeLength1-SNAKE_LENGTH) / 5) * 10;
	int score2 = (SnakeLength2-SNAKE_LENGTH)*10 + int((SnakeLength2-SNAKE_LENGTH) / 5) * 10;
	SetColor(15);
	Psqrt(6,4,42,25);
	Psqrt(5,4,47,25);
	Psqrt(6,4,42,6);
	Psqrt(5,4,47,6);
	Goto(49,27);
	printf("   ");
	Goto(49,8);
	printf("   ");
	SetColor(10);
	Goto(44,27);
	printf("�÷�");
	Goto(49,27);
	printf("%d",score1);
	
	SetColor(8);
	Goto(44,8);
	printf("�÷�");
	Goto(49,8);
	printf("%d",score2);		

}

void Double_GameOver(int (*Snake1)[2],int (*Snake2)[2],int *SnakeLength1,int *SnakeLength2,int *Food)
{
	SetColor(15);
	PBox(18,15); PBox(21,15);
	for(int i = 11; i < 29; i++){
		PBox(i,16);
		PBox(i,18);
		if(i >= 18 && i <= 21)
			PBox(i,14);
	}
	PBox(11,17); PBox(28,17);// ��ӡ�߿� 
	
	SetColor(10);
	Goto(12,17);
	printf("��Ϸ������������Զ���ʼ������Ϸ");	
	Goto(19,15);
	printf("��ʾ");	
	Sleep(3000);//��ͣ����
	system("cls");//�����Ļ
	if(Mode == 'C' || Mode == 'c')
		PK_Rank(*SnakeLength1,*SnakeLength2);//������� 
	else 
		Rank(*SnakeLength1+*SnakeLength2);//������� 
	*SnakeLength1 = SNAKE_LENGTH;	//����������
	*SnakeLength2 = SNAKE_LENGTH;	//����������
	PInterface(); //��ʼ������
	Double_InitSnake(Snake1,*SnakeLength1,1);//��ʼ������
	Double_InitSnake(Snake2,*SnakeLength2,2);//��ʼ������	
	Double_CreateFood(Food,Snake1,Snake2,*SnakeLength1,*SnakeLength2);//������ʵ
	Dire1 = 77;//���÷���
	Dire2 = 's';//���÷���
	Sleep(1000);
	if(Mode == 'C' || Mode == 'c')
		PK_PScore(*SnakeLength1,*SnakeLength2);
	else 
		Double_PScore(*SnakeLength1+*SnakeLength2);
}


bool Double_Judge(int Sx1,int Sy1,int Sx2,int Sy2,int (*Snake1)[2],int (*Snake2)[2],int *SnakeLength1,int *SnakeLength2,int *Food)
{
	int i;	
	if(( Sx1<=0||Sx1>=39||Sy1>=39||Sy1<=0) || (Sx2<=0||Sx2>=39||Sy2>=39||Sy2<=0) )//�ж��Ƿ�ײǽ
		{
			Double_GameOver(Snake1,Snake2,SnakeLength1,SnakeLength2,Food);//������Ϸ
			return false;
		}	
	if(Sx1 == Sx2 && Sy1 == Sy2 )
		{
			Double_GameOver(Snake1,Snake2,SnakeLength1,SnakeLength2,Food);//������Ϸ
			return false;
		}	
	for(i=0;i<*SnakeLength1;i++)
		{
			if( (Sx1==Snake1[i][0]&&Sy1==Snake1[i][1]) || (Sx2==Snake1[i][0]&&Sy2==Snake1[i][1]) )//�ж��Ƿ�ײ���� 
				{
					Double_GameOver(Snake1,Snake2,SnakeLength1,SnakeLength2,Food);//������Ϸ
					return false;
				}
		}
	for(i=0;i<*SnakeLength2;i++)
		{
			if((Sx1==Snake2[i][0]&&Sy1==Snake2[i][1]) || (Sx2==Snake2[i][0]&&Sy2==Snake2[i][1]))
				{
					Double_GameOver(Snake1,Snake2,SnakeLength1,SnakeLength2,Food);//������Ϸ
					return false;
				}
		}	
			
	if( Sx1==*Food&&Sy1==*(Food+1))//�ж��Ƿ���ʳ��
		{	
			//printf("\a"); 
			(*SnakeLength1)++;//���ӳ���
			Double_CreateFood(Food,Snake1,Snake2,*SnakeLength1,*SnakeLength2);//����ʳ��
			if(Mode == 'C' || Mode == 'c')
				PK_PScore(*SnakeLength1,*SnakeLength2);
			else 
				Double_PScore(*SnakeLength1+*SnakeLength2);//���·���
		}
	if( Sx2==*Food&&Sy2==*(Food+1))//�ж��Ƿ���ʳ��
		{	
			//printf("\a"); 
			(*SnakeLength2)++;//���ӳ���
			Double_CreateFood(Food,Snake1,Snake2,*SnakeLength1,*SnakeLength2);//����ʳ��
			if(Mode == 'C' || Mode == 'c')
				PK_PScore(*SnakeLength1,*SnakeLength2);
			else 
				Double_PScore(*SnakeLength1+*SnakeLength2);//���·���
		}
	return true;
}	

void ClearSnake(int (*Snake)[2],int SnakeLength){
	for(int i=SnakeLength-1;i>=0;i--)//��������
		{
			Goto(*(Snake[i]+0),*(Snake[i]+1));
			printf("  ");
		}
}


void PK_Judge(int Sx1,int Sy1,int Sx2,int Sy2,int (*Snake1)[2],int (*Snake2)[2],int *SnakeLength1,int *SnakeLength2,int *Food1,int *Food2,int *Food3)
{
	int i;
	if( (  Sx1<=0||Sx1>=39||Sy1>=39||Sy1<=0 ) && ( Sx2>0 && Sx2 < 39 && Sy2 < 39 && Sy2 > 0 ) ) //�ж��Ƿ�ײǽ
	{
		Double_MoveSnake(Sx2,Sy2,Snake2,*SnakeLength2,2);
	}			
	if( (  Sx2<=0||Sx2>=39||Sy2>=39||Sy2<=0 ) && ( Sx1 > 0 && Sx1 < 39 && Sy1 < 39 && Sy1 > 0 ) ) //�ж��Ƿ�ײǽ
	{
		Double_MoveSnake(Sx1,Sy1,Snake1,*SnakeLength1,1);
	}			
	if( ( Sx2>0 && Sx2 < 39 && Sy2 < 39 && Sy2 > 0 ) && ( Sx1 > 0 && Sx1 < 39 && Sy1 < 39 && Sy1 > 0 ) ) {
		Double_MoveSnake(Sx2,Sy2,Snake2,*SnakeLength2,2);
		Double_MoveSnake(Sx1,Sy1,Snake1,*SnakeLength1,1);
	}			
	
	if(Sx1 == Sx2 && Sy1 == Sy2 )
		{
			ClearSnake(Snake1,*SnakeLength1);
			ClearSnake(Snake2,*SnakeLength2);
			*SnakeLength1 = SNAKE_LENGTH;
			*SnakeLength2 = SNAKE_LENGTH;
			Double_InitSnake(Snake1,*SnakeLength1,1);
			Double_InitSnake(Snake2,*SnakeLength2,2);
			PK_PScore(*SnakeLength1,*SnakeLength2);
			return;
		}		
	for(i= 3;i < *SnakeLength1;i++)
		{
			if( Sx1==Snake1[i][0] && Sy1==Snake1[i][1] )//�ж��Ƿ�ײ���� 
				{
					ClearSnake(Snake1,*SnakeLength1);
					*SnakeLength1 = SNAKE_LENGTH;
					Double_InitSnake(Snake1,*SnakeLength1,1);
					PK_PScore(*SnakeLength1,*SnakeLength2);
					return;
				}
		}
	for(i= 0;i < *SnakeLength1;i++){
			if( Sx2 == Snake1[i][0] && Sy2 == Snake1[i][1] )
				{
					ClearSnake(Snake2,*SnakeLength2);
					for(int j = 0;j < *SnakeLength2 - SNAKE_LENGTH;j++)//��������
						{
							*(Snake2[*SnakeLength1+j]+0) = *(Snake2[*SnakeLength1-1]+0); //�������������δӺ���ǰ����
							*(Snake2[*SnakeLength1+j]+1) = *(Snake2[*SnakeLength1-1]+1);
						}
					*SnakeLength1 = *SnakeLength1 + *SnakeLength2 - SNAKE_LENGTH;
					*SnakeLength2 = SNAKE_LENGTH;
					Double_InitSnake(Snake2,*SnakeLength2,2);
					PK_PScore(*SnakeLength1,*SnakeLength2);
					return;
				}
		}
	for(i = 3 ;i <*SnakeLength2;i++)
		{
			if(Sx2 == Snake2[i][0] && Sy2==Snake2[i][1])
				{
					ClearSnake(Snake2,*SnakeLength2);
					*SnakeLength2 = SNAKE_LENGTH;
					Double_InitSnake(Snake2,*SnakeLength2,2);
					PK_PScore(*SnakeLength1,*SnakeLength2);
					return;
				}
		}
	for(i = 0 ;i <*SnakeLength2;i++){
			if(Sx1 == Snake2[i][0] && Sy1 == Snake2[i][1])
				{
					ClearSnake(Snake1,*SnakeLength1);
					for(int j = 0;j < *SnakeLength1 - SNAKE_LENGTH;j++)//��������
						{
							*(Snake2[*SnakeLength2+j]+0) = *(Snake2[*SnakeLength2-1]+0); //�������������δӺ���ǰ����
							*(Snake2[*SnakeLength2+j]+1) = *(Snake2[*SnakeLength2-1]+1);
						}
					*SnakeLength2 = *SnakeLength1 + *SnakeLength2 - SNAKE_LENGTH;
					*SnakeLength1 = SNAKE_LENGTH;	
					Double_InitSnake(Snake1,*SnakeLength1,1);
					PK_PScore(*SnakeLength1,*SnakeLength2);
					return;
				}
		}		

	if(Sx1==*Food1&&Sy1==*(Food1+1) )//�ж��Ƿ���ʳ��
		{	
			(*SnakeLength1)++;//���ӳ���
			Double_CreateFood(Food1,Snake1,Snake2,*SnakeLength1,*SnakeLength2);//����ʳ��
			if(Mode == 'C' || Mode == 'c')
				PK_PScore(*SnakeLength1,*SnakeLength2);
			else 
				Double_PScore(*SnakeLength1+*SnakeLength2);//���·���
		}
	if( Sx2==*Food1&&Sy2==*(Food1+1))//�ж��Ƿ���ʳ��
		{	 
			(*SnakeLength2)++;//���ӳ���
			Double_CreateFood(Food1,Snake1,Snake2,*SnakeLength1,*SnakeLength2);//����ʳ��
			if(Mode == 'C' || Mode == 'c')
				PK_PScore(*SnakeLength1,*SnakeLength2);
			else 
				Double_PScore(*SnakeLength1+*SnakeLength2);//���·���
		}
		
	if(Sx1==*Food2&&Sy1==*(Food2+1) )//�ж��Ƿ���ʳ��
		{	
			(*SnakeLength1)++;//���ӳ���
			Double_CreateFood(Food2,Snake1,Snake2,*SnakeLength1,*SnakeLength2);//����ʳ��
			if(Mode == 'C' || Mode == 'c')
				PK_PScore(*SnakeLength1,*SnakeLength2);
			else 
				Double_PScore(*SnakeLength1+*SnakeLength2);//���·���
		}
	if( Sx2==*Food2&&Sy2==*(Food2+1))//�ж��Ƿ���ʳ��
		{	 
			(*SnakeLength2)++;//���ӳ���
			Double_CreateFood(Food2,Snake1,Snake2,*SnakeLength1,*SnakeLength2);//����ʳ��
			if(Mode == 'C' || Mode == 'c')
				PK_PScore(*SnakeLength1,*SnakeLength2);
			else 
				Double_PScore(*SnakeLength1+*SnakeLength2);//���·���
		}	
		
	if(Sx1==*Food3&&Sy1==*(Food3+1) )//�ж��Ƿ���ʳ��
		{	
			//printf("\a"); 
			(*SnakeLength1)++;//���ӳ���
			Double_CreateFood(Food3,Snake1,Snake2,*SnakeLength1,*SnakeLength2);//����ʳ��
			if(Mode == 'C' || Mode == 'c')
				PK_PScore(*SnakeLength1,*SnakeLength2);
			else 
				Double_PScore(*SnakeLength1+*SnakeLength2);//���·���
		}
	if( Sx2==*Food3&&Sy2==*(Food3+1))//�ж��Ƿ���ʳ��
		{	
			//printf("\a"); 
			(*SnakeLength2)++;//���ӳ���
			Double_CreateFood(Food3,Snake1,Snake2,*SnakeLength1,*SnakeLength2);//����ʳ��
			if(Mode == 'C' || Mode == 'c')
				PK_PScore(*SnakeLength1,*SnakeLength2);
			else 
				Double_PScore(*SnakeLength1+*SnakeLength2);//���·���
		}		
	return;
}	

void PK_GameOver(int (*Snake1)[2],int (*Snake2)[2],int *SnakeLength1,int *SnakeLength2,int *Food1,int *Food2,int *Food3)
{
	SetColor(15);
	PBox(18,15); PBox(21,15);
	for(int i = 11; i < 29; i++){
		PBox(i,16);
		PBox(i,18);
		if(i >= 18 && i <= 21)
			PBox(i,14);
	}
	PBox(11,17); PBox(28,17);// ��ӡ�߿� 
	SetColor(10);
	Goto(12,17);
	printf("��Ϸ������������Զ���ʼ������Ϸ");	
	Goto(19,15);
	printf("��ʾ");	
	Sleep(3000);//��ͣ����
	system("cls");//�����Ļ
	if(Mode == 'C' || Mode == 'c')
		PK_Rank(*SnakeLength1,*SnakeLength2);//������� 
	else 
		Rank(*SnakeLength1+*SnakeLength2);//������� 
	*SnakeLength1 = SNAKE_LENGTH;	//����������
	*SnakeLength2 = SNAKE_LENGTH;	//����������
	PInterface(); //��ʼ������
	Double_InitSnake(Snake1,*SnakeLength1,1);//��ʼ������
	Double_InitSnake(Snake2,*SnakeLength2,2);//��ʼ������	
	Double_CreateFood(Food1,Snake1,Snake2,*SnakeLength1,*SnakeLength2);//������ʵ
	Sleep(1000);
	Double_CreateFood(Food2,Snake1,Snake2,*SnakeLength1,*SnakeLength2);//������ʵ
	Sleep(1000);
	Double_CreateFood(Food3,Snake1,Snake2,*SnakeLength1,*SnakeLength2);//������ʵ
	Dire1 = 77;//���÷���
	Dire2 = 's';//���÷���
	Sleep(1000);
	if(Mode == 'C' || Mode == 'c')
		PK_PScore(*SnakeLength1,*SnakeLength2);
	else 
		Double_PScore(*SnakeLength1+*SnakeLength2);
}
	
int main(){	
	ReGame: Init(); //��ʼ������
	ThreadKey = false;
	if(Mode == 'A' || Mode == 'a' ){
		int Snake[400][2];
		int SnakeLength = SNAKE_LENGTH;//��ʼ��������
		int Food[2];
		clock_t NowTime; //����ʱ�����
		InitSnake(Snake,SnakeLength);//Snake�ǰ���ַ���ã���ʼ������
		CreateFood(Food,Snake,SnakeLength);//������ʵ
		PScore(SnakeLength);//��ӡ����
		CreateThread( NULL, 0,ListenKey, 0, 0, 0 );   //ʹ��CreateThread���������̣߳��ÿ������߳�ִ��ListenKey����
		while(true) //��ѭ��
			{
				int Sx = Snake[0][0];//ȡ����ͷ������
				int Sy = Snake[0][1];
				AddSpeed(SnakeLength);//���������峤�ȸı��ٶ�
				NextStape(&Sx,&Sy);//���ݷ��򣬼����²���ͷλ��	
				if(Judge(Sx,Sy,Snake,&SnakeLength,Food)!=0)//�ж��²������
				{
					MoveSnake(Sx,Sy,Snake,SnakeLength);
				}//�����жϵ�������ƶ������壬��������������ƶ�����
				NowTime=clock();//��ȡ��ǰʱ��
				while(clock()-NowTime<WaitTime){}	//��ʱ�����õ�ǰʱ���ȥ�����ȡ��ʱ����ȴ�ʱ��Ƚ�
				if(Stoop){
					Stoop = false;
					goto ReGame;
				}
			}
		getch();
	}else if(Mode == 'B' || Mode == 'b' ){
		int Snake1[400][2];
		int Snake2[400][2];
		int SnakeLength1 = SNAKE_LENGTH;//��ʼ��������
		int SnakeLength2 = SNAKE_LENGTH;//��ʼ��������
		int Food[2];
		clock_t NowTime; //����ʱ�����
		CreateThread( NULL, 0,Double_ListenKey, 0, 0, 0 );   //ʹ��CreateThread���������̣߳��ÿ������߳�ִ��ListenKey����
		Double_InitSnake(Snake1,SnakeLength1,1);//Snake�ǰ���ַ���ã���ʼ������
		Sleep(1000);
		Double_InitSnake(Snake2,SnakeLength2,2);//Snake�ǰ���ַ���ã���ʼ������
		Double_CreateFood(Food,Snake1,Snake2,SnakeLength1,SnakeLength2);//����ʳ��
		Double_PScore(SnakeLength1 + SnakeLength2);//��ӡ����
		while(true) //��ѭ��
			{
				int Sx1 = Snake1[0][0];//ȡ����ͷ������
				int Sy1 = Snake1[0][1];
				
				int Sx2 = Snake2[0][0];//ȡ����ͷ������
				int Sy2 = Snake2[0][1];
				
				Double_AddSpeed(SnakeLength1 + SnakeLength2);//���������峤�ȸı��ٶ�
				Double_NextStape(&Sx1,&Sy1,&Sx2,&Sy2);//���ݷ��򣬼����²���ͷλ��			
				if(Double_Judge(Sx1,Sy1,Sx2,Sy2,Snake1,Snake2,&SnakeLength1,&SnakeLength2,Food))//�ж��²������
				{
					Double_MoveSnake(Sx1,Sy1,Snake1,SnakeLength1,1);
					Double_MoveSnake(Sx2,Sy2,Snake2,SnakeLength2,2);
				}
				
				NowTime=clock();//��ȡ��ǰʱ��
				while(clock()-NowTime<WaitTime){}	//��ʱ�����õ�ǰʱ���ȥ�����ȡ��ʱ����ȴ�ʱ��Ƚ�
				if(Stoop){
					Stoop = false;
					goto ReGame;
				}
			}	
		getch();
	}else if(Mode == 'C' || Mode == 'c'){
		int Snake1[400][2];
		int Snake2[400][2];
		int SnakeLength1 = SNAKE_LENGTH;//��ʼ��������
		int SnakeLength2 = SNAKE_LENGTH;//��ʼ��������
		int Food1[2], Food2[2], Food3[2];
		clock_t NowTime; //����ʱ�����
		clock_t StartTime;
		Double_InitSnake(Snake1,SnakeLength1,1);//Snake�ǰ���ַ���ã���ʼ������
		Sleep(1000);
		Double_InitSnake(Snake2,SnakeLength2,2);//Snake�ǰ���ַ���ã���ʼ������
		PK_PScore(SnakeLength1 , SnakeLength2);//��ӡ����
		CreateThread( NULL, 0,PK_ListenKey, 0, 0, 0 );   //ʹ��CreateThread���������̣߳��ÿ������߳�ִ��ListenKey����
		Double_CreateFood(Food1,Snake1,Snake2,SnakeLength1,SnakeLength2);//����ʳ��
		Sleep(1000);
		Double_CreateFood(Food2,Snake1,Snake2,SnakeLength1,SnakeLength2);//����ʳ��
		Sleep(1000);
		Double_CreateFood(Food3,Snake1,Snake2,SnakeLength1,SnakeLength2);//����ʳ��
		Star: StartTime = clock();
		while(true) //��ѭ��
			{
				Sx1 = Snake1[0][0];//ȡ����ͷ������
				Sy1 = Snake1[0][1];
				
				Sx2 = Snake2[0][0];//ȡ����ͷ������
				Sy2 = Snake2[0][1];
						
				Double_AddSpeed(SnakeLength1 + SnakeLength2);//���������峤�ȸı��ٶ�
				Double_NextStape(&Sx1,&Sy1,&Sx2,&Sy2);//���ݷ��򣬼����²���ͷλ��			
				PK_Judge(Sx1,Sy1,Sx2,Sy2,Snake1,Snake2,&SnakeLength1,&SnakeLength2,Food1,Food2,Food3);//�ж��²������							
				NowTime=clock();//��ȡ��ǰʱ��
				while(clock()-NowTime<WaitTime){}	//��ʱ�����õ�ǰʱ���ȥ�����ȡ��ʱ����ȴ�ʱ��Ƚ�
				if(clock() - StartTime > DefaultTime * GameTime ) break;
				if(Stoop){
					Stoop = false;
					goto ReGame;
				}
			}
		PK_GameOver(Snake1,Snake2,&SnakeLength1,&SnakeLength2,Food1,Food2,Food3);//������Ϸ
		goto Star;			
	} 
	return 0;
}

