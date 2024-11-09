// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"
TSet::TSet(int mp) : BitField(-1), MaxPower(mp)
{
    BitField = TBitField(MaxPower);
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(-1)
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(-1)
{
    MaxPower = bf.GetLength();
    BitField = bf;
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if ((Elem >= 0) && (Elem < MaxPower))
        return BitField.GetBit(Elem);
    return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if ((Elem >= 0) && (Elem < MaxPower))
        BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if ((Elem >= 0) && (Elem < MaxPower) && (this->IsMember(Elem)))
        BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (this != &s) {
        MaxPower = s.MaxPower;
        BitField = s.BitField;
    }
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if(MaxPower == s.MaxPower)
        if (s.BitField == BitField)
            return 1;
    return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet A(BitField | s.BitField);
    return A;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TBitField bf = BitField;
    bf.SetBit(Elem);
    TSet A(bf);
    return A;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TBitField bf = BitField;
    bf.ClrBit(Elem);
    TSet A(bf);
    return A;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet A(BitField & s.BitField);

    return A;
}

TSet TSet::operator~(void) // дополнение
{
    TSet A(~BitField);
    return A;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    istr >> s.BitField;
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    ostr << s.BitField;
    return ostr;
}