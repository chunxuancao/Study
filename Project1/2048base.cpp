#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <iomanip>  // ��Ҫ���� <iomanip> ��ʹ�� setw
using namespace std;

#include"2048base.h"

/*����ת��*/
void transform(int* p, int len)
{
    for (int i = 0; i < len; i++)
        for (int j = 0; j < len; j++)
            if (i > j) //ת��ʱֻ��Ҫ���¶Խǲ��ּ���
            {
                int tmp = *(p + i * len + j);
                *(p + i * len + j) = *(p + j * len + i);
                *(p + j * len + i) = tmp;
            }
}

/*ɾ��ĳһ�������е���Ԫ�ء�������Ԫ�ظ���rev��һ������ȥ�ѵ�*/
void delZeros(int* p, int len, bool rev)
{
    int k = rev ? (len - 1) : 0;
    int step = rev ? -1 : 1;
    for (int j = rev ? (len - 1) : 0; j < len && j >= 0;)
    {
        if (*(p + j) != 0)
        {
            *(p + k) = *(p + j);
            k += step;
        }
        j += step;
    }
    for (int j = k; j < len && j >= 0;)
    {
        *(p + j) = 0;
        j += step;
    }
}

/*�ϲ�һ�����ݵ���ͬԪ��,���ص÷�*/
int combine(int* p, int len, bool rev)
{
    int score = 0;				 // �÷�
    int k = rev ? (len - 1) : 0; // ��Ҫ��˳�����
    int step = rev ? -1 : 1;	 // ���������Ƿ����й�
    for (int i = rev ? (len - 1) : 0; i < len && i >= 0; i += step)
    {
        if ((*(p + i) != *(p + i + step)) || (i == (rev ? 0 : (len - 1))))
        {
            *(p + k) = *(p + i);
            k += step;
        }
        else
        {
            *(p + k) = *(p + i) * 2;
            i += step; // i�����ظ����ֵ�λ��
            k += step;
            score += *(p + i) * 2;
        }
    }
    for (int j = k; j < len && j >= 0; j += step)
        *(p + j) = 0; // kû�����꣬����
    return score;
}

/*�����ά����*/
void out(int* p, int len)
{
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
            cout << setw(6) << *(p + i * len + j); // ���ÿ������ʱ�����Ϊ6
        cout << endl;
    }
    cout << endl;
}

/*�ж��ƶ�ǰ�������Ƿ����ı�*/
bool ifchange(int* p, int* q, int len)
{
    bool flag = false;
    for (int i = 0; i < len; i++)
        for (int j = 0; j < len; j++)
            if (*(p + i * len + j) != *(q + i * len + j)) flag = true;
    return flag;
}

/*��������жѵ���pΪ��Ҫ�ѵ���һ��/�����ݣ�lenΪ�߳���rev�ж��Ƿ���[��������], transform�ж��Ƿ���Ҫת��[��/��]��
 *Ĭ�ϵľ���˳���д��ϵ��£��д������ҡ�����ʱ������ÿһ�У��ѵ�ÿһ��
 *��������ѵ�ǰ���Ƿ����仯
 */
bool pileRows(int* p, int len, bool rev, bool trans, int* score)
{
    int* q = new int[len * len];
    for (int i = 0; i < len; i++)
        for (int j = 0; j < len; j++)
            *(q + i * len + j) = *(p + i * len + j); //�ȸ���һ�飬�����ж������Ƿ����ı�
    if (trans) transform(p, len); // ת��
    // out(p, len);
    for (int i = 0; i < len; i++) // ����ÿһ��
    {
        int* q = p + i * len;     // ����һ�����ݶ�Ӧ��ָ��
        // for(int i=0;i<len;i++) cout << *(q+i) << " ";cout << endl;
        delZeros(q, len, rev);    // �Ȱ���һ���е���Ԫ����һ������ѵ�
        // for(int i=0;i<len;i++) cout << *(q+i) << " ";cout << endl;
        *score += combine(q, len, rev); //�ϲ���ͬԪ�أ�����õ÷�
        // for(int i=0;i<len;i++) cout << *(q+i) << " ";cout << endl;
    }
    // out(p, len);
    if (trans) transform(p, len); // �������ˣ���ת�û���
    return ifchange(p, q, len);   // ���������Ƿ����仯�ı�־
}

/*��������*/
void AddNum(int* p, int len)
{
    int x, y;
    do
    {
        x = rand() % 4;
        y = rand() % 4;
    } while (*(p + x * len + y) != 0); // �ҵ�����Ϊ���λ��
    if (rand() % 9 >= 5)  // 4���ֵĸ���Ϊ4/9
        *(p + x * len + y) = 4;
    else
        *(p + x * len + y) = 2;
}

/*����2048*/
void run(int* p, int len, int* score)
{
    char key = _getch();
    switch (key)
    {
    case 72: //"up"
    case 'w':
    case 'W':
        if (pileRows(p, len, false, true, score)) AddNum(p, len); //ֻ�����鷢���ı������һ�������
        //out(p, len);
        break;
    case 80: //"down"
    case 's':
    case 'S':
        if (pileRows(p, len, true, true, score)) AddNum(p, len);
        //out(p, len);
        break;
    case 75: //"left"
    case 'a':
    case 'A':
        if (pileRows(p, len, false, false, score)) AddNum(p, len);
        //out(p, len);
        break;
    case 77: //"right"
    case 'd':
    case 'D':
        if (pileRows(p, len, true, false, score)) AddNum(p, len);
        // out(p, len);
        break;
    default:
        break;
    }
}


