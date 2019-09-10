#include<stdio.h>
#include<conio.h>
#include<windows.h>	
#include<stdlib.h>//产生随机数的库 
#include<time.h> 

const int SNAKE_LENGTH = 3;//设置一个常量，起始蛇身长度 

//定义全局变量
char Mode = 'A';//默认为单蛇模式 
int WaitTime;//等待时间 
int Speed;//当前速度 
double DefaultTime = 1000 * 60;//一分钟 
double GameTime = 1;//游戏时长 
//单蛇模式使用 
char Dire=77;//默认方向 
bool Stoop = false;
bool ThreadKey = false;
int Sx1,Sx2,Sy1,Sy2;//解决双蛇模式的冲突问题 


//双蛇模式下使用 
char Dire1=77;
char Dire2='s';

struct info{
	char name[20];
	char password[20]; 
	int score;
	int DoubleScore;
};//排行榜结构体  

info NowGamer;//记录当前游戏玩家信息 

// 隐藏光标 固定函数	
void Hide_Cursor(HANDLE hConsole)			                    	
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };  //CONSOLE_CURSOR_INFO: 控制台光标的信息
	SetConsoleCursorInfo(hConsole, &cursor_info);//设置光标信息，返回类别bool 
}


//光标定位函数 
void Goto(int x, int y)
{
	short a=(short)x*2;									//*2保证xy是1:1的转换，把x的扩大二倍，因为用的打印的方块都是占一个字符
	COORD pos = {a, (short)y };		        	      	// 定义一个字符在控制台屏幕上的坐标POS, COORD:表示一个字符在控制台屏幕上的坐标
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // 获取标准输出的句柄
	SetConsoleCursorPosition(hConsole, pos);	    	// 定位光标位置的函数
	Hide_Cursor(hConsole);
}
/*
HANDLE就是PVOID，也就是无类型指针
说的确切一点，句柄实际上是一种指向某种资源的指针，但与指针又有所不同：指针对应着一个数据在内存中的地址，
得到了指针就可以自由地修改该数据。Windows并不希望一般程序修改其内部数据结构，因为这样太不安全。
所以Windows给每个使用GlobalAlloc等函数声明的内存区域指定一个句柄(本质上仍是一个指针，但不要直接操作它),
平时你只是在调用API函数时利用这个句柄来说明要操作哪段内存。 
*/


//设置颜色
void SetColor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);//设置控制台窗口字体颜色和背景色的计算机函数 
} 
 
 
void PBox(int x,int y)//在x，y处打印方块
{
	Goto(x,y);
	printf("■");
}

void PBox1(int x,int y)//在x，y处打印方块
{
	Goto(x,y);
	printf("★");
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
					}//单蛇排行榜排序 
			for(j = 0; j < i && j < 10; j++){
				Goto(41,j+6);
				printf("第%d名：%6s 得分：%d",j+1,tmp[j].name,tmp[j].score );
			}
		}else if(Mode == 'B' || Mode == 'b'){
			for(j = 0;j < i;j++)		
				for(k = 0;k <= i;k++){			
					if(tmp[k].DoubleScore<tmp[j].DoubleScore){				
						temp = tmp[k];				
						tmp[k] = tmp[j];				
						tmp[j] = temp;			
						}		
					}//双蛇排行榜排序
			for(j = 0; j < i && j < 10; j++){
				Goto(41,j+6);
				printf("第%d名：%6s 得分：%d",j+1,tmp[j].name,tmp[j].DoubleScore );
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
				}//单蛇排行榜排序 
		for(j = 0; j < i && j < 10; j++){
				Goto(13,j+28);
				printf("第%d名：%6s 得分：%d",j+1,tmp[j].name,tmp[j].score );
			}
		
		for(j = 0;j < i;j++)		
			for(k = 0;k <= i;k++){			
				if(tmp[k].DoubleScore<tmp[j].DoubleScore){				
					temp = tmp[k];				
					tmp[k] = tmp[j];				
					tmp[j] = temp;			
					}		
				}//双蛇排行榜排序
		for(j = 0; j < i && j < 10; j++){
				Goto(31,j+28);
				printf("第%d名：%6s 得分：%d",j+1,tmp[j].name,tmp[j].DoubleScore);
			} 
	}	
	fclose(fp);	
	return 0;
}


