#include <bits/stdc++.h>
using namespace std;

class String
{
private:
    char* data = nullptr;

public:

    // Default constructor
    String() = default;

    // const char* constructor
    String(const char* str)
    {
        if (str)
        {
            int len = strlen(str);

            data = new char[len + 1];

            strcpy(data, str);
        }
    }

    // Copy constructor
    String(const String& other)
    {
        if (other.data)
        {
            int len = strlen(other.data);

            data = new char[len + 1];

            strcpy(data, other.data);
        }
    }

    // Copy assignment
    String& operator=(const String& other)
    {
        if (this != &other)
        {
            char* temp = nullptr;

            if (other.data)
            {
                int len = strlen(other.data);

                temp = new char[len + 1];

                strcpy(temp, other.data);
            }

            delete[] data;

            data = temp;
        }

        return *this;
    }

    // Move constructor
    String(String&& other) noexcept
    {
        data = other.data;

        other.data = nullptr;
    }

    // Move assignment
    String& operator=(String&& other) noexcept
    {
        if (this != &other)
        {
            delete[] data;

            data = other.data;

            other.data = nullptr;
        }

        return *this;
    }

    // Destructor
    ~String()
    {
        delete[] data;
    }

    int length() const
    {
        return data ? strlen(data) : 0;
    }

    const char* c_str() const
    {
        return data ? data : "";
    }

    // operator+
    String operator+(const String& other) const
    {
        int len1 = strlen(data);
        int len2 = strlen(other.data);

        char* temp = new char[len1 + len2 + 1];

        strcpy(temp, data);
        strcat(temp, other.data);

        String result(temp);

        delete[] temp;

        return result;
    }

    // operator+=
    String& operator+=(const String& other)
    {
        int len1 = strlen(data);
        int len2 = strlen(other.data);

        char* temp = new char[len1 + len2 + 1];

        strcpy(temp, data);
        strcat(temp, other.data);

        delete[] data;

        data = temp;

        return *this;
    }
};

int main()
{
    String s1("Hello");
    String s2(" World");

    cout << s1.c_str() << endl;
    cout << s1.length() << endl;

    String s3 = s1;              // Copy constructor

    String s4 = std::move(s1);   // Move constructor

    String s5("ABC");
    s5 = s2;                     // Copy assignment

    String s6("XYZ");
    s6 = std::move(s5);          // Move assignment

    String s7 = s2 + s3;         // operator+

    s7 += s2;                    // operator+=

    cout << s7.c_str() << endl;
}
