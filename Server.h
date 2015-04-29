class User {
    socket sock;
    char *username;
};
class DataPackage { //定长部分数据包
};
class Server { //进行与xml和socket的底层交互
    char SendBuf[MAX_QUEUE][MAX_BUFFER] ; //待发送缓冲
    void Start(xmlFile xml); //输入XML地址
    void Login(User usr, char *username);
    GameRecord GetGameRecord(User usr);
};