//实现排行榜	
int Rank(int SnakeLength){
	SetColor(12); 
	Goto(26,3);
	printf("贪吃蛇");
	SetColor(15);//设置颜色 白色 
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
	}//边框以及得分信息框	
	Psqrt(6,2,25,19);
	
	Goto(25,7);
	SetColor(12); 
	printf("得分");
	Goto(30,7);
	if(Mode == 'A' || Mode == 'a')
		printf("%d",(SnakeLength-SNAKE_LENGTH)*10 + int((SnakeLength-SNAKE_LENGTH) / 5) * 10);
	else if(Mode == 'B' || Mode == 'b')
		printf("%d",(SnakeLength-SNAKE_LENGTH * 2)*10 + int((SnakeLength-SNAKE_LENGTH*2) / 5) * 10);
	SetColor(15);
	Goto(26,16);
	printf("重置难度");//实现界面 
			
	if(Mode == 'A' || Mode == 'a'){
		if(NowGamer.score <= (SnakeLength-SNAKE_LENGTH)*10 + int((SnakeLength-SNAKE_LENGTH) / 5) * 10){
			NowGamer.score = (SnakeLength-SNAKE_LENGTH)*10 + int((SnakeLength-SNAKE_LENGTH) / 5) * 10;
			Psqrt(19,3,18,12);
			Goto(26,13);
			printf("再接再厉");
			Goto(19,14);
			printf("恭喜%s大侠，你创造了自己的新纪录!",NowGamer.name);
			//保存新纪录 
			FILE *fin,*ftp;
		    info temp;
		    fin=fopen("rank.txt","r");//读打开原文件
		    ftp=fopen("tmp.txt","w");//写打开临时文件
		    while(fscanf(fin,"%s %s %d %d",temp.name,temp.password,&temp.score,&temp.DoubleScore)!=EOF)//从原文件读取一行
		        if( strcmp(temp.name,NowGamer.name) != 0 )//检验账号是否相同 
		           fprintf(ftp,"%s %s %d %d\n",temp.name,temp.password,temp.score,temp.DoubleScore);//不是则将这一行写入临时文件tmp.txt
		    fprintf(ftp,"%s %s %d %d\n",NowGamer.name,NowGamer.password,NowGamer.score,NowGamer.DoubleScore);
			fclose(fin);
		    fclose(ftp); 
		    remove("rank.txt");// 删除文件 
		    rename("tmp.txt","rank.txt");//将临时文件名改为原文件名 
		}else{
			Psqrt(19,3,18,12);
			Goto(26,13);
			printf("不要放弃");
			Goto(19,14);
			printf("很遗憾%s大侠，你就差那么一点点!",NowGamer.name);
		} 
	}
	else if(Mode == 'B' || Mode == 'b'){		
		if(NowGamer.DoubleScore <= (SnakeLength-SNAKE_LENGTH * 2)*10 + int((SnakeLength-SNAKE_LENGTH*2) / 5) * 10){
			NowGamer.DoubleScore = (SnakeLength-SNAKE_LENGTH * 2)*10 + int((SnakeLength-SNAKE_LENGTH*2) / 5) * 10;
			Psqrt(19,3,18,12);
			Goto(26,13);
			printf("再接再厉");
			Goto(19,14);
			printf("恭喜%s大侠，你创造了自己的新纪录!",NowGamer.name);
			//保存新纪录 
			FILE *fin,*ftp;
		    info temp;
		    fin=fopen("rank.txt","r");//读打开原文件
		    ftp=fopen("tmp.txt","w");//写打开临时文件
		    while(fscanf(fin,"%s %s %d %d",temp.name,temp.password,&temp.score,&temp.DoubleScore)!=EOF)//从原文件读取一行
		        if( strcmp(temp.name,NowGamer.name) != 0 )//检验账号是否相同 
		           fprintf(ftp,"%s %s %d %d\n",temp.name,temp.password,temp.score,temp.DoubleScore);//不是则将这一行写入临时文件tmp.txt
		    fprintf(ftp,"%s %s %d %d\n",NowGamer.name,NowGamer.password,NowGamer.score,NowGamer.DoubleScore);
			fclose(fin);
		    fclose(ftp); 
		    remove("rank.txt");// 删除文件 
		    rename("tmp.txt","rank.txt");//将临时文件名改为原文件名 
		}else{
			Psqrt(19,3,18,12);
			Goto(26,13);
			printf("不要放弃");
			Goto(19,14);
			printf("很遗憾%s大侠，你就差那么一点点!",NowGamer.name);
		} 
	}
	
	SetColor(10); 
	Goto(16,26);
	printf("单蛇排行榜");
	Goto(34,26);
	printf("双蛇排行榜");
	Readrank(2);
		
	Goto(26,20);
	scanf("%d",&Speed);
	WaitTime = Speed;
	Goto(31,20);
	printf("√");
	Sleep(3000);//暂停三秒
	return 0;
}


void PInterface()//打印界面
{
	system("cls");//清空屏幕
	int i=0;
	SetColor(15);//设置颜色 白色  
	for(;i<55;i++)
	{
		if(i<=39)
			{	
				PBox(0,i);//打印竖线
				PBox(39,i);
				PBox(54,i);
				PBox(i,0);//打印横线
				PBox(i,39);
			}
		else 
			{	
				PBox(i,0);//打印竖线
				PBox(i,39);
			}	
	}
	if(Mode == 'A' || Mode == 'B' || Mode == 'a' || Mode =='b'){
		Goto(45,3);//打印信息
		printf("贪吃蛇游戏");
		Goto(45,5);
		if(Mode == 'A' || Mode == 'a')
			printf("单蛇排行榜");
		else if(Mode == 'B' || Mode == 'b')
			printf("双蛇排行榜");
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
				NowGamer = tmp;//保存当前游戏玩家之前信息 
				fclose(fp);
				return true;
			}
			else{
				fclose(fp);
				return false;
			}
		}			
	}
	NowGamer = temp;//保存当前游戏玩家之前信息 				
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
	PBox(17,16); PBox(34,16);// 打印边框 
	
	SetColor(14);
	Goto(18,16);
	printf("账号或者密码错误，请重新登陆游戏");	
	Goto(25,14);
	printf("提示");		
}

