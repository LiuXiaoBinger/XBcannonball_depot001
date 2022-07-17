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
//	int   m_direct;   //����
//
//
//public:
//	CMario(){
//		// ��������
//		::initgraph(600,600);
//		//�趨���ڱ�����ɫ
//		::setbkcolor(RGB(255,255,255));
//		::cleardevice();    //����
//
//
//		//��ʼ����Ա���ԣ���ǰ���͵ĳ�ʼֵ
//		m_x = 0;
//		m_y = 0;
//		m_direct = 0; 
//	}
//	~CMario(){
//		::closegraph();  //�رմ���
//	}
//public:
//	//�߼������ϵĳ�ʼ���������ҵ���߼��й�
//	void OnInit(){
//		//IMAGE �� �����ϵ�ͼƬ���а󶨹���
//		// ./ ��ǰ·��
//		::loadimage(&m_imgUp,"./res/mali-up.bmp");
//		::loadimage(&m_imgDown,"./res/mali-down.bmp");
//		::loadimage(&m_imgLeft,"./res/mali-left.bmp");
//		::loadimage(&m_imgRight,"./res/mali-right.bmp");
//		
//	
//		m_x = 250;
//		m_y = 250;
//	
//		m_direct = DEF_RIGHT;   //��ʼ��������
//	}
//
//	//�����ػ�
//	void OnPaint(){
//		//�����ػ�
//		::BeginBatchDraw();  //��ʼ�����ػ�
//
//		::cleardevice(); 
//		//���ݷ�����ʾ��ͬ��ͼ
//		ShowMario();
//
//
//		::EndBatchDraw();  //����������ͼ
//	}
//
//	void OnRun(){
//		OnPaint();
//
//		while(1){
//			//�жϷ�����Ƿ񱻰��£�������£���ȡ����İ���
//			if(_kbhit()){
//				int key = _getch();   //��ȡ����İ���
//
//				//if �����ESC �������˳���break ѭ��
//				if(key == ESC){
//					break;
//				}
//
//
//				//���������ƶ��ķ�������key���������ƶ�������
//				MoveMario(key,5);
//
//				//�����ػ�
//				OnPaint();
//			}
//			Sleep(10);
//		}
//	}
//
//	//��ʾ
//	void ShowMario(){
//
//		//���ݷ����䲻ͬ��ͼƬ������
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
//	//�ƶ�
//	// ���� ������ ÿ���ƶ��ľ��루���ص㣩
//	void MoveMario(int direct,int step){
//		switch (direct)
//		{
//		case DEF_UP:
//			{
//				if(  m_y-step  >=0){   //�ж��Ƿ����
//					m_y-=step;
//				}else{  //�жϳ����ˣ�������С���� 0
//					m_y=0;
//				}
//				m_direct = DEF_UP;
//			}
//			break;
//		case DEF_DOWN:
//			{
//				if(  m_y+step  <=540){   //�ж��Ƿ����
//					m_y+=step;
//				}else{  //�жϳ����ˣ����������� 540
//					m_y=540;
//				}
//				m_direct = DEF_DOWN;
//			}
//			break;
//		case DEF_LEFT:
//			{
//				if(  m_x-step  >=0){   //�ж��Ƿ����
//					m_x-=step;
//				}else{  //�жϳ����ˣ�������С���� 0
//					m_x=0;
//				}
//				m_direct = DEF_LEFT;
//			}
//			break;
//		case DEF_RIGHT:
//			{
//				if(  m_x+step  <=540){   //�ж��Ƿ����
//					m_x+=step;
//				}else{  //�жϳ����ˣ����������� 540
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
//	mario.OnInit();  //��ʼ�������
//	mario.OnRun();
//
//
//	return 0;
//}
//
