#include "serialize.h"

QByteArray doubleToData(double num)
{
    union
    {
        char tab[8];
        double n;
    } castUnion;
    //char n[8];
    //*((double*) n) = num;

    castUnion.n=num;
    return QByteArray(castUnion.tab,8);
}

QByteArray floatToData(float num)
{
    union
    {
        char tab[4];
        float n;
    } castUnion;

    castUnion.n=num;
    return QByteArray(castUnion.tab,4);
}

float dataToFloat(QByteArray data)
{
    union
    {
        char tab[4];
        float n;
    } castUnion;

    castUnion.tab[0]=data.data()[0];
    castUnion.tab[1]=data.data()[1];
    castUnion.tab[2]=data.data()[2];
    castUnion.tab[3]=data.data()[3];
    return castUnion.n;
}

// Converts a string into PNet string data
QByteArray stringToData(QString str)
{
    QByteArray data(4,0);
    // Write the size in a Uint of variable lenght (8-32 bits)
    int i=0;
    uint num1 = (uint)str.toUtf8().size();
    while (num1 >= 0x80)
    {
        data[i] = (unsigned char)(num1 | 0x80); i++;
        num1 = num1 >> 7;
    }
    data[i]=num1;
    data.resize(i+1);
    data+=str.toUtf8();
    return data;
}

QString dataToString(QByteArray data)
{
    // Variable UInt32
    unsigned char num3;
    int num = 0;
    int num2 = 0;
    int i=0;
    do
    {
        num3 = data[i]; i++;
        num |= (num3 & 0x7f) << num2;
        num2 += 7;
    } while ((num3 & 0x80) != 0);
    unsigned int strlen = (uint) num;

    if (!strlen)
        return QString();

    data = data.right(data.size()-i); // Remove the strlen
    data.truncate(strlen);
    return QString(data);
}

QByteArray vectorToData(UVector vec)
{
    QByteArray data;
    data += floatToData(vec.x);
    data += floatToData(vec.y);
    data += floatToData(vec.z);
    return data;
}

UVector dataToVector(QByteArray data)
{
    UVector vec;
    vec.x = dataToFloat(data);
    vec.y = dataToFloat(data.mid(4));
    vec.z = dataToFloat(data.mid(8));
    return vec;
}

QByteArray quaternionToData(UQuaternion quat)
{
    QByteArray data;
    data += floatToData(quat.x);
    data += floatToData(quat.y);
    data += floatToData(quat.z);
    data += floatToData(quat.w);
    return data;
}

float dataToRangedSingle(float min, float max, int numberOfBits, QByteArray data)
{
    uint endvalue=0;
    uint value=0;
    if (numberOfBits <= 8)
    {
        endvalue = (uchar)data[0];
        goto done;
    }
    value = (uchar)data[0];
    numberOfBits -= 8;
    if (numberOfBits <= 8)
    {
        endvalue = (value | ((uint) ((uchar)data[1]) << 8));
        goto done;
    }
    value |= (uint) (((uchar)data[1]) << 8);
    numberOfBits -= 8;
    if (numberOfBits <= 8)
    {
        uint num2 = (uint) (((uchar)data[2]) << 0x10);
        endvalue = (value | num2);
        goto done;
    }
    value |= (uint) (((uchar)data[2]) << 0x10);
    numberOfBits -= 8;
    endvalue =  (value | ((uint) (((uchar)data[3]) << 0x18)));
    goto done;

    done:

    float num = max - min;
    int num2 = (((int) 1) << numberOfBits) - 1;
    float num3 = endvalue;
    float num4 = num3 / ((float) num2);
    return (min + (num4 * num));
}

QByteArray rangedSingleToData(float value, float min, float max, int numberOfBits)
{
    QByteArray data;
    float num = max - min;
    float num2 = (value - min) / num;
    int num3 = (((int) 1) << numberOfBits) - 1;
    uint source = num3 * num2;

    if (numberOfBits <= 8)
    {
        data += (unsigned char)source;
        return data;
    }
    data += (unsigned char)source;
    numberOfBits -= 8;
    if (numberOfBits <= 8)
    {
        data += (unsigned char)source>>8;
        return data;
    }
    data += (unsigned char)source>>8;
    numberOfBits -= 8;
    if (numberOfBits <= 8)
    {
        data += (unsigned char)source>>16;
        return data;
    }
    data += (unsigned char)source>>16;
    data += (unsigned char)source>>24;

    return data;
}

uint8_t dataToUint8(QByteArray data)
{
    return (uint8_t)data[0];
}

uint16_t dataToUint16(QByteArray data)
{
    return ((uint16_t)(uint8_t)data[0])
            +(((uint16_t)(uint8_t)data[1])<<8);
}

uint32_t dataToUint32(QByteArray data)
{
    return ((uint32_t)(uint8_t)data[0])
            +(((uint32_t)(uint8_t)data[1])<<8)
            +(((uint32_t)(uint8_t)data[2])<<16)
            +(((uint32_t)(uint8_t)data[3])<<24);
}

unsigned getVUint32Size(QByteArray data)
{
    unsigned lensize=0;
    {
        unsigned char num3;
        do {
            num3 = data[lensize];
            lensize++;
        } while ((num3 & 0x80) != 0);
    }
    return lensize;
}

QByteArray uint8ToData(uint8_t num)
{
    QByteArray data(1,0);
    data[0] = (uint8_t)num;
    return data;
}

QByteArray uint16ToData(uint16_t num)
{
    QByteArray data(2,0);
    data[0] = (uint8_t)(num & 0xFF);
    data[1] = (uint8_t)((num>>8) & 0xFF);
    return data;
}

QByteArray uint32ToData(uint32_t num)
{
    QByteArray data(4,0);
    data[0] = (uint8_t)(num & 0xFF);
    data[1] = (uint8_t)((num>>8) & 0xFF);
    data[2] = (uint8_t)((num>>16) & 0xFF);
    data[3] = (uint8_t)((num>>24) & 0xFF);
    return data;
}
