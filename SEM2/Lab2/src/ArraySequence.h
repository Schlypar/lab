#pragma once

#include "ADT.h"


template <typename T>
class ArraySequence : public Sequence<T>
{
private:
    Array<T> container;

    void Resize(Size newCapacity)
    {
        container.Realloc(newCapacity);
    }

public:

    class Iterator : IIterator<T>
    {
        T* current;
    public:
        Iterator() {}

        Iterator(T* data)
            : current(data) {}
        
        Iterator(IIterator<T>* other)
            : current(other->_GetPointer()) {}

        Iterator& operator+ (int n) 
        {
            while (n > 0)
            {
                this->Next();
                n--;
            }

            return *this;
        }

        Iterator& operator- (int n) 
        {
            while (n > 0)
            {
                this->Prev();
                n--;
            }

            return *this;
        }

        // ~Iterator()
        // {
        //     delete (IIterator<T>*)this;
        // }

        Iterator operator++ () { this->_Next() ; return *this; }

        Iterator operator-- () { this->_Prev() ; return *this; }

        bool operator!= (Iterator& other) const { return this->current != other.current; }

		bool operator== (Iterator& other) const { return this->current == other.current; }

        T& operator* () { return *(this->current); }

        IIterator<T>* _Next() override
        {
            current++;
            return this;
        }

        IIterator<T>* _Prev() override
        {
            current--;
            return this;
        }

        T& _GetCurrent() override
        {
            return *(this->current);
        }

        T* _GetPointer() override
        {
            return this->current;
        }

        bool _isEquals(IIterator<T>* other) override
        {
            return this->current == ((Iterator*)other)->current;
        }
    };

    IIterator<T>* _Begin() override { return (IIterator<T>*) new (Iterator)(GetFirstPointer()); }
    IIterator<T>* _End() override { return (IIterator<T>*) new (Iterator)(GetEndPointer()); }

    Iterator begin() { return (Iterator)(this->_Begin()); }
    Iterator end() { return (Iterator)(this->_End()); }

    ArraySequence()
        : container() {}

    ArraySequence(T* data, Size count)
        : container(data, count) {}

    ArraySequence(const Sequence<T>& other)
        : container(other) {}

    ArraySequence(Sequence<T>&& other)
        : container(other) {}
    
    ~ArraySequence() {}

    T& GetFirst() const  override
    {
        if (isEmpty())
        {
            Logger::Trace("At Get() at ArraySequence.h");
            logException(EXCEPTION_INDEX_OUT_OF_RANGE);
            exit(EXIT_FAILURE);
        }

        return container.Get(0);
    }

    T& GetLast() const override
    {
        if (isEmpty())
        {
            Logger::Trace("At Get() at ArraySequence.h");
            logException(EXCEPTION_INDEX_OUT_OF_RANGE);
            exit(EXIT_FAILURE);
        }
        
        return container.Get(GetLength() - 1);
    }

    T& Get(const Index index) const override
    {
        if (isEmpty() || index > GetLength())
        {
            Logger::Trace("At Get() at ArraySequence.h");
            logException(EXCEPTION_INDEX_OUT_OF_RANGE);
            exit(EXIT_FAILURE);
        }

        return container.Get(index);
    }

    void Append(const T& data) override
    {
        if (container.GetCapacity() - container.GetLength() < 1)
        {
            (container.GetCapacity() == 0) ? Resize(2) : Resize(container.GetLength() * CAPACITY_TO_REAL_SIZE);
        }

        container[GetLength()] = data;
        container.SetSize(GetLength() + 1);
    }

    void Append(T&& data) override
    {
        if (container.GetCapacity() - container.GetLength() < 1)
        {
            Resize(container.GetLength() * CAPACITY_TO_REAL_SIZE);
        }

        container[GetLength()] = data;
        container.SetSize(GetLength() + 1);
    }

    void Prepend(const T& data) override
    {
        if (container.GetCapacity() - container.GetLength() < 1)
        {
            Resize(container.GetLength() * CAPACITY_TO_REAL_SIZE);
        }

        for (Index i = GetLength(); i > 0; i--)
        {
            container[i] = container[i - 1];
        }

        container[0] = data;
        container.SetSize(GetLength() + 1);
    }

    void Prepend(T&& data) override
    {
        if (container.GetCapacity() - container.GetLength() < 1)
        {
            Resize(container.GetLength() * CAPACITY_TO_REAL_SIZE);
        }

        for (Index i = GetLength(); i > 0; i--)
        {
            container[i] = container[i - 1];
        }

        container[0] = data;
        container.SetSize(GetLength() + 1);
    }

    void InsertAt(const Index index, const T& data) override
    {
        if (container.GetCapacity() - container.GetLength() < 1)
        {
            Resize(container.GetLength() * CAPACITY_TO_REAL_SIZE);
        }

        for (Index i = GetLength(); i > index; i--)
        {
            container[i] = container[i - 1];
        }

        container[index] = data;
        container.SetSize(GetLength() + 1);
    }

    Size GetLength() const noexcept override { return container.GetLength(); }

    bool isEmpty() const noexcept override { return GetLength() == 0; }

    
    T* GetFirstPointer() override
    {
        return &(GetFirst());
    }

    T* GetEndPointer() override
    {
        return (&(GetLast()) + 1);
    }

    Sequence<T>* Copy() override
    {
        return (Sequence<T>*) new ArraySequence<T>(*this);
    }

    T& operator[] (const Index index) { return container[index]; }
};