//初始化界面
void Init()
{
	//设置标题
	system("贪吃蛇");
	
	//调整控制台的宽高
	system("mode con: cols=110 lines=40"); 
		
	SetColor(12); 
	Goto(26,3);
	printf("贪吃蛇");
	SetColor(15);//设置颜色 白色 
	for(int i = 0; i < 55; i++){
		PBox(i,0);
		PBox(i,39);
	} 
	for(int i = 0; i < 40; i++){
		PBox(0,i);
		PBox(54,i);
	} //大边框 
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
	} //打印界面 
	Psqrt(8,2,24,22);
	Psqrt(8,2,14,22);
	Psqrt(8,2,34,22);
	PBox1(26,21);PBox1(29,21);
	
	
	SetColor(5);
	Goto(26,7);
	printf("大侠名讳");
	Goto(27,11);
	printf("密码");
	Goto(16,15);
	printf("设置难度等级,10-1000内的一个数值，10是最快，1000最慢。");
	Goto(26,19);
	printf("模式选择");
	Goto(15,23);
	printf("A：单蛇模式");
	Goto(25,23);
	printf("B：双蛇模式");
	Goto(35,23);
	printf("C：对战模式");
	
	SetColor(10); 
	Goto(16,26);
	printf("单蛇排行榜");
	Goto(34,26);
	printf("双蛇排行榜");
	Readrank(2);//实现界面 
	
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
	printf("√");
	
	
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
	printf("√");
	ReSpeed: Goto(26,17);
	//ch = getchar();
	//if(ch == '\n')
	//	goto ReSpeed;
	scanf("%d",&Speed);
	if(Speed > 1000 || Speed < 10){
		Goto(31,17);
		printf("×");
		for(int i = 0; i < 4; i++){
			Goto(26+i,17);
			printf("  ");
		}
		fflush(stdin);
		goto ReSpeed; 
	}
		
	getchar();//消除回车 
	Goto(31,17);
	printf("√");
	ReMode: Goto(27,21);
	scanf("%c",&Mode);
	if( (Mode != 'A' && Mode != 'a' && Mode != 'B' && Mode != 'b' && Mode != 'C' && Mode != 'c') || getchar() != '\n' ){
		Goto(30,21);
		printf("×");
		for(int i = 0; i < 2; i++){
			Goto(27+i,21);
			printf("  ");
		}
		fflush(stdin);//清空输入缓存区
		goto ReMode; 
	} 
	Goto(30,21);
	printf("√");
	if(Mode == 'C' || Mode == 'c'){
		fflush(stdin);//清空输入缓存区
		Psqrt(8,3,34,17);
		SetColor(15);
		Goto(37,18);
		printf("PK时长");
		Goto(39,19);
		printf(":分钟");
		ReGameTime: Goto(38,19);
		scanf("%lf",&GameTime);
		if(GameTime > 15 ){
			Goto(42,19);
			printf("×");
			Goto(38,19);
			printf("  ");
			fflush(stdin);
			goto ReGameTime; 
		}
	} 
	
	
	
	temp.score = 0;
	temp.DoubleScore = 0;
	if( login(temp) ){
		//调用设置边框函数 
		PInterface();
	} else{
		Relogin();
		//重新登陆 
		Sleep(3000);//暂停三秒
		Init();
	}
} 


void InitSnake(int (*Snake)[2],int SnakeLength)//初始化蛇身
{
	int i;
	srand((unsigned)time(NULL));//重置随机种子，使得产生的随机数不固定 
	loop: int Addressx = rand() % 30;//设置一个起始位置的x坐标随机值 
	int Addressy = rand() % 35;//设置一个起始位置的y坐标随机值 
	if(Addressx <= 2 || Addressy == 0) goto loop;//防止蛇初始位置是墙壁 
	 
	//设置颜色,蛇身颜色 
	SetColor(10);
	for(i=SnakeLength-1;i>0;i--)//遍历蛇身
		{
			*(Snake[i]+0) = Addressx - i;//设置初始值
			*(Snake[i]+1) = Addressy;
			PBox(*(Snake[i]+0),*(Snake[i]+1));//打印身体
		}
	Goto(*(Snake[2]+0),*(Snake[2]+1));
	printf("×");	
	*(Snake[0]+0) = Addressx - i;//设置初始值
	*(Snake[0]+1) = Addressy;	
	Goto(*(Snake[0]+0),*(Snake[0]+1));
	printf("@@");
}


void Clear(int x,int y)//清除x，y处的字符
{
	Goto(x,y);
	putchar('\0');
	putchar('\0');
}


void NextStape(int *Sx,int *Sy)//根据方向确定下一步的x，y
{
	
	switch (Dire)
	  {
		  case 72: (*Sy)--;break; //上
		  case 80: (*Sy)++;break; //下
		  case 75: (*Sx)--;break; //左
		  case 77: (*Sx)++;break; //右
		  case 'w': (*Sy)--;break; //上
		  case 's': (*Sy)++;break; //下
		  case 'a': (*Sx)--;break; //左
		  case 'd': (*Sx)++;break; //右
		  case 'W': (*Sy)--;break; //上
		  case 'S': (*Sy)++;break; //下
		  case 'A': (*Sx)--;break; //左
		  case 'D': (*Sx)++;break; //右
	  }
}


//实现蛇身移动 
void MoveSnake(int Sx,int Sy,int (*Snake)[2],int SnakeLength)  //移动蛇到指定的点
{
	int j;
	Clear(*(Snake[SnakeLength-1]+0),*(Snake[SnakeLength-1]+1));//清除蛇尾
	for(j=SnakeLength;j>=2;j--)//遍历蛇身
		{
			*(Snake[j-1]+0) = *(Snake[j-2]+0); //把蛇身坐标依次从后往前传递
			*(Snake[j-1]+1) = *(Snake[j-2]+1);
		}
	*(Snake[0]+0)=Sx;//给蛇头赋值
	*(Snake[0]+1)=Sy;
	
	SetColor(10);
	Goto(*(Snake[0]+0),*(Snake[0]+1));
	printf("@@");//打印蛇头
	Goto(*(Snake[SnakeLength-1]+0),*(Snake[SnakeLength-1]+1));
	printf("×");//打印蛇尾 
	for(int i=SnakeLength-2;i>0;i--)//遍历蛇身
		{
			PBox(*(Snake[i]+0),*(Snake[i]+1));//打印身体
		}
}


