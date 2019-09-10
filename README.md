# 贪吃蛇
#### 作者： 刘陈林   
#### 时间：2019暑期
----

### 答辩说明：
    答辩全是有c语言书写，其中涉及winds的api操作，多线程，随机函数等等。功能包括有：
* 1.登陆注册（采用文件保存的方式实现的数据库）
* 2.排行榜（对文件数据的操作）
* 3.难度设置以及计时系统（调节蛇的移动速度，计时游戏）
* 4.游戏中返回主菜单（游戏中按特定的键位可返回登陆页面）
* 5.三种游戏的模式
    - 单蛇模式（普通贪吃蛇模式）
    - 双蛇模式（控制两条蛇）
    - 对战模式（双人对战，果实数量增多，可吃对方蛇，计时系统）

---

### 答辩内容

* 登陆注册
```c
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
``` 

* 排行榜

```c
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
```

* 难度设置以及计时系统
```c
    if(clock() - StartTime > DefaultTime * GameTime ) break;//DefaultTime一分钟时长，GameTime是用户规定时长，如果现在时间减去开始的时间超过了规定时间，跳出主循环。


    //Speed是一开始用户设定的速度（难度）
	if(WaitTime == 0)//当WaitTime被改变时，进行还原
		{
			int NewTime;
			NewTime = Speed - (SnakeLength-SNAKE_LENGTH)*10;//获取新的等待时间
			if(NewTime >= 10)//如果新的等待时间>=10
				WaitTime = NewTime;//将新的等待时间赋值给WaitTime
			else//新的等待时间<=10
				WaitTime = 10;			
		}

```