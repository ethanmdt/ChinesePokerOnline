public delegate void GetMsgHandler(string msg);//委托

abstract class SockMain//抽象类
{ 
	//构造析构暂时省略
	private int sendToSock(string msg); //把msg写入socket
	getFromSock(string msg); //事件， 从sock读到完整内容以后,交给AnalyMsg()处理
	private int init(); // 初始化，连接等

	private int disconnect();//登出

	public abstract int AnalyMsg(string msg); // 抽象函数，派生类重写具体报文，并进行相应解析

	Timer()//时间触发器，完成轮询
}

public class CriticFarmOwner : SockMain
{
	//需要定义各种事件，在解析报文成功时触发到游戏类
	private override AnalyMsg(string msg);
	
}