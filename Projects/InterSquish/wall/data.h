
#ifndef 
#define DATA_H
struct  TCriptedData1
{
  double rcost;     //реальная цена регистрации в рублях
  double rate;      //курс на момент регистрации
  char sign1[8];
  char sign2[8];
  char sign3[8];
  char sign4[8];
};
//-------------------------------------------------------------------
struct  TCriptedData2
{
  char sign2[8];
  double rate;      //курс на момент регистрации
  char sign1[8];
  double rcost;     //реальная цена регистрации в рублях
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
  char         ver[8];      //Версия ключа
  char          garbage1[16];
  TCriptedData1 data1; //Первый секретный блок
  char          dcost;       //цена регистрации в долларах
  char          garbage2[7];
  TCriptedData2 data2; //Второй секретный блок
  char          Family[16];
  char          garbage3[24];
  TCriptedData3 data3;
  char          garbage[32];
  char          mac1[8];
  char          mac2[8];
};

#endif