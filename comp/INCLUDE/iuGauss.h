//---------------------------------------------------------------------------
#ifndef GaussH
#define GaussH
//---------------------------------------------------------------------------
#include <fastmath.h>
/*
void dd()
{
asm{nop}
}
*/
template <class T> void __fastcall Gauss(T **Matrix,int range)
{
static int col,row,step; // строка и столбец матрицы
static T k;
    // исключаем неизвестные
  for(step=0;step<range;step++)
    for(row=step;row<(range-1);row++)
    {
      k=-Matrix[step][row+1]/Matrix[step][step];
      for(col=step;col<=range;col++)
        Matrix[col][row+1]+=k*Matrix[col][step];
    }
  // вычесляем корни и помещаем их в крайний правый столбец матрицы
  for(row=range-1;row>=0;row--)
  {
    k=0.0;
    for(col=range-1;col>=row+1;col--)
      k+=Matrix[col][row]*Matrix[range][col];
    Matrix[range][row]=(Matrix[range][row]-k)/Matrix[row][row];
  }
}
//---------------------------------------------------------------------------
#endif
