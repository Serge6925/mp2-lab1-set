// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле
#include <iostream>
#include <ostream>
#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (0 <= len)
    {
        BitLen = len;
        pMem = new TELEM[BitLen];
        for (int i = 0; i < BitLen; i++)
        {
            pMem[i] = 0;
        }
    }
    else if(len == -1)
        pMem = nullptr;
    else
        throw exception();
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    pMem = new TELEM[BitLen];
    for (int i = 0; i < BitLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
    BitLen = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return (n - 1);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    TBitField A(BitLen);
    A.SetBit(n);
    return *A.pMem;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((0 <= n) && (n < BitLen))
        pMem[n] = 1;
    else
        throw exception();
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((0 <= n) && (n < BitLen))
        pMem[n] = 0;
    else
        throw exception();
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if ((0 <= n) && (n < BitLen))
        return pMem[n];
    else
        throw exception();
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (&bf == this) return *this;
    delete[] pMem;
    BitLen = bf.BitLen;
    pMem = new TELEM[BitLen];
    for (int i = 0; i < BitLen; i++)
        pMem[i] = bf.pMem[i];
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return 0;
    else
        for (int i = 0; i < BitLen; i++)
            if (pMem[i] != bf.pMem[i])
                return 0;
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (*this == bf)
        return 0;
    return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    TBitField A(0);
    if (BitLen > bf.BitLen) A = *this;
    else A = bf;
    for (int i = 0; (i < BitLen) && (i < bf.BitLen); i++)
        A.pMem[i] = (pMem[i] + bf.pMem[i] != 0);
    return A;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField A(0);
    if (BitLen > bf.BitLen) A = *this;
    else A = bf;
    for (int i = 0; (i < BitLen) && (i < bf.BitLen); i++)
        A.pMem[i] = (pMem[i] + bf.pMem[i] > 1);
    return A;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField A(*this);
    for (int i = 0; i < BitLen; i++)
        A.pMem[i] = (pMem[i] + 1) % 2;
    return A;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    for (int i = 0; i < bf.BitLen; i++)
        istr >> bf.pMem[i];
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
        ostr << bf.pMem[i] << " ";
    ostr << "\n";
    return ostr;
}