//线程监听键盘输入
DWORD WINAPI ListenKey( LPVOID lpParam )				//检测键盘的敲击
{
    while(!ThreadKey)
      {
	  char flag = getch();//获取键盘信息
	  switch(flag)
			{
				case 72: if(Dire!=80)//判读输入的值，是否与当前值方向相反
							{Dire=flag;WaitTime=0;break;}//如果不相反，改变方向，重置等待时间，跳出switch
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
				case 'w': if(Dire!= 's')//判读输入的值，是否与当前值方向相反
							{Dire=flag;WaitTime=0;break;}//如果不相反，改变方向，重置等待时间，跳出switch
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
				case 'W': if(Dire!= 'S')//判读输入的值，是否与当前值方向相反
							{Dire=flag;WaitTime=0;break;}//如果不相反，改变方向，重置等待时间，跳出switch
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


void PCircle(int x,int y,int fg)//在x，y处打印果实 
{	
	if(fg % 5 != 4){	
		Goto(x,y);
		printf("●");
	}else{
		Goto(x,y);
		printf("★");
	}
}


//产生食物
void CreateFood(int *Food,int Snake[400][2],int SnakeLength)
{
	int Cfood[2];
	srand((unsigned)time(NULL));						//设置随机数种子
	while(true)
		{
			int flag=1;
			int i;
			Cfood[0] = rand()%38+1;//生成位置
			Cfood[1] = rand()%38+1;
			for(i=0;i<SnakeLength;i++)//判断获取的位置是否在蛇身体上
				{
					if(Cfood[0]==Snake[i][0]&&Cfood[1]==Snake[i][1])//如果条件成立
						{flag=0;break;}//跳出循环从新计算
				}
			if(flag==1)//生成的食物是正确的
				{
					SetColor(12);
					PCircle(Cfood[0],Cfood[1],SnakeLength - SNAKE_LENGTH);//打印食物
					*Food = Cfood[0];//为食物赋值
					*(Food+1) = Cfood[1];
					break;
				}
		}	
}


void AddSpeed(int SnakeLength)//根据蛇身长度增加速度
{
	if(WaitTime == 0)//当WaitTime被改变时，进行还原
		{
			int NewTime;
			NewTime = Speed - (SnakeLength-SNAKE_LENGTH)*10;//获取新的等待时间
			if(NewTime >= 10)//如果新的等待时间>=10
				WaitTime = NewTime;//将新的等待时间赋值给WaitTime
			else//新的等待时间<=10
				WaitTime = 10;			
		}
}


void PScore(int SnakeLength)//打印分数
{
	int score = (SnakeLength-SNAKE_LENGTH)*10 + int((SnakeLength-SNAKE_LENGTH) / 5) * 10;//当前蛇身长度减去初始值再*10
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
	printf("得分");
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
	PBox(11,17); PBox(28,17);// 打印边框 
	
	SetColor(10);
	Goto(12,17);
	printf("游戏结束！三秒后自动开始继续游戏");	
	Goto(19,15);
	printf("提示");	
	Sleep(3000);//暂停三秒
	system("cls");//清空屏幕
	Rank(*SnakeLength);//保存分数 
	*SnakeLength = SNAKE_LENGTH;	//重置蛇身长度
	PInterface(); //初始化界面
	InitSnake(Snake,*SnakeLength);//初始化蛇身	
	CreateFood(Food,Snake,*SnakeLength);//产生果实
	Dire = 77;//重置方向
	PScore(*SnakeLength);//打印分数
}


int Judge(int Sx,int Sy,int (*Snake)[2],int *SnakeLength,int *Food)
{
	int i;	
	if(Sx<=0||Sx>=39||Sy>=39||Sy<=0)//判断是否撞墙
		{
			GameOver(Snake,SnakeLength,Food);//结束游戏
			return 0;
		}	
	for(i=3;i<*SnakeLength;i++)//遍历蛇身
		{
			if(Sx==Snake[i][0]&&Sy==Snake[i][1])//判断是否撞到自己
				{
					GameOver(Snake,SnakeLength,Food);//结束游戏
					return 0;//表示游戏结束
				}
		}	
	if(Sx==*Food&&Sy==*(Food+1))//判断是否是食物
		{	
			(*SnakeLength)++;//增加长度
			CreateFood(Food,Snake,*SnakeLength);//创造食物
			PScore(*SnakeLength);//更新分数
		}
}	
		
	
//双蛇模式下改动函数
void Double_InitSnake(int (*Snake)[2],int SnakeLength,int color)//初始化蛇身
{
	int i;
	srand((unsigned)time(NULL));//重置随机种子，使得产生的随机数不固定 
	loop: int Addressx = rand() % 30;//设置一个起始位置的x坐标随机值 
	int Addressy = rand() % 35;//设置一个起始位置的y坐标随机值 
	if(Addressx <= 2 || Addressy == 0) goto loop;//防止蛇初始位置是墙壁 
	 
	//设置颜色,蛇身颜色 
	if(color == 1)	SetColor(10);
	else	SetColor(8);
	for(i=SnakeLength-1;i>0;i--)//遍历蛇身
		{
			*(Snake[i]+0) = Addressx - i;//设置初始值
			*(Snake[i]+1) = Addressy;
			PBox(*(Snake[i]+0),*(Snake[i]+1));//打印身体
		}
	Goto(*(Snake[2]+0),*(Snake[2]+1));
	printf("×");	
	*(Snake[0]+0) = Addressx - i;//设置初始值
	*(Snake[0]+1) = Addressy;	
	Goto(*(Snake[0]+0),*(Snake[0]+1));
	printf("@@");
}	
	
void Double_NextStape(int *Sx1,int *Sy1,int *Sx2,int *Sy2)//根据方向确定下一步的x，y
{	
	switch (Dire1)
	  {
		  case 72: if(*Sy1>0) (*Sy1)--;break; //上
		  case 80: if(*Sy1<39) (*Sy1)++;break; //下
		  case 75: if(*Sx1>0) (*Sx1)--;break; //左
		  case 77: if(*Sx1<54) (*Sx1)++;break; //右
	  }
	switch (Dire2)
	{
		  case 'w': if(*Sy1>1) (*Sy2)--;break; //上
		  case 's': if(*Sy1<39) (*Sy2)++;break; //下
		  case 'a': if(*Sx1>0) (*Sx2)--;break; //左
		  case 'd': if(*Sx1<54) (*Sx2)++;break; //右
		  case 'W': if(*Sy1>1) (*Sy2)--;break; //上
		  case 'S': if(*Sy1<39) (*Sy2)++;break; //下
		  case 'A': if(*Sx1>0) (*Sx2)--;break; //左
		  case 'D': if(*Sx1<54) (*Sx2)++;break; //右
	}
}	

//线程监听键盘输入
DWORD WINAPI Double_ListenKey( LPVOID lpParam )				//检测键盘的敲击
{
    while(!ThreadKey)
      {
      		char flag = getch();//获取键盘信息
	  		switch(flag)
			{
				case 72: if(Dire1 !=80  )//判读输入的值，是否与当前值方向相反
							{Dire1 = flag;WaitTime=0;break;}//如果不相反，改变方向，重置等待时间，跳出switch
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
				case 'w': if(Dire2!= 's' )//判读输入的值，是否与当前值方向相反
							{Dire2=flag;WaitTime=0;break;}//如果不相反，改变方向，重置等待时间，跳出switch
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
				case 'W': if(Dire2!= 'S')//判读输入的值，是否与当前值方向相反
							{Dire2=flag;WaitTime=0;break;}//如果不相反，改变方向，重置等待时间，跳出switch
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

//线程监听键盘输入
DWORD WINAPI PK_ListenKey( LPVOID lpParam )				//检测键盘的敲击
{
    while(!ThreadKey)
      {
	  char flag = getch();//获取键盘信息
	  switch(flag)
			{
				case 72: if(Dire1 !=80 && Sy1 > 1 )//判读输入的值，是否与当前值方向相反
							{Dire1 = flag;WaitTime=0;break;}//如果不相反，改变方向，重置等待时间，跳出switch
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
				case 'w': if(Dire2!= 's' && Sy2 > 1)//判读输入的值，是否与当前值方向相反
							{Dire2=flag;WaitTime=0;break;}//如果不相反，改变方向，重置等待时间，跳出switch
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
				case 'W': if(Dire2!= 'S' && Sy2 > 1)//判读输入的值，是否与当前值方向相反
							{Dire2=flag;WaitTime=0;break;}//如果不相反，改变方向，重置等待时间，跳出switch
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

//产生食物
void Double_CreateFood(int *Food,int Snake1[400][2],int Snake2[400][2],int SnakeLength1,int SnakeLength2) 
{
	int Cfood[2];
	srand((unsigned)time(NULL));						//设置随机数种子
	while(true)
		{
			int flag=1;
			int i;
			Cfood[0] = rand()%38+1;//生成位置
			Cfood[1] = rand()%38+1;
			for(i=0;i<SnakeLength1;i++)//判断获取的位置是否在蛇身体上
				{
					if(Cfood[0]==Snake1[i][0]&&Cfood[1]==Snake1[i][1])//如果条件成立
						{flag=0;break;}//跳出循环从新计算
				}
			for(i=0;i<SnakeLength2;i++)//判断获取的位置是否在蛇身体上
				{
					if(Cfood[0]==Snake2[i][0]&&Cfood[1]==Snake2[i][1])//如果条件成立
						{flag=0;break;}//跳出循环从新计算
				}
			if(flag==1)//生成的食物是正确的
				{
					SetColor(12);
					PCircle(Cfood[0],Cfood[1],SnakeLength1 + SnakeLength2  - SNAKE_LENGTH*2);//打印食物
					*Food = Cfood[0];//为食物赋值
					*(Food+1) = Cfood[1];
					break;
				}
		}	
}

//实现蛇身移动 
void Double_MoveSnake(int Sx,int Sy,int (*Snake)[2],int SnakeLength,int color)  //移动蛇到指定的点
{
	int j;
	Clear(*(Snake[SnakeLength-1]+0),*(Snake[SnakeLength-1]+1));//清除蛇尾
	for(j=SnakeLength;j>=2;j--)//遍历蛇身
		{
			*(Snake[j-1]+0) = *(Snake[j-2]+0); //把蛇身坐标依次从后往前传递
			*(Snake[j-1]+1) = *(Snake[j-2]+1);
		}
	*(Snake[0]+0)=Sx;//给蛇头赋值
	*(Snake[0]+1)=Sy;
	
	if(color == 1) SetColor(10);
	else SetColor(8);
	for(int i=SnakeLength-2;i>0;i--)//遍历蛇身
		{
			PBox(*(Snake[i]+0),*(Snake[i]+1));//打印身体
		}
	Goto(*(Snake[0]+0),*(Snake[0]+1));
	printf("@@");//打印蛇头
	Goto(*(Snake[SnakeLength-1]+0),*(Snake[SnakeLength-1]+1));
	printf("×");//打印蛇尾 
}


void Double_AddSpeed(int SnakeLength)//根据蛇身长度增加速度
{
	if(WaitTime == 0)//当WaitTime被改变时，进行还原
		{
			int NewTime;
			NewTime = Speed - (SnakeLength-SNAKE_LENGTH*2)*10;//获取新的等待时间
			if(NewTime >= 10)//如果新的等待时间>=10
				WaitTime = NewTime;//将新的等待时间赋值给WaitTime
			else//新的等待时间<=10
				WaitTime = 10;			
		}
}


void Double_PScore(int SnakeLength)//打印分数
{
	int score = (SnakeLength-SNAKE_LENGTH * 2)*10 + int((SnakeLength-SNAKE_LENGTH*2) / 5) * 10;//当前蛇身长度减去初始值再*10

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
	printf("得分");
	Goto(49,27);
	printf("%d",score);
}

int PK_Rank(int SnakeLength1, int SnakeLength2){
	SetColor(12); 
	Goto(26,3);
	printf("贪吃蛇");
	SetColor(15);//设置颜色 白色 
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
	}//边框以及得分信息框	
	Psqrt(6,2,25,19);
	
	int score1 = (SnakeLength1-SNAKE_LENGTH)*10 + int((SnakeLength1-SNAKE_LENGTH) / 5) * 10;
	int score2 = (SnakeLength2-SNAKE_LENGTH)*10 + int((SnakeLength2-SNAKE_LENGTH) / 5) * 10;
	Goto(25,7);
	SetColor(12); 
	printf("得分");
	Goto(30,7);	
	printf("%d",score1 > score2 ? score1 : score2);
	SetColor(15);
	Goto(26,16);
	printf("重置难度");//实现界面 			
	
	Psqrt(19,3,18,12);
	Goto(26,13);
	printf("恭喜玩家");
	Goto(20,14);
	printf("恭喜大侠，以%d的高分数击败对手！",score1 > score1 ? score1 : score2);
	SetColor(10); 
	Goto(16,26);
	printf("单蛇排行榜");
	Goto(34,26);
	printf("双蛇排行榜");
	Readrank(2);
	
	
	Goto(26,20);
	scanf("%d",&Speed);
	WaitTime = Speed;
	Goto(31,20);
	printf("√");
	Sleep(3000);//暂停三秒
	return 0;
	
}

void PK_PScore(int SnakeLength1,int SnakeLength2)//打印分数
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
	printf("得分");
	Goto(49,27);
	printf("%d",score1);
	
	SetColor(8);
	Goto(44,8);
	printf("得分");
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
	PBox(11,17); PBox(28,17);// 打印边框 
	
	SetColor(10);
	Goto(12,17);
	printf("游戏结束！三秒后自动开始继续游戏");	
	Goto(19,15);
	printf("提示");	
	Sleep(3000);//暂停三秒
	system("cls");//清空屏幕
	if(Mode == 'C' || Mode == 'c')
		PK_Rank(*SnakeLength1,*SnakeLength2);//保存分数 
	else 
		Rank(*SnakeLength1+*SnakeLength2);//保存分数 
	*SnakeLength1 = SNAKE_LENGTH;	//重置蛇身长度
	*SnakeLength2 = SNAKE_LENGTH;	//重置蛇身长度
	PInterface(); //初始化界面
	Double_InitSnake(Snake1,*SnakeLength1,1);//初始化蛇身
	Double_InitSnake(Snake2,*SnakeLength2,2);//初始化蛇身	
	Double_CreateFood(Food,Snake1,Snake2,*SnakeLength1,*SnakeLength2);//产生果实
	Dire1 = 77;//重置方向
	Dire2 = 's';//重置方向
	Sleep(1000);
	if(Mode == 'C' || Mode == 'c')
		PK_PScore(*SnakeLength1,*SnakeLength2);
	else 
		Double_PScore(*SnakeLength1+*SnakeLength2);
}


bool Double_Judge(int Sx1,int Sy1,int Sx2,int Sy2,int (*Snake1)[2],int (*Snake2)[2],int *SnakeLength1,int *SnakeLength2,int *Food)
{
	int i;	
	if(( Sx1<=0||Sx1>=39||Sy1>=39||Sy1<=0) || (Sx2<=0||Sx2>=39||Sy2>=39||Sy2<=0) )//判断是否撞墙
		{
			Double_GameOver(Snake1,Snake2,SnakeLength1,SnakeLength2,Food);//结束游戏
			return false;
		}	
	if(Sx1 == Sx2 && Sy1 == Sy2 )
		{
			Double_GameOver(Snake1,Snake2,SnakeLength1,SnakeLength2,Food);//结束游戏
			return false;
		}	
	for(i=0;i<*SnakeLength1;i++)
		{
			if( (Sx1==Snake1[i][0]&&Sy1==Snake1[i][1]) || (Sx2==Snake1[i][0]&&Sy2==Snake1[i][1]) )//判断是否撞到蛇 
				{
					Double_GameOver(Snake1,Snake2,SnakeLength1,SnakeLength2,Food);//结束游戏
					return false;
				}
		}
	for(i=0;i<*SnakeLength2;i++)
		{
			if((Sx1==Snake2[i][0]&&Sy1==Snake2[i][1]) || (Sx2==Snake2[i][0]&&Sy2==Snake2[i][1]))
				{
					Double_GameOver(Snake1,Snake2,SnakeLength1,SnakeLength2,Food);//结束游戏
					return false;
				}
		}	
			
	if( Sx1==*Food&&Sy1==*(Food+1))//判断是否是食物
		{	
			//printf("\a"); 
			(*SnakeLength1)++;//增加长度
			Double_CreateFood(Food,Snake1,Snake2,*SnakeLength1,*SnakeLength2);//创造食物
			if(Mode == 'C' || Mode == 'c')
				PK_PScore(*SnakeLength1,*SnakeLength2);
			else 
				Double_PScore(*SnakeLength1+*SnakeLength2);//更新分数
		}
	if( Sx2==*Food&&Sy2==*(Food+1))//判断是否是食物
		{	
			//printf("\a"); 
			(*SnakeLength2)++;//增加长度
			Double_CreateFood(Food,Snake1,Snake2,*SnakeLength1,*SnakeLength2);//创造食物
			if(Mode == 'C' || Mode == 'c')
				PK_PScore(*SnakeLength1,*SnakeLength2);
			else 
				Double_PScore(*SnakeLength1+*SnakeLength2);//更新分数
		}
	return true;
}	

void ClearSnake(int (*Snake)[2],int SnakeLength){
	for(int i=SnakeLength-1;i>=0;i--)//遍历蛇身
		{
			Goto(*(Snake[i]+0),*(Snake[i]+1));
			printf("  ");
		}
}


void PK_Judge(int Sx1,int Sy1,int Sx2,int Sy2,int (*Snake1)[2],int (*Snake2)[2],int *SnakeLength1,int *SnakeLength2,int *Food1,int *Food2,int *Food3)
{
	int i;
	if( (  Sx1<=0||Sx1>=39||Sy1>=39||Sy1<=0 ) && ( Sx2>0 && Sx2 < 39 && Sy2 < 39 && Sy2 > 0 ) ) //判断是否撞墙
	{
		Double_MoveSnake(Sx2,Sy2,Snake2,*SnakeLength2,2);
	}			
	if( (  Sx2<=0||Sx2>=39||Sy2>=39||Sy2<=0 ) && ( Sx1 > 0 && Sx1 < 39 && Sy1 < 39 && Sy1 > 0 ) ) //判断是否撞墙
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
			if( Sx1==Snake1[i][0] && Sy1==Snake1[i][1] )//判断是否撞到蛇 
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
					for(int j = 0;j < *SnakeLength2 - SNAKE_LENGTH;j++)//遍历蛇身
						{
							*(Snake2[*SnakeLength1+j]+0) = *(Snake2[*SnakeLength1-1]+0); //把蛇身坐标依次从后往前传递
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
					for(int j = 0;j < *SnakeLength1 - SNAKE_LENGTH;j++)//遍历蛇身
						{
							*(Snake2[*SnakeLength2+j]+0) = *(Snake2[*SnakeLength2-1]+0); //把蛇身坐标依次从后往前传递
							*(Snake2[*SnakeLength2+j]+1) = *(Snake2[*SnakeLength2-1]+1);
						}
					*SnakeLength2 = *SnakeLength1 + *SnakeLength2 - SNAKE_LENGTH;
					*SnakeLength1 = SNAKE_LENGTH;	
					Double_InitSnake(Snake1,*SnakeLength1,1);
					PK_PScore(*SnakeLength1,*SnakeLength2);
					return;
				}
		}		

	if(Sx1==*Food1&&Sy1==*(Food1+1) )//判断是否是食物
		{	
			(*SnakeLength1)++;//增加长度
			Double_CreateFood(Food1,Snake1,Snake2,*SnakeLength1,*SnakeLength2);//创造食物
			if(Mode == 'C' || Mode == 'c')
				PK_PScore(*SnakeLength1,*SnakeLength2);
			else 
				Double_PScore(*SnakeLength1+*SnakeLength2);//更新分数
		}
	if( Sx2==*Food1&&Sy2==*(Food1+1))//判断是否是食物
		{	 
			(*SnakeLength2)++;//增加长度
			Double_CreateFood(Food1,Snake1,Snake2,*SnakeLength1,*SnakeLength2);//创造食物
			if(Mode == 'C' || Mode == 'c')
				PK_PScore(*SnakeLength1,*SnakeLength2);
			else 
				Double_PScore(*SnakeLength1+*SnakeLength2);//更新分数
		}
		
	if(Sx1==*Food2&&Sy1==*(Food2+1) )//判断是否是食物
		{	
			(*SnakeLength1)++;//增加长度
			Double_CreateFood(Food2,Snake1,Snake2,*SnakeLength1,*SnakeLength2);//创造食物
			if(Mode == 'C' || Mode == 'c')
				PK_PScore(*SnakeLength1,*SnakeLength2);
			else 
				Double_PScore(*SnakeLength1+*SnakeLength2);//更新分数
		}
	if( Sx2==*Food2&&Sy2==*(Food2+1))//判断是否是食物
		{	 
			(*SnakeLength2)++;//增加长度
			Double_CreateFood(Food2,Snake1,Snake2,*SnakeLength1,*SnakeLength2);//创造食物
			if(Mode == 'C' || Mode == 'c')
				PK_PScore(*SnakeLength1,*SnakeLength2);
			else 
				Double_PScore(*SnakeLength1+*SnakeLength2);//更新分数
		}	
		
	if(Sx1==*Food3&&Sy1==*(Food3+1) )//判断是否是食物
		{	
			//printf("\a"); 
			(*SnakeLength1)++;//增加长度
			Double_CreateFood(Food3,Snake1,Snake2,*SnakeLength1,*SnakeLength2);//创造食物
			if(Mode == 'C' || Mode == 'c')
				PK_PScore(*SnakeLength1,*SnakeLength2);
			else 
				Double_PScore(*SnakeLength1+*SnakeLength2);//更新分数
		}
	if( Sx2==*Food3&&Sy2==*(Food3+1))//判断是否是食物
		{	
			//printf("\a"); 
			(*SnakeLength2)++;//增加长度
			Double_CreateFood(Food3,Snake1,Snake2,*SnakeLength1,*SnakeLength2);//创造食物
			if(Mode == 'C' || Mode == 'c')
				PK_PScore(*SnakeLength1,*SnakeLength2);
			else 
				Double_PScore(*SnakeLength1+*SnakeLength2);//更新分数
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
	PBox(11,17); PBox(28,17);// 打印边框 
	SetColor(10);
	Goto(12,17);
	printf("游戏结束！三秒后自动开始继续游戏");	
	Goto(19,15);
	printf("提示");	
	Sleep(3000);//暂停三秒
	system("cls");//清空屏幕
	if(Mode == 'C' || Mode == 'c')
		PK_Rank(*SnakeLength1,*SnakeLength2);//保存分数 
	else 
		Rank(*SnakeLength1+*SnakeLength2);//保存分数 
	*SnakeLength1 = SNAKE_LENGTH;	//重置蛇身长度
	*SnakeLength2 = SNAKE_LENGTH;	//重置蛇身长度
	PInterface(); //初始化界面
	Double_InitSnake(Snake1,*SnakeLength1,1);//初始化蛇身
	Double_InitSnake(Snake2,*SnakeLength2,2);//初始化蛇身	
	Double_CreateFood(Food1,Snake1,Snake2,*SnakeLength1,*SnakeLength2);//产生果实
	Sleep(1000);
	Double_CreateFood(Food2,Snake1,Snake2,*SnakeLength1,*SnakeLength2);//产生果实
	Sleep(1000);
	Double_CreateFood(Food3,Snake1,Snake2,*SnakeLength1,*SnakeLength2);//产生果实
	Dire1 = 77;//重置方向
	Dire2 = 's';//重置方向
	Sleep(1000);
	if(Mode == 'C' || Mode == 'c')
		PK_PScore(*SnakeLength1,*SnakeLength2);
	else 
		Double_PScore(*SnakeLength1+*SnakeLength2);
}
	
int main(){	
	ReGame: Init(); //初始化界面
	ThreadKey = false;
	if(Mode == 'A' || Mode == 'a' ){
		int Snake[400][2];
		int SnakeLength = SNAKE_LENGTH;//初始化蛇身长度
		int Food[2];
		clock_t NowTime; //声明时间变量
		InitSnake(Snake,SnakeLength);//Snake是按地址调用，初始化蛇身
		CreateFood(Food,Snake,SnakeLength);//产生果实
		PScore(SnakeLength);//打印分数
		CreateThread( NULL, 0,ListenKey, 0, 0, 0 );   //使用CreateThread方法开启线程，让开启的线程执行ListenKey方法
		while(true) //主循环
			{
				int Sx = Snake[0][0];//取出蛇头的坐标
				int Sy = Snake[0][1];
				AddSpeed(SnakeLength);//根据蛇身体长度改变速度
				NextStape(&Sx,&Sy);//根据方向，计算下步蛇头位置	
				if(Judge(Sx,Sy,Snake,&SnakeLength,Food)!=0)//判断下步的情况
				{
					MoveSnake(Sx,Sy,Snake,SnakeLength);
				}//根据判断的情况，移动蛇身体，如果不是死亡就移动蛇身
				NowTime=clock();//获取当前时间
				while(clock()-NowTime<WaitTime){}	//计时器，用当前时间减去上面获取的时间与等待时间比较
				if(Stoop){
					Stoop = false;
					goto ReGame;
				}
			}
		getch();
	}else if(Mode == 'B' || Mode == 'b' ){
		int Snake1[400][2];
		int Snake2[400][2];
		int SnakeLength1 = SNAKE_LENGTH;//初始化蛇身长度
		int SnakeLength2 = SNAKE_LENGTH;//初始化蛇身长度
		int Food[2];
		clock_t NowTime; //声明时间变量
		CreateThread( NULL, 0,Double_ListenKey, 0, 0, 0 );   //使用CreateThread方法开启线程，让开启的线程执行ListenKey方法
		Double_InitSnake(Snake1,SnakeLength1,1);//Snake是按地址调用，初始化蛇身
		Sleep(1000);
		Double_InitSnake(Snake2,SnakeLength2,2);//Snake是按地址调用，初始化蛇身
		Double_CreateFood(Food,Snake1,Snake2,SnakeLength1,SnakeLength2);//创造食物
		Double_PScore(SnakeLength1 + SnakeLength2);//打印分数
		while(true) //主循环
			{
				int Sx1 = Snake1[0][0];//取出蛇头的坐标
				int Sy1 = Snake1[0][1];
				
				int Sx2 = Snake2[0][0];//取出蛇头的坐标
				int Sy2 = Snake2[0][1];
				
				Double_AddSpeed(SnakeLength1 + SnakeLength2);//根据蛇身体长度改变速度
				Double_NextStape(&Sx1,&Sy1,&Sx2,&Sy2);//根据方向，计算下步蛇头位置			
				if(Double_Judge(Sx1,Sy1,Sx2,Sy2,Snake1,Snake2,&SnakeLength1,&SnakeLength2,Food))//判断下步的情况
				{
					Double_MoveSnake(Sx1,Sy1,Snake1,SnakeLength1,1);
					Double_MoveSnake(Sx2,Sy2,Snake2,SnakeLength2,2);
				}
				
				NowTime=clock();//获取当前时间
				while(clock()-NowTime<WaitTime){}	//计时器，用当前时间减去上面获取的时间与等待时间比较
				if(Stoop){
					Stoop = false;
					goto ReGame;
				}
			}	
		getch();
	}else if(Mode == 'C' || Mode == 'c'){
		int Snake1[400][2];
		int Snake2[400][2];
		int SnakeLength1 = SNAKE_LENGTH;//初始化蛇身长度
		int SnakeLength2 = SNAKE_LENGTH;//初始化蛇身长度
		int Food1[2], Food2[2], Food3[2];
		clock_t NowTime; //声明时间变量
		clock_t StartTime;
		Double_InitSnake(Snake1,SnakeLength1,1);//Snake是按地址调用，初始化蛇身
		Sleep(1000);
		Double_InitSnake(Snake2,SnakeLength2,2);//Snake是按地址调用，初始化蛇身
		PK_PScore(SnakeLength1 , SnakeLength2);//打印分数
		CreateThread( NULL, 0,PK_ListenKey, 0, 0, 0 );   //使用CreateThread方法开启线程，让开启的线程执行ListenKey方法
		Double_CreateFood(Food1,Snake1,Snake2,SnakeLength1,SnakeLength2);//创造食物
		Sleep(1000);
		Double_CreateFood(Food2,Snake1,Snake2,SnakeLength1,SnakeLength2);//创造食物
		Sleep(1000);
		Double_CreateFood(Food3,Snake1,Snake2,SnakeLength1,SnakeLength2);//创造食物
		Star: StartTime = clock();
		while(true) //主循环
			{
				Sx1 = Snake1[0][0];//取出蛇头的坐标
				Sy1 = Snake1[0][1];
				
				Sx2 = Snake2[0][0];//取出蛇头的坐标
				Sy2 = Snake2[0][1];
						
				Double_AddSpeed(SnakeLength1 + SnakeLength2);//根据蛇身体长度改变速度
				Double_NextStape(&Sx1,&Sy1,&Sx2,&Sy2);//根据方向，计算下步蛇头位置			
				PK_Judge(Sx1,Sy1,Sx2,Sy2,Snake1,Snake2,&SnakeLength1,&SnakeLength2,Food1,Food2,Food3);//判断下步的情况							
				NowTime=clock();//获取当前时间
				while(clock()-NowTime<WaitTime){}	//计时器，用当前时间减去上面获取的时间与等待时间比较
				if(clock() - StartTime > DefaultTime * GameTime ) break;
				if(Stoop){
					Stoop = false;
					goto ReGame;
				}
			}
		PK_GameOver(Snake1,Snake2,&SnakeLength1,&SnakeLength2,Food1,Food2,Food3);//结束游戏
		goto Star;			
	} 
	return 0;
}

