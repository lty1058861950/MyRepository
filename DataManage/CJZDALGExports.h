//**********************************************************************************************
//**************************将被提供动态库的函数接口函数****************************************
//**********************************************************************************************
//参数含义：
//unsigned char *input        —— 输入的明文或者密文字符串指针，！！！数据长度必须为16字节的整数倍；
//unsigned long inputlength   —— 输入的数据长度，单位：字节。！！！要求必须为16字节的整数倍；
//unsigned char *output       —— 接收输出数据结果的字符串指针；
//unsigned char * rawkey      —— 原始密钥，128位（16字节）
//unsigned char *IV           —— 初始向量；
//bool EncOrDec               —— 工作模式标识。为ENCRYPT时，执行加密；为DECRYPT时，执行解密。
//注意：为了提高加解密速度，每次调用算法尽可能处理较多的数据，而减少算法的调用次数。
bool DoEncrypOrDecry(unsigned char *input,  unsigned long inputlength, unsigned char *output, unsigned char * rawkey, unsigned char *IV, bool EncOrDec);



