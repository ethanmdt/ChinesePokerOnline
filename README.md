# ChinesePokerOnline
Network course teamwork
大致分为Client端和Server端
将 斗地主游戏部分 和 牌桌管理部分 另存文件
目前考虑将 xml交互 （即用户认证和游戏记录部分） 写入Server端
出于安全考虑，Client端只能获取牌局部分信息，需要使用和Server端不同的子类

目前规定还不稳定，数据报文格式暂未定义
预计5月1日前完成稳定规范

Server和Client文件夹中各自socket部分和游戏部分分离，并且共用 游戏分桌(GameTable)
ChinesePoker是两端游戏的基类，两端采用不同类的原因是Client端不应该获得其他玩家的手牌等数据
