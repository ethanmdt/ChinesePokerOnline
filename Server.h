class User {
    socket sock;
    char *username;
};
class DataPackage { //�����������ݰ�
};
class Server { //������xml��socket�ĵײ㽻��
    char SendBuf[MAX_QUEUE][MAX_BUFFER] ; //�����ͻ���
    void Start(xmlFile xml); //����XML��ַ
    void Login(User usr, char *username);
    GameRecord GetGameRecord(User usr);
};
