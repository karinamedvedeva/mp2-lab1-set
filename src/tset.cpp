// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp), MaxPower(mp)
{
    if (mp <= 0)
    {
        throw mp;
    }
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
    BitField = bf;
}

TSet::operator TBitField()
{
    TBitField tmp(BitField);
    return tmp;
}


int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (Elem < 0 || Elem >= MaxPower)
    {
        throw Elem;
    }
    if (BitField.GetBit(Elem))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower)
    {
        throw Elem;
    }
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower)
    {
        throw Elem;
    }
    BitField.ClrBit(Elem);
}


// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (MaxPower == s.MaxPower)
    {
        if (BitField == s.BitField)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if (MaxPower == s.MaxPower)
    {
        if (BitField == s.BitField)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 1;
    }
}

TSet TSet::operator+(const TSet& s) // объединение
{
    TSet tmp(s.MaxPower);
    tmp.BitField = BitField | s.BitField;
    return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet res(*this);
    res.InsElem(Elem);
    return res;

}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem < 0 || Elem >= MaxPower)
    {
        throw Elem;
    }
    TSet res(*this);
    res.DelElem(Elem);
    return res;

}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet tmp(s.MaxPower);
    tmp.BitField =BitField & s.BitField;
    return tmp;
}

TSet TSet::operator~(void) // дополнение
{
    BitField = ~BitField;
    return *this;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    int x;
    istr>> x;
    while (x>=0)
    {
        s.InsElem(x);
        istr >> x;
    }
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    for (int i = 0; i < s.MaxPower; i++)
    {
        if (s.IsMember(i))
        {
            ostr << i << " ";
        }
    }
    return ostr;
}
