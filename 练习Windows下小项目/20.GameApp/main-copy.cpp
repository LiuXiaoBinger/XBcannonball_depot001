//#include<easyx.h>
//#include<conio.h>
//
//
//#define ESC   27
//#define DEF_UP   72
//#define DEF_DOWN   80
//#define DEF_LEFT   75
//#define DEF_RIGHT   77
//
//
//class CMario{
//public:
//	IMAGE m_imgUp;
//	IMAGE m_imgDown;
//	IMAGE m_imgLeft;
//	IMAGE m_imgRight;
//
//	int   m_x;
//	int   m_y;
//
//	int   m_direct;   //方向
//
//
//public:
//	CMario(){
//		// 创建窗口
//		::initgraph(600,600);
//		//设定窗口背景颜色
//		::setbkcolor(RGB(255,255,255));
//		::cleardevice();    //清屏
//
//
//		//初始化成员属性，当前类型的初始值
//		m_x = 0;
//		m_y = 0;
//		m_direct = 0; 
//	}
//	~CMario(){
//		::closegraph();  //关闭窗口
//	}
//public:
//	//逻辑意义上的初始化，与程序业务逻辑有关
//	void OnInit(){
//		//IMAGE 和 磁盘上的图片进行绑定关联
//		// ./ 当前路径
//		::loadimage(&m_imgUp,"./res/mali-up.bmp");
//		::loadimage(&m_imgDown,"./res/mali-down.bmp");
//		::loadimage(&m_imgLeft,"./res/mali-left.bmp");
//		::loadimage(&m_imgRight,"./res/mali-right.bmp");
//		
//	
//		m_x = 250;
//		m_y = 250;
//	
//		m_direct = DEF_RIGHT;   //初始方向向右
//	}
//
//	//窗口重绘
//	void OnPaint(){
//		//批量重绘
//		::BeginBatchDraw();  //开始批量重绘
//
//		::cleardevice(); 
//		//根据方向显示不同的图
//		ShowMario();
//
//
//		::EndBatchDraw();  //结束批量绘图
//	}
//
//	void OnRun(){
//		OnPaint();
//
//		while(1){
//			//判断方向键是否被按下，如果按下，获取具体的按键
//			if(_kbhit()){
//				int key = _getch();   //获取具体的按键
//
//				//if 如果是ESC ，程序退出，break 循环
//				if(key == ESC){
//					break;
//				}
//
//
//				//调用人物移动的方法，将key串到人物移动方法中
//				MoveMario(key,5);
//
//				//调用重绘
//				OnPaint();
//			}
//			Sleep(10);
//		}
//	}
//
//	//显示
//	void ShowMario(){
//
//		//根据方向传输不同的图片到窗口
//		switch (m_direct)
//		{
//		case DEF_UP:
//			{
//				::putimage(m_x,m_y,&m_imgUp);
//			}
//			break;
//		case DEF_DOWN:
//			{
//				::putimage(m_x,m_y,&m_imgDown);
//			}
//			break;
//		case DEF_LEFT:
//			{
//				::putimage(m_x,m_y,&m_imgLeft);
//			}
//			break;
//		case DEF_RIGHT:
//			{
//				::putimage(m_x,m_y,&m_imgRight);
//			}
//			break;
//		}
//	}
//
//	//移动
//	// 方向 ，步长 每次移动的距离（像素点）
//	void MoveMario(int direct,int step){
//		switch (direct)
//		{
//		case DEF_UP:
//			{
//				if(  m_y-step  >=0){   //判断是否出界
//					m_y-=step;
//				}else{  //判断出界了，但是最小界限 0
//					m_y=0;
//				}
//				m_direct = DEF_UP;
//			}
//			break;
//		case DEF_DOWN:
//			{
//				if(  m_y+step  <=540){   //判断是否出界
//					m_y+=step;
//				}else{  //判断出界了，但是最大界限 540
//					m_y=540;
//				}
//				m_direct = DEF_DOWN;
//			}
//			break;
//		case DEF_LEFT:
//			{
//				if(  m_x-step  >=0){   //判断是否出界
//					m_x-=step;
//				}else{  //判断出界了，但是最小界限 0
//					m_x=0;
//				}
//				m_direct = DEF_LEFT;
//			}
//			break;
//		case DEF_RIGHT:
//			{
//				if(  m_x+step  <=540){   //判断是否出界
//					m_x+=step;
//				}else{  //判断出界了，但是最大界限 540
//					m_x=540;
//				}
//				m_direct = DEF_RIGHT;
//			}
//			break;
//		}
//
//	
//	}
//};
//
//
//
//int main(){
//
//	CMario mario;
//	mario.OnInit();  //初始化马里奥
//	mario.OnRun();
//
//
//	return 0;
//}
//
