
#ifndef 
#define DATA_H
struct  TCriptedData1
{
  double rcost;     //ॠ�쭠� 業� ॣ����樨 � �㡫��
  double rate;      //���� �� ������ ॣ����樨
  char sign1[8];
  char sign2[8];
  char sign3[8];
  char sign4[8];
};
//-------------------------------------------------------------------
struct  TCriptedData2
{
  char sign2[8];
  double rate;      //���� �� ������ ॣ����樨
  char sign1[8];
  double rcost;     //ॠ�쭠� 業� ॣ����樨 � �㡫��
  char sign3[8];
};
//-------------------------------------------------------------------
struct  TCriptedData3
{
  char sign3[8];
  char sign2[8];
  char sign4[8];
};
//-------------------------------------------------------------------

//-------------------------------------------------------------------
struct TKeyData
{
  char         ver[8];      //����� ����
  char          garbage1[16];
  TCriptedData1 data1; //���� ᥪ��� ����
  char          dcost;       //業� ॣ����樨 � �������
  char          garbage2[7];
  TCriptedData2 data2; //��ன ᥪ��� ����
  char          Family[16];
  char          garbage3[24];
  TCriptedData3 data3;
  char          garbage[32];
  char          mac1[8];
  char          mac2[8];
};

#endif