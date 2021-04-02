#pragma once

#include <assert.h>
#include <libutils/Move.h>
#include <libutils/New.h>

template <typename T>
class Optional
{
private:
    bool _present = false;

    union
    {
        T _storage;
    };

public:
    bool present() const
    {
        return _present;
    }

    T &value()
    {
        assert(present());
        return _storage;
    }

    const T &value() const
    {
        assert(present());
        return _storage;
    }

    T value_or(const T &defaut_value) const
    {
        if (present())
        {
            return value();
        }
        else
        {
            return defaut_value;
        }
    }

    Optional() {}

    Optional(const T &value)
    {
        _present = true;
        new (&_storage) T(value);
    }

    Optional(T &&value)
    {
        _present = true;
        new (&_storage) T(move(value));
    }

    Optional(const Optional &other)
    {
        if (other.present())
        {
            _present = true;
            new (&_storage) T(other.value());
        }
    }

    Optional(Optional &&other)
    {
        if (other.present())
        {
            new (&_storage) T(other.value());
            _present = true;
        }
    }

    Optional &operator=(const Optional &other)
    {
        if (this != &other)
        {
            clear();
            _present = other._present;
            if (other._present)
            {
                new (&_storage) T(other.value());
            }
        }

        return *this;
    }

    Optional &operator=(Optional &&other)
    {
        if (this != &other)
        {
            clear();
            _present = other._present;
            if (other._present)
            {
                new (&_storage) T(other.value());
            }
        }

        return *this;
    }

    bool operator==(const T &other) const
    {
        if (!present())
        {
            return false;
        }

        return value() == other;
    }

    ~Optional()
    {
        clear();
    }

    void clear()
    {
        if (_present)
        {
            value().~T();
            _present = false;
        }
    }
};